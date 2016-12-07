//
//  GameObject.cpp
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/4/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject(std::string name) : Component(name){
    //Inherit Object Constructor
    transform = new Transform;
}

GameObject::GameObject(){
    transform = new Transform;
}

GameObject::~GameObject(){
    for(auto& component : _components)
        delete component.second;
}

void GameObject::AddComponent(Behaviour *o){
    _components[o->ToString()] = o;
}

void GameObject::Start(){
    for(auto& component : _components)
        component.second->Start();
}

void GameObject::Update(){
    //update
    for(auto& component : _components)
        component.second->Update();
}

void GameObject::Render(){
    for(auto& component : _components)
        component.second->Render();
}

void GameObject::OnCollision(){
    return;
}

void GameObject::OnCollision(Component *go){
    for(auto& component : _components)
        component.second->OnCollision(go);
}

void GameObject::OnContact(){
    return;
}

void GameObject::OnContact(Component *go){
    for(auto& component : _components)
        component.second->OnContact(go);
}