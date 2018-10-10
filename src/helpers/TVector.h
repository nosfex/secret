#ifndef _TVECTOR_H_
#define _TVECTOR_H_
template <class T>
class TVector
{
public:
	TVector(T _x, T _y) ;
	TVector(const TVector<T>& other);
	virtual ~TVector();

	T X;
	T Y;
};
#endif // _TVECTOR_H_
