/*
* Katherine Hansen
* 2326665
* kahansen@chapman.edu
* CPSC250-01
* Assignment 4
* This is the Window class that holds key information we must know about each student
*/
class Window{
	public:
		int idleTime;
		bool empty;
		
		Window();
		~Window();
};

Window::Window(){
	idleTime=0;
	empty=true;
}
Window::~Window(){
	
}
