// -*- C++ -*-
//
// Package:    Run2_2016/TopplusB
// Class:      TopplusB
// 
/**\class TopplusB TopplusB.cc Run2_2016/TopplusB/plugins/TopplusB.cc

   Description: [one line class summary]
   
   Implementation:
   [Notes on implementation]
*/
//
// Original Author:  Suman Chatterjee
//         Created:  Thu, 31 Oct 2019 16:22:44 GMT
//
//

// system include files-
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/METCollection.h"
#include "DataFormats/METReco/interface/CaloMETCollection.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETFwd.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/JetReco/interface/JetID.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TAxis.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "TRandom.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"

#include "GeneratorInterface/Pythia8Interface/plugins/ReweightUserHooks.h"

#include "fastjet/contrib/SoftDrop.hh"
#include "fastjet/contrib/Nsubjettiness.hh"

//#include "fastjet"
//#include "fastjet/contrib/"

#include <string>

#include <iostream>
#include <fstream>

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalCalibrations.h"
//#include "CalibFormats/HcalObjects/interface/HcalCalibrationWidths.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
//#include "CondFormats/HcalObjects/interface/HcalQIECoder.h"
//#include "CondFormats/HcalObjects/interface/HcalPedestal.h"
//#include "CondFormats/HcalObjects/interface/HcalPedestalWidth.h"
//#include "CondFormats/HcalObjects/interface/HcalElectronicsMap.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "JetMETCorrections/JetCorrector/interface/JetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "FWCore/Utilities/interface/typelookup.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include  "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"
//#include "RecoEgamma/ElectronIdentification/interface/ElectronMVAEstimatorRun2Spring16GeneralPurpose.h"
#include "RecoEgamma/ElectronIdentification/interface/ElectronMVAEstimatorRun2.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtTrigReportEntry.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtTrigReport.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetResolutionObject.h"
#include <FWCore/Framework/interface/EventSetup.h>
#include <FWCore/Framework/interface/ESHandle.h>
//#include "CondFormats/DataRecord/interface/JetResolutionRcd.h"
//#include "CondFormats/DataRecord/interface/JetResolutionScaleFactorRcd.h"
#include "FWCore/Utilities/interface/typelookup.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "SimDataFormats/GeneratorProducts/interface/PdfInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "fastjet/Selector.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"
#include <fastjet/GhostedAreaSpec.hh>
#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/tools/Filter.hh"
#include "fastjet/tools/Pruner.hh"
#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/GridMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"
#include "fastjet/Selector.hh"
#include "fastjet/tools/Subtractor.hh"


using namespace std;
using namespace edm;
using namespace reco;  
using namespace CLHEP;
using namespace trigger;
using namespace math;
using namespace fastjet;
using namespace fastjet::contrib;

const float mu_mass = 0.105658;
const float el_mass = 0.000511;
const float pival = acos(-1.);

const int noptbins = 62 ;

double ptbins[noptbins+1] = {/*37, 43, 49, 56, 64,*/ 74, 84,
			     97, 114, 133, 153, 174, 196, 220, 245, 272, 300, 330, 362, 395, 430, 468, 
			     507, 548, 592, 638, 686, 737, 790, 846, 905, 967, 
			     1032, 1101, 1172, 1248, 1327, 1410, 1497, 1588, 1684, 1784, 1890, 2000, 
			     2116, 2238, 2366, 2500, 2640, 2787, 2941, 3103, 3273, 3450, 3637, 3832,
			     4037, 4252, 4477, 4713, 4961, 5220, 5492, 5777, 6076, 6389, 6717, 7000} ;

static const int nsrc = 7;
//const char* srcnames[nsrc] = {"AbsoluteStat", "AbsoluteScale", "AbsoluteFlavMap", "AbsoluteMPFBias", "Fragmentation", "SinglePionECAL", "SinglePionHCAL", "FlavorQCD", "TimePtEta","RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF", "RelativePtBB", "RelativePtEC1", "RelativePtEC2","RelativePtHF", "RelativeBal", "RelativeSample", "RelativeFSR", "RelativeStatFSR", "RelativeStatEC", "RelativeStatHF", "PileUpDataMC", "PileUpPtRef", "PileUpPtBB", "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF","PileUpMuZero","PileUpEnvelope","SubTotalPileUp","SubTotalRelative","SubTotalPt","SubTotalScale","SubTotalAbsolute","SubTotalMC","Total"};

const char* srcnames[nsrc] = {"SubTotalPileUp","SubTotalRelative","SubTotalPt","SubTotalScale","SubTotalAbsolute","SubTotalMC","Total"};
const int njecmcmx = 2*nsrc + 1 ;

const int nomassbins = 200 ;

double massbins[nomassbins+1] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200}; 

//double massbins[nomassbins+1] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500};

const int norhobins = 51 ;

double rhobins[norhobins+1] = {0.0001,0.00012,0.000144,0.0001728,0.00020736,0.000248832,0.000298598,0.000358318,0.000429982,0.000515978,0.000619174,0.000743008,0.00089161,0.00106993,0.00128392,0.0015407,0.00184884,0.00221861,0.00266233,0.0031948,0.00383376,0.00460051,0.00552061,0.00662474,0.00794968,0.00953962,0.0114475,0.0137371,0.0164845,0.0197814,0.0237376,0.0284852,0.0341822,0.0410186,0.0492224,0.0590668,0.0708802,0.0850562,0.102067,0.122481,0.146977,0.176373,0.211647,0.253977,0.304772,0.365726,0.438871,0.526646,0.631975,0.75837,0.910044,1.09205};

double logrhobins[norhobins+1] = {-0.088059,0.0942625,0.276584,0.458906,0.641227,0.823549,1.00587,1.18819,1.37051,1.55283,1.73516,1.91748,2.0998,2.28212,2.46444,2.64676,2.82909,3.01141,3.19373,3.37605,3.55837,3.74069,3.92302,4.10534,4.28766,4.46998,4.6523,4.83462,5.01694,5.19927,5.38159,5.56391,5.74623,5.92855,6.11087,6.2932,6.47552,6.65784,6.84016,7.02248,7.2048,7.38712,7.56945,7.75177,7.93409,8.11641,8.29873,8.48105,8.66338,8.8457,9.02802,9.21034};

double width = 1.2;

struct triggervar{
  HepLorentzVector trg4v;
  bool		       both;
  bool            level1;
  bool            highl;
  int             ihlt;
  int             prescl;
};

int getbinid(double val, int nbmx, double* array) {
  if (val<array[0]) return -2;
  for (int ix=0; ix<=nbmx; ix++) {
    if (val < array[ix]) return ix-1;
  }
  return -3;
}

double theta_to_eta(double theta) { return -log(tan(theta/2.)); }

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


TLorentzVector productX(TLorentzVector X, TLorentzVector Y, float pro1, float pro2)
{
  float b1, b2, b3;
  float c1, c2, c3;
  
  b1 = X.Px();
  b2 = X.Py();
  b3 = X.Pz();
  
  c1 = Y.Px();
  c2 = Y.Py();
  c3 = Y.Pz();
  
  float d1, d2, e1, e2, X1, X2;
  
  X1 = pro1;
  X2 = pro2;
  
  d1 = (c2*X1 - b2*X2)*1./(b1*c2 - b2*c1);
  d2 = (c1*X1 - b1*X2)*1./(b2*c1 - b1*c2);
  e1 = (b2*c3 - b3*c2)*1./(b1*c2 - b2*c1);
  e2 = (b1*c3 - b3*c1)*1./(b2*c1 - b1*c2);
 
  float A, B, C;
  A = (e1*e1 + e2*e2+ 1);
  B = 2*(d1*e1 + d2*e2);
  C = d1*d1 + d2*d2 - 1;
  
  float sol;
 
  if((pow(B,2) - (4*A*C)) < 0){
    sol = -1*B/(2*A);
    
float A1, A2, A3;
 A3 = sol;
 A1 = d1 + e1*A3;
 A2 = d2 + e2*A3;
 
 TLorentzVector vec4;
 vec4.SetPxPyPzE(A1,A2,A3,0);
 return vec4;
  }
  else{
    float sol1 = (-1*B+sqrt((pow(B,2) - (4*A*C))))*1./(2*A);
    float sol2 =  (-1*B-sqrt((pow(B,2) - (4*A*C))))*1./(2*A);
    (sol1>sol2)?sol=sol1:sol=sol2;
    
    float A1, A2, A3;
    A3 = sol;
    A1 = d1 + e1*A3;
    A2 = d2 + e2*A3;
    
    TLorentzVector vec4;
    vec4.SetPxPyPzE(A1,A2,A3,0);
    return vec4;;
  }
  
}

//class declaration
//
class Leptop : public edm::EDAnalyzer {
public:
  explicit Leptop(const edm::ParameterSet&);
  ~Leptop();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void fillmetarray();
      // ----------member data ---------------------------
  int Nevt;
  int ncnt;
  bool isData;
  bool isMC;
  bool isSoftDrop;
  bool isReconstruct ;
  bool isHistFill;
  std::string theRootFileName;
  std::string theHLTTag;
  std::string softdropmass;
  std::string tau1;
  std::string tau2;
  std::string tau3;
  std::string subjets;
  std::string toptagger;
  std::string Wtagger;
  std::string Ztagger;
  std::string BBtagger;
  std::string CCtagger;
  std::string btag_CMVA_name;
  std::string btag_CSV_name;
  int iTag;
  int iTagMET;
  double jtptthr;
  double minPt;
  double maxEta;
  double maxgenEta;
  double AK8PtCut;
  
  double JetRadius;
  double beta ;
  double z_cut;
  double nprong;
  int nkTsub;
  
  const float t_mass = 173;
  const float w_mass = 80.4;
  float b_mass;
  float mass_l = 0;
  
  //  edm::EDGetTokenT<reco::BeamSpot> tok_beamspot_;
  edm::EDGetTokenT<double> tok_Rho_;
  edm::EDGetTokenT<reco::BeamSpot> tok_beamspot_;
  edm::EDGetTokenT<reco::VertexCollection> tok_primaryVertices_;
  //edm::EDGetTokenT<reco::GenParticleCollection>tok_genparticles_;
  edm::EDGetTokenT<reco::VertexCompositePtrCandidateCollection> tok_sv;
  edm::EDGetTokenT<pat::METCollection>tok_mets_ ;
  edm::EDGetTokenT<reco::GenMETCollection>tok_genmets_;
  
  edm::EDGetTokenT<edm::View<pat::Jet>>tok_pfjetAK8s_;
  edm::EDGetTokenT<edm::View<pat::Jet>>tok_pfsubjetAK8s_;
  edm::EDGetTokenT<reco::GenJetCollection>tok_genjetAK8s_;
  edm::EDGetTokenT<edm::View<pat::Jet>>tok_pfjetAK4s_;
  edm::EDGetTokenT<reco::GenJetCollection>tok_genjetAK4s_;
  //  edm::EDGetTokenT<edm::View<pat::PackedGenParticle>>tok_genparticles_;
  edm::EDGetTokenT<std::vector<reco::GenParticle>>tok_genparticles_;
  
  edm::EDGetTokenT<HepMCProduct> tok_HepMC ;
  edm::EDGetTokenT<GenEventInfoProduct> tok_wt_;
  
  edm::EDGetTokenT<LHEEventProduct> lheEventProductToken_;
  edm::EDGetTokenT<GenEventInfoProduct> GenEventProductToken_;
  
  edm::EDGetTokenT<edm::View<pat::Muon>> tok_muons_;
  edm::EDGetTokenT<edm::View<pat::Electron>> tok_electrons_;
  edm::EDGetTokenT<edm::View<pat::Photon>>tok_photons_;
  
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > pileup_;
  
  //edm::InputTag tag_mvaEleIDSpring16GeneralPurposeV1wp90_reco;
  //edm::InputTag tag_mvaEleIDSpring16GeneralPurposeV1wp90_noIso_reco;
  //edm::EDGetTokenT <edm::ValueMap <bool> > tok_mvaEleIDSpring16GeneralPurposeV1wp90_reco;
  //edm::EDGetTokenT <edm::ValueMap <bool> > tok_mvaEleIDSpring16GeneralPurposeV1wp90_noIso_reco; 
  
  edm::InputTag tag_mvaPhoIDSpring16GeneralPurposeV1wp90_reco;
  edm::EDGetTokenT <edm::ValueMap <bool> > tok_mvaPhoIDSpring16GeneralPurposeV1wp90_reco;
  
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;
  
  TFile* theFile;

  TTree* T1;
  
  // HLTConfigProvider hltConfig_;
  
  unsigned ievt;
  
  static const int njetmx = 20; 
  static const int njetmxAK8 =10;
  static const int npartmx = 50; 
  
  int irunold;
  int irun, ilumi, ifltr, nprim, ibrnch;
  double event_weight;
  double weights[njetmx];
  
  double Rho ;
  
  int npfjetAK8;
  float pfjetAK8pt[njetmxAK8], pfjetAK8y[njetmxAK8], pfjetAK8eta[njetmxAK8], pfjetAK8phi[njetmxAK8], pfjetAK8mass[njetmxAK8];
  float pfjetAK8btag_CMVA[njetmxAK8], pfjetAK8btag_CSV[njetmxAK8], pfjetAK8btag_DeepCSV[njetmxAK8], pfjetAK8btag_DeepFlav[njetmxAK8];
  float pfjetAK8DeepTag_TvsQCD[njetmxAK8], pfjetAK8DeepTag_WvsQCD[njetmxAK8], pfjetAK8DeepTag_ZvsQCD[njetmxAK8], pfjetAK8DeepTag_BBvsQCD[njetmxAK8], pfjetAK8DeepTag_CCvsQCD[njetmxAK8];
  float pfjetAK8CHF[njetmxAK8], pfjetAK8NHF[njetmxAK8], pfjetAK8MUF[njetmxAK8], pfjetAK8PHF[njetmxAK8], pfjetAK8CEMF[njetmxAK8], pfjetAK8NEMF[njetmxAK8], pfjetAK8EEF[njetmxAK8], pfjetAK8HFHF[njetmxAK8], pfjetAK8HFEMF[njetmxAK8], pfjetAK8HOF[njetmxAK8];
  int pfjetAK8CHM[njetmxAK8], pfjetAK8NHM[njetmxAK8], pfjetAK8MUM[njetmxAK8], pfjetAK8PHM[njetmxAK8], pfjetAK8CEMM[njetmxAK8], pfjetAK8NEMM[njetmxAK8], pfjetAK8Neucons[njetmxAK8], pfjetAK8Chcons[njetmxAK8], pfjetAK8EEM[njetmxAK8], pfjetAK8HFHM[njetmxAK8], pfjetAK8HFEMM[njetmxAK8];
  float pfjetAK8chrad[njetmxAK8], pfjetAK8pTD[njetmxAK8], pfjetAK8axis2[njetmxAK8], pfjetAK8leadtrackpt[njetmxAK8];
  float pfjetAK8sdmass[njetmxAK8], pfjetAK8tau1[njetmxAK8], pfjetAK8tau2[njetmxAK8], pfjetAK8tau3[njetmxAK8];
  float pfjetAK8sub1pt[njetmxAK8], pfjetAK8sub1eta[njetmxAK8], pfjetAK8sub1phi[njetmxAK8], pfjetAK8sub1mass[njetmxAK8], pfjetAK8sub1btag[njetmxAK8]; 
  float pfjetAK8sub1hadfrac[njetmxAK8], pfjetAK8sub1chhadfrac[njetmxAK8], pfjetAK8sub1neuhadfrac[njetmxAK8], pfjetAK8sub1emfrac[njetmxAK8], pfjetAK8sub1neuemfrac[njetmxAK8], pfjetAK8sub1phofrac[njetmxAK8], pfjetAK8sub1mufrac[njetmxAK8];
  float pfjetAK8sub2pt[njetmxAK8], pfjetAK8sub2eta[njetmxAK8], pfjetAK8sub2phi[njetmxAK8], pfjetAK8sub2mass[njetmxAK8], pfjetAK8sub2btag[njetmxAK8];
  float pfjetAK8sub2hadfrac[njetmxAK8], pfjetAK8sub2chhadfrac[njetmxAK8], pfjetAK8sub2neuhadfrac[njetmxAK8], pfjetAK8sub2emfrac[njetmxAK8], pfjetAK8sub2neuemfrac[njetmxAK8], pfjetAK8sub2phofrac[njetmxAK8], pfjetAK8sub2mufrac[njetmxAK8];
  
  float pfjetAK8elinsubpt[njetmxAK8], pfjetAK8elinsubeta[njetmxAK8], pfjetAK8elinsubphi[njetmxAK8], pfjetAK8elinsube[njetmxAK8], pfjetAK8elinsubmass[njetmxAK8];
  float pfjetAK8elinsubjpt[njetmxAK8], pfjetAK8elinsubjeta[njetmxAK8], pfjetAK8elinsubjphi[njetmxAK8], pfjetAK8elinsubje[njetmxAK8], pfjetAK8elinsubjmass[njetmxAK8];

  bool pfjetAK8looseID[njetmxAK8], pfjetAK8tightID[njetmxAK8], pfjetAK8tightLVID[njetmxAK8];
  float pfjetAK8JEC[njetmxAK8], pfjetAK8JECL1[njetmxAK8], pfjetAK8JECL2[njetmxAK8], pfjetAK8JECL3[njetmxAK8], pfjetAK8JECL2L3[njetmxAK8];
  float pfjetAK8reso[njetmxAK8], pfjetAK8resoup[njetmxAK8], pfjetAK8resodn[njetmxAK8];
  float pfjetAK8jesup_pu[njetmx], pfjetAK8jesup_rel[njetmx], pfjetAK8jesup_scale[njetmx], pfjetAK8jesup_total[njetmx], pfjetAK8jesdn_pu[njetmx], pfjetAK8jesdn_rel[njetmx], pfjetAK8jesdn_scale[njetmx], pfjetAK8jesdn_total[njetmx];
  float pfjetAK8qgl[njetmxAK8], pfjetAK8PUID[njetmxAK8];
  float pfjetAK8_leppt[njetmxAK8], pfjetAK8_lepeta[njetmxAK8], pfjetAK8_lepphi[njetmxAK8], pfjetAK8_lepe[njetmxAK8];
  float pfjetAK8_bpt[njetmxAK8], pfjetAK8_beta[njetmxAK8], pfjetAK8_bphi[njetmxAK8], pfjetAK8_be[njetmxAK8];
  float pfjetAK8_nupt[njetmxAK8], pfjetAK8_nueta[njetmxAK8], pfjetAK8_nuphi[njetmxAK8], pfjetAK8_nue[njetmxAK8], pfjetAK8_bbyW_E[njetmxAK8], pfjetAK8_Kfactor[njetmxAK8], pfjetAK8_Rnew[njetmxAK8];
  float pfjetAK8subhaddiff[njetmxAK8], pfjetAK8subemdiff[njetmxAK8], pfjetAK8subptdiff[njetmxAK8];
  float pfjetAK8lepemiso[njetmxAK8], pfjetAK8lepchhadiso[njetmxAK8], pfjetAK8lepneuhadiso[njetmxAK8];
  
  int npfjetAK4;
  float pfjetAK4pt[njetmx], pfjetAK4eta[njetmx], pfjetAK4y[njetmx], pfjetAK4phi[njetmx], pfjetAK4mass[njetmx];
  float pfjetAK4btag_CMVA[njetmx], pfjetAK4btag_CSV[njetmx], pfjetAK4btag_DeepCSV[njetmx], pfjetAK4btag_DeepCSV2[njetmx], pfjetAK4btag_DeepFlav[njetmx], pfjetAK4btag_DeepQCD[njetmx];
  float pfjetAK4CHF[njetmx], pfjetAK4NHF[njetmx], pfjetAK4MUF[njetmx], pfjetAK4PHF[njetmx], pfjetAK4CEMF[njetmx], pfjetAK4NEMF[njetmx], pfjetAK4EEF[njetmx], pfjetAK4HFHF[njetmx], pfjetAK4HFEMF[njetmx], pfjetAK4HOF[njetmx];
  int pfjetAK4CHM[njetmx], pfjetAK4NHM[njetmx], pfjetAK4MUM[njetmx], pfjetAK4PHM[njetmx], pfjetAK4CEMM[njetmx], pfjetAK4NEMM[njetmx], pfjetAK4Neucons[njetmx], pfjetAK4Chcons[njetmx], pfjetAK4EEM[njetmx], pfjetAK4HFHM[njetmx], pfjetAK4HFEMM[njetmx];
  float pfjetAK4moment1[njetmx], pfjetAK4moment2[njetmx], pfjetAK4moment3[njetmx], pfjetAK4chrad[njetmx], pfjetAK4beta[njetmx], pfjetAK4betaStar[njetmx], pfjetAK4pTD[njetmx], pfjetAK4axis2[njetmx];
  float pfjetAK4sdmass[njetmx], pfjetAK4tau1[njetmx], pfjetAK4tau2[njetmx], pfjetAK4tau3[njetmx];
  bool pfjetAK4looseID[njetmx], pfjetAK4tightID[njetmx], pfjetAK4tightLVID[njetmx];
  float pfjetAK4JEC[njetmx], pfjetAK4JECL1[njetmx], pfjetAK4JECL2[njetmx], pfjetAK4JECL3[njetmx], pfjetAK4JECL2L3[njetmx];
  float pfjetAK4reso[njetmx], pfjetAK4resoup[njetmx], pfjetAK4resodn[njetmx];
  float pfjetAK4jesup_pu[njetmx], pfjetAK4jesup_rel[njetmx], pfjetAK4jesup_scale[njetmx], pfjetAK4jesup_total[njetmx], pfjetAK4jesdn_pu[njetmx], pfjetAK4jesdn_rel[njetmx], pfjetAK4jesdn_scale[njetmx], pfjetAK4jesdn_total[njetmx];
  int pfjetAK4hadronflav[njetmx], pfjetAK4partonflav[njetmx], pfjetAK4partonpdg[njetmx];
  int pfjetAK4Ncons[njetmx];
  float pfjetAK4qgl[njetmx], pfjetAK4PUID[njetmx];
  int pfjetAK4GenMatch[njetmx];
  
  static const int ngenjetAK8mx =10;
  
  int ngenjetAK8;
  float genjetAK8pt[njetmxAK8], genjetAK8y[njetmxAK8], genjetAK8phi[njetmxAK8], genjetAK8btag[njetmxAK8], genjetAK8mass[njetmxAK8], genjetAK8sdmass[njetmxAK8]; 
  float genjetAK8tau1[njetmxAK8], genjetAK8tau2[njetmxAK8], genjetAK8tau3[njetmxAK8];
  float genjetAK8moment1[njetmxAK8], genjetAK8moment2[njetmxAK8], genjetAK8moment3[njetmxAK8], genjetAK8chrad[njetmxAK8], genjetAK8pTD[njetmxAK8], genjetAK8axis2[njetmxAK8];
  float genjetAK8sub1pt[njetmxAK8], genjetAK8sub1y[njetmxAK8], genjetAK8sub1phi[njetmxAK8], genjetAK8sub1mass[njetmxAK8], genjetAK8sub1hadfrac[njetmxAK8], genjetAK8sub1emfrac[njetmxAK8];
  float genjetAK8sub2pt[njetmxAK8], genjetAK8sub2y[njetmxAK8], genjetAK8sub2phi[njetmxAK8], genjetAK8sub2mass[njetmxAK8], genjetAK8sub2hadfrac[njetmxAK8], genjetAK8sub2emfrac[njetmxAK8];
  
 
  int ngenjetAK4;
  float genjetAK4pt[njetmx], genjetAK4y[njetmx], genjetAK4phi[njetmx], genjetAK4btag[njetmx], genjetAK4mass[njetmx], genjetAK4sdmass[njetmx]; 
  
