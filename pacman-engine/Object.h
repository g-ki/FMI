//
//  Object.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/5/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef __PacManGame__Object__
#define __PacManGame__Object__

#include <iostream>

class Object {
    static unsigned int _ID;
public:
    std::string ToString();
    unsigned GetID();
    
    Object(std::string name);
    Object();
    //~Object();
    
    
protected:
    std::string _name;
    unsigned int _id;
};

#endif /* defined(__PacManGame__Object__) */
