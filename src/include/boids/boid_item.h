#ifndef BOIDS_ITEM
#define BOIDS_ITEM

 //#include <SDL2/SDL.h>
#include <random>
#include <vector>
#include <iostream>
#include <cmath>
#include <random>

#include <SDL2/SDL.h>
#include "../pVector/pVector.h"

#define PI 3.14159265

class boid
{
    public:
        pVector position;
        pVector velocity;
        pVector acceleration;
        float maxForce = 0.05;
        float maxSpeed = 0.5;
        bool subject = false;

        boid(float p_x, float p_y, float v_x, float v_y, float a_x, float a_y): position(p_x, p_y), velocity(v_x, v_y), acceleration(a_x, a_y) {};
        void drawCircle(SDL_Renderer* renderer, float centerX, float centerY, float radius);
        void DrawRotatedTriangle(SDL_Renderer* renderer, float x, float y, float rotation);
        void update();
        std::vector<boid> get_nearby_boids(SDL_Renderer* renderer, std::vector<boid> *flock, float radius);
        pVector align(std::vector<boid> *flock);
        pVector cohesion(std::vector<boid> *flock);
        pVector seperation(std::vector<boid> *flock);
        float distance(boid other);
        float CalculateVectorAngle();
        void draw_line(SDL_Renderer* renderer, boid other); 

    private:
};



#endif 