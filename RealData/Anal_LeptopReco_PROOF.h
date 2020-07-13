/////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 28 22:40:34 2019 by ROOT version 5.34/38
// from TTree T1/WPrimeNtuple
// found on file: root://se01.indiacms.res.in//store/user/chatterj/TT_Mtt-700to1000_TuneCP5_PSweights_13TeV-powheg-pythia8/crab_crab_L5JERC_TTBar_Mtt_700to1000_Autumn18_JECV19/191113_143123/0000/rootuple_jerc_l5_106.root
//////////////////////////////////////////////////////////
//Anal_LeptopReco_PROOF
#ifndef Anal_LeptopReco_PROOF_h
#define Anal_LeptopReco_PROOF_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TTree.h>
#include <TMath.h>

#include "TLorentzVector.h"
#include <TProofOutputFile.h>
#include <TProofServ.h>

#include <string>
#include <cmath>
#include <cassert>
#include <sstream>
#include <string>
#include "TFileCollection.h"
#include "THashList.h"
#include "TBenchmark.h"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"


using namespace TMVA;

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

int getbinid(double val, int nbmx, float* array) {
  if (val<array[0]) return -2;
  for (int ix=0; ix<=nbmx; ix++) {
    if (val < array[ix]) return ix-1;
  }
  return -3;
}

double theta_to_eta(double theta) { return -log(tan(theta/2.)); }

double eta_to_theta(double eta){
  return(2*atan(exp(-2*eta)));
}

double PhiInRange(const double& phi) {
  double phiout = phi;
  
  if( phiout > 2*M_PI || phiout < -2*M_PI) {
    phiout = fmod( phiout, 2*M_PI);
  }
  if (phiout <= -M_PI) phiout += 2*M_PI;
  else if (phiout >  M_PI) phiout -= 2*M_PI;
  
  return phiout;
}

double delta2R(double eta1, double phi1, double eta2, double phi2) {
  return sqrt(pow(eta1 - eta2,2) +pow(PhiInRange(phi1 - phi2),2));
}

double diff_func(double f1, double f2){
  double ff = pow(f1-f2,2)*1./pow(f1+f2,2);
  return ff;
}


bool Muon_TightID(bool muonisGL,bool muonisPF, float muonchi, float muonhit, float muonmst,
				  float muontrkvtx, float muondz, float muonpixhit, float muontrklay){
bool tightid = false;
if(muonisGL && muonisPF){
	if(muonchi<10 && muonhit>0 && muonmst>1){
		if(fabs(muontrkvtx)<0.2 && fabs(muondz)<0.5){
			if(muonpixhit>0 && muontrklay>5){
				tightid = true;
				}
			} 
		}
	}	
return tightid;
}
//https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Tight_Muon

bool Muon_Iso_ID(float muonpfiso)
{
bool isoid = false;	
if(muonpfiso<0.15) { isoid = true; } //SR
//if(muonpfiso>0.15) { isoid = true; }  // CR
return isoid;
}

class Anal_LeptopReco_PROOF : public TSelector {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  
  static const int njetmx = 20;
  static const int njetmxAK8 = 10;
  static const int npartmx = 25;
  
  float weight;
  float event_pt_weight;
   
  bool isMC;
  bool SemiLeptt;
  bool DiLeptt;
  bool Hadtt;
  
  TH1D *hist_event_count;

  // Declaration of leaf types
  Int_t           irun;
  Int_t           ilumi;
  UInt_t          ievt;
  Int_t           nprim;
  Int_t           nvert;
  Int_t           ndofct;
  Int_t           nchict;
  Double_t        Rho;
  Double_t        event_weight;
  Float_t         qscale;
  Int_t           npu_vert;
  Int_t           trig_value;
  Int_t           ihlt01;
  Int_t           ihlt02;
  Int_t           ihlt03;
  Int_t           ihlt04;
  Int_t           ihlt05;
  Int_t           ihlt06;
  Int_t           ihlt07;
  Int_t           ihlt08;
  Int_t           ihlt09;
  Int_t           ihlt10;
  Int_t           ihlt11;
  Int_t           ihlt12;
  Int_t           ihlt13;
  Int_t           ihlt14;
  Int_t           ihlt15;
  Int_t           ihlt16;
  Int_t           ihlt17;

  Float_t         prescl01;
  Float_t         prescl02;
  Float_t         prescl03;
  Float_t         prescl04;
  Float_t         prescl05;
  Float_t         prescl06;
  Float_t         prescl07;
  Float_t         prescl08;
  Float_t         prescl09;
  Float_t         prescl10;
  Float_t         prescl11;
  Float_t         prescl12;
  Float_t         prescl13;
  Float_t         prescl14;
  Float_t         prescl15;
  Float_t         prescl16;
  Float_t         prescl17;

  Int_t           ntrigobjs;
  Float_t         trigobjpt[20];   //[ntrigobjs]
  Float_t         trigobjeta[20];   //[ntrigobjs]
  Float_t         trigobjphi[20];   //[ntrigobjs]
  Float_t         trigobje[20];   //[ntrigobjs]
  Bool_t          trigobjHLT[20];   //[ntrigobjs]
  Bool_t          trigobjL1[20];   //[ntrigobjs]
  Bool_t          trigobjBoth[20];   //[ntrigobjs]
  Int_t           trigobjIhlt[20];   //[ntrigobjs]
  Float_t         PFMET;
  Float_t         PFMETPhi;
  Float_t         MisEtSig;
  Float_t         sumEt;
  Int_t           npfjetAK8;
  Bool_t          pfjetAK8looseID[njetmxAK8];
  Bool_t          pfjetAK8tightID[njetmxAK8];
  Bool_t          pfjetAK8tightLVID[njetmxAK8];
  Float_t         pfjetAK8pt[njetmxAK8];
  Float_t         pfjetAK8y[njetmxAK8];
  Float_t         pfjetAK8phi[njetmxAK8];
  Float_t         pfjetAK8mass[njetmxAK8];
  Float_t         pfjetAK8JEC[njetmxAK8];
  Float_t         pfjetAK8JECL1[njetmxAK8];
  Float_t         pfjetAK8JECL2[njetmxAK8];
  Float_t         pfjetAK8JECL3[njetmxAK8];
  Float_t         pfjetAK8JECL2L3[njetmxAK8];
  Float_t         pfjetAK8btag_CMVA[njetmxAK8];
  Float_t         pfjetAK8btag_CSV[njetmxAK8];
  Float_t         pfjetAK8btag_DeepCSV[njetmxAK8];
  Float_t         pfjetAK8btag_DeepFlav[njetmxAK8];
  Float_t 	  pfjetAK8matchAK4deepb[njetmxAK8];
  Float_t         pfjetAK8DeepTag_TvsQCD[njetmxAK8];
  Float_t         pfjetAK8DeepTag_WvsQCD[njetmxAK8];
  Float_t         pfjetAK8DeepTag_ZvsQCD[njetmxAK8];
  Float_t         pfjetAK8DeepTag_BBvsQCD[njetmxAK8];
  Float_t         pfjetAK8DeepTag_CCvsQCD[njetmxAK8];
  Float_t         pfjetAK8CHF[njetmxAK8];
  Float_t         pfjetAK8NHF[njetmxAK8];
  Float_t         pfjetAK8CEMF[njetmxAK8];
  Float_t         pfjetAK8NEMF[njetmxAK8];
  Float_t         pfjetAK8MUF[njetmxAK8];
  Float_t         pfjetAK8PHF[njetmxAK8];
  Float_t         pfjetAK8EEF[njetmxAK8];
  Float_t         pfjetAK8HFHF[njetmxAK8];
  Float_t         pfjetAK8HFEMF[njetmxAK8];
  Float_t         pfjetAK8HOF[njetmxAK8];
  Float_t		   pfjetAK8neuemfrac[njetmxAK8];
  Float_t		   pfjetAK8neunhadfrac[njetmxAK8];
  Float_t		   pfjetAK8HadF[njetmxAK8];
  Float_t		   pfjetAK8NHadF[njetmxAK8];
  Float_t		   pfjetAK8EmF[njetmxAK8];
  Int_t           pfjetAK8CHM[njetmxAK8];
  Int_t           pfjetAK8NHM[njetmxAK8];
  Int_t           pfjetAK8CEMM[njetmxAK8];
  Int_t           pfjetAK8NEMM[njetmxAK8];
  Int_t           pfjetAK8MUM[njetmxAK8];
  Int_t           pfjetAK8PHM[njetmxAK8];
  Int_t           pfjetAK8EEM[njetmxAK8];
  Int_t           pfjetAK8HFHM[njetmxAK8];
  Int_t           pfjetAK8HFEMM[njetmxAK8];
  Int_t           pfjetAK8Neucons[njetmxAK8];
  Int_t           pfjetAK8Chcons[njetmxAK8];
  Int_t		   pfjetAK8ncons[njetmxAK8];
  Float_t         pfjetAK8reso[njetmxAK8];
  Float_t         pfjetAK8resoup[njetmxAK8];
  Float_t         pfjetAK8resodn[njetmxAK8];
  Float_t         pfjetAK8jesup_pu[njetmxAK8];
  Float_t         pfjetAK8jesup_rel[njetmxAK8];
  Float_t         pfjetAK8jesup_scale[njetmxAK8];
  Float_t         pfjetAK8jesup_total[njetmxAK8];
  Float_t         pfjetAK8jesdn_pu[njetmxAK8];
  Float_t         pfjetAK8jesdn_rel[njetmxAK8];
  Float_t         pfjetAK8jesdn_scale[njetmxAK8];
  Float_t         pfjetAK8jesdn_total[njetmxAK8];
  Float_t         pfjetAK8chrad[njetmxAK8];
  Float_t         pfjetAK8axis2[njetmxAK8];
  Float_t         pfjetAK8pTD[njetmxAK8];
  Float_t         pfjetAK8sdmass[njetmxAK8];
  Float_t         pfjetAK8elsubjptrat[njetmxAK8];
  bool			  pfjetAK8haspfelectron[njetmxAK8];