  int ngenparticles;
  int genpartstatus[npartmx], genpartpdg[npartmx], genpartmompdg[npartmx], genpartmomid[npartmx], genpartdaugno[npartmx];
  float genpartpt[npartmx], genparteta[npartmx], genpartphi[npartmx], genpartm[npartmx], genpartq[npartmx];
  bool genpartfromhard[npartmx], genpartfromhardbFSR[npartmx], genpartisPromptFinalState[npartmx], genpartisLastCopyBeforeFSR[npartmx];
  
  float miset , misphi , sumEt, misetsig, chmiset, chmisphi, chmisetsig;
  float genmiset, genmisphi, genmisetsig;
  
  int nmuons;
  float muonp[njetmx], muone[njetmx], muonpt[njetmx], muoneta[njetmx], muonphi[njetmx], muondrbm[njetmx], muondz[njetmx], muonpter[njetmx], muonchi[njetmx], muonecal[njetmx], muonhcal[njetmx], muonemiso[njetmx], muonhadiso[njetmx], muontkpt03[njetmx], muontkpt05[njetmx];
  float muonposmatch[njetmx], muontrkink[njetmx], muonsegcom[njetmx], muonpfiso[njetmx], muontrkvtx[njetmx], muonhit[njetmx], muonpixhit[njetmx], muonmst[njetmx], muontrklay[njetmx], muonvalfrac[njetmx];
  int muonndf[njetmx];
  bool muonisPF[njetmx], muonisGL[njetmx], muonisTRK[njetmx];
  bool muonisGoodGL[njetmx], muonisMed[njetmx], muonisLoose[njetmx];
  
  int nelecs;
  bool elmvaid[njetmx], elmvaid_noIso[njetmx];
  float elpt[njetmx], eleta[njetmx], elphi[njetmx], ele[njetmx], elp[njetmx], eldxy[njetmx],  eldxy_sv[njetmx], eldz[njetmx], elhovere[njetmx], elqovrper[njetmx], elchi[njetmx], elemiso03[njetmx], elhadiso03[njetmx], elemiso04[njetmx], elhadiso04[njetmx], elhadisodepth03[njetmx], eltkpt03[njetmx], eltkpt04[njetmx], eleoverp[njetmx], elietaieta[njetmx], eletain[njetmx], elphiin[njetmx], elfbrem[njetmx], elchhadiso03[njetmx], elchhadiso04[njetmx], elnohits[njetmx], elmisshits[njetmx] ;
  float elchhadiso[njetmx], elneuhadiso[njetmx], elphoiso[njetmx], elpuchhadiso[njetmx], elpfiso[njetmx], elconvdist[njetmx], elconvdoct[njetmx];
  int elndf[njetmx];
  
  float elsupcl_eta[njetmx], elsupcl_phi[njetmx], elsupcl_rawE[njetmx]; 
  float elsigmaieta[njetmx];
  float elsigmaiphi[njetmx];
  float elr9full[njetmx];
  float elsupcl_etaw[njetmx];
  float elsupcl_phiw[njetmx];
  float elhcaloverecal[njetmx];
  float elcloctftrkn[njetmx];
  float elcloctftrkchi2[njetmx];
  float ele1x5bye5x5[njetmx];
  float elnormchi2[njetmx];
  float elhitsmiss[njetmx];
  float eltrkmeasure[njetmx];
  float elconvtxprob[njetmx];
  float elecloverpout[njetmx];
  float elecaletrkmomentum[njetmx];
  float eldeltaetacltrkcalo[njetmx];
  float elsupcl_preshvsrawe[njetmx];
  float elpfisolsumphet[njetmx];
  float elpfisolsumchhadpt[njetmx];
  float elpfsiolsumneuhadet[njetmx];
  
  int nphotons;
  bool phomvaid[njetmx];
  float phoe[njetmx], phoeta[njetmx], phophi[njetmx], phoe1by9[njetmx], phoe9by25[njetmx], phohadbyem[njetmx], photrkiso[njetmx], phoemiso[njetmx], phohadiso[njetmx], phochhadiso[njetmx], phoneuhadiso[njetmx], phoPUiso[njetmx], phophoiso[njetmx], phoietaieta[njetmx];
  
  int ntrigobjs;
  float trigobjpt[njetmx], trigobjeta[njetmx],trigobjphi[njetmx], trigobje[njetmx];
  bool trigobjHLT[njetmx], trigobjL1[njetmx],  trigobjBoth[njetmx];
  int  trigobjIhlt[njetmx];
  
  unsigned int mypow_2[32];
  
  float qscale;
  float wtfact , weight2 = 1.0;
  int npu_vert;
  
  int nchict;
  int nvert;;
  int ndofct;
  
  static const int nHLTmx = 17;
  const char *hlt_name[nHLTmx] = {"HLT_IsoMu24_v","HLT_Mu50_v","HLT_Ele32_WPTight_Gsf_v","HLT_Ele20_WPLoose_Gsf","HLT_Ele300_CaloIdVT_GsfTrkIdT","HLT_AK8PFJet420_TrimMass30_v","HLT_AK8PFHT900_TrimMass50_v","HLT_PFJet500_v","HLT_AK8PFJet500_v","HLT_PFHT1050_v","HLT_AK8PFHT750_TrimMass50_v","HLT_AK8PFHT800_TrimMass50_v","HLT_AK8PFHT850_TrimMass50_v","HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v","HLT_Ele115_CaloIdVT_GsfTrkIdT_v","HLT_DoubleEle33_CaloIdL_MW_v","HLT_DoubleEle25_CaloIdL_MW_v"};
  int ihlt01, ihlt02, ihlt03, ihlt04, ihlt05, ihlt06, ihlt07, ihlt08, ihlt09, ihlt10, ihlt11, ihlt12, ihlt13, ihlt14, ihlt15, ihlt16, ihlt17;
  float prescl01, prescl02, prescl03, prescl04, prescl05, prescl06, prescl07, prescl08, prescl09, prescl10, prescl11, prescl12, prescl13, prescl14, prescl15, prescl16, prescl17;
  double compres[nHLTmx] = {0};
  int trig_value;
  float weighttrg[nHLTmx];
  
  HLTPrescaleProvider hltPrescaleProvider_;
  
  // ---- Jet Corrector Parameter End---- //
  
  // ---- Jet Corrector Parameter ---- //
  JetCorrectorParameters *L1FastAK4, *L2RelativeAK4, *L3AbsoluteAK4, *L2L3ResidualAK4;
  vector<JetCorrectorParameters> vecL1FastAK4, vecL2RelativeAK4, vecL3AbsoluteAK4, vecL2L3ResidualAK4;
  FactorizedJetCorrector *jecL1FastAK4, *jecL2RelativeAK4, *jecL3AbsoluteAK4, *jecL2L3ResidualAK4;
 
  JetCorrectorParameters *L1FastAK8, *L2RelativeAK8, *L3AbsoluteAK8, *L2L3ResidualAK8;
  vector<JetCorrectorParameters> vecL1FastAK8, vecL2RelativeAK8, vecL3AbsoluteAK8, vecL2L3ResidualAK8;
  FactorizedJetCorrector *jecL1FastAK8, *jecL2RelativeAK8, *jecL3AbsoluteAK8, *jecL2L3ResidualAK8;
  
  
  // std::string mFileName,mPuFileName,mPuTrigName;
  std::string mJECL1FastFileAK4, mJECL2RelativeFileAK4, mJECL3AbsoluteFileAK4, mJECL2L3ResidualFileAK4, mJECL1FastFileAK8, mJECL2RelativeFileAK8, mJECL3AbsoluteFileAK8, mJECL2L3ResidualFileAK8;
  std::string mPtResoFileAK4, mPtResoFileAK8, mPtSFFileAK4, mPtSFFileAK8;
  // ---- Jet Corrector Parameter End---- //
  
  std::string mJECUncFileAK4;
  std::vector<JetCorrectionUncertainty*> vsrc ;
  
