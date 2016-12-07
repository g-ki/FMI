//
//  Scene.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/4/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef __PacManGame__Scene__
#define __PacManGame__Scene__

#include "GameBehaviour.h"
#include "TileMap.h"
#include <vector>
#include <algorithm>

class Scene {
    std::string name;
    //TileMap *map;
    
public:
    Scene(std::string);
    ~Scene();
    
    std::vector<GameObject*> gameObjects;
    std::vector<GameObject*> gameObjectsToRemove;
    TileMap *tileMap;
    
    void Start();
    void Update();
    void Render();
    
    void Add(GameObject*);
    void Add(TileMap*);
    void Remove(Component*);
    void Remove(std::string);
    GameObject* Get(std::string);
    
    void ClearObjects();
};

#endif /* defined(__PacManGame__Scene__) */
