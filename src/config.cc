// Configuration file for the simulation

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include "TSystem.h"
#include "../include/config.h"

using namespace std;

map<string, int> iRunVars;
map<string, float> fRunVars;
map<string, string> sRunVars;
map<string, bool> bRunVars;

int N_EVENTS, MAX_REFL, RUN_NO, RAND_SEED;
float S_LENGTH, S_WIDTH, S_HEIGHT, D_POS_X, D_POS_Y, PATH_STEP;
bool SAVE_MUON, SAVE_PHOTON;
string ROOT_DIR;

void setRunVars() {
    std::ifstream cFile ("config.txt");
    if (cFile.is_open())
    {
        std::string line;
        while(getline(cFile, line)){
            if(line[0] == '#' || line.empty())
                continue;

            auto typePos = line.find(" ");
            auto type = line.substr(0, typePos);

            line = line.substr(typePos + 1);
            auto f = [](unsigned char const c) { return std::isspace(c); };
            line.erase(remove_if(line.begin(), line.end(), f), line.end());
            
            auto valuePos = line.find("=");
            auto name = line.substr(0, valuePos);
            auto value = line.substr(valuePos + 1);
            
            if (type == "int") iRunVars.insert({name, stoi(value)});
            if (type == "float") fRunVars.insert({name, stof(value)});
            if (type == "string") sRunVars.insert({name, value});
            if (type == "bool") bRunVars.insert({name, value=="true" ? true : false});
            
        }
    }
    else {
        std::cerr << "Couldn't open config file for reading.\n";
    }

    RUN_NO = iRunVars["RUN_NO"];
    RAND_SEED = iRunVars["RAND_SEED"];
    N_EVENTS = iRunVars["N_EVENTS"];

    S_LENGTH = fRunVars["S_LENGTH"];
    S_WIDTH = fRunVars["S_WIDTH"];
    S_HEIGHT = fRunVars["S_HEIGHT"];
    D_POS_X = fRunVars["D_POS_X"];
    D_POS_Y = fRunVars["D_POS_Y"];

    PATH_STEP = fRunVars["PATH_STEP"];
    MAX_REFL = iRunVars["MAX_REFL"];

    SAVE_MUON = bRunVars["SAVE_MUON"];
    SAVE_PHOTON = bRunVars["SAVE_PHOTON"];
    ROOT_DIR = sRunVars["ROOT_DIR"];
}

