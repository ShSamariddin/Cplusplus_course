#include "big_integer.h"

#include <cstring>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

__extension__ typedef __int128 int128_t;
const long long int MaxNumber = (1ll<<31ll);
const int MaxBit = (int) (MaxNumber - 1ll);
const int MaxPow = 31;

big_integer::big_integer() : ans(1, 0), sign(1){}


big_integer::big_integer(big_integer const& other): ans(other.ans), sign(other.sign){}

big_integer::big_integer(int val)
{   

    if (val >= 0)
        sign = 1;
    else
        sign = -1;
    long long int value = abs((long long) val);
    ans.clear();
    if (value == 0)
        ans.push_back(0);
    while (value > 0)
    {
        ans.push_back((value) % MaxNumber);
        value /= MaxNumber;
    }
 
}

big_integer::big_integer(myVector ve, int si) : sign(si) 
{
    ans = ve;
}

void normalization_vector(myVector& val){
    if (val.empty())
    {
        val.push_back(0);
    }
    while (val.size() != 1 && val.back() == 0)
    {
        val.pop_back();
    }
}



void  next_bit(long long int mult, long long const& div, const myVector a, myVector& res, int& mod){
    long long int cur_res = 0;
    res.resize(a.size(), 0);

    for(int i = a.size() - 1; i >= 0; i --)
    {
        cur_res = cur_res * mult + a[i];
        res[i] = cur_res / div;
        cur_res = cur_res % div;
    }
    mod = (int) cur_res;
    normalization_vector(res);
}

/*int big_integer::size() const {
    return ans.size();
}*/

big_integer::big_integer(std::string const& str)
{
    myVector v;
    ans.clear();
    sign = 1;
    int t = 0;
    if(str[0] == '-')
    {
        sign = -1;
        t = 1;
    }
    for(int i = str.size() - 1; i >= t; i --)
    {
        v.push_back(str[i] - '0');
    }
    int mod = 0;

    while(v.size() != 1 || v[0] != 0)
    {
        next_bit(10ll, MaxNumber, v, v, mod);
        ans.push_back(mod);
    }

    normalization_vector(ans);
    if(ans.size() == 1 && ans[0] == 0)
        sign = 1;
} 

big_integer::~big_integer() {}

big_integer big_integer::operator+() const
{
    return *this;
}

big_integer big_integer::operator-() const
{

    if(*this == 0){
        return 0;
    } else{
        big_integer b = *this;
        b.sign *= -1;
        return b;
    }
} 

big_integer big_integer::operator~() const
{
    return (-(*this) - 1);
}

big_integer inverse(big_integer const& val)
{
    big_integer rhs(val);
    for (size_t i = 0; i < rhs.ans.size(); ++i)
    {
        rhs.ans[i] = -(rhs.ans[i]);
    }
    return rhs;
}

myVector to_byte(myVector v, int sign)
{
    if (sign < 0)
    {
        big_integer a = big_integer(v, 1);
        v = ((inverse(big_integer(v, 1)))).ans;
    }
    v.push_back((sign >= 0) ? 0 : MaxBit);
    return v;
}

big_integer from_byte(myVector v)
{
    int sign = 1;
    if (v.back() == MaxBit)
        sign = -1;
    v.pop_back();
    // cout << "qq\n";
    big_integer res = ((sign == -1) ? big_integer(((inverse(big_integer(v, 1)))).ans, -1) : big_integer(v, 1));
    // cout<<"tt\n";
    if (res.ans.size() == 1 && res.ans[0] == 0)
        res.sign = 1;
    // cout << "qqq\n";
    return res;

}

enum operation { XOR, OR, AND };

big_integer byteFun(const myVector& a, const myVector& b, operation op)
{
    myVector res(max(a.size(), b.size()));
    for(int i = 0; i < (int)res.size(); i++)
    {
        if (op == AND)
            res[i] = a[min((int)a.size() - 1, i)] & b[min((int)b.size() - 1, i)];
        else if (op == OR)
            res[i] = a[min((int)a.size() - 1, i)] | b[min((int)b.size() - 1, i)];
        else
            res[i] = a[min((int)a.size() - 1, i)] ^ b[min((int)b.size() - 1, i)];
    }
    return from_byte(res);
}

