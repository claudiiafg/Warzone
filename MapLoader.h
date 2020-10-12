//
// Created by Claudia on 2020-10-05.
//

#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class MapFile{
public:
    //constructor
    MapFile(string _name, vector<string> fullContent);
    MapFile(const MapFile& _file);

    //destructor
    ~MapFile();

    string name;
    vector<string> content;
    friend ostream& operator<<(ostream &os, const  MapFile& n);
};



class MapLoader{

public:
    MapLoader();

    void loadMaps();                 // starts loading process
    vector<MapFile> getMaps();       // gets files from directory, checks validity and sets each map as MapFile


private:
    vector<MapFile> maps;           // all maps to create / load
    bool isMapType(string path);    // check validity of map
    vector<string> getContent(string path); // get file content
};
