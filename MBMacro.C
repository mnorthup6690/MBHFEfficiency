#include "TFile.h"
#include "TTree.h"
#include <iostream>

void run()
{
//	TFile* input = TFile::Open("ZeroBiasColFilLM.root");
//	TFile* input = TFile::Open("ZeroBiasColFil.root");
	TFile* input = TFile::Open("ZeroBiasCFRunSel.root");
	
	TTree* inTree = (TTree*)input->Get("HltTree");

	int HLTZeroBias = -99;
	int L1MBHF1AND = -99;
	int L1MBHF1OR = -99;
	int L1MBHF2AND = -99;
        int L1MBHF2OR = -99;
	int events = -99;

        int L1MBHF1ANDit = 0;
        int L1MBHF1ORit = 0;
        int L1MBHF2ANDit = 0;
        int L1MBHF2ORit = 0;
	int numPureZB = 0;

	inTree->SetBranchAddress("HLT_ZeroBias_v1",&HLTZeroBias);
	inTree->SetBranchAddress("L1_MinimumBiasHF1_AND",&L1MBHF1AND);
	inTree->SetBranchAddress("L1_MinimumBiasHF1_OR",&L1MBHF1OR);
	inTree->SetBranchAddress("L1_MinimumBiasHF2_AND",&L1MBHF2AND);
	inTree->SetBranchAddress("L1_MinimumBiasHF2_OR",&L1MBHF2OR);

	events = inTree->GetEntries();

	for (int i = 0; i < events; i++)
	{
		inTree->GetEntry(i);

		if (!HLTZeroBias) continue;
			numPureZB++;
		if (L1MBHF1AND == 1)
			L1MBHF1ANDit++;
		if (L1MBHF1OR == 1)
			L1MBHF1ORit++;
		if (L1MBHF2AND == 1)
			L1MBHF2ANDit++;
		if (L1MBHF2OR == 1)
                        L1MBHF2ORit++;	
	}	

	int HF1ORpre = 80;
	int HF2ORpre = 18000;
	int HF1ANDpre = 16000;
	int HF2ANDpre = 16000;

	std::cout << "HF1ORprescale: " << HF1ORpre << " HF2ORprescale: " << HF2ORpre << " HF1ANDprescale: " << HF1ANDpre << " HF2ANDprescale: " << HF2ANDpre << std::endl;

	std::cout << "Tot Num Events: " << events << " Num ZB: " << numPureZB << " Num HF1AND: " << L1MBHF1ANDit << " Eff HF1AND:  " << (double)(L1MBHF1ANDit*HF1ANDpre)/(double)numPureZB << 
	" Num HF1OR: " << L1MBHF1ORit << " Eff HF1OR:  " << (double)(L1MBHF1ORit*HF1ORpre)/(double)numPureZB << " Num HF2AND: " << L1MBHF2ANDit << " Eff HF2AND:  " << (double)(L1MBHF2ANDit*HF2ANDpre)/(double)numPureZB << " Num HF2OR: " << L1MBHF2ORit << " Eff HF2OR:  " << (double)(L1MBHF2ORit*HF2ORpre)/(double)numPureZB << std::endl;
}
