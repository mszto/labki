#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;

class ListaSlow : public list<string> {
public:
	void parsuj(string & l) {
		stringstream linestream(l);
		string slowo;
		clear();
		while (linestream >> slowo)
			push_back(slowo);
	}

	ostream & pisz(ostream & os) {
		list<string>::iterator i = begin();
		while (i != end())
			os << *(i++) << " ";
		return os;
	}
};

struct sortuj{
	bool operator() (const string &x, const string &y) const {
		return x.length()>y.length();
	}
};

template <class T> struct greater {
	bool operator() (const T& x, const T& y) const {
		return x < y;
	};
	typedef T first_argument_type;
	typedef T second_argument_type;
	typedef bool result_type;
};

struct sortuj_dlugosc{
	bool operator() (const priority_queue<string, vector<string>, sortuj> &x, const priority_queue<string, vector<string>, sortuj> &y){
		return x.size() < y.size();
	}
};

class Mikser :public list<priority_queue<string,vector<string>,sortuj>>{
	

	priority_queue<string, vector<string>, sortuj> parsuj(string & l) {
		stringstream linestream(l);
		string slowo;
		priority_queue<string, vector<string>, sortuj> slowa;
		while (linestream >> slowo){
			slowa.push(slowo);
		}
		return slowa;
	}
public:
	Mikser(){};
	Mikser(string file_name){
		open(file_name);
	}
	void open(string file_name){
		ifstream in(file_name);
		string linia;
		while (getline(in, linia)){
			push_back(parsuj(linia));
		}
	}

	void execute(){
		sort(sortuj_dlugosc());
	}

	void write(string file_name){
		fstream plik(file_name);

		while (!empty()){
			

			cout << front();
			pop_front();
		}
	}

	friend ostream & operator <<(ostream &wyjscie, priority_queue<string, vector<string>, sortuj> &kolejka);
};



ostream & operator <<(ostream &wyjscie, priority_queue<string, vector<string>, sortuj> &kolejka){
	wyjscie << kolejka.size() << ": ";
	while (!kolejka.empty()){
		wyjscie << kolejka.top()<<" ";
		kolejka.pop();
	}
	return wyjscie<< endl;
}

int main() {
	setlocale(LC_ALL, ""); // ustawia systemowe kodowanie polskich znaków w oknie konsoli
	Mikser m("mustafa.txt");

	m.execute();

	m.write("1.txt");
	// przyk³ad korzystania z obiektu typu "ListaSlow":
	
	return 0;
};