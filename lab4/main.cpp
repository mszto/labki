/* ========================================
ZPO: laboratorium 4
WMP.SNS UKSW, Warszawa
========================================
*/
#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include<exception>

using namespace std;

class Bazowe_Cechy {
public:
	static const bool _jest_liczba = false;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = false;
	static const int _dolna_granica_przedzialu = 0;
	static const int _gorna_granica_przedzialu = 0;
	static const bool czy_karta= false;
	static const bool czy_but= false;
	static const bool czy_czest = false;
};

template<typename T>
class Cechy : public Bazowe_Cechy {
public:
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 0; };
	static const int precyzja(){ return 0; };
};

class temperatura_wody {
	double t;
public:
	temperatura_wody(double temp = 50) : t(temp) {};
	double operator()() { return t; };
	temperatura_wody& operator=(double temp) { t = temp; return *this; };
	friend ostream & operator<< (ostream &wyjscie,  const temperatura_wody &d);
};


template<>
class Cechy<temperatura_wody>: public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const double dolna_granica_przedzialu() { return 0; };
	static const double gorna_granica_przedzialu() { return 100; };
	static const int precyzja(){ return 1; };
};

template<class _Cechy = Cechy<T>>
ostream & operator<< (ostream &wyjscie, const temperatura_wody &d){
	wyjscie.precision(Cechy<T>::precyzja());
	return	wyjscie << d.t << endl;
}

class kostka_do_gry {
	int n;
public:
	kostka_do_gry(int num = 1) : n(num) {};
	int operator()() { return n; };
	kostka_do_gry& operator=(int num) { n = num; return *this; };
};

template<>
class Cechy<kostka_do_gry>: public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 1;
	static const int _gorna_granica_przedzialu = 6;
};

class Srednica_opony{
	int sr;
public:
	Srednica_opony(int sred = 10) : sr(sred) {};
	int operator()() { return sr; };
	Srednica_opony& operator=(int sred) { sr = sred; return *this; };
	friend ostream & operator<< (ostream &wyjscie, const Srednica_opony &d);
};

template<> 
class Cechy<Srednica_opony>: public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 10;
	static const int _gorna_granica_przedzialu = 24;
};

template<class _Cechy = Cechy<T>>
ostream & operator<< (ostream &wyjscie, const Srednica_opony &d){
	wyjscie.precision(Cechy<T>::precyzja());
	return  wyjscie << d.sr << ednl;
}

class Czestotliwosc{
	double czest;
public:
	Czestotliwosc(double cze = 87.5) : czest(cze) {};
	double operator()() { return czest; };
	Czestotliwosc& operator=(double cze) { czest = cze; return *this; };
	friend ostream &operator <<(ostream &wyjscie, const Czestotliwosc &d);
};

template<>
class Cechy<Czestotliwosc>: public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = false;
	static const double dolna_granica_przedzialu() { return 87.5; };
	static const double gorna_granica_przedzialu() { return 108; };
	static const bool czy_czest=true;
	static const int precyzja(){ return 2; };
};

template<class _Cechy = Cechy<T>>
ostream &operator<<(ostream &wyjscie, const Czestotliwosc &d){
	//wyjscie.precision(Cechy<T>::precyzja());
	return wyjscie << d.czest << endl;
}


class Rozmiar_buta{
	double roz;
public:
	Rozmiar_buta(double r = 36) : roz(r) {};
	double operator()() { return roz; };
	Rozmiar_buta& operator=(double r) { roz = r; return *this; };
};

template<>
class Cechy<Rozmiar_buta>: public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = false;
	static const double dolna_granica_przedzialu() { return 87.5; };
	static const double gorna_granica_przedzialu() { return 108; };
	static const bool czy_but=true;
};

class Karta{
	int poj;
public:
	Karta(int p = 2) : poj(p) {};
	int operator()() { return poj; };
	Karta& operator=(int p) { poj = p; return *this; };
};

template<>
class Cechy<Karta>: public Bazowe_Cechy{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const int _dolna_granica_przedzialu = 2;
	static const int _gorna_granica_przedzialu = 128;
	static const bool czy_karta=  true; 
};


