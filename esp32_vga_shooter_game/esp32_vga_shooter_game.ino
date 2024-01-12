//This example shows several 2d drawing features available for VGA
//You need to connect a VGA screen cable and an external DAC (simple R2R does the job) to the pins specified below.
//cc by-sa 4.0 license
//bitluni

//include libraries
#include <ESP32Lib.h>
#include <Ressources/Font6x8.h>
#include <ezButton.h>

//include a wallpaper
#include "isagi.h"
#include "kenya.h"
#include "cole.h"
#include "lebron.h"
#include "kendrick.h"
#include "attack.h"
#include "run.h"
#include "roll.h"
#include "die.h"
#include "idle.h"

//pin configuration
const int redPins[] = {2, 4, 12, 13, 14};
const int greenPins[] = {15, 16, 17, 18, 19};
const int bluePins[] = {21, 22, 23, 27};
const int hsyncPin = 32;
const int vsyncPin = 33;

#define PlayerOneXJoystickPin  34
#define PlayerOneYJoystickPin  35 
#define PlayerTwoXJoystickPin  26
#define PlayerTwoYJoystickPin  25


int x, y;
int a, b;
int joystickX = 0; 
int joystickY = 0; 
int joystickTwoX = 0;
int joystickTwoY = 0;
int joystickButtonPin = 5;
int joystickTwoButtonPin = 0;

bool isGameOver = false;
bool isPlayerOneTheWinner = false;

int pointOneX, pointOneY, pointTwoX, pointTwoY, pointThreeX, pointThreeY, pointFourX, pointFourY, pointFiveX, pointFiveY, pointSixX, pointSixY;
bool pointOneScored = false;
bool pointTwoScored = false;
bool pointThreeScored = false;
bool pointFourScored = false;
bool pointFiveScored = false;
bool pointSixScored = false;

ezButton joystickButton(joystickButtonPin);
ezButton joystickTwoButton(joystickTwoButtonPin);

int MODE = 0;
int previous_mode;
int modes = 3;

#define wallpapers 5
int wallpaper_index = 0;
int previous_wallpaper_state = 1;

//VGA Device
VGA6Bit vga;

//initial setup
void setup()
{
	//we need double buffering for smooth animations
	vga.setFrameBufferCount(2);
	//initializing i2s vga (with only one framebuffer)
	vga.init(vga.MODE200x150, redPins, greenPins, bluePins, hsyncPin, vsyncPin);
	//setting the font
	vga.setFont(Font6x8);

  x = 25;
  y = 10;

  a = 194;
  b = 144;

  pointOneX = random(25, 195 + 1);
  pointOneY = random(10, 145 + 1);
  pointTwoX = random(25, 195 + 1);
  pointTwoY = random(10, 145 + 1);
  pointThreeX = random(25, 195 + 1);
  pointThreeY = random(10, 145 + 1);
  pointFourX = random(25, 195 + 1);
  pointFourY = random(10, 145 + 1);
  pointFiveX = random(25, 195 + 1);
  pointFiveY = random(10, 145 + 1);
  pointSixX = random(25, 195 + 1);
  pointSixY = random(10, 145 + 1);
}

