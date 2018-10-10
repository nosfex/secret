#include "TVector.h"
template <class T>
TVector<T>::TVector(T _x, T _y) : X(_x), Y(_y)
{}
template <class T>
TVector<T>::~TVector()
{
}
template <class T>
TVector<T>::TVector(const TVector<T>& other)
{
	X = other.X;
	Y = other.Y;
}
template<>
TVector<float>::TVector(float _x, float _y) : X(_x), Y(_y)
{}