  Float_t         pfjetAK8tau1[njetmxAK8];
  Float_t         pfjetAK8tau2[njetmxAK8];
  Float_t         pfjetAK8tau3[njetmxAK8];
  Float_t         pfjetAK8tau21[njetmxAK8];
  Float_t         pfjetAK8tau32[njetmxAK8];
  Float_t         pfjetAK8sub1pt[njetmxAK8];
  Float_t         pfjetAK8sub1eta[njetmxAK8];
  Float_t         pfjetAK8sub1phi[njetmxAK8];
  Float_t         pfjetAK8sub1mass[njetmxAK8];
  Float_t         pfjetAK8sub1btag[njetmxAK8];
  Float_t         pfjetAK8sub1chhadfrac[njetmxAK8];
  Float_t         pfjetAK8sub1neuhadfrac[njetmxAK8];
  Float_t         pfjetAK8sub1emfrac[njetmxAK8];
  Float_t         pfjetAK8sub1phofrac[njetmxAK8];
  Float_t         pfjetAK8sub1mufrac[njetmxAK8];
  Float_t		   pfjetAK8sub1hadfrac[njetmxAK8];
  Float_t         pfjetAK8sub2pt[njetmxAK8];
  Float_t         pfjetAK8sub2eta[njetmxAK8];
  Float_t         pfjetAK8sub2phi[njetmxAK8];
  Float_t         pfjetAK8sub2mass[njetmxAK8];
  Float_t         pfjetAK8sub2btag[njetmxAK8];
  Float_t         pfjetAK8sub2chhadfrac[njetmxAK8];
  Float_t         pfjetAK8sub2neuhadfrac[njetmxAK8];
  Float_t         pfjetAK8sub2emfrac[njetmxAK8];
  Float_t         pfjetAK8sub2phofrac[njetmxAK8];
  Float_t         pfjetAK8sub2mufrac[njetmxAK8];
  Float_t		   pfjetAK8sub2hadfrac[njetmxAK8];
  Float_t		   pfjetAK8subhaddiff[njetmxAK8];
  Float_t		   pfjetAK8subemdiff[njetmxAK8];
  Float_t         pfjetAK8_leppt[njetmxAK8];
  Float_t         pfjetAK8_lepeta[njetmxAK8];
  Float_t         pfjetAK8_lepphi[njetmxAK8];
  Float_t         pfjetAK8_lepe[njetmxAK8];
  Float_t         pfjetAK8_bpt[njetmxAK8];
  Float_t         pfjetAK8_beta[njetmxAK8];
  Float_t         pfjetAK8_bphi[njetmxAK8];
  Float_t         pfjetAK8_be[njetmxAK8];
  Float_t         pfjetAK8_nupt[njetmxAK8];
  Float_t         pfjetAK8_nueta[njetmxAK8];
  Float_t         pfjetAK8_nuphi[njetmxAK8];
  Float_t         pfjetAK8_nue[njetmxAK8];
  Float_t         pfjetAK8_bbyW_E[njetmxAK8];
  Float_t         pfjetAK8_Kfactor[njetmxAK8];
  Float_t         pfjetAK8_Rnew[njetmxAK8];
  Float_t		   pfjetAK8stau21[njetmxAK8];
  Float_t		   pfjetAK8stau32[njetmxAK8];
  Float_t		   pfjetAK8subptdiff[njetmxAK8];
  Float_t		   pfjetAK8subpldiff[njetmxAK8];
  Float_t		   pfjetAK8subbtag[njetmxAK8];
  Bool_t 		   pfjetAK8haselectron[njetmxAK8];
  Bool_t 		   pfjetAK8hasmuon[njetmxAK8];
  Bool_t		   pfjetAK8hasb[njetmxAK8];
  Bool_t		   pfjetAK8hasqg[njetmxAK8];
  Bool_t 		   pfjetAK8hashadtop[njetmxAK8];
  Bool_t 		   pfjetAK8hasleptop[njetmxAK8];
  Bool_t		   pfjetAK8hastop[njetmxAK8];
  Float_t		   pfjetAK8re_tvsb[njetmxAK8];
  Float_t		   pfjetAK8rnu_tvsb[njetmxAK8];

  Float_t                  pfjetAK8elinsubpt[njetmxAK8];
  Float_t                  pfjetAK8elinsubeta[njetmxAK8];
  Float_t                  pfjetAK8elinsubphi[njetmxAK8];
  Float_t                  pfjetAK8elinsube[njetmxAK8];
  Float_t                  pfjetAK8elinsubmass[njetmxAK8];
  Float_t                  pfjetAK8elinsubjpt[njetmxAK8];
  Float_t                  pfjetAK8elinsubjeta[njetmxAK8];
  Float_t                  pfjetAK8elinsubjphi[njetmxAK8];
  Float_t                  pfjetAK8elinsubje[njetmxAK8];
  Float_t                  pfjetAK8elinsubjmass[njetmxAK8];

  Int_t           npfjetAK4;
  Bool_t          pfjetAK4looseID[njetmx];
  Bool_t          pfjetAK4tightID[njetmx];
  Bool_t          pfjetAK4tightLVID[njetmx];
  Float_t         pfjetAK4pt[njetmx];
  Float_t         pfjetAK4eta[njetmx];
  Float_t         pfjetAK4y[njetmx];
  Float_t         pfjetAK4phi[njetmx];
  Float_t         pfjetAK4mass[njetmx];
  Float_t         pfjetAK4JEC[njetmx];
  Float_t         pfjetAK4JECL1[njetmx];
  Float_t         pfjetAK4JECL2[njetmx];
  Float_t         pfjetAK4JECL3[njetmx];
  Float_t         pfjetAK4JECL2L3[njetmx];
  Float_t         pfjetAK4btag_CMVA[njetmx];
  Float_t         pfjetAK4btag_CSV[njetmx];
  Float_t         pfjetAK4btag_DeepCSV[njetmx];
  Float_t         pfjetAK4btag_DeepFlav[njetmx];
  Float_t         pfjetAK4btag_DeepQCD[njetmx];
  Float_t         pfjetAK4reso[njetmx];
  Float_t         pfjetAK4resoup[njetmx];
  Float_t         pfjetAK4resodn[njetmx];
  Float_t         pfjetAK4jesup_pu[njetmx];
  Float_t         pfjetAK4jesup_rel[njetmx];
  Float_t         pfjetAK4jesup_scale[njetmx];
  Float_t         pfjetAK4jesup_total[njetmx];
  Float_t         pfjetAK4jesdn_pu[njetmx];
  Float_t         pfjetAK4jesdn_rel[njetmx];
  Float_t         pfjetAK4jesdn_scale[njetmx];
  Float_t         pfjetAK4jesdn_total[njetmx];
  Int_t           pfjetAK4hadronflav[njetmx];
  Int_t           pfjetAK4partonflav[njetmx];
  Float_t         pfjetAK4qgl[njetmx];
   Float_t         pfjetAK4PUID[njetmx];
   Int_t           pfjetAK4GenMatch;
   Float_t         GENMET;
   Float_t         GENMETPhi;
   Float_t         GENMETSig;
   Int_t           ngenjetAK8;
   Float_t         genjetAK8pt[njetmx];
   Float_t         genjetAK8y[njetmx];
   Float_t         genjetAK8phi[njetmx];
   Float_t         genjetAK8mass[njetmx];
   Float_t         genjetAK8sdmass[njetmx];
   Float_t         genjetAK8btag[njetmx];
   Float_t         genjetAK8tau1[njetmx];
   Float_t         genjetAK8tau2[njetmx];
   Float_t         genjetAK8tau3[njetmx];
   Float_t         genjetAK8chrad[njetmx];
   Float_t         genjetAK8sub1pt[njetmx];
   Float_t         genjetAK8sub1y[njetmx];
   Float_t         genjetAK8sub1phi[njetmx];
   Float_t         genjetAK8sub1mass[njetmx];
   Float_t         genjetAK8sub1hadfrac[njetmx];
   Float_t         genjetAK8sub1emfrac[njetmx];
   Float_t         genjetAK8sub2pt[njetmx];
   Float_t         genjetAK8sub2y[njetmx];
   Float_t         genjetAK8sub2phi[njetmx];
   Float_t         genjetAK8sub2mass[njetmx];
   Float_t         genjetAK8sub2hadfrac[njetmx];
   Float_t         genjetAK8sub2emfrac[njetmx];
   Int_t           ngenjetAK4;
   Float_t         genjetAK4pt[njetmx];
   Float_t         genjetAK4y[njetmx];
   Float_t         genjetAK4phi[njetmx];
   Float_t         genjetAK4mass[njetmx];
   Float_t         genjetAK4btag[njetmx];
   Int_t           ngenparticles;
   Int_t           genpartstatus[npartmx];
   Int_t           genpartpdg[npartmx];
   Int_t           genpartmompdg[npartmx];
   Int_t           genpartdaugno[npartmx];
   Bool_t          genpartfromhard[npartmx];
   Bool_t          genpartfromhardbFSR[npartmx];
   Float_t         genpartpt[npartmx];
   Float_t         genparteta[npartmx];
   Float_t         genpartphi[npartmx];
   Float_t         genpartm[npartmx];
   Float_t         genpartq[npartmx];
   Int_t           genpartpair[npartmx];
   Int_t           ngenelectrons;
   Float_t         genelectronpt[npartmx];
   Float_t         genelectroneta[npartmx];
   Float_t         genelectronphi[npartmx];
   Float_t         genelectronm[npartmx];
   Int_t	   nleptop;
   Int_t	   nhadtop;
   Int_t           ngenmuons;
   Float_t         genmuonpt[npartmx];
   Float_t         genmuoneta[npartmx];
   Float_t         genmuonphi[npartmx];
   Float_t         genmuonm[npartmx];
   Int_t           ngenqgs;
   Float_t         genqgpt[npartmx];
   Float_t         genqgeta[npartmx];
   Float_t         genqgphi[npartmx];
   Float_t         genqgm[npartmx];
   Int_t           ngenbs;
   Float_t         genbpt[npartmx];
   Float_t         genbeta[npartmx];
   Float_t         genbphi[npartmx];
   Float_t         genbm[npartmx];
   Int_t	   ngentops;
   Float_t	   gentoppt[npartmx];
   Float_t	   gentopeta[npartmx];
   Float_t	   gentopphi[npartmx];
   Float_t	   gentopm[npartmx];
   Int_t	   gentopid[npartmx];
   Int_t           nmuons;
   Bool_t          muonisPF[njetmx];
   Bool_t          muonisGL[njetmx];
   Bool_t          muonisTRK[njetmx];
   Bool_t          muonisLoose[njetmx];
   Bool_t          muonisGoodGL[njetmx];
   Bool_t          muonisMed[njetmx];
   Float_t         muonpt[njetmx];
   Float_t         muonp[njetmx];
   Float_t         muone[njetmx];
   Float_t         muoneta[njetmx];
   Float_t         muonphi[njetmx];
   Float_t         muondrbm[njetmx];
   Float_t         muontrkvtx[njetmx];
   Float_t         muondz[njetmx];
   Float_t         muonpter[njetmx];
   Float_t         muonchi[njetmx];
   Int_t           muonndf[njetmx];
   Float_t         muonecal[njetmx];
   Float_t         muonhcal[njetmx];
   Float_t         muonemiso[njetmx];
   Float_t         muonhadiso[njetmx];
   Float_t         muonpfiso[njetmx];
   Float_t         muontkpt03[njetmx];
   Float_t         muontkpt05[njetmx];
   Float_t         muonposmatch[njetmx];
   Float_t         muontrkink[njetmx];
   Float_t         muonsegcom[njetmx];
   Float_t         muonthit[njetmx];
   Float_t         muonpixhit[njetmx];
   Float_t         muonmst[njetmx];
   Float_t         muontrklay[njetmx];
   Float_t         muonvalfrac[njetmx];
   Int_t           nelecs;
   Float_t         elpt[njetmx];
   Float_t         eldxy_sv[njetmx];
   Float_t         eleta[njetmx];
   Float_t         elphi[njetmx];
   Float_t         elp[njetmx];
   Float_t         ele[njetmx];
   Bool_t          elmvaid[njetmx];
   Bool_t          elmvaid_noIso[njetmx];
   Float_t         eldxy[njetmx];
   Float_t         eldz[njetmx];
   Float_t         elhovere[njetmx];
   Float_t         elchi[njetmx];
   Int_t           elndf[njetmx];
   Float_t         eltkpt03[njetmx];
   Float_t         eltkpt04[njetmx];
   Float_t         elemiso04[njetmx];
   Float_t         elhadiso04[njetmx];
   Float_t         eletain[njetmx];
   Float_t         elphiin[njetmx];
   Float_t         elsceta[njetmx];
   Float_t         elsupcl_eta[njetmx];
   Float_t         elsupcl_phi[njetmx];
   Float_t         elsupcl_rawE[njetmx];
   Float_t         elfbrem[njetmx];
   Float_t         elhadisodepth03[njetmx];
   Float_t         eleoverp[njetmx];
   Float_t         elietaieta[njetmx];
   Float_t         elmisshits[njetmx];
   Float_t         elchhadiso[njetmx];
   Float_t         elneuhadiso[njetmx];
   Float_t         elphoiso[njetmx];
   Float_t         elpuchhadiso[njetmx];
   Float_t         elpfiso[njetmx];
   Float_t         elconvdist[njetmx];
   Float_t         elconvdoct[njetmx];
   
