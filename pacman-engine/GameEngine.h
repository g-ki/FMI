//
//  GameEngine.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/16/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef __PacManGame__GameEngine__
#define __PacManGame__GameEngine__


#include "Global.h"
#include "Scene.h"
#include "CollisionSystem.h"

class GameEngine {
    std::string name;
    bool isRunning, isStarted, render;
    int displayWidth, displayHeight;
    double FPS;
    
    Scene *scene;
    CollisionSystem collisionSys;
    
    
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_TIMER *timer;
    
    bool InitDisplay();
    bool InitEvents();
    
public:
    GameEngine(std::string, int, int, int);
    
    void SetScene(Scene*);
    Scene* GetScene();
    
    bool Start();
    bool Loop();
    bool End();
    
    void Stop();
};

extern GameEngine Game;

#endif /* defined(__PacManGame__GameEngine__) */
