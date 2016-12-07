//
//  GameObject.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/4/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef __PacManGame__GameObject__
#define __PacManGame__GameObject__

#include "Object.h"
#include "Component.h"
#include "Behaviour.h"
#include <map>

class GameObject : public Component{
public:
    GameObject(std::string name);
    GameObject();
    ~GameObject();
    
    bool active = true;
    
    void AddComponent(Behaviour*);
    
    template<typename T>
    void AddComponent(){
        AddComponent(new T(this));
    }
    
    Behaviour* GetComponent(std::string name){
        return _components[name];
    }
    
    virtual void Start();
    virtual void Update();
    virtual void Render();
    virtual void OnCollision(Component*);
    virtual void OnCollision();
    virtual void OnContact(Component*);
    virtual void OnContact();
    
private:
    std::map<std::string, Behaviour*> _components;
};

#endif /* defined(__PacManGame__GameObject__) */
