#ifndef MY_VECTOR
#define MY_VECTOR

# include <bits/stdc++.h>


struct copyVector {

	std::vector<int> vec;
	int cnt;
};

struct myVector {
public:
	myVector();
	myVector(size_t sz);
	myVector(size_t sz, int val);
    myVector(const myVector& rhs);
    ~myVector();
	size_t size() const;
	void push_back(int rhs);
	void pop_back();
	int& operator[](int pos);
	const int& operator[](int pos) const;
    myVector& operator=(const myVector& rhs);
	bool empty() const;
	int& back();
	const int& back() const;
	size_t begin() const;
	size_t end() const;
	void reverseAll();
	void clear();
	void resize(size_t sz);
	void resize(size_t sz, int val);
	void myFill(int val);

private:
	void normalize();
	void safeOrDelete();
	void separate();

	union {
		int small;
		copyVector* my;
	};

	bool isSmall;
	bool isEmpty;
};
#endif