   //***al el ID variables****//
   Float_t         elsigmaieta[njetmx];
   Float_t         elsigmaiphi[njetmx];
   Float_t         elr9full[njetmx];
   Float_t         elsupcl_etaw[njetmx];
   Float_t         elsupcl_phiw[njetmx];
   Float_t         elhcaloverecal[njetmx];
   Float_t         elcloctftrkn[njetmx];
   Float_t         elcloctftrkchi2[njetmx];
   Float_t         ele1x5bye5x5[njetmx];
   Float_t         elnormchi2[njetmx];
   Float_t         elhitsmiss[njetmx];
   Float_t         eltrkmeasure[njetmx];
   Float_t         elconvtxprob[njetmx];
   Float_t         elecloverpout[njetmx];
   Float_t         elecaletrkmomentum[njetmx];
   Float_t         eldeltaetacltrkcalo[njetmx];
   Float_t         elsupcl_preshvsrawe[njetmx];
   Float_t         elpfisolsumphet[njetmx];
   Float_t         elpfisolsumchhadpt[njetmx];
   Float_t         elpfsiolsumneuhadet[njetmx];

   Int_t           nphotons;
   Float_t         phoe[njetmx];
   Float_t         phoeta[njetmx];
   Float_t         phophi[njetmx];
   Bool_t          phomvaid[njetmx];
   Float_t         phoe1by9[njetmx];
   Float_t         phoe9by25[njetmx];
   Float_t         photrkiso[njetmx];
   Float_t         phoemiso[njetmx];
   Float_t         phohadiso[njetmx];
   Float_t         phochhadiso[njetmx];
   Float_t         phoneuhadiso[njetmx];
   Float_t         phophoiso[njetmx];
   Float_t         phoPUiso[njetmx];
   Float_t         phohadbyem[njetmx];
   Float_t         phoietaieta[njetmx];

   // List of branches
   TBranch        *b_irun;   //!
   TBranch        *b_ilumi;   //!
   TBranch        *b_ievt;   //!
   TBranch        *b_nprim;   //!
   TBranch        *b_nvert;   //!
   TBranch        *b_ndofct;   //!
   TBranch        *b_nchict;   //!
   TBranch        *b_Rho;   //!
   TBranch        *b_event_weight;   //!
   TBranch        *b_qscale;   //!
   TBranch        *b_npu_vert;   //!
   TBranch        *b_trig_value;   //!
   TBranch        *b_ihlt01;   //!
   TBranch        *b_ihlt02;   //!
   TBranch        *b_ihlt03;   //!
   TBranch        *b_ihlt04;   //!
   TBranch        *b_ihlt05;   //!
   TBranch        *b_ihlt06;   //!
   TBranch        *b_ihlt07;   //!
   TBranch        *b_ihlt08;   //!
   TBranch        *b_ihlt09;   //!
   TBranch        *b_ihlt10;   //!
   TBranch        *b_ihlt11;   //!
   TBranch        *b_ihlt12;   //!                                                                               
   TBranch        *b_ihlt13;   //!                                                                               
   TBranch        *b_ihlt14;   //!                                                                               
   TBranch        *b_ihlt15;   //!                                                                               
   TBranch        *b_ihlt16;   //!                                                                               
   TBranch        *b_ihlt17;   //!

   TBranch        *b_prescl01;   //!
   TBranch        *b_prescl02;   //!
   TBranch        *b_prescl03;   //!
   TBranch        *b_prescl04;   //!
   TBranch        *b_prescl05;   //!
   TBranch        *b_prescl06;   //!
   TBranch        *b_prescl07;   //!
   TBranch        *b_prescl08;   //!
   TBranch        *b_prescl09;   //!
   TBranch        *b_prescl10;   //!
   TBranch        *b_prescl11;   //!
   TBranch        *b_prescl12;   //!
   TBranch        *b_prescl13;   //!                                                                             
   TBranch        *b_prescl14;   //!                                                                             
   TBranch        *b_prescl15;   //!                                                                             
   TBranch        *b_prescl16;   //!                                                                             
   TBranch        *b_prescl17;   //!                                                                             

   TBranch        *b_ntrigobjs;   //!
   TBranch        *b_trigobjpt;   //!
   TBranch        *b_trigobjeta;   //!
   TBranch        *b_trigobjphi;   //!
   TBranch        *b_trigobje;   //!
   TBranch        *b_trigobjHLT;   //!
   TBranch        *b_trigobjL1;   //!
   TBranch        *b_trigobjBoth;   //!
   TBranch        *b_trigobjIhlt;   //!
   TBranch        *b_miset;   //!
   TBranch        *b_misphi;   //!
   TBranch        *b_misetsig;   //!
   TBranch        *b_sumEt;   //!
   TBranch        *b_npfjetAK8;   //!
   TBranch        *b_pfjetAK8looseID;   //!
   TBranch        *b_pfjetAK8tightID;   //!
   TBranch        *b_pfjetAK8tightLVID;   //!
   TBranch        *b_pfjetAK8pt;   //!
   TBranch        *b_pfjetAK8y;   //!
   TBranch        *b_pfjetAK8phi;   //!
   TBranch        *b_pfjetAK8mass;   //!
   TBranch        *b_pfjetAK8JEC;   //!
   TBranch        *b_pfjetAK8JECL1;   //!
   TBranch        *b_pfjetAK8JECL2;   //!
   TBranch        *b_pfjetAK8JECL3;   //!
   TBranch        *b_pfjetAK8JECL2L3;   //!
   TBranch        *b_pfjetAK8btag_CMVA;   //!
   TBranch        *b_pfjetAK8btag_CSV;   //!
   TBranch        *b_pfjetAK8btag_DeepCSV;   //!
   TBranch        *b_pfjetAK8btag_DeepFlav;   //!
   TBranch        *b_pfjetAK8DeepTag_TvsQCD;   //!
   TBranch        *b_pfjetAK8DeepTag_WvsQCD;   //!
   TBranch        *b_pfjetAK8DeepTag_ZvsQCD;   //!
   TBranch        *b_pfjetAK8DeepTag_BBvsQCD;   //!
   TBranch        *b_pfjetAK8DeepTag_CCvsQCD;   //!
   TBranch        *b_pfjetAK8CHF;   //!
   TBranch        *b_pfjetAK8NHF;   //!
   TBranch        *b_pfjetAK8CEMF;   //!
   TBranch        *b_pfjetAK8NEMF;   //!
   TBranch        *b_pfjetAK8MUF;   //!
   TBranch        *b_pfjetAK8PHF;   //!
   TBranch        *b_pfjetAK8EEF;   //!
   TBranch        *b_pfjetAK8HFHF;   //!
   TBranch        *b_pfjetAK8HFEMF;   //!
   TBranch        *b_pfjetAK8HOF;   //!
   TBranch        *b_pfjetAK8CHM;   //!
   TBranch        *b_pfjetAK8NHM;   //!
   TBranch        *b_pfjetAK8CEMM;   //!
   TBranch        *b_pfjetAK8NEMM;   //!
   TBranch        *b_pfjetAK8MUM;   //!
   TBranch        *b_pfjetAK8PHM;   //!
   TBranch        *b_pfjetAK8EEM;   //!
   TBranch        *b_pfjetAK8HFHM;   //!
   TBranch        *b_pfjetAK8HFEMM;   //!
   TBranch        *b_pfjetAK8Neucons;   //!
   TBranch        *b_pfjetAK8Chcons;   //!
   TBranch        *b_pfjetAK8reso;   //!
   TBranch        *b_pfjetAK8resoup;   //!
   TBranch        *b_pfjetAK8resodn;   //!
   TBranch        *b_pfjetAK8jesup_pu;   //!
   TBranch        *b_pfjetAK8jesup_rel;   //!
   TBranch        *b_pfjetAK8jesup_scale;   //!
   TBranch        *b_pfjetAK8jesup_total;   //!
   TBranch        *b_pfjetAK8jesdn_pu;   //!
   TBranch        *b_pfjetAK8jesdn_rel;   //!
   TBranch        *b_pfjetAK8jesdn_scale;   //!
   TBranch        *b_pfjetAK8jesdn_total;   //!
   TBranch        *b_pfjetAK8chrad;   //!
   TBranch        *b_pfjetAK8axis2;   //!
   TBranch        *b_pfjetAK8pTD;   //!
   TBranch        *b_pfjetAK8sdmass;   //!
   TBranch        *b_pfjetAK8elsubjptrat;
   TBranch        *b_pfjetAK8tau1;   //!
   TBranch        *b_pfjetAK8tau2;   //!
   TBranch        *b_pfjetAK8tau3;   //!
   TBranch        *b_pfjetAK8sub1pt;   //!
   TBranch        *b_pfjetAK8sub1eta;   //!
   TBranch        *b_pfjetAK8sub1phi;   //!
   TBranch        *b_pfjetAK8sub1mass;   //!
   TBranch        *b_pfjetAK8sub1btag;   //!
   TBranch        *b_pfjetAK8sub1chhadfrac;   //!
   TBranch        *b_pfjetAK8sub1neuhadfrac;   //!
   TBranch        *b_pfjetAK8sub1emfrac;   //!
   TBranch        *b_pfjetAK8sub1phofrac;   //!
   TBranch        *b_pfjetAK8sub1mufrac;   //!
   TBranch        *b_pfjetAK8sub2pt;   //!
   TBranch        *b_pfjetAK8sub2eta;   //!
   TBranch        *b_pfjetAK8sub2phi;   //!
   TBranch        *b_pfjetAK8sub2mass;   //!
   TBranch        *b_pfjetAK8sub2btag;   //!
   TBranch        *b_pfjetAK8sub2chhadfrac;   //!
   TBranch        *b_pfjetAK8sub2neuhadfrac;   //!
   TBranch        *b_pfjetAK8sub2emfrac;   //!
   TBranch        *b_pfjetAK8sub2phofrac;   //!
   TBranch        *b_pfjetAK8sub2mufrac;   //!
   TBranch        *b_pfjetAK8_leppt;   //!
   TBranch        *b_pfjetAK8_lepeta;   //!
   TBranch        *b_pfjetAK8_lepphi;   //!
   TBranch        *b_pfjetAK8_lepe;   //!
   TBranch        *b_pfjetAK8_bpt;   //!
   TBranch        *b_pfjetAK8_beta;   //!
   TBranch        *b_pfjetAK8_bphi;   //!
   TBranch        *b_pfjetAK8_be;   //!
   TBranch        *b_pfjetAK8_nupt;   //!
   TBranch        *b_pfjetAK8_nueta;   //!
   TBranch        *b_pfjetAK8_nuphi;   //!
   TBranch        *b_pfjetAK8_nue;   //!
   TBranch        *b_pfjetAK8_bbyW_E;   //!
   TBranch        *b_pfjetAK8_Kfactor;   //!
   TBranch        *b_pfjetAK8_Rnew;   //!
   TBranch        *b_pfjetAK8elinsubpt;
   TBranch        *b_pfjetAK8elinsubeta;
   TBranch        *b_pfjetAK8elinsubphi;
   TBranch        *b_pfjetAK8elinsube;
   TBranch        *b_pfjetAK8elinsubmass;
   TBranch        *b_pfjetAK8elinsubjpt;
   TBranch        *b_pfjetAK8elinsubjeta;
   TBranch        *b_pfjetAK8elinsubjphi;
   TBranch        *b_pfjetAK8elinsubje;
   TBranch        *b_pfjetAK8elinsubjmass;