big_integer leftShift(const myVector& a, int shift)
{
     myVector res(shift / MaxPow, 0);
    long long int cur = 0;
    int last = a.back();
    shift %= MaxPow;
   
    for (size_t i = 0; i < a.size(); i ++){
        cur += ((long long int) a[i]) << shift;
        //cout << shift<<' '<<cur<<' '<<MaxBit<<'\n';
        res.push_back(cur % MaxBit);
        cur /= MaxBit;
        cur >>= MaxPow;
    }
   // for(int i = 0; i < res.size(); i ++) cout << res[i]<<' ';cout<<'\n';
    res.push_back(last);
    while (res.size() > 1 && res.back() == res[res.size() - 2])
        res.pop_back();
    return from_byte(res);
}

big_integer rightShift(const myVector& a, int shift)
{   
    myVector res;
    int last = 0;
    int i = shift / MaxPow;
    shift %= MaxPow;
    long long int cur = a[i] >> shift;
    // cout << "pop\n";
    while(i + 1 < (int)a.size())
    {
        cur = cur + (((int) a[i + 1]) << (MaxPow - shift));
        res.push_back(cur & (long long int) MaxBit);
        cur >>= MaxPow;
        i++;
    }
    if (cur)
        res.push_back(cur);
    res.push_back(last);

    // cout <<"top\n";
    while (res.size() > 1 && res.back() == res[res.size() - 2])
        res.pop_back();
    return from_byte(res);
}

big_integer& big_integer::operator=(big_integer const& other)
{
   // cout << sign<<' '<<other.sign<<'\n';
    sign = other.sign;
    // for(int i = 0; i < ans.size(); i ++) cout << ans[i]<<' ';cout<<'\n';
    // for(int i = 0; i < other.ans.size(); i ++) cout << other.ans[i]<<' ';cout<<'\n';
    ans = other.ans;
    return *this;
}

void add(myVector& res, const myVector& a, const myVector& b)
{   
    long long int carry = 0;
    res.resize(max(a.size(), b.size()));

    for(int i = 0; i < (int) res.size(); i++)
    {
        carry += (i < (int) a.size() ? (long long int) a[i]: 0) + (i < (int) b.size() ? (long long int) b[i]: 0);
        res[i] = carry % MaxNumber;
        carry /= MaxNumber;
    }
    if(carry != 0)
    {
        res.push_back(carry);
    }
    normalization_vector(res);
}

void sub(myVector& res, const myVector& a, const myVector& b)
{
    myVector result = a;
    long long int cur;
    for (size_t i = 0; i < result.size(); ++i)
    {
        cur = result[i];
        if (result[i] < (i < b.size() ? b[i] : 0))
        {
            cur += MaxNumber;
            result[i + 1]--;
        }
        cur -= (i < b.size() ? b[i] : 0);
        result[i] = cur;
    }
    res = result;
    normalization_vector(res);
}

void mul(myVector &res, const myVector a, const myVector &b)
{
    res.resize(a.size() + b.size() + 1);
    res.myFill(0);
    long long int carry;
    vector<long long int> resTemp;
    resTemp.resize(a.size() + b.size() + 1);
    long long int cur;
    for (size_t i = 0; i < a.size(); ++i)
    {
        carry = 0;
        for (size_t j = 0; j < b.size(); ++j)
        {
            cur = resTemp[i + j] + a[i] * 1ll* b[j];
            resTemp[i + j] = cur % MaxNumber;
            carry = cur / MaxNumber;
            resTemp[i + j + 1] += carry;
        }
    }
    for (size_t i = 0; i < resTemp.size(); ++i)
    {
        res[i] = (int) resTemp[i];
    }
    normalization_vector(res);
}

