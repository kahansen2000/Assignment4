/*
* Katherine Hansen
* 2326665
* kahansen@chapman.edu
* CPSC250-01
* Assignment 4
* This is a generic queue class
*/

#include <iostream>
#include "ListNode.h"

template <class T>
class GenQueue{
	public:
		GenQueue();
		~GenQueue();
		
		void insert(T d);
		T remove();
		
		int getSize();
		bool isEmpty();
		
		ListNode<T> *front;
		ListNode<T> *back;
		int size;
		
};


template <class T>
GenQueue<T>::GenQueue() {
    front = NULL;
    back = NULL;
}

template <class T>
GenQueue<T>::~GenQueue() {

}

template <class T>
void GenQueue<T>::insert(T d) {
    ListNode<T> *node = new ListNode<T>(d);

    if(size == 0) {
        front = node;
        back = node;
    }
    else {
        back->next = node;
        node->prev = back;
    }
    back = node;
    size++;
}

template <class T>
T GenQueue<T>::remove() {
    if(isEmpty()) {
    	return NULL;
	}
	
    ListNode<T> *node = front;
    T temp = node->data;
        
    if(front->next == NULL) {
        front = NULL;
        back = NULL;
	}
    else {
        front->next->prev = NULL;
        front = front->next;
    }
    delete node;
    size--;
    return temp;
}


template <class T>
int GenQueue<T>::getSize() {
    return size;
}

template <class T>
bool GenQueue<T>::isEmpty() {
    return (size == 0);
}
