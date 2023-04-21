// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template<typename T>
class TPQueue {
private:
    struct Item {
        SYM data;
        Item* next;
    };
    Item* first;

 public:
    TPQueue() : first(nullptr) {}
    ~TPQueue() {
        while (!isEmpty()) {
            Item* temp = first;
            first = first->next;
            delete temp;
        }
    }
    bool isEmpty() {
        return first == nullptr;
    }
    void push(const SYM& data) {
        Item* newItem = new Item;
        newItem->data = data;
        newItem->next = nullptr;

        if (isEmpty()) {
            first = newItem;
            return;
        }

        if (data.prior > first->data.prior) {
            newItem->next = first;
            first = newItem;
            return;
        }

        Item* current = first;
        while (current->next != nullptr && current->next->data.prior >= data.prior) {
            current = current->next;
        }

        newItem->next = current->next;
        current->next = newItem;
    }

    SYM pop() {
        if (isEmpty())
            throw std::string("Empty");
        SYM result = first->data;
        Item* temp = first;
        first = first->next;
        delete temp;
        return result;
    }
    void print() {
        if (isEmpty())
            std::cout << "Empty";
        Item* temp = first;
        while (temp) {
            std::cout << temp->data.ch << " (pr: " << temp->data.prior << ")" << std::endl;
            temp = temp->next;

        }
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
