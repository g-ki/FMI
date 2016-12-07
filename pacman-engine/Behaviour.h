//
//  Behaviour.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/14/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef __PacManGame__Behaviour__
#define __PacManGame__Behaviour__

#include "Component.h"

class Behaviour :  public Component {
public:
    
    Behaviour(std::string name);
    virtual ~Behaviour() = default;
};

#endif /* defined(__PacManGame__Behaviour__) */
