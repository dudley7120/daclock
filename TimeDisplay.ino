char * showWeek(int v_week) { //显示日期
  //  uint32_t color2 = TFT_BLACK;
  switch (v_week) {
    case 1:
      color = 0xf800; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 53; yy2 = -14; yy3 = -14;
      return "一";
    case 2:
      color = 0xfb20; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 2; yy2 = 0; yy3 = 0;
      return "二";
    case 3:
      color = 0xffec; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 52; yy2 = -42; yy3 = 8;
      return "三";
    case 4:
      color = 0x7e0; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 52; yy2 = -14; yy3 = -14;
      return "四";
    case 5:
      color = 0x7ec; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 2; yy2 = 0; yy3 = 0;
      return "五";
    case 6:
      color = TFT_SKYBLUE; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 52; yy2 = -42; yy3 = 8;
      return "六";
    case 15:
      color = 0xf81f; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 52; yy2 = -14; yy3 = -14;
      return "日";
  }
}
void nightMode() {
  color = 0x8800; //时间
  color2 = 0x8800; //日期
  color3 = 0x8800;//农历
  color4 = 0x8800;//温度
  color5 = 0x8800;
  isnight = true;
}
void refreshData(void * parameter) {
  //每天0点更新网络时间
  if ( minu == 0 && sec == 0) {
    setSyncProvider(getNtpTime);
    GetTime();
    year_ = String(year1);
    month_ = String(month1);
    day_ = String(day1);
    getNongli( year_, month_, day_);
  }
  //

  vTaskDelete(NULL);

}
void housound(void * parameter) {
  common_play();
  vTaskDelete(NULL);
}
void refreshTQ(void * parameter) {
    getWeather();
    get3DayWeather();
    getBirth();
  vTaskDelete(NULL);
}
void showJieri(void * parameter) {
  if (sec % 20 < 15) {
    drawHanziS(0+scroll_x, -1 + yy1, jieri.c_str(), color3);
    if(scroll_x>-60&&jieri.length()>15){
      scroll_x-=4;
    }else{
      scroll_x=0;
    }
    //  color3=1;
  } else {
    scroll_x=0;
    displayNumbers2(year1, 21, -2 + yy1, color2);
    //dma_display->setCursor(27, 3 + yy1);
    //dma_display->setTextSize(1);
    //dma_display->print(year1);
    //dma_display->print(".");
    drawBit(28, yy1 - 2, dot, 7, 14, color2);
    if (month1 < 10) {
      displayNumbers2(0, 32, -2 + yy1, color2);
    }
    displayNumbers2(month1, 39, -2 + yy1, color2);
    //dma_display->setCursor(45, 3 + yy1);
    //dma_display->print(".");
    drawBit(46,  yy1 - 2, dot, 7, 14, color2);
    if (day1 < 10) {
      displayNumbers2(0, 49, -2 + yy1, color2);
    }
    displayNumbers2(day1, 56, -2 + yy1, color2);
  }
  vTaskDelete(NULL);
}
void showTime() {
  const char* v_week = showWeek(week);
  if (minu == 0 && sec == 0 && soundon && hou < 21 && hou > 7) {
    xTaskCreate(
      housound,   /* Task function. */
      "housound", /* String with name of task. */
      10000,     /* Stack size in bytes. */
      NULL,      /* Parameter passed as input of the task */
      1,         /* Priority of the task. */
      NULL);     /* Task handle. */
  }
  Serial.print("节日长度：");
  Serial.println(jieri.length());
  //显示日期
  // displayNumbers2(strlen(jieri),0,0+yy1,color2);
  //drawHanziS(0, 0 + yy1, strlen(jieri), color2);
  //显示节日和日期
  if (jieri.length() < 1) {
    dma_display->setTextColor(color2);
    displayNumbers2(year1, 21, -2 + yy1, color2);
    // dma_display->setCursor(27, 3 + yy1);
    // dma_display->setTextSize(1);
    //dma_display->print(year1);
    //  dma_display->print(".");
    // drawBit(29, 3 + yy1, dot, 7, 14, color2);
    drawBit(28, yy1 - 2, dot, 7, 14, color2);
    if (month1 < 10) {
      displayNumbers2(0, 32, -2 + yy1, color2);
    }
    displayNumbers2(month1, 39, -2 + yy1, color2);
    // dma_display->print(month1);
    //dma_display->setCursor(45, 3 + yy1);
    //dma_display->print(".");
    drawBit(46, yy1 - 2, dot, 7, 14, color2);
    if (day1 < 10) {
      displayNumbers2(0, 49, -2 + yy1, color2);
    }
    displayNumbers2(day1, 56, -2 + yy1, color2);
    //显示节日
  } else {

    xTaskCreate(
      showJieri,   /* Task function. */
      "showJieri", /* String with name of task. */
      10000,     /* Stack size in bytes. */
      NULL,      /* Parameter passed as input of the task */
      1,         /* Priority of the task. */
      NULL);     /* Task handle. */
  }


  //dma_display->print(day1);
  if (sec % 10 < 3) {
    drawHanziS(20, 29 + yy3, china_month, color3);
    drawHanziS(41, 29 + yy3, china_day, color3);
  } else {
    if (strlen(jieqi) < 1) {
      drawHanziS(22, 29 + yy3, "星期", color3);
      drawHanziS(46, 29 + yy3, v_week, color3);
    } else {
      if (sec % 10 >= 3 && sec % 10 < 7) {
        drawHanziS(22, 29 + yy3, "星期", color3);
        drawHanziS(46, 29 + yy3, v_week, color3);
      } else {
        drawHanziS(22, 29 + yy3, jieqi, color3);
      }
    }
  }
  /*显示时间*/
  if (hou  < 10) {
    displayNumbers(0, 0, 41 + yy2, color);
    displayNumbers(hou, 12, 41 + yy2, color);
  } else {
    displayNumbers(hou, 12, 41 + yy2, color);
  }
  if (minu < 10) {
    displayNumbers(0, 36, 41 + yy2, color);
    displayNumbers(minu, 48, 41 + yy2, color);
  } else {
    displayNumbers(minu, 48, 41 + yy2, color);
  }
  disSmallNumbers(sec_ten, 28, 47 + yy2, color);
  disSmallNumbers(sec_one, 28, 54 + yy2, color);
  if (caidaion) {
    drawLine(0, 0, 64, sec_one); //上线
    drawLine(0, 42 + yy2, 64, sec_one); //分隔线
    drawHLine(0, 0, 64, sec_one); //左竖线
    drawLine(0, 63 + yy2, 64, sec_one); //分隔线
    drawHLine(63, 0, 64, sec_one); //右竖线
    drawLine(0, 63, 64, sec_one); //下线
  }

  //十分钟刷新天气
  showTQ(wea_code, 0, 17 + yy3);
  //室外
  drawColorBit(22, 17 + yy3, tianqiwd, 5, 10);
  drawChars( 28, 22 + yy3, wea_temp1, color4);
  Serial.print("temp:");
  Serial.println(wea_temp1);
  //显示摄氏度
  if (atoi(wea_temp1) > -10)
    drawSmBit(36, 19 + yy3, wd, 3, 8, color4);
  //室内温度
  disSmallNumbers(temperature + temp_mod, 32, 16 + yy3, color5);
  drawSmBit(36, 13 + yy3, wd, 3, 8, color5);
  drawColorBit(42, 17 + yy3, tianqisd, 5, 10);
  disSmallNumbers(wea_hm, 52, 22 + yy3, color4);
  //显示H
  drawSmBit(56, 19 + yy3, sd, 3, 8, color4);
  //室内湿度
  disSmallNumbers(humidity + hum_mod, 52, 16 + yy3, color5);
  //显示H
  drawSmBit(56, 13 + yy3, sd, 3, 8, color5);
}
void showTigger() { 
  if(sec_ten%2==0 && !isnight){
  //显示老虎
  showlaohu();
 if(soundon){
    drawBit(65, 52, laba, 12, 12, TFT_GREEN);
  }else{
    drawBit(65, 52, laba, 12, 12, TFT_DARKGREY);
  }
  //显示wifi图标
    drawBit(116, 52, wifi, 12, 12, TFT_GREEN);
  //显示光点
  if (sec % 2 == 0 && isGeneralStar) {
    for (int i = 0; i < starnum; i++) {
      star_x[i] = 64 + rand() % 63;
      star_y[i] = rand() % 63;
      star_color[i] = rand() % 0xffff;
    }
    isGeneralStar = !isGeneralStar;
  }
  if (sec % 2 != 0 && isGeneralStar == false) {
    isGeneralStar = true;
  }
  for (int i = 0; i < starnum; i++) {
    //dma_display->drawPixel(star_x[i], star_y[i], star_color[i]);
    fillTab(star_x[i], star_y[i], star_color[i]);
    fillTab(star_x[i] + 1, star_y[i], star_color[i]);
    fillTab(star_x[i] - 1, star_y[i], star_color[i]);
    //  fillTab(star_x[i]+2,star_y[i],star_color[i]);
    //  fillTab(star_x[i]-2,star_y[i],star_color[i]);
    fillTab(star_x[i], star_y[i] + 1, star_color[i]);
    fillTab(star_x[i], star_y[i] - 1, star_color[i]);
    //  fillTab(star_x[i],star_y[i]+2,star_color[i]);
    //  fillTab(star_x[i],star_y[i]-2,star_color[i]);
  }
  
  }else{
    if(gif_i>17){gif_i=0;}
     show3dayWeather();
  }
}
