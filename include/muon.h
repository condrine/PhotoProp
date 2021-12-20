// Header file for Muon Generation script

#ifndef MUON_H
#define MUON_H

#include <iostream>
#include <vector>
#include <TRandom3.h>

using namespace std;

// Random Number Generator
extern TRandom3 *r;

struct Coords {                    
    float x, y, z, theta, phi;    
};
                   
struct M_Identifiers {                  
    int run, event;                         
};

// Muon Object
class Muon {

public:
    Muon(int n_run, int n_event);   // Constructor
    ~Muon();                        // Destructor
    Coords init_coords;             // Initial Coordinates
    Coords final_coords;            // Final Coordinates
    M_Identifiers identity;           // Muon Identity
    int nphotons = 0;               // No. of photons for this event
};

// Muon List 
extern vector<Muon> muonList;

// Muon Generator
extern void muongen();

// Muon Writer
extern void saveMuon();

#endif
