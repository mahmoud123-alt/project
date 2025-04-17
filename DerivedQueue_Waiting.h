

#pragma once
#include<random>
#include"LinkedQueue.h"
#include"Patient.h"


class U_E_Waiting_DerivedQueue :public LinkedQueue<Patient*>
{
	//frontPtr
	//backPtr
public:
	U_E_Waiting_DerivedQueue() :LinkedQueue<Patient*>()
	{

	}
	bool InsertSorted(Patient*& n)
	{
		if (n == nullptr)
		{
			cout << "NULL in InsertSorted";
			return 0;
		}
		count++;
		Node<Patient*>* latePatient = new Node<Patient*>;
		latePatient->setItem(n);
		int t;
		if (n->get_currentmode() == LATE)
			t = (n->VT - n->PT) / 2 + n->PT;
		else
		{
			Treatment* temp;
			n->Required_Treatments.peek(temp);
			t = temp->duration;
		}
		if (isEmpty())
		{
			frontPtr = backPtr = latePatient;
		}
		else if (backPtr->getItem()->PT <= t)//insert end
		{
			backPtr->setNext(latePatient);
			backPtr = latePatient;
			//add at the end since the last patients pt<=late patients pt same as enqueue
		}
		else if (frontPtr->getItem()->PT > t)//insert begin
		{
			latePatient->setNext(frontPtr);
			frontPtr = latePatient;
			//add at the front since the last patients pt>late patients pt 
		}
		else
		{
			Node<Patient*>* btemp = nullptr;
			Node<Patient*>* temp = frontPtr;
			while (temp->getItem()->PT <= t)
			{
				btemp = temp;
				temp = temp->getNext();
			}
			btemp->setNext(latePatient);
			latePatient->setNext(temp);
			//btemp is the patient before the late patient and temp is the patient after 

		}
		return 1;
	}
	int CalcTreatmentLatency()
	{
		int TL = 0;
		Node<Patient*>* temp = frontPtr;
		Treatment* t;
		while (temp)
		{
			temp->getItem()->Required_Treatments.peek(t);
			TL += t->duration;
			temp = temp->getNext();
		}

		return TL;
	}
};

class X_Waiting_DerivedQueue :public U_E_Waiting_DerivedQueue
{
private:
	int pCancel;
public:
	X_Waiting_DerivedQueue() :U_E_Waiting_DerivedQueue()
	{
		pCancel = 0;
	}
	void setPcancel(int p)
	{
		pCancel = p;
	}
	Patient* PosCancel()
	{

		Patient* cancelPatient = nullptr;
		if (isEmpty())
			return cancelPatient;


		int randomNum = rand() % 101;

		if (randomNum < pCancel)
		{
			int randomPatient = rand() % count;//0->count-1



			if (randomPatient == 0)//first
			{
				if (frontPtr->getItem()->Required_Treatments.get_count() == 1)
					dequeue(cancelPatient);
			}
			else
			{
				Node<Patient*>* btemp = nullptr;
				Node<Patient*>* temp = frontPtr;
				for (int i = 0; i < randomPatient; i++)
				{
					btemp = temp;
					temp = temp->getNext();
				}
				/*
				if temp patient has x as last then we remove temp node and return that patient
				if not we ignore
				*/
				if (temp->getItem()->Required_Treatments.get_count() == 1)// meaning X is last treatment 
				{
					decCount();
					btemp->setNext(temp->getNext());
					temp->setNext(nullptr);
					cancelPatient = temp->getItem();
					delete temp;

					if (frontPtr->getNext() == nullptr)
						backPtr = frontPtr;

				}



			}


		}
		return cancelPatient;
	}

	Patient* GuaranteedCancel()
	{

		Patient* cancelPatient = nullptr;
		if (isEmpty())
			return cancelPatient;


		int randomPatient = rand() % count;//0->count-1



		if (randomPatient == 0)//first
		{
			dequeue(cancelPatient);
		}
		else
		{
			Node<Patient*>* btemp = nullptr;
			Node<Patient*>* temp = frontPtr;
			for (int i = 0; i < randomPatient; i++)
			{
				btemp = temp;
				temp = temp->getNext();
			}

			btemp->setNext(temp->getNext());
			temp->setNext(nullptr);
			cancelPatient = temp->getItem();
			delete temp;


			if (randomPatient == count - 1)
			{
				backPtr = btemp;
			}
			decCount();

		}


		return cancelPatient;
	}


	/*Patient* GuaranteedCancel()
	{
		Patient* patient = nullptr;
		if (this->count == 0)
			return patient;

		if (this->count == 1)
		{
			dequeue(patient);
			return patient;
		}

		Node<Patient*>* ptr = this->frontPtr;
		Node<Patient*>* ptr2 = this->frontPtr;
		int index = rand() % this->count;

		for (int i = 0; i < index - 1; i++)
			ptr = ptr->getNext();

		ptr2 = ptr->getNext();

		if (index == this->count - 1)
		{
			ptr->setNext(nullptr);
			this->backPtr = ptr;
			patient = ptr2->getItem();
			this->count--;
			return patient;
		}
		return patient;
	}*/
};
