#ifndef _FLASH_MEMORY_H_
#define _FLASH_MEMORY_H_
#include "wirish.h"
#include "flash_stm32.h"

#define FLASH_MEM_NUM_PAGES       ((uint8) 10)
#define FLASH_MEM_PAGE_SIZE       ((uint16)0x400)  /* Page size = 1KByte */
#define FLASH_MEM_START_ADDRESS   ((uint32)(0x8000000 + 128 * 1024 - FLASH_MEM_NUM_PAGES * FLASH_MEM_PAGE_SIZE))
#define FLASH_MEM_MAX_ADDRESS     ((uint16) (((FLASH_MEM_PAGE_SIZE - 2)/2)+1))

class FlashMemory {

    public:
        static const uint8 numPages = FLASH_MEM_NUM_PAGES;
        static const uint16 pageSize = FLASH_MEM_PAGE_SIZE;
        static const uint32 startAddress = FLASH_MEM_START_ADDRESS;
        static const uint16 maxAddress = FLASH_MEM_MAX_ADDRESS;

        FlashMemory();
        bool erasePage(uint8 pageNum);
        bool eraseAllPages();
        bool writeData(uint8 pageNum, uint16 address, uint16 data);
        bool writeData(uint8 pageNum, uint16 address, uint8 data0, uint8 data1);
        bool readData(uint8 pageNum, uint16 address, uint16 &data);
        bool readData(uint8 pageNum, uint16 address, uint8 &data0, uint8 &data1);

        void printBasePageAddress();
        void printPage(uint8 pageNum, bool asUint8=false);

    private:
        void lock();
        void unlock();
        uint32 basePageAddress[FLASH_MEM_NUM_PAGES];

};


uint16 pack_uint8(uint8 dataIn0, uint8 dataIn1);
void unpack_uint8(uint16 dataIn, uint8 &dataOut0, uint8 &dataOut1);

extern FlashMemory flashMemory;

#endif