   TBranch        *b_npfjetAK4;   //!
   TBranch        *b_pfjetAK4looseID;   //!
   TBranch        *b_pfjetAK4tightID;   //!
   TBranch        *b_pfjetAK4tightLVID;   //!
   TBranch        *b_pfjetAK4pt;   //!
   TBranch        *b_pfjetAK4eta;   //!
   TBranch        *b_pfjetAK4y;   //!
   TBranch        *b_pfjetAK4phi;   //!
   TBranch        *b_pfjetAK4mass;   //!
   TBranch        *b_pfjetAK4JEC;   //!
   TBranch        *b_pfjetAK4JECL1;   //!
   TBranch        *b_pfjetAK4JECL2;   //!
   TBranch        *b_pfjetAK4JECL3;   //!
   TBranch        *b_pfjetAK4JECL2L3;   //!
   TBranch        *b_pfjetAK4btag_CMVA;   //!
   TBranch        *b_pfjetAK4btag_CSV;   //!
   TBranch        *b_pfjetAK4btag_DeepCSV;   //!
   TBranch        *b_pfjetAK4btag_DeepFlav;   //!
   TBranch        *b_pfjetAK4btag_DeepQCD;   //!
   TBranch        *b_pfjetAK4reso;   //!
   TBranch        *b_pfjetAK4resoup;   //!
   TBranch        *b_pfjetAK4resodn;   //!
   TBranch        *b_pfjetAK4jesup_pu;   //!
   TBranch        *b_pfjetAK4jesup_rel;   //!
   TBranch        *b_pfjetAK4jesup_scale;   //!
   TBranch        *b_pfjetAK4jesup_total;   //!
   TBranch        *b_pfjetAK4jesdn_pu;   //!
   TBranch        *b_pfjetAK4jesdn_rel;   //!
   TBranch        *b_pfjetAK4jesdn_scale;   //!
   TBranch        *b_pfjetAK4jesdn_total;   //!
   TBranch        *b_pfjetAK4hadronflav;   //!
   TBranch        *b_pfjetAK4partonflav;   //!
   TBranch        *b_pfjetAK4qgl;   //!
   TBranch        *b_pfjetAK4PUID;   //!
   TBranch        *b_pfjetAK4GenMatch;   //!
   TBranch        *b_genmiset;   //!
   TBranch        *b_genmisphi;   //!
   TBranch        *b_genmisetsig;   //!
   TBranch        *b_ngenjetAK8;   //!
   TBranch        *b_genjetAK8pt;   //!
   TBranch        *b_genjetAK8y;   //!
   TBranch        *b_genjetAK8phi;   //!
   TBranch        *b_genjetAK8mass;   //!
   TBranch        *b_genjetAK8sdmass;   //!
   TBranch        *b_genjetAK8btag;   //!
   TBranch        *b_genjetAK8tau1;   //!
   TBranch        *b_genjetAK8tau2;   //!
   TBranch        *b_genjetAK8tau3;   //!
   TBranch        *b_genjetAK8chrad;   //!
   TBranch        *b_genjetAK8sub1pt;   //!
   TBranch        *b_genjetAK8sub1y;   //!
   TBranch        *b_genjetAK8sub1phi;   //!
   TBranch        *b_genjetAK8sub1mass;   //!
   TBranch        *b_genjetAK8sub1hadfrac;   //!
   TBranch        *b_genjetAK8sub1emfrac;   //!
   TBranch        *b_genjetAK8sub2pt;   //!
   TBranch        *b_genjetAK8sub2y;   //!
   TBranch        *b_genjetAK8sub2phi;   //!
   TBranch        *b_genjetAK8sub2mass;   //!
   TBranch        *b_genjetAK8sub2hadfrac;   //!
   TBranch        *b_genjetAK8sub2emfrac;   //!
   TBranch        *b_ngenjetAK4;   //!
   TBranch        *b_genjetAK4pt;   //!
   TBranch        *b_genjetAK4y;   //!
   TBranch        *b_genjetAK4phi;   //!
   TBranch        *b_genjetAK4mass;   //!
   TBranch        *b_genjetAK4btag;   //!
   TBranch        *b_ngenparticles;   //!
   TBranch        *b_genpartstatus;   //!
   TBranch        *b_genpartpdg;   //!
   TBranch        *b_genpartmompdg;   //!
   TBranch        *b_genpartdaugno;   //!
   TBranch        *b_genpartfromhard;   //!
   TBranch        *b_genpartfromhardbFSR;   //!
   TBranch        *b_genpartpt;   //!
   TBranch        *b_genparteta;   //!
   TBranch        *b_genpartphi;   //!
   TBranch        *b_genpartm;   //!
   TBranch        *b_genpartq;   //!
   TBranch        *b_nmuons;   //!
   TBranch        *b_muonisPF;   //!
   TBranch        *b_muonisGL;   //!
   TBranch        *b_muonisTRK;   //!
   TBranch        *b_muonisLoose;   //!
   TBranch        *b_muonisGoodGL;   //!
   TBranch        *b_muonisMed;   //!
   TBranch        *b_muonpt;   //!
   TBranch        *b_muonp;   //!
   TBranch        *b_muone;   //!
   TBranch        *b_muoneta;   //!
   TBranch        *b_muonphi;   //!
   TBranch        *b_muondrbm;   //!
   TBranch        *b_muontrkvtx;   //!
   TBranch        *b_muondz;   //!
   TBranch        *b_muonpter;   //!
   TBranch        *b_muonchi;   //!
   TBranch        *b_muonndf;   //!
   TBranch        *b_muonecal;   //!
   TBranch        *b_muonhcal;   //!
   TBranch        *b_muonemiso;   //!
   TBranch        *b_muonhadiso;   //!
   TBranch        *b_muonpfiso;   //!
   TBranch        *b_muontkpt03;   //!
   TBranch        *b_muontkpt05;   //!
   TBranch        *b_muonposmatch;   //!
   TBranch        *b_muontrkink;   //!
   TBranch        *b_muonsegcom;   //!
   TBranch        *b_muonthit;   //!
   TBranch        *b_muonpixhit;   //!
   TBranch        *b_muonmst;   //!
   TBranch        *b_muontrklay;   //!
   TBranch        *b_muonvalfrac;   //!
   TBranch        *b_nelecs;   //!
   TBranch        *b_elpt;   //!
   TBranch        *b_eldxy_sv;
   TBranch        *b_eleta;   //!
   TBranch        *b_elphi;   //!
   TBranch        *b_elp;   //!
   TBranch        *b_ele;   //!
   TBranch        *b_elmvaid;   //!
   TBranch        *b_elmvaid_noIso;   //!
   TBranch        *b_eldxy;   //!
   TBranch        *b_eldz;   //!
   TBranch        *b_elhovere;   //!
   TBranch        *b_elchi;   //!
   TBranch        *b_elndf;   //!
   TBranch        *b_eltkpt03;   //!
   TBranch        *b_eltkpt04;   //!
   TBranch        *b_elemiso04;   //!
   TBranch        *b_elhadiso04;   //!
   TBranch        *b_eletain;   //!
   TBranch        *b_elphiin;   //!
   TBranch        *b_elsceta;   //!
   TBranch        *b_elsupcl_eta;
   TBranch        *b_elsupcl_phi;
   TBranch        *b_elsupcl_rawE;
   TBranch        *b_elfbrem;   //!
   TBranch        *b_elhadisodepth03;   //!
   TBranch        *b_eleoverp;   //!
   TBranch        *b_elietaieta;   //!
   TBranch        *b_elmisshits;   //!
   TBranch        *b_elchhadiso;   //!
   TBranch        *b_elneuhadiso;   //!
   TBranch        *b_elphoiso;   //!
   TBranch        *b_elpuchhadiso;   //!
   TBranch        *b_elpfiso;   //!
   TBranch        *b_elconvdist;   //!
   TBranch        *b_elconvdoct;   //!
   
   TBranch        *b_elsigmaieta;
   TBranch        *b_elsigmaiphi;
   TBranch        *b_elr9full;
   TBranch        *b_elsupcl_etaw;
   TBranch        *b_elsupcl_phiw;
   TBranch        *b_elhcaloverecal;
   TBranch        *b_elcloctftrkn;
   TBranch        *b_elcloctftrkchi2;
   TBranch        *b_ele1x5bye5x5;
   TBranch        *b_elnormchi2;
   TBranch        *b_elhitsmiss;
   TBranch        *b_eltrkmeasure;
   TBranch        *b_elconvtxprob;
   TBranch        *b_elecloverpout;
   TBranch        *b_elecaletrkmomentum;
   TBranch        *b_eldeltaetacltrkcalo;
   TBranch        *b_elsupcl_preshvsrawe;
   TBranch        *b_elpfisolsumphet;
   TBranch        *b_elpfisolsumchhadpt;
   TBranch        *b_elpfsiolsumneuhadet;


   TBranch        *b_nphotons;   //!
   TBranch        *b_phoe;   //!
   TBranch        *b_phoeta;   //!
   TBranch        *b_phophi;   //!
   TBranch        *b_phomvaid;   //!
   TBranch        *b_phoe1by9;   //!
   TBranch        *b_phoe9by25;   //!
   TBranch        *b_photrkiso;   //!
   TBranch        *b_phoemiso;   //!
   TBranch        *b_phohadiso;   //!
   TBranch        *b_phochhadiso;   //!
   TBranch        *b_phoneuhadiso;   //!
   TBranch        *b_phophoiso;   //!
   TBranch        *b_phoPUiso;   //!
   TBranch        *b_phohadbyem;   //!
   TBranch        *b_phoietaieta;   //!
   
