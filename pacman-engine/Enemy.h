//
//  Enemy.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/29/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef PacManGame_Enemy_h
#define PacManGame_Enemy_h

#include "GameEngine.h"
#include "EnemyMove.h"

class Enemy : public GameObject {
    EnemyMove *move;
    Vector2 target;
    
public:
    Enemy(std::string name) : GameObject(name){
        
        this->transform->position.Set(WIN_SIZE_X/2, WIN_SIZE_Y/2 - TILE_SIZE);
        this->transform->scale.Set(TILE_SIZE, TILE_SIZE);
        
        this->collider = new Collider(&transform->position,
                                      this->transform->scale.x, this->transform->scale.y,
                                      ColliderType::Enemy);
    }
    
    void Start(){
        this->transform->position.Set(WIN_SIZE_X/2, WIN_SIZE_Y/2 - TILE_SIZE);
        GameObject::Start();
    }
    
    void Render(){
        al_draw_filled_rectangle(transform->position.x - transform->scale.x/2,
                                 transform->position.y - transform->scale.y/2,
                                 transform->position.x + transform->scale.x/2,
                                 transform->position.y + transform->scale.y/2,
                                 al_map_rgb(255, 0, 0));
        
        
        //GameObject::Render();
    }
    
};

#endif
