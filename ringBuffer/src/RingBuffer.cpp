#include "RingBuffer.hpp"
#include <iostream>

RingBuffer::RingBuffer(size_t size)
    :bufferSize(size), head(0), tail(0),count(0)
{
    if(size == 0)
        throw std::invalid_argument("size must be at least 1");

    buffer = std::make_unique<int32_t[]>(size);
}


uint16_t RingBuffer::getHead(){return head; }
uint16_t RingBuffer::getTail(){return tail; }

bool RingBuffer::isEmpty()
{
    return count == 0;
}

bool RingBuffer::isFull()
{
    return count == bufferSize;
}

void RingBuffer::writeData(int32_t data)
{
    if(isFull())
    {
        std::cout << "buffer is full" << std::endl;
        return;
    }

    buffer[head++] = data;
    if (head >= bufferSize)
        head = 0;

    count++;

}

int32_t RingBuffer::getData()
{
    if(isEmpty())
    {
        std::cout << "buffer is empty, cannot read" << std::endl;
        return -1;
    }

    int32_t val = buffer[tail];
    tail = (tail + 1) % bufferSize;
    count--;
    return val;
}

size_t RingBuffer::getSize(){ return bufferSize; }


