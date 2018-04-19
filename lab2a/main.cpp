#define _CRT_SECURE_NO_WARRNINGS
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <fstream>


using namespace std;

class Stos{
	int size;
	string line;
	//string tab1[10], tab2[10];
	int tab3[10];
public:
	Stos();
	void put(int i);
	void push();
};

class Tag{

	fstream file;
	string line;
	Stos stos();
	int line_number;
	string tab1[10], tab2[10];
	string znak;
public:

	Tag();
	void readline();
	void check(string &line);
	int koniec();
};


Stos::Stos():size(-1){
	
}

void Stos::put(int i){
	size++;
	tab3[size] = i;
}
void Stos::push(){
	size--;
}


Tag::Tag():file("kod.txt"),line_number(0),znak(""){
	tab1[0] = "<TABLE>";
	tab1[1] = "CAPTION>";
	tab1[2] = "<TR>";
	tab1[3] = "<TH>";
	tab1[4] = "<TH>";
	tab1[5] = "<TD>";
	tab1[6] = "<TR>";
	tab1[7] = "<TD>";

	tab2[0] = "</TABLE>";
	tab2[1] = "</CAPTION>";
	tab2[2] = "</TR>";
	tab2[3] = "</TH>";
	tab2[4] = "</TH>";
	tab2[5] = "</TD>";
	tab2[6] = "</TR>";
	tab2[7] = "</TD>";
}

int Tag::koniec(){
	return file.eof();
}

void Tag::readline(){
	line_number++;
	getline(file, line, '>');
	if (line == "\n"){
		znak = ">";
		return;
	}

		line = znak + line + ">";
		znak = "";

	cout << line << endl;
	//check(line);

	getline(file, line, '<');
	
	znak = "<";
	if (line == "\n"){
		znak = "<";
		return;
	}

	cout << line << endl;
	
	getline(file, line, '>');
	if (line == "\n"){
		znak = ">";
		return;
	}

		line = znak + line + ">";
		znak = "";
	cout << line << endl;
	//check(line);
}

void Tag::check(string &line){
	
}



int main(){
	fstream file("kod.txt");
	Tag nowy;
	while (!nowy.koniec()){
		nowy.readline();
	}


}