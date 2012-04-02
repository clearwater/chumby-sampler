#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "gpio.h"

GPIO::GPIO()
{
    this->length = 0x10000;  // bytes                                           
    this->offset = 0x80010000;
}

int GPIO::open()
{
    //Prep for reading and writing to memory                                    
    fd = ::open("/dev/mem", O_RDWR);

    if( fd < 0 ) {
        perror("Unable to open /dev/mem");
        fd = 0;
        return -1;
    }

    // void *addr        starting address of the mapping (0)                    
    // size_t len        number of bytes to map (0xffff)                        
    // int prot                                                                 
    // int flags                                                                
    // int fd            file descriptor to map to                              
    // off_t offset      start at byte offset (in the file?)                    

    //Create the memory map                                                     
    this->mem = (unsigned int*)mmap
        (
         0,                         // starting address                         
         this->length,              // length                                   
         PROT_READ | PROT_WRITE,
         MAP_SHARED,
         fd,
         this->offset               // offset will be at address 0              
         );
    return 0;
}

void GPIO::close()
{
    if (this->fd) {
        ::close(this->fd);
    }
}

void GPIO::set(size_t address, unsigned int value)
{
    unsigned long offset = address - this->offset;
    this->mem[offset/sizeof(unsigned int)] = value;
}

unsigned int GPIO::get(size_t address, unsigned int mask)
{
    unsigned long offset = address - this->offset;
    return this->mem[offset/sizeof(unsigned int)] & mask;
}

