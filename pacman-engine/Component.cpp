//
//  Component.cpp
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/4/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#include "Component.h"

Component::Component(std::string name) : Object(name){
    
}

Component::Component(){}

void Component::Start() {
    return;
}

void Component::Update() {
    return;
}

void Component::Render() {
    return;
}

void Component::OnCollision(Component* c){
    return;
}

void Component::OnContact(Component* c){
    return;
}