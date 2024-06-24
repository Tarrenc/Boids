#ifndef __FLOCKING_H__
#define __FLOCKING_H__


#include "../boids/boid_item.h"
#include "../screen/screen.h"
#include "../pVector/pVector.h"
#include <vector>

class flock
{

    public:

        std::vector<boid> birds;

        flock(int n_boids);
        void update_flock(SDL_Renderer* renderer);
        ~flock();

    private:
        float generate_random_number(float min, float max);

};


#endif //__FLOCKING_H__