//just draw each frame
void loop()
{
  //some value for color ping pong
  static int c = 0;
	static int d = 1;
	c += d;
	if (c == 0 || c == 255)
		d = -d;

	//clear the back buffer with black and start drawing
	vga.clear(0);

  if(joystickButton.getStateRaw() == 0){
   if (previous_wallpaper_state != 0){
      if (wallpaper_index < wallpapers){
      wallpaper_index = wallpaper_index + 1;
      }
      if (wallpaper_index == wallpapers ){
      wallpaper_index = 0;
      }
   }
  }

  if(joystickTwoButton.getStateRaw() == 0){
   if (previous_mode != 0){
      if (MODE < modes){
      MODE = MODE + 1;
      }
      if (MODE == modes ){
      MODE = 0;
      }
   }
  }

  previous_wallpaper_state = joystickButton.getStateRaw();
  previous_mode = joystickTwoButton.getStateRaw();

	// x = 170;
	// y = 5;
	// vga.setCursor(x, y);
	// vga.print("line(x0,y0,x1,y1,c)");
	// //draw a line
	// vga.line(x + c / 8 + 50, y + 10, x + 32 + 40 - c / 8, y + 30, vga.RGB(0, c, 255 - c));

	// x = 15;
	// y = 40;
	// vga.setCursor(x + 10, y);
	// vga.print("rect(x, y, w, h, c)");
	// //draw a rectangle with the given width and height
	// vga.rect(x + 50, y + 15, 3 + c / 8, 19 - c / 16, vga.RGB(0, c, 255 - c));

	// x = 165;
	// y = 40;
	// vga.setCursor(x, y);
	// //draw a filled rectangle
	// vga.print("fillRect(x, y, w, h, c)");
	// vga.fillRect(x + 50, y + 15, 35 - c / 8, 3 + c / 16, vga.RGB(255 - c, c, 0));

	// x = 25;
	// y = 80;
	// vga.setCursor(x + 10, y);
	// //draw a circle with the given radius
	// vga.print("circle(x,y,r,c)");
	// vga.circle(x + 55, y + 20, 1 + r / 4, vga.RGB(255 - c, 0, c));

	// x = 172;
	// y = 80;
	// vga.setCursor(x, y);
	// //draw a filled circle
	// vga.print("fillCircle(x,y,r,c)");
	// vga.fillCircle(x + 60, y + 20, 8 - r / 4, vga.RGB(c / 2, c / 2, 255 - c));

	// x = 10;
	// y = 120;
	// vga.setCursor(x + 10, y);
	// //draw an ellipse
	// vga.print("ellipse(x,y,rx,ry,c)");
	// vga.ellipse(x + 70, y + 20, 1 + r / 2, 8 - r / 4, vga.RGB(255 - c, c, 0));

	// x = 160;
	// y = 120;
	// vga.setCursor(x, y);
	// //draw a filled ellipse
	// vga.print("fillEllipse(x,y,rx,ry,c)");
	// vga.fillEllipse(x + 70, y + 20, 16 - r / 2, 1 + r / 4, vga.RGB(255 - c, c / 2, c / 2));

	// x = 15;
	// y = 160;
	// vga.setCursor(x + 35, y);
	// vga.print("print(text)");
	// //generate a string
	// char text[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	// for (int i = 0; i < 10; i++)
	// 	text[i] = 33 + (i + (c >> 2));
	// vga.setCursor(x + 37, y + 17);
	// //set the text and background color with opaque alpha (use RGBA to get a semi transparent back)
	// vga.setTextColor(vga.RGB(c, 255 - c, 255), vga.RGB(0, c / 2, 127 - c / 2));
	// vga.print(text);
	// //reset the text color. no second parameter makes the background transparent
	// vga.setTextColor(vga.RGB(255, 255, 255));

  
  // set wallpapers
  if(MODE == 0){
    if (wallpaper_index == 0){
  kendrick.draw(vga, (millis() / 150) % 1, 120, 80);
    }
    if (wallpaper_index == 1){
    lebron.draw(vga, (millis() / 150) % 1, 120, 80);
    }
    if (wallpaper_index == 2){
    cole.draw(vga, (millis() / 150) % 1, 120, 80);
    }
    if (wallpaper_index == 3){
    isagi.draw(vga, (millis() / 150) % 1, 120, 80);
    }
    if (wallpaper_index == 4){
    kenya.draw(vga, (millis() / 150) % 1, 30, 30);	
    }
  }

  if(MODE == 1){ 
  joystickX = analogRead(PlayerOneXJoystickPin);
  joystickY = analogRead(PlayerOneYJoystickPin);

  joystickTwoX = analogRead(PlayerTwoXJoystickPin);
  joystickTwoY = analogRead(PlayerTwoYJoystickPin);

  // vga.rect(25, 10, 175, 20, vga.RGB(0,255,0));

if (isGameOver){
  vga.setCursor(90, 76);
	if(isPlayerOneTheWinner) {
    vga.setTextColor(vga.RGB(c, 255 - c, 255), vga.RGB(0, c / 2, 127 - c / 2));
    vga.print("Red Won");
  }
  if(!isPlayerOneTheWinner) {
    vga.setTextColor(vga.RGB(c, 255 - c, 255), vga.RGB(0, c / 2, 127 - c / 2));
    vga.print("Green Won");
  }
}


 if (!isGameOver){
    if(joystickX > 3400){
        if(y > 10) {
      y = y - 1;
    }
  }

  if(joystickTwoX > 3400){
        if(b > 10) {
      b = b - 1;
    }
  }

  if(joystickX < 2900){
    if(y < 145) {
      y = y + 1;
    }
  }

   if(joystickTwoX < 2900){
    if(b < 145) {
      b = b + 1;
    }
  }

  if(joystickY > 3800){
    if(x < 195) {
      x = x + 1;
    }
  }

  if(joystickTwoY > 4000){
    if(a < 195) {
      a = a + 1;
    }
  }

  if(joystickY < 2400){
    if (x > 25){
      x = x - 1;
    }
  }

  if(joystickTwoY < 2400){
    if (a > 25){
      a = a - 1;
    }
  }
 }

	//set a single pixel. dotAdd add the colors. dotMix uses the alpha to mix the colors
	vga.dot(x   , y  , vga.RGB(255, 0, 0));

  vga.circle(x, y, 4, vga.RGB(255, 0, 0));

  vga.fillCircle(a, b, 3, vga.RGB(0, 255, 0));

  if(!pointOneScored){
    vga.fillCircle(pointOneX, pointOneY, 5, vga.RGB(0, 255, 0));
  }
  if(!pointTwoScored){
    vga.fillCircle(pointTwoX, pointTwoY, 5, vga.RGB(0, 255, 0));
  }
  if(!pointThreeScored){
    vga.fillCircle(pointThreeX, pointThreeY, 5, vga.RGB(0, 255, 0));
  }
  if(!pointFourScored){ 
    vga.fillCircle(pointFourX, pointFourY, 5, vga.RGB(0, 255, 0));
  }
  if(!pointFiveScored){ 
    vga.fillCircle(pointFiveX, pointFiveY, 5, vga.RGB(0, 255, 0));
  }
  if(!pointSixScored){ 
    vga.fillCircle(pointSixX, pointSixY, 5, vga.RGB(0, 255, 0));
  }

  if((x==a || x == a-1 || x == a + 1) && (y==b || y == b + 1 || y == b-1)){
    isGameOver = true;
    isPlayerOneTheWinner = true;
  }

  if( ((a>=pointOneX)&&(a<=pointOneX + 10)) && ((b>=pointOneY)&&(b<=pointOneY + 10))  ){
    pointOneScored = true;
  }
  if( ((a>=pointTwoX)&&(a<=pointTwoX + 10)) && ((b>=pointTwoY)&&(b<=pointTwoY + 10))  ){
    pointTwoScored = true;
  }
  if( ((a>=pointThreeX)&&(a<=pointThreeX + 10)) && ((b>=pointThreeY)&&(b<=pointThreeY + 10))  ){
    pointThreeScored = true;
  }
  if( ((a>=pointFourX)&&(a<=pointFourX + 10)) && ((b>=pointFourY)&&(b<=pointFourY + 10))  ){
    pointFourScored = true;
  }
  if( ((a>=pointFiveX)&&(a<=pointFiveX + 10)) && ((b>=pointFiveY)&&(b<=pointFiveY + 10))  ){
    pointFiveScored = true;
  }
  if( ((a>=pointSixX)&&(a<=pointSixX + 10)) && ((b>=pointSixY)&&(b<=pointSixY + 10))  ){
    pointSixScored = true;
  }
  

  if(pointOneScored && pointTwoScored && pointThreeScored && pointFourScored && pointFiveScored && pointSixScored){
    isGameOver = true;
  }

  }

  if (MODE == 2){
    attackAnimation.draw(vga, (millis() / 200) % 5, 65, 25);
    runAnimation.draw(vga, (millis() / 200) % 6, 145, 25);
    rollAnimation.draw(vga, (millis() / 200) % 4, 65, 65);
    dieAnimation.draw(vga, (millis() / 200) % 7, 145, 65);
    idleAnimation.draw(vga, (millis() / 200) % 4, 115, 95);
  }

	//show the rendering
	vga.show();
}