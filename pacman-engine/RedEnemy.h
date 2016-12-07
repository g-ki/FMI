//
//  RedEnemy.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 1/2/15.
//  Copyright (c) 2015 Georgi Kiryakov. All rights reserved.
//

#ifndef PacManGame_RedEnemy_h
#define PacManGame_RedEnemy_h

#include "GameEngine.h"
#include "Enemy.h"

class RedEnemyMove : public EnemyMove {
public:
    
    RedEnemyMove(GameObject *g) : EnemyMove(g){
    
    }
    void ExitHome(){
        mode = EnemyMode::ExitHome;
        transform->position.Set(17*TILE_SIZE+ TILE_SIZE/2, 14*TILE_SIZE+ TILE_SIZE/2);
    }
    
    void Scatter(){
        mode = EnemyMode::Scatter;
        this->targetTile.Set(24, 6);
    }

};

class RedEnemy : public Enemy {
public:
    RedEnemy() : Enemy("RedEnemy"){
        this->transform->position.Set(WIN_SIZE_X/2, WIN_SIZE_Y/2 - 4*TILE_SIZE);
        this->AddComponent<RedEnemyMove>();
    }
    
    void Start(){
        this->transform->position.Set(WIN_SIZE_X/2, WIN_SIZE_Y/2 - 4*TILE_SIZE);
        GameObject::Start();
    }
    
    void Render(){
        al_draw_filled_rectangle(transform->position.x - transform->scale.x/2,
                                 transform->position.y - transform->scale.y/2,
                                 transform->position.x + transform->scale.x/2,
                                 transform->position.y + transform->scale.y/2,
                                 al_map_rgb(255, 0, 0));
    }
};

#endif
