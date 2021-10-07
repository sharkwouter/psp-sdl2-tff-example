#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define NAME "Font Example"
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
    printf("Starting game\n");
    if (setupSdl() != 0) {
        return 1;
    }

    if (TTF_Init() == -1) {
        return 5;
    }
    // open font files
    TTF_Font *font2P = TTF_OpenFont("PressStart2P.ttf", 16);
    if (font2P == NULL) {
        printf("TTF_OpenFont font2P: %s\n", TTF_GetError());
        return 2;
    }
    TTF_Font *fontSquare = TTF_OpenFont("square_sans_serif_7.ttf", 64);
    if (fontSquare == NULL) {
        printf("TTF_OpenFont fontSquare: %s\n", TTF_GetError());
        return 2;
    }
    // load title
    SDL_Color fontColor = {0, 0, 0};
    SDL_Surface *surface1 = TTF_RenderUTF8_Blended(fontSquare, "Title", fontColor);
    if (surface1 == NULL) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load create title! SDL Error: %s\n", SDL_GetError());
        return 3;
    }
    SDL_Texture* title = SDL_CreateTextureFromSurface(renderer, surface1);
    if (title == NULL) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load texture for image block.bmp! SDL Error: %s\n", SDL_GetError());
        return 4;
    }
    SDL_FreeSurface(surface1);

    // load subtitle
    SDL_Surface *surface2 = TTF_RenderUTF8_Blended(font2P, "Subtitle", fontColor);
    if (surface2 == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load create subtitle! SDL Error: %s\n", SDL_GetError());
        return 3;
    }
    SDL_Texture* subtitle = SDL_CreateTextureFromSurface(renderer, surface2);
    if (title == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load texture for image block.bmp! SDL Error: %s\n", SDL_GetError());
        return 4;
    }
    SDL_FreeSurface(surface2);

    // Create SDL 
    SDL_Rect titleRect;
    SDL_QueryTexture(title, NULL, NULL, &titleRect.w, &titleRect.h);
    titleRect.x = WIDTH/2 - titleRect.w/2;
    titleRect.y = HEIGHT/2 - titleRect.h/2;

    SDL_Rect subtitleRect;
    SDL_QueryTexture(subtitle, NULL, NULL, &subtitleRect.w, &subtitleRect.h);
    subtitleRect.x = WIDTH/2 - subtitleRect.w/2;
    subtitleRect.y = titleRect.y + titleRect.h + subtitleRect.h/2;

    while (!closed) {
        handleEvents();
        SDL_RenderCopy(renderer, title, NULL, &titleRect);
        SDL_RenderCopy(renderer, subtitle, NULL, &subtitleRect);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
    }
    return 0;
}

#ifdef __PSP__
int SDL_main(int argc, char *argv[]) {
    SDL_strlen("test");
    return game(argc, argv);
}
#else
int main(int argc, char *argv[]) {
    return game(argc, argv);
}
#endif
