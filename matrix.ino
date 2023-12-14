#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define WIDTH 128
#define HEIGHT 64
#define OLED_DC 7
#define OLED_CS 10
#define OLED_RESET 8
Adafruit_SSD1306 display(WIDTH, HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);
#define MODE SSD1306_SWITCHCAPVCC  // get display voltage from 3.3V internally


//TFT_eSPI tft = TFT_eSPI(); //Invoke library, pins defined in user_setup.h


const int BUTTON = 16;
const int LED = 5;
int timedelay = 25;

int height =128;
int width = 64;
int y[120];
int x;
int temp;
char z;

byte randNumber;    // if your random number
byte prevRand = 0;  //could be initialized


void setup(void) {
  Serial.begin(9600);
  if (!display.begin(MODE)) {
    Serial.println("Could not initialize display");
    while (1)
      ;  // halt
  }
  //showAt(10,10,"Start",1);
  //display.display();
  display.setRotation(1);
  display.setTextColor(SSD1306_BLACK);
  display.clearDisplay();  
  pinMode(BUTTON, INPUT);
  pinMode(LED, OUTPUT);
  for (x = 0; x < width; x = x + 8) {
    temp = random(0, height / 8) * 8;
    do {
      y[x] = random(0, height / 8) * 8;

    } while (temp != y[x]);
  }
}
void loop() {
  for (x = 0; x < width; x = x + 8) {
    temp = random(0, 10);
    if (temp <= 2)
      z = ('0' + random(0, 10));
    else if (temp <= 4)
      z = ('a' + random(0, 27));
    else if (temp <= 6)
      z = ('A' + random(0, 27));
    else
      z = (' ' + random(1, 220));
    if (x == 16)
      display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
    else if (x == 48)
      display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
    else if (x == 96)
      display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
    else
      display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
      showAt(x,y[x],z);
    // display.setCursor(x, (y[x] / x));
    // display.print(z);
    temp = y[x] - 16;
    if (temp < 0)  //When there is negative value
      temp = temp + height;
    else if (temp >= height)
      temp = 0;
    showAt(x,temp,z);
   
    temp = y[x] - 80;
    if (temp < 0)  //When there is negative
      temp = temp + height;
    else if (temp >= height)
      temp = 0;
    showAt(x,temp,' ');
    temp = y[x] + 8;
    if (temp < 0)  //When there is negative value
      temp = temp + height;
    else if (temp >= height)
      temp = 0;
    y[x] = temp;

    delay(8);
  }
}


void showAt(int x, int y, char text)
{
  //display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(x, y); // Move the cursor to 0,0
  //display.clearDisplay();  // clear the screen
  display.setTextSize(1);
  display.write(text);
  display.display();
}
