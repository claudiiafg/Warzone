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
        mainPath = "/home/ian/Warzone/Warzone/testing/";

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
            cout << "->VALID File: " << fileName << endl;
            vector<string> content = getContent(path_name);
            string name = fileName;
            maps.push_back(new MapFile(name, content));
        } else {
            cout << "Invalid: " << fileName << endl;
        }
    }
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
    ifstream myFile (path);

    string lineContent;
    vector<string> vecOfStr;

    // push each line of file into vector of strings (easier to find / parse information)
    while ( getline(myFile, lineContent)) {
        vecOfStr.push_back(lineContent);
    }

    // Close the file
    myFile.close();

    // conquest identifiers
    const string CONT_ID_CQ = "Continents";
    const string TERR_ID_CQ = "Territories";

    // get indexes of each section
    int contI = 0;
    int terrI = 0;
    for (size_t i = 0; i < vecOfStr.size(); ++i){
        if(vecOfStr[i].find(CONT_ID_CQ) < vecOfStr.size() && vecOfStr[i].find(CONT_ID_CQ) > 0) {
            contI = i;
        } else if(vecOfStr[i].find(TERR_ID_CQ) < vecOfStr.size() && vecOfStr[i].find(TERR_ID_CQ) > 0) {
            terrI = i;
        }
    }

    // get all continent strings from map data
    vector<string> tempContinents;
    for (int i = (contI + 1); i < (terrI); ++i){
        tempContinents.push_back(vecOfStr[i]);
    }

    // get all territories strings from map data
    vector<string> tempTerritories;
    for (int i = (terrI + 1); i < (vecOfStr.size()); ++i){
        tempTerritories.push_back(vecOfStr[i]);
    }

    // get each sections of map adapted
    vector<string> finalContinents = adaptContinents(tempContinents);
    vector<string> finalTerritories = adaptTerritories(tempTerritories);
    vector<string> finalBorders = adaptBorders(tempTerritories, finalTerritories);

    // add empty lines between sections
    vector<string> finalVecStr;
    finalContinents.emplace_back("\n");
    finalTerritories.emplace_back("\n");
    finalBorders.emplace_back("\n");

    // merge all sections together
    finalVecStr.insert( finalVecStr.end(), finalContinents.begin(), finalContinents.end());
    finalVecStr.insert( finalVecStr.end(), finalTerritories.begin(), finalTerritories.end() );
    finalVecStr.insert( finalVecStr.end(), finalBorders.begin(), finalBorders.end() );

    return finalVecStr;
}

string ConquestFileReader::findIdOfTerritory(string terrName, const vector<string> finalTerritories) {
    string name = terrName.substr(0, terrName.length() - 1);
    for_each(name.begin(), name.end(), [name](char & c) {
        c = ::tolower(c);
    });

    for(auto & line: finalTerritories) {
        if(line != "[countries]") {
            string tempLine = line;
            for_each(tempLine.begin(), tempLine.end(), [tempLine](char & c) {
                c = ::tolower(c);
            });
            if (tempLine.find(name) != std::string::npos && tempLine.find(name) < 4) {
                string substr;
                stringstream ss(line);
                getline( ss, substr, ' ');
                if(ss.good()) {
                    int inputNum = count(name);
                    int outputNum = count(tempLine);
                    if(outputNum - inputNum <= 3) {
                        return substr;
                    }
                }
            }
        }
    }
    return "not found";
}

int ConquestFileReader::count( string str )
{
    int iSpaces = 0;

    for(unsigned int iLoop = 0; iLoop < ( sizeof( str ) / sizeof( str [0] ) ); iLoop++ )
        if(str [iLoop] == ' ' )
            iSpaces++;

    return iSpaces;
}

int ConquestFileReader::nthOccurrence(const string &str, const string &findMe, int nth) {
    size_t pos = 0;
    int counter = 0;

    while(counter != nth) {
        pos += 1;
        pos = str.find(findMe, pos);
        if (pos == string::npos) return -1;
        counter++;
    }
    return pos;
}

