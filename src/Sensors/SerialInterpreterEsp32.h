#pragma once

#include "../Materials/RGBColor.h"
#include "../Menu/SingleButtonMenu.h"
#include <SerialTransfer.h>

class SerialInterpreterEsp32
{
private:
    static SerialTransfer dataTransfer;

    static struct __attribute__((__packed__)) ESP32Data
    {
        uint8_t faceState;
        uint8_t brightness;
        uint8_t accentBrightness;
        uint8_t useMic;
        uint8_t micLevel;
        uint8_t useBoop;
        uint8_t spectrumMirror;
        uint8_t faceSize;
        uint8_t faceColor;
        uint8_t use;
    } e32DataTX, e32DataRX;

public:
    static void Initialize()
    {
        Serial4.begin(9600);
        dataTransfer.begin(Serial4, true); //_debug = true
        SetCurAll();
    }

    static uint8_t GetMode()
    {
        return e32DataRX.faceState;
    }

    static void SetCurMode(uint8_t curMode)
    {
        e32DataTX.faceState = curMode;
        SendData();
    }

    static void SetCurAll(){
        e32DataTX.faceState = Menu::GetFaceState();
        e32DataTX.brightness = Menu::GetBrightness();
        e32DataTX.accentBrightness = Menu::GetAccentBrightness();
        e32DataTX.useMic = Menu::UseMicrophone();
        e32DataTX.micLevel = Menu::GetMicLevel();
        e32DataTX.useBoop = Menu::UseBoopSensor();
        e32DataTX.spectrumMirror = Menu::MirrorSpectrumAnalyzer();
        e32DataTX.faceSize = Menu::GetFaceSize();
        e32DataTX.faceColor = Menu::GetFaceColor();
    }

    static bool GetUse()
    {
        if (e32DataRX.use == 1)
        {
            SendData();
            return true;
        }
        else
        {
            return false;
        }
    }

    static void Update()
    {
        if (dataTransfer.available())
        {
            dataTransfer.rxObj(e32DataRX);
        }
    }

    static void SendData()
    {
        //uint16_t sendSize = 0;
        //sendSize = dataTransfer.txObj(e32DataTX, sendSize);
        dataTransfer.sendDatum(e32DataTX);
    }
};

SerialTransfer SerialInterpreterEsp32::dataTransfer;
SerialInterpreterEsp32::ESP32Data SerialInterpreterEsp32::e32DataRX;
SerialInterpreterEsp32::ESP32Data SerialInterpreterEsp32::e32DataTX;
