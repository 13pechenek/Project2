#pragma once


struct KeyDirections
{
	bool up = 0;
	bool down = 0;
	bool right = 0;
	bool left = 0;
};




template <class T>
class ListNode {
public:
    T data;
    ListNode* next;

    ListNode(T val) : data(val), next(nullptr) {}
};

template <class T>
class SinglyLinkedList {
private:
    ListNode<T>* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void append(T val) {
        if (!head) {
            head = new ListNode<T>(val);
        }
        else {
            ListNode<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new ListNode<T>(val);
        }
    }

    void removeAt(int index) {
        if (index == 0) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        else {
            ListNode<T>* current = head;
            ListNode<T>* previous = nullptr;
            for (int i = 0; i < index; i++) {
                if (!current) {
                    std::cout << "Index out of bounds" << std::endl;
                    return;
                }
                previous = current;
                current = current->next;
            }
            if (!current) {
                std::cout << "Index out of bounds" << std::endl;
                return;
            }
            previous->next = current->next;
            delete current;
        }
    }

    void printList() {
        ListNode<T>* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};
