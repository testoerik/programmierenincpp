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

TEST(RingBufferTest, RingBufferInt) {
  size_t capacity3 = 4;
  RingBuffer<int> rb3(capacity3);
  ASSERT_TRUE(rb3.isEmpty());
  ASSERT_FALSE(rb3.isFull());
  rb3.push(47);
  rb3.push(56);
  rb3.push(48);
  rb3.push(49);
  ASSERT_TRUE(rb3.isFull());
  ASSERT_EQ(rb3.pop(), 47);
  rb3.push(456);
  ASSERT_EQ(rb3[0], 456);
  ASSERT_EQ(rb3.pop(), 56);
  rb3.push(123);
  ASSERT_EQ(rb3[1], 123);
  // ASSERT_EQ(head_, 3);
}

TEST(RingBufferTest, RingBufferFloat) {
  size_t capacity4 = 5;
  RingBuffer<float> rb4(capacity4);
  ASSERT_TRUE(rb4.isEmpty());
  ASSERT_FALSE(rb4.isFull());
  rb4.push(4.67);
  rb4.push(3.14);
  rb4.push(4.89);
  ASSERT_FLOAT_EQ(rb4.pop(), 4.67);
}

TEST(RingBufferTest, TemplateClassSpecialization) {
  {
    size_t capacity5 = 2;
    RingBuffer<bool> rb5(capacity5);
    rb5.push(true);
    ASSERT_EQ(rb5.bitStringMemory_, 1);
    rb5.push(true);
    ASSERT_EQ(rb5.bitStringMemory_, 3);
    rb5.pop();
    ASSERT_EQ(rb5.bitStringMemory_, 2);
    rb5.pop();
    ASSERT_EQ(rb5.bitStringMemory_, 0);
    rb5.push(true);
    ASSERT_EQ(rb5.bitStringMemory_, 1);
  }
  {
    size_t capacity6 = 2;
    RingBuffer<bool> rb6(capacity6);
    ASSERT_TRUE(rb6.isEmpty());
    ASSERT_FALSE(rb6.isFull());
    rb6.push(true);
    rb6.push(true);
    ASSERT_FALSE(rb6.isEmpty());
    ASSERT_TRUE(rb6.isFull());
  }
  {
    size_t capacity7 = 64;
    RingBuffer<bool> rb7(capacity7);
    ASSERT_FALSE(rb7.isFull());
    for (int i = 0; i < capacity7; i++) {
      rb7.push(true);
    }
    ASSERT_TRUE(rb7.isFull());
    ASSERT_EQ(rb7.tail_, 0);
    for (int i = 0; i < capacity7; i++) {
      rb7.pop();
    }
    ASSERT_TRUE(rb7.isEmpty());
    ASSERT_FALSE(rb7.isFull());
    ASSERT_EQ(rb7.head_, 0);
    rb7.push(true);
    ASSERT_EQ(rb7.tail_, 1);
    ASSERT_FALSE(rb7.isEmpty());
  }
}
