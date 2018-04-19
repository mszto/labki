#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <list>


using namespace std;


double gen_liczb(){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	static default_random_engine generator(seed);

	std::normal_distribution<double> distribution(5.0, 10.0);

	return distribution(generator);

}


class niezdominowane{

public:
	niezdominowane(){};


	bool operator()(double x, double y){
		return x <= y;
	}
};
class punkt
	:public vector<double>{


public:
	punkt(){};
	punkt(int n) :vector<double>(n){
		generate(begin(), end(), gen_liczb);
	}

	bool operator  <=(punkt &r){
		vector<bool> g;
		vector<bool>::iterator it;
		transform(begin(), end(), r.begin(), g.begin(), niezdominowane());
		it = find(g.begin(), g.end(), false);
		if (it != g.end())
			return true;
		else
			return false;
	}
};


class gen_punkt{
	int n;
public:
	gen_punkt(){};
	gen_punkt(int x) :n(x){};

	punkt operator()(){
		return punkt(n);
	}
};

class czy{
	bool t;
	double x;
public:
	bool get_t(){
		return t;
	}
	czy(){};
	czy(double k) :x(k), t(true){};

	void operator()(double y){
		if (x >= y)
			t = false;
	}
};
class sprawdz_czy{
	punkt i;
	czy c;
	bool pom;
public:

	sprawdz_czy() {};
	sprawdz_czy(punkt x) :i(x){};
	bool get_b(){
		return pom;
	}
	void operator()(punkt y){
		vector<bool> g(y.size());
		vector<bool>::iterator it;
		transform(i.begin(), i.end(), y.begin(), g.begin(), [](double z, double j)->bool{return z <= j; });

		it = find(g.begin(), g.end(), false);
		if (it != g.end())
			pom = false;
		else
			pom = true;
	}
};
class sprawdz{
	typedef list<punkt>::iterator pocz;
	punkt g;
	int n;
	list<punkt> h;
	bool pom;
	sprawdz_czy m;
	list<punkt> *A, *B;

public:
	sprawdz(){};
	sprawdz(punkt b, list<punkt> &j, list<punkt> &aa, list<punkt> &bb) :g(b), n(0), A(&aa), B(&bb), pom(true){ h = j; };
	bool get_b(){
		return pom;
	}
	void operator()(punkt i){
		m = for_each(h.begin(), h.end(), sprawdz_czy(i));
		pom = m.get_b();
		if (pom){
			A->push_back(i);
		}
		else{
			B->push_back(i);
		}
	}

};

class oblicz{
	punkt d;
	list<double> *od;
public:
	oblicz(){};
	oblicz(punkt g, list<double> *p) :d(g), od(p){};
	void operator()(punkt i){
		double pom = 0;
		pom=inner_product(d.begin(), d.end(), i.begin(), pom, plus<double>(), [](double x, double y)->double{return (x - y)*(x - y); });
		pom = sqrt(pom);
		od->push_back(pom);
	}
};
class odl{
	list<punkt> b;
	list<double> *od;
public:
	odl(){};
	odl(list<punkt> g, list<double> &o) :b(g), od(&o){};
	void operator()(punkt G){
		for_each(b.begin(), b.end(), oblicz(G, od));
	}
};

class szukaj{
	double gest;
	int l;
	int ile;
public:
	szukaj(){};
	szukaj(int k) :l(k),ile(0), gest(0){}
	double get_gest(){
		return gest;
	}
	void operator()(double x){
		if (l == ile){
			gest = x;
		}
		ile++;
	}
};
class Niezdo{
	list<punkt> P;
	list<punkt> A;
	list<punkt> B;
	list<double> G;
	vector<double> l;
	int ile;
public:
	Niezdo(int k, int n) :P(k), ile(k){
		generate(P.begin(), P.end(), gen_punkt(n));
	}

	void wypelnij_a(){
		punkt s;
		list<punkt> pom = P;
		sprawdz p;
		p = for_each(P.begin()++, P.end(), sprawdz(*P.begin(), pom, A, B));
	}
	void odleglosc(){
		szukaj pom;
		for_each(A.begin(), A.end(), odl(B, G));
		G.sort();
		pom = for_each(G.begin(), G.end(), szukaj(sqrt(ile)));
		cout << pom.get_gest() << endl;

	}

};

int main(){
	Niezdo g(101, 5);
	g.wypelnij_a();
	cout << endl;
	g.odleglosc();

}