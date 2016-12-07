//
//  Scene.cpp
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/4/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#include "Scene.h"

Scene::Scene(std::string name){
    this->name = name;
}

Scene::~Scene(){
    for (auto &gameObject : gameObjects)
        delete gameObject;
    
    while (!this->gameObjects.empty())
        this->gameObjects.pop_back();

}

void Scene::Start(){
    for (auto gameObject : gameObjects)
        gameObject->Start();
}

void Scene::Update(){
    //update
    for (auto &gameObject : gameObjects){
        gameObject->Update();
    }
    //collision correction
    
}

void Scene::Render(){
    tileMap->Render();
    for (auto &gameObject : gameObjects)
        gameObject->Render();
    
}

void Scene::Add(GameObject *gameObject){
    this->gameObjects.push_back(gameObject);
}
void Scene::Add(TileMap *map){
    std::vector<GameObject*> mapTiles = map->GetTiles();
    
    for (int i=0; i<mapTiles.size(); i++) {
        gameObjects.push_back(mapTiles[i]);

    }
    mapTiles.clear();
    this->tileMap = map;
}

void Scene::Remove(Component *go){
    
    for (int i=0; i<gameObjects.size(); i++) {
        if(go->GetID() == gameObjects[i]->GetID()){
            gameObjectsToRemove.push_back(gameObjects[i]);
            gameObjects.erase(gameObjects.begin() + i);
            break;
        }
        
    }
}

void Scene::Remove(std::string name){
    
    for (int i=0; i<gameObjects.size(); i++) {
        if(name == gameObjects[i]->ToString()){
            gameObjectsToRemove.push_back(gameObjects[i]);
            gameObjects.erase(gameObjects.begin() + i);
            break;
        }
        
    }
}

void Scene::ClearObjects(){
    for (auto &gameObject : gameObjectsToRemove)
        delete gameObject;
    
    gameObjectsToRemove.clear();
}


GameObject* Scene::Get(std::string name){
    for (int i=0; i<gameObjects.size(); i++)
        if(name == gameObjects[i]->ToString()){
            return gameObjects[i];
        }
    
    return nullptr;
}



