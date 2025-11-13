#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS(){}

    // Insertion
    void push(const T& item) override{
        list.addHead(item);
    }

    // Deletion
    T pop() override{
        T data = list.getHead()->data;
        list.removeHead();
        return data;
    }

    // Access
    T peek() const override{
        if (list.getHead() == nullptr){
            throw std::runtime_error("No elements in list");
        }
        return list.getHead()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }

    //Print
    void PrintForward() const{
        list.printForward();
    }

    void PrintReverse() const{
        list.printReverse();
    }
};