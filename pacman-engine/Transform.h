//
//  Transform.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/13/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef __PacManGame__Transform__
#define __PacManGame__Transform__


#include "Vector2.h"

class Transform {
public:
    Transform();
    Transform(float, float);
    
    Vector2 position;
    Vector2 scale;
    Vector2 rotation;
};

#endif /* defined(__PacManGame__Transform__) */
