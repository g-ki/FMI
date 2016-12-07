//
//  PinkEnemy.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 1/3/15.
//  Copyright (c) 2015 Georgi Kiryakov. All rights reserved.
//

#ifndef PacManGame_PinkEnemy_h
#define PacManGame_PinkEnemy_h

#include "GameEngine.h"
#include "Enemy.h"

class PinkEnemyMove : public EnemyMove {
public:
    
    PinkEnemyMove(GameObject *g) : EnemyMove(g){
        
    }
    
    void Scatter(){
        mode = EnemyMode::Scatter;
        this->targetTile.Set(0, 0);
    }
    
    virtual void ExitHome(){
        mode = EnemyMode::ExitHome;
        transform->position.Set(13*TILE_SIZE+ TILE_SIZE/2, 14*TILE_SIZE+ TILE_SIZE/2);
    }
    
    void Chase(){
        if(player == nullptr)
        {
            Scatter();
            return;
        }
        mode = EnemyMode::Chase;
        SetTarget(player->transform->position.x -
                  player->transform->rotation.x*TILE_SIZE*4,
                  player->transform->position.y -
                  player->transform->rotation.y*TILE_SIZE*4);
    }
};

class PinkEnemy : public Enemy {
public:
    PinkEnemy() : Enemy("PinkEnemy"){
        this->AddComponent<PinkEnemyMove>();
    }
    
    void Render(){
        al_draw_filled_rectangle(transform->position.x - transform->scale.x/2,
                                 transform->position.y - transform->scale.y/2,
                                 transform->position.x + transform->scale.x/2,
                                 transform->position.y + transform->scale.y/2,
                                 al_map_rgb(255, 105, 180));
    }
};


#endif
