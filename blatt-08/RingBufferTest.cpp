#include "./RingBuffer.h"
#include <gtest/gtest.h>

TEST(RingBufferTest, RingBufferConstructor) {
  RingBuffer RingBuffer(5);
  ASSERT_EQ(fieldSize_, 5);
}
