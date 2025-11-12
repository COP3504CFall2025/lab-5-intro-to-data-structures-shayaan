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
		Node* current = head;
		head = head->next;
		if (head != nullptr){
			head->prev = nullptr;
		}
		delete current;
		count--;
		return true;
	}
	bool removeTail(){
		if (tail == nullptr){
			return false;
		}
		Node* current = tail;
		tail = tail->prev;
		if (tail != nullptr){
			tail->next = nullptr;
		}
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
		head = nullptr;
		tail = nullptr;
		count = 0;
		Node* current = rhs.head;
		while (current != nullptr){
			addTail(current->data);
			current = current->next;
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList(){
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
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