int vec_cmp(myVector const &a, myVector const &b, int pos1, int pos2, int len)
{
     int x, y;
     for (int i = 0; i < len; ++i)
     {
        x = a[pos1 - i];
        y = b[pos2 - i];
        if (x != y)
        {
            return x > y ? 1 : -1;
        }
     }
     return 0;
}

int bigPref(const myVector& a, int pos, int len, myVector& b)
{
    while (len > 0 && pos >= 0 && a[pos] == 0)
    {
        --len;
        --pos;
    }
    if (len == 0)
    {
        pos++;
        len++;
    }
    if ((int) b.size() != len)
    {
        return len < (int) b.size() ? -1 : 1;
    }
    return vec_cmp(a, b, pos, (int) b.size() - 1, len);
}

void subPref(myVector& a, int pos, int len, const myVector& b)
{
    long long int cur;

    int pos2 = pos - len + 1;

    for (int i = 0; i < len; ++i)
    {
        cur = a[pos2 + i];
        if (a[pos2 + i] < (i < (int) b.size() ? b[i] : 0)) 
        {
            cur += MaxNumber;
            a[pos2 + i + 1]--;
        }
        cur -= (i < (int) b.size() ? b[i] : 0);
        a[pos2 + i] = cur;
    }
    return;
}

void div(myVector& res, myVector a, const myVector& b)
{
    if (a.size() < b.size())
    {
        res.clear();
        res.push_back(0);
        return;
    }
    else if (b.size() == 1)
    {
        int nth = 0;
        next_bit(MaxNumber, b[0], a, res, nth);
        return;
    }
    res.clear();
    int128_t divident = 0, divisor = 0, result = 0;
    myVector temp;
    a.push_back(0);
    for (int i = (int) a.size() - 1; i >= (int) b.size(); --i)
    {
        divident = ((int128_t) a[i]) * ((int128_t) MaxNumber) * ((int128_t) MaxNumber) + ((int128_t) a[i - 1]) * ((int128_t) MaxNumber) + ((int128_t) a[i - 2]);
        divisor = ((int128_t) b[b.size() - 1]) * ((int128_t) MaxNumber) + ((int128_t) b[b.size() - 2]);
        result = divident / divisor;
        result = min(result, (int128_t) MaxBit);
        mul(temp, myVector(1, (int) result), b);
        if (bigPref(a, i, (int) b.size() + 1, temp) == -1)
        {
            --result;
            mul(temp, myVector(1, (int) result), b);
        }
        res.push_back((int) result);
        subPref(a, i, (int) b.size() + 1, temp);
    }
    res.reverseAll();
    normalization_vector(res);
}


int bigger(const big_integer& a, const big_integer& b, bool cas = 0)
{
    if (!cas && a.sign != b.sign)
        return (a.sign > b.sign ? 1 : -1);
    if (a.ans.size() != b.ans.size())
    {
        if (a.ans.size() > b.ans.size()  && a.sign == 1 && !cas)
            return 1;
        if (a.ans.size() < b.ans.size() && a.sign == -1 && !cas)
            return 1;
        if (cas && a.ans.size() > b.ans.size())
            return 1;
        return -1;
    }
    for (int i = a.ans.size() - 1; i >= 0; --i)
    {
        if (a.ans[i] == b.ans[i])
            continue;
        if (!cas && a.ans[i] > b.ans[i] && a.sign == 1)
            return 1;
        if (!cas && a.ans[i] < b.ans[i] && a.sign == -1)
            return 1;
        if (cas)
            return (a.ans[i] > b.ans[i]) ? 1 : -1;
        return -1;
    }
    return 0;
} 

big_integer& big_integer::operator/=(big_integer const& rhs)
{
    int signO = rhs.sign;
    div(ans, ans, rhs.ans);
    sign *= signO;
    return *this;
}