  std::string mJECUncFileAK8;
  std::vector<JetCorrectionUncertainty*> vsrcAK8 ;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

/*
  triggerBits_(consumes<edm::TriggerResults>(pset.getParameter<edm::InputTag>("bits"))),
  triggerObjects_(consumes<pat::TriggerObjectStandAloneCollection>(pset.getParameter<edm::InputTag>("objects"))),
  triggerPrescales_(consumes<pat::PackedTriggerPrescales>(pset.getParameter<edm::InputTag>("prescales"))),
  hltPrescaleProvider_(pset, consumesCollector(), *this)
*/

Leptop::Leptop(const edm::ParameterSet& pset):
  hltPrescaleProvider_(pset, consumesCollector(), *this)
{
  //now do what ever initialization is needed
  
  edm::Service<TFileService> fs;
  
  isData    = pset.getUntrackedParameter<bool>("Data",false);
  isMC      = pset.getUntrackedParameter<bool>("MonteCarlo", false);
  isSoftDrop      = pset.getUntrackedParameter<bool>("SoftDrop_ON",false);
  isHistFill = pset.getUntrackedParameter<bool>("HistFill", true); 
  weight2 = pset.getUntrackedParameter<double>("HistWeight", 1.0);
  isReconstruct = pset.getUntrackedParameter<bool>("isRECO", true);
  theRootFileName = pset.getUntrackedParameter<string>("RootFileName");
  theHLTTag = pset.getUntrackedParameter<string>("HLTTag", "HLT");
  beta = pset.getUntrackedParameter<double>("beta",0);
  minPt = pset.getUntrackedParameter<double>("minPt",100.);
  maxEta = pset.getUntrackedParameter<double>("maxEta",3.);
  maxgenEta = pset.getUntrackedParameter<double>("maxgenEta",3.);
  AK8PtCut = pset.getUntrackedParameter<double>("AK8PtCut",250.);
  nkTsub = pset.getUntrackedParameter<int>("nkTsub",2);
  
  triggerBits_ = consumes<edm::TriggerResults> ( pset.getParameter<edm::InputTag>("bits"));
  triggerObjects_ = consumes<pat::TriggerObjectStandAloneCollection>(pset.getParameter<edm::InputTag>("objects"));
  triggerPrescales_ = consumes<pat::PackedTriggerPrescales>(pset.getParameter<edm::InputTag>("prescales"));
  
  softdropmass = pset.getUntrackedParameter<string>("softdropmass");
  tau1 = pset.getUntrackedParameter<string>("tau1");
  tau2 = pset.getUntrackedParameter<string>("tau2");
  tau3 = pset.getUntrackedParameter<string>("tau3");
  subjets = pset.getUntrackedParameter<string>("subjets");
  toptagger = pset.getUntrackedParameter<string>("toptagger");
  Wtagger = pset.getUntrackedParameter<string>("Wtagger");
  Ztagger = pset.getUntrackedParameter<string>("Ztagger");
  BBtagger = pset.getUntrackedParameter<string>("BBtagger");
  CCtagger = pset.getUntrackedParameter<string>("CCtagger");
  btag_CMVA_name = pset.getUntrackedParameter<string>("btag_CMVA_name");
  btag_CSV_name = pset.getUntrackedParameter<string>("btag_CSV_name");
  
  tok_beamspot_ = consumes<reco::BeamSpot> (pset.getParameter<edm::InputTag>("Beamspot"));
  tok_primaryVertices_ =consumes<reco::VertexCollection>( pset.getParameter<edm::InputTag>("PrimaryVertices"));
  //slimmedSecondaryVertices
  tok_sv =consumes<reco::VertexCompositePtrCandidateCollection>( pset.getParameter<edm::InputTag>("SecondaryVertices"));
  
  tok_Rho_ = consumes<double>(pset.getParameter<edm::InputTag>("PFRho"));
  
  tok_mets_= consumes<pat::METCollection> ( pset.getParameter<edm::InputTag>("PFMet"));
  tok_genmets_= consumes<reco::GenMETCollection> ( pset.getParameter<edm::InputTag>("GENMet"));
  
  tok_muons_ = consumes<edm::View<pat::Muon>> ( pset.getParameter<edm::InputTag>("Muons"));
  tok_electrons_ = consumes<edm::View<pat::Electron>> ( pset.getParameter<edm::InputTag>("Electrons"));
  tok_photons_ = consumes<edm::View<pat::Photon>>  ( pset.getParameter<edm::InputTag>("Photons"));
  
  tok_pfjetAK8s_= consumes<edm::View<pat::Jet>>( pset.getParameter<edm::InputTag>("PFJetsAK8"));
  tok_pfsubjetAK8s_= consumes<edm::View<pat::Jet>>( pset.getParameter<edm::InputTag>("PFSubJetsAK8"));
  tok_pfjetAK4s_= consumes<edm::View<pat::Jet>>( pset.getParameter<edm::InputTag>("PFJetsAK4"));
  if(isMC){
    tok_genjetAK8s_= consumes<reco::GenJetCollection>( pset.getParameter<edm::InputTag>("GENJetAK8"));
    tok_genjetAK4s_= consumes<reco::GenJetCollection>( pset.getParameter<edm::InputTag>("GENJetAK4"));
    //	  tok_genparticles_ = consumes<edm::View<pat::PackedGenParticle>>( pset.getParameter<edm::InputTag>("GenParticles"));
    tok_genparticles_ = consumes<std::vector<reco::GenParticle>>( pset.getParameter<edm::InputTag>("GenParticles"));
  }
  
  //tag_mvaEleIDSpring16GeneralPurposeV1wp90_reco = pset.getParameter<edm::InputTag>("label_mvaEleIDSpring16GeneralPurposeV1wploose_reco");
  //tok_mvaEleIDSpring16GeneralPurposeV1wp90_reco = consumes<edm::ValueMap <bool> >(tag_mvaEleIDSpring16GeneralPurposeV1wp90_reco);
  
  //  tag_mvaEleIDSpring16GeneralPurposeV1wp90_noIso_reco = pset.getParameter<edm::InputTag>("label_mvaEleIDSpring16GeneralPurposeV1wploose_noIso_reco");
  //tok_mvaEleIDSpring16GeneralPurposeV1wp90_noIso_reco = consumes<edm::ValueMap <bool> >(tag_mvaEleIDSpring16GeneralPurposeV1wp90_noIso_reco);
 
  tag_mvaPhoIDSpring16GeneralPurposeV1wp90_reco = pset.getParameter<edm::InputTag>("label_mvaPhoIDSpring16GeneralPurposeV1wploose_reco");
  tok_mvaPhoIDSpring16GeneralPurposeV1wp90_reco = consumes<edm::ValueMap <bool> >(tag_mvaPhoIDSpring16GeneralPurposeV1wp90_reco);
  
  mJECL1FastFileAK4         = pset.getParameter<std::string>("jecL1FastFileAK4");
  mJECL1FastFileAK8         = pset.getParameter<std::string>("jecL1FastFileAK8");
  mJECL2RelativeFileAK4     = pset.getParameter<std::string>("jecL2RelativeFileAK4");
  mJECL2RelativeFileAK8     = pset.getParameter<std::string>("jecL2RelativeFileAK8");
  mJECL3AbsoluteFileAK4     = pset.getParameter<std::string>("jecL3AbsoluteFileAK4");
  mJECL3AbsoluteFileAK8     = pset.getParameter<std::string> ("jecL3AbsoluteFileAK8");
  mJECL2L3ResidualFileAK4   = pset.getParameter<std::string> ("jecL2L3ResidualFileAK4");
  mJECL2L3ResidualFileAK8   = pset.getParameter<std::string> ("jecL2L3ResidualFileAK8");
  
  mPtResoFileAK4  = pset.getParameter<std::string>("PtResoFileAK4");
  mPtResoFileAK8  = pset.getParameter<std::string>("PtResoFileAK8");
  mPtSFFileAK4  = pset.getParameter<std::string>("PtSFFileAK4");
  mPtSFFileAK8  = pset.getParameter<std::string>("PtSFFileAK8");
  
  mJECUncFileAK4 = pset.getParameter<std::string>("JECUncFileAK4");
  mJECUncFileAK8 = pset.getParameter<std::string>("JECUncFileAK8");
  
  if(isMC){    
    tok_HepMC = consumes<HepMCProduct>(pset.getParameter<edm::InputTag>("Generator"));
    tok_wt_ = consumes<GenEventInfoProduct>(pset.getParameter<edm::InputTag>("Generator")) ;
    pileup_ = consumes<std::vector<PileupSummaryInfo> >(pset.getParameter<edm::InputTag>("slimmedAddPileupInfo"));
  } 
  
  beta = pset.getUntrackedParameter<double>("beta",0.);
  z_cut = pset.getUntrackedParameter<double>("z_cut",0.1); 
  nprong = pset.getUntrackedParameter<int>("prongno",1);
  
  theFile = new TFile(theRootFileName.c_str(), "RECREATE");
  theFile->cd();
  
  //  T1 = fs->make<TTree>("T1","PFandgenjetAK8AK8s") ;
  T1 = new TTree("T1", "WPrimeNtuple");
  
  T1->Branch("irun", &irun, "irun/I");  
  T1->Branch("ilumi", &ilumi, "ilumi/I");  
  
  T1->Branch("ievt", &ievt, "ievt/i");
  T1->Branch("nprim", &nprim, "nprim/I");
  T1->Branch("nvert", &nvert, "nvert/I");  
  T1->Branch("ndofct", &ndofct, "ndofct/I");
  T1->Branch("nchict", &nchict, "nchict/I");
  
  T1->Branch("Rho", &Rho, "Rho/D") ;
  
  T1->Branch("event_weight", &event_weight, "event_weight/D") ;
  T1->Branch("qscale",&qscale,"qscale/F");
  T1->Branch("npu_vert",&npu_vert,"npu_vert/I");
  
  T1->Branch("trig_value",&trig_value,"trig_value/I");  
  T1->Branch("ihlt01",&ihlt01,"ihlt01/I");
  T1->Branch("ihlt02",&ihlt02,"ihlt02/I");
  T1->Branch("ihlt03",&ihlt03,"ihlt03/I");
  T1->Branch("ihlt04",&ihlt04,"ihlt04/I");
  T1->Branch("ihlt05",&ihlt05,"ihlt05/I");
  T1->Branch("ihlt06",&ihlt06,"ihlt06/I");
  T1->Branch("ihlt07",&ihlt07,"ihlt07/I");
  T1->Branch("ihlt08",&ihlt08,"ihlt08/I");
  T1->Branch("ihlt09",&ihlt09,"ihlt09/I");
  T1->Branch("ihlt10",&ihlt10,"ihlt10/I");
  T1->Branch("ihlt11",&ihlt01,"ihlt11/I");
  T1->Branch("ihlt12",&ihlt02,"ihlt12/I");
  T1->Branch("ihlt13",&ihlt03,"ihlt13/I");
  T1->Branch("ihlt14",&ihlt04,"ihlt14/I");
  T1->Branch("ihlt15",&ihlt05,"ihlt15/I");
  T1->Branch("ihlt16",&ihlt06,"ihlt16/I");
  T1->Branch("ihlt17",&ihlt07,"ihlt17/I");
  
  T1->Branch("prescl01",&prescl01,"prescl01/F");
  T1->Branch("prescl02",&prescl02,"prescl02/F");
  T1->Branch("prescl03",&prescl03,"prescl03/F");
  T1->Branch("prescl04",&prescl04,"prescl04/F");
  T1->Branch("prescl05",&prescl05,"prescl05/F");
  T1->Branch("prescl06",&prescl06,"prescl06/F");
  T1->Branch("prescl07",&prescl07,"prescl07/F");
  T1->Branch("prescl08",&prescl08,"prescl08/F");
  T1->Branch("prescl09",&prescl09,"prescl09/F");
  T1->Branch("prescl10",&prescl10,"prescl10/F");
  T1->Branch("prescl11",&prescl01,"prescl11/F");
  T1->Branch("prescl12",&prescl02,"prescl12/F");
  T1->Branch("prescl13",&prescl03,"prescl13/F");
  T1->Branch("prescl14",&prescl04,"prescl14/F");
  T1->Branch("prescl15",&prescl05,"prescl15/F");
  T1->Branch("prescl16",&prescl06,"prescl16/F");
  T1->Branch("prescl17",&prescl07,"prescl17/F");

  
  T1->Branch("ntrigobjs",&ntrigobjs,"ntrigobjs/I");
  T1->Branch("trigobjpt",trigobjpt,"trigobjpt[ntrigobjs]/F");
  T1->Branch("trigobjeta",trigobjeta,"trigobjeta[ntrigobjs]/F");
  T1->Branch("trigobjphi",trigobjphi,"trigobjphi[ntrigobjs]/F");
  T1->Branch("trigobje",trigobje,"trigobje[ntrigobjs]/F");
  T1->Branch("trigobjHLT",trigobjHLT,"trigobjHLT[ntrigobjs]/O");
  T1->Branch("trigobjL1",trigobjL1,"trigobjL1[ntrigobjs]/O");
  T1->Branch("trigobjBoth",trigobjBoth,"trigobjBoth[ntrigobjs]/O");
  T1->Branch("trigobjIhlt",trigobjIhlt,"trigobjIhlt[ntrigobjs]/I");
  
  T1->Branch("PFMET",&miset,"miset/F") ;
  T1->Branch("PFMETPhi",&misphi,"misphi/F") ;
  T1->Branch("MisEtSig",&misetsig,"misetsig/F");/*
  T1->Branch("PFCHMET",&chmiset,"chmiset/F") ;
  T1->Branch("PFCHMETPhi",&chmisphi,"chmisphi/F");
  T1->Branch("CHMisEtSig",&chmisetsig,"chmisetsig/F");*/
  T1->Branch("sumEt",&sumEt,"sumEt/F");

  T1->Branch("npfjetAK8",&npfjetAK8, "npfjetAK8/I"); 
  T1->Branch("pfjetAK8looseID",&pfjetAK8looseID,"pfjetAK8looseID[npfjetAK8]/O");
  T1->Branch("pfjetAK8tightID",&pfjetAK8tightID,"pfjetAK8tightID[npfjetAK8]/O");
  T1->Branch("pfjetAK8tightLVID",&pfjetAK8tightLVID,"pfjetAK8tightLVID[npfjetAK8]/O");
  T1->Branch("pfjetAK8pt",pfjetAK8pt,"pfjetAK8pt[npfjetAK8]/F");
  T1->Branch("pfjetAK8y",pfjetAK8y,"pfjetAK8y[npfjetAK8]/F");
  T1->Branch("pfjetAK8eta",pfjetAK8eta,"pfjetAK8eta[npfjetAK8]/F");
  T1->Branch("pfjetAK8phi",pfjetAK8phi,"pfjetAK8phi[npfjetAK8]/F");
  T1->Branch("pfjetAK8mass",pfjetAK8mass,"pfjetAK8mass[npfjetAK8]/F");
  T1->Branch("pfjetAK8JEC",pfjetAK8JEC,"pfjetAK8JEC[npfjetAK8]/F");
  T1->Branch("pfjetAK8JECL1",pfjetAK8JECL1,"pfjetAK8JECL1[npfjetAK8]/F");
  T1->Branch("pfjetAK8JECL2",pfjetAK8JECL2,"pfjetAK8JECL2[npfjetAK8]/F");
  T1->Branch("pfjetAK8JECL3",pfjetAK8JECL3,"pfjetAK8JECL3[npfjetAK8]/F");
  T1->Branch("pfjetAK8JECL2L3",pfjetAK8JECL2L3,"pfjetAK8JECL2L3[npfjetAK8]/F");
  T1->Branch("pfjetAK8btag_CMVA",pfjetAK8btag_CMVA,"pfjetAK8btag_CMVA[npfjetAK8]/F");
  T1->Branch("pfjetAK8btag_CSV",pfjetAK8btag_CSV,"pfjetAK8btag_CSV[npfjetAK8]/F");
  T1->Branch("pfjetAK8btag_DeepCSV",pfjetAK8btag_DeepCSV,"pfjetAK8btag_DeepCSV[npfjetAK8]/F");
  T1->Branch("pfjetAK8btag_DeepFlav",pfjetAK8btag_DeepFlav,"pfjetAK8btag_DeepFlav[npfjetAK8]/F");
  T1->Branch("pfjetAK8DeepTag_TvsQCD",pfjetAK8DeepTag_TvsQCD,"pfjetAK8DeepTag_TvsQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8DeepTag_WvsQCD",pfjetAK8DeepTag_WvsQCD,"pfjetAK8DeepTag_WvsQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8DeepTag_ZvsQCD",pfjetAK8DeepTag_ZvsQCD,"pfjetAK8DeepTag_ZvsQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8DeepTag_BBvsQCD",pfjetAK8DeepTag_BBvsQCD,"pfjetAK8DeepTag_BBvsQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8DeepTag_CCvsQCD",pfjetAK8DeepTag_CCvsQCD,"pfjetAK8DeepTag_CCvsQCD[npfjetAK8]/F");
  T1->Branch("pfjetAK8CHF",pfjetAK8CHF,"pfjetAK8CHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8NHF",pfjetAK8NHF,"pfjetAK8NHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8CEMF",pfjetAK8CEMF,"pfjetAK8CEMF[npfjetAK8]/F");
  T1->Branch("pfjetAK8NEMF",pfjetAK8NEMF,"pfjetAK8NEMF[npfjetAK8]/F");
  T1->Branch("pfjetAK8MUF",pfjetAK8MUF,"pfjetAK8MUF[npfjetAK8]/F");
  T1->Branch("pfjetAK8PHF",pfjetAK8PHF,"pfjetAK8PHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8EEF",pfjetAK8EEF,"pfjetAK8EEF[npfjetAK8]/F");
  T1->Branch("pfjetAK8HFHF",pfjetAK8HFHF,"pfjetAK8HFHF[npfjetAK8]/F");
  T1->Branch("pfjetAK8HFEMF",pfjetAK8HFEMF,"pfjetAK8HFEMF[npfjetAK8]/F");
  T1->Branch("pfjetAK8HOF",pfjetAK8HOF,"pfjetAK8HOF[npfjetAK8]/F");
  T1->Branch("pfjetAK8CHM",pfjetAK8CHM,"pfjetAK8CHM[npfjetAK8]/I");
  T1->Branch("pfjetAK8NHM",pfjetAK8NHM,"pfjetAK8NHM[npfjetAK8]/I");
  T1->Branch("pfjetAK8CEMM",pfjetAK8CEMM,"pfjetAK8CEMM[npfjetAK8]/I");
  T1->Branch("pfjetAK8NEMM",pfjetAK8NEMM,"pfjetAK8NEMM[npfjetAK8]/I");
  T1->Branch("pfjetAK8MUM",pfjetAK8MUM,"pfjetAK8MUM[npfjetAK8]/I");
  T1->Branch("pfjetAK8PHM",pfjetAK8PHM,"pfjetAK8PHM[npfjetAK8]/I");
  T1->Branch("pfjetAK8EEM",pfjetAK8EEM,"pfjetAK8EEM[npfjetAK8]/I");
  T1->Branch("pfjetAK8HFHM",pfjetAK8HFHM,"pfjetAK8HFHM[npfjetAK8]/I");
  T1->Branch("pfjetAK8HFEMM",pfjetAK8HFEMM,"pfjetAK8HFEMM[npfjetAK8]/I");
  T1->Branch("pfjetAK8Neucons",pfjetAK8Neucons,"pfjetAK8Neucons[npfjetAK8]/I");
  T1->Branch("pfjetAK8Chcons",pfjetAK8Chcons,"pfjetAK8Chcons[npfjetAK8]/I");
  
  T1->Branch("pfjetAK8_leppt",pfjetAK8_leppt,"pfjetAK8_leppt[npfjetAK8]/F");
  T1->Branch("pfjetAK8_lepeta",pfjetAK8_lepeta,"pfjetAK8_lepeta[npfjetAK8]/F");
  T1->Branch("pfjetAK8_lepphi",pfjetAK8_lepphi,"pfjetAK8_lepphi[npfjetAK8]/F");
  T1->Branch("pfjetAK8_lepe",pfjetAK8_lepe,"pfjetAK8_lepe[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8_bpt",pfjetAK8_bpt,"pfjetAK8_bpt[npfjetAK8]/F");
  T1->Branch("pfjetAK8_beta",pfjetAK8_beta,"pfjetAK8_beta[npfjetAK8]/F");
  T1->Branch("pfjetAK8_bphi",pfjetAK8_bphi,"pfjetAK8_bphi[npfjetAK8]/F");
  T1->Branch("pfjetAK8_be",pfjetAK8_be,"pfjetAK8_be[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8_nupt",pfjetAK8_nupt,"pfjetAK8_nupt[npfjetAK8]/F");
  T1->Branch("pfjetAK8_nueta",pfjetAK8_nueta,"pfjetAK8_nueta[npfjetAK8]/F");
  T1->Branch("pfjetAK8_nuphi",pfjetAK8_nuphi,"pfjetAK8_nuphi[npfjetAK8]/F");
  T1->Branch("pfjetAK8_nue",pfjetAK8_nue,"pfjetAK8_nue[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8_bbyW_E",pfjetAK8_bbyW_E,"pfjetAK8_bbyW_E[npfjetAK8]/F");
  T1->Branch("pfjetAK8_Kfactor",pfjetAK8_Kfactor,"pfjetAK8_Kfactor[npfjetAK8]/F");
  T1->Branch("pfjetAK8_Rnew",pfjetAK8_Rnew,"pfjetAK8_Rnew[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8reso",pfjetAK8reso,"pfjetAK8reso[npfjetAK8]/F");
  T1->Branch("pfjetAK8resoup",pfjetAK8resoup,"pfjetAK8resoup[npfjetAK8]/F");
  T1->Branch("pfjetAK8resodn",pfjetAK8resodn,"pfjetAK8resodn[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8jesup_pu",pfjetAK8jesup_pu,"pfjetAK8jesup_pu[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_rel",pfjetAK8jesup_rel,"pfjetAK8jesup_rel[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_scale",pfjetAK8jesup_scale,"pfjetAK8jesup_scale[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesup_total",pfjetAK8jesup_total,"pfjetAK8jesup_total[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_pu",pfjetAK8jesdn_pu,"pfjetAK8jesdn_pu[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_rel",pfjetAK8jesdn_rel,"pfjetAK8jesdn_rel[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_scale",pfjetAK8jesdn_scale,"pfjetAK8jesdn_scale[npfjetAK8]/F");
  T1->Branch("pfjetAK8jesdn_total",pfjetAK8jesdn_total,"pfjetAK8jesdn_total[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8chrad",pfjetAK8chrad,"pfjetAK8chrad[npfjetAK8]/F");
  T1->Branch("pfjetAK8axis2",pfjetAK8axis2,"pfjetAK8axis2[npfjetAK8]/F");
  T1->Branch("pfjetAK8pTD",pfjetAK8pTD,"pfjetAK8pTD[npfjetAK8]/F");
  T1->Branch("pfjetAK8leadtrackpt",pfjetAK8leadtrackpt,"pfjetAK8leadtrackpt[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8sdmass",pfjetAK8sdmass,"pfjetAK8sdmass[npfjetAK8]/F");
  T1->Branch("pfjetAK8tau1",pfjetAK8tau1,"pfjetAK8tau1[npfjetAK8]/F");
  T1->Branch("pfjetAK8tau2",pfjetAK8tau2,"pfjetAK8tau2[npfjetAK8]/F");
  T1->Branch("pfjetAK8tau3",pfjetAK8tau3,"pfjetAK8tau3[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8sub1pt",pfjetAK8sub1pt,"pfjetAK8sub1pt[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1eta",pfjetAK8sub1eta,"pfjetAK8sub1eta[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1phi",pfjetAK8sub1phi,"pfjetAK8sub1phi[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1mass",pfjetAK8sub1mass,"pfjetAK8sub1mass[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1btag",pfjetAK8sub1btag,"pfjetAK8sub1btag[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1chhadfrac",pfjetAK8sub1chhadfrac,"pfjetAK8sub1chhadfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1neuhadfrac",pfjetAK8sub1neuhadfrac,"pfjetAK8sub1neuhadfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1emfrac",pfjetAK8sub1emfrac,"pfjetAK8sub1emfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1phofrac",pfjetAK8sub1phofrac,"pfjetAK8sub1phofrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub1mufrac",pfjetAK8sub1mufrac,"pfjetAK8sub1mufrac[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8sub2pt",pfjetAK8sub2pt,"pfjetAK8sub2pt[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2eta",pfjetAK8sub2eta,"pfjetAK8sub2eta[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2phi",pfjetAK8sub2phi,"pfjetAK8sub2phi[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2mass",pfjetAK8sub2mass,"pfjetAK8sub2mass[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2btag",pfjetAK8sub2btag,"pfjetAK8sub2btag[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2chhadfrac",pfjetAK8sub2chhadfrac,"pfjetAK8sub2chhadfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2neuhadfrac",pfjetAK8sub2neuhadfrac,"pfjetAK8sub2neuhadfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2emfrac",pfjetAK8sub2emfrac,"pfjetAK8sub2emfrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2phofrac",pfjetAK8sub2phofrac,"pfjetAK8sub2phofrac[npfjetAK8]/F");
  T1->Branch("pfjetAK8sub2mufrac",pfjetAK8sub2mufrac,"pfjetAK8sub2mufrac[npfjetAK8]/F");
 
  T1->Branch("pfjetAK8elinsubpt", pfjetAK8elinsubpt, "pfjetAK8elinsubpt[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubeta", pfjetAK8elinsubeta, "pfjetAK8elinsubeta[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubphi", pfjetAK8elinsubphi, "pfjetAK8elinsubphi[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsube", pfjetAK8elinsube, "pfjetAK8elinsube[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubmass", pfjetAK8elinsubmass, "pfjetAK8elinsubmass[npfjetAK8]/F");

  T1->Branch("pfjetAK8elinsubjpt", pfjetAK8elinsubjpt, "pfjetAK8elinsubjpt[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubjeta", pfjetAK8elinsubjeta, "pfjetAK8elinsubjeta[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubjphi", pfjetAK8elinsubjphi, "pfjetAK8elinsubjphi[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubje", pfjetAK8elinsubje, "pfjetAK8elinsubje[npfjetAK8]/F");
  T1->Branch("pfjetAK8elinsubjmass", pfjetAK8elinsubjmass, "pfjetAK8elinsubjmass[npfjetAK8]/F");


  T1->Branch("pfjetAK8subhaddiff",pfjetAK8subhaddiff,"pfjetAK8subhaddiff[npfjetAK8]/F");
  T1->Branch("pfjetAK8subemdiff",pfjetAK8subemdiff,"pfjetAK8subemdiff[npfjetAK8]/F");
  T1->Branch("pfjetAK8subptdiff",pfjetAK8subptdiff,"pfjetAK8subptdiff[npfjetAK8]/F");
  
  T1->Branch("pfjetAK8lepemiso",pfjetAK8lepemiso,"pfjetAK8lepemiso[npfjetAK8]/F");
  T1->Branch("pfjetAK8lepchhadiso",pfjetAK8lepchhadiso,"pfjetAK8lepchhadiso[npfjetAK8]/F");
  T1->Branch("pfjetAK8lepneuhadiso",pfjetAK8lepneuhadiso,"pfjetAK8lepneuhadiso[npfjetAK8]/F");
 
  T1->Branch("npfjetAK4",&npfjetAK4,"npfjetAK4/I"); 
  T1->Branch("pfjetAK4looseID",&pfjetAK4looseID,"pfjetAK4looseID[npfjetAK4]/O");
  T1->Branch("pfjetAK4tightID",&pfjetAK4tightID,"pfjetAK4tightID[npfjetAK4]/O");
  T1->Branch("pfjetAK4tightLVID",&pfjetAK4tightLVID,"pfjetAK4tightLVID[npfjetAK4]/O");
  T1->Branch("pfjetAK4pt",pfjetAK4pt,"pfjetAK4pt[npfjetAK4]/F");
  T1->Branch("pfjetAK4eta",pfjetAK4eta,"pfjetAK4eta[npfjetAK4]/F");
  T1->Branch("pfjetAK4y",pfjetAK4y,"pfjetAK4y[npfjetAK4]/F");
  T1->Branch("pfjetAK4phi",pfjetAK4phi,"pfjetAK4phi[npfjetAK4]/F");
  T1->Branch("pfjetAK4mass",pfjetAK4mass,"pfjetAK4mass[npfjetAK4]/F");
  T1->Branch("pfjetAK4JEC",pfjetAK4JEC,"pfjetAK4JEC[npfjetAK4]/F");
  T1->Branch("pfjetAK4JECL1",pfjetAK4JECL1,"pfjetAK4JECL1[npfjetAK4]/F");
  T1->Branch("pfjetAK4JECL2",pfjetAK4JECL2,"pfjetAK4JECL2[npfjetAK4]/F");
  T1->Branch("pfjetAK4JECL3",pfjetAK4JECL3,"pfjetAK4JECL3[npfjetAK4]/F");
  T1->Branch("pfjetAK4JECL2L3",pfjetAK4JECL2L3,"pfjetAK4JECL2L3[npfjetAK4]/F");
  T1->Branch("pfjetAK4btag_CMVA",pfjetAK4btag_CMVA,"pfjetAK4btag_CMVA[npfjetAK4]/F");
  T1->Branch("pfjetAK4btag_CSV",pfjetAK4btag_CSV,"pfjetAK4btag_CSV[npfjetAK4]/F");
  T1->Branch("pfjetAK4btag_DeepCSV",pfjetAK4btag_DeepCSV,"pfjetAK4btag_DeepCSV[npfjetAK4]/F");
  T1->Branch("pfjetAK4btag_DeepFlav",pfjetAK4btag_DeepFlav,"pfjetAK4btag_DeepFlav[npfjetAK4]/F");
  T1->Branch("pfjetAK4btag_DeepQCD",pfjetAK4btag_DeepQCD,"pfjetAK4btag_DeepQCD[npfjetAK4]/F"); 
 
  T1->Branch("pfjetAK4reso",pfjetAK4reso,"pfjetAK4reso[npfjetAK4]/F");
  T1->Branch("pfjetAK4resoup",pfjetAK4resoup,"pfjetAK4resoup[npfjetAK4]/F");
  T1->Branch("pfjetAK4resodn",pfjetAK4resodn,"pfjetAK4resodn[npfjetAK4]/F");
  
  T1->Branch("pfjetAK4jesup_pu",pfjetAK4jesup_pu,"pfjetAK4jesup_pu[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_rel",pfjetAK4jesup_rel,"pfjetAK4jesup_rel[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_scale",pfjetAK4jesup_scale,"pfjetAK4jesup_scale[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesup_total",pfjetAK4jesup_total,"pfjetAK4jesup_total[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_pu",pfjetAK4jesdn_pu,"pfjetAK4jesdn_pu[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_rel",pfjetAK4jesdn_rel,"pfjetAK4jesdn_rel[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_scale",pfjetAK4jesdn_scale,"pfjetAK4jesdn_scale[npfjetAK4]/F");
  T1->Branch("pfjetAK4jesdn_total",pfjetAK4jesdn_total,"pfjetAK4jesdn_total[npfjetAK4]/F");
  
  T1->Branch("pfjetAK4hadronflav",pfjetAK4hadronflav,"pfjetAK4hadronflav[npfjetAK4]/I");
  T1->Branch("pfjetAK4partonflav",pfjetAK4partonflav,"pfjetAK4partonflav[npfjetAK4]/I");
//  T1->Branch("pfjetAK4partonpdg",pfjetAK4partonpdg,"pfjetAK4partonpdg[npfjetAK4]/I");
  T1->Branch("pfjetAK4qgl",pfjetAK4qgl,"pfjetAK4qgl[npfjetAK4]/F");
  T1->Branch("pfjetAK4PUID",pfjetAK4PUID,"pfjetAK4PUID[npfjetAK4]/F");
  T1->Branch("pfjetAK4GenMatch",pfjetAK4GenMatch,"pfjetAK4GenMatch/I");
  
  if(isMC){
    
  T1->Branch("GENMET",&genmiset,"genmiset/F") ;
  T1->Branch("GENMETPhi",&genmisphi,"genmisphi/F") ;
  T1->Branch("GENMETSig",&genmisetsig,"genmisetsig/F") ;
  
  T1->Branch("ngenjetAK8",&ngenjetAK8, "ngenjetAK8/I");
  T1->Branch("genjetAK8pt",genjetAK8pt,"genjetAK8pt[ngenjetAK8]/F");
  T1->Branch("genjetAK8y",genjetAK8y,"genjetAK8y[ngenjetAK8]/F");
  T1->Branch("genjetAK8phi",genjetAK8phi,"genjetAK8phi[ngenjetAK8]/F");
  T1->Branch("genjetAK8mass",genjetAK8mass,"genjetAK8mass[ngenjetAK8]/F");
  
  T1->Branch("genjetAK8sdmass",genjetAK8sdmass,"genjetAK8sdmass[ngenjetAK8]/F");
  T1->Branch("genjetAK8btag",genjetAK8btag,"genjetAK8btag[ngenjetAK8]/F");
  T1->Branch("genjetAK8tau1",genjetAK8tau1,"genjetAK8tau1[ngenjetAK8]/F");
  T1->Branch("genjetAK8tau2",genjetAK8tau2,"genjetAK8tau2[ngenjetAK8]/F");
  T1->Branch("genjetAK8tau3",genjetAK8tau3,"genjetAK8tau3[ngenjetAK8]/F");
  T1->Branch("genjetAK8chrad",genjetAK8chrad,"genjetAK8chrad[ngenjetAK8]/F");
   
  T1->Branch("genjetAK8sub1pt",genjetAK8sub1pt,"genjetAK8sub1pt[ngenjetAK8]/F");
  T1->Branch("genjetAK8sub1y",genjetAK8sub1y,"genjetAK8sub1y[ngenjetAK8]/F");
  T1->Branch("genjetAK8sub1phi",genjetAK8sub1phi,"genjetAK8sub1phi[ngenjetAK8]/F");
  T1->Branch("genjetAK8sub1mass",genjetAK8sub1mass,"genjetAK8sub1mass[ngenjetAK8]/F");
  T1->Branch("genjetAK8sub1hadfrac",genjetAK8sub1hadfrac,"genjetAK8sub1hadfrac[ngenjetAK8]/F");
  T1->Branch("genjetAK8sub1emfrac",genjetAK8sub1emfrac,"genjetAK8sub1emfrac[ngenjetAK8]/F");
  T1->Branch("genjetAK8sub2pt",genjetAK8sub2pt,"genjetAK8sub2pt[ngenjetAK8]/F");
  T1->Branch("genjetAK8sub2y",genjetAK8sub2y,"genjetAK8sub2y[ngenjetAK8]/F");
  T1->Branch("genjetAK8sub2phi",genjetAK8sub2phi,"genjetAK8sub2phi[ngenjetAK8]/F");
  T1->Branch("genjetAK8sub2mass",genjetAK8sub2mass,"genjetAK8sub2mass[ngenjetAK8]/F");
  T1->Branch("genjetAK8sub2hadfrac",genjetAK8sub2hadfrac,"genjetAK8sub2hadfrac[ngenjetAK8]/F");
  T1->Branch("genjetAK8sub2emfrac",genjetAK8sub2emfrac,"genjetAK8sub2emfrac[ngenjetAK8]/F");
 
  T1->Branch("ngenjetAK4",&ngenjetAK4, "ngenjetAK4/I");
  T1->Branch("genjetAK4pt",genjetAK4pt,"genjetAK4pt[ngenjetAK4]/F");
  T1->Branch("genjetAK4y",genjetAK4y,"genjetAK4y[ngenjetAK4]/F");
  T1->Branch("genjetAK4phi",genjetAK4phi,"genjetAK4phi[ngenjetAK4]/F");
  T1->Branch("genjetAK4mass",genjetAK4mass,"genjetAK4mass[ngenjetAK4]/F");
  T1->Branch("genjetAK4btag",genjetAK4btag,"genjetAK4btag[ngenjetAK4]/F");
  
  T1->Branch("ngenparticles",&ngenparticles, "ngenparticles/I");
  T1->Branch("genpartstatus",genpartstatus,"genpartstatus[ngenparticles]/I");
  T1->Branch("genpartpdg",genpartpdg,"genpartpdg[ngenparticles]/I");
  T1->Branch("genpartmompdg",genpartmompdg,"genpartmompdg[ngenparticles]/I");
  //  T1->Branch("genpartmomid",genpartmomid,"genpartmomid[ngenparticles]/I");
  T1->Branch("genpartdaugno",genpartdaugno,"genpartdaugno[ngenparticles]/I");
  T1->Branch("genpartfromhard",genpartfromhard,"genpartfromhard[ngenparticles]/O");
  T1->Branch("genpartfromhardbFSR",genpartfromhardbFSR,"genpartfromhardbFSR[ngenparticles]/O");
  T1->Branch("genpartisPromptFinalState",genpartisPromptFinalState,"genpartisPromptFinalState[ngenparticles]/O");
  T1->Branch("genpartisLastCopyBeforeFSR",genpartisLastCopyBeforeFSR,"genpartisLastCopyBeforeFSR[ngenparticles]/O");
  T1->Branch("genpartpt",genpartpt,"genpartpt[ngenparticles]/F");
  T1->Branch("genparteta",genparteta,"genparteta[ngenparticles]/F");
  T1->Branch("genpartphi",genpartphi,"genpartphi[ngenparticles]/F");
  T1->Branch("genpartm",genpartm,"genpartm[ngenparticles]/F");
  T1->Branch("genpartq",genpartq,"genpartq[ngenparticles]/F");
  
 
  } //isMC


  T1->Branch("nmuons",&nmuons,"nmuons/I");
  T1->Branch("muonisPF",muonisPF,"muonisPF[nmuons]/O");
  T1->Branch("muonisGL",muonisGL,"muonisPF[nmuons]/O");
  T1->Branch("muonisTRK",muonisTRK,"muonisTRK[nmuons]/O");
  T1->Branch("muonisLoose",muonisLoose,"muonisLoose[nmuons]/O");
  T1->Branch("muonisGoodGL",muonisGoodGL,"muonisGoodGL[nmuons]/O");
  T1->Branch("muonisMed",muonisMed,"muonisMed[nmuons]/O");
  T1->Branch("muonpt",muonpt,"muonpt[nmuons]/F");
  T1->Branch("muonp",muonp,"muonp[nmuons]/F");
  T1->Branch("muone",muone,"muone[nmuons]/F");
  T1->Branch("muoneta",muoneta,"muoneta[nmuons]/F");
  T1->Branch("muonphi",muonphi,"muonphi[nmuons]/F");
  T1->Branch("muondrbm",muondrbm,"muondrbm[nmuons]/F");
  T1->Branch("muontrkvtx",muontrkvtx,"muontrkvtx[nmuons]/F");
  T1->Branch("muondz",muondz,"muondz[nmuons]/F");
  T1->Branch("muonpter",muonpter,"muonpter[nmuons]/F");
  T1->Branch("muonchi",muonchi,"muonchi[nmuons]/F");
  T1->Branch("muonndf",muonndf,"muonndf[nmuons]/I");
  T1->Branch("muonecal",muonecal,"muonecal[nmuons]/F");
  T1->Branch("muonhcal",muonhcal,"muonhcal[nmuons]/F");
  T1->Branch("muonemiso",muonemiso,"muonemiso[nmuons]/F");
  T1->Branch("muonhadiso",muonhadiso,"muonhadiso[nmuons]/F");
  T1->Branch("muonpfiso",muonpfiso,"muonpfiso[nmuons]/F");
  T1->Branch("muontkpt03",muontkpt03,"muontkpt03[nmuons]/F");
  T1->Branch("muontkpt05",muontkpt05,"muontkpt05[nmuons]/F");
  T1->Branch("muonposmatch",muonposmatch,"muonposmatch[nmuons]/F");
  T1->Branch("muontrkink",muontrkink,"muontrkink[nmuons]/F");
  T1->Branch("muonsegcom",muonsegcom,"muonsegcom[nmuons]/F");
  T1->Branch("muonthit",muonhit,"muonhit[nmuons]/F");
  T1->Branch("muonpixhit",muonpixhit,"muonpixhit[nmuons]/F");
  T1->Branch("muonmst",muonmst,"muonmst[nmuons]/F");
  T1->Branch("muontrklay",muontrklay,"muontrklay[nmuons]/F"); 
  T1->Branch("muonvalfrac",muonvalfrac,"muonvalfrac[nmuons]/F"); 
 
 
  T1->Branch("nelecs",&nelecs,"nelecs/I");

  T1->Branch("elsupcl_eta",&elsupcl_eta,"elsupcl_eta[nelecs]/F");
  T1->Branch("elsupcl_phi",&elsupcl_phi,"elsupcl_phi[nelecs]/F");
  T1->Branch("elsupcl_rawE",&elsupcl_rawE,"elsupcl_rawE[nelecs]/F");
  T1->Branch("elpt",elpt,"elpt[nelecs]/F");
  //new 20 variables added//
  T1->Branch("elsigmaieta", elsigmaieta, "elsigmaieta[nelecs]/F");
  T1->Branch("elsigmaiphi", elsigmaiphi, "elsigmaiphi[nelecs]/F");
  T1->Branch("elr9full", elr9full, "elr9full[nelecs]/F");
  T1->Branch("elsupcl_etaw", elsupcl_etaw, "elsupcl_etaw[nelecs]/F");
  T1->Branch("elsupcl_phiw", elsupcl_phiw, "elsupcl_phiw[nelecs]/F");
  T1->Branch("elhcaloverecal", elhcaloverecal, "elhcaloverecal[nelecs]/F");
  T1->Branch("elcloctftrkn", elcloctftrkn, "elcloctftrkn[nelecs]/F");
  T1->Branch("elcloctftrkchi2", elcloctftrkchi2, "elcloctftrkchi2[nelecs]/F");
  T1->Branch("ele1x5bye5x5", ele1x5bye5x5, "ele1x5bye5x5[nelecs]/F");
  T1->Branch("elnormchi2", elnormchi2, "elnormchi2[nelecs]/F");
  T1->Branch("elhitsmiss", elhitsmiss, "elhitsmiss[nelecs]/F");
  T1->Branch("eltrkmeasure", eltrkmeasure, "eltrkmeasure[nelecs]/F");
  T1->Branch("elconvtxprob", elconvtxprob, "elconvtxprob[nelecs]/F");
  T1->Branch("elecloverpout", elecloverpout, "elecloverpout[nelecs]/F");
  T1->Branch("elecaletrkmomentum", elecaletrkmomentum, "elecaletrkmomentum[nelecs]/F");
  T1->Branch("eldeltaetacltrkcalo", eldeltaetacltrkcalo, "eldeltaetacltrkcalo[nelecs]/F");
  T1->Branch("elsupcl_preshvsrawe", elsupcl_preshvsrawe, "elsupcl_preshvsrawe[nelecs]/F");
  T1->Branch("elpfisolsumphet", elpfisolsumphet, "elpfisolsumphet[nelecs]/F");
  T1->Branch("elpfisolsumchhadpt", elpfisolsumchhadpt, "elpfisolsumchhadpt[nelecs]/F");
  T1->Branch("elpfsiolsumneuhadet", elpfsiolsumneuhadet, "elpfsiolsumneuhadet[nelecs]/F");
  ///20 variables addition ended//
  T1->Branch("eleta",eleta,"eleta[nelecs]/F");
  T1->Branch("elphi",elphi,"elphi[nelecs]/F");
  T1->Branch("elp",elp,"elp[nelecs]/F");
  T1->Branch("ele",ele,"ele[nelecs]/F");
  T1->Branch("elmvaid",elmvaid,"elmvaid[nelecs]/O");
  T1->Branch("elmvaid_noIso",elmvaid_noIso,"elmvaid_noIso[nelecs]/O");
  T1->Branch("eldxy",eldxy,"eldxy[nelecs]/F");
  T1->Branch("eldxy_sv",eldxy_sv,"eldxy_sv[nelecs]/F");
  T1->Branch("eldz",eldz,"eldz[nelecs]/F");
  T1->Branch("elhovere",elhovere,"elhovere[nelecs]/F");
  T1->Branch("elchi",elchi,"elchi[nelecs]/F");
  T1->Branch("elndf",elndf,"elndf[nelecs]/I");
  T1->Branch("eltkpt03",eltkpt03,"eltkpt03[nelecs]/F");
//  T1->Branch("elemiso03",elemiso03,"elemiso03[nelecs]/F");
//  T1->Branch("elhadiso03",elhadiso03,"elhadiso03[nelecs]/F");
  T1->Branch("eltkpt04",eltkpt04,"eltkpt04[nelecs]/F");
  T1->Branch("elemiso04",elemiso04,"elemiso04[nelecs]/F");
  T1->Branch("elhadiso04",elhadiso04,"elhadiso04[nelecs]/F");
  T1->Branch("eletain",eletain,"eletain[nelecs]/F");
  T1->Branch("elphiin",elphiin,"elphiin[nelecs]/F");
  //T1->Branch("elsceta",elsceta,"elsceta[nelecs]/F");
  T1->Branch("elfbrem",elfbrem,"elfbrem[nelecs]/F");
  T1->Branch("elhadisodepth03",elhadisodepth03,"elhadisodepth03[nelecs]/F");
  T1->Branch("eleoverp",eleoverp,"eleoverp[nelecs]/F");
  T1->Branch("elietaieta",elietaieta,"elietaieta[nelecs]/F");
  T1->Branch("elmisshits",elmisshits,"elmisshits[nelecs]/F");
  T1->Branch("elchhadiso",elchhadiso,"elchhadiso[nelecs]/F");
  T1->Branch("elneuhadiso",elneuhadiso,"elneuhadiso[nelecs]/F");
  T1->Branch("elphoiso",elphoiso,"elphoiso[nelecs]/F");
  T1->Branch("elpuchhadiso",elpuchhadiso,"elpuchhadiso[nelecs]/F");
  T1->Branch("elpfiso",elpfiso,"elpfiso[nelecs]/F");
  T1->Branch("elconvdist",elconvdist,"elconvdist[nelecs]/F");
  T1->Branch("elconvdoct",elconvdoct,"elconvdoct[nelecs]/F");
  
  T1->Branch("nphotons",&nphotons,"nphotons/I");
  T1->Branch("phoe",phoe,"phoe[nphotons]/F");
  T1->Branch("phoeta",phoeta,"phoeta[nphotons]/F");
  T1->Branch("phophi",phophi,"phophi[nphotons]/F");
  T1->Branch("phomvaid",phomvaid,"phomvaid[nphotons]/O");
  T1->Branch("phoe1by9",phoe1by9,"phoe1by9[nphotons]/F");
  T1->Branch("phoe9by25",phoe9by25,"phoe9by25[nphotons]/F");
  T1->Branch("photrkiso",photrkiso,"photrkiso[nphotons]/F");
  T1->Branch("phoemiso",phoemiso,"phoemiso[nphotons]/F");
  T1->Branch("phohadiso",phohadiso,"phohadiso[nphotons]/F");
  T1->Branch("phochhadiso",phochhadiso,"phochhadiso[nphotons]/F");
  T1->Branch("phoneuhadiso",phoneuhadiso,"phoneuhadiso[nphotons]/F");
  T1->Branch("phophoiso",phophoiso,"phophoiso[nphotons]/F");
  T1->Branch("phoPUiso",phoPUiso,"phoPUiso[nphotons]/F");
  T1->Branch("phohadbyem",phohadbyem,"phohadbyem[nphotons]/F");
  T1->Branch("phoietaieta",phoietaieta,"phoietaieta[nphotons]/F");
  
  Nevt=0;
  ncnt = 0;
  irunold = -1;
  
}


Leptop::~Leptop()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
Leptop::analyze(const edm::Event& iEvent, const edm::EventSetup& pset) {

  using namespace edm;
  Nevt++;

  irun = iEvent.id().run();
  ilumi = iEvent.luminosityBlock();
  
  ievt = iEvent.id().event();
  
  //if (Nevt%100==1)cout <<"Leptop::analyze "<<Nevt<<" "<<iEvent.id().run()<<" "<<iEvent.id().event()<<endl;
  //cout <<"Leptop::analyze "<<Nevt<<" "<<iEvent.id().run()<<" "<<iEvent.id().event()<<endl;
  //  HLTConfigProvider const&  hltConfig_ = hltPrescaleProvider_.hltConfigProvider(); 
  
   wtfact = 1.;
   
   if(isMC){
     edm::Handle<GenEventInfoProduct>eventinfo ;  
     iEvent.getByToken(tok_wt_,eventinfo) ;
     
     if (eventinfo.isValid()){
       event_weight = eventinfo->weight();
       qscale = eventinfo->qScale();
     }
     
     wtfact *= event_weight;
   }
   
   Handle<VertexCollection> primaryVertices;
   iEvent.getByToken(tok_primaryVertices_, primaryVertices);
   
   edm::Handle<reco::VertexCollection> vertexHandle;
   iEvent.getByToken(tok_primaryVertices_, vertexHandle);
   reco::Vertex vertex = vertexHandle->at(0);
   
   if (primaryVertices.isValid()) {
     int ndofct_org=0;
     int nchict_org=0;
     int nvert_org = 0;
     for (reco::VertexCollection::const_iterator vert=primaryVertices->begin(); vert<primaryVertices->end(); vert++) {
       nvert_org++;
       if (vert->isValid() && !vert->isFake()) {
	 if (vert->ndof()>7) {
	   ndofct_org++;
	   if (vert->normalizedChi2()<5) nchict_org++;
	 }
       }
     }
     nprim = min(99,nvert_org) + 100*min(99,ndofct_org) + 10000*min(99,nchict_org);

     nvert = nvert_org;
     nchict = nchict_org;
     ndofct = ndofct_org;
     
   } else { nprim = 0;}
   
   reco::TrackBase::Point beamPoint(0,0, 0);
   edm::Handle<reco::BeamSpot> beamSpotH;
   
   iEvent.getByToken(tok_beamspot_, beamSpotH);  //Label("offlineBeamSpot",beamSpotH);
   if (beamSpotH.isValid()){
     beamPoint = beamSpotH->position();
   }
   
   npu_vert = 0;
   
   edm::Handle<reco::VertexCompositePtrCandidateCollection> svin;
   iEvent.getByToken(tok_sv,svin);
   
   if (isMC) {
     
     edm::Handle<std::vector<PileupSummaryInfo> > PupInfo;
     iEvent.getByToken(pileup_, PupInfo);
     int npu = -1;
     if (PupInfo.isValid()) {
       std::vector<PileupSummaryInfo>::const_iterator PVI;
       for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
                if (PVI->getBunchCrossing()==0) {
		  npu = PVI->getPU_NumInteractions();
		  break;
                }
       }
     }
     
     npu_vert = npu;
     
  }//isMC
   
