#include "./RingBuffer.h"
// Constructor of class template.
template <typename T> RingBuffer<T>::RingBuffer(size_t capacity) {
  fieldSize_ = capacity;
  fieldOfElements_ = new T[fieldSize_];
}

template <typename T> size_t RingBuffer<T>::getMaxFieldSize() const {
  return fieldSize_;
}
// Destructor of class template.
template <typename T> RingBuffer<T>::~RingBuffer() {
  delete[] fieldOfElements_;
}
template class RingBuffer<int>;
template class RingBuffer<float>;
// Subscript operator.
template <typename T> RingBuffer<T>::operator[](int i) const {
  return fieldOfElements_[i];
}

template <typename T> size_t RingBuffer<T>::size() const {
  size_t elementCounter = 0;
  for (int i = 0; i < fieldSize_; i++) {
    if (fieldOfElements_[i] != 0) {
      elementCounter++;
    } else {
      continue;
    }
  }
  return elementCounter;
}
