#pragma once
#include"Resource.h"


class Treatment
{
public:

	int duration;
	int ST;
	Resource* rptr;

public:

	Treatment(int d) :duration(d)
	{
		rptr = nullptr;
		ST = 0;
	}

	virtual bool CanAssign()		//	waiting -> in-treatment 
	{
		return rptr;
	}
	virtual void MoveToWait() = 0;

	virtual ~Treatment()
	{

	}

};

class U_Treatment :public Treatment
{
public:
	U_Treatment(int d) :Treatment(d)
	{

	}
	virtual void MoveToWait()
	{

	}
};

class E_Treatment :public Treatment
{
public:
	E_Treatment(int d) :Treatment(d)
	{

	}
	virtual void MoveToWait()
	{

	}
};

class X_Treatment : public Treatment
{
public:
	X_Treatment(int d) :Treatment(d)
	{

	}
	virtual void MoveToWait()
	{

	}
};



inline ostream& operator <<(ostream& out, U_Treatment& u)
{
	out << "U " << u.duration << " ";
	return out;
}
inline ostream& operator <<(ostream& out, E_Treatment& e)
{
	out << "E " << e.duration << " ";
	return out;
}
inline ostream& operator <<(ostream& out, X_Treatment& x)
{
	out << "X " << x.duration << " ";
	return out;
}

inline ostream& operator <<(ostream& out, Treatment* const& t)
{
	if (U_Treatment* ptr = dynamic_cast<U_Treatment*>(t))
	{
		out << *ptr;
	}
	else if (E_Treatment* ptr = dynamic_cast<E_Treatment*>(t))
	{
		out << *ptr;
	}
	else if (X_Treatment* ptr = dynamic_cast<X_Treatment*>(t))
	{
		out << *ptr;
	}
	return out;
}
