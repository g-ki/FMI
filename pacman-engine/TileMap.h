//
//  TileMap.h
//  PacManGame
//
//  Created by Georgi Kiryakov on 12/22/14.
//  Copyright (c) 2014 Georgi Kiryakov. All rights reserved.
//

#ifndef PacManGame_TileMap_h
#define PacManGame_TileMap_h


#include "Global.h"
#include <vector>
#include <fstream>
#include <string>


class Tile : public GameObject{
    int size;
    ColliderType type;
public:
    Tile(int size, int x, int y, ColliderType type = ColliderType::Wall){
        this->size = size;
        this->type = type;
        this->transform->position.Set(y*size + size/2, x*size + size/2);
        
        type = (type == ColliderType::Door)? ColliderType::Wall : type;
        this->collider = new Collider(&transform->position, size, size, type);
        
    }
    
    void Render(){
        if(type == ColliderType::Wall)
            al_draw_filled_rectangle(transform->position.x - size/2 + 2,
                                     transform->position.y - size/2 + 2,
                                     transform->position.x + size/2, transform->position.y + size/2,
                                     al_map_rgb(0, 100, 255));
        else if(type == ColliderType::Food)
            al_draw_filled_circle(transform->position.x, transform->position.y, 2, al_map_rgb(0, 255, 0));
        else if(type == ColliderType::Energizer)
            al_draw_filled_circle(transform->position.x, transform->position.y, 4, al_map_rgb(0, 255, 0));
        
        
    }
    
};

class TileMap : public GameObject {
    int sizeX, sizeY, tileSize;
    std::vector< std::vector<char> > map;
    std::string filePath;
    ALLEGRO_KEYBOARD_STATE state;
public:
    TileMap(std::string mapFilePath, int tileSize) : GameObject("TileMap"){
        this->filePath = mapFilePath;
        this->tileSize = tileSize;
        LoadMapFile(mapFilePath);
    }
    
    void LoadMapFile(std::string mapFilePath){
        std::string line;
        std::ifstream mapFile (mapFilePath);
        if (mapFile.is_open())
        {
            map.clear();
            while ( getline (mapFile,line) ){
                std::vector<char> tmp;
                for (int j=0; j<line.length(); j++) {
                    tmp.push_back(line[j]);
                }
                for (int j=line.length()-1; j>=0; j--) {
                    tmp.push_back(line[j]);
                }
                map.push_back(tmp);
            }
            mapFile.close();
            
            
            
        }
    }
    
    std::vector<GameObject*> GetTiles(){
        std::vector<GameObject*> tmp;
        
        for (int i=0; i<map.size(); i++) {
            for (int j=0; j<map[i].size(); j++) {
                if(map[i][j]=='w')
                    tmp.push_back(new Tile(tileSize,i,j, ColliderType::Wall));
                else if(map[i][j]=='f')
                    tmp.push_back(new Tile(tileSize,i,j,ColliderType::Food));
                else if(map[i][j]=='h')
                    tmp.push_back(new Tile(tileSize,i,j,ColliderType::Door));
                else if(map[i][j]=='s')
                    tmp.push_back(new Tile(tileSize,i,j,ColliderType::Slow));
                else if(map[i][j]=='e')
                    tmp.push_back(new Tile(tileSize,i,j,ColliderType::Energizer));
            }
        }
        return tmp;
    }
    
    int GetSize(int i=-1){
        
        if(i<0)
            return map.size();
        
        return map[i].size();
    }
    
    void Render(){
        
        for (int i=0; i<map.size(); i++) {
            for (int j=0; j<map[i].size(); j++) {

                /*if(map[i][j]=='w'){
                    
                        al_draw_filled_rectangle(j*tileSize + 2, i*tileSize + 2,
                                                 j*tileSize +tileSize, i*tileSize+tileSize,
                                                 al_map_rgb(0, 100, 255));
                }*/
                
               /*if(map[i][j]=='f')
                   al_draw_filled_circle(j*tileSize + tileSize/2, i*tileSize + tileSize/2, 2, al_map_rgb(0, 255, 0));*/
            }
        }
        
        
        GameObject::Render();
    }
};


#endif
