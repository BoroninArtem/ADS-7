// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>
template<typename T>
class TPQueue {
 private:
    struct Item {
        T data;
        Item* next;
    };
    Item* first;
    Item* last;
    Item* create(T data) {
        Item* item = new Item;
        item->data = data;
        item->next = nullptr;
        return item;
    }

 public:
    TPQueue() :first(nullptr), last(nullptr) {}
    ~TPQueue() {
        while (!isEmpty())
            pop();
    }
    void push(const T& data) {
        if (isEmpty()) {
            first = create(data);
            last = first;
        } else {
            Item* begin = first;
            Item* newItem = create(data);
            if (data.prior > first->data.prior) {
                newItem->next = first;
                first = newItem;
            } else {
                while (begin->next && data.prior <= begin->next->data.prior)
                    begin = begin->next;
                newItem->next = begin->next;
                begin->next = newItem;
                if (begin == last)
                    last = newItem;
            }
        }
    }
    T pop() {
        if (isEmpty())
            throw std::string("Empty");
        Item* temp = first->next;
        T data = first->data;
        delete first;
        first = temp;
        return data;
    }
    bool isEmpty() const {
        return first == nullptr;
    }
};

struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
