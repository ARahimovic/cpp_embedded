### Welcome to Ring Buffer implementation
This is the first data structure that we need to implement in our journey of creating shell programms and a shell interpreter

## What is a ring buffer
a ring buffer is simply a fixed size buffer, that can loop, 
and operates on the principle of FIFO (first in , first out)
basically we have a fixed sized buffer (an array, or maybe dynamic allocations) then we have two index HEAD, TAIL, HEAD is used to write data, and TAIL is used to read the data
after each write/read we increment the appropriate indexes, and if it reaches the end, we loop.

data is overwritten , when we write in an already writen slot


we Will write a class that implemnets this data structure
