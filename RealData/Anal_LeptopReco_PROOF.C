#define Anal_LeptopReco_PROOF_cxx
#include "Anal_LeptopReco_PROOF.h"
#include <TH2.h>
#include <TStyle.h>

#define E_Jets_TTBar

void Anal_LeptopReco_PROOF::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TString option = GetOption();
}

void Anal_LeptopReco_PROOF::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  TString option = GetOption();
  //OutFile = new TProofOutputFile("testHadronic_elid_notallevtsv4.root");
  OutFile = new TProofOutputFile("testData.root");

  //fOutput->Add(OutFile);
  fileOut = OutFile->OpenFile("RECREATE");
  if ( !(fileOut = OutFile->OpenFile("RECREATE")) )
    {
      Warning("SlaveBegin", "problems opening file: %s/%s",
	      OutFile->GetDir(), OutFile->GetFileName());
    }
  
  isMC = false;
  Tout = new TTree("leptop","leptop");
  Tout->Branch("event_pt_weight",&event_pt_weight,"event_pt_weight/F");
  Tout->Branch("weight",&weight,"weight/F");
  
  char name[1000];
  for(int ihist=0; ihist<nobshist; ihist++){
    sprintf(name,"Obs_%s",obsnames[ihist]);
    hist_obs[ihist] = new TH1D(name,name,obs_nbins[ihist],obs_low[ihist],obs_up[ihist]);
    hist_obs[ihist]->Sumw2();
    
    sprintf(name,"Obs_%s_pass",obsnames[ihist]);
    hist_obs_1[ihist] = new TH1D(name,name,obs_nbins[ihist],obs_low[ihist],obs_up[ihist]);
    hist_obs_1[ihist]->Sumw2();
    
    sprintf(name,"Obs_%s_fail",obsnames[ihist]);
    hist_obs_2[ihist] = new TH1D(name,name,obs_nbins[ihist],obs_low[ihist],obs_up[ihist]);
    hist_obs_2[ihist]->Sumw2();
  }
  
  char title[1000];
  sprintf(name,"N_PV");
  sprintf(title,"# of Primary Vertices");
  hist_npv = new TH1D(name,title,100,-0.1,99.9);//80,-0.1,79.9);
  hist_npv->Sumw2();
  
  sprintf(name,"N_PU");
  sprintf(title,"# of Pileup Vertices");
  hist_npu = new TH1D(name,title,100,0,100);//80,-0.1,79.9);
  hist_npu->Sumw2();

  sprintf(name,"Counter_event");
  hist_event_count = new TH1D(name,title,2,-0.5,1.5);
  hist_event_count->Sumw2();

  reader1 = new TMVA::Reader( "BDTG_Re" );
  reader1->AddVariable( "selpfjetAK8NHadF", &in_pfjetAK8NHadF);
  reader1->AddVariable( "selpfjetAK8neunhadfrac", &in_pfjetAK8neunhadfrac);
  reader1->AddVariable( "selpfjetAK8subhaddiff", &in_pfjetAK8subhaddiff);
  reader1->AddVariable( "selpfjetAK8tau21", &in_pfjetAK8tau21);
  reader1->AddVariable( "selpfjetAK8chrad", &in_pfjetAK8chrad);
  reader1->AddVariable( "selpfjetAK8sdmass", &in_pfjetAK8sdmass);
  reader1->AddVariable( "selpfjetAK8matchedeldxy_sv", &in_pfjetAK8eldxy_sv);
  reader1->AddVariable( "selpfjetAK8matchedelcleta", &in_pfjetAK8matchedelcleta);
  //reader1->AddVariable( "selpfjetAK8matchedelID", &in_pfjetAK8matchedelID);
  reader1->AddVariable("selpfjetAK8matchedelpt", &in_pfjetAK8matchedelpt);
  reader1->AddVariable("selpfjetAK8matchedelsigmaieta", &in_pfjetAK8matchedelsigmaieta);
  reader1->AddVariable("selpfjetAK8matchedelsigmaiphi", &in_pfjetAK8matchedelsigmaiphi);
  reader1->AddVariable("selpfjetAK8matchedelr9full", &in_pfjetAK8matchedelr9full);
  reader1->AddVariable("selpfjetAK8matchedelsupcl_etaw", &in_pfjetAK8matchedelsupcl_etaw);
  reader1->AddVariable("selpfjetAK8matchedelsupcl_phiw", &in_pfjetAK8matchedelsupcl_phiw);
  reader1->AddVariable("selpfjetAK8matchedelhcaloverecal", &in_pfjetAK8matchedelhcaloverecal);
  reader1->AddVariable("selpfjetAK8matchedelcloctftrkn", &in_pfjetAK8matchedelcloctftrkn);
  reader1->AddVariable("selpfjetAK8matchedelcloctftrkchi2", &in_pfjetAK8matchedelcloctftrkchi2);
  reader1->AddVariable("selpfjetAK8matchedele1x5bye5x5", &in_pfjetAK8matchedele1x5bye5x5);
  reader1->AddVariable("selpfjetAK8matchedelnormchi2", &in_pfjetAK8matchedelnormchi2);
  reader1->AddVariable("selpfjetAK8matchedelhitsmiss", &in_pfjetAK8matchedelhitsmiss);
  reader1->AddVariable("selpfjetAK8matchedeltrkmeasure", &in_pfjetAK8matchedeltrkmeasure);
  reader1->AddVariable("selpfjetAK8matchedelecloverpout", &in_pfjetAK8matchedelecloverpout);
  reader1->AddVariable("selpfjetAK8matchedelecaletrkmomentum", &in_pfjetAK8matchedelecaletrkmomentum);
  reader1->AddVariable("selpfjetAK8matchedeldeltaetacltrkcalo", &in_pfjetAK8matchedeldeltaetacltrkcalo);
  reader1->AddVariable("selpfjetAK8matchedelsupcl_preshvsrawe", &in_pfjetAK8matchedelsupcl_preshvsrawe);
  reader1->AddVariable("selpfjetAK8matchedelpfisolsumphet", &in_pfjetAK8matchedelpfisolsumphet);
  reader1->AddVariable("selpfjetAK8matchedelpfisolsumchhadpt", &in_pfjetAK8matchedelpfisolsumchhadpt);
  reader1->AddVariable("selpfjetAK8matchedelpfisolsumneuhadet", &in_pfjetAK8matchedelpfisolsumneuhadet);
  reader1->AddVariable("selpfjetAK8matchedeletain", &in_pfjetAK8matchedeletain);
  reader1->AddVariable("selpfjetAK8matchedelphiin", &in_pfjetAK8matchedelphiin);
  reader1->AddVariable("selpfjetAK8matchedelfbrem", &in_pfjetAK8matchedelfbrem);
  reader1->AddVariable("selpfjetAK8matchedeleoverp", &in_pfjetAK8matchedeleoverp);
  reader1->AddVariable("selpfjetAK8matchedelhovere", &in_pfjetAK8matchedelhovere);
  reader1->AddVariable("selpfjetAK8matchedelRho", &in_pfjetAK8matchedelRho);
  reader1->BookMVA("BDTG method", weightfile1);

  reader2 = new TMVA::Reader( "BDTG_Rnu" );
  reader2->AddVariable( "selpfjetAK8_bbyW_E", &in_pfjetAK8_bbyW_E);
  reader2->AddVariable( "selpfjetAK8_Kfactor", &in_pfjetAK8_Kfactor);
  reader2->BookMVA("BDTG method", weightfile2);
}

