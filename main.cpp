#include <LovyanGFXSetup.hpp>
#include <zombiePictures.hpp>
static int32_t touchX, touchY;
static int32_t touchXAdjusted, touchYAdjusted;
static LGFX lcd;
static LGFX_Sprite canvas;
static LGFX_Sprite logo;
static LGFX_Sprite zombie;
int lights;
int x, y;
int failcount = 0;  //not yet used, but may be in the future for a failed-to-touch counter to determine when the game is over, rather than the only
                    //end condition being the player winning.
unsigned long currentMillis;
unsigned long startTimer;
int timeLeftToTouch = 2000;
bool touched = false;
void zombieWalking(int, int);
void zombieDeathAnimation(int, int);
void displayZombieImage1(int, int);
void displayZombieImage2(int, int);
void subtractLightsIfTooSlow();

extern const unsigned short logoScreen[];
extern const unsigned short zombieDeathImage1[]; // 98x108   pixels
extern const unsigned short zombieDeathImage2[]; // 85x100   pixels
extern const unsigned short zombieDeathImage3[]; // 84x93    pixels
extern const unsigned short grassImage[];        // 160x120  pixels
extern const unsigned short zombieImage2[];      // 91x118   pixels
extern const unsigned short zombieImage1[];      // 82x110   pixels pixels

float zoom = 0.1;
bool exitStartScreen = false;
void setup(void)
{
  Serial.begin(115200);
  lcd.init();
  if (lcd.width() < lcd.height())
  {
    lcd.setRotation(lcd.getRotation() ^ 1);
  }
  canvas.createSprite(200, 150);
  logo.createSprite(200, 150);
  // logo.setColorDepth(8);
  // canvas.setColorDepth(8);
  uint16_t calData[8] = {3846, 356, 3841, 3890, 196, 472, 266, 3861};
  lcd.setTouchCalibrate(calData);
  logo.setSwapBytes(true);
  canvas.setSwapBytes(true);
  zombie.setSwapBytes(true);
  lcd.startWrite();
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(32, OUTPUT);
}

