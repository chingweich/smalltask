

#include "untuplizer.h"
#include "TH1D.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TDirectory.h"
#include "iostream"

int DMCompareBase(string input,int option=0){
	TFile *f;
	TTree *tree;
	f = TFile::Open(Form("/data7/monoH_genOnly_Phil/DMSimp_spin0/%s.root",input.data()));
	if (!f || !f->IsOpen())return 0;
		
	tree=(TTree *)f->Get("Events");
	 
	
	TreeReader data(tree);
	
	
	TH1D* th1[20];
	
	th1[0]=new TH1D("genMET_true","genMET_true",100,0,1000);
	th1[1]=new TH1D("Higgs_pt","Higgs_pt",100,0,1000);
	th1[2]=new TH1D("b0_pt","b0_pt",100,0,1000);
	th1[3]=new TH1D("b1_pt","b1_pt",100,0,1000);
	th1[4]=new TH1D("deltaR","deltaR",30,0,3);
	th1[5]=new TH1D("Mt","Mt",100,0,2000);
	
	for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){
		data.GetEntry(jEntry);
		float genMET_true=data.GetFloat("fMet");
		th1[0]->Fill(genMET_true);
	}
	
	TFile* output=new TFile(Form("output2/%s.root",input.data()),"recreate");
	for(int i=0;i<6;i++)th1[i]->Write();
	output->Close();
	
	
	return 0;
	
	
}

void DMCompare2(){
	int MSC[7]={10,20,50,100,200,300,500};
	int MDM[7]={1,10,20,50,100,150,200};
	
	
	
	for(int i=0;i<7;i++){
		for(int j=0;j<7;j++){
			
			cout<<Form("DMspin0_MSC%d_MDM%d.root",MSC[i]-5,MDM[j])<<endl;
			DMCompareBase(Form("MonoH_%d_%d_0.4_1.0_805",MSC[i],MDM[j]),1);
		}
	}
}