Bool_t Anal_LeptopReco_PROOF::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // It can be passed to either Anal_LeptopReco_PROOF::GetEntry() or TBranch::GetEntry()
  // to read either all or the required parts of the data. When processing
  // keyed objects with PROOF, the object is already loaded and is available
  // via the fObject pointer.
  //
  // This function should contain the "body" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.
  
  GetEntry(entry);
  if(isMC){
    weight = event_weight;
  }else{
    weight = 1;
  }
  Tout->Fill();
  
  hist_event_count->Fill(1,weight);
  
  int fjet = 0;
  for(int ijet=0; ijet<npfjetAK8; ijet++){
    if(!pfjetAK8looseID[ijet]) continue; //switch to tight ID (even tight ID calculation also do here in this code)
    
    if(fabs(pfjetAK8y[ijet])>2.5) continue;
    pfjetAK8pt[ijet] *= pfjetAK8JEC[ijet] ;
    pfjetAK8mass[ijet] *= pfjetAK8JEC[ijet];
    
    if(isMC){
      pfjetAK8pt[ijet] *= (1+pfjetAK8reso[ijet]) ;
      pfjetAK8mass[ijet] *= (1+pfjetAK8reso[ijet]) ;
      pfjetAK8sdmass[ijet] *= (1+pfjetAK8reso[ijet]) ;
    }
    
    if(pfjetAK8pt[ijet] < ptcut) continue;
    //if (pfjetAK8elinsubpt[ijet] < 0 && pfjetAK8elinsubjpt[ijet]< 0) continue;
    pfjetAK8pt[fjet] = pfjetAK8pt[ijet];
    pfjetAK8mass[fjet] = pfjetAK8mass[ijet];
    pfjetAK8y[fjet] = pfjetAK8y[ijet];
    pfjetAK8phi[fjet] = pfjetAK8phi[ijet];
    pfjetAK8chrad[fjet] = pfjetAK8chrad[ijet];
    pfjetAK8tau21[fjet] = pfjetAK8tau2[ijet]*1./pfjetAK8tau1[ijet];
    pfjetAK8tau32[fjet] = pfjetAK8tau3[ijet]*1./pfjetAK8tau2[ijet];
    pfjetAK8DeepTag_TvsQCD[fjet] = pfjetAK8DeepTag_TvsQCD[ijet];
    pfjetAK8DeepTag_WvsQCD[fjet] = pfjetAK8DeepTag_WvsQCD[ijet];
    pfjetAK8DeepTag_ZvsQCD[fjet] = pfjetAK8DeepTag_ZvsQCD[ijet];
    pfjetAK8btag_DeepCSV[fjet] = pfjetAK8btag_DeepCSV[ijet];
    pfjetAK8btag_CMVA[fjet] = pfjetAK8btag_CMVA[ijet];
    pfjetAK8CHF[fjet] = pfjetAK8CHF[ijet];
    pfjetAK8NHF[fjet] = pfjetAK8NHF[ijet];
    pfjetAK8CEMF[fjet] = pfjetAK8CEMF[ijet];
    pfjetAK8NEMF[fjet] = pfjetAK8NEMF[ijet];
    pfjetAK8MUF[fjet] = pfjetAK8MUF[ijet];
    pfjetAK8PHF[fjet] = pfjetAK8PHF[ijet];
    pfjetAK8HadF[fjet] = (pfjetAK8NHF[fjet]+pfjetAK8CHF[fjet]);
    pfjetAK8NHadF[fjet] = (1.-pfjetAK8HadF[fjet]);
    pfjetAK8EmF[fjet] = (pfjetAK8NEMF[fjet]+pfjetAK8CEMF[fjet]);
    pfjetAK8EEM[fjet] = pfjetAK8EEM[ijet];
    pfjetAK8ncons[fjet] = pfjetAK8Chcons[ijet]+pfjetAK8Chcons[ijet];
    pfjetAK8Chcons[fjet] = pfjetAK8Chcons[ijet];
    pfjetAK8neuemfrac[fjet] = (pfjetAK8NEMF[fjet]*1./pfjetAK8EmF[fjet]);
    pfjetAK8neunhadfrac[fjet] = (pfjetAK8NEMF[fjet]*1./pfjetAK8NHadF[fjet]);
    pfjetAK8sdmass[fjet] = pfjetAK8sdmass[ijet];
    pfjetAK8sub1pt[fjet] = pfjetAK8sub1pt[ijet];
    pfjetAK8sub1eta[fjet] = pfjetAK8sub1eta[ijet];
    pfjetAK8sub1phi[fjet] = pfjetAK8sub1phi[ijet];
    pfjetAK8sub1mass[fjet] = pfjetAK8sub1mass[ijet];
    pfjetAK8sub1btag[fjet] = pfjetAK8sub1btag[ijet];
    pfjetAK8sub1hadfrac[fjet] = pfjetAK8sub1chhadfrac[ijet]+pfjetAK8sub1neuhadfrac[ijet];
    pfjetAK8sub1emfrac[fjet] = pfjetAK8sub1emfrac[ijet];//pfjetAK8sub1chemfrac[ijet]+pfjetAK8sub1frac[ijet];
    pfjetAK8sub2pt[fjet] = pfjetAK8sub2pt[ijet];
    pfjetAK8sub2eta[fjet] = pfjetAK8sub2eta[ijet];
    pfjetAK8sub2phi[fjet] = pfjetAK8sub2phi[ijet];
    pfjetAK8sub2mass[fjet] = pfjetAK8sub2mass[ijet];
    pfjetAK8sub2btag[fjet] = pfjetAK8sub2btag[ijet];
    pfjetAK8sub2hadfrac[fjet] = pfjetAK8sub2chhadfrac[ijet]+pfjetAK8sub2neuhadfrac[ijet];
    pfjetAK8sub2emfrac[fjet] = pfjetAK8sub2emfrac[ijet];//pfjetAK8sub2chemfrac[ijet]+pfjetAK8sub2neuemfrac[ijet];
    pfjetAK8subbtag[fjet] = max(pfjetAK8sub1btag[fjet],pfjetAK8sub2btag[fjet]);
    pfjetAK8subhaddiff[fjet] = diff_func(pfjetAK8sub1hadfrac[fjet],pfjetAK8sub2hadfrac[fjet]);
    pfjetAK8subemdiff[fjet] = diff_func(pfjetAK8sub1emfrac[fjet],pfjetAK8sub2emfrac[fjet]);
    pfjetAK8subptdiff[fjet] = diff_func(pfjetAK8sub1pt[fjet],pfjetAK8sub2pt[fjet]);
    pfjetAK8_leppt[fjet] = pfjetAK8_leppt[ijet];
    pfjetAK8_lepeta[fjet] = pfjetAK8_lepeta[ijet];
    pfjetAK8_lepphi[fjet] = pfjetAK8_lepphi[ijet];
    pfjetAK8_lepe[fjet] = pfjetAK8_lepe[ijet];
    pfjetAK8_bpt[fjet] = pfjetAK8_bpt[ijet];
    pfjetAK8_beta[fjet] = pfjetAK8_beta[ijet];
    pfjetAK8_bphi[fjet] = pfjetAK8_bphi[ijet];
    pfjetAK8_be[fjet] = pfjetAK8_be[ijet];
    pfjetAK8_nupt[fjet] = pfjetAK8_nupt[ijet];
    pfjetAK8_nueta[fjet] = pfjetAK8_nueta[ijet];
    pfjetAK8_nuphi[fjet] = pfjetAK8_nuphi[ijet];
    pfjetAK8_nue[fjet] = pfjetAK8_nue[ijet];
    pfjetAK8_bbyW_E[fjet] = pfjetAK8_bbyW_E[ijet];
    pfjetAK8_Kfactor[fjet] = pfjetAK8_Kfactor[ijet];
    pfjetAK8_Rnew[fjet] = pfjetAK8_Rnew[ijet];
    pfjetAK8haspfelectron[fjet] = false;

    if (pfjetAK8elinsubpt[ijet] > 0. && pfjetAK8elinsubjpt[ijet]> 0.) {
      if (delta2R(pfjetAK8elinsubeta[ijet],pfjetAK8elinsubphi[ijet],pfjetAK8y[fjet],pfjetAK8phi[fjet]) < 0.8) {
	pfjetAK8haspfelectron[fjet] = true;
      }
    }

    int pfjetAK8mactAK4_i = -1;
    float minR = 0.4;
    
    for(int kjet=0; kjet<npfjetAK4; kjet++){
      if(delta2R(pfjetAK8y[fjet],pfjetAK8phi[fjet],pfjetAK4y[kjet],pfjetAK4phi[kjet])<minR){
	minR = delta2R(pfjetAK8y[fjet],pfjetAK8phi[fjet],pfjetAK4y[kjet],pfjetAK4phi[kjet]);
	pfjetAK8mactAK4_i = kjet;
      }
    }
    if(pfjetAK8mactAK4_i>=0){
      pfjetAK8matchAK4deepb[fjet] = pfjetAK4btag_DeepFlav[pfjetAK8mactAK4_i];
    }else{
      pfjetAK8matchAK4deepb[fjet] = -100;
    }
    fjet++;
    if(fjet>=njetmxAK8) break;
  }
  npfjetAK8 = fjet;
  int maxM(-1);
  float LMass(0);
  for(int ljet=0; ljet< npfjetAK8; ljet++){
    if (!(isnan(pfjetAK8mass[ljet]))) {
      if (pfjetAK8mass[ljet] > LMass) {
	LMass = pfjetAK8mass[ljet];
	maxM = ljet;
      }
    }
  }
  int nmuon1 = 0;
  for(int mu=0; mu<nmuons; mu++){
    if(muonpt[mu]<30.) continue; 
    if(fabs(muoneta[mu])>2.4)  continue; 
    bool mu_id = Muon_TightID(muonisGL[mu],muonisPF[mu],
			      muonchi[mu],muonthit[mu],muonmst[mu],
			      muontrkvtx[mu],muondz[mu],muonpixhit[mu],muontrklay[mu]);
    bool mu_iso = Muon_Iso_ID(muonpfiso[mu]);
    if(!mu_id) continue;
    muonpt[nmuon1] = muonpt[mu];
    muoneta[nmuon1] = muoneta[mu];
    muonphi[nmuon1] = muonphi[mu];
    muone[nmuon1] = muone[mu];
    muonp[nmuon1] = muonp[mu];
    nmuon1++;
    if(nmuon1 >= njetmx) break;
  }
  nmuons = nmuon1;
  fjet = 0;
  int nbjetAK4 = 0;
  for(int ijet=0; ijet<npfjetAK4; ijet++){
    if(!pfjetAK4looseID[ijet]) continue; //switch to tight ID (even tight ID calculation also do here in this code)
    if(fabs(pfjetAK4eta[ijet])>2.5) continue;
    pfjetAK4pt[ijet] *= pfjetAK4JEC[ijet] ;
    pfjetAK4mass[ijet] *= pfjetAK4JEC[ijet];
    if(isMC){
      pfjetAK4pt[ijet] *= (1+pfjetAK4reso[ijet]) ;
      pfjetAK4mass[ijet] *= (1+pfjetAK4reso[ijet]) ;
    }
    if(pfjetAK4pt[ijet]<30.) continue;
    pfjetAK4pt[fjet] = pfjetAK4pt[ijet];
    pfjetAK4mass[fjet] = pfjetAK4mass[ijet];
    pfjetAK4eta[fjet] = pfjetAK4eta[ijet];
    pfjetAK4y[fjet] = pfjetAK4y[ijet];
    pfjetAK4phi[fjet] = pfjetAK4phi[ijet];
    pfjetAK4btag_DeepFlav[fjet] = pfjetAK4btag_DeepFlav[ijet];
    if(pfjetAK4btag_DeepFlav[fjet] > deep_btag_cut) { nbjetAK4++; }
    fjet++;
    if(fjet >= njetmx) break;
  }
  npfjetAK4 = fjet;
  hist_npv->Fill(nchict,weight);
  if(isMC){
    hist_npu->Fill(npu_vert,weight);
  }
  
  if(nchict<1) return kFALSE;
  bool itrig_epass = false;
  bool itrig_ljpass = false;

  // e + jets (semileptonic ttbar) 
