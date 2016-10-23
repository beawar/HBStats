#ifndef VETTORE_H
#define VETTORE_H

#include "iterator.h"
#include <stddef.h>

#define DEFAULT_DIMENSION 10

template <class T>
class Vettore
{
    friend class Iterator<T>;

private:
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef size_t size_type;

    pointer array;
    unsigned int dim;
    unsigned int _size;

    static pointer copia (const Vettore&);
    static pointer ridimensiona (const Vettore<T>&, int);
    static bool confronta (const Vettore &, const Vettore &);

public:
    typedef Iterator<value_type, true> const_iterator;
    typedef Iterator<value_type, false> iterator;

    explicit Vettore();
    Vettore(size_type, const_reference);
    Vettore(size_type);

    Vettore(const Vettore&);
    ~Vettore();
    Vettore& operator =(const Vettore&);
    Vettore& operator +(const Vettore&);

    size_type size () const;
    size_type capacity () const;

    bool operator ==(const Vettore&)const;
    bool operator !=(const Vettore&)const;
    bool operator <(const Vettore&)const;
    bool operator <=(const Vettore&) const;
    bool operator >(const Vettore&) const;
    bool operator >=(const Vettore&) const;

    bool empty () const;

    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    iterator copia(iterator from_pos, iterator from_to, iterator to_pos);
    iterator insert(iterator, value_type);
    iterator insert(iterator, size_type, value_type);
    void insert(int, value_type);
    iterator erase(iterator);
    iterator erase(iterator, iterator);
    void erase (const_reference);
    void clear();

    void push_back (const_reference);
    void pop_back ();

    reference at(int) const;
    reference operator [](int) const;
    reference operator *() const;

};

//implementazione metodi template <class T> class Vettore

template <class T>
typename Vettore<T>::pointer Vettore<T>::copia(const Vettore<T>&v){
    T* aux = new T[v.dim];
    for(unsigned int i=0; i<v.size(); ++i){
        aux[i] = v.array[i];
    }
    return aux;
}

template <class T>
typename Vettore<T>::pointer Vettore<T>::ridimensiona(const Vettore<T>& v, int d){
    T* aux = new T[d];
    for(unsigned int i=0; i<(v.size()); ++i){
        aux[i] = v.array[i];
    }
    delete [] v.array;
    return aux;
}

template<class T>
bool Vettore<T>::confronta(const Vettore<T>& a, const Vettore<T>& b){
    if(!a.array && !b.array){
        return true;
    }
    else if(a.size() != b.size()){
        return false;
    }
    else{
        for(unsigned int i=0; i<a.size(); ++i){
            if(a[i] != b[i]){
                return false;
            }
        }
        return true;
    }
}

template <class T>
Vettore<T>::Vettore()
    :array(0), dim(0), _size(0) {}

template <class T>
Vettore<T>::Vettore(size_type n, const_reference t)
    :array(new T[n]), _size(n), dim(n){
    for(int i=0; i<n; ++i){
        array[i] = t;
    }    
}

template<class T>
Vettore<T>::Vettore(size_type n)
    :array(new T[n]), _size(0), dim(n) {}

template <class T>
Vettore<T>::Vettore(const Vettore<T>& v){
    array = copia(v);
    dim = v.dim;
    _size = v._size;
}

template <class T>
Vettore<T>::~Vettore(){
    delete [] array;
}

template <class T>
Vettore<T>& Vettore<T>::operator =(const Vettore<T>& v){
    if(*this != v){
        if(array){
            delete[] array;
        }
        dim = v.dim;
        _size = v._size;
        array = copia(v);
    }
    return *this;
}

template <class T>
Vettore<T>& Vettore<T>::operator +(const Vettore<T>& v){
   for(unsigned int i = 0; i<v.size(); ++i){
       push_back(v[i]);
   }
   return *this;
}

template <class T>
typename Vettore<T>::size_type Vettore<T>::size() const{
    return _size;
}

template<class T>
typename Vettore<T>::size_type Vettore<T>::capacity() const{
    return dim;
}

template<class T>
bool Vettore<T>::operator ==(const Vettore<T>& v) const{
    return confronta(*this, v);
}

template<class T>
bool Vettore<T>::operator !=(const Vettore<T>& v) const{
    return !confronta(*this, v);
}

