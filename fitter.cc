// Script for Histogram generation and fitting

#include <iostream>
#include "TCanvas.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1I.h"
#include "TPaveStats.h"
#include "TF1.h"

using namespace std;

// Function that initialises a hist
TH1I* createHist(TString name, TString title, TString X_Title, TString Y_Title, Int_t NBINS, Float_t lim1, Float_t lim2, Int_t m_color, Int_t m_style, Int_t m_size) {

    // define and style histogram
    TH1I* hist = new TH1I(name, title, NBINS, lim1, lim2);
    hist->SetMarkerColor(m_color);
    hist->SetMarkerStyle(m_style);
    hist->SetMarkerSize(m_size);
    hist->SetFillColor(m_color);
    hist->SetFillStyle(3001);
    hist->GetXaxis()->SetTitle(X_Title);
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetTitleSize(0.05);
    hist->GetXaxis()->SetTitleOffset(1.041);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitle(Y_Title);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelOffset(-0.001);
    hist->GetYaxis()->SetTitleSize(0.05);
    hist->GetYaxis()->SetTitleOffset(1.2);
    hist->GetYaxis()->SetTitleFont(42);

    return hist;
}

// Function that initialises a canvas
TCanvas* createCanvas(TString name, TString title, Int_t w, Int_t h) {

    TCanvas *c = new TCanvas(name, title, w, h);
    c->SetFillColor(10);
    c->SetBorderMode(0);
    c->SetBorderSize(2);
    c->SetLeftMargin(0.1322082);
    c->SetRightMargin(0.05063291);
    c->SetTopMargin(0.04862579);
    c->SetBottomMargin(0.1501057);
    c->SetFrameFillColor(0);
    c->SetFrameBorderMode(0);
    c->SetFrameBorderMode(0);

    return c;
}

// Main macro
void fitter() {

    // Declare and initialise a chain of files
    TChain* ch = new TChain("t");
    ch->Add("ROOTFiles/muonList*");

    // Set the nPhoton branch
    Int_t nPhotons;
    ch->SetBranchAddress("nPhotons", &nPhotons);
    
    // Get total entries in data
    Int_t nch =(int)ch->GetEntries();
    cout <<"Number of Entries in data files = " << nch << endl;

    // Declare a histogram
    Int_t NBINS = 200;
    TString X_Title = "No. of Photons";
    TString Y_Title = "Entries";
    TH1I* nP = createHist("nPhotons", "Photon Hist", X_Title, Y_Title, NBINS, 0, NBINS, 4, 2, 1);
    
    // Fill the histogram
    for(int i=0;i< nch;i++) {
        ch->GetEntry(i);
        nP->Fill(nPhotons);
    }

    // Fit the histogram
    nP->Fit("landau");

    // Styling
    gStyle->SetOptTitle(0);
    gStyle->SetOptFit(0111);
    gStyle->SetOptStat(1);

    // Draw the histogram
    TCanvas *s = createCanvas("s","No. of photons",1200,800);
    nP->Draw();

    // Refine stat box location
    TPaveStats *st = (TPaveStats*)nP->FindObject("stats");
    st->SetX1NDC(0.6);
    st->SetX2NDC(0.9);

    // Update canvas and save
    s->Update();
    s->SaveAs("pFit.png");
}
