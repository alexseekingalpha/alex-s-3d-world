#include <SDL3/SDL.h>

int main () { 
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
SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
if (!renderer) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}
SDL_FRect rectangle = {100, 100, 200, 150};
bool running = true;

SDL_Event event; 

while (running) {
    while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
        running = false;
        }
    }
    const bool * keyboard = SDL_GetKeyboardState(nullptr);
    if (keyboard[SDL_SCANCODE_D]) {
        rectangle.x +=1;
    }

    if (keyboard[SDL_SCANCODE_A]) {
        rectangle.x -= 1;
    }


        SDL_SetRenderDrawColor(renderer, 25, 55, 95, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 239, 156, 60, 255);
        SDL_RenderFillRect(renderer, &rectangle);

        SDL_RenderPresent(renderer);
    }

    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}