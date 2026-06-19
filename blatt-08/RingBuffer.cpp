#include "./RingBuffer.h"
// Constructor of class template.
template <typename T> RingBuffer<T>::RingBuffer(size_t capacity) {
  fieldSize_ = capacity;
  fieldOfElements_ = new T[fieldSize_];

  numOfElements_ = 0;

  head_ = fieldSize_ - 1;
  tail_ = 0;
}

template <typename T> size_t RingBuffer<T>::getMaxFieldSize() const {
  return fieldSize_;
}

template <typename T> size_t RingBuffer<T>::size() const {
  return numOfElements_;
}

template <typename T> bool RingBuffer<T>::isEmpty() const {
  return numOfElements_ == 0;
}

template <typename T> bool RingBuffer<T>::isFull() const {
  return numOfElements_ == fieldSize_;
}

template <typename T> void RingBuffer<T>::push(T value) {
  if (fieldOfElements_.isFull()) {
    return;
  } else {
    fieldOfElements_[head_] = value;
  }
}
// Destructor of class template.
template <typename T> RingBuffer<T>::~RingBuffer() {
  delete[] fieldOfElements_;
}
// Explicit template class instantiation.
template class RingBuffer<int>;
template class RingBuffer<float>;
