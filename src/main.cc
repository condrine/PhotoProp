#include <iostream>
#include <TSystem.h>

#include "../include/muon.h"
#include "../include/config.h"
#include "../include/photon.h"

using namespace std;

int main(Int_t argc, Char_t** argv) {
    
    // Welcome message
    cout << "Welcome to the simulation!\n";
    cout << "Author: Rishabh Mehta.\n";

    // Set Run Parameters
    cout << "Setting Run Parameters\n";
    setRunVars();
    cout << "This is RUN " + to_string(RUN_NO) << endl;

    // Muon generation
    cout << "Now generating the muon list:\n";
    muongen();
    cout << "Generation Complete!\n";
    cout << "No. of muons generated: " << muonList.size() << ".\n";

    // Photon generation
    cout << "Now generating the photons via muon propagation:\n";
    photongen();
    cout << "Generation Complete!\n";
    cout << "No. of photons detected: " << photonList.size() << ".\n";

    // Saving Muon list
    if (SAVE_MUON) {
        saveMuon();
        cout << "Muon list saved to " << ROOT_DIR << "muonList_Run" + to_string(RUN_NO) + ".root\n";
    }

    // savePhoton();
    if (SAVE_PHOTON) {
        savePhoton();
        cout << "Photon list saved to " << ROOT_DIR << "photonList_Run" + to_string(RUN_NO) + ".root\n";
    } 
}
