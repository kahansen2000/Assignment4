/*
* Katherine Hansen
* 2326665
* kahansen@chapman.edu
* CPSC250-01
* Assignment 4
* This is the main method that runs the simulation
*/

#include <iostream>
#include "Simulation.h"

using namespace std;

int main(int argc, char** argv) {
	Simulation sim;
	string file;
	//if user forgot to provide a file
	if(argc < 2){
		cout<<"You didnt provide a file. Please provide the file name now"<<endl;
		cin>>file;
	}
	else{
		file=argv[1];
	}
	int openWindows=0;
	int currentTime=0;//initializing current time to zero
	
	sim.getFile(file);//sets up queue of students and windows
	while(true){
		if(sim.studentQueue.isEmpty()){//if there are no more students in the queue
			int count=0;
			for(int i=0;i<sim.numWindows;i++){//check to see if windows are also empty
				if(sim.windows[i]->empty)
					count++;//number of empty windows
			}
			if(count==sim.numWindows){
				//break;
			}
		}
		//inserts a student into an empty window
		for(int i=0; i<sim.numWindows;i++){
			if(sim.windows[i]->empty){
				sim.currAtWindow[i]=sim.studentQueue.remove();
				sim.wait.insert(sim.currAtWindow[i]->waitTime);
			}
		}
		
		currentTime++;
		sim.timer(currentTime);
		
		
	}
	
	
	//print all of the stats
	sim.printStats();
	
	return 0;
}
