#pragma once

#include "../Materials/RGBColor.h"
#include <SerialTransfer.h>

class SerialInterpreterEsp32{
private:
    static SerialTransfer dataTransfer;

    static struct ESP32Data {
        uint16_t r;
        uint16_t g;
        uint16_t b;
        uint8_t mode;
        uint8_t curMode;
        uint8_t use;
    } e32DataTX, e32DataRX;

public:

    static void Initialize(){
        Serial4.begin(9600);
        dataTransfer.begin(Serial4, true);//_debug = true
    }

    static RGBColor GetColor(){
        return RGBColor(e32DataRX.r, e32DataRX.g, e32DataRX.b);
    }

    static uint8_t GetMode(){
        return e32DataRX.mode;
    }

    static void SetCurMode(uint8_t curMode){
        e32DataTX.curMode = curMode;
        SendData();
    }

    static bool GetUse(){
        if (e32DataRX.use == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    static void Update(){
        if(dataTransfer.available()){

            dataTransfer.rxObj(e32DataRX);

            Serial.print(GetUse());
            Serial.println(GetMode());
            //Serial.println(GetColor().ToString());
            //Serial.print("\t");
        }
    }

    static void SendData(){
        uint16_t sendSize = 0;
        sendSize = dataTransfer.txObj(e32DataTX, sendSize);
        dataTransfer.sendData(sendSize);
    }

};

SerialTransfer SerialInterpreterEsp32::dataTransfer;
SerialInterpreterEsp32::ESP32Data SerialInterpreterEsp32::e32DataRX;
SerialInterpreterEsp32::ESP32Data SerialInterpreterEsp32::e32DataTX;
