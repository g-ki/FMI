//
//  OrangeEnemy.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 1/3/15.
//  Copyright (c) 2015 Georgi Kiryakov. All rights reserved.
//

#ifndef PacManGame_OrangeEnemy_h
#define PacManGame_OrangeEnemy_h

#include "GameEngine.h"
#include "Enemy.h"

class OrangeEnemyMove : public EnemyMove {
public:
    OrangeEnemyMove(GameObject *g) : EnemyMove(g){
        
    }
    
    void Start(){
        EnemyMove::Start();
    }
    
    void Scatter(){
        mode = EnemyMode::Scatter;
        this->targetTile.Set(0, 38);
    }
    
    virtual void ExitHome(){
        mode = EnemyMode::ExitHome;
        transform->position.Set(9*TILE_SIZE + TILE_SIZE/2, 15*TILE_SIZE+ TILE_SIZE/2);
    }
    
    void Chase(){
        
        if(player == nullptr)
        {
            Scatter();
            return;
        }
        
        
        mode = EnemyMode::Chase;
        
        float tileDist = Vector2::Distance(WichTileIs(player->transform->position),
                                           WichTileIs(this->transform->position));
        
        if(tileDist <=8){
            Scatter();
            return;
        }
        
        SetTarget(player->transform->position.x,
                  player->transform->position.y);
    }
};

class OrangeEnemy : public Enemy {
public:
    OrangeEnemy() : Enemy("OrangeEnemy"){
        this->AddComponent<OrangeEnemyMove>();
    }
    
    void Render(){
        al_draw_filled_rectangle(transform->position.x - transform->scale.x/2,
                                 transform->position.y - transform->scale.y/2,
                                 transform->position.x + transform->scale.x/2,
                                 transform->position.y + transform->scale.y/2,
                                 al_map_rgb(255, 165, 0));
    }
};


#endif
