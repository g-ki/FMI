//
//  Collider.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/20/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef __PacManGame__Collider__
#define __PacManGame__Collider__

#include "Vector2.h"

enum ColliderType{
    PlayerCollider,
    Food,
    Wall,
    Enemy,
    Door,
    Slow,
    Energizer
};

class Collider {
public:
    Vector2 *center;
    float width, height, radious;
    ColliderType type;
    
    Collider();
    Collider(Vector2*, float, float, ColliderType type); // box collider
    
    virtual bool Collision(Collider other, bool contact = false){
        
        float dX = std::abs(this->center->x - other.center->x);
        float dY = std::abs(this->center->y - other.center->y);
        
        float lW = this->width + other.width;
        float lH = this->height + other.height;
        
        if(contact)
            if(lW >= dX && lH >= dY)
                return true;
        
        if(lW > dX && lH > dY)
            return true;
        
        return false;
    }
    
    bool Contact(Collider  other){
        return Collision(other, true);
    }
    
};

#endif /* defined(__PacManGame__Collider__) */
