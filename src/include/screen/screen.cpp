#include "screen.h"
#include <vector>

std::vector<boid> boids;
int numBoids = 200;

float getRandomNumber(float min, float max) 
{
    // Create a random device and use it to seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    // Define the range for the distribution
    std::uniform_real_distribution<> distr(min, max);
    // Generate and return a random float within the specified range
    return distr(gen);
}

void createSDLWindow() 
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Boids",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1250, 750,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) 
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    // Create renderer for window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) 
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    flock flock(100);

    // While application is running
    while (!quit) 
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) 
        {
            // User requests quit
            if (e.type == SDL_QUIT) 
            {
                quit = true;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        flock.update_flock(renderer);

        // Update screen
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();
}

