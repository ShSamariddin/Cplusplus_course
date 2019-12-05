#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <cstddef>
# include <string>
# include "myVector.h"
//#include <gmp.h>
#include <iosfwd>
#include <vector>
//#include "big_integer.cpp"

struct big_integer
{
    //enum operation { XOR, OR, AND };
    //friend big_integer boolyteFun(const std::vector<int>& a, const std::vector<int>& b, operation op);
    friend std::string to_string(big_integer const& a);
    friend big_integer from_byte(myVector v);
    friend big_integer rightShift(const myVector& a, int shift);

    friend big_integer leftShift(const myVector& a, int shift);
    friend myVector to_byte(myVector v, int sign);
    friend big_integer inverse(big_integer const& val);
    friend int bigger(const big_integer& a, const big_integer& b, bool cas);
    big_integer();
    big_integer(myVector ve, int si);
    big_integer(big_integer const& other);
    big_integer(int a);
    explicit big_integer(std::string const& str);
    big_integer(myVector vec);
    ~big_integer();

    big_integer& operator=(big_integer const& other);
    // int size() const;
    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    big_integer& operator/=(big_integer const& rhs);
    big_integer& operator%=(big_integer const& rhs);

    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs);

    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);

    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator!=(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);
    friend bool operator>(big_integer const& a, big_integer const& b);
    friend bool operator<=(big_integer const& a, big_integer const& b);
    friend bool operator>=(big_integer const& a, big_integer const& b);
    // int bigger(const big_integer& a, const big_integer& b, int cas);
    //friend std::string to_string(big_integer const& a);
private:
    myVector ans;
    int sign;
};

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);
big_integer operator/(big_integer a, big_integer const& b);
big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);
big_integer operator|(big_integer a, big_integer const& b);
big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int b);
big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);

#endif // BIG_INTEGER_H