template<class T>
bool Vettore<T>::operator <(const Vettore<T>& v) const{
    if(!v.array){
        return false;
    }
    else if(!array){
        return true;
    }
    else if(size() < v.size()){
        return true;
    }
    else if(size() > v.size()){
        return false;
    }
    else{
        for(int i=0; i<size(); ++i){
            if(array[i] > v.array[i]){
                return false;
            }
        }
        return true;
    }
}

template <class T>
bool Vettore<T>::operator <=(const Vettore<T>& v) const{
    return operator <(v) || operator ==(v);
}

template<class T>
bool Vettore<T>::operator >(const Vettore<T> & v) const{
    return !operator <=(v);
}

template<class T>
bool Vettore<T>::operator >=(const Vettore<T>& v) const{
    return !operator <(v);
}

template <class T>
bool Vettore<T>::empty() const{
    return size()==0;
}

template <class T>
typename Vettore<T>::iterator Vettore<T>::begin() const{
    iterator iaux(array);
    return iaux;
}

template <class T>
typename Vettore<T>::iterator Vettore<T>::end() const{
    iterator iaux(&array[size()]);
    return iaux;
}

template <class T>
typename Vettore<T>::const_iterator Vettore<T>::cbegin() const{
    const_iterator iaux(array);
    return iaux;
}

template <class T>
typename Vettore<T>::const_iterator Vettore<T>::cend() const{
    const_iterator iaux(&array[size()]);
    return iaux;
}

template <class T>
typename Vettore<T>::iterator Vettore<T>::copia(iterator from_pos, iterator from_to, iterator to_pos){
    while(from_pos != from_to){
        *to_pos = *from_pos;
        from_pos++;
        to_pos++;
    }
    return to_pos;
}

template <class T>
typename Vettore<T>::iterator Vettore<T>::insert(iterator it, value_type x){
    if(capacity() == size()){
        array = ridimensiona(*this, capacity() + DEFAULT_DIMENSION);
        dim += DEFAULT_DIMENSION;
    }
    int oldSize = size();
    ++_size;
    for(iterator i(&array[oldSize-1]); i >= it; --i){
        *(i+1) = *i;
    }
    *it = x;
    return it;
}

template <class T>
typename Vettore<T>::iterator Vettore<T>::insert(iterator it, size_type n, value_type x){
    for(int i=0; i<n; ++i){
        it = insert(it, x);
    }
    return it;

}

template <class T>
void Vettore<T>::insert(int index, value_type x){
    if(capacity() == size()){
        array = ridimensiona(*this, capacity() + DEFAULT_DIMENSION);
        dim += DEFAULT_DIMENSION;
    }
    int oldSize = size();
    ++_size;
    for(int i=oldSize-1; i>=index; --i){
        array[i+1] = array[i];
    }
    array[index] = x;
}

template <class T>
typename Vettore<T>::iterator Vettore<T>::erase(iterator it){
    for(iterator i=it; i<end(); ++i){
        *i = *(i+1);
    }
    pop_back();
    return it;
}

template <class T>
typename Vettore<T>::iterator Vettore<T>::erase(Vettore<T>::iterator from, Vettore<T>::iterator to){
    for(iterator it=from; it<to;){
        it=erase(it);
    }
    return to;
}

template <class T>
void Vettore<T>::erase(const_reference t){
    iterator it=begin();
    while(it<end()){
        if(*it==t){
            it = erase(it);
        }
        else{
            ++it;
        }
    }
}

template <class T>
void Vettore<T>::clear(){
    iterator temp = erase(begin(), end());
}

template <class T>
void Vettore<T>::push_back(const_reference t){
    if(capacity() == size()){
        array = ridimensiona(*this, dim + DEFAULT_DIMENSION);
        dim += DEFAULT_DIMENSION;
    }
    array[size()] = t;
    ++_size;
}

template <class T>
void Vettore<T>::pop_back(){
    if(capacity() - size() > DEFAULT_DIMENSION){
        array = ridimensiona(*this, capacity() - DEFAULT_DIMENSION);
        dim -= DEFAULT_DIMENSION;
    }
    --_size;
}

template <class T>
typename Vettore<T>::reference Vettore<T>::at (int i) const{
    return array[i];
}
template <class T>
typename Vettore<T>::reference Vettore<T>::operator [](int i) const{
    return array[i];
}

template <class T>
typename Vettore<T>::reference Vettore<T>::operator *() const{
    return *array;
}


#endif // VETTORE_H
