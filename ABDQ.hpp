#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ(){
        capacity_ = 4;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    explicit ABDQ(std::size_t capacity){
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[capacity_];
    }
    ABDQ(const ABDQ& other){
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < capacity_; i++){
            data_[i] = other.data_[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept{
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;

    }
    ABDQ& operator=(const ABDQ& other){
        if (this == &other){
            return *this;
        }
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < capacity_; i++){
            data_[i] = other.data_[i];
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept{
        if (this == &other) {
            return *this;
        }
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }
    ~ABDQ() {
        delete[] data_;
        data_ = nullptr;
    }

    // Insertion
    void pushFront(const T& item) override{
        if (size_ == capacity_){
            size_t new_capacity = 0;
            if (capacity_ == 0){
                new_capacity = 1;
            }
            else{
                new_capacity = capacity_ * 2;
            }
            T* temp = new T[new_capacity];
            for (size_t i = 0; i < size_; i++){
                temp[i+ 1] = data_[(front_ + i) % capacity_];
            }
            delete[] data_;
            data_ = temp;
            capacity_ = new_capacity;

            front_ = 0;
            back_ = size_;
        }
        else{
            if (front_ == 0){
                front_ = capacity_ - 1;
            }
            else{
                front_ = front_ - 1;
            }
        }
        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override{
        if (size_ == capacity_){
            size_t new_capacity = 0;
            if (capacity_ == 0){
                new_capacity = 1;
            }
            else{
                new_capacity = capacity_ * 2;
            }
            T* temp = new T[new_capacity];
            for (size_t i = 0; i < size_; i++){
                temp[i] = data_[(front_ + i) % capacity_];
            }
            delete[] data_;
            data_ = temp;
            capacity_ = new_capacity;

            front_ = 0;
            back_ = size_;
        }
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override{
        if (size_ == 0){
            throw std::runtime_error("Array is empty");
        }
        T popFrontVal = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        return popFrontVal;
    }
    T popBack() override{
        if (size_ == 0){
            throw std::runtime_error("Array is empty");
        }
        T popBackVal = data_[(back_ + capacity_ - 1) % capacity_];
        back_ = (back_ - 1 + capacity_) % capacity_;
        size_--;
        return popBackVal;
    }

    // Access
    const T& front() const override{
        if (size_ == 0){
            throw std::runtime_error("Array is empty");
        }
        return data_[front_];
    }
    const T& back() const override{
        if (size_ == 0){
            throw std::runtime_error("Array is empty");
        }
        return data_[(back_ + capacity_ - 1) % capacity_];
    }

    // Getters
    std::size_t getSize() const noexcept override{
        return size_;
    }

    void ensureCapacity(){
        if (capacity_ == 0){
            capacity_ = 1;
        }
        size_t old_capacity = capacity_;
        capacity_ *= 2;
        size_t j = 0;
        T* temp = new T[capacity_];
        for (std::size_t i = front_; i != back_; i = (i + 1) % old_capacity){
            temp[j] = data_[i];
            j++;
        }
        front_ = 0;
        back_ = j;
        size_ = j;
        delete[] data_;
        data_ = temp;
    }

    void shrinkIfNeeded(){
        if (size_ < (capacity_/2)){
            if (size_ == 0){
                delete[] data_;
                capacity_ = 1;
                data_ = new T[capacity_];
                front_ = 0;
                back_ = 0;
                return;
            }
            size_t old_capacity = capacity_;
            capacity_ /= 2;
            size_t j = 0;
            T* temp = new T[capacity_];
            for (std::size_t i = front_; i != back_; i = (i + 1) % old_capacity){
                temp[j] = data_[i];
                j++;
            }
            front_ = 0;
            back_ = j;
            size_ = j;
            delete[] data_;
            data_ = temp;
        }
    }

    //Print Methods
    void PrintForward() const {
        for (std::size_t i = front_; i != back_; i = (i + 1) % capacity_){
            std::cout << data_[i] << " ";
        }
    }

    void PrintReverse() const{
        size_t i = (back_ + capacity_ - 1) % capacity_;
        for (size_t count = 0; count < size_; count++){
            std::cout << data_[i] << " ";
            i = (i + capacity_ - 1) % capacity_;
        }
    }

};
