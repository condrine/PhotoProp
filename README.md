# Description
 This code simulates of photon production due to minimallyionising muons incident on a plastic scintillator detector and their subsequent detectionby a photodetector placed on one end of the scintillator. It also provides a function f fitting the simulation files so obtained by the simulation using a Landau Distribution

# Prerequisites
To run this code, latest version of gcc 11 and ROOT (6.24) are recommended. This code has been tested to run on Fedora and other linux servers only, and its compatibility with other systems is not guaranteed.

# Simulation
Simuation portion of the code uses files present in *src* and *include* directory.

## Building
To build the code, run ```./build.sh``` or ```source build.sh```. Please make sure the prerequisites are fulfilled before this step.

## Config
After building, different configuration options can be set using the *config.txt* file. The most common and recommended changes to be done are to *RUN_NO*, *EVENT_NO* and *RAND_SEED*. Apart from these, other config parameters can also be changed accordlingly.

## Execution
After doing the necessary config, run ```./runsim``` to execute the code. As this code is procedural, it might take a lot of time depending upon the number of events specified. Have a coffee!

# Fitting
The fitting is done using the *fitter.cc* file. This is to be done after Simulation is complete. Make sure that all your data files (*muonList_RunX.root*) are present in *ROOTFiles* directory. Run ```root -l fitter.cc``` to generate, fit and save the histogram. The saved file will be named as *pFit.png*.
