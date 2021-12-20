// Script for generating Muon Data

#include <iostream>
#include <cmath>
#include <TFile.h>
#include <TTree.h>

#include "../include/muon.h"
#include "../include/config.h"

using namespace std;

// Random Number Generator
TRandom3 *r = new TRandom3(RAND_SEED);

// Muon Class Constructor
Muon::Muon(int n_run, int n_event) {
    
    init_coords = {              //Initialising muon coords
        float(S_LENGTH*(-0.5 + r->Uniform())),     
        float(S_WIDTH*(-0.5 + r->Uniform())),
        0.,
        float(acos(pow(1. - 0.9375*r->Uniform(), 0.25))),
        float(2.*M_PI*(-0.5 + r->Uniform()))
    };

    final_coords = init_coords;  //Initialising mutable muon coords

    identity = {
        n_run,
        n_event
    };  
}

// Muon Class Destructor
Muon::~Muon(){}

// List of Muons
vector<Muon> muonList;

// Generating the Muons and Filling List
void muongen() {
    for (int i = 0; i < N_EVENTS; i++) {
        muonList.emplace_back(Muon(RUN_NO,i));
    }    
}

// Writing the muon list to a ROOT file
void saveMuon() {

    // Defining Branch Variables
    Coords init_pos, final_pos;
    M_Identifiers identity;
    Int_t nPhotons;

    // Creating ROOT file
    TString filename = "muonList_Run" + to_string(RUN_NO) + ".root";
    TFile f(ROOT_DIR + filename,"recreate");

    // Setting Tree and Branches
    TTree *t = new TTree("t","MuonList");
    t->Branch("identity", &identity, "run/I:event/I");
    t->Branch("init_pos", &init_pos, "x/F:y/F:z/F:theta/F:phi/F");
    t->Branch("final_pos", &final_pos, "x/F:y/F:z/F:theta/F:phi/F");
    t->Branch("nPhotons", &nPhotons, "nPhotons/I");
    

    // Iterating over Muon List and Filling Tree
    for (auto m = muonList.begin(); m != muonList.end(); ++m) {
        identity = m->identity;
        init_pos = m->init_coords;
        final_pos = m->final_coords;
        nPhotons = m->nphotons;
        t->Fill();
    }

    // Write to ROOT file
    t->Write();
    delete t;
}

 
