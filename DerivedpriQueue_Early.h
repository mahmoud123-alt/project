#pragma once
#include"priQueue.h"
#include"Patient.h"
#include<random>

class DerivedpriQueue_Early :public priQueue<Patient*>
{
private:
	int pResc;
public:
	DerivedpriQueue_Early() :priQueue()
	{
		pResc = 0;
	}
	void setPresc(int p)
	{
		pResc = p;
	}
	bool PosResc()
	{
		if (isEmpty())
			return 0;
		/*
		so first i generate a random number if < presc then i select a random patient 0->count-1 and make a new pt
		for that patient
		*/

		int randomNum = (rand() % 101);//0->100
		if (randomNum < pResc)
		{

			int randomPatient = rand() % count;//0->count-1

			Patient* tempPatient;
			int oldPT;//not needed 
			if (randomPatient == 0)
			{

				dequeue(tempPatient, oldPT);

			}
			else
			{

				priNode<Patient*>* btemp = nullptr;
				priNode<Patient*>* temp = head;
				for (int i = 0; i < randomPatient; i++)
				{
					btemp = temp;
					temp = temp->getNext();
				}
				decCount();
				btemp->setNext(temp->getNext());
				temp->setNext(nullptr);
				tempPatient = temp->getItem(oldPT);
				delete temp;



			}
			//new pt 
			tempPatient->PT = oldPT + rand() % (oldPT * 2 - oldPT + 1);//assuming upper bound


			enqueue(tempPatient, tempPatient->PT);
			return 1;
		}
		return 0;
	}


	bool GuaranteedResc()
	{
		if (isEmpty())
			return 0;
		/*
		so first i generate a random number if < presc then i select a random patient 0->count-1 and make a new pt
		for that patient
		*/

		int randomPatient = rand() % count;//0->count-1

		Patient* tempPatient;
		int oldPT;
		if (randomPatient == 0)
		{

			dequeue(tempPatient, oldPT);

		}
		else
		{

			priNode<Patient*>* btemp = nullptr;
			priNode<Patient*>* temp = head;
			for (int i = 0; i < randomPatient; i++)
			{
				btemp = temp;
				temp = temp->getNext();
			}

			decCount();
			btemp->setNext(temp->getNext());
			temp->setNext(nullptr);
			tempPatient = temp->getItem(oldPT);
			delete temp;


		}
		//new pt 
		oldPT = -oldPT;//since the pri queue is max pri so we negate the pri to get min pri and now we have to negate again 
		tempPatient->PT = oldPT + rand() % (oldPT * 2 - oldPT + 1);//assuming upper bound


		enqueue(tempPatient, tempPatient->PT);

		return 1;
	}
};
