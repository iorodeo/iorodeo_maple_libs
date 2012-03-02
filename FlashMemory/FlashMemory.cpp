#include "FlashMemory.h"
#include "WProgram.h"
#include <Streaming.h>

FlashMemory::FlashMemory() {
    // Contructor for Flash memory - sets base address for flash memory
    // pages.
    for (uint8 i=0; i<numPages; i++) {
        basePageAddress[i] = startAddress + i*((uint32) pageSize);
    }
    lock();
}

void FlashMemory::unlock() {
    FLASH_Unlock();
}

void FlashMemory::lock() {
    FLASH_Lock();
}

bool FlashMemory::erasePage(uint8 pageNum) {
    // Erases a page of flash memory given the page number
    FLASH_Status status;
    if (pageNum >= numPages) {
        return false;
    }
    unlock();
    status = FLASH_ErasePage(basePageAddress[pageNum]);
    lock();
    if (status == FLASH_COMPLETE) {
        return true;
    }
    else {
        return false;
    }
}

bool FlashMemory::eraseAllPages() {
    // Erases all pages of flash memory
    bool rtnVal = true;
    for (uint8 pageNum=0; pageNum<numPages; pageNum++) {
        if (!erasePage(pageNum)) {
            rtnVal = false;
        }
    }
    return rtnVal;
}

bool FlashMemory::writeData(uint8 pageNum, uint16 address, uint16 data) {
    // Writes uint16 data to the given page and address of flash memory.
    uint32 trueAddress; 
    FLASH_Status status;
    if (pageNum >= numPages) {
        return false;
    }
    if (address >= maxAddress) {
        return false;
    }
    trueAddress = basePageAddress[pageNum] + 2*((uint32) address);
    unlock();
    status = FLASH_ProgramHalfWord(trueAddress, data);
    lock();
    if (status == FLASH_COMPLETE) {
        return true;
    }
    else {
        return false;
    }
}

bool FlashMemory::writeData(uint8 pageNum, uint16 address, uint8 data0, uint8 data1) {
    // Writes two uint8 data to the given page and address of flash memory. 
    uint16 packedData;
    packedData = pack_uint8(data0,data1);
    return writeData(pageNum, address, packedData);
}

bool FlashMemory::readData(uint8 pageNum, uint16 address, uint16 &data) {
    // Reads the given page and address of flash memory and returns the value
    // as a uint16. 
    uint32 trueAddress; 
    FLASH_Status status;
    if (pageNum >= numPages) {
        return false;
    }
    if (address >= maxAddress) {
        return false;
    }
    trueAddress = basePageAddress[pageNum] + 2*((uint32) address); 
    data = *((uint16*)  trueAddress);
    return true;
}

bool FlashMemory::readData(uint8 pageNum, uint16 address, uint8 &data0, uint8 &data1) {
    // Read the given page and address of flash memory and returns the data as two uint8. 
    bool rtnVal;
    uint16 packedData;
    rtnVal = readData(pageNum, address, packedData);
    unpack_uint8(packedData,data0,data1);
    return rtnVal;
}

void FlashMemory::printBasePageAddress() {
    // Prints the base page addresses
    for (uint8 i=0; i<numPages; i++) {
        SerialUSB << "page: " << i << " " << _HEX(basePageAddress[i]) << endl;
    }
    SerialUSB << endl;
}

void FlashMemory::printPage(uint8 pageNum, bool asUint8) {
    // Prints the given page of flash memory.
    uint16 value;
    uint8 value0;
    uint8 value1;
    if (pageNum >= numPages) {
        SerialUSB << "pageNum > numPages" << endl;
        return;
    }
    SerialUSB << "page, address, value" << endl;
    for (uint16 address=0; address<maxAddress; address++) { 
        if (asUint8) {
            readData(pageNum, address, value0, value1);
            SerialUSB << pageNum << ", " << address << ", " << value0 << ", " << value1 << endl; 
        }
        else {
            readData(pageNum, address, value);
            SerialUSB << pageNum << ", " << address << ", " << value << endl; 
        }
    }
    SerialUSB << endl;
}

uint16 pack_uint8(uint8 dataIn0, uint8 dataIn1) {
    // Packs two uint8s into a uint16
    return (((uint16) dataIn0) << 8) | ((uint16) dataIn1);
}

void unpack_uint8(uint16 dataIn, uint8 &dataOut0, uint8 &dataOut1) {
    // Unpacks two uint8s from a unit16
    dataOut0 = (uint8) (dataIn >> 8);
    dataOut1 = (uint8) (0x00ff & dataIn);
}

FlashMemory flashMemory;

