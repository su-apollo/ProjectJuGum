
#pragma once

template <typename T>
inline void SafeDelete( T* &p )
{
	if ( p != nullptr )
	{
		delete p;
		p = nullptr;
	}
}

template <typename T>
inline void SafeArrayDelete( T* &p )
{
	if ( p != nullptr )
	{
		delete[] p;
		p = nullptr;
	}
}

template <typename T>
inline void SafeRelease( T* &p )
{
	if ( p != nullptr )
	{
		p->Release();
		p = nullptr;
	}
}

#define NN_PI 3.14159265358979

inline float NNDegreeToRadian( float n )
{
	return n / 180.f * (float)NN_PI;
}
inline double NNDegreeToRadian( double n )
{
	return n / 180 * NN_PI;
}

inline float NNRadianToDegree( float n )
{
	return n * 180.f / (float)NN_PI;
}
inline double NNRadianToDegree( double n )
{
	return n * 180 / NN_PI;
}

inline float NNAngleToX( int angle )
{
	return (float)cos(NN_PI*angle/180);
}

inline float NNAngleToY( int angle )
{
	return (float)sin(NN_PI*angle/180);
}

#define SINGLETON(type) \
	public: \
	type(); \
	~type(); \
	public: \
	static type* GetInstance() {static type s; return &s;}