  static const int nmaxjet = 10;
 
  static const int nobshist = 14;
  
  const char *obsnames[nobshist] = {
	  "pt","y","mass",
	  "NHad","neuhad","sdmass","chrad","subhaddiff","tau21",
	  "DAK8_topvsQCD","bbyW_E","Kfactor",
	  "re","rnu"
	  };
	  
 double obs_low[nobshist] = {400,-2.5,0,0,0,0,-2.5,0,0,0,0,-2,0,0}; 
 double obs_up[nobshist] = {3100,2.5,300,1,1,300,2.5,1,1,1,2.5,4.5,1,1}; 
 int obs_nbins[nobshist] = {25,25,25,25,25,25,25,25,25,20,25,25,20,20};
 
 TH1D *hist_obs[nobshist] ;
 TH1D *hist_obs_1[nobshist] ;
 TH1D *hist_obs_2[nobshist] ;
  
  float DAK8_topcut = 0.470 ;//1% mistag rate (0.920 // 0.1% mistag) (0.802 // 1% mistag )
  float deep_btag_cut = 0.2770; //medium (0.7264 //tight)
  float re_cut = 0.93;
  
  TProofOutputFile *OutFile;
  TFile *fileOut;
   
  TTree *Tout ;

  TH1D *hist_npv;
  TH1D *hist_npv_final;
  TH1D *hist_npu;
  
  float in_pfjetAK8NHadF;
  float in_pfjetAK8neunhadfrac;
  float in_pfjetAK8subhaddiff;
  float in_pfjetAK8tau21;
  float in_pfjetAK8chrad;
  float in_pfjetAK8sdmass;
  float in_pfjetAK8eldxy_sv;
  float in_pfjetAK8matchedelcleta;
  float in_pfjetAK8matchedelpt;
  float in_pfjetAK8matchedelsigmaieta;
  float in_pfjetAK8matchedelsigmaiphi;
  float in_pfjetAK8matchedelr9full;
  float in_pfjetAK8matchedelsupcl_etaw;
  float in_pfjetAK8matchedelsupcl_phiw;
  float in_pfjetAK8matchedelhcaloverecal;
  float in_pfjetAK8matchedelcloctftrkn;
  float in_pfjetAK8matchedelcloctftrkchi2;
  float in_pfjetAK8matchedele1x5bye5x5;
  float in_pfjetAK8matchedelnormchi2;
  float in_pfjetAK8matchedelhitsmiss;
  float in_pfjetAK8matchedeltrkmeasure;
  float in_pfjetAK8matchedelecloverpout;
  float in_pfjetAK8matchedelecaletrkmomentum;
  float in_pfjetAK8matchedeldeltaetacltrkcalo;
  float in_pfjetAK8matchedelsupcl_preshvsrawe;
  float in_pfjetAK8matchedelpfisolsumphet;
  float in_pfjetAK8matchedelpfisolsumchhadpt;
  float in_pfjetAK8matchedelpfisolsumneuhadet;
  float in_pfjetAK8matchedeletain;
  float in_pfjetAK8matchedelphiin;
  float in_pfjetAK8matchedelfbrem;
  float in_pfjetAK8matchedeleoverp;
  float in_pfjetAK8matchedelhovere;
  float in_pfjetAK8matchedelRho;

  float in_pfjetAK8_bbyW_E;
  float in_pfjetAK8_Kfactor;
  
  TMVA::Reader *reader1;
  TMVA::Reader *reader2;

  //TString dir = "/home/chatterj/t3store/Leptop/CMSSW_10_5_0/src/V2/RealData/";
  TString dir = "/home/deroy/t3store3/CMSSW_10_5_0/src/BDTResponse_validator/Analysis/newvar_sv/Signal/";
  //TString weightfile1 = dir + TString("TMVAClassification_BDTG_re.weights.xml");
  TString weightfile1 = dir + TString("TMVAClassification_BDTG_elIDvarv3.weights.xml");
  TString weightfile2 = dir + TString("TMVAClassification_BDTG_rnu.weights.xml");
  
  float ptcut = 400;

   Anal_LeptopReco_PROOF(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Anal_LeptopReco_PROOF() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(Anal_LeptopReco_PROOF,0);
};

#endif

#ifdef Anal_LeptopReco_PROOF_cxx
void Anal_LeptopReco_PROOF::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("irun", &irun, &b_irun);
   fChain->SetBranchAddress("ilumi", &ilumi, &b_ilumi);
   fChain->SetBranchAddress("ievt", &ievt, &b_ievt);
   fChain->SetBranchAddress("nprim", &nprim, &b_nprim);
   fChain->SetBranchAddress("nvert", &nvert, &b_nvert);
   fChain->SetBranchAddress("ndofct", &ndofct, &b_ndofct);
   fChain->SetBranchAddress("nchict", &nchict, &b_nchict);
   fChain->SetBranchAddress("Rho", &Rho, &b_Rho);
   fChain->SetBranchAddress("event_weight", &event_weight, &b_event_weight);
   fChain->SetBranchAddress("qscale", &qscale, &b_qscale);
   fChain->SetBranchAddress("npu_vert", &npu_vert, &b_npu_vert);
   fChain->SetBranchAddress("trig_value", &trig_value, &b_trig_value);
   fChain->SetBranchAddress("ihlt01", &ihlt01, &b_ihlt01);
   fChain->SetBranchAddress("ihlt02", &ihlt02, &b_ihlt02);
   fChain->SetBranchAddress("ihlt03", &ihlt03, &b_ihlt03);
   fChain->SetBranchAddress("ihlt04", &ihlt04, &b_ihlt04);
   fChain->SetBranchAddress("ihlt05", &ihlt05, &b_ihlt05);
   fChain->SetBranchAddress("ihlt06", &ihlt06, &b_ihlt06);
   fChain->SetBranchAddress("ihlt07", &ihlt07, &b_ihlt07);
   fChain->SetBranchAddress("ihlt08", &ihlt08, &b_ihlt08);
   fChain->SetBranchAddress("ihlt09", &ihlt09, &b_ihlt09);
   fChain->SetBranchAddress("ihlt10", &ihlt10, &b_ihlt10);
   fChain->SetBranchAddress("ihlt11", &ihlt11, &b_ihlt11);
   fChain->SetBranchAddress("ihlt12", &ihlt12, &b_ihlt12);
   fChain->SetBranchAddress("ihlt13", &ihlt13, &b_ihlt13);
   fChain->SetBranchAddress("ihlt14", &ihlt14, &b_ihlt14);
   fChain->SetBranchAddress("ihlt15", &ihlt15, &b_ihlt15);
   fChain->SetBranchAddress("ihlt16", &ihlt16, &b_ihlt16);
   fChain->SetBranchAddress("ihlt17", &ihlt17, &b_ihlt17);

   fChain->SetBranchAddress("prescl01", &prescl01, &b_prescl01);
   fChain->SetBranchAddress("prescl02", &prescl02, &b_prescl02);
   fChain->SetBranchAddress("prescl03", &prescl03, &b_prescl03);
   fChain->SetBranchAddress("prescl04", &prescl04, &b_prescl04);
   fChain->SetBranchAddress("prescl05", &prescl05, &b_prescl05);
   fChain->SetBranchAddress("prescl06", &prescl06, &b_prescl06);
   fChain->SetBranchAddress("prescl07", &prescl07, &b_prescl07);
   fChain->SetBranchAddress("prescl08", &prescl08, &b_prescl08);
   fChain->SetBranchAddress("prescl09", &prescl09, &b_prescl09);
   fChain->SetBranchAddress("prescl10", &prescl10, &b_prescl10);
   fChain->SetBranchAddress("prescl11", &prescl11, &b_prescl11);
   fChain->SetBranchAddress("prescl12", &prescl12, &b_prescl12);
   fChain->SetBranchAddress("prescl13", &prescl13, &b_prescl13);
   fChain->SetBranchAddress("prescl14", &prescl14, &b_prescl14);
   fChain->SetBranchAddress("prescl15", &prescl15, &b_prescl15);
   fChain->SetBranchAddress("prescl16", &prescl16, &b_prescl16);
   fChain->SetBranchAddress("prescl17", &prescl17, &b_prescl17);

