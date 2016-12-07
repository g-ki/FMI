//
//  GameBehaviour.cpp
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/14/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#include "GameBehaviour.h"

GameBehaviour::GameBehaviour(GameObject *gO, std::string name) : Behaviour(name) {
    this->gameObject = gO;
    this->transform = this->gameObject->transform;
    this->collider = this->gameObject->collider;
}

GameBehaviour::~GameBehaviour(){
    this->gameObject = NULL;
    this->transform = NULL;
}

void GameBehaviour::OnCollision(Component *go)
{
    return;
}
void GameBehaviour::OnContact(Component *go)
{
    return;
}