   Handle<double> Rho_PF;
   
   iEvent.getByToken(tok_Rho_,Rho_PF);
   Rho = *Rho_PF;
   
   const char* variab1;
   
   edm::Handle<edm::TriggerResults> trigRes;
   iEvent.getByToken(triggerBits_, trigRes);
   
   const edm::TriggerNames &names = iEvent.triggerNames(*trigRes);
   
   edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
   iEvent.getByToken(triggerObjects_, triggerObjects);
   
   edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
   iEvent.getByToken(triggerPrescales_, triggerPrescales);
   
   // Trigger Selection;
   //  cout<<" prescale set "<<hltPrescaleProvider_.prescaleSet(iEvent,pset)<<endl;
   int ihlttrg[nHLTmx+1]= {0};
   int iprescale[nHLTmx]= {0};
   
   for (int jk=0; jk<nHLTmx; jk++) {
     for(unsigned ij = 0; ij<trigRes->size(); ++ij) {
       std::string name = names.triggerName(ij);
       
       variab1 = name.c_str(); 
       
       if (strstr(variab1,hlt_name[jk]) && ((strlen(variab1)-strlen(hlt_name[jk]))<5))
	 {
	   if ((trigRes->accept(ij))){   //||(isMC)) {
	     ihlttrg[jk] = ihlttrg[nHLTmx] = 1;
	     iprescale[jk] = hltPrescaleProvider_.prescaleValue(iEvent,pset,name);
	   }
	 }
     }//ij     
     
   }//jk
   
   //  if (isData) {
   //    if (ihlttrg[nHLTmx]>0){
   //			wtfact = 1.0;///compres[ihlt];
   //		  } else { return ; } 
   //	}
   
   trig_value = 1;
   
   for (int jk=1; jk<(nHLTmx+1); jk++) {
     if(ihlttrg[nHLTmx-jk]>0) {
       trig_value+=(1<<jk);
     }
   }
   
   for (int ij=0; ij<nHLTmx; ij++) {
     weighttrg[ij] = wtfact;
     if (isData) { weighttrg[ij] *=compres[ij];}
   }//ij
   
   vector<triggervar> alltrgobj;
   if (trigRes.isValid()) { 
     
     const char* variab2 ;
     
     alltrgobj.clear(); 
     
     // const edm::TriggerNames &names = iEvent.triggerNames(*trigRes);
     for (pat::TriggerObjectStandAlone obj : *triggerObjects) {
       
       obj.unpackPathNames(names);
       std::vector<std::string> pathNamesAll  = obj.pathNames(false);
       
       for (unsigned ih = 0, n = pathNamesAll.size(); ih < n; ih++) {
	 variab2 = pathNamesAll[ih].c_str(); 
	 
	 for (int jk=0; jk<nHLTmx; jk++) {
	   if (strstr(variab2,hlt_name[jk]) && (strlen(variab2)-strlen(hlt_name[jk])<5)) {
	     
	     if(obj.pt()>20 && fabs(obj.eta())<3.0) {
	       
	       triggervar tmpvec1;
	       
	       tmpvec1.both = obj.hasPathName( pathNamesAll[ih], true, true );
	       tmpvec1.highl  = obj.hasPathName( pathNamesAll[ih], false, true );
	       tmpvec1.level1 = obj.hasPathName( pathNamesAll[ih], true, false );
	       tmpvec1.trg4v = HepLorentzVector(obj.px(), obj.py(), obj.pz(), obj.energy());
	       tmpvec1.prescl = 1;    //triggerPrescales->getPrescaleForIndex(ij);
	       tmpvec1.ihlt = jk;
	       alltrgobj.push_back(tmpvec1);
	       
	     }
	   }
	 }//jk 
       }//ih
     }
   }
  
   ntrigobjs = alltrgobj.size();
   if(ntrigobjs>njetmx) { ntrigobjs = njetmx; }
  if(alltrgobj.size()>0){
    for(unsigned int iht=0; iht<(alltrgobj.size()); iht++){
      trigobjpt[iht] = alltrgobj[iht].trg4v.perp();
      trigobjeta[iht] = alltrgobj[iht].trg4v.rapidity();
      trigobjphi[iht] = alltrgobj[iht].trg4v.phi();
      trigobje[iht] = alltrgobj[iht].trg4v.e();
      trigobjHLT[iht] = alltrgobj[iht].highl;
      trigobjL1[iht] = alltrgobj[iht].level1;
      trigobjBoth[iht] = alltrgobj[iht].both;
      trigobjIhlt[iht] = alltrgobj[iht].ihlt;
      if(iht == (njetmx-1)) break;
    }
  }
  
  
  miset = misphi = -1000 ;
  
  edm::Handle<pat::METCollection> pfmet_ ;
  iEvent.getByToken(tok_mets_,pfmet_) ;
  
  if(pfmet_.isValid()){
    const pat::MET &met = pfmet_->front();
    /*
      miset = pfmet_->begin()->et();
      misphi = pfmet_->begin()->phi();
      misetsig = pfmet_->begin()->significance();
      sumEt = pfmet_->begin()->sumEt() ;
      if(sumEt<1.) { sumEt = 1.; }
    */
    miset = met.corPt(); //met.pt();
    misphi = met.corPhi();//met.phi();
    misetsig = met.significance();
    sumEt = met.corSumEt();//sumEt();
    if(isMC){
      genmiset = met.genMET()->pt();
      genmisphi = met.genMET()->phi();
      genmisetsig = met.genMET()->significance();
    }
  }
  
  edm::Handle<edm::View<pat::Jet>> pfjetAK8s;
  edm::Handle<reco::GenJetCollection> genjetAK8s;
  
  JetDefinition pfjetAK8Def(antikt_algorithm,0.8,E_scheme);
  SoftDrop sd(beta,z_cut,0.8);
  
  JetDefinition jetDefkT(kt_algorithm,10,E_scheme);
  
  edm::Handle<edm::View<pat::Jet>> pfsubjetAK8s;
  
  edm::Handle<edm::View<pat::Jet>> pfjetAK4s;
  edm::Handle<reco::GenJetCollection> genjetAK4s;
  JetDefinition pfjetAK4Def(antikt_algorithm,0.4,E_scheme);
  
  //	edm::Handle<edm::View<pat::PackedGenParticle>> genparticles;
  edm::Handle<std::vector<reco::GenParticle>> genparticles;
  
  npfjetAK8 = 0;
  
