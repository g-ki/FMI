//
//  CollisionSystem.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/21/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef __PacManGame__CollisionSystem__
#define __PacManGame__CollisionSystem__

#include <vector>
#include "Global.h"
#include "GameObject.h"

struct CollisionTile{
public:
    int x,y;
    std::vector<GameObject*> gameObjects;
    void Set(int x, int y){
        this->x = x;
        this->y = y;
    }
};

class CollisionSystem {
private:
    int tileSize;
    std::vector<CollisionTile> tiles;
    
    void AddToTile(int, int, GameObject*);
public:
    
    CollisionSystem(int tileSize){
        this->tileSize = tileSize;
    }
    
    void CollisionChek();
    void AddObject(GameObject*);
};

#endif /* defined(__PacManGame__CollisionSystem__) */
