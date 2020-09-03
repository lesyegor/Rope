#ifndef ROPE_ROPE_CPP
#define ROPE_ROPE_CPP

#include "Rope.h"


template<typename T>
Rope<T>::Rope()
    : impTreap() {}

template<typename T>
Rope<T>::Rope(const Rope& otherRope)
    : impTreap(otherRope.impTreap) {}

template<typename T>
Rope<T>::Rope(Rope&& otherRope)
    : impTreap(std::move(otherRope.impTreap)) {}

template<typename T>
Rope<T>::Rope(const std::vector<T>& values)
    : impTreap(values) {}

template<typename T>
Rope<T>::Rope(std::vector<T>&& values)
    : impTreap(std::move(values)) {}

template<typename T>
Rope<T>::Rope(const std::string& s)
    : impTreap(s) {}

template<typename T>
Rope<T>::Rope(std::string&& s)
    : impTreap(std::move(s)) {}

template<typename T>
template<typename It>
Rope<T>::Rope(It first, It last)
    : impTreap(first, last) {}

template<typename T>
void Rope<T>::concat(Rope& other) {
    impTreap = ImplicitTreap<T>::merge((*this).impTreap, other.impTreap);
}

template<typename T>
std::pair<Rope<T>, Rope<T>> Rope<T>::split(size_t toCut) {
    auto p = (*this).impTreap.split(toCut);
    std::pair<Rope<T>, Rope<T>> result;
    result.first.impTreap = p.first;
    result.second.impTreap = p.second;
    return result;
}

template<typename T>
void Rope<T>::erase(size_t pos) {
    impTreap.erase(pos);
}

template<typename T>
void Rope<T>::erase(size_t pos, size_t cnt) {
    impTreap.erase(pos, cnt);
}

template<typename T>
void Rope<T>::insert(size_t pos, const T& value) {
    impTreap.insert(pos, value);
}

template<typename T>
template<typename It>
void Rope<T>::insert(size_t pos, It first, It last) {
    while (first != last) impTreap.insert(impTreap.getSize(), *first++);
}

template<typename T>
void Rope<T>::insert(size_t pos, Rope& otherRope) {
    impTreap.insert(pos, otherRope.impTreap);
}

template<typename T>
size_t Rope<T>::getSize() const {
    return impTreap.getSize();
}

template<typename T>
T& Rope<T>::operator[](int pos) {
    return impTreap.getValue(pos);
}

template<typename T>
const T& Rope<T>::operator[](int pos) const {
    return impTreap.getvalue(pos);
}

template<typename T>
bool Rope<T>::operator==(const Rope<T>& otherRope) const {
    if (otherRope.getSize() != getSize()) return false;
    size_t n = getSize();
    for (size_t i = 0; i < n; i++) {
        if ((*this)[i] != otherRope[i]) return false;
    }
    return true;
}

template<typename T>
bool Rope<T>::operator!=(const Rope<T>& otherRope) const {
    return !((*this) == otherRope);
}

template<typename T>
bool Rope<T>::operator<(const Rope<T>& otherRope) const {
    size_t n = getSize(), m = otherRope();
    std::vector<T> my_v(getSize()), other_v(otherRope.getSize());
    for (size_t i = 0; i < n; i++) my_v.push_back((*this)[i]);
    for (size_t i = 0; i < m; i++) other_v.push_back(otherRope[i]);
    return my_v < other_v;
}

template<typename T>
bool Rope<T>::operator<=(const Rope<T>& otherRope) const {
    return (*this) == otherRope || (*this) < otherRope;
}

template<typename T>
bool Rope<T>::operator>(const Rope<T>& otherRope) const {
    return !((*this) <= otherRope);
}

template<typename T>
bool Rope<T>::operator>=(const Rope <T>& otherRope) const {
    return !((*this) < otherRope);
}

#endif //ROPE_ROPE_CPP