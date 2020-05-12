#include <SDL2/SDL.h>

#define NAME "Jewels"
#define WIDTH 480
#define HEIGHT 272

int closed = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int setupSdl() {
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);

    window = SDL_CreateWindow(
        NAME,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initiation window. Error %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize renderer. Error: %s", SDL_GetError());
        return 1;
    }

    return 0;
}

void handleEvents(){
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                closed = 1;
                break;
        }
    }
}

int game(int argc, char *argv[]){
    if (setupSdl() != 0) {
        return 1;
    }

    // load image
    SDL_Surface* surface = NULL;
    surface = SDL_LoadBMP("block.bmp");
    if (surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load image block.bmp! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Texture* block = NULL;
    block = SDL_CreateTextureFromSurface(renderer, surface);
    if (block == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load texture for image block.bmp! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_FreeSurface(surface);

    // Create SDL rect
    SDL_Rect blockRect;
    SDL_QueryTexture(block, NULL, NULL, &blockRect.w, &blockRect.h);
    blockRect.x = WIDTH/2;
    blockRect.y = HEIGHT/2;

    while (!closed) {
        handleEvents();
        SDL_RenderCopy(renderer, block, NULL, &blockRect);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
    }
    return 0;
}

#ifdef __PSP__
int SDL_main(int argc, char *argv[]) {
    return game(argc, argv);
}
#else
int main(int argc, char *argv[]) {
    return game(argc, argv);
}
#endif