   fChain->SetBranchAddress("ntrigobjs", &ntrigobjs, &b_ntrigobjs);
   fChain->SetBranchAddress("trigobjpt", trigobjpt, &b_trigobjpt);
   fChain->SetBranchAddress("trigobjeta", trigobjeta, &b_trigobjeta);
   fChain->SetBranchAddress("trigobjphi", trigobjphi, &b_trigobjphi);
   fChain->SetBranchAddress("trigobje", trigobje, &b_trigobje);
   fChain->SetBranchAddress("trigobjHLT", trigobjHLT, &b_trigobjHLT);
   fChain->SetBranchAddress("trigobjL1", trigobjL1, &b_trigobjL1);
   fChain->SetBranchAddress("trigobjBoth", trigobjBoth, &b_trigobjBoth);
   fChain->SetBranchAddress("trigobjIhlt", trigobjIhlt, &b_trigobjIhlt);
   fChain->SetBranchAddress("PFMET", &PFMET, &b_miset);
   fChain->SetBranchAddress("PFMETPhi", &PFMETPhi, &b_misphi);
   fChain->SetBranchAddress("MisEtSig", &MisEtSig, &b_misetsig);
   fChain->SetBranchAddress("sumEt", &sumEt, &b_sumEt);
   fChain->SetBranchAddress("npfjetAK8", &npfjetAK8, &b_npfjetAK8);
   fChain->SetBranchAddress("pfjetAK8looseID", pfjetAK8looseID, &b_pfjetAK8looseID);
   fChain->SetBranchAddress("pfjetAK8tightID", pfjetAK8tightID, &b_pfjetAK8tightID);
   fChain->SetBranchAddress("pfjetAK8tightLVID", pfjetAK8tightLVID, &b_pfjetAK8tightLVID);
   fChain->SetBranchAddress("pfjetAK8pt", pfjetAK8pt, &b_pfjetAK8pt);
   fChain->SetBranchAddress("pfjetAK8y", pfjetAK8y, &b_pfjetAK8y);
   fChain->SetBranchAddress("pfjetAK8phi", pfjetAK8phi, &b_pfjetAK8phi);
   fChain->SetBranchAddress("pfjetAK8mass", pfjetAK8mass, &b_pfjetAK8mass);
   fChain->SetBranchAddress("pfjetAK8JEC", pfjetAK8JEC, &b_pfjetAK8JEC);
   fChain->SetBranchAddress("pfjetAK8JECL1", pfjetAK8JECL1, &b_pfjetAK8JECL1);
   fChain->SetBranchAddress("pfjetAK8JECL2", pfjetAK8JECL2, &b_pfjetAK8JECL2);
   fChain->SetBranchAddress("pfjetAK8JECL3", pfjetAK8JECL3, &b_pfjetAK8JECL3);
   fChain->SetBranchAddress("pfjetAK8JECL2L3", pfjetAK8JECL2L3, &b_pfjetAK8JECL2L3);
   fChain->SetBranchAddress("pfjetAK8btag_CMVA", pfjetAK8btag_CMVA, &b_pfjetAK8btag_CMVA);
   fChain->SetBranchAddress("pfjetAK8btag_CSV", pfjetAK8btag_CSV, &b_pfjetAK8btag_CSV);
   fChain->SetBranchAddress("pfjetAK8btag_DeepCSV", pfjetAK8btag_DeepCSV, &b_pfjetAK8btag_DeepCSV);
   fChain->SetBranchAddress("pfjetAK8btag_DeepFlav", pfjetAK8btag_DeepFlav, &b_pfjetAK8btag_DeepFlav);
   fChain->SetBranchAddress("pfjetAK8DeepTag_TvsQCD", pfjetAK8DeepTag_TvsQCD, &b_pfjetAK8DeepTag_TvsQCD);
   fChain->SetBranchAddress("pfjetAK8DeepTag_WvsQCD", pfjetAK8DeepTag_WvsQCD, &b_pfjetAK8DeepTag_WvsQCD);
   fChain->SetBranchAddress("pfjetAK8DeepTag_ZvsQCD", pfjetAK8DeepTag_ZvsQCD, &b_pfjetAK8DeepTag_ZvsQCD);
   fChain->SetBranchAddress("pfjetAK8DeepTag_BBvsQCD", pfjetAK8DeepTag_BBvsQCD, &b_pfjetAK8DeepTag_BBvsQCD);
   fChain->SetBranchAddress("pfjetAK8DeepTag_CCvsQCD", pfjetAK8DeepTag_CCvsQCD, &b_pfjetAK8DeepTag_CCvsQCD);
   fChain->SetBranchAddress("pfjetAK8CHF", pfjetAK8CHF, &b_pfjetAK8CHF);
   fChain->SetBranchAddress("pfjetAK8NHF", pfjetAK8NHF, &b_pfjetAK8NHF);
   fChain->SetBranchAddress("pfjetAK8CEMF", pfjetAK8CEMF, &b_pfjetAK8CEMF);
   fChain->SetBranchAddress("pfjetAK8NEMF", pfjetAK8NEMF, &b_pfjetAK8NEMF);
   fChain->SetBranchAddress("pfjetAK8MUF", pfjetAK8MUF, &b_pfjetAK8MUF);
   fChain->SetBranchAddress("pfjetAK8PHF", pfjetAK8PHF, &b_pfjetAK8PHF);
   fChain->SetBranchAddress("pfjetAK8EEF", pfjetAK8EEF, &b_pfjetAK8EEF);
   fChain->SetBranchAddress("pfjetAK8HFHF", pfjetAK8HFHF, &b_pfjetAK8HFHF);
   fChain->SetBranchAddress("pfjetAK8HFEMF", pfjetAK8HFEMF, &b_pfjetAK8HFEMF);
   fChain->SetBranchAddress("pfjetAK8HOF", pfjetAK8HOF, &b_pfjetAK8HOF);
   fChain->SetBranchAddress("pfjetAK8CHM", pfjetAK8CHM, &b_pfjetAK8CHM);
   fChain->SetBranchAddress("pfjetAK8NHM", pfjetAK8NHM, &b_pfjetAK8NHM);
   fChain->SetBranchAddress("pfjetAK8CEMM", pfjetAK8CEMM, &b_pfjetAK8CEMM);
   fChain->SetBranchAddress("pfjetAK8NEMM", pfjetAK8NEMM, &b_pfjetAK8NEMM);
   fChain->SetBranchAddress("pfjetAK8MUM", pfjetAK8MUM, &b_pfjetAK8MUM);
   fChain->SetBranchAddress("pfjetAK8PHM", pfjetAK8PHM, &b_pfjetAK8PHM);
   fChain->SetBranchAddress("pfjetAK8EEM", pfjetAK8EEM, &b_pfjetAK8EEM);
   fChain->SetBranchAddress("pfjetAK8HFHM", pfjetAK8HFHM, &b_pfjetAK8HFHM);
   fChain->SetBranchAddress("pfjetAK8HFEMM", pfjetAK8HFEMM, &b_pfjetAK8HFEMM);
   fChain->SetBranchAddress("pfjetAK8Neucons", pfjetAK8Neucons, &b_pfjetAK8Neucons);
   fChain->SetBranchAddress("pfjetAK8Chcons", pfjetAK8Chcons, &b_pfjetAK8Chcons);
   fChain->SetBranchAddress("pfjetAK8reso", pfjetAK8reso, &b_pfjetAK8reso);
   fChain->SetBranchAddress("pfjetAK8resoup", pfjetAK8resoup, &b_pfjetAK8resoup);
   fChain->SetBranchAddress("pfjetAK8resodn", pfjetAK8resodn, &b_pfjetAK8resodn);
   fChain->SetBranchAddress("pfjetAK8jesup_pu", pfjetAK8jesup_pu, &b_pfjetAK8jesup_pu);
   fChain->SetBranchAddress("pfjetAK8jesup_rel", pfjetAK8jesup_rel, &b_pfjetAK8jesup_rel);
   fChain->SetBranchAddress("pfjetAK8jesup_scale", pfjetAK8jesup_scale, &b_pfjetAK8jesup_scale);
   fChain->SetBranchAddress("pfjetAK8jesup_total", pfjetAK8jesup_total, &b_pfjetAK8jesup_total);
   fChain->SetBranchAddress("pfjetAK8jesdn_pu", pfjetAK8jesdn_pu, &b_pfjetAK8jesdn_pu);
   fChain->SetBranchAddress("pfjetAK8jesdn_rel", pfjetAK8jesdn_rel, &b_pfjetAK8jesdn_rel);
   fChain->SetBranchAddress("pfjetAK8jesdn_scale", pfjetAK8jesdn_scale, &b_pfjetAK8jesdn_scale);
   fChain->SetBranchAddress("pfjetAK8jesdn_total", pfjetAK8jesdn_total, &b_pfjetAK8jesdn_total);
   fChain->SetBranchAddress("pfjetAK8chrad", pfjetAK8chrad, &b_pfjetAK8chrad);
   fChain->SetBranchAddress("pfjetAK8axis2", pfjetAK8axis2, &b_pfjetAK8axis2);
   fChain->SetBranchAddress("pfjetAK8pTD", pfjetAK8pTD, &b_pfjetAK8pTD);
   fChain->SetBranchAddress("pfjetAK8sdmass", pfjetAK8sdmass, &b_pfjetAK8sdmass);
   fChain->SetBranchAddress("pfjetAK8elsubjptrat", pfjetAK8elsubjptrat, &b_pfjetAK8elsubjptrat);
   fChain->SetBranchAddress("pfjetAK8tau1", pfjetAK8tau1, &b_pfjetAK8tau1);
   fChain->SetBranchAddress("pfjetAK8tau2", pfjetAK8tau2, &b_pfjetAK8tau2);
   fChain->SetBranchAddress("pfjetAK8tau3", pfjetAK8tau3, &b_pfjetAK8tau3);
   fChain->SetBranchAddress("pfjetAK8sub1pt", pfjetAK8sub1pt, &b_pfjetAK8sub1pt);
   fChain->SetBranchAddress("pfjetAK8sub1eta", pfjetAK8sub1eta, &b_pfjetAK8sub1eta);
   fChain->SetBranchAddress("pfjetAK8sub1phi", pfjetAK8sub1phi, &b_pfjetAK8sub1phi);
   fChain->SetBranchAddress("pfjetAK8sub1mass", pfjetAK8sub1mass, &b_pfjetAK8sub1mass);
   fChain->SetBranchAddress("pfjetAK8sub1btag", pfjetAK8sub1btag, &b_pfjetAK8sub1btag);
   fChain->SetBranchAddress("pfjetAK8sub1chhadfrac", pfjetAK8sub1chhadfrac, &b_pfjetAK8sub1chhadfrac);
   fChain->SetBranchAddress("pfjetAK8sub1neuhadfrac", pfjetAK8sub1neuhadfrac, &b_pfjetAK8sub1neuhadfrac);
   fChain->SetBranchAddress("pfjetAK8sub1emfrac", pfjetAK8sub1emfrac, &b_pfjetAK8sub1emfrac);
   fChain->SetBranchAddress("pfjetAK8sub1phofrac", pfjetAK8sub1phofrac, &b_pfjetAK8sub1phofrac);
   fChain->SetBranchAddress("pfjetAK8sub1mufrac", pfjetAK8sub1mufrac, &b_pfjetAK8sub1mufrac);
   fChain->SetBranchAddress("pfjetAK8sub2pt", pfjetAK8sub2pt, &b_pfjetAK8sub2pt);
   fChain->SetBranchAddress("pfjetAK8sub2eta", pfjetAK8sub2eta, &b_pfjetAK8sub2eta);
   fChain->SetBranchAddress("pfjetAK8sub2phi", pfjetAK8sub2phi, &b_pfjetAK8sub2phi);
   fChain->SetBranchAddress("pfjetAK8sub2mass", pfjetAK8sub2mass, &b_pfjetAK8sub2mass);
   fChain->SetBranchAddress("pfjetAK8sub2btag", pfjetAK8sub2btag, &b_pfjetAK8sub2btag);
   fChain->SetBranchAddress("pfjetAK8sub2chhadfrac", pfjetAK8sub2chhadfrac, &b_pfjetAK8sub2chhadfrac);
   fChain->SetBranchAddress("pfjetAK8sub2neuhadfrac", pfjetAK8sub2neuhadfrac, &b_pfjetAK8sub2neuhadfrac);
   fChain->SetBranchAddress("pfjetAK8sub2emfrac", pfjetAK8sub2emfrac, &b_pfjetAK8sub2emfrac);
   fChain->SetBranchAddress("pfjetAK8sub2phofrac", pfjetAK8sub2phofrac, &b_pfjetAK8sub2phofrac);
   fChain->SetBranchAddress("pfjetAK8sub2mufrac", pfjetAK8sub2mufrac, &b_pfjetAK8sub2mufrac);
   fChain->SetBranchAddress("pfjetAK8_leppt", pfjetAK8_leppt, &b_pfjetAK8_leppt);
   fChain->SetBranchAddress("pfjetAK8_lepeta", pfjetAK8_lepeta, &b_pfjetAK8_lepeta);
   fChain->SetBranchAddress("pfjetAK8_lepphi", pfjetAK8_lepphi, &b_pfjetAK8_lepphi);
   fChain->SetBranchAddress("pfjetAK8_lepe", pfjetAK8_lepe, &b_pfjetAK8_lepe);
   fChain->SetBranchAddress("pfjetAK8_bpt", pfjetAK8_bpt, &b_pfjetAK8_bpt);
   fChain->SetBranchAddress("pfjetAK8_beta", pfjetAK8_beta, &b_pfjetAK8_beta);
   fChain->SetBranchAddress("pfjetAK8_bphi", pfjetAK8_bphi, &b_pfjetAK8_bphi);
   fChain->SetBranchAddress("pfjetAK8_be", pfjetAK8_be, &b_pfjetAK8_be);
   fChain->SetBranchAddress("pfjetAK8_nupt", pfjetAK8_nupt, &b_pfjetAK8_nupt);
   fChain->SetBranchAddress("pfjetAK8_nueta", pfjetAK8_nueta, &b_pfjetAK8_nueta);
   fChain->SetBranchAddress("pfjetAK8_nuphi", pfjetAK8_nuphi, &b_pfjetAK8_nuphi);
   fChain->SetBranchAddress("pfjetAK8_nue", pfjetAK8_nue, &b_pfjetAK8_nue);
   fChain->SetBranchAddress("pfjetAK8_bbyW_E", pfjetAK8_bbyW_E, &b_pfjetAK8_bbyW_E);
   fChain->SetBranchAddress("pfjetAK8_Kfactor", pfjetAK8_Kfactor, &b_pfjetAK8_Kfactor);
   fChain->SetBranchAddress("pfjetAK8_Rnew", pfjetAK8_Rnew, &b_pfjetAK8_Rnew);

