// Header file for Config Options

#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <TSystem.h>
#include <string>
#include <map>

using namespace std;

extern map<string, int> iRunVars;
extern map<string, float> fRunVars;
extern map<string, string> sRunVars;
extern map<string, bool> bRunVars;

extern int N_EVENTS, MAX_REFL, RUN_NO, RAND_SEED;
extern float S_LENGTH, S_WIDTH, S_HEIGHT, D_POS_X, D_POS_Y, PATH_STEP;
extern bool SAVE_MUON, SAVE_PHOTON;
extern string ROOT_DIR;

extern void setRunVars();

#endif