#include "boid_item.h"


void boid::drawCircle(SDL_Renderer* renderer, float centerX, float centerY, float radius)
{
    // Convert floating-point positions to integers
    int x0 = static_cast<int>(centerX);
    int y0 = static_cast<int>(centerY);
    int r = static_cast<int>(radius);

    int x = r - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (r << 1);

    while (x >= y) 
    {
        // Draw the circle's points in each octant
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);

        if (err <= 0) 
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) 
        {
            x--;
            dx += 2;
            err += dx - (r << 1);
        }
    }
}

void boid::update()
{
    this->position = this->velocity + this->position;
    this->velocity = this->velocity + this->acceleration;
    this->acceleration = pVector(0,0);
    this->velocity.limit(maxSpeed);

    if (this->position.x > 1250)
    {
        this->position.x = 0;
        //this->position.y = 750 - this->position.y;
    }
    else if (this->position.x < 0)
    {
        this->position.x = 1250;
        //this->position.y = 750 - this->position.y;
    }

    if (this->position.y > 750)
    {
        this->position.y = 0;
        //this->position.x = 750 - this->position.x;
    }
    else if (this->position.y < 0)
    {
        this->position.y = 750;
        //this->position.x = 750 - this->position.x;
    }


}

float boid::distance(boid other)
{
    float dx = this->position.x - other.position.x;
    float dy = this->position.y - other.position.y;

    return std::sqrt((dx * dx) + (dy * dy));
}

pVector boid::align(std::vector<boid> flock)
{
    pVector average = pVector(0,0);
    float radius = 50;
    int total = 0;
    float distance = 0;
    for (auto& boid : flock)
    {
        distance = this->distance(boid);
        //std::cout << distance << std::endl;
        if (&boid != this && distance < radius)
        {
            average = average + boid.velocity;
            total++;
        }
    }

    //std::cout << total << std::endl;
    if (total > 0)
    {
        average = average / total;
        average.setMagnitude(this->maxSpeed);
        average = average - this->velocity;
        average.limit(this->maxForce);
    }
    return average;
}

pVector boid::cohesion(std::vector<boid> flock)
{
    pVector average = pVector(0,0);
    float radius = 50;
    int total = 0;
    float distance = 0;
    for (auto& boid : flock)
    {
        distance = this->distance(boid);
        //std::cout << distance << std::endl;
        if (&boid != this && distance < radius)
        {
            average = average + boid.position;
            total++;
        }
    }

    //std::cout << total << std::endl;
    if (total > 0)
    {
        average = average / total;
        average = average - this->position;
        average.setMagnitude(this->maxSpeed);
        //std::cout << average.x << std::endl;
        average = average - this->velocity;
        average.limit(this->maxForce);
    }
   return average;
}

pVector boid::seperation(std::vector<boid> flock)
{
    pVector average = pVector(0,0);
    pVector diff = pVector(0,0);
    float radius = 50;
    int total = 0;
    float distance = 0;
    for (auto& boid : flock)
    {
        distance = this->distance(boid);
        if (&boid != this && distance < radius)
        {
            diff = this->position - boid.position;
            if (distance != 0)
            {
                diff = diff / (distance * distance);
                average = average + diff;
                total++;    
            }

        }
    }

    if (total > 0)
    {
        average = average / total;
        average.setMagnitude(this->maxSpeed);
        average = average - this->velocity;
        average.limit(this->maxForce);
    }

   return average;
}

void boid::DrawRotatedTriangle(SDL_Renderer* renderer, float x, float y, float rotation) 
{
// Triangle dimensions (height and base half-length)
    const float height = 20.0f;
    const float halfBase = 5.0f;

    // Convert rotation angle to radians
    float angle = rotation * PI / 180.0f;

    // Calculate the vertices of the triangle
    SDL_FPoint vertices[3];

    // Top vertex (rotated upwards along the y-axis)
    vertices[0].x = x + height * cosf(angle);
    vertices[0].y = y + height * sinf(angle);

    // Bottom left vertex (rotated to the left)
    float leftAngle = angle + 3.0f * PI / 2.0f; // 270 degrees
    vertices[1].x = x + halfBase * cosf(leftAngle);
    vertices[1].y = y + halfBase * sinf(leftAngle);

    // Bottom right vertex (rotated to the right)
    float rightAngle = angle + PI / 2.0f; // 90 degrees
    vertices[2].x = x + halfBase * cosf(rightAngle);
    vertices[2].y = y + halfBase * sinf(rightAngle);

    // Draw the triangle
    SDL_RenderDrawLineF(renderer, vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y);
    SDL_RenderDrawLineF(renderer, vertices[1].x, vertices[1].y, vertices[2].x, vertices[2].y);
    SDL_RenderDrawLineF(renderer, vertices[2].x, vertices[2].y, vertices[0].x, vertices[0].y);
}

float boid::CalculateVectorAngle() {
    // Use atan2 to get the angle in radians
    float angleRadians = atan2f(this->velocity.y, this->velocity.x);
    // Convert the angle from radians to degrees
    float angleDegrees = angleRadians * 180.0f / PI;
    return angleDegrees;
}