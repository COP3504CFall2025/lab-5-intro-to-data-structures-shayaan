#pragma once
#include <iostream>
using namespace std;

template <typename T>

class LinkedList {
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
public:
	// Behaviors
	void printForward() const{
		Node* current = head;
		while (true){
			if (current == nullptr) {
				break;
			}
			cout << current->data << " ";
			current = current->next;
		}
	}
	void printReverse() const{
		Node* current = tail;
		while (true){
			if (current == nullptr) {
				break;
			}
			cout << current->data << " ";
			current = current->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const{
		return count;
	}
	Node* getHead(){
		return head;
	}
	const Node* getHead() const{
		return head;
	}
	Node* getTail(){
		return tail;
	}
	const Node* getTail() const{
		return tail;
	}

	// Insertion
	void addHead(const T& data){
		Node* newNode = new Node();
		newNode->data = data;
		newNode->prev = nullptr;
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		count++;
	}
	void addTail(const T& data){
		Node* newNode = new Node();
		newNode->data = data;
		newNode->prev = tail;
		newNode->next = nullptr;
		tail->next = newNode;
		tail = newNode;
		count++;
	}

	// Removal
	bool removeHead(){
		if (head == nullptr){
			return false;
		}
		if (count == 1){
			delete head;
			head = nullptr;
			tail = nullptr;
			count = 0;
			return true;
		}
		Node* current = head;
		head = head->next;
		head->prev = nullptr;

		delete current;
		count--;
		return true;
	}
	bool removeTail(){
		if (tail == nullptr){
			return false;
		}
		if (count == 1){
			delete head;
			head = nullptr;
			tail = nullptr;
			count = 0;
			return true;
		}
		Node* current = tail;
		tail = tail->prev;
		tail->next = nullptr;

		delete current;
		count--;
		return true;
	}
	void clear(){
		while (head != nullptr){
			removeHead();
		}
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if (this == &other){
			return *this;
		}
		clear();
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if (this == &rhs){
			return *this;
		}
		LinkedList temp(rhs);
		this->clear();
		this->head = temp.head;
		this->tail = temp.tail;
		this->count = temp.count;
		temp.head = nullptr;
		temp.tail = nullptr;
		return *this;
	}

	// Construction/Destruction
	LinkedList(){
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list){
		head = nullptr;
		tail = nullptr;
		count = 0;
		Node* current = list.head;
		while (current != nullptr){
			addTail(current->data);
			current = current->next;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept{
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList(){
		clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


