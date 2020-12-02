//
// Created by Claudia on 2020-10-05.
//


#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
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
    string mainPath;

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

class ConquestFileReader{
public:
    MapFile* map{};

    //constructor
    ConquestFileReader();
    ConquestFileReader(const ConquestFileReader& _file);

    // destructor
    ~ConquestFileReader();
    explicit ConquestFileReader(MapFile* otherMap);
    vector<string> getContent(const string& path);   // get files content
    static vector<string> adaptContinents(vector<string> tempContinents);
    static vector<string> adaptTerritories(vector<string> tempTerritories);
    vector<string> adaptBorders(vector<string> tempTerritories, vector<string> finalTerritories);
    static int nthOccurrence(const string& str, const string& findMe, int nth);
    static string findIdOfTerritory(string terrName, vector<string> finalTerritories);

    // operator
    friend ostream& operator<<(ostream &os, const  ConquestFileReader& l);
    ConquestFileReader& operator = (const ConquestFileReader& mapToAssign);

};

class ConquestFileReaderAdapter : public MapLoader{
public:
    ConquestFileReader* conquestFileReader;

    //constructor
    ConquestFileReaderAdapter();
    explicit ConquestFileReaderAdapter(ConquestFileReader* toAdapt);
    ConquestFileReaderAdapter(const ConquestFileReaderAdapter& _file);

    // destructor
    ~ConquestFileReaderAdapter();

    vector<string> getContent(const string& path);   // call adaptee to get files content

    // operator
    friend ostream& operator<<(ostream &os, const  ConquestFileReaderAdapter& l);
    ConquestFileReaderAdapter& operator = (const ConquestFileReaderAdapter& adapter);
};
