#include "./RingBuffer.h"
#include <gtest/gtest.h>

TEST(RingBufferTest, RingBufferConstructor) {
  // Stores 5 integers.
  RingBuffer<int> rb1(5);
  ASSERT_EQ(rb1.getFieldSize(), 5);
}
