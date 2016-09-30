#ifndef ITERATOR_H
#define ITERATOR_H

#include <stddef.h>


template <bool flag, class _nConst, class _Const>
struct const_or_notc;

template <class _nConst, class _Const>
struct const_or_notc<true, _nConst, _Const>{
    typedef _Const type;
};

template <class _nConst, class _Const>
struct const_or_notc<false, _nConst, _Const>{
    typedef _nConst type;
};


template <class T, bool is_const = true>
class Iterator{

private:
    typedef T value_type;
    typedef typename const_or_notc<is_const, value_type&, const value_type&>::type reference;
    typedef typename const_or_notc<is_const, value_type*, const value_type*>::type pointer;
    typedef size_t syze_type;

    pointer punt;

public:
    explicit Iterator(pointer =0);
    Iterator(const Iterator&);

    bool operator ==(const Iterator&) const;
    bool operator !=(const Iterator&) const;
    bool operator <(const Iterator&) const;
    bool operator <=(const Iterator&) const;
    bool operator >(const Iterator&) const;
    bool operator >=(const Iterator&) const;

    Iterator& operator =(pointer);
    Iterator& operator =(const Iterator&);
    Iterator& operator ++();
    Iterator operator ++(int);
    Iterator& operator--();
    Iterator operator --(int);
    Iterator& operator += (int);
    Iterator operator +(int);
    Iterator& operator -=(int);
    Iterator operator -(int);
    reference operator *() const;

};

//implementazione metodi template <class T, bool is_const> class Iterator

template <class T, bool is_const>
Iterator<T, is_const>::Iterator(pointer p)
    :punt(p) {}

template <class T, bool is_const>
Iterator<T, is_const>::Iterator(const Iterator<T, is_const>& it)
    :punt(it.punt) {}

template <class T, bool is_const>
bool Iterator<T, is_const>::operator ==(const Iterator<T, is_const>& it) const{
    return punt==it.punt;
}

template <class T, bool is_const>
bool Iterator<T, is_const>::operator !=(const Iterator<T, is_const>& it) const{
    return punt!=it.punt;
}

template <class T, bool is_const>
bool Iterator<T, is_const>::operator <(const Iterator<T, is_const>& it) const{
    return punt<it.punt;
}

template <class T, bool is_const>
bool Iterator<T, is_const>::operator <=(const Iterator<T, is_const>& it) const{
    return punt<=it.punt;
}

template <class T, bool is_const>
bool Iterator<T, is_const>::operator >(const Iterator<T, is_const>& it) const{
    return punt>it.punt;
}

template <class T, bool is_const>
bool Iterator<T, is_const>::operator >=(const Iterator<T, is_const>& it) const{
    return punt>=it.punt;
}

template <class T, bool is_const>
Iterator<T, is_const>& Iterator<T, is_const>::operator =(pointer x) {
    punt = x;
    return *this;
}

template <class T, bool is_const>
Iterator<T, is_const>& Iterator<T, is_const>::operator =(const Iterator<T, is_const>& it) {
    punt = it.punt;
    return *this;
}

template <class T, bool is_const>
Iterator<T, is_const>& Iterator<T, is_const>::operator ++() {
    if(punt)
        ++punt;
    return *this;
}

template <class T, bool is_const>
Iterator<T, is_const> Iterator<T, is_const>::operator ++(int x) {
    Iterator<T, is_const> temp = *this;
    if(punt){
        ++punt;
    }
    return temp;
}

template <class T, bool is_const>
Iterator<T, is_const>& Iterator<T, is_const>::operator --() {
    if(punt)
        --punt;
    return *this;
}

template <class T, bool is_const>
Iterator<T, is_const> Iterator<T, is_const>::operator --(int x) {
    Iterator<T, is_const> temp = *this;
    if(punt){
        --punt;
    }
    return temp;
}

template <class T, bool is_const>
Iterator<T, is_const>& Iterator<T, is_const>::operator +=(int x) {
    if(punt)
        punt+=x;
    return *this;
}

template <class T, bool is_const>
Iterator<T, is_const> Iterator<T, is_const>::operator +(int x) {
    Iterator<T, is_const> temp = *this;
    temp += x;
    return temp;
}

template <class T, bool is_const>
Iterator<T, is_const>& Iterator<T, is_const>::operator -=(int x) {
    if(punt)
        punt-=x;
    return *this;
}

template <class T, bool is_const>
Iterator<T, is_const> Iterator<T, is_const>::operator -(int x) {
    Iterator<T, is_const> temp = *this;
    temp += x;
    return temp;
}

template <class T, bool is_const>
typename Iterator<T, is_const>::reference Iterator<T, is_const>::operator *() const{
    return *punt;
}

#endif // ITERATOR_H
