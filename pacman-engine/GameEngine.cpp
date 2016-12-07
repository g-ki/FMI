//
//  GameEngine.cpp
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/16/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#include "GameEngine.h"

GameEngine::GameEngine(std::string name, int width = 800, int height = 600, int tileSize=40) : collisionSys(tileSize)
{
    this->name = name;
    this->FPS = 60;
    
    // display
    this->displayWidth = width;
    this->displayHeight = height;
    this->display = NULL;
    
    this->eventQueue = NULL;
    this->timer = NULL;
    
    this->isRunning = false;
    this->isStarted = false;
    this->render = false;
}

void GameEngine::SetScene(Scene *scene){
    this->scene = scene;
}

Scene* GameEngine::GetScene(){
    return scene;
}

void GameEngine::Stop(){
    isRunning = false;
}

bool GameEngine::InitDisplay(){
    
    this->display = al_create_display(this->displayWidth, this->displayHeight);
    if(!this->display){
        std::cout<<"failed to create display!\n";
        return 0;
    }
    
    return 1;
}

bool GameEngine::InitEvents(){
    
    this->eventQueue = al_create_event_queue();
    
    //timer
    this->timer = al_create_timer( 1 / this->FPS);
    al_register_event_source(this->eventQueue, al_get_timer_event_source(this->timer));
    
    //keyboard
    al_install_keyboard();
    al_register_event_source(this->eventQueue, al_get_keyboard_event_source());
    
    //mouse
    al_install_mouse();
    al_register_event_source(this->eventQueue, al_get_mouse_event_source());
    
    return 1;
}

bool GameEngine::Start(){
    //init allegro lib
    
    if(!al_init()){
        std::cout<<"failed to initialize allegro!\n";
        return 0;
    }
    
    if(!this->InitDisplay())
        return 0;
    
    this->InitEvents();
    
    al_init_primitives_addon();
    
    al_init_font_addon(); // initialize the font addon
    Global.font = al_load_font("LA KAME A LEON.ttf",72,0 );
    
    this->isStarted = true;
    return 1;
}

bool GameEngine::Loop() {
    
    if(!this->isStarted)
        return 1;
    
    this->isRunning = true;
    this->scene->Start();
    
    al_start_timer(this->timer);
    
    while (this->isRunning) {
        // allegro
        ALLEGRO_EVENT events;
        al_wait_for_event(this->eventQueue, &events);
        
        if(events.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if(events.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                this->isRunning = false;
            }
        }
        
        if(events.type == ALLEGRO_EVENT_TIMER){
            
            al_get_keyboard_state(&Global.keyboardState);
            al_get_mouse_state(&Global.mouseState);
            
            this->scene->Update();
            
            for(auto gameObj : this->scene->gameObjects)
                collisionSys.AddObject(gameObj);
            
            collisionSys.CollisionChek();
            
            this->render = true;
        }
        
        if(this->render){
            this->scene->Render();
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            this->render = false;
            
            this->scene->ClearObjects();
        }
        
        
    }
    
    this->isRunning = false;
    return 1;
}

bool GameEngine::End() {
    this->isRunning = false;
    delete this->scene;
    al_destroy_display(this->display);
    
    return 1;
}