//
// Created by Claudia on 2020-10-05.
//

#include "MapLoader.h"

using namespace std;

MapLoader::MapLoader()= default;

//load all files in testing directory
void MapLoader::loadMaps() {
    char *path = "../testing";
    vector<string> fileNames = listFilesRecursively(path);
    string folderName = "";

    for(auto &file : fileNames) {
        bool isFolderName = (file.find_last_of('.') > 100);
        if(isFolderName) {
            folderName = file + "/";
        }

        string path_name = "../testing/" + folderName + file;
        // check for file with map data and create MapFiles
        if(isMapType(path_name)) {
            cout << "->VALID Map: " << file << endl;
            vector<string> content = getContent(path_name);
            string name = file;
            maps.push_back(new MapFile(name, content));
        } else {
            cout << "->Invalid: " << file << endl;
        }
    }
    cout << endl << endl;
}

vector<string> MapLoader::listFilesRecursively(const char *basePath) {
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    vector<string> fileNames = {};

    // Unable to open directory stream
    if (!dir)
        return fileNames;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            vector<string> tempFileNames = {};

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            fileNames.push_back(dp->d_name);

            tempFileNames = listFilesRecursively(path);

            for(auto &f: tempFileNames) {
                fileNames.push_back(f);
            }
        }
    }

    closedir(dir);
    return fileNames;
}


// validate map type
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
vector<MapFile*> MapLoader::getMaps() {
    return maps;
}

// streams insertion operator
ostream& operator<<(ostream &os, const MapLoader& n) {
    return os << "Files loaded: " << n.maps.size() << endl;
}

// assignment operator
MapLoader& MapLoader::operator = (const MapLoader& loader){
    maps = loader.maps;
    return *this;
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
    return os << n.name << endl;
}

// assignment operator
MapFile& MapFile::operator = (const MapFile& _file) {
    name = _file.name;
    content = _file.content;
    return *this;
}

// destructor
MapFile::~MapFile() = default;


