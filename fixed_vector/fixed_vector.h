//
// Created by Samariddin on 24.09.2018.
//

#ifndef UNTITLED_FIXED_VECTOR_H
#define UNTITLED_FIXED_VECTOR_H

# include <assert.h>
#include <iostream>

template<typename T, size_t si>
class fixed_vector {
public:
    using iterator = T *;
    using const_iterator = const T *;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin() {
        return iterator(reinterpret_cast<T *>(data));
    }

    const_iterator begin() const {
        return const_iterator((reinterpret_cast<const T *>(data)));
    }

    iterator end() {
        return begin() + pos;
    }

    const_iterator end() const {
        return begin() + pos;
    }

    const_iterator cend() const {
        return end();
    }

    const_iterator cbegin() const {
        return begin();
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(begin());
    }

private:
public:
    fixed_vector() : pos(0) {}

    fixed_vector(const fixed_vector &other){
        try {
            pos = 0;
            for(const_iterator it = other.begin(); it != other.end(); it ++) {
                push_back(T(*it));
            }
        } catch(...) {
            while(!empty()) {
                pop_back();
            }
        }
    }
    fixed_vector& operator=(const fixed_vector& other){
        fixed_vector new_other(other);
        swap(*this, new_other);
        return *this;
    }

    ~fixed_vector(){
        for(size_t i = 0; i < pos; i++) {
            reinterpret_cast<T*> (&data[i])->~T();
        }
    }


    bool empty() const {//+
        return !pos;
    }

    size_t size() const {//+
        return pos;
    }

    constexpr size_t max_size() const {//+
        return si;
    }

    constexpr size_t capacity() const {//+
        return si;
    }

    void push_back(const T &value) {//
        assert(pos < si);
        new(&data[pos])T(value);
        pos++;
    }

    void pop_back() {//+
        assert(pos != 0);
        reinterpret_cast<T *> (&data[pos - 1])->~T();
        pos--;
    }

    void clear() {//+
        while (pos) {
            pop_back();
        }
    }

    T &back() {//+
        return *reinterpret_cast<T *> (&data[pos - 1]);
    }

    const T &back() const {
        return *reinterpret_cast<const T *> (&data[pos - 1]);
    }

    T &front() {//+
        return *reinterpret_cast<T *> (&data[0]);
    }

    const T &front() const {
        return *reinterpret_cast<const T *> (&data[0]);
    }

    T &operator[](size_t ind) {//+
        return *reinterpret_cast<T *> (&data[ind]);
    }

    const T &operator[](size_t ind) const {
        return *reinterpret_cast<const T *>(&data[ind]);
    }

    iterator erase(const_iterator er_pos) {
        auto i = static_cast<size_t>(std::distance(cbegin(), er_pos));
        for (; i + 1 < size(); i++) {
            data[i] = data[i + 1];
        }
        pop_back();
        return iterator(er_pos);
    }

    iterator insert(const_iterator in_pos, T const &value) {
        push_back(value);
        auto x = static_cast<size_t>(std::distance(cbegin(), in_pos));
        for (auto i = size() - 1; i >= x + 1; i--) {
            swap(data[i], data[i - 1]);
        }
        return iterator(in_pos);
    }
    friend void swap(fixed_vector &first, fixed_vector &second) noexcept {
        std::swap(first.data, second.data);
        std::swap(first.pos, second.pos);
    }


private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data[si];
    size_t pos;

};


#endif //UNTITLED_FIXED_VECTOR_H
