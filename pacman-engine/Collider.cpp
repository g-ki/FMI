//
//  Collider.cpp
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/20/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#include "Collider.h"

Collider::Collider(Vector2 *c, float w, float h, ColliderType type){
    this->center = c;
    this->width = w/2;
    this->height = h/2;
    this->radious = sqrtf(w*w/4 + h*h/4);
    this->type = type;
}