big_integer& big_integer::operator+=(big_integer const& value)
{   
    if(sign == value.sign){
        add(ans, ans, value.ans);
    } else{
        int big = bigger(*this, value, true);
        if(big == 1){
            sub(ans, ans, value.ans);
        } else{
            sub(ans, value.ans, ans), sign = value.sign;
        }
    }
    if(ans.size() == 1 && ans[0] == 0)
    {
        sign = 1;
    }

    return *this;
}

big_integer& big_integer::operator-=(big_integer const& rhs)
{
    return *this += -rhs;
}

big_integer& big_integer::operator*=(big_integer const& rhs)
{
    mul(ans, ans, rhs.ans);
    sign *= rhs.sign;
    return *this;
}


big_integer& big_integer::operator%=(big_integer const& rhs)
{
    *this = *this - (*this / rhs) * rhs;
    return *this;
}

big_integer& big_integer::operator&=(big_integer const& rhs)
{   
    
    return *this = byteFun(to_byte(ans, sign), to_byte(rhs.ans, rhs.sign), AND);
}

big_integer& big_integer::operator|=(big_integer const& rhs)
{
    return *this = byteFun(to_byte(ans, sign), to_byte(rhs.ans, rhs.sign), OR);
}

big_integer& big_integer::operator^=(big_integer const& rhs)
{
    return *this = byteFun(to_byte(ans, sign), to_byte(rhs.ans, rhs.sign), XOR);
}

big_integer& big_integer::operator<<=(int rhs)
{
        int q = sign;
        *this = leftShift(ans, rhs);
        sign = q;
    return *this;
}

big_integer& big_integer::operator>>=(int rhs)
{ 
    int q = sign;
    if(sign == -1){
        *this += 1;
    } 
    *this = rightShift(ans, rhs);
    if(q == -1)  
    *this += 1;
    sign = q;

    return *this;
}


big_integer& big_integer::operator++()
{
    return (*this += 1);
}

big_integer big_integer::operator++(int)
{
    big_integer res = *this;
    ++*this;
    return res;
}

big_integer& big_integer::operator--()
{
    //mpz_sub_ui(mpz, mpz, 1);
    return (*this -= 1);
}

big_integer big_integer::operator--(int)
{
    big_integer r = *this;
    *this = *this - 1;
    return r;
}

big_integer operator+(big_integer a, big_integer const& b)
{
     a += b;
     return a;
}

big_integer operator-(big_integer a, big_integer const& b)
{
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const& b)
{
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const& b)
{
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const& b)
{
    return a %= b;
}

big_integer operator&(big_integer a, big_integer const& b)
{
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const& b)
{
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const& b)
{
    return a ^= b;
}

big_integer operator<<(big_integer a, int b)
{
    return a <<= b;
}

big_integer operator>>(big_integer a, int b)
{
    return a >>= b;
}

bool operator==(big_integer const& a, big_integer const& b)
{
    return bigger(a, b) == 0;;
}

bool operator!=(big_integer const& a, big_integer const& b)
{
    return bigger(a, b) != 0;
}

bool operator<(big_integer const& a, big_integer const& b)
{
    return bigger(a, b) == -1;
}

bool operator>(big_integer const& a, big_integer const& b)
{
    return bigger(a, b) == 1;
}

bool operator>=(big_integer const& a, big_integer const& b)
{
    return bigger(a, b) != -1;
}

bool operator<=(big_integer const& a, big_integer const& b)
{
    return bigger(a, b) != 1;
}

string to_string(big_integer const& a)
{

    std::string res = "";
    myVector v_res = a.ans;
    int mod;
    while(v_res.size() != 1 || v_res[0] != 0){
        next_bit(MaxNumber, 10, v_res, v_res, mod);
        res = res + char(mod + 48);
    }
    if(a.sign == -1)
    {
        res += '-';
    }
    reverse(res.begin(), res.end());
    return (res.size() ? res: "0");
}

std::ostream& operator<<(std::ostream& s, big_integer const& a)
{
    return s << to_string(a);
}

