#pragma once
#include "priNode.h"
#include"iostream"
using namespace std;

//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue



template <typename T>
class priQueue
{
   
protected:
    int count;   priNode<T>* head;
public:
    priQueue() : head(nullptr),count(0) {}

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);
        count++;
        if (head == nullptr || priority > head->getPri()) {

            newNode->setNext(head);
            head = newNode;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;
        count--;
        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem();
        pri = head->getPri();
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
    void print()const
    {
        if (isEmpty())
            return;
        priNode<T>* temp = head;
        int pri;
        while (temp)
        {
            if (!temp->getNext()) {
                cout << temp->getItem(pri);
                temp = temp->getNext();
            }
            else {

                cout << temp->getItem(pri) << ", ";
                temp = temp->getNext();
            }
        }
        cout << "\n";
    }
    int get_count() {
        return count;
    }
    void decCount()
    {
        if (count == 0)
            return;
        count--;
    }


};
