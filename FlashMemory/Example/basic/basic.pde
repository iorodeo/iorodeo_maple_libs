#include <Streaming.h>
#include <FlashMemory.h>

void printHelp();
void eraseFlashPage();
void writeToUint16FlashPage();
void writeToUint8FlashPage();
void printFlashPage();

const char cmdPrintHelp = '0';
const char cmdEraseFlashPage = '1';
const char cmdWriteUint16ToFlashPage = '2';
const char cmdWriteUint8ToFlashPage = '3';
const char cmdPrintFlashPage = '4';

const uint8 flashPageNum=1;

void setup() {
}

void loop() {

    while (SerialUSB.available() >0) {
        char cmd = SerialUSB.read();

        switch (cmd) {

            case cmdPrintHelp:
                printHelp();
                break;

            case cmdEraseFlashPage:
                eraseFlashPage();
                break;

            case cmdWriteUint16ToFlashPage:
                writeUint16ToFlashPage();
                break;

            case cmdWriteUint8ToFlashPage:
                writeUint8ToFlashPage();
                break;

            case cmdPrintFlashPage:
                printFlashPage();
                break;

            default:
                break;
        }
    }
}

void printHelp() {
    SerialUSB << "Command Summary" << endl;
    SerialUSB << "-------------------------------------------------------------" << endl;
    SerialUSB << "0 - print help" << endl;
    SerialUSB << "1 - erase flash page" << endl;
    SerialUSB << "2 - write uint16 data to flash page" << endl;
    SerialUSB << "3 - write uint8 data to flash page" << endl;
    SerialUSB << "4 - print flash page" << endl;
    SerialUSB << endl;
}

void eraseFlashPage() {
    flashMemory.erasePage(flashPageNum);
    SerialUSB << "page erased" << endl;
}

void writeUint16ToFlashPage() {
    uint16 value=0;
    for (uint16 address=0; address<flashMemory.maxAddress; address++) {
        flashMemory.writeData(flashPageNum,address,value);
        value += 2;
    }
    SerialUSB << "uint16 data written to flash" << endl;
}

void writeUint8ToFlashPage() {
    uint8 data0=0;
    uint8 data1=0;
    for (uint16 address=0; address<flashMemory.maxAddress; address++) {
        flashMemory.writeData(flashPageNum,address,data0,data1);
        if (data0 < 255) {
            data0++;
        }
        else {
            data0 = 0;
            data1++;
        }
    }
    SerialUSB << "uint8 data written to flash" << endl;
}

void printFlashPage() {
    uint16 data_uint16;
    uint8 data0_uint8;
    uint8 data1_uint8;
    SerialUSB << "Flash Page #: " << flashPageNum << endl;
    SerialUSB << "-------------------------------------------------------------" << endl;
    SerialUSB << "address : data_int16, data0_uint8, data1_uint8" << endl;
    for (uint16 address=0; address<flashMemory.maxAddress; address++) {
        flashMemory.readData(flashPageNum, address, data_uint16);
        flashMemory.readData(flashPageNum, address, data0_uint8, data1_uint8);
        SerialUSB << address << " : " << data_uint16 << ", " << data0_uint8 << ", " << data1_uint8 << endl;
    }
    SerialUSB << endl;
}
