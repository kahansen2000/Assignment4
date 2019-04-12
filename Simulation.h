/*
* Katherine Hansen
* 2326665
* kahansen@chapman.edu
* CPSC250-01
* Assignment 4
* This is the simulation class that goes through how each student ends up at each window and tracks many statistics
*/

#include <iostream>
#include <string>
#include "Student.h"
#include "GenQueue.h"
#include "Window.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
//#include "ListNode.h"

using namespace std;

class Simulation {

    public:
        Simulation();
        ~Simulation();

        
        void getFile(string file);

        void timer(int t);
        
        //Simulation statistics
        void printStats();
        double meanWaitTime();
        double medianWaitTime();
        int longestWaitTime();
        int tenWaitTime();
        double meanIdleTime();
        int longestIdleTime();
        int fiveIdleTime();

		int numWindows;
        int numStudents;
        int numCurrStudents;
        int entryTime;
        int timeNeed;
        int medCount;
        int idleCount;
        
        //Student Queue
        GenQueue<Student*> studentQueue;
        //Window List
        Window* *windows;
        Student* *currAtWindow;
        
        //helpers in calculating statistics
        GenQueue<int> wait;
        GenQueue<int> idle;
        int *waitArray;
        int *idleArray;

};

Simulation::Simulation(){
	int numWindows=0;
    int numStudent=0;
    int numCurrStudents=0;
    int entryTime=0;
}

Simulation::~Simulation(){
	
}

//opening file and filling out necessary information
void Simulation::getFile(string file){
	ifstream input;
	input.open(file.c_str());
	string line;
	int lineNum = 1;
	
	if(input.is_open()){
		//getting num windows
		getline(input, line);
     	numWindows =atoi(line.c_str());//converting string to int
       	cout<<numWindows;
		
		//filling window array
		windows = new Window*[numWindows];
		currAtWindow = new Student*[numWindows];
		for(int i=0; i<numWindows;i++){
			Window* w =new Window();
			windows[i]=w;
		}
		lineNum++;
		
		
		//filling out student info
		while(getline(input, line)){
			int type=1;
			switch(type) {
            
            	case(1): {
                	entryTime = atoi(line.c_str());
                	type++;
               		lineNum++;
                	break;
            	}
           		//count num students
            	case(2): {
                	if(line != "") {
                    	numCurrStudents = atoi(line.c_str());
                    	for(int i = 0; i < numCurrStudents; ++i) {
                       		getline(input, line);
                        	lineNum++;
                        	timeNeed = atoi(line.c_str());
                        	numStudents++;
                        	Student* student = new Student(entryTime, timeNeed);
                        	studentQueue.insert(student);
                        	type--;
                    	}
            		}
                	break;
            	}
           		default:
                	break;
        }
		}
	}
}

//keeps track of window/student idle/wait times and updates accordingly
void Simulation::timer(int t){
	for(int i = 0; i < numWindows; i++) {
        if(!windows[i]->empty) {//if the window is full, idle time decreases
            windows[i]->idleTime--;
        }
        else {
            windows[i]->idleTime++;//idle time increases when there is no student
        }
    }

    if(!studentQueue.isEmpty()) {
        ListNode<Student*> *curr = studentQueue.front;

        while(curr != NULL) {
            if(curr->data->timeArrived < t) {
                curr->data->waitTime += 1;//if the student is waiting, their wait time goes up
            }
            curr = curr->next;
        }
    }
}


void Simulation::printStats(){
	cout << "Mean Wait time for students:";
	cout << meanWaitTime() << endl;
	cout << "Median Wait time for students:";
    cout << medianWaitTime()<< endl;
    cout << "Longest Wait time for students:";
	cout << longestWaitTime()<< endl;
	cout << "Number of waits more than 10 minutes:";
    cout << tenWaitTime() << endl;
    cout << "Mean Idle time for windows:";
    cout << meanIdleTime()<< endl;
    cout << "Longest Idle time for windows:";
    cout << longestIdleTime()<< endl;
    cout << "Number of windows idle for more than 5 minutes:";
    cout << fiveIdleTime() << endl;
}
int Simulation::fiveIdleTime(){
	int count =0;
	for(int i=0; i<idleCount;i++){
		if(idleArray[i]>10){
			count++;
		}
	}
	return count;	
}
int Simulation::longestIdleTime(){
	ListNode<int> *curr = idle.front;

    idleCount = 0;

    while(curr != NULL) {
        curr = curr->next;
        idleCount++;
    }

    idleArray = new int[idleCount];

    curr = idle.front;

    for(int i = 0; i < idleCount; ++i) {
        idleArray[i] = curr->data;
        curr = curr->next;
    }
	//sorts list
    sort(idleArray, idleArray + idleCount);
	//returns highest value
    return(idleArray[idleCount - 1]);
}
double Simulation::meanIdleTime(){
	ListNode<int> *curr = idle.front;
    double sum = 0;
    int count = 0;

    while(curr != NULL) {
        sum += curr->data;
        curr = curr->next;
        count++;
    }

    if(count == 0) {
        return 0;
    }
    return sum/count;
}
int Simulation::tenWaitTime(){
	int count =0;
	for(int i=0; i<medCount;i++){
		if(waitArray[i]>10){
			count++;
		}
	}
	return count;
}
int Simulation::longestWaitTime(){
	//returns the highest number from the already ordered array from median
	return waitArray[medCount-1];
}
double Simulation::medianWaitTime(){
	ListNode<int> *curr = wait.front;

    double median = 0;
    medCount=0;

    while(curr != NULL) {
        curr = curr->next;
        medCount++;
    }

    if(medCount == 0) {
        return 0;
    }
    else {
        waitArray = new int[medCount];
        curr = wait.front;

        for(int i = 0; i < medCount; i++) {
            waitArray[i] = curr->data;
            curr = curr->next;
        }
        sort(waitArray, waitArray+medCount);//sorts values by number
        //Odd number of values
        if(medCount % 2 == 1) {
            int r = 0;

            r = (medCount/2) + 1;//finds the correct value
            return waitArray[r];//returns the median value
        }
        else {//is an odd number of values
        	//takes the average of the two middle numbers
            int mid1 = 0;
            int mid2 = 0;

            mid1 = medCount/2;
            mid2 = (medCount/2) + 1;


            return double(waitArray[mid1])/double(waitArray[mid2]);
        }
    }
}
double Simulation::meanWaitTime(){
	ListNode<int> *curr = wait.front;
    double sum = 0;
    int count = 0;

    while(curr != NULL) {
        sum += curr->data;
        curr = curr->next;
        count++;
    }
    if(count == 0) {
        return 0;
    }
    return (sum/count);
}
