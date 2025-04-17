
#pragma once

#define UI_H
#include "EarlyPList.h"
#include "priQueue.h"
#include "EU_WaitList.h"
#include "X_WaitList.h"
#include "ArrayStack.h"
#include <string>
#include "Scheduler.h"

// Forward declarations of your list classes:

class UI {
private:
    enum Mode { INTERACTIVE=1, SILENT=2 };


    Mode interfaceMode;      
    std::string inputFileName;
    std::string outputFileName;

public:
    
    UI() :interfaceMode(INTERACTIVE), // default
        inputFileName(""),outputFileName("") {

    }
    void read_outputFileName() {
        cout << "please Enter outfilename:" << endl;
        string x;
        cin >> x;
        outputFileName = x;



    }
   

    
    void readInterfaceMode() {
        int input;
        cout << "Enter interfaceMode (1: INTERACTIVE, 2: SILENT)" << endl;
        cin >> input;
        if (input == 1) {
            interfaceMode = INTERACTIVE;
            return;
        }


        if (input == 2) {
            interfaceMode = SILENT;


            return;

        }

    }
    void readinputFileName() {
        cout << "please Enter inputfilename:" << endl;
      
        string x;
        cin >> x;
        inputFileName = x;

    }


    string getInputFileName() const {
        return inputFileName;

    }
    string getOutputFileName() const {
        return outputFileName;
    }

    Mode getInterfaceMode() const {
        return interfaceMode;
    }







    void printOutputScreen(int current_time_step,
        LinkedQueue<Patient*>* allPatients,
        DerivedpriQueue_Early* earlyPatients,
        priQueue<Patient*>* latePatients,
        U_E_Waiting_DerivedQueue* uWaitingPatients,
        U_E_Waiting_DerivedQueue* eWaitingPatients,
        X_Waiting_DerivedQueue* xWaitingPatients,
        LinkedQueue<Resource*>* eDevices,
        LinkedQueue<Resource*>* uDevices,
        LinkedQueue<Resource*>* xRooms,
        priQueue<Patient*>* inTreatmentList,
        ArrayStack<Patient*>* finishedPatients
    ) {
        if (getInterfaceMode() == SILENT) {
            cout << "Silent Mode, Simulation ends, Output file created" << endl;
            return;
    }
        cout << "Current Timestep: " << current_time_step << endl;


        cout << "==============  ALL List   ============== " << endl;
        cout << allPatients->get_count() << " " << "patients remaining: ";
        allPatients->Print_first_ten();
        cout << endl;

        cout<< "==============  Waiting Lists    ============== " << endl;
        cout << eWaitingPatients->get_count() <<" E-therapy patients: ";
        eWaitingPatients->print();
        cout << endl;
        cout << uWaitingPatients->get_count() << " U-therapy patients: ";
        uWaitingPatients->print();
        cout << endl;
        cout <<xWaitingPatients->get_count() <<" X-therapy patients: ";
        xWaitingPatients->print();
        cout << endl;

        cout << "=============== Early Patient ===============" << endl;
        cout << earlyPatients->get_count() << " " << "patients: ";
        earlyPatients->print();
        cout << endl;


        cout << "=============== Late List ================== " << endl;
        cout << latePatients->get_count()<<" ";
        latePatients->print();
        cout << endl;

        cout << "=============== Avail E-devices =============== " << endl;
        cout << eDevices->get_count() << " Electro device: ";
        eDevices->print();
        cout << "=============== Avail U-devices =============== " << endl;
        cout << uDevices->get_count() << " " << " Ultra device: ";
        uDevices->print();
        cout << "=============== Avail X-rooms =============== " << endl;
        cout << xRooms->get_count() << " ";
        xRooms->print();




        cout << "=============== In-treatment List ===============" << endl;
        cout << inTreatmentList->get_count();
        cout << " ==> ";
        inTreatmentList->print();
        


        cout << "-------------------------------------------------" << endl;
        cout << finishedPatients->get_count() << " finishedPatients: ";
        finishedPatients->print();


        std::cout << "Press any Key to display next timestep...";
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cin.get();




    }











   

   
    ~UI() {

    }


  





};

