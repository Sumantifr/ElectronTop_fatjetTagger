#include "TROOT.h"
#include "TChain.h"
#include "TProof.h"
#include "TProofServ.h"
#include "TSystem.h"
#include "boost/config.hpp"
#include "boost/lexical_cast.hpp"
using namespace boost;

void runAll(){

 TProof *plite = TProof::Open("");

 char datafile[100];
// TChain *fChain = new TChain("ttDM__noSyst");
 TChain *fChain = new TChain("T1");

 char rootfiles[100];
 //sprintf(rootfiles,"QCD_HT1000to1500_1.log");
 sprintf(rootfiles,"Data2018A_0000_EL.log"); 

 ifstream file_db;
 file_db.open(rootfiles); 

 while(!(file_db.eof())){
   file_db >> datafile;
   cout <<"datafile name is "<<datafile<<endl;
   if (strstr(datafile,"#")) continue;
    
   if(file_db.eof()) break;
    
   fChain->Add(datafile);
   cout<<"Added "<<datafile<<endl;
   }

  std::cout<<"Entries:" << fChain->GetEntries()<<std::endl;
  
  fChain->SetProof();
  fChain->Process("Anal_Leptop_PROOF.C+");
  fChain->SetProof(0);
  gSystem->Exit(0);
}
