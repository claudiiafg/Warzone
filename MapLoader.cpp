//
// Created by Claudia on 2020-10-05.
//

#include "MapLoader.h"
#include <string.h>
#include <errno.h>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
///   MAPLOADER					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

MapLoader::MapLoader()= default;

//load all files in testing directory
void MapLoader::loadMaps() {
    string name = "";
    mainPath = "";

    cout << "In order to search for the Maps in your computer, please enter your first name" << endl;
    cin >> name;
    if (name == "clau") {
        // can use relative paths on mac
        mainPath = "../testing/";

    } else if (name == "james") {
        mainPath = "C://Users/James/source/repos/TestWarzone1/testing/";

    } else if ( name == "gini") {
        mainPath = "C:/Users/gini/source/repos/claudiiafg/Warzone/testing/";

    } else if (name == "ian") {
        mainPath = "/home/ian/CLion-workspace/Warzone/testing/";

    } else if (name == "ta") {
        mainPath = "../testing/";

    } else {
        cout << "no option for you, please go look into MapLoader::loadMaps() and get yourself an personalized option";
    }

    vector<string> fileNames = {
            "brasil.cards",
            "brasil.map",
            "brasil_map.gif",
            "brasil_pic.gif",
            "canada.cards",
            "canada.map",
            "canada.gif",
            "canada.gif",
            "europe.cards",
            "europe.map",
            "europe.gif",
            "europe.gif",
            "Andorra.map",
            "Andorra.bmp",
            "Atlantis.map",
            "Atlantis.bmp"
    };

    for(auto &fileName : fileNames) {
        string parendFolder = fileName.substr(0,fileName.find_last_of('.'));
        string path_name = mainPath + parendFolder + "/" + fileName;
        // check for file with map data and create MapFiles
        if(isMapType(path_name)) {
            cout << "->VALID Map: " << fileName << endl;
            vector<string> content = getContent(path_name);
            string name = fileName;
            maps.push_back(new MapFile(name, content));
        } else {
            cout << "->Invalid: " << fileName << endl;
        }
    }
    cout << endl << endl;
}


// validate map type
bool MapLoader::isMapType(const string& path) {
    //get file extension
    string ext = path.substr(path.find_last_of('.'));

    // only look for files with .map extension
    if(ext != ".map") {
        return false;
    }

	ifstream myFile (path);
    // check for errors opening the file
    if (!myFile.is_open()) {
        cout<<"It failed\n"<<strerror(errno)<<endl;
        return false;
    }

    // close the file
	myFile.close();
    return true;
}

// extract map data
vector<string> MapLoader::getContent(const string& path) {
	ifstream myFile (path);

    string lineContent;
    vector<string> vecOfStr;

    // push each line of file into vector of strings (easier to find / parse information)
    while ( getline(myFile, lineContent)) {
        vecOfStr.push_back(lineContent);
    }

    // Close the file
	myFile.close();

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

/////////////////////////////////////////////////////////////////////////////
///   MAPFILE					   	                                      ///
/////////////////////////////////////////////////////////////////////////////

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


/////////////////////////////////////////////////////////////////////////////
///   CONQUEST-FILE-READER					   	                          ///
/////////////////////////////////////////////////////////////////////////////

ConquestFileReader::ConquestFileReader() = default;

ConquestFileReader::ConquestFileReader(const ConquestFileReader &_file) {
    map = _file.map;
}

ConquestFileReader::~ConquestFileReader() {
    delete map;
    map = nullptr;
}

ConquestFileReader::ConquestFileReader(MapFile *otherMap) {
    map = otherMap;
}

vector<string> ConquestFileReader::getContent(const string &path) {
    cout << "WAS CALLED" << endl;
    cout << "JUST ADAPTING THE CONTENT LEFT" << endl;
//    ifstream myFile (path);
//
//    string lineContent;
    vector<string> vecOfStr;
//
//    // push each line of file into vector of strings (easier to find / parse information)
//    while ( getline(myFile, lineContent)) {
//        vecOfStr.push_back(lineContent);
//    }
//
//    // Close the file
//    myFile.close();

    return vecOfStr;
}

ostream &operator<<(ostream &os, const ConquestFileReader &l) {
    return os << l.map << endl;
}

ConquestFileReader &ConquestFileReader::operator=(const ConquestFileReader &mapToAssign) {
    map = mapToAssign.map;
    return *this;
}


/////////////////////////////////////////////////////////////////////////////
///   CONQUEST-FILE-READER-ADAPTER					   	                  ///
/////////////////////////////////////////////////////////////////////////////


ConquestFileReaderAdapter::ConquestFileReaderAdapter() = default;

ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader *toAdapt) {
    conquestFileReader = toAdapt;
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(const ConquestFileReaderAdapter &_file) {
    conquestFileReader = _file.conquestFileReader;
}

ConquestFileReaderAdapter::~ConquestFileReaderAdapter() {
    delete conquestFileReader;
    conquestFileReader = nullptr;
}

vector<string> ConquestFileReaderAdapter::getContent(const string& path) {
    string fileName = conquestFileReader->map->name;
    string parendFolder = fileName.substr(0,fileName.find_last_of('.'));
    string path_name = path + parendFolder + "/" + fileName;

    return conquestFileReader->getContent(path_name);
}

ostream &operator<<(ostream &os, const ConquestFileReaderAdapter &l) {
    return os << l.conquestFileReader << endl;
}

ConquestFileReaderAdapter &ConquestFileReaderAdapter::operator=(const ConquestFileReaderAdapter &adapter) {
    conquestFileReader = adapter.conquestFileReader;
    return *this;
}