#ifdef E_Jets_TTBar
  //itrig_pass = ((ihlt05==1)||(ihlt07==1)||(ihlt08==1)||(ihlt09==1)||(ihlt10==1));
  itrig_epass = ((ihlt14==1)||(ihlt15==1));
  itrig_ljpass = (ihlt09==1);
  if(!itrig_epass && !itrig_ljpass) return kFALSE;
  int npfjetAK8_we = 0;
  for(int ijet=0; ijet<npfjetAK8; ijet++){
    if (pfjetAK8haspfelectron[ijet]) {
      npfjetAK8_we++;
    }
  }
  if(npfjetAK8<2) return kFALSE;
  if(npfjetAK8_we<1) return kFALSE;
#endif
  if(PFMET < 50.) return kFALSE;  // MET cut of 50 GeV

  for(int ijet=0; ijet< npfjetAK8; ijet++){
    if(ijet>(nmaxjet-1)) break;
    if(isnan(pfjetAK8pt[ijet])) { pfjetAK8pt[ijet] = -100; }
    if(isnan(pfjetAK8y[ijet])) { pfjetAK8y[ijet] = -100; }
    if(isnan(pfjetAK8mass[ijet])) { pfjetAK8mass[ijet] = -100; }
    if(isnan(pfjetAK8phi[ijet])) { pfjetAK8phi[ijet] = -100; }
    if(isnan(pfjetAK8btag_CMVA[ijet])) { pfjetAK8btag_CMVA[ijet] = -100; }
    if(isnan(pfjetAK8btag_CSV[ijet])) { pfjetAK8btag_CSV[ijet] = -100; }
    if(isnan(pfjetAK8btag_DeepCSV[ijet])) { pfjetAK8btag_DeepCSV[ijet] = -100; }
    if(isnan(pfjetAK8matchAK4deepb[ijet])) { pfjetAK8matchAK4deepb[ijet] = -100; }
    if(isnan(pfjetAK8DeepTag_TvsQCD[ijet])) { pfjetAK8DeepTag_TvsQCD[ijet] = -100; }
    if(isnan(pfjetAK8DeepTag_WvsQCD[ijet])) { pfjetAK8DeepTag_WvsQCD[ijet] = -100; }
    if(isnan(pfjetAK8DeepTag_ZvsQCD[ijet])) { pfjetAK8DeepTag_ZvsQCD[ijet] = -100; }
    if(isnan(pfjetAK8CHF[ijet])) { pfjetAK8CHF[ijet] = -100; }
    if(isnan(pfjetAK8NHF[ijet])) { pfjetAK8NHF[ijet] = -100; }
    if(isnan(pfjetAK8CEMF[ijet])) { pfjetAK8CEMF[ijet] = -100; }
    if(isnan(pfjetAK8NEMF[ijet])) { pfjetAK8NEMF[ijet] = -100; }
    if(isnan(pfjetAK8MUF[ijet])) { pfjetAK8MUF[ijet] = -100; }
    if(isnan(pfjetAK8HOF[ijet])) { pfjetAK8HOF[ijet] = -100; }
    if(isnan(pfjetAK8HadF[ijet])) { pfjetAK8HadF[ijet] = -100; }
    if(isnan(pfjetAK8NHadF[ijet])) { pfjetAK8NHadF[ijet] = -100; }
    if(isnan(pfjetAK8EmF[ijet])) { pfjetAK8EmF[ijet] = -100; }
    if(isnan(pfjetAK8neuemfrac[ijet])) { pfjetAK8neuemfrac[ijet] = -100; }
    if(isnan(pfjetAK8neunhadfrac[ijet])) { pfjetAK8neunhadfrac[ijet] = -100; }
    if(isnan(pfjetAK8EEM[ijet])) { pfjetAK8EEM[ijet] = -100; }
    if(isnan(pfjetAK8chrad[ijet])) { pfjetAK8chrad[ijet] = -100; }
    if(isnan(pfjetAK8pTD[ijet])) { pfjetAK8pTD[ijet] = -100; }
    if(isnan(pfjetAK8sdmass[ijet])) { pfjetAK8sdmass[ijet] = -100; }
    if(isnan(pfjetAK8elsubjptrat[ijet])) { pfjetAK8elsubjptrat[ijet] = -100; }
    if(isnan(pfjetAK8elinsubpt[ijet])) { pfjetAK8elinsubpt[ijet] = -100; }
    if(isnan(pfjetAK8elinsubeta[ijet])) { pfjetAK8elinsubeta[ijet] = -100; }
    if(isnan(pfjetAK8elinsubphi[ijet])) { pfjetAK8elinsubphi[ijet] = -100; }
    if(isnan(pfjetAK8elinsubjpt[ijet])) { pfjetAK8elinsubjpt[ijet] = -100; }
    if(isnan(pfjetAK8elinsubjeta[ijet])) { pfjetAK8elinsubjeta[ijet] = -100; }
    if(isnan(pfjetAK8elinsubjphi[ijet])) { pfjetAK8elinsubjphi[ijet] = -100; }
    if(isnan(pfjetAK8tau21[ijet])) { pfjetAK8tau21[ijet] = -100; }
    if(isnan(pfjetAK8tau32[ijet])) { pfjetAK8tau32[ijet] = -100; }
    if(isnan(pfjetAK8sub1mass[ijet])) { pfjetAK8sub1mass[ijet] = -100; }
    if(isnan(pfjetAK8sub1btag[ijet])) { pfjetAK8sub1btag[ijet] = -100; }
    if(isnan(pfjetAK8sub1hadfrac[ijet])) { pfjetAK8sub1hadfrac[ijet] = -100; }
    if(isnan(pfjetAK8sub1emfrac[ijet])) { pfjetAK8sub1emfrac[ijet] = -100; }
    if(isnan(pfjetAK8sub2mass[ijet])) { pfjetAK8sub2mass[ijet] = -100; }
    if(isnan(pfjetAK8sub2btag[ijet])) { pfjetAK8sub2btag[ijet] = -100; }
    if(isnan(pfjetAK8sub2hadfrac[ijet])) { pfjetAK8sub2hadfrac[ijet] = -100; }
    if(isnan(pfjetAK8sub2emfrac[ijet])) { pfjetAK8sub2emfrac[ijet] = -100; }
    if(isnan(pfjetAK8subhaddiff[ijet])) { pfjetAK8subhaddiff[ijet] = -100; }
    if(isnan(pfjetAK8subemdiff[ijet])) { pfjetAK8subemdiff[ijet] = -100; }
    if(isnan(pfjetAK8subptdiff[ijet])) { pfjetAK8subptdiff[ijet] = -100; }
    if(isnan(pfjetAK8subbtag[ijet])) { pfjetAK8subbtag[ijet] = -100; }
    if(isnan(pfjetAK8haselectron[ijet])) { pfjetAK8haselectron[ijet] = -100; }
    if(isnan(pfjetAK8hasmuon[ijet])) { pfjetAK8hasmuon[ijet] = -100; }
    if(isnan(pfjetAK8hasleptop[ijet])) { pfjetAK8hasleptop[ijet] = -100; }
    if(isnan(pfjetAK8hashadtop[ijet])) { pfjetAK8hashadtop[ijet] = -100; }
    if(isnan(pfjetAK8hasqg[ijet])) { pfjetAK8hasqg[ijet] = -100; }
    if(isnan(pfjetAK8hasb[ijet])) { pfjetAK8hasb[ijet] = -100; }
    if(isnan(pfjetAK8_bbyW_E[ijet])) { pfjetAK8_bbyW_E[ijet] = -100; }
    if(isnan(pfjetAK8_Kfactor[ijet])) { pfjetAK8_Kfactor[ijet] = -100; }
    if(isnan(pfjetAK8_Rnew[ijet])) { pfjetAK8_Rnew[ijet] = -100; }
    if(isnan(pfjetAK8_leppt[ijet])) { pfjetAK8_leppt[ijet] = -100; }
    if(isnan(pfjetAK8_bpt[ijet])) { pfjetAK8_bpt[ijet] = -100; }
    if(isnan(pfjetAK8_nupt[ijet])) { pfjetAK8_nupt[ijet] = -100; }

    Float_t Re(-100);
    in_pfjetAK8NHadF = pfjetAK8NHadF[ijet];
    in_pfjetAK8neunhadfrac = pfjetAK8neunhadfrac[ijet];
    in_pfjetAK8subhaddiff = pfjetAK8subhaddiff[ijet];
    in_pfjetAK8tau21 = pfjetAK8tau21[ijet];
    in_pfjetAK8chrad = pfjetAK8chrad[ijet];
    in_pfjetAK8sdmass = pfjetAK8sdmass[ijet];
    in_pfjetAK8eldxy_sv = -999;
    in_pfjetAK8matchedelcleta = -999;
    in_pfjetAK8matchedelpt = -999;
    in_pfjetAK8matchedelsigmaieta = -999;
    in_pfjetAK8matchedelsigmaiphi = -999;
    in_pfjetAK8matchedelr9full = -999;
    in_pfjetAK8matchedelsupcl_etaw = -999;
    in_pfjetAK8matchedelsupcl_phiw = -999;
    in_pfjetAK8matchedelhcaloverecal = -999;
    in_pfjetAK8matchedelcloctftrkn = -999;
    in_pfjetAK8matchedelcloctftrkchi2 = -999;
    in_pfjetAK8matchedele1x5bye5x5 = -999;
    in_pfjetAK8matchedelnormchi2 = -999;
    in_pfjetAK8matchedelhitsmiss = -999;
    in_pfjetAK8matchedeltrkmeasure = -999;
    in_pfjetAK8matchedelecloverpout = -999;
    in_pfjetAK8matchedelecaletrkmomentum = -999;
    in_pfjetAK8matchedeldeltaetacltrkcalo = -999;
    in_pfjetAK8matchedelsupcl_preshvsrawe = -999;
    in_pfjetAK8matchedelpfisolsumphet = -999;
    in_pfjetAK8matchedelpfisolsumchhadpt = -999;
    in_pfjetAK8matchedelpfisolsumneuhadet = -999;
    in_pfjetAK8matchedeletain = -999;
    in_pfjetAK8matchedelphiin = -999;
    in_pfjetAK8matchedelfbrem = -999;
    in_pfjetAK8matchedeleoverp = -999;
    in_pfjetAK8matchedelhovere = -999;
  
    if (pfjetAK8elinsubeta[ijet] != -100 && pfjetAK8elinsubphi[ijet] != -100)
      {
        if (nelecs > 0) {
          float dR_min(0.4); int nearest(-1);
          for(int el=0; el<nelecs; el++){
            float dR = delta2R(eleta[el],elphi[el],pfjetAK8elinsubeta[ijet],pfjetAK8elinsubphi[ijet]);
            if (dR < dR_min) {
              dR_min = dR;
              nearest = el;
            }
	  }
          if (nearest >= 0) {
            in_pfjetAK8eldxy_sv = eldxy_sv[nearest];
	    in_pfjetAK8matchedelcleta = elsupcl_eta[nearest];
	    in_pfjetAK8matchedelpt = fabs(elpt[nearest]);
	    in_pfjetAK8matchedelsigmaieta = elsigmaieta[nearest];
            in_pfjetAK8matchedelsigmaiphi = elsigmaiphi[nearest];
	    in_pfjetAK8matchedelr9full = elr9full[nearest];
	    in_pfjetAK8matchedelsupcl_etaw = elsupcl_etaw[nearest];
            in_pfjetAK8matchedelsupcl_phiw = elsupcl_phiw[nearest];
	    in_pfjetAK8matchedelhcaloverecal = elhcaloverecal[nearest];
            in_pfjetAK8matchedelcloctftrkn = elcloctftrkn[nearest];
	    in_pfjetAK8matchedelcloctftrkchi2 = elcloctftrkchi2[nearest];
            in_pfjetAK8matchedele1x5bye5x5 = ele1x5bye5x5[nearest];
	    in_pfjetAK8matchedelnormchi2 = elnormchi2[nearest];
            in_pfjetAK8matchedelhitsmiss = elhitsmiss[nearest];
	    in_pfjetAK8matchedeltrkmeasure = eltrkmeasure[nearest];
	    in_pfjetAK8matchedelecloverpout = elecloverpout[nearest];
	    in_pfjetAK8matchedelecaletrkmomentum = elecaletrkmomentum[nearest];
	    in_pfjetAK8matchedeldeltaetacltrkcalo = eldeltaetacltrkcalo[nearest];
	    in_pfjetAK8matchedelsupcl_preshvsrawe = elsupcl_preshvsrawe[nearest];
	    in_pfjetAK8matchedelpfisolsumphet = elpfisolsumphet[nearest];
            in_pfjetAK8matchedelpfisolsumchhadpt = elpfisolsumchhadpt[nearest];
            in_pfjetAK8matchedelpfisolsumneuhadet = elpfsiolsumneuhadet[nearest];
	    in_pfjetAK8matchedeletain = eletain[nearest];
            in_pfjetAK8matchedelphiin = elphiin[nearest];
            in_pfjetAK8matchedelfbrem = elfbrem[nearest];
	    in_pfjetAK8matchedeleoverp = eleoverp[nearest];
            in_pfjetAK8matchedelhovere = elhovere[nearest];
	  }
	}
      }
    if (!isnan(Rho)) in_pfjetAK8matchedelRho = Rho;
    else in_pfjetAK8matchedelRho = -999;
    
    pfjetAK8re_tvsb[ijet] = -100;
    Re = reader1->EvaluateMVA("BDTG method");
    pfjetAK8re_tvsb[ijet] = Re;

    in_pfjetAK8_bbyW_E = pfjetAK8_bbyW_E[ijet];
    in_pfjetAK8_Kfactor = pfjetAK8_Kfactor[ijet];
    Float_t Rnu(-100);

    Rnu = reader2->EvaluateMVA("BDTG method");
    pfjetAK8rnu_tvsb[ijet] = Rnu;
  }//ijet
  
  int t_cand = -1;
  double remax = -200;
  for(int ijet=0; ijet < npfjetAK8; ijet++){
    if(pfjetAK8re_tvsb[ijet] > remax){
      remax = pfjetAK8re_tvsb[ijet];
      t_cand = ijet;
    }
  }
 
  // object assignment //
  int telcand = -1;
  bool te_found = false;
  // for e+jets
