#ifndef __JJC__COMPRESSED__LIST__H__
#define __JJC__COMPRESSED__LIST__H__

#include <miniSTL/defines.h>
#include <miniSTL/DynamicArray.h>
#include <miniSTL/Stack.h>

#include <iostream>

template<class T>
class CompressedList {
private:
    // doubly linked list
    struct Node {
        T datum;
        Node* next; // address of next node in list
        Node* prev; // address of previous node in list
        bool used;
    };

    int __node_size = sizeof(Node); // important for finding indexes from addresses

    // the next index to be used is placed on this stack
    Stack<int> __free_indices;

    // carrier of actual nodes
    DynamicArray<Node> __node_list;

    // how many elements are currently in the list
    int numElements = 0;

    // ptrs to first and last elements
    Node *__first = 0, *__last = 0; // start as invalid ptrs

    // called when there are no available nodes for the list
    void allocateNewNodes(void);

public:
    // fill the array with empty nodes
    CompressedList(void) {
        for(int i = 0; i < DYNARR_STARTING_SIZE; i++) { // DYNARR_STARTING_SIZE is macro defining starting size of DynamicArray
            CompressedList<T>::Node element;
            element.next = 0;
            element.prev = 0;
            element.used = false;

            __node_list.pushBack(element);
        }

    }

    // put a new element on the end of the list
    void pushBack(T data);

    // pull an element off the end of the list
    T popBack(void);

    // put a new element on the front of the list
    void pushFront(T data);

    // pull an element off the front of the list
    T popFront(void);

    int listSize(void) {
        return numElements;
    }

    int listCapacity(void) {
        return __node_list.arrayCapacity();
    }
};

template<class T>
void CompressedList<T>::pushBack(T data) {

}

#endif // __JJC__COMPRESSED__LIST__H__









