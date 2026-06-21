#include "./RingBuffer.h"
// Constructor of class template.
template <typename T> RingBuffer<T>::RingBuffer(size_t capacity) {
  fieldSize_ = capacity;
  fieldOfElements_ = new T[fieldSize_];

  numOfElements_ = 0;

  head_ = 0;
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
  fieldOfElements_[tail_] = value;
  numOfElements_++;
  tail_ = (tail_ + 1) % fieldSize_;
}

template <typename T> T RingBuffer<T>::pop() {
  T firstElement = fieldOfElements_[head_];
  numOfElements_--;
  head_ = (head_ + 1) % fieldSize_;
  return firstElement;
}

template <typename T> T RingBuffer<T>::operator[](int index) const {
  return fieldOfElements_[index];
}
// Destructor of class template.
template <typename T> RingBuffer<T>::~RingBuffer() {
  delete[] fieldOfElements_;
}
// Explicit template class instantiation.
template class RingBuffer<int>;
template class RingBuffer<float>;

// Specialization of the class template.
// Constructor.
RingBuffer<bool>::RingBuffer(size_t capacity) {
  bitStringSize_ = capacity;
  char bitStringBuffer[bitStringSize_];
  for (int i = 0; (i < 64) && (i < bitStringSize_); i++) {
    bitStringBuffer[i] = '0';
  }
}
