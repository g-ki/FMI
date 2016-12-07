//
//  Component.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/4/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef __PacManGame__Component__
#define __PacManGame__Component__

#include "Object.h"
#include "Transform.h"
#include "Collider.h"

class Component : public Object {
    
public:
    Component(std::string);
    Component();
    Transform *transform;
    Collider *collider;
    
    virtual void Start();
    virtual void Update();
    virtual void Render();
    
    virtual void OnCollision(Component*);
    virtual void OnContact(Component*);
};

#endif /* defined(__PacManGame__Component__) */
