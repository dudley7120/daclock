void onlyShowTime2() {
  /*显示时间*/
  GetTime();
  if (hou  < 10) {
    displayNumbers2(0, 0, 10, color3);
    displayNumbers2(hou, 16,10, color3);
  } else {
    //displayNumbers(hou, 12, 40 + yy2, color);
    displayNumbers2(hou, 16, 10, color3);
  }
 // drawBit(30, 40 + yy2,maohao, 7, 14, color3);
  //drawHLine(32,40+yy2,30,color3);
  if (minu < 10) {
    displayNumbers2(0, 33, 10, color3);
    displayNumbers2(minu, 49, 10, color3);
  } else {
    //displayNumbers(minu, 48, 40 + yy2, color);
    displayNumbers2(minu, 49, 10, color3);
  }
  //产生光点
  
  for (int i = 0; i < starnum; i++) {
    star1_x = rand() % 63;
    star1_y = rand() % 63;
    colorl=rand() % 0xffff;
    dma_display->drawPixel(star1_x, star1_y, colorl);
  }
  
}
