#include "flocking.h"

flock::flock(int n_boids)
{
   for (int i = 0; i < n_boids; ++i)
    {
        this->birds.push_back(boid(generate_random_number(0,1250),generate_random_number(0,750),
                           generate_random_number(-1,1),generate_random_number(-1,1),
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
    for (auto& current_boid : this->birds)
    { 
        std::vector<boid> local_flockmates = current_boid.get_nearby_boids(renderer, &(this->birds), 100);
        pVector alignment = current_boid.align(&local_flockmates);
        pVector cohesion = current_boid.cohesion(&local_flockmates);
        pVector seperation = current_boid.seperation(&local_flockmates);
        current_boid.acceleration = seperation + alignment + cohesion;
        
        current_boid.update();
        float angle = current_boid.CalculateVectorAngle();
        current_boid.DrawRotatedTriangle(renderer, current_boid.position.x, current_boid.position.y, angle);
    }
}