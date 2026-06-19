#include "./RingBuffer.h"
#include <gtest/gtest.h>

TEST(RingBufferTest, RingBufferConstructor) {
  // Stores 5 integers.
  size_t capacity1 = 5;
  RingBuffer<int> rb1(capacity1);
  ASSERT_EQ(rb1.getMaxFieldSize(), capacity1);
}

TEST(RingBufferTest, RingBufferSize) {
  RingBuffer<int> rb2(3);
  ASSERT_EQ(rb2.size(), 1);
}
