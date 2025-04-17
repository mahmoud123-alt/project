#include "Treatement.h"
#pragma once
#include"DerivedpriQueue_Early.h"
#include"DerivedQueue_Waiting.h"
#include"ArrayStack.h"
#include<fstream>
#include "UI.h"


class Scheduler
{
private:
	
	LinkedQueue<Patient*>		ALL_Patients;
	DerivedpriQueue_Early		Early_Patients;
	priQueue<Patient*>			Late_Patients;
	priQueue<Patient*>			In_Treatment;
	ArrayStack<Patient*>		Finished_Patients;

	U_E_Waiting_DerivedQueue	U_Waiting;
	U_E_Waiting_DerivedQueue	E_Waiting;
	X_Waiting_DerivedQueue		X_Waiting;

	LinkedQueue<Resource*>		U_Devices;
	LinkedQueue<Resource*>		E_Devices;
	LinkedQueue<Resource*>		X_Rooms;
	
public:
	int							time_step;
private:

	void RandomWaiting(Patient* p)
	{
		int N = rand() % 101;//0->100

		if (N < 33)
		{
			if (p->get_currentmode() == ERLY || p->get_currentmode() == IDLE)
				E_Waiting.enqueue(p);
			else if (p->get_currentmode() == LATE)
				E_Waiting.InsertSorted(p);

		}
		else if (N < 66)
		{
			if (p->get_currentmode() == ERLY || p->get_currentmode() == IDLE)
				U_Waiting.enqueue(p);
			else if (p->get_currentmode() == LATE)
				U_Waiting.InsertSorted(p);
		}
		else
		{
			if (p->get_currentmode() == ERLY || p->get_currentmode() == IDLE)
				X_Waiting.enqueue(p);
			else if (p->get_currentmode() == LATE)
				X_Waiting.InsertSorted(p);
		}
		p->set_currentmode(WAIT);

	}
	Patient* GetRandomWaiting()
	{
		int N = rand() % 101;//0->100
		Patient* rp = nullptr;
		if (N < 33)
		{
			E_Waiting.dequeue(rp);

		}
		else if (N < 66)
		{
			U_Waiting.dequeue(rp);
		}
		else
		{
			X_Waiting.dequeue(rp);
		}
		return rp;
	}


	//amr's version
	void GetRandomWaitingList(char& listType) {
		int r = rand() % 3;  //from 0 to 2

		if (r == 0) {
			listType = 'E';
		}
		else if (r == 1) {
			listType = 'U';
		}
		else {
			listType = 'X';
		}
	}

public:
	void LoadPatientsFromFile(const std::string& filename) {
		ifstream inFile;
		inFile.open(filename);


		if (!inFile.is_open()) {
			cout << 10;
			return;
		}
		int num;
		inFile >> num;
		Resource* temp;
		for (int i = 0; i < num; i++) {

			temp = new Resource("E", i + 1, 1);

			E_Devices.enqueue(temp);



		}
		inFile >> num;
		for (int i = 0; i < num; i++) {
			temp = new Resource("U", i + 100, 1);

			U_Devices.enqueue(temp);
		}
		inFile >> num;
		for (int i = 0; i < num; i++) {
			int num2;
			inFile >> num2;
			temp = new Resource("X", i + 200, num2);

			X_Rooms.enqueue(temp);

		}
		inFile >> num;



		X_Waiting.setPcancel(num);
		inFile >> num;

		Early_Patients.setPresc(num);

		inFile >> num;
		for (int j = 0; j < num; j++) {
			char type;
			inFile >> type;

			int PT, VT, NT;


			inFile >> PT >> VT >> NT;
			LinkedQueue <Treatment*> q;


			for (int i = 0; i < NT; i++) {
				char v;
				inFile >> v;
				if (v == 'U') {
					int x;
					inFile >> x;
					Treatment* f = new  U_Treatment(x);
					q.enqueue(f);


				}
				else if (v == 'X') {
					int x;
					inFile >> x;
					Treatment* f = new  X_Treatment(x);
					q.enqueue(f);



				}
				else {
					int x;
					inFile >> x;
					Treatment* f = new  E_Treatment(x);
					q.enqueue(f);


				}


			}




			Patient* p = new Patient(IDLE, type, PT, VT, q, j + 1);



			ALL_Patients.enqueue(p);



		}




		inFile.close();




	}





