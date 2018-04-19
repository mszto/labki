#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <time.h>
#include <numeric>
#include <functional>

using namespace std;


class dod{
	int sr;
public:

	dod():sr(0){}
	void operator()(int i){
		sr += i;
	}
	ostream & operator <<(ostream &wyjscie){ wyjscie << sr; 
	return wyjscie << endl;
	}
	int get_sr(){ return sr; }
};

class od{
	int sr;
	int sum;
public:
	od(int x):sr(x),sum(0){}
	int operator()(int i){
		int ocz;
		 ocz=sr - i;
		 ocz *= ocz;
		 sum += ocz;
		 return ocz;
	}
};
int main(){
	int n = 20;
	vector<int> K(n);
	vector<int> pom(n);
	dod l;
	int sr;
	generate(K.begin(), K.end(), []()->int{return rand() % 100; });
	l = for_each(K.begin(), K.end(), dod());
	for_each(K.begin(), K.end(), [](int i)->void{cout << i << endl; });
	cout << endl;
	sr = l.get_sr() / n;
	cout << l.get_sr() / n << endl;
	transform(K.begin(), K.end(), pom.begin(),od(sr));
	cout << endl;
	for_each(pom.begin(), pom.end(), [](int i)->void{cout << i << endl; });
	l = for_each(pom.begin(), pom.end(), dod());
	cout << endl << l.get_sr() / (n - 1) << endl;
}