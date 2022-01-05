
// Example sketch which shows how to display some patterns
// on a 64x64 LED matrix
//



//MatrixPanel_I2S_DMA dma_display;

uint16_t myBLACK = dma_display->color565(0, 0, 0);
uint16_t myWHITE = dma_display->color565(255, 255, 255);
uint16_t myRED = dma_display->color565(255, 0, 0);
uint16_t myGREEN = dma_display->color565(0, 255, 0);
uint16_t myBLUE = dma_display->color565(0, 0, 255);

void drawBit(int x, int y, const uint8_t *bitmap ,int width, int height, uint16_t color) 
{
  
  int32_t i, j, byteWidth = (width + 7) / 8;

  for (j = 0; j < height; j++) {
    for (i = 0; i < width; i++ ) {
      if (pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
        dma_display->drawPixel(x + i, y + j, color);
      }
    }
  }
}

void drawBit2(int x, int y, const uint8_t *bitmap ,int width, int height, uint16_t color) 
{
  
  int32_t i, j, byteWidth = (width + 7) / 8;

  for (j = 0; j < height; j++) {
    for (i = 0; i < width; i++ ) {
      if (pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
        dma_display->drawPixel(x + i, y + j, color);
      }
    }
  }
}
void drawSmBit(int x, int y, const uint8_t *bitmap ,int width, int height, uint16_t color){
   int32_t i, j;
  unsigned char a[3];
  unsigned char temp;
  for (j = 0; j < height; j++) {
        temp=bitmap[j];
        for(i=width;i>0;i--){
          a[i-1]=temp&0x01;
                temp>>=1;
             if (a[i-1]==1){
               dma_display->drawPixel(x + i, y + j, color);
        }
    }
  }
}

void drawColorBit(int x, int y, const uint16_t *bitmap ,int width, int height) 
{
  
  int32_t i, j, byteWidth = (width + 7) / 8;

  for (j = 0; j < height; j++) {
    for (i = 0; i < width; i++ ) {
           dma_display->drawPixel(x + i, y + j,bitmap[i+j*width]);
    }
  }
}
void drawColorBit2(int x, int y, const uint16_t *bitmap ,int width, int height) 
{
  
  int32_t i, j, byteWidth = (width + 7) / 8;

  for (j = 0; j < height; j++) {
    for (i = 0; i < width; i++ ) {
           dma_display->drawPixel(x + i, y + j,bitmap[i+j*width]);
        
    }
  }
}
void showTQ(int c, int x, int y)
{
  int hz_width;
  for (int k = 0; k < 61; k++) {
    if (tq20[k].Index == c)   {
      drawColorBit2(x, y, tq20[k].tq20_Id, 20 , 20);
    }
  }

}
void drawText(String words,int x,int y)
{
  dma_display->setCursor(x,y);   
  dma_display->setTextColor(dma_display->color565(255,0,255));
  dma_display->print(words);
}
void clearOLED(){
  dma_display->clearScreen();
}

void initOLED() {

  // Module configuration
  HUB75_I2S_CFG mxconfig(
    PANEL_RES_X,   // module width
    PANEL_RES_Y,   // module height
    PANEL_CHAIN    // Chain length
  );

  mxconfig.gpio.e = 32;
  mxconfig.clkphase = false;
  mxconfig.driver = HUB75_I2S_CFG::FM6126A;

  // Display Setup
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->begin();
  dma_display->setBrightness8(50); //0-255
  dma_display->clearScreen();
  dma_display->fillScreen(myBLACK);
}
void setBrightness(int dianya){
  dma_display->setBrightness8(10+8*dianya); //0-255
}
void displayNumber(int c, int x, int y, uint16_t color)
{
  int hz_width;
  for (int k = 0; k < 10; k++) {
    if (shuzi24[k].Index == c)   {
      drawBit2(x, y, shuzi24[k].hz24_Id, 12 , 24, color);
    }
  }

}
void disSmallNumber(int c, int x, int y, uint16_t color)
{
  int hz_width;
  for (int k = 0; k < 10; k++) {
    if (smsz[k].Index == c)   {
    //  Serial.println("run here");
      drawSmBit(x, y, smsz[k].smsz_Id, 3 , 5, color);
    }
  }
}
void disSmallNumbers(int numbers, int x, int y, uint16_t color)
{
  int count = 0;
  int temp = 0;
  char buffer[32];
  if (numbers == 0) {
    disSmallNumber(numbers, x, y, color);
  }
  while (numbers)
  {
    temp = numbers % 10;
    if (numbers < 10)
    {
      temp = numbers;
    }

    disSmallNumber(temp, x - (count * 4), y, color);
    numbers = numbers / 10;
    count++;  //count表示val是一个几位数
  }

}
void displayNumbers(int numbers, int x, int y, uint16_t color)
{
  int count = 0;
  int temp = 0;
  char buffer[32];
  if (numbers == 0) {
    displayNumber(numbers, x, y, color);
  }
  while (numbers)
  {
    temp = numbers % 10;
    if (numbers < 10)
    {
      temp = numbers;
    }

    displayNumber(temp, x - (count * 12), y, color);
    numbers = numbers / 10;
    count++;  //count表示val是一个几位数
  }

}
void disSmallChar(char c, int x, int y, uint16_t color)
{
  int hz_width;
  for (int k = 0; k < 11; k++) {
    if (smchar[k].Index == c)   {
      //Serial.println("run here!DrawChar");
      drawSmBit(x, y, smchar[k].smchar_Id, 3 , 5, color);
    }
  }
}
void drawChars(int32_t x, int32_t y, const char str[], uint32_t color) {
  int x0 = x;
  for (int i = 0; i < strlen(str); i++) {
   // Serial.print("当前char:");
   // Serial.println(str[i]);
    disSmallChar(str[i],x0, y, color);
    x0 += 4;
  }
}
void displayNumber2(int c, int x, int y, uint16_t color)
{
  int hz_width;
  for (int k = 0; k < 10; k++) {
    if (shuzi14[k].Index == c)   {
      drawBit(x, y, shuzi14[k].hz14_Id, 8 , 14, color);
    }
  }

}
void displayNumbers2(int numbers, int x, int y, uint16_t color)
{
  int count = 0;
  int temp = 0;
  char buffer[32];
  if (numbers == 0) {
    displayNumber(numbers, x, y, color);
  }
  while (numbers)
  {
    temp = numbers % 10;
    if (numbers < 10)
    {
      temp = numbers;
    }

    displayNumber2(temp, x - (count * 7), y, color);
    numbers = numbers / 10;
    count++;  //count表示val是一个几位数
  }

}
void drawHanzi(int32_t x, int32_t y, const char *c, uint32_t color) {  //显示单一汉字
  int hz_width;

  for (int k = 0; k < 101; k++) {//k小于中文数组大小
    if (hanzi12[k].Index[0] == c[0] && hanzi12[k].Index[1] == c[1] && hanzi12[k].Index[2] == c[2])   {
      //Serial.println("equal!");
      hz_width = atoi(hanzi12[k].hz_width);
      drawBit(x, y, hanzi12[k].hz12_Id, 12 , 12, color);
     // tft.drawBitmap(x, y, hanzi12[k].hz16_Id, hz_width ,12, color);
    }
  }
}
void drawHanziS(int32_t x, int32_t y, const char str[], uint32_t color) {
  int x0 = x;
  char b[3];
  for (int i = 0; i < strlen(str); i = i + 3) {
    b[0] = str[i];
    b[1] = str[i + 1];
    b[2] = str[i + 2];
    drawHanzi(x0, y, b, color);
    x0 += 11;
  }
}
