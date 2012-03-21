#include <stddef.h>

class GPIO
{
    unsigned int *mem;
    int fd;
    size_t length;
    size_t offset;

 public:
    GPIO();
    int open();
    void close();
    void set(size_t address, unsigned int value);
};
