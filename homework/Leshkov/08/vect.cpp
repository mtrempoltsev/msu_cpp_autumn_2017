#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <iterator>
#include <unistd.h>
using namespace std;


template<class T>
class RIterator : public std::iterator<std::random_access_iterator_tag, T>{

public:
	T* current;

    explicit RIterator(T *first): current(first) {}

    RIterator operator + (int n) const{
        return RIterator(current - n);
    }

    RIterator operator++(int){
        RIterator tmp(current--);
        return tmp;
    }

    RIterator& operator++(){
        --current;
        return *this;
    }

    RIterator operator - (int n) const{
        return RIterator(current + n);
    }

    RIterator operator--(int){
        RIterator tmp(current++);
        return tmp;
    }

    RIterator& operator--(){
        ++current;
        return *this;
    }

    bool operator==(const RIterator &it) const{
        return current == it.current;
    }

    bool operator!=(const RIterator &it) const{
        return !(*this == it);
    }

    T &operator*() {
        return *current;
    }

    const T &operator*() const{
        return *current;
    } 
};



template<class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T>{

public:
	T* current;

    explicit Iterator(T *first): current(first) {}

    Iterator operator + (int n) const{
        return Iterator(current + n);
    }

    Iterator operator++(int){
        Iterator tmp(current++);
        return tmp;
    }

    Iterator& operator++(){
        ++current;
        return *this;
    }

    Iterator operator - (int n) const{
        return Iterator(current - n);
    }

    Iterator operator--(int){
        Iterator tmp(current--);
        return tmp;
    }

    Iterator& operator--(){
        --current;
        return *this;
    }

    bool operator==(const Iterator &it) const{
        return current == it.current;
    }

    bool operator!=(const Iterator &it) const{
        return !(*this == it);
    }

    T &operator*() {
        return *current;
    }

    const T &operator*() const{
        return *current;
    } 
};


template <class T>
class Vect{
public:


	using iterator= Iterator<T>;
	using riterator= RIterator<T>;


	T* v;
	int memsize;
	int currelems;


	iterator begin(){
		return iterator(v);
	}
	
	iterator end(){
		return iterator(v+currelems);
	}

	riterator rbegin(){
		return riterator(v+currelems-1);
	}

	riterator rend(){
		return riterator(v-1);
	}
	


	Vect(int s=0, T init=0){
		if (s<0) throw 'V';
		v= new T[s];
		memsize =s;
		currelems =s;
		for (int i=0; i<s; i++)
			v[i]=init;
	}

	~Vect(){
		free(v);
	}

	void resize(int x){
		int i;
		T* q;
		if (memsize!=x){

			if (memsize>x){
				q=new T[x];
				for(i=0; i<x; i++)
					q[i]=v[i];
				delete[] v;
				currelems=x;
				memsize=x;
			}
			else{
				q=new T[x];
				for(i=0; i<currelems; i++)
					q[i]=v[i];
				memsize=x;
			}
			v=q;
		}
	}

	int size() noexcept {return currelems;}
	void clear() noexcept {resize(0);}
	bool empty() noexcept {return (currelems==0);}


	void push_back(T x){
		if (currelems==memsize)
			resize((memsize+1)*2);
		v[currelems]=x;
		currelems++;

	}

	T pop_back(){
		
		if(empty()){
			cout<<"Vect is empty";
			throw "pop_back\n";
		}

		T x=v[currelems];
		currelems--;

		if (memsize/2-1>currelems){
			resize(memsize/2);
		}

		return x;
	}
	

	
	T& operator[](int x){
			if ((x> this->currelems)||(x<0)){
				//cout<<"index out of range\n";
				throw '1';
			}
			return this->v[x];
	}

	friend ostream& operator<<(ostream& out, Vect<T>& vect){
	    	for (int i=0; i<vect.currelems; i++){
	    		out<<vect.v[i];
	    		out<<'	';
	    	}
	    	out<< endl;
	    	return out;
		}
};





void CheckOperator();
void CheckPush_back();
void CheckPop_back();
void CheckEmpty();
void CheckSize();
void CheckClear();
void CheckResize();
void CheckIterator();
void CheckReverseIterator();


int main(){




	try{
		CheckOperator();
		CheckPush_back();
		CheckEmpty();
		CheckSize();
		CheckClear();
		CheckResize();
		CheckIterator();
		CheckReverseIterator();
	}
	catch(const char* x){cout<<x<<endl;}
	catch(...){cout<<"Called catch(...)\n";}


	return 0;
}



void CheckReverseIterator(){
	Vect<int> a(0,0);
	int i;
	for(i=0; i<10; i++)
		a.push_back(i);
	
	for(auto iter=a.rbegin(); iter!=a.rend(); iter++){
		i--;
		if(*iter!=i){
			cout<<"Unexpected behavior of Reverseiterator rbegin/rend\n";
			throw "ReverseIterator";
		}

	}

}

void CheckIterator(){
	
	Vect<int> a(34,55);
	a.clear();

	Vect<int> b(6,11);
	b.resize(20);

	for(auto iter= a.begin(); iter!= a.end(); iter++)
		b.push_back(*iter);
	
	for(auto iter= b.begin(); iter!= b.end(); iter++){
		if(*iter!=11){
			cout<<"Unexpected behavior of iterator begin/end\n";
			throw "Iterator";
		}
	}
}


void CheckResize(){

	Vect<float> b(13,2);
	b.resize(5);
	if(b.size()!=5){
		cout<<"Error in size\n";
		throw "size";
	}
}




void CheckClear(){

	try{
		Vect<float> b(13,2);
		b.clear();
		b[2]=b[0];
		cout<<"Error in Clear\n";
		throw(1);
	}
	catch(char x){
		if (x!='1'){
			//operator[] Бросает исключение [1]
			throw x;
		}
	}
}

void CheckSize(){
	Vect<float> a(0,0);
	Vect<float> b(13,2);
	if((a.size()!=0) ||(b.size()!=13)){
		cout<<"Error: In size\n";
		throw "size";
	}

}

void CheckEmpty(){

	Vect<float> a(0,0);
	if (a.empty()!=true){
		cout<<"Error: In empty\n";
		throw "empty";
	}
}

void CheckPush_back(){
	Vect<char> a(13,'f');
	a.push_back('e');
	if(a[13]!='e'){
		cout<<"Error: In Push_Back\n";
		throw "Push_Back";
	}
}

void CheckPop_back(){
	Vect<char> a(13,'f');
	a.push_back('e');
	if(a.pop_back()!='e'){
		cout<<"Error: In Pop_Back\n";
		throw "Pop_Back";
	}
}

void CheckOperator(){
	Vect<int> a(5,3);
	a[3]=31415;
	if(a[3]!=31415){
		cout<<"Error: Operator[]\n";
		throw "CheckOperator";
	}
}



