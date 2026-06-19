#include "./RingBuffer.h"
// Constructor of class template.
template <typename T> RingBuffer<T>::RingBuffer(size_t capacity) {
  fieldSize_ = capacity;
  fieldOfElements_ = new T[fieldSize_];

  numOfElements_ = 0;
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

template <typename T> size_t RingBuffer<T>::size() const {
  return numOfElements_;
}
