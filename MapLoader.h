//
// Created by Claudia on 2020-10-05.
//

#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <experimental/filesystem>

using namespace std;

class MapFile{
public:
    // constructor
    MapFile(string _name, vector<string> fullContent);
    MapFile(const MapFile& _file);

    // destructor
    ~MapFile();

    string name;
    vector<string> content;

    // operator
    friend ostream& operator<<(ostream &os, const  MapFile& n);
    MapFile& operator = (const MapFile& _file);
};



class MapLoader{

public:
    MapLoader();

    void loadMaps();    // starts loading process
    vector<MapFile*> getMaps();  // gets files from directory, checks validity and sets each map as MapFile


private:
    vector<MapFile*> maps;   // all maps to create / load
    static bool isMapType(const string& path);  // check validity of map
    static vector<string> getContent(const string& path);   // get files content

    // operator
    friend ostream& operator<<(ostream &os, const  MapLoader& l);
    MapLoader& operator = (const MapLoader& loader);
};
