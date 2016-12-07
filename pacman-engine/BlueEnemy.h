//
//  BlueEnemy.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 1/3/15.
//  Copyright (c) 2015 Georgi Kiryakov. All rights reserved.
//

#ifndef PacManGame_BlueEnemy_h
#define PacManGame_BlueEnemy_h

#include "GameEngine.h"
#include "Enemy.h"

class BlueEnemyMove : public EnemyMove {
public:
    
    GameObject *redEnemy;
    
    BlueEnemyMove(GameObject *g) : EnemyMove(g){
        
    }
    
    void Start(){
        EnemyMove::Start();
    }
    
    void Scatter(){
        mode = EnemyMode::Scatter;
        this->targetTile.Set(WIN_SIZE_X, WIN_SIZE_X);
    }
    
    virtual void ExitHome(){
        mode = EnemyMode::ExitHome;
        transform->position.Set(12*TILE_SIZE+ TILE_SIZE/2, 14*TILE_SIZE+ TILE_SIZE/2);
    }
    
    void Chase(){
        if(player == nullptr)
        {
            Scatter();
            return;
        }
        
        if(redEnemy == nullptr)
            redEnemy = Game.GetScene()->Get("RedEnemy");
        
        if(redEnemy == nullptr){
            Scatter();
            return;
        }
        
        mode = EnemyMode::Chase;
        
        Vector2 t;
        t.x = player->transform->position.x - player->transform->rotation.x*TILE_SIZE*2;
        t.y = player->transform->position.y - player->transform->rotation.y*TILE_SIZE*2;
        
        t.x = 2*t.x - redEnemy->transform->position.x;
        t.y = 2*t.y - redEnemy->transform->position.y;
        
        SetTarget(t.x, t.y);
    }
};

class BlueEnemy : public Enemy {
public:
    BlueEnemy() : Enemy("BlueEnemy"){
        this->AddComponent<BlueEnemyMove>();
    }
    
    void Render(){
        al_draw_filled_rectangle(transform->position.x - transform->scale.x/2,
                                 transform->position.y - transform->scale.y/2,
                                 transform->position.x + transform->scale.x/2,
                                 transform->position.y + transform->scale.y/2,
                                 al_map_rgb(0, 0, 255));
    }
};


#endif
