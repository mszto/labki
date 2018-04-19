#define _CRT_SECURE_NO_WARRNINGS
#include <iostream>
#include <stack>
#include <vector>
#include <assert.h>
#include <ctime>

using namespace std;


template<typename T>
class Konten
{
	enum { ssize = 100 };
	T stack[ssize];
	int top;
public:
	Konten() : top(0) {}
	void push(T i) {
		assert(top < ssize);  stack[top++] = i;
	};
	T pop() {
		assert(top > 0);  return stack[--top];
	};
	int rozmiar() { return top; };

	T show(int i){
		return stack[i];
	}

	class iterator {
		Konten& s;
		int index;
	public:
		iterator(Konten& is) : s(is), index(0) {};
		iterator(Konten& is, bool) : s(is), index(s.top) {};
		T operator++() { // Prefix
			assert(index < s.top);
			return s.stack[++index];
		};
		T operator++(int) { // Postfix
			//assert(index < s.top);
			return s.stack[index++];
		};
		T operator==(int) { // Postfix
			assert(index < s.top);
			return index;
		};
		T operator--(int) { // Postfix
			//assert(index < s.top);
			return s.stack[index--];
		};
		T& operator*() const { return s.stack[index]; };
		iterator& operator=(const iterator& rv) {
			s = rv.s;
			index = rv.index;
			return *this; s;
		}
		T & operator <<( const  iterator &d){
			cout << s.stack[index];
			return cout << endl;
		}
		bool operator!=(const iterator& rv) const {
			return index != rv.index;
		}
	};
	iterator begin() { return iterator(*this); };
	iterator end() { return iterator(*this, true); };

	friend class iterator;
};

double randdouble(){

	
	return (rand()/ (double(RAND_MAX)+1)+(rand()%10));
}
double rand2(){
	return (rand() / (RAND_MAX + 1) + ((rand() % 10) + 5));
}



template <typename T>
void roznicuj(T i1,T i2, T i3){
	
	while (i1 != i2){
		*i1 = *i1 - *i3;
		i1++;
		i3++;
	}
}
template <typename T>
void sumuj(T i1, T i2, double &a){
	while (i1 != i2){
		a = a + *i1;
		i1++;
	}
}

template <typename T>
void DoKwadratu(T i1, T i2){
	while (i1 != i2){
		*i1 = (*i1)*(*i1);
		i1++;
	}
}
template <typename T>
class Kalkulator{
	Konten<Konten<double>> kontener;
public:

	void push(Konten<double> i){
		kontener.push(i);
	}
	Konten< Konten<double>>::iterator begin(){
		return kontener.begin();
	}
	Konten< Konten<double>>::iterator end(){
		return kontener.end();
	}
	
	

	void najmOdleglosc(Konten< Konten<T>>::iterator &pierwszy, Konten< Konten<T>>::iterator &drugi){

		Konten<Konten<double>>::iterator pom = pierwszy;
		int ilosc = kontener.rozmiar()-1 ;
		int pocz = 0;
		Konten<double> kont1= kontener.show(pocz);
		Konten<double> kont2 = kontener.show(kontener.rozmiar());
		double odleglosc = 0, odleglosc2 = 0;
		Konten<Konten<T>>::iterator punkt1 = pierwszy;
		Konten<Konten<T>>::iterator punkt2 = drugi;
		int k = 0,p1=1,p2=kontener.rozmiar();

		while (drugi != pom){
			kont1 = kontener.show(pocz);
			kont2 = kontener.show(ilosc);
			while (pierwszy != drugi){
				roznicuj(kont1.begin(), kont1.end(), kont2.begin());
				DoKwadratu(kont1.begin(), kont2.end());
				sumuj(kont1.begin(), kont1.end(), odleglosc);
				sqrt(odleglosc);

				if (odleglosc2 == 0)
					odleglosc2 = odleglosc;

				if (odleglosc < odleglosc2){
					odleglosc2 = odleglosc;

					punkt1 = pierwszy;
					punkt2 = drugi;
				}
				odleglosc = 0;
				pierwszy++;
				pocz++;
				kont1 = kontener.show(pocz);
			}
			k++;
			ilosc--;
			kont2 = kontener.show(ilosc);
			pocz = 0;
			pierwszy = pom;
			drugi--;
		}

		pierwszy = punkt1;
		drugi = punkt2;
		cout << p1<< " "<<p2 << endl;
	}
	
};

	int main(){
		int a = 4, b = 3, c = 3, n = 4, m = 5;

		Konten<double> kontener1;
		Konten<double> kontener2;
		double suma = 0;
		Kalkulator <double> cosiek;
		Konten<Konten<double>> d;
		srand(time(NULL));

		for (int j = 0; j < m; j++){


			for (int i = 0; i < n; i++){
				kontener1.push(randdouble());
			}
			cosiek.push(kontener1);
			for (int i = 0; i < n; i++){
				kontener1.pop();
			}
		}

		for (int i = 0; i < n; i++){
			kontener1.push(randdouble());
		}

		Konten< Konten<double>>::iterator pierwszy = cosiek.begin();
		Konten< Konten<double>>::iterator drugi = cosiek.end();
		cosiek.najmOdleglosc(d.begin, d.end);
		//roznicuj(kontener3.begin(), kontener3.end(), kontener3.end());

		roznicuj(kontener1.begin(), kontener1.end(), kontener2.begin());
		DoKwadratu(kontener1.begin(), kontener1.end());
		sumuj(kontener1.begin(), kontener1.end(), suma);

		//suma = sqrt(suma);
		cout << suma;



		return 0;
}
