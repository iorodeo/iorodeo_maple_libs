#include "Streaming.h"
#include "SerialReceiver.h"

SerialReceiver receiver = SerialReceiver();

void setup() {
}

void loop() {
    int myInt;
    float myFloat;

    while (SerialUSB.available() > 0) {
        receiver.process(SerialUSB.read());
        if (receiver.messageReady()) {
            SerialUSB << "Message Ready" << endl;
            SerialUSB << "-------------" << endl;
            myInt = receiver.readInt(0);
            myFloat = receiver.readFloat(1);
            SerialUSB << "myInt = " << _DEC(myInt) << endl;
            SerialUSB << "myFloat = " << myFloat << endl;
            SerialUSB << "-------------" << endl;
            SerialUSB << endl;
            receiver.reset();
        }
    }
}

