// Script for generation of photons

#include <iostream>
#include <random>
#include <cmath>
#include <TFile.h>
#include <TTree.h>
#include <TH1I.h>
#include <TCanvas.h>

#include "../include/photon.h"
#include "../include/muon.h"
#include "../include/config.h"

using namespace std;

// Photon Class Constructor
Photon::Photon(
    Coords muon_coords,
    M_Identifiers muon_id,
    int pid
) {
    coords = {
        muon_coords.x,
        muon_coords.y,
        muon_coords.z,
        float(acos(1. - 2.*r->Uniform())),
        float(2*M_PI*(-0.5 + r->Uniform()))
    };

    identity = {
        muon_id.run,
        muon_id.event,
        pid
    };
}

// Photon Class Destructor
Photon::~Photon(){};

// Caluculate the number of photons generated in a path step
Int_t nPhotons() {

    // Scintillator properties and constants
    Double_t betaSqr = 0.99934;
    Double_t A = 12.;
    Double_t Z = 6.;
    Double_t S = 1030.*PATH_STEP;
    Double_t xi = (0.1536/betaSqr)*(Z/A)*S;
    Double_t gammaE = 0.577;

    // Random sample from Landau Distribution
    Double_t lambda = r->Landau()/xi;
    
    // Energy deposited while traversing the path length
    Double_t deltaE = xi*(lambda + log((5.597e9*betaSqr*xi)/((1-betaSqr)*Z*Z)) + 1 - betaSqr - gammaE);

    // Photon number
    return (Int_t) (deltaE*10.);    
}

// Photon list
vector<Photon> photonList;

// Function for muon propagation and photon generation
void muonProp(Muon& m) {

    // Iteration temp vars
    int nP =0;
    Coords temp = m.init_coords;

    // Muon propagation
    bool stopLoop = false;
    while (!stopLoop) {
        
        // Photon generation
        int tempP = nPhotons();
        if (tempP) {
            for (int i = 0; i < tempP; i++){
                // Create photon instance
                Photon P (temp, m.identity, nP);
                if (photonProp(P)) nP++;
            }
        }

        // Check if muon has left the detector
        if ( temp.x > S_LENGTH/2. - PATH_STEP*sin(temp.theta)*cos(temp.phi) || temp.x < -S_LENGTH/2. - PATH_STEP*sin(temp.theta)*cos(temp.phi) ) {
            stopLoop = true;
            m.final_coords = temp;
        } else if ( temp.y > S_WIDTH/2. - PATH_STEP*sin(temp.theta)*sin(temp.phi) || temp.y < -S_WIDTH/2. - PATH_STEP*sin(temp.theta)*sin(temp.phi)) {
            stopLoop = true;
            m.final_coords = temp;
        } else if (temp.z > S_HEIGHT - PATH_STEP*cos(temp.theta)) {
            stopLoop = true;
            m.final_coords = temp;
        } else {
            // Update Muon path
            temp.x += PATH_STEP*sin(temp.theta)*cos(temp.phi);
            temp.y += PATH_STEP*sin(temp.theta)*sin(temp.phi);
            temp.z += PATH_STEP*cos(temp.theta);
        }
    }

    // Aftermath
    m.nphotons = nP;
    if(m.identity.event%1000==0){
        cout << "Processed event no. " << m.identity.event << endl;
    }
}

// Muon propagation and photon generation
void photongen() {
    // Iterating over Muon list
     for (auto m = muonList.begin(); m != muonList.end(); ++m) muonProp(*m);
}

// Writing the photon list to a ROOT file
void savePhoton() {

    // Defining Branch Variables
    P_Identifiers identity;
    Coords pos;

    // Creating ROOT file
    TString filename = "photonList_Run" + to_string(RUN_NO) + ".root";
    TFile f(ROOT_DIR + filename,"recreate");

    // Setting Tree and Branches
    TTree *t = new TTree("t","PhotonList");
    t->Branch("identity", &identity, "run/I:event/I:pid/I");
    t->Branch("pos", &pos, "x/F:y/F:z/F:theta/F:phi/F");

    // Iterating over Muon List and Filling Tree
    for (auto p = photonList.begin(); p != photonList.end(); ++p) {
        identity = p->identity;
        pos = p->coords;
        t->Fill();
    }

    // Write to ROOT file
    t->Write();
    delete t;
}