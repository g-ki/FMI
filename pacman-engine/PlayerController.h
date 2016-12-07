//
//  PlayerController.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 1/4/15.
//  Copyright (c) 2015 Georgi Kiryakov. All rights reserved.
//

#ifndef PacManGame_PlayerController_h
#define PacManGame_PlayerController_h

#include "GameEngine.h"
#include <ctime>

class PlayerController : public GameBehaviour {
protected:
    int score;
    int lives;
    bool isEnergyzed;
    
    std::clock_t timer;
    
public:
    
    PlayerController(GameObject *gameObject) : GameBehaviour(gameObject, "PlayerController"){
        score = 0;
        lives = 3;
        isEnergyzed = false;
    }
    
    void Start(){
        this->transform->position.Set(14 * TILE_SIZE , 26 * TILE_SIZE);
    }

    
    void Update(){
        
        std::cout<<"\n+Score: "<<score;
        std::cout<<"\n+Lives: "<<lives;
        
        if(isEnergyzed){
             if((std::clock() - timer) / (double)(CLOCKS_PER_SEC) > 10)
             {
                 isEnergyzed = false;
                 Global.gameMode = EnemyMode::Chase;
             }
        }
    }
    
    
    void OnCollision(Component *go){
    
        if(go->collider->type==ColliderType::Food)
        {
            Game.GetScene()->Remove(go);
            score +=20;
        } else if(go->collider->type==ColliderType::Energizer)
        {
            Game.GetScene()->Remove(go);
            score +=40;
            isEnergyzed = true;
            timer = std::clock();
            Global.gameMode = EnemyMode::Frightened;
            
        } else if(go->collider->type == ColliderType::Enemy)
        {
            if(!isEnergyzed)
            {
                lives--;
                Game.GetScene()->Start();
                
                if(lives<=0)
                {
                    std::cout<<"\n----- Game Over!!! -----\n";
                    Game.Stop();
                    
                }
            } else {
                score +=200;
                go->Start();
            }
        }
        
        
    }
    
    
    
};


#endif
