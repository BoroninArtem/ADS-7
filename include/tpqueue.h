// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
template<typename T>
class TPQueue {
 private:
    struct Item {
        T data;
        Item* next;
    };
    Item* first, last;
    Item* create(T data) {
        Item* item = new Item;
        item->data = data;
        item->next = nullptr;
        return item;
    }
 public:
    TPQueue() :first(nullptr), tail(nullptr) {}
    ~TPQueue() {
        while (!isEmpty())
            pop();
    }
    void push(const T& data) {
        if (!isEmpty) {
            Item* begin = first;
            Item* newItem = create(data);
            if (first == tail) {
                if (data.prior > first->data.prior) {
                    newItem->next = first;
                    first = newItem;
                }
                else {
                    first->next = newItem;
                    tail = newItem;
                }
            }
            else {
                Item* prev = nullptr;
                while (begin != tail && data.prior <= begin->data.prior) {
                    prev = begin;
                    begin = begin->next;
                }
                if (data.prior > begin->data.prior) {
                    newItem->next = begin;
                    if (prev) {
                        prev->next = newItem;
                    }
                    else {
                        first = newItem;
                    }
                }
                else {
                    tail->next = newItem;
                    tail = newItem;
                }
            }
        }
        else {
            first = create(data);
            tail = first;
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
