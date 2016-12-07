//
//  Player.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/29/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef PacManGame_Player_h
#define PacManGame_Player_h

#include "GameEngine.h"
#include "Move.h"
#include "PlayerController.h"


class Player : public GameObject {
public:
    
    Player(std::string name) : GameObject(name){
        this->transform->position.Set(14 * TILE_SIZE , 26 * TILE_SIZE);
        this->transform->scale.Set(TILE_SIZE, TILE_SIZE);
        
        this->AddComponent<Move>();
        this->AddComponent<PlayerController>();
        
        this->collider = new Collider(&transform->position,
                                      this->transform->scale.x, this->transform->scale.y,
                                      ColliderType::PlayerCollider);
    }
    
    void Render(){
        al_draw_filled_circle(transform->position.x,
                              transform->position.y,
                              transform->scale.x/2,
                              al_map_rgb(255, 255, 0));
        //GameObject::Render();
    }
    
};

#endif
