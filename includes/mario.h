#ifndef __MARIO
#define __MARIO

#include <SDL.h>
#define MARIO_WIDTH 50
#define MARIO_HEIGTH 50
#define PLAYER_SPEED 5
enum {SEE_RIGHT, SEE_LEFT};

typedef struct Mario{
    int state;
    SDL_Texture* player_image;
    SDL_Rect player_position;
} Mario;

Mario initPlayer(SDL_Renderer **screen_render);
void printPlayer(Mario mario, SDL_Renderer **screen_render);
#endif