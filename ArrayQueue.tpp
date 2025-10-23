// ArrayQueue.tpp

#include "ArrayQueue.hpp"

template <typename T>
ArrayQueue<T>::ArrayQueue(int cap) {
    if (cap <= 0) throw string("constructor: invalid capacity");
    this->buffer = new T[cap];
    this->maxSize = cap;
    this->length = 0;
    this->frontIndex = 0;
    this->backIndex = cap - 1; // so first enqueue lands at 0
}

template <typename T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& copyObj) {
    this->buffer = nullptr;
    this->maxSize = 0;
    this->length = 0;
    this->frontIndex = 0;
    this->backIndex = 0;
    copy(copyObj);
}

template <typename T>
ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& rightObj) {
    if (this != &rightObj) {
        clear();       // reset indices/length (buffer kept for now)
        copy(rightObj);
    }
    return *this;
}

template <typename T>
ArrayQueue<T>::~ArrayQueue() {
    delete[] this->buffer;
    this->buffer = nullptr;
    this->length = 0;
    this->maxSize = 0;
    this->frontIndex = 0;
    this->backIndex = 0;
}

template <typename T>
T ArrayQueue<T>::back() const {
    if (isEmpty()) throw string("back: error, queue is empty");
    return this->buffer[this->backIndex];
}

template <typename T>
void ArrayQueue<T>::clear() {
    this->length = 0;
    this->frontIndex = 0;
    this->backIndex = (this->maxSize == 0) ? 0 : (this->maxSize - 1);
}

template <typename T>
void ArrayQueue<T>::copy(const ArrayQueue<T>& copyObj) {
    if (this->buffer != nullptr && this->maxSize != copyObj.maxSize) {
        delete[] this->buffer;
        this->buffer = nullptr;
    }
    if (this->buffer == nullptr) {
        this->maxSize = copyObj.maxSize;
        this->buffer = new T[this->maxSize];
    }
    this->length = copyObj.length;

    if (this->length == 0) {
        this->frontIndex = 0;
        this->backIndex = (this->maxSize == 0) ? 0 : (this->maxSize - 1);
        return;
    }

    // Normalize into 0..length-1 preserving order
    for (int i = 0; i < this->length; ++i) {
        int src = (copyObj.frontIndex + i) % copyObj.maxSize;
        this->buffer[i] = copyObj.buffer[src];
    }
    this->frontIndex = 0;
    this->backIndex  = this->length - 1;
}

template <typename T>
void ArrayQueue<T>::dequeue() {
    if (isEmpty()) throw string("dequeue: error, queue is empty");
    this->frontIndex = (this->frontIndex + 1) % this->maxSize;
    --this->length;
}

template <typename T>
void ArrayQueue<T>::enqueue(const T& elem) {
    if (isFull()) throw string("enqueue: error, queue is full");
    this->backIndex = (this->backIndex + 1) % this->maxSize;
    this->buffer[this->backIndex] = elem;
    ++this->length;
}

template <typename T>
T ArrayQueue<T>::front() const {
    if (isEmpty()) throw string("front: error, queue is empty");
    return this->buffer[this->frontIndex];
}

template <typename T>
int ArrayQueue<T>::getLength() const {
    return this->length;
}

template <typename T>
int ArrayQueue<T>::getMaxSize() const {
    return this->maxSize;
}

template <typename T>
bool ArrayQueue<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
bool ArrayQueue<T>::isFull() const {
    return this->length == this->maxSize;
}