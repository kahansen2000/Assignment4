/*
* Katherine Hansen
* 2326665
* kahansen@chapman.edu
* CPSC250-01
* Assignment 4
* This is a generic DoublyLinkedList class
*/

#include <iostream>
#include "ListNode.h"

using namespace std;


template <class T>
class DoublyLinkedList {
    private:

    public:
        ListNode<T> *front;
        ListNode<T> *back;
        unsigned int size;

        DoublyLinkedList(); //Constructor
        ~DoublyLinkedList(); //Destructor

        void insertBack(T d);//inserting data into back of List
        T removeFront();//removing data from front of list
        T deletePos(int pos);//deleting item given a position
        bool isEmpty();//returns if list is empty or not
        void printList();//prints list
        
        unsigned int getSize();//returns size of list
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    front = NULL;
    back = NULL;
    size = 0;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	
}

template <class T>
void DoublyLinkedList<T>::insertBack(T d) {
    ListNode<T> *node = new ListNode<T>(d);
    //Checks if list is empty
    if(size == 0) {
        front = node;
        back=node;
    }
    else {
        back->next = node;
        node->prev = back;
    }
    back = node;
    size++;
}

template <class T>
T DoublyLinkedList<T>::removeFront() {
    if(!isEmpty()) {
        ListNode<T> *node = front;
        //Only Node in List
        if(front->next == NULL) {
            front = NULL;
            back = NULL;
        }
        //More than One
        else {
            front->next->prev = NULL;
            front = front->next;
        }

        //node->next = NULL;

        T temp = node->data;

        delete node;
        --size;
        return temp;
    }
    else {
        return T();
    }
}
template <class T>
void DoublyLinkedList<T>::printList(){
  ListNode<T> *curr = front;
  while(curr->next!=NULL){
    cout << curr->data <<endl;
    curr=curr->next;
  }
}

template <class T>
T DoublyLinkedList<T>::deletePos(int pos) {
    int idx = 0;
    ListNode<T> *curr = front;
    ListNode<T> *prev = front;

    while(idx != pos) {
        prev = curr;
        curr = curr->next;
        ++idx;
    }

    prev->next = curr->next;
    curr->next->prev = prev;
    curr->next = NULL;
    curr->prev = NULL;
    curr->data = NULL;

    --size;
    delete curr;
}

template <class T>
bool DoublyLinkedList<T>::isEmpty() {
    return(size == 0);
}

template <class T>
unsigned int DoublyLinkedList<T>::getSize() {
    return size;
}
