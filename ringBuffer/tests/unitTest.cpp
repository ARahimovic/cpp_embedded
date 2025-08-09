#include <gtest/gtest.h>
#include "RingBuffer.hpp"


TEST(RingBufferTest, testSize)
{
    RingBuffer rb(20);
    EXPECT_EQ(rb.getSize(), 20);
    
    EXPECT_THROW(RingBuffer rb_invalid(-1), std::bad_array_new_length);
    
    EXPECT_THROW(RingBuffer rb_invalid(0), std::invalid_argument);
}



TEST(RingBufferTest, WriteAndReadData) {
    RingBuffer rb(5);
    
    rb.writeData(10);
    rb.writeData(20);
    rb.writeData(30);
    
    EXPECT_EQ(rb.getData(), 10);
    EXPECT_EQ(rb.getData(), 20);
    EXPECT_EQ(rb.getData(), 30);
    EXPECT_TRUE(rb.isEmpty());
}



TEST(RingBufferTest, testFullEmpty)
{
    RingBuffer rb(3);
    EXPECT_TRUE(rb.isEmpty());
    
    rb.writeData(10);
    rb.writeData(20);
    rb.writeData(30);
    
    EXPECT_FALSE(rb.isEmpty());
    EXPECT_TRUE(rb.isFull());

    EXPECT_EQ(rb.getData(), 10);
    EXPECT_EQ(rb.getData(), 20);
    EXPECT_EQ(rb.getData(), 30);

    EXPECT_TRUE(rb.isEmpty());
    EXPECT_FALSE(rb.isFull());
}

TEST(RingBufferTest, testHeadTail)
{
    RingBuffer rb(5);

    EXPECT_EQ(rb.getHead(), 0);
    EXPECT_EQ(rb.getTail(), 0);

    rb.writeData(0);
    
    EXPECT_EQ(rb.getHead(), 1);
    EXPECT_EQ(rb.getTail(), 0);

    //should increment the tail
    EXPECT_EQ(rb.getData(), 0);

    EXPECT_EQ(rb.getHead(), 1);
    EXPECT_EQ(rb.getTail(), 1);
    EXPECT_TRUE(rb.isEmpty());
   
    rb.writeData(1); 
    rb.writeData(2);
    rb.writeData(3);
    rb.writeData(4);
    rb.writeData(5);

    //the buffer should be full
    EXPECT_TRUE(rb.isFull());
    //the head is now at pos 0
    EXPECT_EQ(rb.getHead(), 1);
    EXPECT_EQ(rb.getTail(), 1);
    
}