  iEvent.getByToken(tok_pfjetAK8s_, pfjetAK8s);	
  if(isMC){
    iEvent.getByToken(tok_genjetAK8s_, genjetAK8s);
  }
  if(pfjetAK8s.isValid()){
    for (unsigned jet = 0; jet< pfjetAK8s->size(); jet++) {
      
      HepLorentzVector pfjetAK84v((*pfjetAK8s)[jet].correctedP4("Uncorrected").px(),(*pfjetAK8s)[jet].correctedP4("Uncorrected").py(),(*pfjetAK8s)[jet].correctedP4("Uncorrected").pz(), (*pfjetAK8s)[jet].correctedP4("Uncorrected").energy());
      HepLorentzVector tmpjetAK84v((*pfjetAK8s)[jet].px(),(*pfjetAK8s)[jet].py(),(*pfjetAK8s)[jet].pz(), (*pfjetAK8s)[jet].energy());
      
      double tmprecpt = pfjetAK84v.perp();
      if(tmprecpt<AK8PtCut) continue;
      if(tmpjetAK84v.perp()<AK8PtCut) continue;
      if(abs(pfjetAK84v.rapidity())>maxEta) continue;
      
      pfjetAK8pt[npfjetAK8] = 	tmprecpt;
      pfjetAK8y[npfjetAK8] = pfjetAK84v.rapidity();
      pfjetAK8eta[npfjetAK8] = pfjetAK84v.eta();
      pfjetAK8phi[npfjetAK8] = pfjetAK84v.phi();
      pfjetAK8mass[npfjetAK8] = (*pfjetAK8s)[jet].correctedP4("Uncorrected").mass();
      
      pfjetAK8btag_CMVA[npfjetAK8] = (*pfjetAK8s)[jet].bDiscriminator(btag_CMVA_name);
      pfjetAK8btag_CSV[npfjetAK8] = (*pfjetAK8s)[jet].bDiscriminator(btag_CSV_name);
      pfjetAK8btag_DeepCSV[npfjetAK8] = (*pfjetAK8s)[jet].bDiscriminator("pfDeepCSVJetTags:probb")+(*pfjetAK8s)[jet].bDiscriminator("pfDeepCSVJetTags:probbb");
      pfjetAK8btag_DeepFlav[npfjetAK8] = (*pfjetAK8s)[jet].bDiscriminator("pfDeepFlavourJetTags:probb") + (*pfjetAK8s)[jet].bDiscriminator("pfDeepFlavourJetTags:probbb")+(*pfjetAK8s)[jet].bDiscriminator("pfDeepFlavourJetTags:problepb");
      
      pfjetAK8DeepTag_TvsQCD[npfjetAK8] = (*pfjetAK8s)[jet].bDiscriminator(toptagger);
      pfjetAK8DeepTag_WvsQCD[npfjetAK8] = (*pfjetAK8s)[jet].bDiscriminator(Wtagger);
      pfjetAK8DeepTag_ZvsQCD[npfjetAK8] = (*pfjetAK8s)[jet].bDiscriminator(Ztagger);
      pfjetAK8DeepTag_BBvsQCD[npfjetAK8] = (*pfjetAK8s)[jet].bDiscriminator(BBtagger);
      pfjetAK8DeepTag_CCvsQCD[npfjetAK8] = (*pfjetAK8s)[jet].bDiscriminator(CCtagger);
      
      double total_cor =1;
      
      jecL1FastAK8->setJetPt(tmprecpt); jecL1FastAK8->setJetA((*pfjetAK8s)[jet].jetArea()); jecL1FastAK8->setRho(*Rho_PF);jecL1FastAK8->setJetEta(pfjetAK84v.eta());
      double corFactorL1Fast = jecL1FastAK8->getCorrection();
      total_cor *= corFactorL1Fast;
      tmprecpt = tmprecpt * corFactorL1Fast;
      pfjetAK8JECL1[npfjetAK8] = corFactorL1Fast;
      
      jecL2RelativeAK8->setJetPt(tmprecpt); jecL2RelativeAK8->setJetEta(pfjetAK84v.eta());
      double corFactorL2Relative = jecL2RelativeAK8->getCorrection();
      total_cor *= corFactorL2Relative ;
      tmprecpt = tmprecpt * corFactorL2Relative;
      pfjetAK8JECL2[npfjetAK8] = corFactorL2Relative;
      
      jecL3AbsoluteAK8->setJetPt(tmprecpt); jecL3AbsoluteAK8->setJetEta(pfjetAK84v.eta());
      double corFactorL3Absolute = jecL3AbsoluteAK8->getCorrection();
      total_cor *= corFactorL3Absolute ;
      tmprecpt = tmprecpt * corFactorL3Absolute;
      pfjetAK8JECL3[npfjetAK8] = corFactorL3Absolute;
      
      double corFactorL2L3Residual=1.;
      
      if(isData){
	jecL2L3ResidualAK8->setJetPt(tmprecpt); jecL2L3ResidualAK8->setJetEta(pfjetAK84v.eta());
	corFactorL2L3Residual = jecL2L3ResidualAK8->getCorrection();
	total_cor*= corFactorL2L3Residual;
	tmprecpt *=corFactorL2L3Residual;
      }
      
      pfjetAK8JECL2L3[npfjetAK8] = corFactorL2L3Residual;
      pfjetAK8JEC[npfjetAK8] = total_cor;
      
      if(isMC){
	
	JME::JetResolution resolution_AK8;
	resolution_AK8 = JME::JetResolution(mPtResoFileAK8.c_str());
	JME::JetResolutionScaleFactor res_sf_AK8;
	res_sf_AK8 = JME::JetResolutionScaleFactor(mPtSFFileAK8.c_str());
	
	JME::JetParameters parameters_5 = {{JME::Binning::JetPt, tmprecpt}, {JME::Binning::JetEta, pfjetAK84v.eta()}, {JME::Binning::Rho, *Rho_PF}};
	double rp_AK8 = resolution_AK8.getResolution(parameters_5);
	double gaus_rp_AK8 = gRandom->Gaus(0.,rp_AK8);
	double sf_AK8 = res_sf_AK8.getScaleFactor(parameters_5, Variation::NOMINAL);
	double sf_up_AK8= res_sf_AK8.getScaleFactor(parameters_5, Variation::UP);
	double sf_dn_AK8= res_sf_AK8.getScaleFactor(parameters_5, Variation::DOWN);
	
	bool match_AK8 = false;
	int match_gen_AK8 = -1;
	
	for (unsigned get = 0; get<(genjetAK8s->size()); get++) {
	  HepLorentzVector genjet8v((*genjetAK8s)[get].px(),(*genjetAK8s)[get].py(),(*genjetAK8s)[get].pz(), (*genjetAK8s)[get].energy());
	  if((delta2R(pfjetAK84v.eta(),pfjetAK84v.phi(),genjet8v.eta(),genjet8v.phi()) < (0.5*0.8)) &&(fabs(tmprecpt-genjet8v.perp())<(3*fabs(rp_AK8)*tmprecpt))){
	    match_AK8 = true;
	    match_gen_AK8 = get;
	    break;
	  }
	}
	
	if(match_AK8&&(match_gen_AK8>=0)){
	  pfjetAK8reso[npfjetAK8] = (sf_AK8-1.)*(tmprecpt-(*genjetAK8s)[match_gen_AK8].pt())*1./tmprecpt;
	  pfjetAK8resoup[npfjetAK8] = (sf_up_AK8-1.)*(tmprecpt-(*genjetAK8s)[match_gen_AK8].pt())*1./tmprecpt;
	  pfjetAK8resodn[npfjetAK8] = (sf_dn_AK8-1.)*(tmprecpt-(*genjetAK8s)[match_gen_AK8].pt())*1./tmprecpt;
	}else{
	  
	  pfjetAK8reso[npfjetAK8] = sqrt(max(0.,(sf_AK8*sf_AK8-1))) * gaus_rp_AK8;
	  pfjetAK8resoup[npfjetAK8] = sqrt(max(0.,(sf_up_AK8*sf_up_AK8-1))) * gaus_rp_AK8;
	  pfjetAK8resodn[npfjetAK8] = sqrt(max(0.,(sf_dn_AK8*sf_dn_AK8-1))) * gaus_rp_AK8;
	}
	
      }//isMC
      
      for(int isrc =0 ; isrc<njecmcmx; isrc++){
        double sup = 1.0 ;
	
	if((isrc>0)&&(isrc<=nsrc)){
	  JetCorrectionUncertainty *jecUnc = vsrcAK8[isrc-1];
	  jecUnc->setJetEta((*pfjetAK8s)[jet].eta());
	  jecUnc->setJetPt(tmprecpt);
	  
	  sup += jecUnc->getUncertainty(true);         
	  if(isrc==1){ pfjetAK8jesup_pu[npfjetAK8] = sup; }
	  if(isrc==2){ pfjetAK8jesup_rel[npfjetAK8] = sup; }
	  if(isrc==4){ pfjetAK8jesup_scale[npfjetAK8] = sup; }
	  if(isrc==7){ pfjetAK8jesup_total[npfjetAK8] = sup; }
	}
	else if(isrc>nsrc){
	  JetCorrectionUncertainty *jecUnc = vsrcAK8[isrc-1-nsrc];
	  jecUnc->setJetEta((*pfjetAK8s)[jet].eta());
	  jecUnc->setJetPt(tmprecpt);
	  
	  sup -= jecUnc->getUncertainty(false);
	  if(isrc==8){ pfjetAK8jesdn_pu[npfjetAK8] = sup; }
	  if(isrc==9){ pfjetAK8jesdn_rel[npfjetAK8] = sup; }
	  if(isrc==11){ pfjetAK8jesdn_scale[npfjetAK8] = sup; }
	  if(isrc==14){ pfjetAK8jesdn_total[npfjetAK8] = sup; }
	}
	
      }
      
      pfjetAK8CHF[npfjetAK8] = (*pfjetAK8s)[jet].chargedHadronEnergyFraction();
      pfjetAK8NHF[npfjetAK8] = (*pfjetAK8s)[jet].neutralHadronEnergyFraction();
      pfjetAK8CEMF[npfjetAK8] = (*pfjetAK8s)[jet].chargedEmEnergyFraction();
      pfjetAK8NEMF[npfjetAK8] = (*pfjetAK8s)[jet].neutralEmEnergyFraction();
      pfjetAK8MUF[npfjetAK8] = (*pfjetAK8s)[jet].muonEnergyFraction();
      pfjetAK8PHF[npfjetAK8] = (*pfjetAK8s)[jet].photonEnergyFraction();
      pfjetAK8EEF[npfjetAK8] = (*pfjetAK8s)[jet].electronEnergyFraction();
      pfjetAK8HFHF[npfjetAK8] = (*pfjetAK8s)[jet].HFHadronEnergyFraction();
      pfjetAK8HFEMF[npfjetAK8] = (*pfjetAK8s)[jet].HFEMEnergyFraction();
      pfjetAK8HOF[npfjetAK8] = (*pfjetAK8s)[jet].hoEnergyFraction();
      
      pfjetAK8CHM[npfjetAK8] = (*pfjetAK8s)[jet].chargedHadronMultiplicity();
      pfjetAK8NHM[npfjetAK8] = (*pfjetAK8s)[jet].neutralHadronMultiplicity();
      pfjetAK8CEMM[npfjetAK8] = (*pfjetAK8s)[jet].chargedMultiplicity() - (*pfjetAK8s)[jet].chargedHadronMultiplicity();
      pfjetAK8NEMM[npfjetAK8] = (*pfjetAK8s)[jet].neutralMultiplicity() - (*pfjetAK8s)[jet].neutralHadronMultiplicity();
      pfjetAK8MUM[npfjetAK8] = (*pfjetAK8s)[jet].muonMultiplicity();
      pfjetAK8PHM[npfjetAK8] = (*pfjetAK8s)[jet].photonMultiplicity();
      pfjetAK8EEM[npfjetAK8] = (*pfjetAK8s)[jet].electronMultiplicity();
      pfjetAK8HFHM[npfjetAK8] = (*pfjetAK8s)[jet].HFHadronMultiplicity();
      pfjetAK8HFEMM[npfjetAK8] = (*pfjetAK8s)[jet].HFEMMultiplicity();
      
      pfjetAK8Chcons[npfjetAK8] = (*pfjetAK8s)[jet].chargedMultiplicity();
      pfjetAK8Neucons[npfjetAK8] = (*pfjetAK8s)[jet].neutralMultiplicity();
      
      pfjetAK8looseID[npfjetAK8] = false;
      pfjetAK8tightID[npfjetAK8] = false;
      pfjetAK8tightLVID[npfjetAK8] = false;
      
      int NumConst = pfjetAK8Chcons[npfjetAK8] + pfjetAK8Neucons[npfjetAK8];
      double eta = pfjetAK84v.rapidity();

      //it needs rechecking as looks wrong //Debarati
      
      pfjetAK8looseID[npfjetAK8] = ((pfjetAK8NHF[npfjetAK8]<0.99 && pfjetAK8NEMF[npfjetAK8]<0.99 && NumConst>1) && ((abs(eta)<=2.4 && pfjetAK8CHF[npfjetAK8]>0 && pfjetAK8CHM[npfjetAK8]>0 && pfjetAK8CEMF[npfjetAK8]<0.99) || abs(eta)>2.4) && abs(eta)<=2.7)|| (pfjetAK8NEMF[npfjetAK8]<0.90 && pfjetAK8NEMF[npfjetAK8]>2 && abs(eta)>2.7 && abs(eta)<=3.0 )||(pfjetAK8NEMF[npfjetAK8]<0.90 && pfjetAK8NEMF[npfjetAK8]>10 && abs(eta)>3.0)?true:false ;
      
      pfjetAK8tightID[npfjetAK8] = ((pfjetAK8NHF[npfjetAK8]<0.9 && pfjetAK8NEMF[npfjetAK8]<0.9 && NumConst>1) && ((abs(eta)<=2.4 && pfjetAK8CHF[npfjetAK8]>0 && pfjetAK8CHM[npfjetAK8]>0 && pfjetAK8CEMF[npfjetAK8]<0.99) || abs(eta)>2.4) && abs(eta)<=2.7)|| (pfjetAK8NEMF[npfjetAK8]<0.90 && pfjetAK8NEMF[npfjetAK8]>2 && abs(eta)>2.7 && abs(eta)<=3.0 )||(pfjetAK8NEMF[npfjetAK8]<0.90 && pfjetAK8NEMF[npfjetAK8]>10 && abs(eta)>3.0)?true:false;
      
      pfjetAK8tightLVID[npfjetAK8] = ((pfjetAK8NHF[npfjetAK8]<0.99 && pfjetAK8NEMF[npfjetAK8]<0.99 && NumConst>1 && pfjetAK8MUF[npfjetAK8]<0.8) && ((abs(eta)<=2.4 && pfjetAK8CHF[npfjetAK8]>0 && pfjetAK8CHM[npfjetAK8]>0 && pfjetAK8CEMF[npfjetAK8]<0.99) || abs(eta)>2.4) && abs(eta)<=2.7)?true:false;
      
      //	  vector <fastjet::PseudoJet> sortedJets;
      //	  fastjet::ClusterSequence clustSeq(fjInputs, pfjetAK8Def);
      //	  fjInputs.clear();
      //	  sortedJets    = sorted_by_pt(clustSeq.inclusive_jets());
      //	  if(sortedJets.size()>0){
      //	  PseudoJet sd_jet = sd(sortedJets[0]);
      
      //	  }
      //	  sortedJets.clear();
      
      //// substructure variables
      
      pfjetAK8chrad[npfjetAK8] = 0;
      
      float sumpt = 0, sumpt2 = 0;
      float leadjtrackpt = -100; //int leadjtrackid = -1;
      
      std::vector<reco::CandidatePtr> daught((*pfjetAK8s)[jet].daughterPtrVector());
      std::sort(daught.begin(), daught.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2)
		{ return p1->pt() > p2->pt(); });
      
      for (unsigned int i2 = 0; i2< daught.size(); ++i2) {
	
	float pt2 = ((daught[i2])->pt()) * ((daught[i2])->pt());
	float delR = delta2R((*daught[i2]).rapidity(), (*daught[i2]).phi(),pfjetAK8y[npfjetAK8],pfjetAK8phi[npfjetAK8]);
	
	sumpt2 += pt2;
	sumpt += daught[i2]->pt();
	
	pfjetAK8chrad[npfjetAK8] +=  (*daught[i2]).charge() * (daught[i2])->pt() * pow(delR,1);
	
	if(fabs((*daught[i2]).charge())>0 && (daught[i2])->pt()>leadjtrackpt){
	  leadjtrackpt = (daught[i2])->pt();
	  //	  leadjtrackid = i2;
	}
	
      }
      
      daught.clear();
      
      pfjetAK8chrad[npfjetAK8] *= 1./sumpt;
      
      pfjetAK8leadtrackpt[npfjetAK8] = leadjtrackpt;
      
      pfjetAK8pTD[npfjetAK8] = (sumpt2>0) ? sqrt(sumpt2)*1./sumpt : 0;
      
      if(isSoftDrop){
	
	//	  Nsubjettiness nsub1_beta1(1,OnePass_WTA_KT_Axes(), UnnormalizedMeasure(1.));
	pfjetAK8tau1[npfjetAK8] = (*pfjetAK8s)[jet].userFloat(tau1);//"NjettinessAK8Puppi:tau1");//  nsub1_beta1(sd_jet);
	//	  Nsubjettiness nsub2_beta1(2,OnePass_WTA_KT_Axes(), UnnormalizedMeasure(1.));
	pfjetAK8tau2[npfjetAK8] = (*pfjetAK8s)[jet].userFloat(tau2);//"NjettinessAK8Puppi:tau2");// nsub2_beta1(sd_jet);
	//	  Nsubjettiness nsub3_beta1(3,OnePass_WTA_KT_Axes(), UnnormalizedMeasure(1.));
	pfjetAK8tau3[npfjetAK8] = (*pfjetAK8s)[jet].userFloat(tau3);//"NjettinessAK8Puppi:tau3");// nsub3_beta1(sd_jet);
	
	if(((*pfjetAK8s)[jet].subjets(subjets)).size()>1){   ////subjets = "SoftDropPuppi"
	  
	  pfjetAK8sdmass[npfjetAK8] = ((*pfjetAK8s)[jet].groomedMass(subjets) > 1.e-9)? (*pfjetAK8s)[jet].groomedMass(subjets) : 0;
	  
	  TLorentzVector elInsubjet1, elInsubjet2, subjet1_wel, subjet2_wel;
	  std::vector<TLorentzVector> elInsubjet1vec, elInsubjet2vec;
	  for(unsigned int isub=0; isub<(((*pfjetAK8s)[jet].subjets(subjets)).size()); isub++){
	    std::vector<reco::CandidatePtr> subdaught(((*pfjetAK8s)[jet].subjets(subjets))[isub]->daughterPtrVector());
	    if (isub==0 || isub==1) {
	      float el_maxpt(-100);
	      int el_indx(-100);
	      for(unsigned int i2=0; i2 < subdaught.size(); i2++){
		if (abs((*subdaught[i2]).pdgId()) == 11){
		  
		  //SuperClusterRef cluster = (*subdaught[i2]).get<SuperClusterRef>();
		  //GsfTrackRef tr = (*subdaught[i2]).get<GsfTrackRef>();
		  //if (cluster.isNonnull()) {
		  //float caleta = (*cluster).eta();
		  //float calphi = (*cluster).phi();
		  //std::cout << " cal eta" <<  caleta << " " << " cal phi " << calphi << std::endl;
		  //}
		  
		  //float Ref_dR(0.3);
		  //edm::Handle<edm::View<pat::Electron>> elcoll;
		  //iEvent.getByToken(tok_electrons_, elcoll);
		  //if (elcoll.isValid() && elcoll->size()>0) {
		  //std::cout << " gsf electron valid " << std::endl;
		  //for( edm::View<pat::Electron>::const_iterator ele = elcoll->begin(); ele != elcoll->end(); ele++ ) {
		  //  GsfTrackRef trk = ele->gsfTrack();
		  //if (trk.isNonnull()) {
		  //float dR = delta2R(ele->eta(),ele->phi(),(*subdaught[i2]).eta(),(*subdaught[i2]).phi());
		  //if (dR < Ref_dR) Ref_dR = dR;
		  //nearest = ele;
		  //}}}
		  //if (Ref_dR < 0.4) std::cout << " dR " << Ref_dR << std::endl;
		  
		  if ((*subdaught[i2]).pt() > el_maxpt) {
		    el_maxpt = (*subdaught[i2]).pt();
		    el_indx = i2;
		    //std::cout << " el_maxpt " << el_maxpt << " el_indx " << el_indx << " isub " << isub << std::endl;
		  }
		}
	      }
	      if (el_indx >= 0 && isub==0) {
		//std::cout << (*subdaught[el_indx]).pt() << (*subdaught[el_indx]).eta() << (*subdaught[el_indx]).phi() << (*subdaught[el_indx]).energy() << " isub " << isub <<" ievt " << ievt << " for largejet " << jet << std::endl;
		elInsubjet1.SetPtEtaPhiE((*subdaught[el_indx]).pt(),(*subdaught[el_indx]).eta(),(*subdaught[el_indx]).phi(),(*subdaught[el_indx]).energy());
		subjet1_wel.SetPtEtaPhiM(((*pfjetAK8s)[jet].subjets(subjets))[isub]->pt(),((*pfjetAK8s)[jet].subjets(subjets))[isub]->eta(),((*pfjetAK8s)[jet].subjets(subjets))[isub]->phi(),((*pfjetAK8s)[jet].subjets(subjets))[isub]->mass());
		elInsubjet1vec.push_back(elInsubjet1);
	      }
	      if (el_indx >= 0 && isub==1) {
		//std::cout << (*subdaught[el_indx]).pt() << (*subdaught[el_indx]).eta() << (*subdaught[el_indx]).phi() << (*subdaught[el_indx]).energy() << "isub " << isub << " ievt " << ievt << " for large jet " << jet << std::endl;
                elInsubjet2.SetPtEtaPhiM((*subdaught[el_indx]).pt(),(*subdaught[el_indx]).eta(),(*subdaught[el_indx]).phi(),(*subdaught[el_indx]).energy());
		subjet2_wel.SetPtEtaPhiM(((*pfjetAK8s)[jet].subjets(subjets))[isub]->pt(),((*pfjetAK8s)[jet].subjets(subjets))[isub]->eta(),((*pfjetAK8s)[jet].subjets(subjets))[isub]->phi(),((*pfjetAK8s)[jet].subjets(subjets))[isub]->mass());
		elInsubjet2vec.push_back(elInsubjet2);
	      }
	    }
	    float emsub=0, phosub=0, musub=0, chhad=0, neuhad=0;
	    for(unsigned int i2=0; i2 < subdaught.size(); i2++){    
	      switch (abs((*subdaught[i2]).pdgId())){
	      case 11 :
		emsub += (*subdaught[i2]).energy();
		break;
	      case 13 :	
		musub += (*subdaught[i2]).energy();
		break;
	      case 22 :
		phosub += (*subdaught[i2]).energy();
		break;
	      case 211 :
		chhad += (*subdaught[i2]).energy();
		break;
	      case 130 :
		neuhad += (*subdaught[i2]).energy();
		break;
	      }
	    }
	    
	    if(isub==0){
	      pfjetAK8sub1pt[npfjetAK8] = ((*pfjetAK8s)[jet].subjets(subjets))[isub]->pt();
	      pfjetAK8sub1eta[npfjetAK8] = ((*pfjetAK8s)[jet].subjets(subjets))[isub]->eta();
	      pfjetAK8sub1phi[npfjetAK8] = ((*pfjetAK8s)[jet].subjets(subjets))[isub]->phi();
	      pfjetAK8sub1mass[npfjetAK8] = ((*pfjetAK8s)[jet].subjets(subjets))[isub]->mass();	 
	      pfjetAK8sub1btag[npfjetAK8] = ((*pfjetAK8s)[jet].subjets(subjets))[isub]->bDiscriminator("pfDeepCSVJetTags:probb")+((*pfjetAK8s)[jet].subjets(subjets))[isub]->bDiscriminator("pfDeepCSVJetTags:probbb");
	      //((*pfjetAK8s)[jet].subjets(subjets))[isub]->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
	      
	      pfjetAK8sub1emfrac[npfjetAK8] = emsub*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
	      pfjetAK8sub1mufrac[npfjetAK8] = musub*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
	      pfjetAK8sub1phofrac[npfjetAK8] = phosub*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
	      pfjetAK8sub1chhadfrac[npfjetAK8] = chhad*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
	      pfjetAK8sub1neuhadfrac[npfjetAK8] = neuhad*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
	      pfjetAK8sub1hadfrac[npfjetAK8] = (chhad+neuhad)*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
	      
	    }
	    else{
	      if(isub==1){
		pfjetAK8sub2pt[npfjetAK8] = ((*pfjetAK8s)[jet].subjets(subjets))[isub]->pt();
		pfjetAK8sub2eta[npfjetAK8] = ((*pfjetAK8s)[jet].subjets(subjets))[isub]->eta();
		pfjetAK8sub2phi[npfjetAK8] = ((*pfjetAK8s)[jet].subjets(subjets))[isub]->phi();
		pfjetAK8sub2mass[npfjetAK8] = ((*pfjetAK8s)[jet].subjets(subjets))[isub]->mass();	 
		pfjetAK8sub2btag[npfjetAK8] = ((*pfjetAK8s)[jet].subjets(subjets))[isub]->bDiscriminator("pfDeepCSVJetTags:probb")+((*pfjetAK8s)[jet].subjets(subjets))[isub]->bDiscriminator("pfDeepCSVJetTags:probbb");
		//((*pfjetAK8s)[jet].subjets(subjets))[isub]->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
		
		pfjetAK8sub2emfrac[npfjetAK8] = emsub*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
		pfjetAK8sub2mufrac[npfjetAK8] = musub*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
		pfjetAK8sub2phofrac[npfjetAK8] = phosub*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
		pfjetAK8sub2chhadfrac[npfjetAK8] = chhad*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
		pfjetAK8sub2neuhadfrac[npfjetAK8] = neuhad*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
		pfjetAK8sub2hadfrac[npfjetAK8] = (chhad+neuhad)*1./((*pfjetAK8s)[jet].subjets(subjets))[isub]->energy();
	      }
	    }	  
	  }
	  //std::cout << pfjetAK8sub1hadfrac[npfjetAK8] << "  " << pfjetAK8sub2hadfrac[npfjetAK8] << std::endl;
	  
	  if (pfjetAK8sub1hadfrac[npfjetAK8] > 0 && pfjetAK8sub2hadfrac[npfjetAK8] > 0) {
	    
	    //std::cout << pfjetAK8sub1hadfrac[npfjetAK8] << " hello " << pfjetAK8sub2hadfrac[npfjetAK8] << std::endl;
	    if (pfjetAK8sub1hadfrac[npfjetAK8] < pfjetAK8sub2hadfrac[npfjetAK8]) {
	      //std::cout << pfjetAK8sub1hadfrac[npfjetAK8] << " hello " << pfjetAK8sub2hadfrac[npfjetAK8] << " isub0 " << std::endl;
	      //std::cout << " size of elInsubjet1vec " << elInsubjet1vec.size() << std::endl;
	      if (elInsubjet1vec.size() > 0) {
		pfjetAK8elinsubpt[npfjetAK8] =  elInsubjet1.Pt();
		pfjetAK8elinsubeta[npfjetAK8] =  elInsubjet1.Eta();
		pfjetAK8elinsubphi[npfjetAK8] =  elInsubjet1.Phi();
		pfjetAK8elinsube[npfjetAK8] =  elInsubjet1.E();
		pfjetAK8elinsubmass[npfjetAK8] =  elInsubjet1.M();
	
		pfjetAK8elinsubjpt[npfjetAK8] =  subjet1_wel.Pt();
                pfjetAK8elinsubjeta[npfjetAK8] = subjet1_wel.Eta();
                pfjetAK8elinsubjphi[npfjetAK8] = subjet1_wel.Phi();
                pfjetAK8elinsubje[npfjetAK8] =   subjet1_wel.E();
                pfjetAK8elinsubjmass[npfjetAK8] =  subjet1_wel.M();
		
		//std::cout << " pfjetAK8elinsubpt[npfjetAK8] " <<  npfjetAK8  << " " << pfjetAK8elinsubpt[npfjetAK8] << " " << pfjetAK8elinsubeta[npfjetAK8] << " " << pfjetAK8elinsubphi[npfjetAK8] << " " << pfjetAK8elinsube[npfjetAK8] << " " << pfjetAK8elinsubmass[npfjetAK8] << " " <<  "pfjetAK8elinsubjpt[npfjetAK8]" <<  " " << pfjetAK8elinsubjpt[npfjetAK8] << " " << pfjetAK8elinsubjeta[npfjetAK8] << " " << pfjetAK8elinsubjphi[npfjetAK8] << " " << pfjetAK8elinsubjmass[npfjetAK8] << " " << pfjetAK8elinsubje[npfjetAK8] << std::endl;
		
	      }}
	    else if (pfjetAK8sub1hadfrac[npfjetAK8] > pfjetAK8sub2hadfrac[npfjetAK8]){
	      //std::cout << pfjetAK8sub1hadfrac[npfjetAK8] << " hello " << pfjetAK8sub2hadfrac[npfjetAK8] << " isub1 " << std::endl;
	      //std::cout<< " size of elInsubjet2vec " << elInsubjet2vec.size() << std::endl;
	      if (elInsubjet2vec.size() > 0) {
		pfjetAK8elinsubpt[npfjetAK8] =  elInsubjet2.Pt();
		pfjetAK8elinsubeta[npfjetAK8] =  elInsubjet2.Eta();
		pfjetAK8elinsubphi[npfjetAK8] =  elInsubjet2.Phi();
		pfjetAK8elinsube[npfjetAK8] =  elInsubjet2.E();
		pfjetAK8elinsubmass[npfjetAK8] =  elInsubjet2.M();
		
		pfjetAK8elinsubjpt[npfjetAK8] =  subjet2_wel.Pt();
                pfjetAK8elinsubjeta[npfjetAK8] = subjet2_wel.Eta();
                pfjetAK8elinsubjphi[npfjetAK8] = subjet2_wel.Phi();
                pfjetAK8elinsubje[npfjetAK8] =   subjet2_wel.E();
                pfjetAK8elinsubjmass[npfjetAK8] =  subjet2_wel.M();
		
		//std::cout << " pfjetAK8elinsubpt[npfjetAK8] " <<  npfjetAK8  <<" " << pfjetAK8elinsubpt[npfjetAK8] << " " << pfjetAK8elinsubeta[npfjetAK8] << " " << pfjetAK8elinsubphi[npfjetAK8] << " " <<  pfjetAK8elinsube[npfjetAK8] << " " <<pfjetAK8elinsubmass[npfjetAK8] << " " <<  "pfjetAK8elinsubjpt[npfjetAK8]" <<  " " << pfjetAK8elinsubjpt[npfjetAK8] << " " << pfjetAK8elinsubjeta[npfjetAK8] << " " << pfjetAK8elinsubjphi[npfjetAK8] << " " << pfjetAK8elinsubjmass[npfjetAK8] << " " << pfjetAK8elinsubje[npfjetAK8] << std::endl;
		
	      }}
	    else {
	      pfjetAK8elinsubpt[npfjetAK8] = -100; 
	      pfjetAK8elinsubeta[npfjetAK8] = -100;
	      pfjetAK8elinsubphi[npfjetAK8] = -100;
	      pfjetAK8elinsube[npfjetAK8] =  -100;
	      pfjetAK8elinsubmass[npfjetAK8] = -100;
	      pfjetAK8elinsubjpt[npfjetAK8] = -100; 
	      pfjetAK8elinsubjeta[npfjetAK8] = -100;
	      pfjetAK8elinsubjphi[npfjetAK8] = -100;
	      pfjetAK8elinsubje[npfjetAK8] = -100;  
	      pfjetAK8elinsubjmass[npfjetAK8] = -100; 
	    }}
	  
	  TLorentzVector lep4; 
	  TLorentzVector bjet4;
	  
	  vector <fastjet::PseudoJet> fjInputs;
	  fjInputs.resize(0);
	  int isubtag = -1;
	  if(pfjetAK8sub2hadfrac[npfjetAK8] < pfjetAK8sub1hadfrac[npfjetAK8]) { isubtag = 1; }
	  else { isubtag = 0; }
	  
	  int leadtrackid = -1;
	  float leadtrackpt = -1;
	  
	  std::vector<reco::CandidatePtr> subdaught(((*pfjetAK8s)[jet].subjets(subjets))[isubtag]->daughterPtrVector());
	  for(unsigned int i2=0; i2 < subdaught.size(); i2++){
	    PseudoJet psjet ;
	    psjet = PseudoJet( (*subdaught[i2]).px(),(*subdaught[i2]).py(),(*subdaught[i2]).pz(),(*subdaught[i2]).energy() );
	    psjet.set_user_index(i2);
	    fjInputs.push_back(psjet);
	    if(abs((*subdaught[i2]).charge())>0 && (*subdaught[i2]).pt()>leadtrackpt){
	      leadtrackpt = (*subdaught[i2]).pt();
	      leadtrackid = i2;
	    }
	  }
	  
	  ClusterSequence clustSeq_kT(fjInputs,jetDefkT);
	  vector <PseudoJet> kTl_sortedJets;
	  kTl_sortedJets = sorted_by_pt(clustSeq_kT.inclusive_jets());
	  
	  int ilms = -1;
	  
	  if(kTl_sortedJets.size() > 0){
	    
	    vector <fastjet::PseudoJet> lkT_subjets =  sorted_by_pt(kTl_sortedJets[0].exclusive_subjets_up_to(nkTsub));
	    bool lepmatch = false;
	    for(unsigned int kk=0; kk<lkT_subjets.size(); kk++){
	      vector <PseudoJet> const_kTsub = lkT_subjets[kk].constituents();     
	      for(unsigned int icons=0; icons<const_kTsub.size(); icons++){
		int id = const_kTsub[icons].user_index();
		if(id==leadtrackid){
		  lepmatch = true;
		  ilms = kk;
		  break;
		}
	      }
	      if(lepmatch) break;
	    }
	    
	    if(ilms>=0){
	      
	      lep4.SetPxPyPzE(lkT_subjets[ilms].px(),lkT_subjets[ilms].py(),lkT_subjets[ilms].pz(),lkT_subjets[ilms].e());
	      pfjetAK8_leppt[npfjetAK8] = lep4.Pt();
	      pfjetAK8_lepeta[npfjetAK8] = lep4.Eta();
	      pfjetAK8_lepphi[npfjetAK8] = lep4.Phi();
	      pfjetAK8_lepe[npfjetAK8] = lep4.E();
	      
	      TLorentzVector tmpsub1; 
	      tmpsub1.SetPtEtaPhiM(pfjetAK8sub1pt[npfjetAK8],pfjetAK8sub1eta[npfjetAK8],pfjetAK8sub1phi[npfjetAK8],pfjetAK8sub1mass[npfjetAK8]);
	      TLorentzVector tmpsub2; 
	      tmpsub2.SetPtEtaPhiM(pfjetAK8sub2pt[npfjetAK8],pfjetAK8sub2eta[npfjetAK8],pfjetAK8sub2phi[npfjetAK8],pfjetAK8sub2mass[npfjetAK8]);
	      TLorentzVector groomp4;
	      groomp4 = tmpsub1 + tmpsub2;
	      bjet4 = groomp4 - lep4;
			
	      pfjetAK8_bpt[npfjetAK8] = bjet4.Pt();
	      pfjetAK8_beta[npfjetAK8] = bjet4.Eta();
	      pfjetAK8_bphi[npfjetAK8] = bjet4.Phi();
	      pfjetAK8_be[npfjetAK8] = bjet4.E();
	      
	    }else{
	      pfjetAK8_leppt[npfjetAK8] = pfjetAK8_lepeta[npfjetAK8] = pfjetAK8_lepphi[npfjetAK8] = pfjetAK8_lepe[npfjetAK8] = -100;
	      pfjetAK8_bpt[npfjetAK8] = pfjetAK8_beta[npfjetAK8] = pfjetAK8_bphi[npfjetAK8] = pfjetAK8_be[npfjetAK8] = -100;
	    }
	  }
	  
	  if(ilms>=0){
	    
	    // neutrino reconstruction
	    
	    float nx = lep4.Px()/lep4.P();
	    float ny = lep4.Py()/lep4.P();
	    float nz = lep4.Pz()/lep4.P();
	    
	    TLorentzVector new_nu_vec4_perp;
	    
	    //		float bx = bjet4.Px();
	    //		float by = bjet4.Py();
	    //		float bz = bjet4.Pz();
	    
	    b_mass = bjet4.M();
	    
	    pfjetAK8_Kfactor[npfjetAK8] = (lep4.P()*1./bjet4.P())*(1./(w_mass*w_mass - mass_l*mass_l))*(t_mass*t_mass - w_mass*w_mass - b_mass*b_mass - 2*bjet4.Dot(lep4));
	    
	    float pll_dot = bjet4.Vect() * lep4.Vect().Unit();//  bx*nx + by*ny + bz*nz;
	    
	    pfjetAK8_Rnew[npfjetAK8] = (2 * w_mass * w_mass  * 1./lep4.E()) * (bjet4.E() - pll_dot) * 1./(t_mass*t_mass - w_mass*w_mass - b_mass*b_mass - 2*bjet4.Dot(lep4));
	    pfjetAK8_Rnew[npfjetAK8] = sqrt(pfjetAK8_Rnew[npfjetAK8]);
	    
	    float costheB = (3*bjet4.E()-pll_dot)*pfjetAK8_Rnew[npfjetAK8]/(4*bjet4.P());
	    float nupll = 0.5 * (w_mass*w_mass)*1./(lep4.E()*(sqrt(1+pfjetAK8_Rnew[npfjetAK8]*pfjetAK8_Rnew[npfjetAK8]) )- lep4.P());
	    float nue = nupll * sqrt(1+pfjetAK8_Rnew[npfjetAK8]*pfjetAK8_Rnew[npfjetAK8]);
	    
	    TLorentzVector new_nu_vec4;
	    new_nu_vec4.SetPxPyPzE(nx*nupll,ny*nupll,nz*nupll,0);
	    
	    new_nu_vec4_perp = productX(new_nu_vec4,bjet4,0,costheB*bjet4.P());
	    new_nu_vec4_perp *= (pfjetAK8_Rnew[npfjetAK8]*nupll); 
	    new_nu_vec4 += new_nu_vec4_perp;
	    new_nu_vec4.SetE(nue);
	    
	    pfjetAK8_nue[npfjetAK8] = nue;
	    pfjetAK8_nupt[npfjetAK8] = new_nu_vec4.Pt();
	    pfjetAK8_nueta[npfjetAK8] = new_nu_vec4.Eta();
	    pfjetAK8_nuphi[npfjetAK8] = new_nu_vec4.Phi();
	    
	    pfjetAK8_bbyW_E[npfjetAK8] = (bjet4.E())*1./(pfjetAK8_nue[npfjetAK8]+lep4.E());
	    
	    // neutrino reconstrunction ends
	  }
	  else{
	    pfjetAK8_Kfactor[npfjetAK8] = pfjetAK8_bbyW_E[npfjetAK8] = pfjetAK8_nue[npfjetAK8] = pfjetAK8_nupt[npfjetAK8] = pfjetAK8_nueta[npfjetAK8] = pfjetAK8_nuphi[npfjetAK8] = -100;
	  }
	  
	  pfjetAK8subhaddiff[npfjetAK8] = diff_func(pfjetAK8sub1hadfrac[npfjetAK8],pfjetAK8sub2hadfrac[npfjetAK8]);
	  pfjetAK8subemdiff[npfjetAK8] = diff_func(pfjetAK8sub1emfrac[npfjetAK8],pfjetAK8sub2emfrac[npfjetAK8]);
	  pfjetAK8subptdiff[npfjetAK8] = diff_func(pfjetAK8sub1pt[npfjetAK8],pfjetAK8sub2pt[npfjetAK8]);
	  
	  if(ilms>=0){
	    
	    std::vector<reco::CandidatePtr> daught2((*pfjetAK8s)[jet].daughterPtrVector());
	    std::sort(daught2.begin(), daught2.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2)
		      { return p1->pt() > p2->pt(); });
	    
	    float phosum = 0;
	    float chhadsum = 0;
	    float neuhadsum = 0;
	    float minlR = 20./lep4.Pt();
	    
	    for (unsigned int i2 = 0; i2< daught2.size(); ++i2) {
	      
	      float delR = delta2R((*daught2[i2]).rapidity(), (*daught2[i2]).phi(),lep4.Rapidity(),lep4.Phi());
	      
	      if(delR < minlR){
		if(abs((*daught2[i2]).pdgId())==11){
		  phosum += (*daught2[i2]).pt();
		}
		if(abs((*daught2[i2]).pdgId())==211){
		  chhadsum += (*daught2[i2]).pt();
		}	
		if(abs((*daught2[i2]).pdgId())==130){
		  neuhadsum += (*daught2[i2]).pt();
		}		
		
	      }
	    }
	    
	    pfjetAK8lepemiso[npfjetAK8] = phosum*1./lep4.Pt();
	    pfjetAK8lepchhadiso[npfjetAK8] = chhadsum*1./lep4.Pt();
	    pfjetAK8lepneuhadiso[npfjetAK8] = neuhadsum*1./lep4.Pt();
	    
	    daught2.clear();
	    
	  }
	  
	}
	  else{
	    pfjetAK8sub1pt[npfjetAK8] = pfjetAK8sub1eta[npfjetAK8] = pfjetAK8sub1phi[npfjetAK8] = pfjetAK8sub1mass[npfjetAK8] = pfjetAK8sub1btag[npfjetAK8] = pfjetAK8sub1chhadfrac[npfjetAK8] = pfjetAK8sub1neuhadfrac[npfjetAK8] = pfjetAK8sub1emfrac[npfjetAK8] = pfjetAK8sub1neuemfrac[npfjetAK8] = pfjetAK8sub1phofrac[npfjetAK8] = pfjetAK8sub1mufrac[npfjetAK8] = -100;
	    pfjetAK8sub2pt[npfjetAK8] = pfjetAK8sub2eta[npfjetAK8] = pfjetAK8sub2phi[npfjetAK8] = pfjetAK8sub2mass[npfjetAK8] = pfjetAK8sub2btag[npfjetAK8] = pfjetAK8sub2chhadfrac[npfjetAK8] = pfjetAK8sub2neuhadfrac[npfjetAK8] = pfjetAK8sub2emfrac[npfjetAK8] = pfjetAK8sub2neuemfrac[npfjetAK8] = pfjetAK8sub2phofrac[npfjetAK8] = pfjetAK8sub2mufrac[npfjetAK8] = -100;
	    pfjetAK8sdmass[npfjetAK8] = -100;
	    
	    pfjetAK8elinsubpt[npfjetAK8] = -100;
	    pfjetAK8elinsubeta[npfjetAK8] = -100;
	    pfjetAK8elinsubphi[npfjetAK8] = -100;
	    pfjetAK8elinsube[npfjetAK8] =  -100;
	    pfjetAK8elinsubmass[npfjetAK8] = -100; 
	    
	    pfjetAK8elinsubjpt[npfjetAK8] = -100;
            pfjetAK8elinsubjeta[npfjetAK8] = -100;
            pfjetAK8elinsubjphi[npfjetAK8] = -100;
            pfjetAK8elinsubje[npfjetAK8] =  -100;
            pfjetAK8elinsubjmass[npfjetAK8] = -100;
	    
	    pfjetAK8_bpt[npfjetAK8] = pfjetAK8_beta[npfjetAK8] = pfjetAK8_bphi[npfjetAK8] = pfjetAK8_be[npfjetAK8] = -100;
	    pfjetAK8_leppt[npfjetAK8] = pfjetAK8_lepeta[npfjetAK8] = pfjetAK8_lepphi[npfjetAK8] = pfjetAK8_lepe[npfjetAK8] = -100;
	  }
	
      }//isSoftDrop
      
