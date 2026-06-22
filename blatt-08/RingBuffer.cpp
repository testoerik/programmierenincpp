#include "./RingBuffer.h"

//_____________________________________________________________________________
template <typename T> RingBuffer<T>::RingBuffer(size_t capacity) {
  fieldSize_ = capacity;
  fieldOfElements_ = new T[fieldSize_];

  numOfElements_ = 0;

  head_ = 0;
  tail_ = 0;
}

//_____________________________________________________________________________
template <typename T> size_t RingBuffer<T>::getMaxFieldSize() const {
  return fieldSize_;
}

//_____________________________________________________________________________
template <typename T> size_t RingBuffer<T>::size() const {
  return numOfElements_;
}

//_____________________________________________________________________________
template <typename T> bool RingBuffer<T>::isEmpty() const {
  return numOfElements_ == 0;
}

//_____________________________________________________________________________
template <typename T> bool RingBuffer<T>::isFull() const {
  return numOfElements_ == fieldSize_;
}

//_____________________________________________________________________________
template <typename T> void RingBuffer<T>::push(T value) {
  fieldOfElements_[tail_] = value;
  numOfElements_++;
  tail_ = (tail_ + 1) % fieldSize_;
}

//_____________________________________________________________________________
template <typename T> T RingBuffer<T>::pop() {
  T firstElement = fieldOfElements_[head_];
  numOfElements_--;
  head_ = (head_ + 1) % fieldSize_;
  return firstElement;
}

//_____________________________________________________________________________
template <typename T> T RingBuffer<T>::operator[](int index) const {
  return fieldOfElements_[index];
}

//_____________________________________________________________________________
template <typename T> RingBuffer<T>::~RingBuffer() {
  delete[] fieldOfElements_;
}

//_____________________________________________________________________________
template class RingBuffer<int>;
template class RingBuffer<float>;

//_____________________________________________________________________________
RingBuffer<bool>::RingBuffer(size_t capacity) {
  bitStringSize_ = capacity;
  bitStringMemory_ = 0;
  numOfBits_ = 0;

  head_ = 0;
  tail_ = 0;
}

//_____________________________________________________________________________
size_t RingBuffer<bool>::size() const { return bitStringSize_; }

//_____________________________________________________________________________
bool RingBuffer<bool>::isFull() const { return numOfBits_ == bitStringSize_; }

//_____________________________________________________________________________
bool RingBuffer<bool>::isEmpty() const { return numOfBits_ == 0; }

//_____________________________________________________________________________
void RingBuffer<bool>::push(bool value) {
  if (value) {
    bitStringMemory_ |= (uint64_t(1) << tail_);
  } else {
    bitStringMemory_ &= ~(uint64_t(1) << tail_);
  }
  tail_ = (tail_ + 1) % bitStringSize_;
  numOfBits_++;
}

//_____________________________________________________________________________
bool RingBuffer<bool>::pop() {
  bool firstElement = ((bitStringMemory_ & (uint64_t(1) << head_)) != 0);
  bitStringMemory_ = (bitStringMemory_ & ~(uint64_t(1) << head_));
  head_ = (head_ + 1) % bitStringSize_;
  numOfBits_--;
  return firstElement;
}