class Przepelnienie : public exception {
	char opis[100];
public:
	Przepelnienie(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};
class BrakDanych : public exception {
	char opis[100];
public:
	BrakDanych(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};


template<typename T, int rozmiar, class _Cechy = Cechy<T>>
class SzablonStosu{
	T stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	SzablonStosu() : top(0) {}
	void push(const T& i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	void push(int i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		if (Cechy<T>::_jest_liczba && Cechy<T>::_jest_liczba_calkowita) {
			if (Cechy<T>::_nalezy_do_przedzialu) {
				if (Cechy<T>::czy_karta){
					if ((Cechy<T>::_dolna_granica_przedzialu <= i) && (i <= Cechy<T>::_gorna_granica_przedzialu)){
						int pom=2;
						for (int j = 0; j < 7;i++){
							if (i == pom){
								stos[top++];
							}
							pom = pom * 2;
						}
					}
				}
				else if ((Cechy<T>::_dolna_granica_przedzialu <= i) && (i <= Cechy<T>::_gorna_granica_przedzialu))	
					stos[top++] = i;
			}
			else
				stos[top++] = i;
		}
	}
	void push(double i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		if (Cechy<T>::_jest_liczba && !Cechy<T>::_jest_liczba_calkowita) {
			if (Cechy<T>::_nalezy_do_przedzialu) {
				if ( Cechy<T>::czy_but){
					if (abs(i - (int)i) == 0.5 || abs(i - (int)i) == 0){
						if ((Cechy<T>::dolna_granica_przedzialu() <= i) && (i <= Cechy<T>::gorna_granica_przedzialu()))
							stos[top++] = i;
						else
							return;
					}
				}
				if (Cechy<T>::czy_czest){
					if (abs(i - (int)i) <= 0.9 && abs(i - (int)i) >= 0.01){
						if ((Cechy<T>::dolna_granica_przedzialu() <= i) && (i <= Cechy<T>::gorna_granica_przedzialu()))
							stos[top++] = i;
						else
							return;
					}
				}
				if ((Cechy<T>::dolna_granica_przedzialu() <= i) && (i <= Cechy<T>::gorna_granica_przedzialu()))
					stos[top++] = i;
			}
			else
				stos[top++] = i;
		}
	}
	T pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());
		return stos[--top];
	}

	void wypisz(){
		for (int i = 0; i < top; i++){
			cout.precision(Cechy<T>::precyzja());
			cout <<stos[i];
		}
	}

	class iterator {
		SzablonStosu& s;
		int index;
	public:
		iterator(SzablonStosu& is) : s(is), index(0) {};
		iterator(SzablonStosu& is, bool) : s(is), index(s.top) {};
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
		T & operator <<(const  iterator &d){
			cout << s.stack[index];
			return cout << endl;
		}
		bool operator!=(const iterator& rv) const {
			return index != rv.index;
		}
	};
	iterator begin() { return iterator(*this); };
	iterator end() { return iterator(*this, true); };
	
};
template<typename T>
void ws(T d,T w){

	while (d != w){
		cout << d;
		d++;
	}
}

int main() {
	SzablonStosu<string, 5> K1;
	SzablonStosu<temperatura_wody, 10> K2;
	SzablonStosu<kostka_do_gry, 10> K3;
	SzablonStosu<Czestotliwosc, 5> K4;
	
	K4.push(85.8);
	K4.push(105.5);
	K4.push(150.3);

	SzablonStosu<Czestotliwosc, 5>::iterator sa=K4.begin();

	K4.wypisz();

	// zape³nianie stosu
	ifstream fi("qv-lab4.txt");
	string s;
	try{
		K1.push("Henryk");
		K1.push("Sienkiewicz");
		while (fi) {
			fi >> s;
			K1.push(s);
			fi.seekg(ios::beg);
			fi.clear();
		};
	}
	catch (Przepelnienie& e){
		cout << "K1 gotowy: " << e.what() << endl;
	};
	cout << "Danych na stosie K1: " << K1.zajetosc() << endl;

	K2.push(temperatura_wody());
	K2.push(temperatura_wody(36.6));
	K2.push(40);
	K2.push(71.2);
	cout << "Danych na stosie K2: " << K2.zajetosc() << endl;

	K3.push(kostka_do_gry(3));
	K3.push(kostka_do_gry());
	K3.push(4);
	K3.push(6);
	K3.push(10);
	cout << "Danych na stosie K3: " << K3.zajetosc() << endl;

	// opró¿nianie stosu
	try{
		while (true)
			K1.pop();
	}
	catch (BrakDanych& e) {
		cout << "K1 pusty: " << e.what() << endl;
	}
	try{
		while (true)
			K2.pop();
	}
	catch (BrakDanych& e) {
		cout << "K2 pusty: " << e.what() << endl;
	}
	try{
		while (true)
			K3.pop();
	}
	catch (BrakDanych& e) {
		cout << "K3 pusty: " << e.what() << endl;
	}

	system("pause");
	return 0;
}
