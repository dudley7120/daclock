void onlyShowTime2() {
  /*显示时间*/
  GetTime();
  if (hou  < 10) {
    displayNumbers2(0, 8+screen_num, 10+yy1, color3);
    displayNumbers2(hou, 16+screen_num,10+yy1, color3);
  } else {
    //displayNumbers(hou, 12, 40 + yy2, color);
    displayNumbers2(hou, 16+screen_num, 10+yy1, color3);
  }
  drawBit(24+screen_num,10 + yy1,maohao, 7, 14, color3);
  //drawHLine(32,40+yy2,30,color3);
  if (minu < 10) {
    displayNumbers2(0, 29+screen_num, 10+yy1, color3);
    displayNumbers2(minu, 37+screen_num, 10+yy1, color3);
  } else {
    //displayNumbers(minu, 48, 40 + yy2, color);
    displayNumbers2(minu, 37+screen_num, 10+yy1, color3);
  }
}
