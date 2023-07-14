#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

class SSD1306
{

public:
  Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

  struct DisplayCon
  {
    String line0;
    String line1;

    String line2;
    String line3;
    String line4;
  } displayData;

  // Initialize the display
  void Begin()
  {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    delay(500);

    // Clear the buffer.
    Clear();

    UpdateDisplay(displayData);
  }

  // Clear the display
  void Clear()
  {
    // Clear the buffer.
    display.clearDisplay();
    display.display();
  }

  // Set the display brightness
  void SetBrightness(uint8_t value)
  {
    SendCommand(0x81); // Set contrast control
    SendCommand(value);
  }

  // Print text to a specific line on the display
  void PrintLine(int16_t line, String text)
  {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, line*8);
    display.print(text);
    display.display(); // actually display all of the above
  }

  void UpdateDisplay(DisplayCon data)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0*8);
    display.print(data.line0);

    display.setCursor(0, 1*8);
    display.print(data.line1);

    display.setCursor(0, 2*8);
    display.print(data.line2);

    display.setCursor(0, 3*8);
    display.print(data.line3);

    display.setCursor(0, 4*8);
    display.print(data.line4);

    display.display();
  }

private:
  // Send a command to the display
  void SendCommand(uint8_t value)
  {
    Wire.beginTransmission(0x3C); // I2C address of the display
    Wire.write(0x00);             // Co = 0, D/C = 0
    Wire.write(value);
    Wire.endTransmission();
  }

  // Send data to the display
  void SendData(uint8_t value)
  {
    Wire.beginTransmission(0x3C); // I2C address of the display
    Wire.write(0x40);             // Co = 0, D/C = 1
    Wire.write(value);
    Wire.endTransmission();
  }
};