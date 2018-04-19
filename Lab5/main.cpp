#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;

class ListaSlow {
 list<string> slowa;
public:
	void parsuj(string & l) {
		stringstream linestream(l);
		string slowo;
		slowa.clear();
		while (linestream >> slowo)
			slowa.push_back(slowo);
		slowa.sort([](string l1, string l2)-> bool{return l1.length() < l2.length(); });
	}

	ostream & pisz(ostream & os) {
		list<string>::iterator i = slowa.begin();
		while (i != slowa.end())
			os << *(i++) << " ";
		return os;
	}

	list<string> getSlowa(){
		return slowa;
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

struct sortuj{
	bool operator() (const string &x, const string y) const {
		return x.length()>y.length();
	}
};

 class Mikser : public  list < priority_queue<string, vector<string>,sortuj>>{
 private :
	 void parsuj(string & l) {
		 stringstream linestream(l);
		 string slowo;
		 priority_queue<string, vector<string>, sortuj> slowa;
		 while (linestream >> slowo)
			 slowa.push(slowo);
		 
		 push_back(slowa);
	 }
public:

	Mikser(){};
	Mikser(string file_name){
		open(file_name);
	}

	void open(string file_name){
		ifstream in(file_name);
		string linia;
		while (getline(in, linia)) {
			parsuj(linia);
		}
	}

	void execute(){
		typedef priority_queue<string, vector<string>, sortuj> xd;
		sort([]( xd k1, xd k2)->bool{return k1.size() < k2.size(); });
	}
	
	void write(string file_name){
		fstream out;
		list < priority_queue<string, vector<string>, sortuj>>:: iterator d=begin();
		out.open(file_name, ios::out);
		while ( d != end()){
			out << d;	
			d++;
		}
	}

	friend ostream & operator <<(ostream &wyjscie, list<priority_queue<string, vector<string>, sortuj>>::iterator &k);

};
 
  ostream &operator <<(ostream &wyjscie, list<priority_queue<string, vector<string>, sortuj>>::iterator &k){
	 list<priority_queue<string, vector<string>, sortuj>>::iterator slowa=k;
	 wyjscie << k->size() << ": ";
	 for (int i = 0; i <= slowa->size(); i++)
	 {
		 wyjscie << slowa->top() << " ";
		 slowa->pop();
		
	 }
	 return  wyjscie << endl;
 }
 
int main() {
	setlocale(LC_ALL, ""); // ustawia systemowe kodowanie polskich znaków w oknie konsoli
	
	// przyk³ad korzystania z obiektu typu "ListaSlow":
	ifstream in("mustafa.txt");
	ListaSlow LS;
	string linia;
	Mikser lista;
	lista.open("mustafa.txt");
	lista.execute();
	lista.write("wyjscie.txt");
	cout << "dupa" << endl;
	while (getline(in, linia)) {
		LS.parsuj(linia);
		//lista.addList(LS.getSlowa());
		LS.pisz(cout);
		cout << endl;
	}
	return 0;
};