      npfjetAK8++;	
      if(npfjetAK8 >= njetmxAK8) { break;}
      
    }
  }
  
  
  /*
    int nsubjets=0;
    iEvent.getByToken(tok_pfsubjetAK8s_, pfsubjetAK8s);
    for (unsigned jet = 0; jet< pfsubjetAK8s->size(); jet++) {
    //	cout<<(*pfsubjetAK8s)[jet].chargedHadronEnergyFraction()<<endl;
    }
  */	
  npfjetAK4 = 0;
  iEvent.getByToken(tok_pfjetAK4s_, pfjetAK4s);
  if(isMC){
    iEvent.getByToken(tok_genjetAK4s_, genjetAK4s);
  }
  
  for (unsigned jet = 0; jet< pfjetAK4s->size(); jet++) {
    
    HepLorentzVector pfjetAK44v((*pfjetAK4s)[jet].correctedP4("Uncorrected").px(),(*pfjetAK4s)[jet].correctedP4("Uncorrected").py(),(*pfjetAK4s)[jet].correctedP4("Uncorrected").pz(), (*pfjetAK4s)[jet].correctedP4("Uncorrected").energy());
    //	  HepLorentzVector pfjetAK44v((*pfjetAK4s)[jet].px(),(*pfjetAK4s)[jet].py(),(*pfjetAK4s)[jet].pz(), (*pfjetAK4s)[jet].energy());
    
    double tmprecpt = pfjetAK44v.perp();
    
    if(tmprecpt<minPt) continue;
    if(abs(pfjetAK44v.rapidity())>maxEta) continue;
    
    pfjetAK4pt[npfjetAK4] = 	tmprecpt;
    pfjetAK4eta[npfjetAK4] = 	pfjetAK44v.eta();
    pfjetAK4y[npfjetAK4] = pfjetAK44v.rapidity();
    pfjetAK4phi[npfjetAK4] = pfjetAK44v.phi();
    pfjetAK4mass[npfjetAK4] = (*pfjetAK4s)[jet].correctedP4("Uncorrected").mass();
    //	  pfjetAK4mass[npfjetAK4] = (*pfjetAK4s)[jet].mass();
    pfjetAK4btag_CMVA[npfjetAK4] = (*pfjetAK4s)[jet].bDiscriminator(btag_CMVA_name);
    pfjetAK4btag_CSV[npfjetAK4] = (*pfjetAK4s)[jet].bDiscriminator(btag_CSV_name);
    pfjetAK4btag_DeepCSV[npfjetAK4] = (*pfjetAK4s)[jet].bDiscriminator("pfDeepCSVJetTags:probb")+(*pfjetAK4s)[jet].bDiscriminator("pfDeepCSVJetTags:probbb");
    pfjetAK4btag_DeepCSV2[npfjetAK4] = (*pfjetAK4s)[jet].bDiscriminator("pfDeepCSVDiscriminatorsJetTags:BvsAll");
    pfjetAK4btag_DeepFlav[npfjetAK4] = (*pfjetAK4s)[jet].bDiscriminator("pfDeepFlavourJetTags:probb") + (*pfjetAK4s)[jet].bDiscriminator("pfDeepFlavourJetTags:probbb")+(*pfjetAK4s)[jet].bDiscriminator("pfDeepFlavourJetTags:problepb");
    pfjetAK4btag_DeepQCD[npfjetAK4] = (*pfjetAK4s)[jet].bDiscriminator("pfDeepBoostedJetTags:probQCDbb")+(*pfjetAK4s)[jet].bDiscriminator("pfDeepBoostedJetTags:probQCDcc")+(*pfjetAK4s)[jet].bDiscriminator("pfDeepBoostedJetTags:probQCDb")+(*pfjetAK4s)[jet].bDiscriminator("pfDeepBoostedJetTags:probQCDc")+(*pfjetAK4s)[jet].bDiscriminator("pfDeepBoostedJetTags:probQCDothers") ;
    
    double total_cor =1;
    
    jecL1FastAK4->setJetPt(tmprecpt); jecL1FastAK4->setJetA((*pfjetAK4s)[jet].jetArea()); jecL1FastAK4->setRho(*Rho_PF);jecL1FastAK4->setJetEta(pfjetAK44v.eta());
    double corFactorL1Fast = jecL1FastAK4->getCorrection();
    total_cor*= corFactorL1Fast;
    tmprecpt = tmprecpt * corFactorL1Fast;
    
    jecL2RelativeAK4->setJetPt(tmprecpt); jecL2RelativeAK4->setJetEta(pfjetAK44v.eta());
    double corFactorL2Relative = jecL2RelativeAK4->getCorrection();
    total_cor*= corFactorL2Relative ;
    tmprecpt = tmprecpt * corFactorL2Relative;
    
    jecL3AbsoluteAK4->setJetPt(tmprecpt); jecL3AbsoluteAK4->setJetEta(pfjetAK44v.eta());
    double corFactorL3Absolute = jecL3AbsoluteAK4->getCorrection();
    total_cor*= corFactorL3Absolute ;
    tmprecpt = tmprecpt * corFactorL3Absolute;
    
    double corFactorL2L3Residual=1.;
    
    if(isData){
      
      jecL2L3ResidualAK4->setJetPt(tmprecpt); jecL2L3ResidualAK4->setJetEta(pfjetAK44v.eta());
      
      corFactorL2L3Residual = jecL2L3ResidualAK4->getCorrection();
      total_cor*= corFactorL2L3Residual;
      tmprecpt *=corFactorL2L3Residual;
    }
		
    pfjetAK4JEC[npfjetAK4] = total_cor;
    
    pfjetAK4JECL1[npfjetAK4] = corFactorL1Fast;
    pfjetAK4JECL2[npfjetAK4] = corFactorL2Relative;
    pfjetAK4JECL3[npfjetAK4] = corFactorL3Absolute;
    pfjetAK4JECL2L3[npfjetAK4] = corFactorL2L3Residual;
    
    if(isMC){
      
      JME::JetResolution resolution_AK4;
      resolution_AK4 = JME::JetResolution(mPtResoFileAK4.c_str());
      JME::JetResolutionScaleFactor res_sf_AK4;
      res_sf_AK4 = JME::JetResolutionScaleFactor(mPtSFFileAK4.c_str());
      
      JME::JetParameters parameters_5 = {{JME::Binning::JetPt, tmprecpt}, {JME::Binning::JetEta, pfjetAK44v.eta()}, {JME::Binning::Rho, *Rho_PF}};
      double rp_AK4 = resolution_AK4.getResolution(parameters_5);
      double gaus_rp_AK4 = gRandom->Gaus(0.,rp_AK4);
      double sf_AK4 = res_sf_AK4.getScaleFactor(parameters_5, Variation::NOMINAL);
      double sf_up_AK4 = res_sf_AK4.getScaleFactor(parameters_5, Variation::UP);
      double sf_dn_AK4 = res_sf_AK4.getScaleFactor(parameters_5, Variation::DOWN);
      
      bool match_AK4 = false;
      int match_gen_AK4 = -1;
      
      for (unsigned get = 0; get<(genjetAK4s->size()); get++) {
	HepLorentzVector genjet4v((*genjetAK4s)[get].px(),(*genjetAK4s)[get].py(),(*genjetAK4s)[get].pz(), (*genjetAK4s)[get].energy());
	if((delta2R(pfjetAK44v.eta(),pfjetAK44v.phi(),genjet4v.eta(),genjet4v.phi()) < (0.5*0.4)) &&(fabs(tmprecpt-genjet4v.perp())<(3*fabs(rp_AK4)*tmprecpt))){
	  match_AK4 = true;
	  match_gen_AK4 = get;
	  break;
	}
      }
      
      pfjetAK4GenMatch[npfjetAK4] = match_gen_AK4;
      
      if(match_AK4&&(match_gen_AK4>=0)){
	pfjetAK4reso[npfjetAK4] = (sf_AK4-1.)*(tmprecpt-(*genjetAK4s)[match_gen_AK4].pt())*1./tmprecpt;
	pfjetAK4resoup[npfjetAK4] = (sf_up_AK4-1.)*(tmprecpt-(*genjetAK4s)[match_gen_AK4].pt())*1./tmprecpt;
	pfjetAK4resodn[npfjetAK4] = (sf_dn_AK4-1.)*(tmprecpt-(*genjetAK4s)[match_gen_AK4].pt())*1./tmprecpt;
      }else{
	
	pfjetAK4reso[npfjetAK4] = sqrt(max(0.,(sf_AK4*sf_AK4-1))) * gaus_rp_AK4;
	pfjetAK4resoup[npfjetAK4] = sqrt(max(0.,(sf_up_AK4*sf_up_AK4-1))) * gaus_rp_AK4;
	pfjetAK4resodn[npfjetAK4] = sqrt(max(0.,(sf_dn_AK4*sf_dn_AK4-1))) * gaus_rp_AK4;
      }
    }//isMC
    
	  
    // JES Uncertainty //
    
    for(int isrc =0 ; isrc<njecmcmx; isrc++){
      double sup = 1.0 ;
      
      if((isrc>0)&&(isrc<=nsrc)){
	JetCorrectionUncertainty *jecUnc = vsrc[isrc-1];
	jecUnc->setJetEta((*pfjetAK4s)[jet].eta());
	jecUnc->setJetPt(tmprecpt);
	
	sup += jecUnc->getUncertainty(true);         
	if(isrc==1){ pfjetAK4jesup_pu[npfjetAK4] = sup; }
	if(isrc==2){  pfjetAK4jesup_rel[npfjetAK4] = sup; }
	if(isrc==4){ pfjetAK4jesup_scale[npfjetAK4] = sup; }
	if(isrc==7){ pfjetAK4jesup_total[npfjetAK4] = sup; }
      }
      else if(isrc>nsrc){
	JetCorrectionUncertainty *jecUnc = vsrc[isrc-1-nsrc];
	jecUnc->setJetEta((*pfjetAK4s)[jet].eta());
	jecUnc->setJetPt(tmprecpt);
	
	sup -= jecUnc->getUncertainty(false);
			 if(isrc==8){ pfjetAK4jesdn_pu[npfjetAK4] = sup; }
			 if(isrc==9){ pfjetAK4jesdn_rel[npfjetAK4] = sup; }
			 if(isrc==11){ pfjetAK4jesdn_scale[npfjetAK4] = sup; }
			 if(isrc==14){ pfjetAK4jesdn_total[npfjetAK4] = sup; }
			}
      
    }
    /*
      pfjetAK4jesup[npfjetAK4] = 1.+jecUnc->getUncertainty(true);
      pfjetAK4jesdn[npfjetAK4] = 1.-jecUnc->getUncertainty(false);	  
    */
    // JES Uncertainty Ends //
	
    pfjetAK4CHF[npfjetAK4] = (*pfjetAK4s)[jet].chargedHadronEnergyFraction();
    pfjetAK4NHF[npfjetAK4] = (*pfjetAK4s)[jet].neutralHadronEnergyFraction();
    pfjetAK4CEMF[npfjetAK4] = (*pfjetAK4s)[jet].chargedEmEnergyFraction();
    pfjetAK4NEMF[npfjetAK4] = (*pfjetAK4s)[jet].neutralEmEnergyFraction();
    pfjetAK4MUF[npfjetAK4] = (*pfjetAK4s)[jet].muonEnergyFraction();
    pfjetAK4PHF[npfjetAK4] = (*pfjetAK4s)[jet].photonEnergyFraction();
    pfjetAK4EEF[npfjetAK4] = (*pfjetAK4s)[jet].electronEnergyFraction();
    pfjetAK4HFHF[npfjetAK4] = (*pfjetAK4s)[jet].HFHadronEnergyFraction();
    pfjetAK4HFEMF[npfjetAK4] = (*pfjetAK4s)[jet].HFEMEnergyFraction();
    pfjetAK4HOF[npfjetAK4] = (*pfjetAK4s)[jet].hoEnergyFraction();
    
    pfjetAK4CHM[npfjetAK4] = (*pfjetAK4s)[jet].chargedHadronMultiplicity();
    
    pfjetAK4NHM[npfjetAK4] = (*pfjetAK4s)[jet].neutralHadronMultiplicity();
    pfjetAK4CEMM[npfjetAK4] = (*pfjetAK4s)[jet].chargedMultiplicity() - (*pfjetAK4s)[jet].chargedHadronMultiplicity();
    pfjetAK4NEMM[npfjetAK4] = (*pfjetAK4s)[jet].neutralMultiplicity() - (*pfjetAK4s)[jet].neutralHadronMultiplicity();
    pfjetAK4MUM[npfjetAK4] = (*pfjetAK4s)[jet].muonMultiplicity();
    pfjetAK4PHM[npfjetAK4] = (*pfjetAK4s)[jet].photonMultiplicity();
    pfjetAK4EEM[npfjetAK4] = (*pfjetAK4s)[jet].electronMultiplicity();
    pfjetAK4HFHM[npfjetAK4] = (*pfjetAK4s)[jet].HFHadronMultiplicity();
    pfjetAK4HFEMM[npfjetAK4] = (*pfjetAK4s)[jet].HFEMMultiplicity();
    
    pfjetAK4Chcons[npfjetAK4] = (*pfjetAK4s)[jet].chargedMultiplicity();
    pfjetAK4Neucons[npfjetAK4] = (*pfjetAK4s)[jet].neutralMultiplicity();
    
    pfjetAK4looseID[npfjetAK4] = false;
    pfjetAK4tightID[npfjetAK4] = false;
    pfjetAK4tightLVID[npfjetAK4] = false;
    
    int NumConst = pfjetAK4Chcons[npfjetAK4] + pfjetAK4Neucons[npfjetAK4];
    double eta = pfjetAK44v.rapidity();

    pfjetAK4looseID[npfjetAK4] = ((pfjetAK4NHF[npfjetAK4]<0.99 && pfjetAK4NEMF[npfjetAK4]<0.99 && NumConst>1) && ((abs(eta)<=2.4 && pfjetAK4CHF[npfjetAK4]>0 && pfjetAK4CHM[npfjetAK4]>0 && pfjetAK4CEMF[npfjetAK4]<0.99) || abs(eta)>2.4) && abs(eta)<=2.7)|| (pfjetAK4NEMF[npfjetAK4]<0.90 && pfjetAK4NEMF[npfjetAK4]>2 && abs(eta)>2.7 && abs(eta)<=3.0 )||(pfjetAK4NEMF[npfjetAK4]<0.90 && pfjetAK4NEMF[npfjetAK4]>10 && abs(eta)>3.0)?true:false ;
    
    pfjetAK4tightID[npfjetAK4] = ((pfjetAK4NHF[npfjetAK4]<0.9 && pfjetAK4NEMF[npfjetAK4]<0.9 && NumConst>1) && ((abs(eta)<=2.4 && pfjetAK4CHF[npfjetAK4]>0 && pfjetAK4CHM[npfjetAK4]>0 && pfjetAK4CEMF[npfjetAK4]<0.99) || abs(eta)>2.4) && abs(eta)<=2.7)|| (pfjetAK4NEMF[npfjetAK4]<0.90 && pfjetAK4NEMF[npfjetAK4]>2 && abs(eta)>2.7 && abs(eta)<=3.0 )||(pfjetAK4NEMF[npfjetAK4]<0.90 && pfjetAK4NEMF[npfjetAK4]>10 && abs(eta)>3.0)?true:false;
    
    pfjetAK4tightLVID[npfjetAK4] = ((pfjetAK4NHF[npfjetAK4]<0.99 && pfjetAK4NEMF[npfjetAK4]<0.99 && NumConst>1 && pfjetAK4MUF[npfjetAK4]<0.8) && ((abs(eta)<=2.4 && pfjetAK4CHF[npfjetAK4]>0 && pfjetAK4CHM[npfjetAK4]>0 && pfjetAK4CEMF[npfjetAK4]<0.99) || abs(eta)>2.4) && abs(eta)<=2.7)?true:false;
    
    pfjetAK4chrad[npfjetAK4] = 0;
    
    float sumpt = 0, sumpt2 = 0;
	 
    vector <fastjet::PseudoJet> fjInputs;
    fjInputs.resize(0);
    
    std::vector<reco::CandidatePtr> daught((*pfjetAK4s)[jet].daughterPtrVector());
    std::sort(daught.begin(), daught.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2)
	      { return p1->pt() > p2->pt(); });
    
    pfjetAK4Ncons[npfjetAK4] = daught.size();
    
    for (unsigned int i2 = 0; i2< daught.size(); ++i2) {
      
      float pt2 = ((daught[i2])->pt()) * ((daught[i2])->pt());
      float delR = delta2R((*daught[i2]).rapidity(), (*daught[i2]).phi(),pfjetAK4y[npfjetAK4],pfjetAK4phi[npfjetAK4]);
      
      sumpt2 += pt2;
      sumpt += daught[i2]->pt();
      
      pfjetAK4chrad[npfjetAK4] +=  (*daught[i2]).charge() * (daught[i2])->pt() * pow(delR,1);
      
      PseudoJet psjet ;
      psjet = PseudoJet( (*daught[i2]).px(),(*daught[i2]).py(),(*daught[i2]).pz(),(*daught[i2]).energy() );
      fjInputs.push_back(psjet);
    }
    
    pfjetAK4chrad[npfjetAK4] *= 1./sumpt;
    
    pfjetAK4pTD[npfjetAK4] = (sumpt2>0) ? sqrt(sumpt2)*1./sumpt : 0;
    
    vector <fastjet::PseudoJet> sortedJets;
    fastjet::ClusterSequence clustSeq(fjInputs, pfjetAK4Def);
    fjInputs.clear();
    sortedJets    = sorted_by_pt(clustSeq.inclusive_jets());
	  
    if(sortedJets.size()>0){
      PseudoJet sd_jet = sd(sortedJets[0]);
      pfjetAK4sdmass[npfjetAK4] = sd_jet.m();
    }
    sortedJets.clear();
    
    pfjetAK4hadronflav[npfjetAK4] = (*pfjetAK4s)[jet].hadronFlavour();
    pfjetAK4partonflav[npfjetAK4] = (*pfjetAK4s)[jet].partonFlavour();
    //    pfjetAK4partonpdg[npfjetAK4] = (*pfjetAK4s)[jet].genParton()->pdgId();
    
    pfjetAK4qgl[npfjetAK4] = (*pfjetAK4s)[jet].userFloat("QGTagger:qgLikelihood");
    pfjetAK4PUID[npfjetAK4] = (*pfjetAK4s)[jet].userFloat("pileupJetId:fullDiscriminant");
    
    npfjetAK4++;	
    if(npfjetAK4 >= njetmx) { break;}
  }
  
  
  if(isMC){
    
    /*
      edm::Handle<reco::GenMETCollection> genmet_ ;
      iEvent.getByToken(tok_genmets_,genmet_) ;
      
     if(genmet_.isValid()){
     genmiset = genmet_->begin()->et();
     genmisphi = genmet_->begin()->phi();
     genmisetsig = genmet_->begin()->significance();
     }
    */
    
    ngenjetAK8 = 0;
    //	iEvent.getByToken(tok_genjetAK8s_, genjetAK8s);
    //	cout<<"genjetAK8s->size() "<<genjetAK8s->size()<<endl;
    
    for(unsigned gjet = 0; gjet<genjetAK8s->size(); gjet++)	{
      
      HepLorentzVector genjetAK84v((*genjetAK8s)[gjet].px(),(*genjetAK8s)[gjet].py(),(*genjetAK8s)[gjet].pz(), (*genjetAK8s)[gjet].energy());
      if(genjetAK84v.perp()<minPt) continue;
      if(abs(genjetAK84v.rapidity())>maxgenEta) continue;
      
      genjetAK8pt[ngenjetAK8] = genjetAK84v.perp();
      genjetAK8y[ngenjetAK8] = genjetAK84v.rapidity();
      genjetAK8phi[ngenjetAK8] = genjetAK84v.phi();
      genjetAK8mass[ngenjetAK8] = (*genjetAK8s)[gjet].mass();
      
      vector <fastjet::PseudoJet> fjInputs;
      fjInputs.resize(0);
      
      std::vector<reco::CandidatePtr> daught((*genjetAK8s)[gjet].daughterPtrVector());
      //		cout<<"AK8 jet "<<gjet+1<<" number of daughters "<<daught.size()<<endl;
      
      std::sort(daught.begin(), daught.end(), [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2)
		{ return p1->pt() > p2->pt(); }); 
      
      float sumpt = 0, sumpt2 = 0;
      
      genjetAK8chrad[ngenjetAK8] = 0;
      
        if(daught.size()>0){    
	  for (unsigned int i2 = 0; i2< daught.size(); ++i2) {
	    
	    float pt2 = ((daught[i2])->pt()) * ((daught[i2])->pt());
	    float delR = delta2R((*daught[i2]).rapidity(), (*daught[i2]).phi(),genjetAK8y[ngenjetAK8],genjetAK8phi[ngenjetAK8]);
		  
	    sumpt2 += pt2;
	    sumpt += daught[i2]->pt();
	    
	    genjetAK8chrad[ngenjetAK8] +=  (*daught[i2]).charge() * (daught[i2])->pt() * pow(delR,1);
	    
	    PseudoJet psjet ;
	    psjet = PseudoJet( (*daught[i2]).px(),(*daught[i2]).py(),(*daught[i2]).pz(),(*daught[i2]).energy() );
	    psjet.set_user_index(i2);
	    fjInputs.push_back(psjet);
	  } //i2
	  
	  genjetAK8chrad[ngenjetAK8] *= 1./sumpt;
	  
	  genjetAK8pTD[ngenjetAK8] = (sumpt2>0) ? sqrt(sumpt2)*1./sumpt : 0;
	  
	  vector <fastjet::PseudoJet> sortedJets;
	  fastjet::ClusterSequence clustSeq(fjInputs, pfjetAK8Def);
	  fjInputs.clear();
	  sortedJets    = sorted_by_pt(clustSeq.inclusive_jets());
	  
	  if(sortedJets.size()>0){
	    PseudoJet sd_jet = sd(sortedJets[0]);
	    genjetAK8sdmass[ngenjetAK8] = sd_jet.m();
	    Nsubjettiness nsub1_beta1(1,OnePass_WTA_KT_Axes(), UnnormalizedMeasure(1.));
	    genjetAK8tau1[ngenjetAK8] = nsub1_beta1(sd_jet);
	    Nsubjettiness nsub2_beta1(2,OnePass_WTA_KT_Axes(), UnnormalizedMeasure(1.));
	    genjetAK8tau2[ngenjetAK8] = nsub2_beta1(sd_jet);
	    Nsubjettiness nsub3_beta1(3,OnePass_WTA_KT_Axes(), UnnormalizedMeasure(1.));
	    genjetAK8tau3[ngenjetAK8] = nsub3_beta1(sd_jet);
	    
	    vector<PseudoJet> pieces;
	    pieces = sd_jet.pieces();
		
	    if(pieces.size()>0){
	      genjetAK8sub1pt[ngenjetAK8] = pieces[0].pt();
	      genjetAK8sub1y[ngenjetAK8] = pieces[0].rapidity();
	      genjetAK8sub1phi[ngenjetAK8] = pieces[0].phi();
	      genjetAK8sub1mass[ngenjetAK8] = pieces[0].m();
	      
	      for(unsigned isub=0; isub<(pieces.size()); isub++){
		
		float emsub=0, hadsub=0;
		for(unsigned id2=0; id2<pieces[isub].constituents().size(); id2++){
		  int id = (pieces[isub].constituents()[id2].user_index()); 
		  if(abs((*daught[id]).pdgId())==11 || abs((*daught[id]).pdgId())==22){
		    emsub += pieces[isub].constituents()[id2].e();
		  }
		  if(!(abs((*daught[id]).pdgId())==11 || abs((*daught[id]).pdgId())==22 || abs((*daught[id]).pdgId())==13)){
		    hadsub += pieces[isub].constituents()[id2].e();
		  }	
		}
		
		if(isub==0){
		  genjetAK8sub1hadfrac[ngenjetAK8] = hadsub*1./pieces[isub].e();
		  genjetAK8sub1emfrac[ngenjetAK8] = emsub*1./pieces[isub].e();
		}
		if(isub==1){
		  genjetAK8sub2hadfrac[ngenjetAK8] = hadsub*1./pieces[isub].e();
		  genjetAK8sub2emfrac[ngenjetAK8] = emsub*1./pieces[isub].e();
		}	
	      }
	      
	      genjetAK8sub2pt[ngenjetAK8] = pieces[1].pt();
	      genjetAK8sub2y[ngenjetAK8] = pieces[1].rapidity();
	      genjetAK8sub2phi[ngenjetAK8] = pieces[1].phi();
	      genjetAK8sub2mass[ngenjetAK8] = pieces[1].m();
	    }
	    else{ 
	      genjetAK8sub1pt[ngenjetAK8] = genjetAK8sub1y[ngenjetAK8] = genjetAK8sub1phi[ngenjetAK8] =  genjetAK8sub1mass[ngenjetAK8] = -100;
	      genjetAK8sub2pt[ngenjetAK8] = genjetAK8sub2y[ngenjetAK8] = genjetAK8sub2phi[ngenjetAK8] =  genjetAK8sub2mass[ngenjetAK8] = -100;
	    }
	    
	  }
	  sortedJets.clear();
	  
	} 
	
	//	if(daught.size() == 1) { genjetAK8sdmass[ngenjetAK8] =0; }
	
	if (++ngenjetAK8>=njetmx) break;
	    
    }
    
    ngenjetAK4 = 0;
    //	iEvent.getByToken(tok_genjetAK4s_, genjetAK4s);
    //	cout<<"genjetAK4s->size() "<<genjetAK4s->size()<<endl;
    
    for(unsigned gjet = 0; gjet<genjetAK4s->size(); gjet++)	{
      
      HepLorentzVector genjetAK44v((*genjetAK4s)[gjet].px(),(*genjetAK4s)[gjet].py(),(*genjetAK4s)[gjet].pz(), (*genjetAK4s)[gjet].energy());
      if(genjetAK44v.perp()<minPt) continue;
      if(abs(genjetAK44v.rapidity())>maxgenEta) continue;

      genjetAK4pt[ngenjetAK4] = genjetAK44v.perp();
      genjetAK4y[ngenjetAK4] = genjetAK44v.rapidity();
      genjetAK4phi[ngenjetAK4] = genjetAK44v.phi();
      genjetAK4mass[ngenjetAK4] = (*genjetAK4s)[gjet].mass();
      
      //    if(daught.size() == 1) { genjetAK4sdmass[ngenjetAK4] = genjetAK4mass[ngenjetAK4]; }
      
      if (++ngenjetAK4>=njetmx) break;
    }
    
    ngenparticles = 0;
    
    iEvent.getByToken(tok_genparticles_,genparticles);
    if(genparticles.isValid()){
      //		cout<<"# of gen particles "<<genparticles->size()<<endl;
      for(unsigned ig=0; ig<(genparticles->size()); ig++){
	/*
	  if( (abs((*genparticles)[ig].pdgId())>=1 && abs((*genparticles)[ig].pdgId())<=6 ) || (abs((*genparticles)[ig].pdgId())>=11 && abs((*genparticles)[ig].pdgId())<=16 )){
	  cout<<"PID "<<(*genparticles)[ig].pdgId()<<" status "<<(*genparticles)[ig].status()<<" from hardprocessfinalstate "<<(*genparticles)[ig].fromHardProcessFinalState()<<" promptfinalstate "<<(*genparticles)[ig].isPromptFinalState()<<endl;
	  }
	*/
	/*		    if((abs(((*genparticles)[ig].status())==23) || (*genparticles)[ig].status()==1) && ((*genparticles)[ig].isHardProcess()==1)){
			    cout<<"PID "<<(*genparticles)[ig].pdgId()<<" monId "<<((*genparticles)[ig].mother())->pdgId()<<" status "<<(*genparticles)[ig].status()<<endl;
			    }
			    if(abs((*genparticles)[ig].status())==22 && ((*genparticles)[ig].isHardProcess()==1)){
			    cout<<"PID "<<(*genparticles)[ig].pdgId()<<" daughters "<<(*genparticles)[ig].numberOfDaughters()<<endl;
			    }
	*/	
	if(!(((*genparticles)[ig].status()==1)||((*genparticles)[ig].status()==22)||((*genparticles)[ig].status()==23))) continue;
	if(!((*genparticles)[ig].isHardProcess())) continue;
		    
	if(!((abs((*genparticles)[ig].pdgId())>=1&&abs((*genparticles)[ig].pdgId())<=6)||(abs((*genparticles)[ig].pdgId())>=11&&abs((*genparticles)[ig].pdgId())<=16)||(abs((*genparticles)[ig].pdgId())==24))) continue;
	
	//cout<<"PID "<<(*genparticles)[ig].pdgId()<<" monId "<<((*genparticles)[ig].mother())->pdgId()<<" status "<<(*genparticles)[ig].status()<<endl;
	
	const Candidate * mom = (*genparticles)[ig].mother();

	genpartstatus[ngenparticles] = (*genparticles)[ig].status();
	genpartpdg[ngenparticles] = (*genparticles)[ig].pdgId();
	genpartmompdg[ngenparticles] = mom->pdgId();//(*genparticles)[ig].
	//		    genpartmomid[ngenparticles] = *mom;//->Id();  "?numberOfMothers>0?motherRef(0).key():-1
	genpartdaugno[ngenparticles] = (*genparticles)[ig].numberOfDaughters();
	genpartfromhard[ngenparticles] = (*genparticles)[ig].isHardProcess();
	genpartfromhardbFSR[ngenparticles] = (*genparticles)[ig].fromHardProcessBeforeFSR();
	genpartisLastCopyBeforeFSR[ngenparticles] = (*genparticles)[ig].isLastCopyBeforeFSR();
	genpartisPromptFinalState[ngenparticles] = (*genparticles)[ig].isPromptFinalState();
	genpartpt[ngenparticles] = (*genparticles)[ig].pt();
	genparteta[ngenparticles] = (*genparticles)[ig].eta();
	genpartphi[ngenparticles] = (*genparticles)[ig].phi();
	genpartm[ngenparticles] = (*genparticles)[ig].mass();
	genpartq[ngenparticles] = (*genparticles)[ig].charge();
		    
	ngenparticles++;
	if(ngenparticles>=npartmx) break;
      }
    }
    
  }//isMC
  
  nmuons = 0; 
  edm::Handle<edm::View<pat::Muon>> muons;
  iEvent.getByToken(tok_muons_, muons);
  if (muons.isValid() && muons->size()>0) {
    edm::View<pat::Muon>::const_iterator muon1;
    for( muon1 = muons->begin(); muon1 < muons->end(); muon1++ ) {
      if ((!muon1->isTrackerMuon()) && (!muon1->isGlobalMuon()) && (!muon1->isStandAloneMuon())) continue;
      
      TrackRef trkglb =muon1->globalTrack();
      
      if ((!muon1->isGlobalMuon())) {
        if (muon1->isTrackerMuon()) {
          trkglb =muon1->innerTrack();
        } else {
          trkglb =muon1->outerTrack();
        }
      }
      
      TrackRef trktrk =muon1->innerTrack();

      if ((!muon1->isTrackerMuon())) {
        if (muon1->isGlobalMuon()) {
          trktrk =muon1->globalTrack();
        } else {
          trktrk =muon1->outerTrack();
        }
      }
      
      if (trktrk->pt()<3.0) continue;
      
      muonisPF[nmuons] = muon1->isPFMuon();
      muonisGL[nmuons] = muon1->isGlobalMuon();
      muonisTRK[nmuons] = muon1->isTrackerMuon();
      
      muonecal[nmuons] = (muon1->calEnergy()).em;
      muonhcal[nmuons] = (muon1->calEnergy()).had;
      muonemiso[nmuons] = (muon1->isolationR03()).emEt;
      muonhadiso[nmuons] = (muon1->isolationR03()).hadEt;
      muontkpt03[nmuons] = (muon1->isolationR03()).sumPt;
      muontkpt05[nmuons] = (muon1->isolationR05()).sumPt;
      muonposmatch[nmuons] = (muon1->combinedQuality()).chi2LocalPosition;
      muontrkink[nmuons] = (muon1->combinedQuality()).trkKink;
      muonsegcom[nmuons] = int(1000. * muon::segmentCompatibility(*muon1)) / 1000.;
      
      muonpfiso[nmuons] = (muon1->pfIsolationR04().sumChargedHadronPt + max(0., muon1->pfIsolationR04().sumNeutralHadronEt + muon1->pfIsolationR04().sumPhotonEt - 0.5*muon1->pfIsolationR04().sumPUPt))/muon1->pt();
      
      muonisGoodGL[nmuons] = muon1->isGlobalMuon() && muon1->globalTrack()->normalizedChi2() < 3 && muon1->combinedQuality().chi2LocalPosition < 12 && muon1->combinedQuality().trkKink < 20; 
      muonisMed[nmuons] = (muon::isLooseMuon(*muon1))&&(muon1->innerTrack()->validFraction() > 0.8)&&(muonsegcom[nmuons] > (muonisGoodGL[nmuons] ? 0.303 : 0.451));
      muonisLoose[nmuons] = (muon::isLooseMuon(*muon1));
      
      muonpt[nmuons] = muon1->pt();
      muone[nmuons] = muon1->energy();
      muonp[nmuons] = trktrk->charge()*trktrk->p();
      muoneta[nmuons] = muon1->eta();
      muonphi[nmuons] = muon1->phi();
      
      muondrbm[nmuons] = trktrk->dxy(beamPoint);
      //  muontrkvtx[nmuons] = muon1->muonBestTrack()->dxy(beamPoint);
      //  muondz[nmuons] = muon1->muonBestTrack()->dz(beamPoint);
      muontrkvtx[nmuons] = muon1->muonBestTrack()->dxy(vertex.position());
      muondz[nmuons] = muon1->muonBestTrack()->dz(vertex.position());
      
      muonpter[nmuons] = trktrk->ptError();
      
      muonchi[nmuons] = trkglb->normalizedChi2();
      muonndf[nmuons] = (int)trkglb->ndof();
      
      muonhit[nmuons] = trkglb->hitPattern().numberOfValidMuonHits();
      muonmst[nmuons] = muon1->numberOfMatchedStations();
      muonpixhit[nmuons] = trktrk->hitPattern().numberOfValidPixelHits();
      muontrklay[nmuons] = trktrk->hitPattern().trackerLayersWithMeasurement();
      muonvalfrac[nmuons] = trktrk->validFraction();
      
      if (++nmuons>=njetmx) break;
    }
  }
  
  
  nelecs = 0;
  int iE1 = 0;
  for(const auto& electron1 : iEvent.get(tok_electrons_) ) {
    bool isPassMVAiso90 = electron1.electronID("mvaEleID-Fall17-iso-V2-wp90");
    bool isPassMVAnoiso90 = electron1.electronID("mvaEleID-Fall17-noIso-V2-wp90");
    elmvaid[nelecs] = isPassMVAiso90;                                                                          
    elmvaid_noIso[nelecs] = isPassMVAnoiso90;
    GsfTrackRef gsftrk1 = electron1.gsfTrack();
    if (gsftrk1.isNull()) continue;
    TrackRef ctftrk = electron1.closestCtfTrackRef();
    HepLorentzVector tmpelectron1(electron1.px(),electron1.py(),electron1.pz(), sqrt(electron1.p()*electron1.p()+el_mass*el_mass));
    iE1++;
    if (tmpelectron1.perp()<5.0) continue;
    if (gsftrk1->ndof() <9) continue;
    
    elsigmaieta[nelecs] = electron1.full5x5_sigmaIetaIeta();
    elsigmaiphi[nelecs] = electron1.full5x5_sigmaIphiIphi();
    elr9full[nelecs] = electron1.full5x5_r9();
    elsupcl_etaw[nelecs] = electron1.superCluster()->etaWidth();
    elsupcl_phiw[nelecs] = electron1.superCluster()->phiWidth();
    elhcaloverecal[nelecs] = electron1.full5x5_hcalOverEcal();
    elcloctftrkn[nelecs] = electron1.closestCtfTrackNLayers();
    elcloctftrkchi2[nelecs] = electron1.closestCtfTrackNormChi2();
    ele1x5bye5x5[nelecs] = 1.-electron1.full5x5_e1x5()/electron1.full5x5_e5x5();
    elnormchi2[nelecs] =  electron1.gsfTrack()->normalizedChi2();
    elhitsmiss[nelecs] =  electron1.gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);
    eltrkmeasure[nelecs] = electron1.gsfTrack()->hitPattern().trackerLayersWithMeasurement();
    elconvtxprob[nelecs] = electron1.convVtxFitProb();
    elecloverpout[nelecs] = electron1.eEleClusterOverPout();
    elecaletrkmomentum[nelecs] = 1.0/(electron1.ecalEnergy())-1.0/(electron1.trackMomentumAtVtx().R());
    eldeltaetacltrkcalo[nelecs] = electron1.deltaEtaSeedClusterTrackAtCalo();
    elsupcl_preshvsrawe[nelecs] = electron1.superCluster()->preshowerEnergy()/electron1.superCluster()->rawEnergy();
    elpfisolsumphet[nelecs] = electron1.pfIsolationVariables().sumPhotonEt;
    elpfisolsumchhadpt[nelecs] = electron1.pfIsolationVariables().sumChargedHadronPt;
    elpfsiolsumneuhadet[nelecs] = electron1.pfIsolationVariables().sumNeutralHadronEt;
    
    /*
      std::cout << " full5x5_sigmaIetaIeta " << electron1.full5x5_sigmaIetaIeta() << " " << " full5x5_sigmaIphiIphi " << electron1.full5x5_sigmaIphiIphi() << " " << " full5x5_r9 " << electron1.full5x5_r9() << " " << " superCluster.etaWidth " << electron1.superCluster()->etaWidth() << " superCluster.phiWidth " << electron1.superCluster()->phiWidth() << " full5x5_hcalOverEcal " << " " << electron1.full5x5_hcalOverEcal() << " " << " closestCtfTrackNLayers " << electron1.closestCtfTrackNLayers() << " " << " closestCtfTrackNormChi2 " << electron1.closestCtfTrackNormChi2() << " " << " 1.-full5x5_e1x5/full5x5_e5x5 " << 1.-electron1.full5x5_e1x5()/electron1.full5x5_e5x5() << " " << " normalizedChi2 " << electron1.gsfTrack()->normalizedChi2() << " " << " hitPattern.trackerLayersWithMeasurement " << " " << electron1.gsfTrack()->hitPattern().trackerLayersWithMeasurement() << " hitPattern.numberOfLostHits('MISSING_INNER_HITS') " << " " << electron1.gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS) << " convVtxFitProb  " << " " << electron1.convVtxFitProb() << " eEleClusterOverPout " << " " << electron1.eEleClusterOverPout() << " " << " 1.0/ecalEnergy-1.0/trackMomentumAtVtx.R" << 1.0/(electron1.ecalEnergy())-1.0/(electron1.trackMomentumAtVtx().R()) << " deltaEtaSeedClusterTrackAtCalo" << " " << electron1.deltaEtaSeedClusterTrackAtCalo()<< " superCluster.preshowerEnergy/superCluster.rawEnergy " << (electron1.superCluster()->preshowerEnergy()/electron1.superCluster()->rawEnergy()) << " pfIsolationVariables.sumPhotonEt " << electron1.pfIsolationVariables().sumPhotonEt << " pfIsolationVariables.sumChargedHadronPt " << electron1.pfIsolationVariables().sumChargedHadronPt << " pfIsolationVariables.sumNeutralHadronEt " << electron1.pfIsolationVariables().sumNeutralHadronEt <<  " Rho_PF " << Rho << " " << " myRho " << (*Rho_PF.product()) << std::endl;
    */
    eleoverp[nelecs] = electron1.eSuperClusterOverP();
    elhovere[nelecs] = electron1.hadronicOverEm();
    elhadisodepth03[nelecs] = electron1.dr03HcalDepth1TowerSumEt() + electron1.dr03HcalDepth2TowerSumEt();
    eltkpt03[nelecs] = electron1.dr03TkSumPt();
    elemiso03[nelecs] = electron1.dr03EcalRecHitSumEt();
    elhadiso03[nelecs] = electron1.dr03HcalTowerSumEt();
    eltkpt04[nelecs] = electron1.dr04TkSumPt();
    elemiso04[nelecs] = electron1.dr04EcalRecHitSumEt();
    elhadiso04[nelecs] = electron1.dr04HcalTowerSumEt();
    elietaieta[nelecs] = electron1.sigmaIetaIeta();
    eletain[nelecs] = electron1.deltaEtaSuperClusterTrackAtVtx();
    elphiin[nelecs] = electron1.deltaPhiSuperClusterTrackAtVtx();
    elfbrem[nelecs] = electron1.fbrem();
    elchhadiso[nelecs] = electron1.chargedHadronIso();
    elneuhadiso[nelecs] = electron1.neutralHadronIso();
    elphoiso[nelecs] = electron1.photonIso();
    elpuchhadiso[nelecs] = electron1.puChargedHadronIso();
    const reco::GsfElectron::PflowIsolationVariables& pfIso = electron1.pfIsolationVariables();
    elpfiso[nelecs] = pfIso.sumChargedHadronPt + max(0., pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - 0.5*pfIso.sumPUPt);
    elpt[nelecs] = electron1.charge()*electron1.pt();
    eleta[nelecs] = electron1.eta();
    elphi[nelecs] = electron1.phi();
    ele[nelecs] = electron1.ecalEnergy();
    elp[nelecs] = electron1.trackMomentumAtVtx().R();
    elsupcl_eta[nelecs] = electron1.superCluster()->eta();
    elsupcl_phi[nelecs] = electron1.superCluster()->phi();
    elsupcl_rawE[nelecs] = electron1.superCluster()->rawEnergy();
    eldxy[nelecs] = gsftrk1->dxy(beamPoint);
    eldz[nelecs] = gsftrk1->dz();
    float dzmin = 1000;
    float dxymin = 1000;
    if(svin.isValid()){
      for(unsigned int isv=0; isv<(svin->size()); isv++){
	const auto &sv = (*svin)[isv];
	reco::TrackBase::Point svpoint(sv.vx(),sv.vy(),sv.vz());
	if(fabs(gsftrk1->dz(svpoint)) < dzmin){
	  dzmin = fabs(gsftrk1->dz(svpoint));
	  dxymin = gsftrk1->dxy(svpoint);
	}
      }
    }
    eldxy_sv[nelecs] = dxymin;
    elchi[nelecs] = gsftrk1->chi2();
    elndf[nelecs] = (int)gsftrk1->ndof();
    elmisshits[nelecs] = (int)gsftrk1->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);
    elconvdist[nelecs] = electron1.convDist();
    elconvdoct[nelecs] = electron1.convDcot();
    if(++nelecs>=njetmx) break;
  }
    
  nphotons = 0;
  edm::Handle<edm::View<pat::Photon>> photons;
  
  edm::Handle <edm::ValueMap <bool> > mvaPhoIDSpring16GeneralPurposeV1wp90_reco;
  iEvent.getByToken(tok_mvaPhoIDSpring16GeneralPurposeV1wp90_reco, mvaPhoIDSpring16GeneralPurposeV1wp90_reco);
  
  
  iEvent.getByToken(tok_photons_, photons);
  if (photons.isValid()) {
    edm::View<pat::Photon>::const_iterator gamma1;
    int iPh1 = 0;
    for( gamma1 = photons->begin(); gamma1 != photons->end(); gamma1++ ) {
      if (!gamma1->isPhoton()) continue; 
      
      edm::Ptr<pat::Photon> pho_ptr(photons,iPh1);
      phomvaid[nphotons] = (*mvaPhoIDSpring16GeneralPurposeV1wp90_reco)[pho_ptr];
      
      iPh1++;
      
      phoe[nphotons] = gamma1->energy();
      phoeta[nphotons] = gamma1->eta();
      phophi[nphotons] = gamma1->phi();
      phoe1by9[nphotons] = gamma1->maxEnergyXtal()/max(float(1),gamma1->e3x3());
      if (gamma1->hasConversionTracks()) { phoe1by9[nphotons] *= -1; }
      phoe9by25[nphotons] = gamma1->r9();
      phohadbyem[nphotons] = gamma1->hadronicOverEm();
      
      photrkiso[nphotons] = gamma1->trkSumPtSolidConeDR04();
      phoemiso[nphotons] = gamma1->ecalRecHitSumEtConeDR04();
      phohadiso[nphotons] = gamma1->hcalTowerSumEtConeDR04();
      phophoiso[nphotons] = gamma1->photonIso() ;
      phochhadiso[nphotons] = gamma1->chargedHadronIso();
      phoneuhadiso[nphotons] = gamma1->neutralHadronIso();
      //phoPUiso[nphotons] = gamma1->sumPUPt();
      phoietaieta[nphotons] = gamma1->sigmaIetaIeta();
      if (++nphotons>=njetmx) break;
    }
  }
  
  for(int jk=0; jk<nHLTmx; jk++) {
    
    switch(jk) {
      
    case 0 :
      ihlt01 = ihlttrg[jk];
      prescl01 = iprescale[jk];
      break;
      
    case 1 :
      ihlt02 = ihlttrg[jk];
      prescl02 = iprescale[jk];
      break;
      
    case 2 :
      ihlt03 = ihlttrg[jk];
      prescl03 = iprescale[jk];
      break;
      
    case 3 :
      ihlt04 = ihlttrg[jk];
      prescl04 = iprescale[jk];
      break;
      
    case 4 :
      ihlt05 = ihlttrg[jk];
      prescl05 = iprescale[jk];
      break;
      
    case 5 :
      ihlt06 = ihlttrg[jk];
      prescl06 = iprescale[jk];
      break;
      
    case 6 :
      ihlt07 = ihlttrg[jk];
      prescl07 = iprescale[jk];
      break;
      
    case 7 :
      ihlt08 = ihlttrg[jk];
      prescl08 = iprescale[jk];
      break;
      
    case 8 :
      ihlt09 = ihlttrg[jk];
      prescl09 = iprescale[jk];
      break;
      
    case 9 :
      ihlt10 = ihlttrg[jk];
      prescl10 = iprescale[jk];
      break;
      
    case 10 :
      ihlt11 = ihlttrg[jk];
      prescl11 = iprescale[jk];
      break;

    case 11 :
      ihlt12 = ihlttrg[jk];
      prescl12 = iprescale[jk];
      break;

    case 12 :
      ihlt13 = ihlttrg[jk];
      prescl13 = iprescale[jk];
      break;

    case 13 :
      ihlt14 = ihlttrg[jk];
      prescl14 = iprescale[jk];
      break;

    case 14 :
      ihlt15 = ihlttrg[jk];
      prescl15 = iprescale[jk];
      break;

    case 15 :
      ihlt16 = ihlttrg[jk];
      prescl16 = iprescale[jk];
      break;
      
    case 16 :
      ihlt17 = ihlttrg[jk];
      prescl17 = iprescale[jk];
      break;

    }
  }	  
  //  cout<<"done!"<<endl;
  T1->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
