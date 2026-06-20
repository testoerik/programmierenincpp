#include "./RingBuffer.h"
#include <gtest/gtest.h>

TEST(RingBufferTest, RingBufferConstructor) {
  // Stores 5 integers.
  size_t capacity1 = 5;
  RingBuffer<int> rb1(capacity1);
  ASSERT_EQ(rb1.getMaxFieldSize(), capacity1);
}

TEST(RingBufferTest, RingBufferSize) {
  size_t capacity2 = 3;
  RingBuffer<int> rb2(capacity2);
  ASSERT_EQ(rb2.size(), 0);
  ASSERT_TRUE(rb2.isEmpty());
  ASSERT_FALSE(rb2.isFull());
}

TEST(RingBufferTest, RingBuffer) {
  size_t capacity3 = 4;
  RingBuffer<int> rb3(capacity3);
  rb3.push(47);
  ASSERT_FALSE(rb3.isEmpty();
  // ASSERT_EQ(head_, 3);
}
