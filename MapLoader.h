//
// Created by Claudia on 2020-10-05.
//

#ifndef WARZONE_MAPLOADER_H
#define WARZONE_MAPLOADER_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class MapFile{
public:
    string name;
    vector<string> content;
    MapFile(string _name, vector<string> fullContent);
    friend ostream& operator<<(ostream &os, const  MapFile& n);
};



class MapLoader{

public:
    MapLoader();
    void loadMaps();                 // starts loading process

private:
    vector<MapFile> maps;           // all maps to create / load
    void getMaps();                 // gets files from directory, checks validity and sets each map as MapFile
    bool isMapType(string path);    // check validity of map
    vector<string> getContent(string path); // get file content
    void createMaps();              // create map (call Map class)
};




#endif //WARZONE_MAPLOADER_H