ostream &operator<<(ostream &os, const ConquestFileReader &l) {
    return os << l.map << endl;
}

ConquestFileReader &ConquestFileReader::operator=(const ConquestFileReader &mapToAssign) {
    map = mapToAssign.map;
    return *this;
}

vector<string> ConquestFileReader::adaptTerritories(const vector<string> tempTerritories) {
    //flags
    int continentCounter = 1;
    int territoryCounter = 0;
    bool previousWasEmpty = false;

    //constants
    const string COMMA = ",";
    const string TERR_ID_WZ = "[countries]";

    //vars
    string terrName;
    size_t pos;
    vector<string> finalTerritories;

    finalTerritories.push_back(TERR_ID_WZ);
    for(auto & terr: tempTerritories) {
        // two consecutive new lines means nothing more to search through
        if(previousWasEmpty && terr.size() == 1) {
            break;
        }

        // if current new line next territories are from another continent
        if(terr.size() == 1) {
            continentCounter += 1;
            previousWasEmpty = true;

        // if territory data push to vector in right format
        } else {
            territoryCounter += 1;
            pos = terr.find(COMMA);
            terrName = terr.substr (0, pos);
            finalTerritories.push_back(to_string(territoryCounter) + " " + terrName + " " + to_string(continentCounter));
            previousWasEmpty = false;
        }
    }

    return finalTerritories;
}

vector<string> ConquestFileReader::adaptBorders(const vector<string> tempTerritories, const vector<string> finalTerritories) {
    // flags
    bool previousWasEmpty = false;
    int territoryCounter = 0;
    // constacts
    const string COMMA = ",";
    const string ADJ_ID_WZ = "[borders]";

    // vars
    size_t initIndex;
    vector<string> finalAdjacents;

    finalAdjacents.push_back(ADJ_ID_WZ);
    for(auto & terr: tempTerritories) {
        // two consecutive new lines means nothing more to search through
        if (previousWasEmpty && terr.size() == 1) {
            break;
        }

        if (terr.size() == 1) {
            previousWasEmpty = true;

        } else {
            previousWasEmpty = false;
            territoryCounter += 1;

            // start at 3rd comma
            initIndex = nthOccurrence(terr, COMMA, 4);
            string adjacentList = terr.substr (initIndex);
            stringstream ss(adjacentList);
            vector<string> adjacentVector;

            // start territory adjacent's line with territory node id
            string finalAdjLine = to_string(territoryCounter);
            vector<string> tempFinal;

            // split line by commas
            while(ss.good()) {
                string substr;
                getline( ss, substr, ',');

                // push only unique adjacent territories
                if (find(adjacentVector.begin(), adjacentVector.end(), substr) == adjacentVector.end()) {
                    adjacentVector.push_back(substr);
                }
            }
            // loop through adjacent territories and find their id -> push to territory adjacent's line
            for (int i = 1; i < adjacentVector.size(); i++) {
                string nodeId = findIdOfTerritory(adjacentVector[i], finalTerritories);
                if(nodeId != "not found" && (!(std::find(tempFinal.begin(), tempFinal.end(), nodeId) != tempFinal.end()))) {
                    finalAdjLine += " " + nodeId;
                    tempFinal.push_back(nodeId);
                }
            }

            // push to territory adjacent's line'' vector
            finalAdjacents.push_back(finalAdjLine);

        }
    }
    return finalAdjacents;
}

vector<string> ConquestFileReader::adaptContinents(const vector<string> tempContinents) {
    const string CONT_ID_WZ = "[continents]";
    const string EQUAL = "=";

    vector<string> finalContinents;
    size_t pos;
    string continentName;
    string continentBonus;

    finalContinents.push_back(CONT_ID_WZ);
    for(auto & continent: tempContinents) {
        pos = continent.find(EQUAL);
        continentName = continent.substr (0, pos);
        continentBonus = continent.substr (pos + 1);
        finalContinents.push_back(continentName + " " + continentBonus);
    }

    return finalContinents;
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

