//
// Created by Claudia on 2020-10-05.
//

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <numeric>

#include "MapLoader.h"
#include "Map.cpp"

using namespace std;
namespace fs = std::filesystem;

MapLoader::MapLoader(){}

vector<MapFile> maps;

//load all files in testing directory
void MapLoader::loadMaps() {
    std::string path = "../testing";
    for (const auto& entry : fs::directory_iterator(path)) {
        const auto filenameStr = entry.path().filename().string();

        // check for all files inside each folder of testing directory
        if (entry.is_directory()) {
//            std::cout << "dir:  " << filenameStr << '\n';
            for (const auto & entry : fs::directory_iterator(entry.path())) {
//                cout << entry.path() << endl;

                // check for file with map data and create MapFiles
                if(isMapType(entry.path())) {
                    vector<string> content = getContent(entry.path());
                    string name = entry.path().filename().string();
                    MapFile newFile(name, content);
                    maps.push_back(newFile);
                }
            }
        }

        // check for all files inside testing directory
        else if (entry.is_regular_file()) {
//            cout << "file: " << filenameStr << '\n';
        }
    }

//    getMaps();
    createMaps();
}

bool MapLoader::isMapType(string path) {
    //get file extension
    string ext = path.substr(path.find_last_of('.'));

    // only look for files with .map extension
    if(ext != ".map") {
        return false;
    }


    ifstream PathFile(path);
    // check for errors opening the file
    if (PathFile.fail()) {
        cout<<"It failed\n"<<strerror(errno)<<endl;
        return false;
    }
    // Close the file
    PathFile.close();
    return true;
}

// extract map data
vector<string> MapLoader::getContent(string path) {
    ifstream PathFile(path);
    string lineContent;
    vector<string> vecOfStr;

    while (getline (PathFile, lineContent)) {
        vecOfStr.push_back(lineContent);
    }

    // Close the file
    PathFile.close();

    return vecOfStr;
}

// print maps ready to load
void MapLoader::getMaps() {
    for(vector<int>::size_type i = 0; i != maps.size(); i++) {
        cout << maps[i] << endl;
    }

}

// call Map class and create
void MapLoader::createMaps() {
    for (int i = 0; i < maps.size(); i++) {
        Map* map = new Map(maps[i].name, maps[i].content);
        cout << *map << endl;
    }

}

// create temporary map files, to create
MapFile::MapFile(string _name, vector<string> fullContent) {
    name = _name;
    content = fullContent;
}

ostream& operator<<(ostream &os, const MapFile& n) {
    return os << "Maps available: " << n.name << endl;
}


