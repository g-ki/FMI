//
//  Object.cpp
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/5/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#include "Object.h"

unsigned Object::_ID = 0;

Object::Object(){
    //do nothing
    _id = ++_ID;
}

Object::Object(std::string name){
    _name = name;
    _id = ++_ID;
}

std::string Object::ToString(){
    return _name;
}

unsigned Object::GetID(){
    return _id;
}