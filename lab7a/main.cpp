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
#include <cstdlib>
#include <cmath>
#include <limits>


using namespace std;

class genliczby{
	double sigma;
	double mu;
public:
	genliczby(double m, double si) :mu(m), sigma(si){};
	double operator()(){
		//srand(time(NULL));
		static const double epsilon = std::numeric_limits<double>::epsilon();
		static const double two_pi = 2.0*3.14159265358979323846;

		double z1 = 1;
		//bool generate;
		//generate = !generate;

		//if (!generate)
		//	return z1 * sigma + mu;

		double u1, u2;
		do
		{
			u1 = rand() * (1.0 / RAND_MAX);
			u2 = rand() * (1.0 / RAND_MAX);
		} while (u1 <= epsilon);

		double z0;
		z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
		z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
		return z0 * sigma + mu;
	}
};



class punkt
	:public vector<double>{
	typedef vector<double>::iterator iter;
	string chmura;
public:
	punkt(int n, double mu, double sigma) :vector<double>(n){ generate(begin(), end(), genliczby(mu, sigma)); };
	punkt(int n, double mu, double sigma,string chmur) :vector<double>(n),chmura(chmur){ generate(begin(), end(), genliczby(mu, sigma)); };
	punkt(int n) :vector<double>(n){};
	punkt(){};

	string get_chmura(){
		return chmura;
	}
	punkt operator+ (const punkt & r){

		transform(begin(), end(), r.begin(), begin(), plus<double>());
		return *this;
	}

	friend ostream & operator <<(ostream &wyjscie, punkt &d);

};

ostream & operator <<(ostream &wyjscie, punkt &d){
	for_each(d.begin(), d.end(), [](double i)->void{cout << i << " "; });
	wyjscie << d.chmura << endl;
	return wyjscie<< endl;
}
class gen_punkt{
	punkt p;
	double sigma;
	double mu;
	int n;
	string g;
public:
	gen_punkt(double m, double si, int n) :p(n, m, si), mu(m), sigma(si)  { };
	gen_punkt(double m, double si, int na,string ch) :p(na, m, si,ch), mu(m), sigma(si),g(ch) ,n(na) { };
	punkt operator()(){
		punkt d(n, mu, sigma, g);
		p = d;
		return p;
	}
};

template<class T>
class dziel{
private:
	T sum;
public:
	dziel(const T &x) :sum(x){};
	void operator()(T &i)
		const{
		i /= sum;

	};

};

class zmiana{
	list<punkt> *s;
	list<punkt> *chmur_a;
	punkt centroA;
	punkt centroB;
public:
	zmiana(list<punkt> &d,list<punkt> &g, punkt a, punkt b) : centroA(a), centroB(b){ s = &d; chmur_a = &g; };

	void operator ()(punkt i)const{
		double distanceA=0;
		double distanceB=0;
		distanceA = inner_product(i.begin(), i.end(), centroA.begin(), distanceA, plus<double>(), [](double x, double y)->double{ return (x - y)*(x - y); });
		distanceA = sqrt(distanceA);
		distanceB = inner_product(i.begin(), i.end(), centroB.begin(), distanceB, plus<double>(), [](double x, double y)->double{ return (x - y)*(x - y); });
		distanceB = sqrt(distanceB);

		if (distanceB < distanceA){
			s->push_back(i);
			chmur_a->remove(i);
		}
	};
};

class zmiana_2{
	list<punkt> *s;
	list<punkt> *chmur_a;
	punkt centroA;
	punkt centroB;
public:
	zmiana_2(list<punkt> &d, list<punkt> &g, punkt a, punkt b) : centroA(a), centroB(b){ s = &d; chmur_a = &g; };

	void operator ()(punkt i)const{
		double distanceA = 0;
		double distanceB = 0;
		distanceA = inner_product(i.begin(), i.end(), centroA.begin(), distanceA, plus<double>(), [](double x, double y)->double{ return (x - y)*(x - y); });
		distanceA = sqrt(distanceA);
		distanceB = inner_product(i.begin(), i.end(), centroB.begin(), distanceB, plus<double>(), [](double x, double y)->double{ return (x - y)*(x - y); });
		distanceB = sqrt(distanceB);

		if (distanceA < distanceB){
			chmur_a->push_back(i);
			s->remove(i);
		}
	};
};
class centro{
	list<punkt> A;
	list<punkt> B;
	
	punkt centroid_A;
	punkt centroid_B;
	int n;
public:
	centro(int d) :A(100), B(100), n(d){};

	void gen_punkty(double mu, double sigma, int n){

		generate(A.begin(), A.end(), gen_punkt(0, 10, n, "a"));
		generate(B.begin(), B.end(), gen_punkt(10, 10, n, "b"));
	}

	punkt centroidA(int n){
		punkt pom(n);
		centroid_A = accumulate(A.begin(), A.end(), pom, [](punkt x, punkt y)->punkt{return x + y; });
		for_each(centroid_A.begin(),centroid_A.end(), dziel<double>(100));
		return centroid_A;
	}
	punkt centroidB(int n){
		punkt pom(n);
		centroid_B = accumulate(B.begin(), B.end(), pom, [](punkt x, punkt y)->punkt{return x + y; });
		for_each(centroid_B.begin(),centroid_B.end(), dziel<double>(100));
		return centroid_B;
	}

	void wypisz_a(){
		for_each(A.begin(), A.end(), [](punkt i)->void{cout << i << endl; });
	}
	void sprawdz(){
		for_each(A.begin(), A.end(), zmiana(B,A, centroid_A, centroid_B));
		//for_each(A.begin(), A.end(), zmiana_2(A, B, centroid_A, centroid_B));
		cout << endl <<"rozmiar A: "<< A.size() << endl;
		cout << endl << "rozmiar B: " << B.size() << endl;
	}

	
};




int main(){
	srand(time(NULL));
	int n;
	centro g(20);
	cout << "podaj wymiar: ";
	cin >> n;
	g.gen_punkty(0, 10, n);
	punkt p(20, 0, 10);
	punkt x;
	vector<punkt> t;
	p = g.centroidA(n);
	x = g.centroidB(n);
	double distanc = 0;
	distanc = inner_product(p.begin(), p.end(), x.begin(), distanc, plus<double>(), [](double x, double y)->double{ return (x - y)*(x - y); });
	distanc = sqrt(distanc);
	cout << "centroid A:" << endl;
	copy(p.begin(), p.end(), ostream_iterator<double>(cout, "\n"));
	cout << "centroid B:" << endl;
	copy(x.begin(), x.end(), ostream_iterator<double>(cout, "\n"));
	cout << endl << "odleglosc: " << distanc << endl;

	g.sprawdz();
	//g.wypisz_a();
	return 0;
}