//
//  CollisionSystem.cpp
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/21/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#include "CollisionSystem.h"

void CollisionSystem::CollisionChek(){
    //std::cout<<tiles.size()<<'\n';
    for(auto tile : tiles){
        unsigned size = tile.gameObjects.size();
        for (unsigned i=0; i<size; i++) {
            for (unsigned j=0; j<tile.gameObjects.size()-1; j++) {
                
                if(tile.gameObjects.front()->collider->type==ColliderType::Wall
                   && tile.gameObjects[j+1]->collider->type==ColliderType::Wall)
                    continue;
                
                if(tile.gameObjects.front()->collider->type==ColliderType::Food
                   && tile.gameObjects[j+1]->collider->type==ColliderType::Food)
                    continue;
                    
                if(tile.gameObjects.front()->collider->Contact(*tile.gameObjects[j+1]->collider))
                {
                    tile.gameObjects.front()->OnContact(tile.gameObjects[j+1]);
                    tile.gameObjects[j+1]->OnContact(tile.gameObjects.front());
                    if(tile.gameObjects.front()->collider->Collision(*tile.gameObjects[j+1]->collider)){
                        tile.gameObjects.front()->OnCollision(tile.gameObjects[j+1]);
                        tile.gameObjects[j+1]->OnCollision(tile.gameObjects.front());
                    }
                }
            }
        tile.gameObjects.erase(tile.gameObjects.begin());
        }
    }
    tiles.clear();
}

void CollisionSystem::AddObject(GameObject *go){
    if(go->collider == NULL)
        return;
    
    //std::cout<<go->ToString()<<std::endl;
    Vector2 topLeft, bottomRight;
    
    topLeft = (go->transform->position-Vector2::one() - go->transform->scale/2)/tileSize;
    bottomRight = (go->transform->position+Vector2::one() + go->transform->scale/2)/tileSize;
    
    int n = bottomRight.x;
    int m = bottomRight.y;
    
    for(int i = topLeft.x;i<=n;i++)
        for(int j = topLeft.y;j<=m;j++){
            AddToTile(i, j, go);
        }
    
}

void CollisionSystem::AddToTile(int x, int y, GameObject *go){
    unsigned size = tiles.size();
    for (unsigned i=0; i<size; i++) {
        if(x == tiles[i].x && y == tiles[i].y){
            tiles[i].gameObjects.push_back(go);
            //al_draw_circle(x*tileSize +tileSize/2, y*tileSize+tileSize/2, (tileSize+2)/2, al_map_rgb(0, 255, 0), 4);
            return;
        }
    }
    
    //al_draw_circle(x*tileSize +tileSize/2, y*tileSize+tileSize/2, tileSize/2, al_map_rgb(255, 0, 255), 4);
    CollisionTile t;
    t.Set(x, y);
    t.gameObjects.push_back(go);
    tiles.push_back(t);
}