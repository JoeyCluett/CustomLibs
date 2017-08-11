#ifndef __JJC__DYNAMICARRAY__H__
#define __JJC__DYNAMICARRAY__H__

#include <cstring>
#include <iostream>
#include <stdexcept>

#define DYNARR_STARTING_SIZE 16

template<class T>
class DynamicArray {
protected:
    T* arr;

    // current number of elements in the array
    int numElements = 0;

    // maximum number of elements that can be in the array
    int maxElements = 0;

    // resize the array to fit more elements
    // array size always gets doubled
    void resizeArray(void);

public:
    // only a default constructor
    DynamicArray(void) {
        // allocate space for the first elements
        arr = new T[DYNARR_STARTING_SIZE];

        maxElements = DYNARR_STARTING_SIZE;
    }

    // delete allocated memory
    ~DynamicArray(void) {
        //std::cout << "Deleting array, addr: " << this << std::endl;
        delete[] arr; // OS maintains how many bytes to deallocate
    }

    // add data to end of dynamic array
    void pushBack(T type);

    // return the last element in the array and reduce the size of dynamic array
    T popBack(void);

    // return the size of the array
    int arraySize(void);

    // return the capacity of the array
    int arrayCapacity(void);

    // erase all elements in this DynamicArray
    // by setting numElements to zero
    void clearSimple(void);

    // erase all elements in this DynamicArray
    // by deallocating memory for all elements
    // then reallocating
    void clearFull(void);

    // access elements like you would in a regular array
    T& operator[](const int index);
};

template<class T>
void DynamicArray<T>::clearSimple(void) {
    this->numElements = 0;
}

template<class T>
void DynamicArray<T>::clearFull(void) {
    delete[] arr;
    arr = new T[DYNARR_STARTING_SIZE];
    maxElements = DYNARR_STARTING_SIZE;
}

template<class T>
void DynamicArray<T>::pushBack(T data) {
    if(numElements == maxElements)
        resizeArray();

    arr[numElements] = data;
    numElements++;
}

template<class T>
T DynamicArray<T>::popBack(void) {
    if(numElements) {
        T temp = arr[numElements-1];
        numElements--;
        return temp;
    } else {
        throw std::range_error("Not enough elements to retrieve");
    }
}

template<class T>
int DynamicArray<T>::arraySize(void) {
    return numElements;
}

template<class T>
int DynamicArray<T>::arrayCapacity(void) {
    return maxElements;
}

template<class T>
T& DynamicArray<T>::operator[](const int index) {
    return arr[index];
}

template<class T>
void DynamicArray<T>::resizeArray(void) {
    //std::cout << "Resizing array" << std::endl;
    T* tempArr = new T[maxElements*2];
    std::memcpy(tempArr, arr, sizeof(T) * maxElements);
    delete[] arr;
    arr = tempArr;
    maxElements *= 2;
}

#endif // __JJC__DYNAMICARRAY__H__

















