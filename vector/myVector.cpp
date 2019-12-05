# include <bits/stdc++.h>
# include "myVector.h"
using namespace std;

myVector::myVector() : small(0), isSmall(false), isEmpty(true){}

myVector::myVector(const myVector& rhs) : isSmall(rhs.isSmall),isEmpty(rhs.isEmpty)
{
	if(isEmpty)
		return;
	if(rhs.isSmall)
	{
		small = rhs.small;
	} else{
		my = rhs.my;
		my->cnt++;
	}
}

void myVector::separate()
{
	if(my->cnt > 1)
	{
		copyVector* newVector = new copyVector();
		my->cnt--;
		newVector->vec = my->vec;
		newVector->cnt = 1;
		swap(newVector, my);
	} 
}

int& myVector::operator[](int pos){
	if(isSmall && pos > 0){
		throw "out of bound";
	}
	if(isSmall)
		return small;
	separate();
	return my->vec[pos];
}


const int& myVector::operator[](int pos) const{
	if(isSmall && pos > 0){
		throw "out of bound";
	}
	if(isSmall)
		return small;
	return my->vec[pos];
} 

size_t myVector::size() const
{
	if(isEmpty)
		return (size_t) 0;
	if(isSmall)
		return (size_t) 1;
	return my->vec.size();
}

void myVector::push_back(int rhs){
	if(isEmpty){
		small = rhs;
		isSmall = true;
		isEmpty = false;
	} else{
		if(isSmall){
			int temp = small;
			copyVector* newVector = new copyVector();
			newVector->cnt = 1;
			newVector->vec.push_back(temp);
			newVector->vec.push_back(rhs);
			swap(newVector, my);
			isSmall = false;
		} else{
			separate();
			my->vec.push_back(rhs);
		}
	}
}

void myVector::safeOrDelete(){

	if(my->cnt > 1){
		my->cnt --;
	} else{
		delete my;
	}
}

myVector::~myVector()
{
	if (!isEmpty && !isSmall)
		safeOrDelete();
}

void myVector::normalize(){
	if(!isEmpty && !isSmall && my->vec.size() == 1){
		separate();
		int number = my->vec[0];
		safeOrDelete();
		small = number;
		isSmall = true;
	}
}

void myVector::pop_back(){
	if(isEmpty){
		throw "vector is empty";
	}
	if(isSmall){
		isSmall = false;
		isEmpty = true;
	} else{
		separate();
		my->vec.pop_back();
	}
	normalize();
}

bool myVector::empty() const{
	return (size() == 0);
} 

int& myVector::back(){
	if(isEmpty){
		throw "out of band";
	}
	if(isSmall)
		return small;
	return my->vec.back();
}

const int& myVector::back() const{
	if(isEmpty){
		throw "out of band";
	}
	if(isSmall)
		return small;
	return my->vec.back();
}

size_t myVector::begin() const{
	return size_t(0);
}

size_t myVector::end() const{
	return size();
}

void myVector::reverseAll(){
	if(isEmpty || isSmall)
		return ;
	separate();
	reverse(my->vec.begin(), my->vec.end());
}

void myVector::clear(){
	if(!isSmall && !isEmpty){
		separate();
		my->vec.clear();
		safeOrDelete();
	}
	isEmpty = true;
}

void myVector::resize(size_t sz, int val)
{
	while(sz > size())
	{
	
		push_back(val);
	}
	//cout << "samar the best\n";
	//cout << sz<<' '<<size()<<'\n';
	//cin>> el;
	while(sz < size())
	{
		pop_back();
	}
	//cout << "sag";
	//cin>> el;
}
void myVector::resize(size_t sz)
{

	
	resize(sz, 0);

}

myVector::myVector(size_t sz) : myVector() 
{
	resize(sz);
}
myVector::myVector(size_t sz, int val) : small(0), isSmall(false), isEmpty(true)
{
	resize(sz, val);
}

void myVector::myFill(int val){
	if(isEmpty){
		return ;
	} else if(isSmall){
		small = val;
	} else{
		separate();
		fill(my->vec.begin(), my->vec.end(), val);
	}
}

myVector& myVector::operator=(const myVector& rhs)
{
    if (rhs.isEmpty)
        return *this;
    if (rhs.isSmall)
    {
    	if(!isEmpty && !isSmall && my->cnt > 1){
    		my->cnt --;
    	} else if(!isEmpty && !isSmall){
    		delete my;
    	}
        small = rhs.small;
    }
    else
    {
    	if (my == rhs.my){
			isSmall = rhs.isSmall;
    		isEmpty = rhs.isEmpty;
    		return *this;
    	}
    	if(!isEmpty && !isSmall && my->cnt > 1){
    		my->cnt--;
    	} else if(!isEmpty && !isSmall){
    		delete my;
    	}
        my = rhs.my;
        my->cnt++;
    }
    isSmall = rhs.isSmall;
    isEmpty = rhs.isEmpty;
    return *this;
}
