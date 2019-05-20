// LevenshteinovaRazdalja.cpp : Defines the entry point for the console application.
//

/* Karmen Unuk
OA_N0000819_sklop4_naloga3&4: Levenshteinova razdalja */

/* Napišite program, ki izraèuna Levenshteinovo razdaljo za dva niza in izpiše poravnavo
   nizov s to razdaljo. */


#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class CLR
{
public:
	CLR(string aN1, string aN2);
	~CLR(void);
	string niz1;
	string niz2;
	int** rez;
	int min(int a, int b, int c);
	void ZapolniMatriko();
	int Razlika(char aP, char aR);
	void IzpisMatrike();
	void PoravnavaNizov();

	////drugi del////
	string Najdaljse();
	string Maximum(vector<string> aM);
};

CLR::CLR(string aN1, string aN2)
{
	niz1 = aN1;
	niz2 = aN2;
	rez = new int*[aN1.size()+1];
	for(int i = 0; i< aN2.size(); i++){
		rez[i] = new int[aN2.size()+1]; 
	}
	for(int k = 0; k< aN1.size()+1; k++){
		rez[k][0] = k;
	}
	for(int l = 1; l< aN2.size()+1; l++){
		rez[0][l] = l;
	}
}

CLR::~CLR(void)
{
}

int CLR:: min(int a, int b, int c)
{
	int aM;
	if(a <= b && b <= c)
		aM = a;
	else{
		if(b <= a && b <= c){
			aM = b;
		}else{
			aM = c;
		}
	}
	return aM;
}

void CLR::ZapolniMatriko()
{
	for(int i = 1; i< niz1.size()+1; i++){
		for(int j = 1; j< niz2.size()+1; j++){
			int aR = Razlika(niz1.at(i-1), niz2.at(j-1));
			rez[i][j] = min(rez[i-1][j-1]+ aR, rez[i-1][j]+ aR, rez[i][j-1]+ aR);
		}
	}
	IzpisMatrike();
	cout << endl << "Niz 1 lahko dobimo Niza 2 (oz. obratno) s " << rez[niz1.size()][niz2.size()] << " spremembami." << endl;
}

int CLR:: Razlika(char aP, char aR)
{
	if(aP == aR){
		return 0;
	}else{
		return 1;
	}
}

void CLR:: IzpisMatrike()
{
	cout << "Matrika: " << endl;
	cout <<"    ";
	for(int k = 0; k< niz2.size(); k++){
		cout << niz2.at(k) << " ";
	}
	cout << endl;
	for(int i = 0; i< niz1.size()+1; i++){
		if(i == 0)
			cout << "  ";
		else
			cout << niz1.at(i-1) << " ";
		for(int j = 0; j< niz2.size()+1; j++){
			cout << rez[i][j] <<" ";
		}
		cout<< endl;
	}
}

void CLR::PoravnavaNizov()
{	
	string aP1;
	string aP2;
		ZapolniMatriko();
		cout << endl;
		int i = niz1.size();
		int j = niz2.size();
		while(i > 0 && j > 0){
			cout << i << " " << j << endl;
			if(j >= 1 && (rez[i][j-1] == rez[i][j]-1)){ 
				aP1 = '*' + aP1;			//na levo od gledanega elementa lahko gremo, le èe je razlika med levim in gledanim elementom 1
				aP2 = niz2.at(j-1)+ aP2;	//takrat vrineš j-ti znak v 2.; sicer pa je 1.poravnana z *
				j--;
			}else{
				if(i >= 1 && (rez[i-1][j] == rez[i][j]-1)){
					aP1 = niz1.at(i-1) + aP1;   //gor od gledanega elementa lahko gremo, le èe je razlika med levim in gledanim elementom 1	
					aP2 = '*' + aP2;			//takrat vrineš i-ti znak v	1.; sicer pa je 2.poravnana z *
					i--;
				}else{
					aP1 = niz1.at(i-1) + aP1;	//diagonalno lahko gremo (poravnana sta znaka)
					aP2 = niz2.at(j-1) + aP2;
					i--;
					j--;
				}
			}
		}
			cout << aP1 << endl;
			cout << aP2 << endl;
}

////////////////drugi del////////////////////////////

string CLR:: Najdaljse()
{
	vector<string> aNaj;
	ZapolniMatriko();
	string aP1; 
	string aP2;
		int i = niz1.size();
		int j = niz2.size();
		while(i > 0 && j > 0){
			if(j >= 1 && (rez[i][j-1] == rez[i][j]-1)){ 
				aP1 = '*' + aP1;			//na levo od gledanega elementa lahko gremo, le èe je razlika med levim in gledanim elementom 1
				aP2 = niz2.at(j-1)+ aP2;	//takrat vrineš j-ti znak v 2.; sicer pa je 1.poravnana z *
				j--;
			}else{
				if(i >= 1 && (rez[i-1][j] == rez[i][j]-1)){
					aP1 = niz1.at(i-1) + aP1;   //gor od gledanega elementa lahko gremo, le èe je razlika med levim in gledanim elementom 1	
					aP2 = '*' + aP2;			//takrat vrineš i-ti znak v	1.; sicer pa je 2.poravnana z *
					i--;
				}else{
					aP1 = niz1.at(i-1) + aP1;	//diagonalno lahko gremo (poravnana sta znaka)
					aP2 = niz2.at(j-1) + aP2;
					i--;
					j--;
				}
			}
		}
		cout << aP1 << " in " << aP2 << endl;
		int aM = aP1.size();
		string aT;
		for(int l = 0; l< aM; l++){
			cout << aP1.at(l) << " in " << aP2.at(l) << endl;
			if(aP1.at(l) == aP2.at(l)){
				aT.push_back(aP1.at(l));
			}else{
				if(aT.size() != 0){
					aNaj.push_back(aT);
					aT.clear();
				}
			}
			cout << aT << endl;
		}
		cout << "Velikost vektorja aNaj: "<< aNaj.size() << endl;
		for(int r = 0; r < aNaj.size(); r++){
			cout << aNaj.at(r) << endl;
		}
		return Maximum(aNaj);
}

string CLR:: Maximum(vector<string> aM)		//funkcija, ki vrne index, na katerem se nahaja niz z maximalno dolžino
{
	int max = aM.at(0).size();
	int aI = 0;
	for(int i = 1; i< aM.size(); i++){
		if(aM.at(i).size() > max){
			max = aM.at(i).size();
			aI = i;
		}
	}
	return aM.at(aI);
}




int _tmain(int argc, _TCHAR* argv[])
{

	cout << "_____________________Prva naloga_____________________" << endl;
	string niz1;
	string niz2;
	cout << "Vnesi niz1(krajsi niz): ";
	cin >> niz1;
	cout << "Vnesi niz2(daljsi niz): ";
	cin >> niz2;

	cout << endl;
	CLR* aR = new CLR(niz1, niz2);
	aR->PoravnavaNizov();
	cout << endl << endl;
	cout << "_____________________Druga naloga_____________________" << endl;

	string aT = aR->Najdaljse();
	cout << "Najdaljse skupno podzaporedje v obeh nizih: " << aT << endl;
	cin.ignore();
	cin.get();


	return 0;
}

