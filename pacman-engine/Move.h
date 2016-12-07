//
//  Move.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/29/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef PacManGame_Move_h
#define PacManGame_Move_h

#include "GameEngine.h"

class Move : public GameBehaviour {
protected:
    bool top=true, left=true, right=true, bottom=true;
public:
    Move(GameObject* gameObject) : GameBehaviour(gameObject, "MoveBehaviour"){
        direction = Vector2::zero();
    }
    
    Vector2 direction, lastDir;
    float speed = 3.5;
    
    Vector2 WichTileIs(Vector2 v){
        return Vector2((int)(v.x/TILE_SIZE), (int)(v.y/TILE_SIZE));
    }
    
    Vector2 TilePosition(){
        return WichTileIs(transform->position);
    }
    
    void Update(){
        
        lastDir = direction;
        
        if(Global.Input(ALLEGRO_KEY_W))
            direction = Vector2::up();
        else if(Global.Input(ALLEGRO_KEY_D))
            direction = Vector2::right()*(-1);
        else if(Global.Input(ALLEGRO_KEY_S))
            direction = Vector2::up()*(-1);
        else if(Global.Input(ALLEGRO_KEY_A))
            direction = Vector2::right();
        
        
        if((!top && direction == Vector2::up())
           || (!bottom && direction == Vector2::up()*(-1))
           || (!left && direction == Vector2::right())
           || (!right && direction == Vector2::right()*(-1)))
        {
            direction = lastDir;
        }
        
        transform->position = transform->position - direction*speed;
        transform->rotation = direction;
        
        Vector2 perfectPos = TilePosition()*TILE_SIZE + Vector2(TILE_SIZE/2, TILE_SIZE/2);
        float dist = Vector2::Distance(transform->position, perfectPos);
        
        if(dist < speed)
            transform->position = perfectPos;
        
        if(transform->position.x > WIN_SIZE_X)
            transform->position.x -= WIN_SIZE_X;
        else if(transform->position.x < 0)
            transform->position.x += WIN_SIZE_X;
            
        
        Global.playerTileX = transform->position.x;
        Global.playerTileY = transform->position.y;
        
        if(dist<=speed)
            top = right = left = bottom = true;
    }
    
    void OnContact(Component *go){
        
        // allowed directions
        if(go->collider->type==ColliderType::Wall){
            Vector2 v;
            v = WichTileIs(go->transform->position);
            
            int xT = v.x;
            int yT = v.y;
            
            v = TilePosition();
            
            if(v.x+1 == xT && v.y == yT)
                right = false;
            if(v.x-1 == xT && v.y == yT)
                left = false;
            if(v.x == xT && v.y-1 == yT)
                top = false;
            if(v.x == xT && v.y+1 == yT)
                bottom = false;
        }
    }
    void OnCollision(Component *go){
        
        if(go->collider->type==ColliderType::Wall)
        {
            transform->position = transform->position + direction*speed;
            Vector2 perfectPos = TilePosition()*TILE_SIZE + Vector2(TILE_SIZE/2, TILE_SIZE/2);
            transform->position = perfectPos;
            
            direction = lastDir;
        }
    }
};


#endif
