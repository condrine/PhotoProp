// Script for propagating the photon

#include <iostream>
#include <cmath>
#include <TRandom3.h>

#include "../include/muon.h"
#include "../include/photon.h"
#include "../include/config.h"

using namespace std;

// returns whether or not photon survives
bool photonProp(Photon P) {

    Coords temp = P.coords;
    float dist[3];
    for (int i = 0; i < MAX_REFL; i++) {
        
        // Precalculation for optimisation
        float theta = temp.theta;
        float phi = temp.phi;

        float sintheta = sin(theta);
        float costheta = cos(theta);
        float sinphi = sin(phi);
        float cosphi = cos(phi);

        float P_x = temp.x;
        float P_y = temp.y;
        float P_z = temp.z;

        // Find plane of intersection of particle
        dist[0] = (sintheta*cosphi > 0) ? (S_LENGTH/2. - P_x)/(sintheta*cosphi) : (-S_LENGTH/2. - P_x)/(sintheta*cosphi);
        dist[1] = (sintheta*sinphi > 0) ? (S_WIDTH/2. - P_y)/(sintheta*sinphi) : (-S_WIDTH/2. - P_y)/(sintheta*sinphi);
        dist[2] = (costheta > 0) ? (S_HEIGHT - P_z)/costheta : -P_z/costheta;

        // Calculate the plane of intersection
        int min_index = distance(dist,min_element(dist, dist + 3));
        float d = dist[min_index]; // distance from original point to plane

        // Check for attenuation
        float lambda_sc = 100.;
        float x_surv = -lambda_sc*log(r->Uniform());
        if (d > x_surv) return false;
        
        // Update particle coords
        temp.x = P_x + d*sintheta*cosphi;
        temp.y = P_y + d*sintheta*sinphi;
        temp.z = P_z + d*costheta;

        // check if particle hit photodetector
        if (min_index  == 0 && sintheta*cosphi > 0 && temp.y <= -S_WIDTH/2. + 1) {
            P.coords = temp;
            photonList.push_back(P);
            return true;
        }

        // Check for reflective loss
        if (r->Uniform() < 0.05) return false;

        // reflect particle
        if (min_index  == 0) {
            temp.phi = M_PI - phi;
        } else if (min_index == 1) {
            temp.phi = -phi;
        } else if (min_index == 2) {
            temp.theta = -theta;
        }
    }
    
    return false;
}