	void update()
	{
		Patient* peekPatient = nullptr;
		if (ALL_Patients.peek(peekPatient) && peekPatient->VT == time_step)
		{
			ALL_Patients.dequeue(peekPatient);

			if (peekPatient->VT < peekPatient->PT)
			{
				peekPatient->set_currentmode(ERLY);
				Early_Patients.enqueue(peekPatient, peekPatient->PT);
			}
			else if (peekPatient->VT > peekPatient->PT)
			{
				peekPatient->set_currentmode(LATE);
				int penalty = (peekPatient->VT - peekPatient->PT) / 2 + peekPatient->VT;
				Late_Patients.enqueue(peekPatient, penalty);
			}

			else
			{
				//here i dequeue the treatment after the patient leaves the waiting and not when he joins !!!
				peekPatient->set_currentmode(WAIT);
				Treatment* nextTreatment = nullptr;
				peekPatient->Required_Treatments.peek(nextTreatment);
				if (U_Treatment* ptr = dynamic_cast<U_Treatment*>(nextTreatment))
				{
					U_Waiting.enqueue(peekPatient);
				}
				else if (E_Treatment* ptr = dynamic_cast<E_Treatment*>(nextTreatment))
				{
					E_Waiting.enqueue(peekPatient);
				}
				else if (X_Treatment* ptr = dynamic_cast<X_Treatment*>(nextTreatment))
				{
					X_Waiting.enqueue(peekPatient);
				}
			}

			/*else
			{
				RandomWaiting(peekPatient);
			}*/
		}

		if (ALL_Patients.peek(peekPatient) && peekPatient->VT == time_step)
			update();

	}

	void RandomUpdate()
	{
		int x = rand() % 101;
		Patient* p1 = nullptr;
		Patient* p2 = nullptr;
		int val;
		if (x < 10)
		{
			if (Early_Patients.dequeue(p1, val))
				RandomWaiting(p1);

		}
		else if (x < 20)
		{
			if (Late_Patients.dequeue(p1, val))
				RandomWaiting(p1);
		}
		else if (x < 40)
		{

			Patient* p1 = GetRandomWaiting();
			Patient* p2 = GetRandomWaiting();
			Treatment* treatmentp1 = nullptr;
			Treatment* treatmentp2 = nullptr;
			p1->Required_Treatments.dequeue(treatmentp1);
			p2->Required_Treatments.dequeue(treatmentp2);
			if (p1)
			{
				p1->set_currentmode(SERV);
				In_Treatment.enqueue(p1, time_step + treatmentp1->duration);
			}
			if (p2)
			{
				p2->set_currentmode(SERV);
				In_Treatment.enqueue(p2, time_step + treatmentp2->duration);
			}
		}
		else if (x < 50)
		{
			if (In_Treatment.dequeue(p1, val))
				RandomWaiting(p1);
		}
		else if (x < 60)
		{
			if (In_Treatment.dequeue(p1, val))
				Finished_Patients.push(p1);
		}
		else if (x < 70)
		{

			if (p1 = X_Waiting.GuaranteedCancel())
				Finished_Patients.push(p1);
		}
		else if (x < 80)
		{
			Early_Patients.GuaranteedResc();
		}
	}

	bool finished()
	{
		return	ALL_Patients.isEmpty() &&
				Early_Patients.isEmpty() &&
				Late_Patients.isEmpty() &&
				In_Treatment.isEmpty() &&
				U_Waiting.isEmpty() &&
				E_Waiting.isEmpty() &&
				X_Waiting.isEmpty();

		

	}

	



	

