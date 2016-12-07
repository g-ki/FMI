//
//  EnemyMove.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/22/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef PacManGame_EnemyMove_h
#define PacManGame_EnemyMove_h

#include "GameEngine.h"
#include "Move.h"


class EnemyMove : public Move{
protected:
    Vector2 targetTile;
    Vector2 homeTile;
    float targetDist;
    EnemyMode mode;
    GameObject *player;
public:
    
    EnemyMove(GameObject *gameObject) : Move(gameObject)
    {
        direction = Vector2::up() * -1;
        speed = 3;
    }
    
    void SetTarget(float x, float y)
    {
        this->targetTile.Set(x, y);
        this->targetTile = WichTileIs(this->targetTile);
    }
    
    int Options(){
        int count = 0;
        if(top)
            count++;
        if(bottom)
            count++;
        if(right)
            count++;
        if(left)
            count++;
        
        return count;
    }
    
    virtual void Scatter(){
        mode = EnemyMode::Scatter;
        SetTarget(0, 0);
    }
    
    virtual void Chase(){
        if(player == nullptr)
        {
            Scatter();
            return;
        }
        mode = EnemyMode::Chase;
        SetTarget(player->transform->position.x, player->transform->position.y);
    }
    
    virtual void Frightened() {
        mode = EnemyMode::Frightened;
        if(Options() > 1)
        {
            float x = rand()%WIN_SIZE_X,
            y = rand()%WIN_SIZE_Y;
            SetTarget(x, y);
        }
    }
    
    virtual void ExitHome(){
        mode = EnemyMode::ExitHome;
        transform->position.Set(14*TILE_SIZE, 14*TILE_SIZE);
    }
    
    /* Game */
    
    void Start(){
        player = Game.GetScene()->Get("MainPlayer");
        ExitHome();
        top = right = left = bottom = true;
    }
    
    void Update(){
        
        if(mode == EnemyMode::Chase)
            Chase();
        else if(mode == EnemyMode::Frightened)
            Frightened();
        else if(mode == EnemyMode::ExitHome)
            Chase();
        
        //std::cout<<gameObject->ToString()<<" "<<targetTile.x<<" "<<targetTile.y<<'\n';
        
        
        int options = Options();
        if(options <= 1)
        {
            if(top)
                direction = Vector2::up();
            else if(right)
                direction = Vector2::right() * -1;
            else if(bottom)
                direction = Vector2::up() * -1;
            else if(left)
                direction = Vector2::right();
            
        } else {
            
            float dist[4] = {2000, 2000, 2000, 2000};
            
            if(top)
                dist[0] = Vector2::Distance(TilePosition() - Vector2::up(), targetTile);
            if(right)
                dist[1] = Vector2::Distance(TilePosition() + Vector2::right(), targetTile);
            if(bottom)
                dist[2] = Vector2::Distance(TilePosition() + Vector2::up(), targetTile);
            if(left)
                dist[3] = Vector2::Distance(TilePosition() - Vector2::right(), targetTile);
            
            float minDist = 2000;
            int minIndex = 4;
            
            for (int i=0; i<4; i++)
                if(dist[i] < minDist){
                    minDist = dist[i];
                    minIndex = i;
                }
            
            switch (minIndex) {
                case 0:
                    direction = Vector2::up();
                    break;
                case 1:
                    direction = Vector2::right() * -1;
                    break;
                case 2:
                    direction = Vector2::up() * -1;
                    break;
                case 3:
                    direction = Vector2::right();
                    break;
            }
        
        }
        
        transform->position = transform->position - direction*speed;
        transform->rotation = direction;
        
        Vector2 perfectPos = TilePosition()*TILE_SIZE + Vector2(TILE_SIZE/2, TILE_SIZE/2);
        float dist = Vector2::Distance(transform->position, perfectPos);
        
        if(transform->position.x > WIN_SIZE_X)
            transform->position.x -= WIN_SIZE_X;
        else if(transform->position.x < 0)
            transform->position.x += WIN_SIZE_X;
        
        if(dist<speed)
            top = right = left = bottom = true;
        
        speed = 3;
    }
    
    void OnContact(Component *go){
        Move::OnContact(go);
        
        if(direction == Vector2::right() * -1)
            left = false;
        else if(direction == Vector2::right())
            right = false;
        else if(direction == Vector2::up())
            bottom = false;
        else if(direction == Vector2::up() * -1)
            top = false;
    }
    
    void OnCollision(Component *go){
        
        if(go->collider->type==ColliderType::Wall)
        {
            Vector2 perfectPos = TilePosition()*TILE_SIZE + Vector2(TILE_SIZE/2, TILE_SIZE/2);
            transform->position = perfectPos;
        }
        else if(go->collider->type==ColliderType::Slow)
        {
            speed = 2;
        }
        
    }
};

#endif
