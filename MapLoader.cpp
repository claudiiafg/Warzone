//
// Created by Claudia on 2020-10-05.
//

#include "MapLoader.h"

using namespace std;
namespace fs = std::filesystem;

MapLoader::MapLoader()= default;

//load all files in testing directory
void MapLoader::loadMaps() {
    std::string path = "../testing";
    for (const auto& entry : fs::directory_iterator(path)) {
        const auto filenameStr = entry.path().filename().string();

        cout << "Files Found:" << endl;

        // check for all files inside each folder of testing directory
        if (entry.is_directory()) {
//            std::cout << "dir:  " << filenameStr << '\n';
            for (const auto & entry : fs::directory_iterator(entry.path())) {
//                cout << entry.path() << endl;

                // check for file with map data and create MapFiles
                if(isMapType(entry.path())) {
                    cout << "->VALID Map: " << entry.path().filename().string() << endl;
                    vector<string> content = getContent(entry.path());
                    string name = entry.path().filename().string();
                    maps.push_back(*new MapFile(name, content));
                } else {
                    cout << "->Invalid: " << entry.path().filename().string() << endl;
                }
            }
        }

        // check for all files directly inside testing directory
        else if (entry.is_regular_file()) {
//            cout << "file: " << filenameStr << '\n';
        }
        cout << endl;
    }
}

bool MapLoader::isMapType(const string& path) {
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

    // close the file
    PathFile.close();
    return true;
}

// extract map data
vector<string> MapLoader::getContent(const string& path) {
    ifstream PathFile(path);
    string lineContent;
    vector<string> vecOfStr;

    // push each line of file into vector of strings (easier to find / parse information)
    while (getline (PathFile, lineContent)) {
        vecOfStr.push_back(lineContent);
    }

    // Close the file
    PathFile.close();

    return vecOfStr;
}

// prints and returns maps available
vector<MapFile> MapLoader::getMaps() {
    for(vector<int>::size_type i = 0; i != maps.size(); i++) {
        cout << maps[i] << endl;
    }
    return maps;

}

// MapFile constructor -> creates valid map files to be turned into Graphs
MapFile::MapFile(string _name, vector<string> fullContent) {
    name = _name;
    content = fullContent;
}

// copy constructor
MapFile::MapFile(const MapFile& _file) {
    name =_file.name;
    content = _file.content;
}

// streams insertion operator
ostream& operator<<(ostream &os, const MapFile& n) {
    return os << "Maps available for creation: " << n.name << endl;
}

// assignment operator
MapFile& MapFile::operator = (const MapFile& _file) {
    return *this;
}

// destructor
MapFile::~MapFile() = default;


