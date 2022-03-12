#include "../includes/moveMapAndPlayer.h"
#include "../includes/init.h"
#include "../includes/mario.h"
void moveMap(int direction, Map *map_to_move){
    int i, j, jumpCount, widthMap = map_to_move->map_width;

    for (i = 0; i < MAP_BLOC_HEIGTH; i++){
    
        switch (direction){
        case LEFT:
            if(!(map_to_move->data_map[i]->case_pos.x+PLAYER_SPEED>0))
                for (j = 0; j < widthMap; j++)
                    map_to_move->data_map[i][j].case_pos.x+=PLAYER_SPEED;
            break;

        case RIGTH:
            if(!(map_to_move->data_map[i][widthMap-1].case_pos.x-PLAYER_SPEED < SCREEN_WIDTH-UNIT_BLOC_GAME))
                for (j = 0; j < widthMap; j++)
                    map_to_move->data_map[i][j].case_pos.x-=PLAYER_SPEED;
            break;

        }
        
    }

    // for (i = 0; i < MAP_BLOC_HEIGTH; i++){
    //     for (j = 0; j < map_to_move->map_width; j++)
    //         printf("| %d %d |", map_to_move->data_map[i][j].case_pos.x, map_to_move->data_map[i][j].case_pos.y);

    //     printf("\n\n");
    // }
    
}

void movePlayer(int direction, Mario *mario){
    switch (direction){
        case LEFT:
            mario->player_position.x-= PLAYER_SPEED;
            break;

        case RIGTH:
            mario->player_position.x+= PLAYER_SPEED;
            break;

    }
}

void move(int direction, Mario *mario, Map *map, CamGame *cam_game){
    int  widthMap = map->map_width, i, j;
    switch (direction)
    {
    case RIGTH:
        if (!(mario->player_position.x + PLAYER_SPEED > SCREEN_WIDTH - MARIO_WIDTH)){

            cam_game->cam.x+=PLAYER_SPEED;

            if (mario->player_position.x != SCREEN_WIDTH * 2/3 || map->data_map[0][widthMap-1].case_pos.x-PLAYER_SPEED < SCREEN_WIDTH-UNIT_BLOC_GAME)
                mario->player_position.x+= PLAYER_SPEED;
            else if( !(map->data_map[0][widthMap-1].case_pos.x-PLAYER_SPEED < SCREEN_WIDTH-UNIT_BLOC_GAME))
                for (i = 0; i < MAP_BLOC_HEIGTH; i++)
                    for (j = 0; j < widthMap; j++)
                        map->data_map[i][j].case_pos.x-=PLAYER_SPEED;

        }       
        
        break;

    case LEFT:
        if (!(mario->player_position.x - PLAYER_SPEED < 0)){

            cam_game->cam.x-=PLAYER_SPEED;

            if (mario->player_position.x != SCREEN_WIDTH * 1/3 || map->data_map[0]->case_pos.x+PLAYER_SPEED > 0)
                mario->player_position.x-= PLAYER_SPEED;
            else if( !( map->data_map[0]->case_pos.x+PLAYER_SPEED > 0))
                for (i = 0; i < MAP_BLOC_HEIGTH; i++)
                    for (j = 0; j < widthMap; j++)
                        map->data_map[i][j].case_pos.x+=PLAYER_SPEED;

        }
    
    }
}

void jump(Mario *mario, Map *map, CamGame* camGame, int *gravity_status){
    static int jump_heigth=0;

    if (jump_heigth!=HEIGHT_JUMP){
        mario->player_position.y--;
        camGame->cam.y--;

        jump_heigth++;
    }else{
        jump_heigth = 0;
        *gravity_status = 1;    
    }
}