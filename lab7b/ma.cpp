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
#include <random>
#include <chrono>
#include <Windows.h>


using namespace std;

double gen_liczb(){
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);
		std::normal_distribution<double> distribution(5.0, 10.0);
		//Sleep(1);
		return distribution(generator);
	
}

template <typename T>
class dziel{
	T k;
public:
	dziel(T i) :k(i){};
	void operator()(T & i)const{
		i /= k;
	};
};



template <typename T>
class mno{
	T k;
public:
	mno(T i) :k(i){};
	void operator()(T & i)const{
		i = i-k;
	};
};




class punkt
	:public vector<double>{

public:
	punkt(){};
		punkt(int n): vector<double>(n){
			generate(begin(), end(), gen_liczb);
		}

		punkt operator+ (const punkt & r){
			
			transform(begin(), end(), r.begin(), begin(), plus<double>());
			return *this;
		}
		punkt operator- (const punkt & r){

			transform(begin(), end(), r.begin(), begin(), minus<double>());
			return *this;
		}
		friend ostream & operator <<(ostream &wyjscie, punkt &d);
};

ostream & operator <<(ostream  &wyjscie, punkt  &d){
	for_each(d.begin(), d.end(), [](int x)->void{cout << x<<endl; });
	return wyjscie << endl;
}

class gen_punkt{
	int n;
public:
	gen_punkt(int i) :n(i){};
	punkt operator()(){
		return punkt(n);
	}
};

class promien{
	double R;
	punkt centr;
public:
	promien(punkt cent):centr(cent),R(0){};
	promien(){};
	double get_R(){
		return R;
	}
	void operator()(punkt i){
		double pom = 0;
		pom = inner_product(i.begin(), i.end(), centr.begin(), pom, plus<double>(), [](double x, double y)->double{return ((x + y)*(x + y)); });
		pom = sqrt(pom);
		if (R < pom)
			R = pom;
	}
};

class odleglosc{
	double R;
	int mniejsze;
	int wieksze;
	punkt centr;
public:
	odleglosc(punkt cent, double promien) :centr(cent), R(promien),mniejsze(0),wieksze(0){};
	odleglosc(){};
	double get_R(){
		return R;
	}
	int get_mniejsze(){
		return mniejsze;
	}
	int get_wieksze(){
		return wieksze;
	}
	void operator()(punkt i){
		double pom = 0;
		pom = inner_product(i.begin(), i.end(), centr.begin(), pom, plus<double>(), [](double x, double y)->double{return ((x + y)*(x + y)); });
		pom = sqrt(pom);
		if (R < pom)
			wieksze++;
		else
			mniejsze++;
	}
};


list<punkt> operator+ (const list<punkt> & l, list<punkt> &r){

	//transform(l.begin(), l.end(), r.begin(), l.begin(), plus<punkt>());
	return l;
}
class Cent{
	typedef list<punkt> chmura;
	chmura A;
	chmura A_p;
	chmura pom;
	punkt centroid_a;
	punkt centroid_a_p;
	int n;
	promien R;
	odleglosc odl;
public:
	Cent(int i):centroid_a(i),n(i),A(100),A_p(100){
		generate(A.begin(), A.end(), gen_punkt(n));
	};
	Cent(){};
	punkt get_centroid_a(){
		return centroid_a;
	}
	punkt get_centroid_a_p(){
		return centroid_a_p;
	}
	chmura get_a(){
		return A;
	}

	void policz_centroid_a(){
		punkt pom(n);
		centroid_a = accumulate(A.begin(), A.end(), pom, [](punkt x, punkt y)->punkt{return x + y; });
		for_each(centroid_a.begin(), centroid_a.end(), dziel<double>(100.0));
	}

	void policz_centroid_a_p(){
		punkt pom(n);
		centroid_a_p = accumulate(A_p.begin(), A_p.end(), pom, [](punkt x, punkt y)->punkt{return x + y; });
		for_each(centroid_a_p.begin(), centroid_a_p.end(), dziel<double>(100.0));
	}

	void oblicz_A_p(){
		A_p = A;
		
		 transform(A.begin(), A.end(), A_p.begin(), A_p.begin(), [](punkt x, punkt y)->punkt{return x + y; });
		cout << endl;
		for_each(A_p.begin(), A_p.end(),mno<punkt>(centroid_a));
		//copy(pom.begin(), pom.end(), ostream_iterator<punkt>(cout, " "));
	}

	void policz_promien(){
		R=for_each(A.begin(), A.end(), promien(centroid_a));
		cout << endl << R.get_R() << endl;
		odl = for_each(A_p.begin(), A_p.end(), odleglosc(centroid_a, R.get_R()));
		cout << "odl mniejsza: " << odl.get_mniejsze() << " odl wieksze: " << odl.get_wieksze() << endl;
	}


};
int main(){
	int n;
	cout << "Podaj n: " << endl;
	cin >> n;
	punkt d;
	punkt g;
	Cent c(n);
	c.policz_centroid_a();
	d = c.get_centroid_a();
	//for_each(c.get_a().begin(), c.get_a().end(), [](punkt i)->void{cout << i << endl; });
		copy(d.begin(), d.end(), ostream_iterator<double>(cout, " "));
		cout << endl;
		c.oblicz_A_p();
		c.policz_centroid_a_p();
		g = c.get_centroid_a_p();
		cout << endl;
		copy(g.begin(), g.end(), ostream_iterator<double>(cout, " "));
		c.policz_promien();
	return 0;
}