void loop(void)
{
  while (zoom < 1.5 && lights == 0) // Display the logo, it zooms to fill screen
  {
    canvas.fillSprite(TFT_BLACK);
    logo.pushImage(0, 0, 200, 150, logoScreen);
    zoom += 0.05;
    logo.pushSprite(&canvas, 0, 0);
    canvas.pushRotateZoomWithAA(&lcd, 150, 120, 0, zoom, zoom);
  }
  // Nothing happens until the screen is touched
  while (exitStartScreen == false)
  {
    // When the screen is touched, the logo is deleted and the canvas is filled with black
    lcd.getTouch(&touchX, &touchY);
    if (touchX != 0 && touchY != 0)
    {
      // logo.fillSprite(TFT_BLACK);
      logo.clear();
      logo.pushSprite(&canvas, 0, 0);
      canvas.pushRotateZoomWithAA(&lcd, 150, 120, 0, zoom, zoom);
      logo.deleteSprite();
      exitStartScreen = true;
      touchX = -30;
      touchY = -30;
    }
  }
  zoom = 0.1; // This line is no longer used, but I'm keeping it here just in case.
  x = random(0, 140);
  y = random(0, 80);
  touched = false;
  // startTimer = millis();
  while (touched == false)
  {
    subtractLightsIfTooSlow(); // If the player takes too long to touch the zombie, they lose a light.
    currentMillis = millis();  // This is currently only used for the zombie walking animation.
    displayZombieImage1(x, y);
    // Erase previous touch location.  If the following two lines are removed and the zombie teleports
    // to a location near the previous, it will count as another touch because the previous adjusted teleportation coordinates are being stored.
    touchX = -30;
    touchY = -30;
    while (millis() - currentMillis <= 150)
    {
      lcd.getTouch(&touchX, &touchY);
      // The screen size is 320x240.  However the teleportation locations work out to be 160x120, due to the zoom.
      // if the screen is touched, the touch location is adjusted to match the zoomed in screen, otherwise the zombie will appear off-screen.
      touchXAdjusted = touchX / 2; 

      // check if sprite is touched and adjust sprite teleportation speed and lights lit accordingly.
      if (touchXAdjusted >= x && touchXAdjusted <= x + 20 && touchYAdjusted >= y && touchYAdjusted <= y + 40)
      {
        zombieDeathAnimation(x, y);
        touched = true;
        lights++;
        timeLeftToTouch -= 250;
        if (timeLeftToTouch < 300)
        {
          timeLeftToTouch = 300;
        }
        break;
      }
    }

    displayZombieImage2(x, y);
    // Erase previous touch location.  If the following two lines are removed and the zombie teleports
    touchX = -30;
    touchY = -30;
    while (millis() - currentMillis <= 300)
    {
      lcd.getTouch(&touchX, &touchY);
      touchXAdjusted = touchX / 2;
      touchYAdjusted = touchY / 2;
      // check if sprite is touched and adjust sprite teleportation speed and lights lit accordingly.
      if (touchXAdjusted >= x && touchXAdjusted <= x + 20 && touchYAdjusted >= y && touchYAdjusted <= y + 40)
      {
        zombieDeathAnimation(x, y);
        touched = true;
        lights++;
        timeLeftToTouch -= 250;
        if (timeLeftToTouch < 300)
        {
          timeLeftToTouch = 300;
        }
        break;
      }
    }
  }
  // The number of lights lit cooresponds successful or unsuccessful touches.
  if (lights >= 1)
  {
    digitalWrite(12, HIGH);
  }
  else
  {
    digitalWrite(12, LOW);
  }
  if (lights >= 2)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
  if (lights >= 3)
  {
    digitalWrite(14, HIGH);
  }
  else
  {
    digitalWrite(14, LOW);
  }
  if (lights >= 4)
  {
    digitalWrite(27, HIGH);
  }
  else
  {
    digitalWrite(27, LOW);
  }
  if (lights >= 5)
  {
    digitalWrite(26, HIGH);
  }
  else
  {
    digitalWrite(26, LOW);
  }
  if (lights >= 6)
  {
    digitalWrite(25, HIGH);
  }
  else
  {
    digitalWrite(25, LOW);
  }
  if (lights >= 7)
  {
    digitalWrite(33, HIGH);
  }
  else
  {
    digitalWrite(33, LOW);
  }
  if (lights >= 8)
  {
    digitalWrite(32, HIGH);
  }
  else
  {
    digitalWrite(32, LOW);
  }
  if (lights >= 9)
  {
    zombieDeathAnimation(x, y);
    for (int i = 0; i < 20; i++)
    {
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      digitalWrite(14, LOW);
      digitalWrite(27, LOW);
      digitalWrite(26, LOW);
      digitalWrite(25, LOW);
      digitalWrite(33, LOW);
      digitalWrite(32, LOW);
      delay(50);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(14, HIGH);
      digitalWrite(27, HIGH);
      digitalWrite(26, HIGH);
      digitalWrite(25, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(32, HIGH);
      delay(50);
    }
    //Because the game is over, the screen is reset to the start screen.
    ESP.restart();

    // The following code is for testing purposes only.  It is never executed due to the ESP.restart() above.
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    digitalWrite(14, LOW);
    digitalWrite(27, LOW);
    digitalWrite(26, LOW);
    digitalWrite(25, LOW);
    digitalWrite(33, LOW);
    digitalWrite(32, LOW);
    lights = 0; // Number of lights lit
    zoom = 0.1;
    exitStartScreen = false;
    lcd.fillScreen(TFT_BLACK);
    while (zoom < 1.5) // Display the logo, it zooms to fill screen
    {
      logo.createSprite(200, 150);
      canvas.fillSprite(TFT_BLACK);
      logo.pushImage(0, 0, 200, 150, logoScreen);
      zoom += 0.05;
      logo.pushSprite(&canvas, 0, 0);
      canvas.pushRotateZoomWithAA(&lcd, 150, 120, 0, zoom, zoom);
    }
    // Nothing happens until the screen is touched
    while (exitStartScreen == false)
    {
      touchX = -30;
      touchY = -30;
      // When the screen is touched, the logo is deleted and the canvas is filled with black
      lcd.getTouch(&touchX, &touchY);
      if (touchX != -30 && touchY != -30)
      {
        // logo.fillSprite(TFT_BLACK);
        logo.clear();
        logo.pushSprite(&canvas, 0, 0);
        canvas.pushRotateZoomWithAA(&lcd, 150, 120, 0, zoom, zoom);
        logo.deleteSprite();
        exitStartScreen = true;
        touchX = -30;
        touchY = -30;
      }
    }
  }
  startTimer = millis();
  // zombieDeathAnimation(randx, randy);
}
//Display the zombie walking animation at x, y coordinates of the zoomed canvas sprite.
void displayZombieImage2(int x, int y)
{
  zombie.clear();
  zombie.deleteSprite();
  zombie.createSprite(91, 118);
  canvas.pushImage(0, 0, 160, 120, grassImage);
  zombie.pushImage(0, 0, 91, 118, zombieImage2);
  zombie.pushRotateZoom(&canvas, x + 10, y + 20, 0, .4, .4, TFT_BLACK);
  canvas.pushRotateZoom(&lcd, 200, 150, 0, 2, 2);
}
//Display the zombie walking animation at x, y coordinates of the zoomed canvas sprite.
void displayZombieImage1(int x, int y)
{
  zombie.clear();
  zombie.deleteSprite();
  zombie.createSprite(82, 110);
  canvas.pushImage(0, 0, 160, 120, grassImage);
  zombie.pushImage(0, 0, 82, 110, zombieImage1);
  zombie.pushRotateZoom(&canvas, x + 10, y + 20, 0, .4, .4, TFT_BLACK);
  canvas.pushRotateZoom(&lcd, 200, 150, 0, 2, 2);
}
//Display the zombie death animation at x, y coordinates of the zoomed canvas sprite.
void zombieDeathAnimation(int x, int y)
{
  zombie.clear();
  zombie.deleteSprite();
  zombie.createSprite(98, 108);
  canvas.pushImage(0, 0, 160, 120, grassImage);
  zombie.pushImage(0, 0, 98, 108, zombieDeathImage1);
  zombie.pushRotateZoom(&canvas, x + 10, y + 20, 0, .4, .4, TFT_BLACK);
  canvas.pushRotateZoom(&lcd, 200, 150, 0, 2, 2);
  delay(100);
  zombie.clear();
  zombie.deleteSprite();
  zombie.createSprite(85, 100);
  canvas.pushImage(0, 0, 160, 120, grassImage);
  zombie.pushImage(0, 0, 85, 100, zombieDeathImage2);
  zombie.pushRotateZoom(&canvas, x + 10, y + 20, 0, .4, .4, TFT_BLACK);
  canvas.pushRotateZoom(&lcd, 200, 150, 0, 2, 2);
  delay(100);
  zombie.clear();
  zombie.deleteSprite();
  zombie.createSprite(84, 93);
  canvas.pushImage(0, 0, 160, 120, grassImage);
  zombie.pushImage(0, 0, 84, 93, zombieDeathImage3);
  zombie.pushRotateZoom(&canvas, x + 10, y + 20, 0, .4, .4, TFT_BLACK);
  canvas.pushRotateZoom(&lcd, 200, 150, 0, 2, 2);
  delay(100);
}
// If the player takes too long to touch the zombie, they lose a light and teleport to a new location.
void subtractLightsIfTooSlow()
{
  if (millis() - startTimer >= timeLeftToTouch)
  {
    x = random(0, 140);
    y = random(0, 80);
    startTimer = millis();
    lights--;
    timeLeftToTouch += 250;
    if (timeLeftToTouch > 2000)
    {
      timeLeftToTouch = 2000;
    }
    if (lights < 0)
    {
      lights = 0;
    }
    if (lights >= 1)
    {
      digitalWrite(12, HIGH);
    }
    else
    {
      digitalWrite(12, LOW);
    }
    if (lights >= 2)
    {
      digitalWrite(13, HIGH);
    }
    else
    {
      digitalWrite(13, LOW);
    }
    if (lights >= 3)
    {
      digitalWrite(14, HIGH);
    }
    else
    {
      digitalWrite(14, LOW);
    }
    if (lights >= 4)
    {
      digitalWrite(27, HIGH);
    }
    else
    {
      digitalWrite(27, LOW);
    }
    if (lights >= 5)
    {
      digitalWrite(26, HIGH);
    }
    else
    {
      digitalWrite(26, LOW);
    }
    if (lights >= 6)
    {
      digitalWrite(25, HIGH);
    }
    else
    {
      digitalWrite(25, LOW);
    }
    if (lights >= 7)
    {
      digitalWrite(33, HIGH);
    }
    else
    {
      digitalWrite(33, LOW);
    }
    if (lights >= 8)
    {
      digitalWrite(32, HIGH);
    }
    else
    {
      digitalWrite(32, LOW);
    }
  }
}