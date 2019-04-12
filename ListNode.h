/*
* Katherine Hansen
* 2326665
* kahansen@chapman.edu
* CPSC250-01
* Assignment 4
* This is a generic ListNode class
*/

#include <iostream>

using namespace std;

template <class T>
class ListNode {
    private:

    public:
        T data;
        ListNode<T> *next;
        ListNode<T> *prev;

        ListNode();
        ListNode(T d);
        ~ListNode();
};

template <class T>
ListNode<T>::ListNode() {
	data=NULL;
	next=NULL;
	prev=NULL;
}
template <class T>
ListNode<T>::ListNode(T d) {
    data = d;
    next = NULL;
    prev = NULL;
}

template <class T>
ListNode<T>::~ListNode() {
    if(next != NULL) {
        next = NULL;
        prev = NULL;

        delete next;
        delete prev;
    }
}
