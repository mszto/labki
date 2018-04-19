#define _CRT_SECURE_NO_WARRNINGS
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

class stos{
	int  znacznik = 0;
	int rozmiar = 7;
	string tab1[8];//{"<TABLE>", "<CAPTION>", "<TR>", "<TH>"};
	string tab2[8];//{"/TABLE>","/CAPTION>","/TR>","/TH>"};
	int tab3[10];

public:
	stos::stos(){
		tab1[0] = "<TABLE>";
		tab1[1] = "CAPTION>";
		tab1[2] = "<TR>";
		tab1[3] = "<TH>";
		tab1[4] = "TH>";
		tab1[5] = "<TD>";
		tab1[6] = "TR>";
		tab1[7] = "TD>";

		tab2[0] = "/TABLE>";
		tab2[1] = "/CAPTION>";
		tab2[2] = "/TR>";
		tab2[3] = "/TH>";
		tab2[4] = "/TH>";
		tab2[5] = "/TD>";
		tab2[6] = "/TR>";
		tab2[7] = "/TD>";
	}
	void put(string &dom){
		for (int i = 0; i < 8; i++){
			if (dom == tab1[i]){
				tab3[znacznik] = i;
				znacznik++;
				return;
			}
		}
	}
	void sprawdz(string &dom2){
		if (dom2 == tab2[tab3[znacznik - 1]]){
			znacznik--;
		}
		else{
			throw 2.4;
		}
	}
	
};

void wczytaj_linie(fstream &plik,stos &stosa){
	string line;

	getline(plik, line, '>');
	if (line == "\n"){
		return;
	}
	line = line + '>';
	stosa.put(line);
	getline(plik, line, '<');
	if (line == "\n"){
		return;
	}
	getline(plik, line, '>');
	if (line == "\n"){
		return;
	}
	line = line + '>';
	stosa.put(line);
	stosa.sprawdz(line);
	getline(plik, line, '\n');
}
void math(fstream &plik){
	string line;
	stos stosa;
	stos *pom=new stos;
	
	getline(plik, line);
	if (line != "<TABLE>"){
		throw 1;
	}
	else{
		stosa.put(line);
	}
	
	while (!plik.eof()){
		wczytaj_linie(plik,stosa);
		
	}

}

int main()
{
	int nr_lini = 1;
	int il;
	string linia;
	fstream file("kod.txt");
	string dom = "/TH>";

	"<" + dom;

	try{
		math(file);
	}

	catch (int s ){
		cout << "To nie jest tabela HTML" << endl;
	}
	catch (double d){
		cout << "Brak tagu lub niepoprawny tag" << endl;
		cout << dom;
	}
	catch (string d){

	}
	return 0;
}