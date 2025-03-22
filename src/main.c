// hello
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char** argv) {
    if (!SDL_CreateWindowAndRenderer(
                "Picky", 900, 800,
                SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_BORDERLESS,
                &window, &renderer))
    {
        SDL_Log("Error: Unable to create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
            break;
        case SDL_EVENT_KEY_DOWN:
            ;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            ;
            break;
        case SDL_EVENT_MOUSE_MOTION:
            ;
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            ;
            break;
        default:
            break;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    ;
}