   fChain->SetBranchAddress("pfjetAK8elinsubpt", pfjetAK8elinsubpt, &b_pfjetAK8elinsubpt);
   fChain->SetBranchAddress("pfjetAK8elinsubeta", pfjetAK8elinsubeta, &b_pfjetAK8elinsubeta);
   fChain->SetBranchAddress("pfjetAK8elinsubphi", pfjetAK8elinsubphi, &b_pfjetAK8elinsubphi);
   fChain->SetBranchAddress("pfjetAK8elinsube", pfjetAK8elinsube, &b_pfjetAK8elinsube);
   fChain->SetBranchAddress("pfjetAK8elinsubmass", pfjetAK8elinsubmass, &b_pfjetAK8elinsubmass);

   fChain->SetBranchAddress("pfjetAK8elinsubjpt", pfjetAK8elinsubjpt, &b_pfjetAK8elinsubjpt);
   fChain->SetBranchAddress("pfjetAK8elinsubjeta", pfjetAK8elinsubjeta, &b_pfjetAK8elinsubjeta);
   fChain->SetBranchAddress("pfjetAK8elinsubjphi", pfjetAK8elinsubjphi, &b_pfjetAK8elinsubjphi);
   fChain->SetBranchAddress("pfjetAK8elinsubje", pfjetAK8elinsubje, &b_pfjetAK8elinsubje);
   fChain->SetBranchAddress("pfjetAK8elinsubjmass", pfjetAK8elinsubjmass, &b_pfjetAK8elinsubjmass);

   fChain->SetBranchAddress("npfjetAK4", &npfjetAK4, &b_npfjetAK4);
   fChain->SetBranchAddress("pfjetAK4looseID", pfjetAK4looseID, &b_pfjetAK4looseID);
   fChain->SetBranchAddress("pfjetAK4tightID", pfjetAK4tightID, &b_pfjetAK4tightID);
   fChain->SetBranchAddress("pfjetAK4tightLVID", pfjetAK4tightLVID, &b_pfjetAK4tightLVID);
   fChain->SetBranchAddress("pfjetAK4pt", pfjetAK4pt, &b_pfjetAK4pt);
   fChain->SetBranchAddress("pfjetAK4eta", pfjetAK4eta, &b_pfjetAK4eta);
   fChain->SetBranchAddress("pfjetAK4y", pfjetAK4y, &b_pfjetAK4y);
   fChain->SetBranchAddress("pfjetAK4phi", pfjetAK4phi, &b_pfjetAK4phi);
   fChain->SetBranchAddress("pfjetAK4mass", pfjetAK4mass, &b_pfjetAK4mass);
   fChain->SetBranchAddress("pfjetAK4JEC", pfjetAK4JEC, &b_pfjetAK4JEC);
   fChain->SetBranchAddress("pfjetAK4JECL1", pfjetAK4JECL1, &b_pfjetAK4JECL1);
   fChain->SetBranchAddress("pfjetAK4JECL2", pfjetAK4JECL2, &b_pfjetAK4JECL2);
   fChain->SetBranchAddress("pfjetAK4JECL3", pfjetAK4JECL3, &b_pfjetAK4JECL3);
   fChain->SetBranchAddress("pfjetAK4JECL2L3", pfjetAK4JECL2L3, &b_pfjetAK4JECL2L3);
   fChain->SetBranchAddress("pfjetAK4btag_CMVA", pfjetAK4btag_CMVA, &b_pfjetAK4btag_CMVA);
   fChain->SetBranchAddress("pfjetAK4btag_CSV", pfjetAK4btag_CSV, &b_pfjetAK4btag_CSV);
   fChain->SetBranchAddress("pfjetAK4btag_DeepCSV", pfjetAK4btag_DeepCSV, &b_pfjetAK4btag_DeepCSV);
   fChain->SetBranchAddress("pfjetAK4btag_DeepFlav", pfjetAK4btag_DeepFlav, &b_pfjetAK4btag_DeepFlav);
   fChain->SetBranchAddress("pfjetAK4btag_DeepQCD", pfjetAK4btag_DeepQCD, &b_pfjetAK4btag_DeepQCD);
   fChain->SetBranchAddress("pfjetAK4reso", pfjetAK4reso, &b_pfjetAK4reso);
   fChain->SetBranchAddress("pfjetAK4resoup", pfjetAK4resoup, &b_pfjetAK4resoup);
   fChain->SetBranchAddress("pfjetAK4resodn", pfjetAK4resodn, &b_pfjetAK4resodn);
   fChain->SetBranchAddress("pfjetAK4jesup_pu", pfjetAK4jesup_pu, &b_pfjetAK4jesup_pu);
   fChain->SetBranchAddress("pfjetAK4jesup_rel", pfjetAK4jesup_rel, &b_pfjetAK4jesup_rel);
   fChain->SetBranchAddress("pfjetAK4jesup_scale", pfjetAK4jesup_scale, &b_pfjetAK4jesup_scale);
   fChain->SetBranchAddress("pfjetAK4jesup_total", pfjetAK4jesup_total, &b_pfjetAK4jesup_total);
   fChain->SetBranchAddress("pfjetAK4jesdn_pu", pfjetAK4jesdn_pu, &b_pfjetAK4jesdn_pu);
   fChain->SetBranchAddress("pfjetAK4jesdn_rel", pfjetAK4jesdn_rel, &b_pfjetAK4jesdn_rel);
   fChain->SetBranchAddress("pfjetAK4jesdn_scale", pfjetAK4jesdn_scale, &b_pfjetAK4jesdn_scale);
   fChain->SetBranchAddress("pfjetAK4jesdn_total", pfjetAK4jesdn_total, &b_pfjetAK4jesdn_total);
   fChain->SetBranchAddress("pfjetAK4hadronflav", pfjetAK4hadronflav, &b_pfjetAK4hadronflav);
   fChain->SetBranchAddress("pfjetAK4partonflav", pfjetAK4partonflav, &b_pfjetAK4partonflav);
   fChain->SetBranchAddress("pfjetAK4qgl", pfjetAK4qgl, &b_pfjetAK4qgl);
   fChain->SetBranchAddress("pfjetAK4PUID", pfjetAK4PUID, &b_pfjetAK4PUID);
   fChain->SetBranchAddress("pfjetAK4GenMatch", &pfjetAK4GenMatch, &b_pfjetAK4GenMatch);
   fChain->SetBranchAddress("GENMET", &GENMET, &b_genmiset);
   fChain->SetBranchAddress("GENMETPhi", &GENMETPhi, &b_genmisphi);
   fChain->SetBranchAddress("GENMETSig", &GENMETSig, &b_genmisetsig);
   fChain->SetBranchAddress("ngenjetAK8", &ngenjetAK8, &b_ngenjetAK8);
   fChain->SetBranchAddress("genjetAK8pt", genjetAK8pt, &b_genjetAK8pt);
   fChain->SetBranchAddress("genjetAK8y", genjetAK8y, &b_genjetAK8y);
   fChain->SetBranchAddress("genjetAK8phi", genjetAK8phi, &b_genjetAK8phi);
   fChain->SetBranchAddress("genjetAK8mass", genjetAK8mass, &b_genjetAK8mass);
   fChain->SetBranchAddress("genjetAK8sdmass", genjetAK8sdmass, &b_genjetAK8sdmass);
   fChain->SetBranchAddress("genjetAK8btag", genjetAK8btag, &b_genjetAK8btag);
   fChain->SetBranchAddress("genjetAK8tau1", genjetAK8tau1, &b_genjetAK8tau1);
   fChain->SetBranchAddress("genjetAK8tau2", genjetAK8tau2, &b_genjetAK8tau2);
   fChain->SetBranchAddress("genjetAK8tau3", genjetAK8tau3, &b_genjetAK8tau3);
   fChain->SetBranchAddress("genjetAK8chrad", genjetAK8chrad, &b_genjetAK8chrad);
   fChain->SetBranchAddress("genjetAK8sub1pt", genjetAK8sub1pt, &b_genjetAK8sub1pt);
   fChain->SetBranchAddress("genjetAK8sub1y", genjetAK8sub1y, &b_genjetAK8sub1y);
   fChain->SetBranchAddress("genjetAK8sub1phi", genjetAK8sub1phi, &b_genjetAK8sub1phi);
   fChain->SetBranchAddress("genjetAK8sub1mass", genjetAK8sub1mass, &b_genjetAK8sub1mass);
   fChain->SetBranchAddress("genjetAK8sub1hadfrac", genjetAK8sub1hadfrac, &b_genjetAK8sub1hadfrac);
   fChain->SetBranchAddress("genjetAK8sub1emfrac", genjetAK8sub1emfrac, &b_genjetAK8sub1emfrac);
   fChain->SetBranchAddress("genjetAK8sub2pt", genjetAK8sub2pt, &b_genjetAK8sub2pt);
   fChain->SetBranchAddress("genjetAK8sub2y", genjetAK8sub2y, &b_genjetAK8sub2y);
   fChain->SetBranchAddress("genjetAK8sub2phi", genjetAK8sub2phi, &b_genjetAK8sub2phi);
   fChain->SetBranchAddress("genjetAK8sub2mass", genjetAK8sub2mass, &b_genjetAK8sub2mass);
   fChain->SetBranchAddress("genjetAK8sub2hadfrac", genjetAK8sub2hadfrac, &b_genjetAK8sub2hadfrac);
   fChain->SetBranchAddress("genjetAK8sub2emfrac", genjetAK8sub2emfrac, &b_genjetAK8sub2emfrac);
   fChain->SetBranchAddress("ngenjetAK4", &ngenjetAK4, &b_ngenjetAK4);
   fChain->SetBranchAddress("genjetAK4pt", genjetAK4pt, &b_genjetAK4pt);
   fChain->SetBranchAddress("genjetAK4y", genjetAK4y, &b_genjetAK4y);
   fChain->SetBranchAddress("genjetAK4phi", genjetAK4phi, &b_genjetAK4phi);
   fChain->SetBranchAddress("genjetAK4mass", genjetAK4mass, &b_genjetAK4mass);
   fChain->SetBranchAddress("genjetAK4btag", genjetAK4btag, &b_genjetAK4btag);
   fChain->SetBranchAddress("ngenparticles", &ngenparticles, &b_ngenparticles);
   fChain->SetBranchAddress("genpartstatus", genpartstatus, &b_genpartstatus);
   fChain->SetBranchAddress("genpartpdg", genpartpdg, &b_genpartpdg);
   fChain->SetBranchAddress("genpartmompdg", genpartmompdg, &b_genpartmompdg);
   fChain->SetBranchAddress("genpartdaugno", genpartdaugno, &b_genpartdaugno);
   fChain->SetBranchAddress("genpartfromhard", genpartfromhard, &b_genpartfromhard);
   fChain->SetBranchAddress("genpartfromhardbFSR", genpartfromhardbFSR, &b_genpartfromhardbFSR);
   fChain->SetBranchAddress("genpartpt", genpartpt, &b_genpartpt);
   fChain->SetBranchAddress("genparteta", genparteta, &b_genparteta);
   fChain->SetBranchAddress("genpartphi", genpartphi, &b_genpartphi);
   fChain->SetBranchAddress("genpartm", genpartm, &b_genpartm);
   fChain->SetBranchAddress("genpartq", genpartq, &b_genpartq);
   fChain->SetBranchAddress("nmuons", &nmuons, &b_nmuons);
   fChain->SetBranchAddress("muonisPF", muonisPF, &b_muonisPF);
   fChain->SetBranchAddress("muonisGL", muonisGL, &b_muonisGL);
   fChain->SetBranchAddress("muonisTRK", muonisTRK, &b_muonisTRK);
   fChain->SetBranchAddress("muonisLoose", muonisLoose, &b_muonisLoose);
   fChain->SetBranchAddress("muonisGoodGL", muonisGoodGL, &b_muonisGoodGL);
   fChain->SetBranchAddress("muonisMed", muonisMed, &b_muonisMed);
   fChain->SetBranchAddress("muonpt", muonpt, &b_muonpt);
   fChain->SetBranchAddress("muonp", muonp, &b_muonp);
   fChain->SetBranchAddress("muone", muone, &b_muone);
   fChain->SetBranchAddress("muoneta", muoneta, &b_muoneta);
   fChain->SetBranchAddress("muonphi", muonphi, &b_muonphi);
   fChain->SetBranchAddress("muondrbm", muondrbm, &b_muondrbm);
   fChain->SetBranchAddress("muontrkvtx", muontrkvtx, &b_muontrkvtx);
   fChain->SetBranchAddress("muondz", muondz, &b_muondz);
   fChain->SetBranchAddress("muonpter", muonpter, &b_muonpter);
   fChain->SetBranchAddress("muonchi", muonchi, &b_muonchi);
   fChain->SetBranchAddress("muonndf", muonndf, &b_muonndf);
   fChain->SetBranchAddress("muonecal", muonecal, &b_muonecal);
   fChain->SetBranchAddress("muonhcal", muonhcal, &b_muonhcal);
   fChain->SetBranchAddress("muonemiso", muonemiso, &b_muonemiso);
   fChain->SetBranchAddress("muonhadiso", muonhadiso, &b_muonhadiso);
   fChain->SetBranchAddress("muonpfiso", muonpfiso, &b_muonpfiso);
   fChain->SetBranchAddress("muontkpt03", muontkpt03, &b_muontkpt03);
   fChain->SetBranchAddress("muontkpt05", muontkpt05, &b_muontkpt05);
   fChain->SetBranchAddress("muonposmatch", muonposmatch, &b_muonposmatch);
   fChain->SetBranchAddress("muontrkink", muontrkink, &b_muontrkink);
   fChain->SetBranchAddress("muonsegcom", muonsegcom, &b_muonsegcom);
   fChain->SetBranchAddress("muonthit", muonthit, &b_muonthit);
   fChain->SetBranchAddress("muonpixhit", muonpixhit, &b_muonpixhit);
   fChain->SetBranchAddress("muonmst", muonmst, &b_muonmst);
   fChain->SetBranchAddress("muontrklay", muontrklay, &b_muontrklay);
   fChain->SetBranchAddress("muonvalfrac", muonvalfrac, &b_muonvalfrac);
   fChain->SetBranchAddress("nelecs", &nelecs, &b_nelecs);
   fChain->SetBranchAddress("elpt", elpt, &b_elpt);
   fChain->SetBranchAddress("eldxy_sv", eldxy_sv, &b_eldxy_sv);
   fChain->SetBranchAddress("eleta", eleta, &b_eleta);
   fChain->SetBranchAddress("elphi", elphi, &b_elphi);
   fChain->SetBranchAddress("elp", elp, &b_elp);
   fChain->SetBranchAddress("ele", ele, &b_ele);
   fChain->SetBranchAddress("elmvaid", elmvaid, &b_elmvaid);
   fChain->SetBranchAddress("elmvaid_noIso", elmvaid_noIso, &b_elmvaid_noIso);
   fChain->SetBranchAddress("eldxy", eldxy, &b_eldxy);
   fChain->SetBranchAddress("eldz", eldz, &b_eldz);
   fChain->SetBranchAddress("elhovere", elhovere, &b_elhovere);
   fChain->SetBranchAddress("elchi", elchi, &b_elchi);
   fChain->SetBranchAddress("elndf", elndf, &b_elndf);
   fChain->SetBranchAddress("eltkpt03", eltkpt03, &b_eltkpt03);
   fChain->SetBranchAddress("eltkpt04", eltkpt04, &b_eltkpt04);
   fChain->SetBranchAddress("elemiso04", elemiso04, &b_elemiso04);
   fChain->SetBranchAddress("elhadiso04", elhadiso04, &b_elhadiso04);
   fChain->SetBranchAddress("eletain", eletain, &b_eletain);
   fChain->SetBranchAddress("elphiin", elphiin, &b_elphiin);
   fChain->SetBranchAddress("elsceta", elsceta, &b_elsceta);
   fChain->SetBranchAddress("elsupcl_eta", elsupcl_eta, &b_elsupcl_eta);
   fChain->SetBranchAddress("elsupcl_phi", elsupcl_phi, &b_elsupcl_phi);
   fChain->SetBranchAddress("elsupcl_rawE", elsupcl_rawE, &b_elsupcl_rawE);
   fChain->SetBranchAddress("elfbrem", elfbrem, &b_elfbrem);
   fChain->SetBranchAddress("elhadisodepth03", elhadisodepth03, &b_elhadisodepth03);
   fChain->SetBranchAddress("eleoverp", eleoverp, &b_eleoverp);
   fChain->SetBranchAddress("elietaieta", elietaieta, &b_elietaieta);
   fChain->SetBranchAddress("elmisshits", elmisshits, &b_elmisshits);
   fChain->SetBranchAddress("elchhadiso", elchhadiso, &b_elchhadiso);
   fChain->SetBranchAddress("elneuhadiso", elneuhadiso, &b_elneuhadiso);
   fChain->SetBranchAddress("elphoiso", elphoiso, &b_elphoiso);
   fChain->SetBranchAddress("elpuchhadiso", elpuchhadiso, &b_elpuchhadiso);
   fChain->SetBranchAddress("elpfiso", elpfiso, &b_elpfiso);
   fChain->SetBranchAddress("elconvdist", elconvdist, &b_elconvdist);
   fChain->SetBranchAddress("elconvdoct", elconvdoct, &b_elconvdoct);
   
