#include <SDL3/SDL.h>

int main () { SDL_Init(SDL_INIT_VIDEO);
    if (!SDL_Init(SDL_INIT_VIDEO)){
        return 1;
    }
SDL_Window* window = SDL_CreateWindow(
    "Alex's 3D World",
    1000,
    700,
    SDL_WINDOW_RESIZABLE
);
if (!window) {
    return 1;
}
bool running = true;

SDL_Event event; 

while (running) {
    while (SDL_PollEvent(&event))
    if (event.type == SDL_EVENT_QUIT) {
        running = false;
        }

    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}