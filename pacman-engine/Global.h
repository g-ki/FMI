//
//  Global.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/17/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef PacManGame_Global_h
#define PacManGame_Global_h

#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#define WIN_SIZE_X 504
#define WIN_SIZE_Y 648
#define TILE_SIZE 18

enum EnemyMode {Scatter, Chase, Frightened, ExitHome};

class __Global {
public:
    ALLEGRO_KEYBOARD_STATE keyboardState;
    ALLEGRO_MOUSE_STATE mouseState;
    ALLEGRO_FONT *font;
    
    EnemyMode gameMode;
    
    int playerTileX=0, playerTileY=0;
    
    bool Input(int keycode){
        return al_key_down(&keyboardState, keycode);
    }
    
    int MouseAxis(int axis){
        switch (axis) {
            case 1:
                return mouseState.x;
                break;
            case 2:
                return mouseState.y;
                break;
        }
        
        return 0;
    }
};

extern __Global Global;

#endif
