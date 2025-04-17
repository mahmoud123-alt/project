#pragma once
#include"LinkedQueue.h"
#include"Treatement.h"
#include "fstream"

enum statues { IDLE,ERLY,LATE,WAIT,SERV,FNSH };
class Patient
{
public:
	
	statues Patient_statue;
	
	int ID;
	char type;
	int VT, PT;
	LinkedQueue<Treatment*> Required_Treatments;
	

public:
	Patient(statues s, char t , int pt, int vt, LinkedQueue<Treatment*>& q, int ID ) :Patient_statue(s), type(t), PT(pt), VT(vt), ID(ID)
	{
		Required_Treatments = q;
	}
	void set_currentmode(statues x)
	{
		Patient_statue = x;

	}
	statues get_currentmode() {
		return Patient_statue;
	}

	



	 ostream& print(ostream & os) const {
		switch(Patient_statue) {

		case IDLE:
			os << "P" << ID << "_" << VT << ", ";
			break;
		case SERV:
			os << "P" << ID<<"_";
			Required_Treatments.print();
			break;
		case LATE:
			os << ID << ", ";
			break;
		case FNSH:
			os << ID << ", ";
			break;
		case WAIT:
			os << ID << ", ";
			break;
		case ERLY:
			os << ID << ", ";
				break;
			

		}
		return os;
		
		




		}

	
};

/*inline ostream& operator <<(ostream& out, const Patient& p)
{
	out << p.type << " " << p.VT << " " << p.PT << " ";
	p.Required_Treatments.print();
}*/
inline ostream& operator << (ostream& out, const Patient& p) {

	
	return p.print(out);


}

inline ostream& operator <<(ostream& out, Patient* const& p)
{
	out << *p;

	return out;
}
