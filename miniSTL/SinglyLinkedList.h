#ifndef __JJC__SINGLYLINKEDLIST__H__
#define __JJC__SINGLYLINKEDLIST__H__

// the last element's next ptr is always zero (0)
#define S_LIST_END 0

template<class T>
class SinglyLinkedList {
public:
    struct Node {
        Node* next;
        T data;
    };

private:
    // allocate space for a new node
    Node* newNode(T data) {
        Node* t = new Node;
        t->next = S_LIST_END;
        t->data = data;
    }

    Node start;

public:
    // constructor takes one
    SinglyLinkedList(void) {
        start->next = S_LIST_END;
    }

    ~SinglyLinkedList(void) {
        Node* __t = start.next;
        while(__t != S_LIST_END) {
            Node* __tmp = __t->next;
            delete __t;
            __t = __tmp;
        }
    }

    // this data is returned if an invalid request for
    // data in the list is made
    void setDefaultData(T data);

    // get the first element in the list this
    // allows the user to get a handle for iterating
    Node* getFirst(void) {
        return start->next;
    }

    // add a new element to the end of the list
    // this operation takes O(n) for n elements
    void pushBack(T data);

    // add a new element to the beginning of the list
    // this operation is done in constant time
    void pushFront(T data);

    // return the last element of the list
    // this operation takes O(n) for n elements
    T popBack(void);

    // return the first element of the list
    // this operation takes constant time
    T popFront(void);
};

template<class T>
void SinglyLinkedList<T>::pushBack(T data) {
    Node* t = &start;
    while(t->next != S_LIST_END) // iterate to end of list
        t = t->next;

    t->next = newNode(data);
}

template<class T>
void SinglyLinkedList<T>::pushFront(T data) {
    Node* t = start.next;
    start.next = newNode(data);
    start.next->next = t;
}

template<class T>
T SinglyLinkedList<T>::popBack(void) {
    // special case returns more quickly
    if(start.next == S_LIST_END)
        return start.data; // this may be set by the user
}

template<class T>
T SinglyLinkedList<T>::popFront(void) {
    // special case if list size is zero
    if(start.next == S_LIST_END)
        return start.data;

    T datum = start.next->data;

    Node* node = start.next->next;
    delete start.next;

    start.next = node;

    return datum;
}

template<class T>
void SinglyLinkedList<T>::setDefaultData(T data) {
    this->start.data = data;
}

#endif // __JJC__SINGLYLINKEDLIST__H__
