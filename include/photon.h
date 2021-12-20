// Script for generating Photon Data

#ifndef PHOTON_H
#define PHOTON_H

#include <iostream>
#include <vector>
#include "muon.h"

using namespace std;

struct P_Identifiers {                  
    int run, event, pid;                         
};

class Photon {

public:
    Photon(                     // Constructor
        Coords muon_coords,
        M_Identifiers muon_id,
        int pid
    );
    ~Photon();                  // Destructor        
    Coords coords;              // Photon Coordinates
    P_Identifiers identity;     // Photon Identity
};

// Photon List 
extern vector<Photon> photonList;

// Muon propagator and photon generator
extern void photongen();

// Photon propagator
extern bool photonProp(Photon P);

// Save Photon list to root file
extern void savePhoton();

// Photon Histogram
extern void photonHist();
#endif