#ifdef E_Jets_TTBar
  int thcand = -1;
  float maxscore = DAK8_topcut;
  for(int ijet=0; ijet<npfjetAK8; ijet++){
    if(pfjetAK8pt[ijet]<400.) { continue; }
    if(pfjetAK8sdmass[ijet] > 105. &&  pfjetAK8sdmass[ijet] < 210. && pfjetAK8DeepTag_TvsQCD[ijet] > maxscore){
      maxscore = pfjetAK8DeepTag_TvsQCD[ijet] ;
      thcand = ijet;
    }
  }
  if(thcand >=0){
    for(int ijet=0; ijet<npfjetAK8; ijet++){
      if(pfjetAK8pt[ijet]<400.) continue; 
      if(ijet==thcand) continue;
      if( (delta2R(pfjetAK8y[thcand],pfjetAK8phi[thcand],pfjetAK8y[ijet],pfjetAK8phi[ijet]) > 1.6)
	  && (PhiInRange(pfjetAK8phi[thcand] - pfjetAK8phi[ijet]) > M_PI/3.) 
	  && pfjetAK8haspfelectron[ijet]	){
	te_found = true;
	telcand = ijet;
      }
      if(te_found) break;
    }
  }
#endif
  /* 
  #if !defined(E_Jets_TTBar) && !defined(E_MU_TTBar) 
  if(npfjetAK8>0){ telcand = 0; }
  #endif
 */  
  
  // object assignment ends //
  if(telcand>=0){
    hist_obs[0]->Fill(pfjetAK8pt[telcand],weight);
    hist_obs[1]->Fill(pfjetAK8y[telcand],weight);
    hist_obs[2]->Fill(pfjetAK8mass[telcand],weight);
    hist_obs[3]->Fill(pfjetAK8NHadF[telcand],weight);
    hist_obs[4]->Fill(pfjetAK8neunhadfrac[telcand],weight);
    hist_obs[5]->Fill(pfjetAK8sdmass[telcand],weight);
    hist_obs[6]->Fill(pfjetAK8chrad[telcand],weight);
    hist_obs[7]->Fill(pfjetAK8subhaddiff[telcand],weight);
    hist_obs[8]->Fill(pfjetAK8tau21[telcand],weight);
    hist_obs[9]->Fill(pfjetAK8DeepTag_TvsQCD[telcand],weight);
    hist_obs[10]->Fill(pfjetAK8_bbyW_E[telcand],weight);
    hist_obs[11]->Fill(pfjetAK8_Kfactor[telcand],weight);
    hist_obs[12]->Fill(pfjetAK8re_tvsb[telcand],weight);
    hist_obs[13]->Fill(pfjetAK8rnu_tvsb[telcand],weight);
    if(pfjetAK8re_tvsb[telcand] > re_cut){
      hist_obs_1[0]->Fill(pfjetAK8pt[telcand],weight);
      hist_obs_1[1]->Fill(pfjetAK8y[telcand],weight);
      hist_obs_1[2]->Fill(pfjetAK8mass[telcand],weight);
      hist_obs_1[3]->Fill(pfjetAK8NHadF[telcand],weight);
      hist_obs_1[4]->Fill(pfjetAK8neunhadfrac[telcand],weight);
      hist_obs_1[5]->Fill(pfjetAK8sdmass[telcand],weight);
      hist_obs_1[6]->Fill(pfjetAK8chrad[telcand],weight);
      hist_obs_1[7]->Fill(pfjetAK8subhaddiff[telcand],weight);
      hist_obs_1[8]->Fill(pfjetAK8tau21[telcand],weight);
      hist_obs_1[9]->Fill(pfjetAK8DeepTag_TvsQCD[telcand],weight);
      hist_obs_1[10]->Fill(pfjetAK8_bbyW_E[telcand],weight);
      hist_obs_1[11]->Fill(pfjetAK8_Kfactor[telcand],weight);
      hist_obs_1[12]->Fill(pfjetAK8re_tvsb[telcand],weight);
      hist_obs_1[13]->Fill(pfjetAK8rnu_tvsb[telcand],weight);
    }else{
      hist_obs_2[0]->Fill(pfjetAK8pt[telcand],weight);
      hist_obs_2[1]->Fill(pfjetAK8y[telcand],weight);
      hist_obs_2[2]->Fill(pfjetAK8mass[telcand],weight);
      hist_obs_2[3]->Fill(pfjetAK8NHadF[telcand],weight);
      hist_obs_2[4]->Fill(pfjetAK8neunhadfrac[telcand],weight);
      hist_obs_2[5]->Fill(pfjetAK8sdmass[telcand],weight);
      hist_obs_2[6]->Fill(pfjetAK8chrad[telcand],weight);
      hist_obs_2[7]->Fill(pfjetAK8subhaddiff[telcand],weight);
      hist_obs_2[8]->Fill(pfjetAK8tau21[telcand],weight);
      hist_obs_2[9]->Fill(pfjetAK8DeepTag_TvsQCD[telcand],weight);
      hist_obs_2[10]->Fill(pfjetAK8_bbyW_E[telcand],weight);
      hist_obs_2[11]->Fill(pfjetAK8_Kfactor[telcand],weight);
      hist_obs_2[12]->Fill(pfjetAK8re_tvsb[telcand],weight);
      hist_obs_2[13]->Fill(pfjetAK8rnu_tvsb[telcand],weight);
    }
  }
return kTRUE;
}

void Anal_LeptopReco_PROOF::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  fileOut->cd();
  fileOut->Write();
  fOutput->Add(OutFile);
  fileOut->Close();
}

void Anal_LeptopReco_PROOF::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  
}
