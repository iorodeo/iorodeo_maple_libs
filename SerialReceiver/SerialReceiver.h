#include "WProgram.h" 

#ifndef SerialReceiver_h
#define SerialReceiver_h

#define SR_MAX_ITEM_SZ 25
#define SR_MAX_ITEMS   4

#define SR_DFLT_START_CHAR '['
#define SR_DFLT_STOP_CHAR ']'
#define SR_DFLT_SEP_CHAR  ',' 

#define SR_STATE_IDLE      0
#define SR_STATE_RECEIVING 1
#define SR_STATE_MESSAGE   2

#define SR_ERR_NONE 0
#define SR_ERR_ILLEGAL_CHAR 1
#define SR_ERR_ITEM_LENGTH 2
#define SR_ERR_MESSAGE_LENGTH 3

class SerialReceiver {

    public:
        SerialReceiver();
        void process(int serialByte);
        bool messageReady();
        void reset();
        uint8 numberOfItems();
        uint8 itemLength(uint8 itemNum);
        char readChar(uint8 itemNum, uint8 ind); 
        int readInt(uint8 itemNum);
        long readLong(uint8 itemNum);
        float readFloat(uint8 itemNum);
        double readDouble(uint8 itemNum);
        void copyString(uint8 itemNum, char *string, uint8 size);
        void printInfo();
        void printMessageInfo();
        void printMessage();
        
    private:
        uint8 state;
        uint8 error;
        char itemBuffer[SR_MAX_ITEMS][SR_MAX_ITEM_SZ+1];
        uint8 itemLenBuffer[SR_MAX_ITEMS];
        uint8 itemCnt;
        uint8 itemPos; 
        char startChar;
        char stopChar; 
        char sepChar;
        void resetItems();
        void resetState();
        void processNewMsg(int serialByte);
        void processCurMsg(int serialByte);
        void handleNewChar(int serialByte);
        void handleSepChar(int serialByte);
        void handleStopChar(int serialByte);
        void handleStartChar(int serialByte);
        bool checkItemRange(uint8 itemNum);
};


#endif
