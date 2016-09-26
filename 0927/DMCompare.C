

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
	if(option ==1)f = TFile::Open(Form("/data7/monoH_genOnly/DMSimp_spin0/gentuple_%s",input.data()));
	else f = TFile::Open(Form("/data7/monoH_genOnly/Scalar/gentuple_%s",input.data()));
	if (!f || !f->IsOpen())return 0;
		
	TDirectory * dir;
	if(option==1) dir = (TDirectory*)f->Get(Form("/data7/monoH_genOnly/DMSimp_spin0/gentuple_%s:/tree",input.data()));
	else dir = (TDirectory*)f->Get(Form("/data7/monoH_genOnly/Scalar/gentuple_%s:/tree",input.data()));
		
	dir->GetObject("treeMaker",tree);
	
	 
	
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
		float genMET_true=data.GetFloat("genMET_true");
		th1[0]->Fill(genMET_true);
		
		TClonesArray* genParP4 = (TClonesArray*) data.GetPtrTObject("genParP4");
		int nGenPar=data.GetInt("nGenPar");
		int * genParSt=data.GetPtrInt("genParSt");
		int * genParId=data.GetPtrInt("genParId");
		
		int bIndex[2]={-1,-1};
		TLorentzVector* thisJet ,* thatJet;
		bool findThis=0, findThat=0;
		
		int DMId=18;
		if(option==0)DMId=9000006;
		
		for(int i=0;i<nGenPar;i++){
			
			if(genParId[i]==25&&genParSt[i]==22 ){
				thisJet=(TLorentzVector*)genParP4->At(i);
				th1[1]->Fill(thisJet->Pt());
				findThis=1;
			}
			
			if(fabs(genParId[i])==DMId&&genParSt[i]==1 ){
				//cout<<"found";
				thatJet=(TLorentzVector*)genParP4->At(i);
				findThat=1;
			}
			
			//if(genParSt[i]!=23)continue;
			if(fabs(genParId[i])==5 && bIndex[0]==-1 &&genParSt[i]==23){
				bIndex[0]=i;
			}
			else if (fabs(genParId[i])==5 && bIndex[0]!=-1 &&genParSt[i]==23 ){
				bIndex[1]=i;
			}
			
		}
		TLorentzVector* thisbJet =(TLorentzVector*)genParP4->At(bIndex[0]);
		TLorentzVector* thatbJet =(TLorentzVector*)genParP4->At(bIndex[1]);
		
		th1[2]->Fill(thisbJet->Pt());
		th1[3]->Fill(thatbJet->Pt());
		th1[4]->Fill(thisbJet->DeltaR(*thatbJet)); 
		//cout<<findThat<<","<<findThis<<endl;
		if(findThis && findThat){
			//cout<<"M="<<(*thisJet+*thatJet).M()<<endl;
			th1[5]->Fill((*thisJet+*thatJet).M());
		}
		
		//TClonesArray* ak4nGenJet = (TClonesArray*) data.GetPtrTObject("ak4nGenJet");
		
		
	}
	
	TFile* output=new TFile(Form("output/%s",input.data()),"recreate");
	for(int i=0;i<6;i++)th1[i]->Write();
	output->Close();
	
	
	return 0;
	
	
}

void DMCompare(){
	int MSC[7]={10,20,50,100,200,300,500};
	int MDM[6]={1,10,20,100,150,200};
	
	for(int i=0;i<7;i++){
		for(int j=0;j<6;j++){
			if(i==4 && j==3)continue;
			if(i==4 && j==4)continue;
			if(i==4 && j==5)continue;
			cout<<Form("Scalar_MSC%d_MDM%d.root",MSC[i]-5,MDM[j])<<endl;
			if(MSC[i]==MDM[j]*2)DMCompareBase(Form("Scalar_MSC%d_MDM%d.root",MSC[i]-5,MDM[j]),0);
			else DMCompareBase(Form("Scalar_MSC%d_MDM%d.root",MSC[i],MDM[j]),0);
			
			if(MSC[i]==MDM[j]*2)DMCompareBase(Form("DMSpin0_MSC%d_MDM%d.root",MSC[i]-5,MDM[j]),1);
			else DMCompareBase(Form("DMSpin0_MSC%d_MDM%d.root",MSC[i],MDM[j]),1);
		}
	}
}