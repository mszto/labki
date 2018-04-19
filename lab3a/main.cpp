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

	friend class iterator;
};

double RandDouble(){
	return rand()%10;
}

template<typename T>
void Roznicuj(T i1, T i2, T i3){
	while (i1 != i2){
		*i1 = *i1 - *i3;
		i1++;
		i3++;
	}
}

template <typename T>
void DoKwadratu(T i1, T i2){
	while (i1 != i2){
		*i1 = *i1 *i1;
		i1++;
	}
}

template <typename T>
void sumuj(T i1, T i2, double &a){
	while (i1 != i2){
		a = a + *i1;
	}
}

template<typename T>
class Kalkulator{

	T

};


int main(){
	Konten<double> p;
	Konten<double> q;

	return 0;
}