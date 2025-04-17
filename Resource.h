#pragma once
#include<iostream>
using namespace std;


class Resource
{
public:
	string type;
	int id;
	int capacity;
	int occupation;

public:
	Resource(string name, int i, int c) :type(name), id(i), capacity(c)
	{
		occupation = 0;
	}
	Resource()
	{
		type = "none";
		id = capacity = occupation = 0;
	}
	
	
};

inline ostream& operator << (ostream& out, const Resource& r)
{
	if (r.type == "X")
	{
		out << "R" << r.id << "[" << r.occupation << "," << r.capacity << "], ";
		return out;
	}
	else
	{
		out << r.type << r.id << ' ';
		return out;  
	}
}

inline ostream& operator << (ostream& out, Resource* const &r)
{
	
	cout << *r;
	return out;
}
