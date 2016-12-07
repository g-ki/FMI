//
//  GameBehaviour.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/14/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef __PacManGame__GameBehaviour__
#define __PacManGame__GameBehaviour__

#include "Behaviour.h"
#include "GameObject.h"

class GameBehaviour : public Behaviour {
public:
    GameBehaviour(GameObject*, std::string);
    ~GameBehaviour();
    GameObject *gameObject;
    
    virtual void OnCollision(Component*);
    virtual void OnContact(Component*);
};

#endif /* defined(__PacManGame__GameBehaviour__) */
