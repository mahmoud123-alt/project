#include<iostream>
#include<fstream>
#include"Scheduler.h"

using namespace std;

//hi gethub 

int main()
{
    Scheduler s;
    

   //aaaa

    
    s.LoadPatientsFromFile("input.txt");

    
    s.Simulation();

   

    /*
    s.print();

    Scheduler sch;

    LinkedQueue<Treatment*> q1;
    q1.enqueue(new U_Treatment(5));   // 5 timesteps of U

    LinkedQueue<Treatment*> q2;
    q2.enqueue(new E_Treatment(3));   //3 timesteps of E
    q2.enqueue(new X_Treatment(4));   //4 timesteps of X

    LinkedQueue<Treatment*> q3;
    q3.enqueue(new X_Treatment(6));   // 6 timesteps of X

    Patient* p1 = new Patient('N', 2, 0, q1);  //PT=2, VT=0
    Patient* p2 = new Patient('R', 1, 1, q2);  //PT=1, VT=1
    Patient* p3 = new Patient('N', 5, 2, q3);  //PT=5, VT=2

    sch.toAllPatients(p1);
    sch.toAllPatients(p2);
    sch.toAllPatients(p3);

    sch.Simulation();*/


































    return 0;
}
