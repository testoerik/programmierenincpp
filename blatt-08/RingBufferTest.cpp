#include "./RingBuffer.h"
#include <gtest/gtest.h>

TEST(RingBufferTest, RingBufferConstructor) {
  // Stores 5 integers.
  size_t capacity1 = 5;
  RingBuffer<int> rb1(capacity1);
  ASSERT_EQ(rb1.getFieldSize(), capacity1);
}
