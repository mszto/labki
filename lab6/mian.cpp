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
class Statistic{

	multiset<int> r;
	multiset<int> s;
	vector<int> R;
	vector<int> S;
	void gen_obserwacje();
	double x;
public:

	void wypisz();
	Statistic();
	void ile_ptakow();
	void wariancja();

};

void Statistic::wypisz(){
	for each (int var in R)
	{
		cout << var << " ";
	}
	cout << endl;

	for each (int var in S)
	{
		cout << var << " ";
	}
	cout << endl;
}
void Statistic::gen_obserwacje(){
	srand(time(NULL)); // bufor do zapisywania obserwacji

	for (int i = 0; i < 1000; i++){
	
		r.insert(rand() % 10); // dodaj wynik nowej obserwacji
		s.insert(rand() % 10);
	}
}

Statistic::Statistic(){
	gen_obserwacje();
}

void Statistic::ile_ptakow(){
	typedef multiset<int>::iterator it;
	for (int i = 0; i < 10; i++){
		pair<it, it > d = equal_range(r.begin(), r.end(), i);
		pair<it, it> e = equal_range(s.begin(), s.end(), i);
		R.push_back(distance(d.first, d.second));
		S.push_back(distance(e.first,e.second));
	}
	///R.push_back(327);
	//R.push_back(317);
	//R.push_back(356);
	//S.push_back(359);
	//S.push_back(320);
	//S.push_back(321);
}

template<typename T>
double oblicz(T x, T y){ 
	if (x == 0 & y == 0){
		return 0;
	}
	double i = x - y;
	i = i*i;
	i=i / (x + y);
	return i;
}
void Statistic::wariancja(){
	double init = 0;
	x=inner_product(R.begin(), R.end(), S.begin(), init, [](double s, double z)->double{return s + z; }, oblicz<int>);
	cout << endl << x << endl;
}



//int myaccumulator(int x, int y) { return x - y; }
//int myproduct(int x, int y) { return x + y; }


int main(){
	class Statistic stat;

	stat.ile_ptakow();
	stat.wypisz();
	stat.wariancja();

	return 0;


}