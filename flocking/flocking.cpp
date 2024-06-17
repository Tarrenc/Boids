#include "flocking.h"

flock::flock(int n_boids)
{

   for (int i = 0; i < n_boids; ++i)
    {
        this->birds.push_back(boid(generate_random_number(0,1250),generate_random_number(0,750),
                           generate_random_number(-5,5),generate_random_number(-5,5),
                           generate_random_number(-0.1,0.1),generate_random_number(-0.1,0.1)));
    }
}

flock::~flock(){
    std::cout << "My flock has been destroyed" << std::endl;
}

float flock::generate_random_number(float min, float max) 
{
    // Create a random device and seed the generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define a uniform real distribution between min and max
    std::uniform_real_distribution<float> distrib(min, max);

    // Generate and return a random number
    return distrib(gen);
}

void flock::update_flock(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    this->birds[0].subject = true;
    for (auto& boid : this->birds)
    {
        pVector alignment = boid.align(this->birds);
        pVector cohesion = boid.cohesion(this->birds);
        pVector seperation = boid.seperation(this->birds);
        boid.acceleration = alignment + cohesion + seperation;
        
        boid.update();
        float angle = boid.CalculateVectorAngle();
        boid.DrawRotatedTriangle(renderer, boid.position.x, boid.position.y, angle);
    }
}