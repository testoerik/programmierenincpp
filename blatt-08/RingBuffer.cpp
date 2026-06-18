#include "./RingBuffer.h"
template <typename T> RingBuffer<T>::RingBuffer(size_t capacity) {
  fieldSize_ = capacity;
  fieldOfElements_ = new T[fieldSize_];
}

template class RingBuffer<int>;
