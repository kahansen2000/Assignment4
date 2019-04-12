/*
* Katherine Hansen
* 2326665
* kahansen@chapman.edu
* CPSC250-01
* Assignment 4
* This is the student class that holds key information we must know about each student
*/
class Student{
	public:
		int timeArrived;
		int timeNeeded;
		int waitTime;
		bool hasWindow;
		
		Student();
		Student(int timeArrive, int timeNeed);
		~Student();
};


Student::Student(){
	timeArrived=0;
	timeNeeded=0;
	waitTime=0;
	hasWindow=false;
}
Student::Student(int timeArrive, int timeNeed){
	timeArrived=timeArrive;
	timeNeeded=timeNeed;
}
Student::~Student(){
	
}
