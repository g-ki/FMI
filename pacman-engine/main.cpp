//
//  main.cpp
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/4/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#include <iostream>
#include "Global.h"
#include "GameEngine.h"

#include "TileMap.h"
#include "Player.h"
#include "RedEnemy.h"
#include "PinkEnemy.h"
#include "BlueEnemy.h"
#include "OrangeEnemy.h"

using namespace std;



__Global Global;
GameEngine Game("PacMan", WIN_SIZE_X, WIN_SIZE_Y, TILE_SIZE*2);

int main(int argc, char **argv) {

    //GameEngine game("PacMan", WIN_SIZE_X, WIN_SIZE_Y, TILE_SIZE*2);
    
    
    Scene *lounchScene = new Scene("First");
    
    lounchScene->Add(new TileMap("map.data.txt", TILE_SIZE));
    
    lounchScene->Add(new Player("MainPlayer"));
    
    lounchScene->Add(new RedEnemy());
    lounchScene->Add(new PinkEnemy());
    lounchScene->Add(new BlueEnemy());
    lounchScene->Add(new OrangeEnemy());
    
    
    
    //lounchScene->Add
    
    Game.SetScene(lounchScene);
    
    if(!Game.Start())
    {
        cout<<"Error occurred during initialization of GameEngine:\n";
        return -1;
    }
    
    Game.Loop();
    
    Game.End();
    
    return 0;
}