#pragma once
#include <iostream>
using namespace std;

template <typename T>
class ABQ {
    int capacity;
    int currentSize;
    T* array;
    float scaleFactor;
    unsigned int totalRe = 0;

public:
    ABQ() {
        capacity = 1;
        currentSize = 0;
        array = new T[capacity];
        scaleFactor = 2.0f;
    }

    ABQ(int _capacity, float _scaleFactor) {
        capacity = _capacity;
        currentSize = 0;
        array = new T[capacity];
        scaleFactor = _scaleFactor;
    }

    ABQ(const ABQ& d) {
        capacity = d.capacity;
        currentSize = d.currentSize;
        scaleFactor = d.scaleFactor;
    }

    ABQ& operator=(const ABQ& d) {
        capacity = d.capacity;
        currentSize = d.currentSize;
        scaleFactor = d.scaleFactor;
    }

    ~ABQ() {
        delete[] array;
        array = nullptr;
    }

    void enqueue(T data) {
        if (currentSize == capacity) {
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

    T dequeue() {
        T removed = ABQ::peek();
        float maker = 1.0f;
        currentSize--;

        if ((currentSize * maker) / capacity < 1 / scaleFactor) {
            capacity /= scaleFactor;
            totalRe++;
        }

        T* chngArray = new T[capacity];

        for (int i = 0; i < capacity; i++) {
            chngArray[i] = array[i + 1];
        }

        delete[] array;
        array = chngArray;
        return removed;
    }

    T peek() {
        if (currentSize == 0) {
            throw runtime_error("error");
        }

        return array[0];
    }

    unsigned int getSize() {
        return currentSize;
    }

    unsigned int getMaxCapacity() {
        return capacity;
    }

    unsigned int getTotalResizes() {
        unsigned int returnVal = totalRe;
        totalRe = 0;
        return returnVal;
    }

};