#include <time.h>
#include "../includes/startGame.h"
#include "../includes/map.h"
#include "../includes/moveMapAndPlayer.h"
#include "../includes/mario.h"
#include "../includes/cam.h"
#include "../includes/utils.h"

void play(SDL_Renderer **screen_renderer){
    SDL_Event e;
    int continuer=1, timeContinue = SDL_GetTicks(), s=0, gravity_active = 1, colision;

    Map my_map = initMap("levelFile/lvl1.txt", screen_renderer);
    Mario my_mario = initPlayer(screen_renderer);
    CamGame game_camera = initCam(my_mario);


    while (continuer){
        // if(gravity_active && SDL_GetTicks() - timeContinue >= 5){
        // gravity(&my_mario, &my_map, &game_camera);
        // // printf("%d\n\n", s++);
        // timeContinue = SDL_GetTicks();
        // }else if(!gravity_active && SDL_GetTicks() - timeContinue >= 5){
        //     jump(&my_mario, &my_map, &game_camera, &gravity_active);
        //     timeContinue = SDL_GetTicks();
        // }

        if(SDL_GetTicks() - timeContinue >= 5){
            
            if (gravity_active)
                gravity(&my_mario, &my_map, &game_camera);
            else
                jump(&my_mario, &my_map, &game_camera, &gravity_active);
            
            timeContinue = SDL_GetTicks();
        }

        // printf("\nCamera : %d %d\n\nMario : %d %d\n", game_camera.cam.x, game_camera.cam.y, my_mario.player_position.x, my_mario.player_position.y);

        while (SDL_PollEvent(&e)){
            switch (e.type){
                case SDL_QUIT:
                destroyMap(my_map);
                destroyPlayer(my_mario);
                continuer=0;
                break;

			case SDL_KEYDOWN:
				switch (e.key.keysym.sym){
					case  SDLK_RIGHT:
                    colision = testColision(game_camera, my_map, my_mario, RIGTH);
                    printf("Colison : %d\n", colision);
                    move(RIGTH, &my_mario, &my_map, &game_camera, colision);
					break;

					case  SDLK_LEFT:
                    colision = testColision(game_camera, my_map, my_mario, LEFT);
                    printf("Colison : %d\n", colision);
                    move(LEFT, &my_mario, &my_map, &game_camera, colision);
					break;

                    case SDLK_SPACE:
                    gravity_active = 0;
                    break;
				}
                // printf("\nCamera : %d %d\n\nMario : %d %d\n", game_camera.cam.x, game_camera.cam.y, my_mario.player_position.x, my_mario.player_position.y);
				break;

            }

        }
        SDL_RenderClear(*screen_renderer);
        if (continuer){
            printMap(my_map, my_mario, screen_renderer, game_camera);
            printPlayer(my_mario, screen_renderer);
        }
        SDL_RenderPresent(*screen_renderer);
    }
}