   fChain->SetBranchAddress("elsigmaieta", elsigmaieta, &b_elsigmaieta);
   fChain->SetBranchAddress("elsigmaiphi", elsigmaiphi, &b_elsigmaiphi);
   fChain->SetBranchAddress("elr9full", elr9full, &b_elr9full);
   fChain->SetBranchAddress("elsupcl_etaw", elsupcl_etaw, &b_elsupcl_etaw); 
   fChain->SetBranchAddress("elsupcl_phiw", elsupcl_phiw, &b_elsupcl_phiw);
   fChain->SetBranchAddress("elhcaloverecal", elhcaloverecal, &b_elhcaloverecal);
   fChain->SetBranchAddress("elcloctftrkn",  elcloctftrkn, &b_elcloctftrkn);
   fChain->SetBranchAddress("elcloctftrkchi2", elcloctftrkchi2, &b_elcloctftrkchi2);
   fChain->SetBranchAddress("ele1x5bye5x5", ele1x5bye5x5, &b_ele1x5bye5x5);
   fChain->SetBranchAddress("elnormchi2", elnormchi2, &b_elnormchi2);
   fChain->SetBranchAddress("elhitsmiss", elhitsmiss, &b_elhitsmiss);
   fChain->SetBranchAddress("eltrkmeasure", eltrkmeasure, &b_eltrkmeasure);
   fChain->SetBranchAddress("elconvtxprob", elconvtxprob, &b_elconvtxprob);
   fChain->SetBranchAddress("elecloverpout", elecloverpout, &b_elecloverpout);
   fChain->SetBranchAddress("elecaletrkmomentum", elecaletrkmomentum, &b_elecaletrkmomentum);
   fChain->SetBranchAddress("eldeltaetacltrkcalo", eldeltaetacltrkcalo, &b_eldeltaetacltrkcalo);
   fChain->SetBranchAddress("elsupcl_preshvsrawe", elsupcl_preshvsrawe, &b_elsupcl_preshvsrawe);
   fChain->SetBranchAddress("elpfisolsumphet", elpfisolsumphet, &b_elpfisolsumphet);
   fChain->SetBranchAddress("elpfisolsumchhadpt", elpfisolsumchhadpt, &b_elpfisolsumchhadpt);
   fChain->SetBranchAddress("elpfsiolsumneuhadet", elpfsiolsumneuhadet, &b_elpfsiolsumneuhadet);

   fChain->SetBranchAddress("nphotons", &nphotons, &b_nphotons);
   fChain->SetBranchAddress("phoe", phoe, &b_phoe);
   fChain->SetBranchAddress("phoeta", phoeta, &b_phoeta);
   fChain->SetBranchAddress("phophi", phophi, &b_phophi);
   fChain->SetBranchAddress("phomvaid", phomvaid, &b_phomvaid);
   fChain->SetBranchAddress("phoe1by9", phoe1by9, &b_phoe1by9);
   fChain->SetBranchAddress("phoe9by25", phoe9by25, &b_phoe9by25);
   fChain->SetBranchAddress("photrkiso", photrkiso, &b_photrkiso);
   fChain->SetBranchAddress("phoemiso", phoemiso, &b_phoemiso);
   fChain->SetBranchAddress("phohadiso", phohadiso, &b_phohadiso);
   fChain->SetBranchAddress("phochhadiso", phochhadiso, &b_phochhadiso);
   fChain->SetBranchAddress("phoneuhadiso", phoneuhadiso, &b_phoneuhadiso);
   fChain->SetBranchAddress("phophoiso", phophoiso, &b_phophoiso);
   fChain->SetBranchAddress("phoPUiso", phoPUiso, &b_phoPUiso);
   fChain->SetBranchAddress("phohadbyem", phohadbyem, &b_phohadbyem);
   fChain->SetBranchAddress("phoietaieta", phoietaieta, &b_phoietaieta);
}

Bool_t Anal_LeptopReco_PROOF::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Anal_LeptopReco_PROOF_cxx
