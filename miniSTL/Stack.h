#ifndef __JJC__STACK__H__
#define __JJC__STACK__H__

#include <miniSTL/defines.h>
#include <miniSTL/DynamicArray.h>

template<class T>
class Stack {
private:
    DynamicArray<T> __stack_space;

public:
    // typical push operation
    void push(T data) {
        __stack_space.pushBack(data);
    }

    // pretty self-explanatory
    T pop(void) {
        return __stack_space.popBack();
    }

    // return the number of elements on the stack
    int stackSize(void) {
        return __stack_space.arraySize();
    }

    // returns the maximum number of elements that
    // can be placed on the stack before the
    // underlying DynamicArray will need to be resized
    int stackCapacity(void) {
        return __stack_space.arrayCapacity();
    }

};

#endif // __JJC__STACK__H__
