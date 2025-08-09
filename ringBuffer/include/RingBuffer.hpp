#include <cstdint>
#include <cstddef>
#include <memory>

class RingBuffer
{
    private:
    
    std::unique_ptr<int32_t[]> buffer;
    size_t bufferSize;
    uint16_t head;
    uint16_t tail;
    size_t count;


    public :
        explicit RingBuffer(size_t size);
        RingBuffer(const RingBuffer&) = delete;


        uint16_t getHead();
        uint16_t getTail();
        void writeData(int32_t data);
        int32_t getData();
        bool isEmpty();
        bool isFull();
        void reset();
        size_t getSize();
        
        ~RingBuffer()=default;
    
};


