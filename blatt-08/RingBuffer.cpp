#include "./RingBuffer.h"
// Definition of the template of the constructor.
template <typename T> RingBuffer<T>::RingBuffer(size_t capacity) {
  fieldSize_ = capacity;
  fieldOfElements_ = new T[fieldSize_];
}
// Definition of the template of the destructor.
template <typename T> RingBuffer<T>::~RingBuffer() {
  delete[] fieldOfElements_;
}
template class RingBuffer<int>;

// Definition of the template specialization for the constructor of
// fieldOfElements_ which contains integers.
RingBufferInt::RingBufferInt(int capacity) {
  fieldSize_ = capacity;
  fieldOfElements_ = new int[fieldSize_];
}
// Definition of the template specialization for the destructor of
// fieldOfElements_ which contains integers.
RingBufferInt::~RingBufferInt() { delete[] fieldOfElements_; }
