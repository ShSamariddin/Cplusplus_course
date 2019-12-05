#ifndef PER_SET_H
#define PER_SET_H

# include<iostream>


template<typename T>
class per_set
{
public:
    struct node{
        node  *l, *r, *p;
        T value;
        ~node();
    };
    template<typename T>
    per_set(){}
};



#endif // SET_H