Leptop::beginJob()
{
  
  Nevt = 0;
/* 
   for(int ij=0; ij<nomassbins; ij++){
  massbins[ij] = 10*ij ;
  }
  
  rhobins[0] = 0.005;
  
  for(int ij=1; ij<norhobins; ij++){
  rhobins[ij] = width*rhobins[ij-1] ;
  }
*/
  ////JEC /////
  L1FastAK4       = new JetCorrectorParameters(mJECL1FastFileAK4.c_str());
  L2RelativeAK4   = new JetCorrectorParameters(mJECL2RelativeFileAK4.c_str());
  L3AbsoluteAK4   = new JetCorrectorParameters(mJECL3AbsoluteFileAK4.c_str());
  L2L3ResidualAK4 = new JetCorrectorParameters(mJECL2L3ResidualFileAK4.c_str());
  
  vecL1FastAK4.push_back(*L1FastAK4);
  vecL2RelativeAK4.push_back(*L2RelativeAK4);
  vecL3AbsoluteAK4.push_back(*L3AbsoluteAK4);
  vecL2L3ResidualAK4.push_back(*L2L3ResidualAK4);
  
  jecL1FastAK4       = new FactorizedJetCorrector(vecL1FastAK4);
  jecL2RelativeAK4   = new FactorizedJetCorrector(vecL2RelativeAK4);
  jecL3AbsoluteAK4   = new FactorizedJetCorrector(vecL3AbsoluteAK4);
  jecL2L3ResidualAK4 = new FactorizedJetCorrector(vecL2L3ResidualAK4);
  
  L1FastAK8       = new JetCorrectorParameters(mJECL1FastFileAK8.c_str());
  L2RelativeAK8   = new JetCorrectorParameters(mJECL2RelativeFileAK8.c_str());
  L3AbsoluteAK8   = new JetCorrectorParameters(mJECL3AbsoluteFileAK8.c_str());
  L2L3ResidualAK8 = new JetCorrectorParameters(mJECL2L3ResidualFileAK8.c_str());
  
  vecL1FastAK8.push_back(*L1FastAK8);
  vecL2RelativeAK8.push_back(*L2RelativeAK8);
  vecL3AbsoluteAK8.push_back(*L3AbsoluteAK8);
  vecL2L3ResidualAK8.push_back(*L2L3ResidualAK8);
  
  jecL1FastAK8       = new FactorizedJetCorrector(vecL1FastAK8);
  jecL2RelativeAK8   = new FactorizedJetCorrector(vecL2RelativeAK8);
  jecL3AbsoluteAK8   = new FactorizedJetCorrector(vecL3AbsoluteAK8);
  jecL2L3ResidualAK8 = new FactorizedJetCorrector(vecL2L3ResidualAK8);
  /*
    const char *pname = srcnames[0];
    JetCorrectorParameters *pars = new JetCorrectorParameters(mJECUncFileAK4.c_str(),pname) ;
    JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*pars);
    //  vsrc[0] = unc;
    vsrc.push_back(unc);
  */
  for (int isrc = 0; isrc < nsrc; isrc++) {
    const char *name = srcnames[isrc];
    //    JetCorrectorParameters *p = new JetCorrectorParameters("Fall15_25nsV2_DATA_UncertaintySources_AK4PFchs.txt", name); 
    JetCorrectorParameters *p = new JetCorrectorParameters(mJECUncFileAK4.c_str(), name) ;
    JetCorrectionUncertainty *unc = new JetCorrectionUncertainty(*p);
    //    vsrc[isrc] = unc;
    vsrc.push_back(unc);
    JetCorrectorParameters *p1 = new JetCorrectorParameters(mJECUncFileAK8.c_str(), name) ;
    JetCorrectionUncertainty *unc1 = new JetCorrectionUncertainty(*p1);
    //    vsrc[isrc] = unc;
    vsrcAK8.push_back(unc1);
  }
  
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
Leptop::endJob() 
{
  // T1->Write();
 //fs->cd();
  // fs->Write();
  // fs->Close();
  
  //delete fs;	
  
  theFile->cd();
  theFile->Write();
  theFile->Close();
}

// ------------ method called when starting to processes a run  ------------
void 
Leptop::beginRun(edm::Run const& iRun, edm::EventSetup const& pset)
{
  bool changed(true);
  hltPrescaleProvider_.init(iRun,pset,theHLTTag,changed);
  HLTConfigProvider const&  hltConfig_ = hltPrescaleProvider_.hltConfigProvider();
  hltConfig_.dump("Triggers");
  hltConfig_.dump("PrescaleTable");
}

// ------------ method called when ending the processing of a run  ------------
void 
Leptop::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
Leptop::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
Leptop::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Leptop::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(Leptop);
