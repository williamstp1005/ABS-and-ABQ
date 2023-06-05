#pragma once
#include <iostream>
using namespace std;

template <typename T>
class ABS {
    int capacity;
    int currentSize;
    T* array;
    float scaleFactor;
    unsigned int totalRe = 0;

public:
    ABS() {
        capacity = 1;
        currentSize = 0;
        array = new T[capacity];
        scaleFactor = 2.0f;
    }

    ABS(int _capacity, float _scaleFactor) {
        capacity = _capacity;
        currentSize = 0;
        array = new T[capacity];
        scaleFactor = _scaleFactor;
    }

    ABS(const ABS& d) {
        capacity = d.capacity;
        currentSize = d.currentSize;
        array = new T[capacity];
        scaleFactor = d.scaleFactor;
    }

    ABS& operator=(const ABS& d) {
        capacity = d.capacity;
        currentSize = d.currentSize;
        array = new T[capacity];
        scaleFactor = d.scaleFactor;
    }

    ~ABS() {
        delete[] array;
        array = nullptr;
    }

    void push(T data) {
        if (capacity == currentSize) {
            capacity *= scaleFactor;
            T* chngArray = new T[capacity];

            for (int i = 0; i < currentSize; i++) {
                chngArray[i] = array[i];
            }
            chngArray[currentSize] = data;

            delete[] array;
            array = chngArray;
            totalRe++;
        }
        else {
            array[currentSize] = data;
        }

        currentSize++;

    }

    unsigned int getMaxCapacity() {
        return capacity;
    }

    unsigned int getSize() {
        return currentSize;
    }

    unsigned int getTotalResizes() {
        unsigned int returnVal = totalRe;
        totalRe = 0;
        return returnVal;
    }

    T peek() {
        if (currentSize == 0) {
            throw runtime_error("error");
        }

        return array[currentSize - 1];
    }

    T pop() {
        if (currentSize == 0) {
            throw runtime_error("error");
        }
        float maker = 1.0f;
        currentSize--;
        T popped = array[currentSize];

        if ((currentSize * maker) / capacity < 1 / scaleFactor) {
            capacity /= scaleFactor;
            T* chngArray = new T[capacity];

            for (int i = 0; i < capacity; i++) {
                chngArray[i] = array[i];
            }

            delete[] array;
            array = chngArray;
            totalRe++;
        }
        return popped;
    }

};