	void Simulation() {
		

		// simulating until all patients are done
		while (!ALL_Patients.isEmpty() || !Early_Patients.isEmpty() || !Late_Patients.isEmpty() ||
			!E_Waiting.isEmpty() || !U_Waiting.isEmpty() || !X_Waiting.isEmpty() ||
			!In_Treatment.isEmpty()) 
		{
			UI x;
			int currentTime = 1;

			// load patients from file

			x.printOutputScreen(currentTime, &ALL_Patients, &Early_Patients, &Late_Patients, &U_Waiting, &E_Waiting, &X_Waiting, &E_Devices, &U_Devices, &X_Rooms, &In_Treatment, &Finished_Patients);


			//moving new patients
			Patient* p = nullptr;
			while (!ALL_Patients.isEmpty()) {
				if (ALL_Patients.peek(p) && p->VT == currentTime) {
					ALL_Patients.dequeue(p);

					//seperate them into appropriate lists
					if (p->VT < p->PT) {
						Early_Patients.enqueue(p, p->PT);
					}
					else if (p->VT > p->PT) {
						int penalty = (p->VT - p->PT) / 2;
						Late_Patients.enqueue(p, p->PT + penalty);
					}
					else {
						//then PT == VT
						int N = rand() % 101; //  random number from 0 to 100
						if (N < 33) {
							// to EWaiting list
							E_Waiting.enqueue(p);
						}
						else if (N < 66) {
							//to UWaiting list
							U_Waiting.enqueue(p);
						}
						else {
							//to XWaiting list
							X_Waiting.enqueue(p);
						}
						//RandomWaiting(p);
					}
				}
			}

			int X = rand() % 101;

			if (X < 10) {
				// move from early list to random waiting list
				if (!Early_Patients.isEmpty()) {
					//the returned pri
					int pri;
					Early_Patients.dequeue(p, pri);
					
					char listType;
					GetRandomWaitingList(listType);
					switch (listType) {
					case 'E':
						E_Waiting.enqueue(p);
						break;

					case 'U':
						U_Waiting.enqueue(p);
						break;

					case 'X':
						X_Waiting.enqueue(p);
						break;
					}
				}
			}
			else if (X < 20) {
				// move a patient from Late Patients and apply a penalty
				if (!Late_Patients.isEmpty()) {
					int pri;
					Late_Patients.dequeue(p, pri);
					//RandomWaiting(p);
		//////////////////////////////////
					/*
					int N = rand() % 101;
					if (N < 33) {
						//  patient to E-Waiting list
						E_Waiting.InsertSorted(p);
					}
					else if (N < 66) {
						//  patient to U-Waiting list
						U_Waiting.InsertSorted(p);
					}
					else {
						//  patient to X-Waiting list
						X_Waiting.InsertSorted(p);
					}
					*/
					char listType;
					GetRandomWaitingList(listType);
					switch (listType) {
					case 'E':
						E_Waiting.InsertSorted(p);
						break;

					case 'U':
						U_Waiting.InsertSorted(p);
						break;

					case 'X':
						X_Waiting.InsertSorted(p);
						break;
					}
				}
			}
			else if (X < 40) {
				// move 2 patients from RandomWaitingList to InTreatment
				char listType;
				GetRandomWaitingList(listType);
				switch (listType) {
				case 'E':
					E_Waiting.dequeue(p);
					break;

				case 'U':
					U_Waiting.dequeue(p);
					break;

				case 'X':
					X_Waiting.dequeue(p);
					break;
				}
				for (int i = 0; i < 2; ++i) {
					if (p != nullptr) {
						In_Treatment.enqueue(p, p->PT);
					}
				}
			}
			else if (X < 50) {
				// move patients from InTreatment  to RandomWaitingList
				if (!In_Treatment.isEmpty()) {
					int pri;
					In_Treatment.dequeue(p, pri);
					char listType;
					GetRandomWaitingList(listType);
					switch (listType) {
					case 'E':
						E_Waiting.InsertSorted(p);
						break;

					case 'U':
						U_Waiting.InsertSorted(p);
						break;

					case 'X':
						X_Waiting.InsertSorted(p);
						break;
					}
				}
			}
			else if (X < 60) {
				// move patients from InTreatment to Finished
				if (!In_Treatment.isEmpty()) {
					Patient* p;
					int pri;
					In_Treatment.dequeue(p, pri);
					Finished_Patients.push(p);         // push patient into Finished (it's ArrayStack)
				}
			}

			else if (X < 70) {
				// move cancelled patients from X_Waiting to Finished
				Patient* Cpatient;
				X_Waiting.GuaranteedCancel();
				Finished_Patients.push(Cpatient);
			}
			else if (X < 80) {
				// reschedule a patient from Early_Patients
				Early_Patients.PosResc();
			}

			// print system state


			//increment timestep
			currentTime++;
		}

		cout << "simulation is finished!!" << endl;
	}


};

