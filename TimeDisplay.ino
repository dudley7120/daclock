char * showWeek(int v_week) { //显示日期
  //  uint32_t color2 = TFT_BLACK;
  switch (v_week) {
    case 1:
      color = 0xf800; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 52; yy2 = -14; yy3 = -14;
      return "一";
      break;
    case 2:
      color = 0xfb20; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 0; yy2 = 0; yy3 = 0;
      return "二";
      break;
    case 3:
      color = 0xffec; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 52; yy2 = -40; yy3 = 8;
      return "三";
      break;
    case 4:
      color = 0x7e0; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 52; yy2 = -14; yy3 = -14;
      return "四";
      break;
    case 5:
      color = 0x7ec; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 0; yy2 = 0; yy3 = 0;
      return "五";
      break;
    case 6:
      color = 0x1f; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 52; yy2 = -40; yy3 = 8;
      return "六";
      break;
    case 15:
      color = 0xf81f; //时间
      color2 = TFT_ORANGE; //日期
      color3 = 0xf000;//农历
      color4 = 0xfff0;//温度
      color5 = TFT_ORANGE;
      yy1 = 52; yy2 = -14; yy3 = -14;
      return "日";
      break;
  }
}
void refreshData(void * parameter) {
  //每天0点更新网络时间
   while(!WiFi.status() == WL_CONNECTED){
    autoConfig();
   }
  if (hou == 0 && minu == 0 && sec == 0) {
    setSyncProvider(getNtpTime);
    GetTime();
    year_ = String(year1);
    getNongli( year_, month_, day_);
  }
  dht11read();
  //
  month_ = String(month1);
  day_ = String(day1);

  setBrightness(sensor_Read());
  vTaskDelete(NULL);

}
void refreshTQ(void * parameter) {
      getWeather();
    vTaskDelete(NULL);
}
void showTime() {
  showWeek(week);
  GetTime();
  //更新天气
   if (minu % 10 == 0 && sec == 0) {
    xTaskCreate(
    refreshTQ,   /* Task function. */
    "refreshTQ", /* String with name of task. */
    10000,     /* Stack size in bytes. */
    NULL,      /* Parameter passed as input of the task */
    1,         /* Priority of the task. */
    NULL);     /* Task handle. */
  }
  //显示日期
  // displayNumbers2(strlen(jieri),0,0+yy1,color2);
   //drawHanziS(0, 0 + yy1, strlen(jieri), color2);

  if (strlen(jieri) < 1) {
    dma_display->setTextColor(color2);
    displayNumbers2(year1, 21, -2 + yy1, color2);
    dma_display->setCursor(27, 3 + yy1);
    dma_display->setTextSize(1);
    //dma_display->print(year1);
    dma_display->print(".");
    displayNumbers2(month1, 39, -2 + yy1, color2);
    // dma_display->print(month1);
    dma_display->setCursor(45, 3 + yy1);
    dma_display->print(".");
    displayNumbers2(day1, 56, -2 + yy1, color2);
    //显示节日
  } else {
    if (sec % 10 < 5) {
      drawHanziS(0, 0 + yy1, jieri, color3);
    } else {
      dma_display->setTextColor(color2);
      displayNumbers2(year1, 21, -2 + yy1, color2);
      dma_display->setCursor(27, 3 + yy1);
      dma_display->setTextSize(1);
      //dma_display->print(year1);
      dma_display->print(".");
      displayNumbers2(month1, 39, -2 + yy1, color2);
      // dma_display->print(month1);
      dma_display->setCursor(45, 3 + yy1);
      dma_display->print(".");
      displayNumbers2(day1, 56, -2 + yy1, color2);
    }
  }
  
  //dma_display->print(day1);
  if (sec % 10 < 3) {
    drawHanziS(20, 28 + yy3, china_month, color3);
    drawHanziS(41, 28 + yy3, china_day, color3);
  } else {
    if (strlen(jieqi) < 1) {
      drawHanziS(22, 28 + yy3, "星期", color3);
      drawHanziS(46, 28 + yy3, showWeek(week), color3);
    } else {
      if (sec % 10 >= 3 && sec % 10 < 7) {
        drawHanziS(22, 28 + yy3, "星期", color3);
        drawHanziS(46, 28 + yy3, showWeek(week), color3);
      } else {
        drawHanziS(22, 28 + yy3, jieqi, color3);
      }
    }
  }
  /*显示时间*/
  if (hou  < 10) {
    displayNumbers(0, 0, 40 + yy2, color);
    displayNumbers(hou, 12, 40 + yy2, color);
  } else {
    displayNumbers(hou, 12, 40 + yy2, color);
  }
  if (minu < 10) {
    displayNumbers(0, 36, 40 + yy2, color);
    displayNumbers(minu, 48, 40 + yy2, color);
  } else {
    displayNumbers(minu, 48, 40 + yy2, color);
  }


  disSmallNumbers(sec_ten, 28, 45 + yy2, color);
  disSmallNumbers(sec_one, 28, 52 + yy2, color);
  //十分钟刷新天气
  showTQ(wea_code, 0, 16 + yy3);
  //室外
  drawColorBit(22, 16 + yy3, tianqiwd, 5, 10);
  drawChars( 28, 21 + yy3,wea_temp1, color4);
    Serial.print("temp:");
  Serial.println(wea_temp1);
  //显示摄氏度
  if(atoi(wea_temp1)>-10)
  drawSmBit(36, 18 + yy3, wd, 3, 8, color4);
  //室内温度
  disSmallNumbers(temperature+temp_mod, 32, 15 + yy3, color5);
  drawSmBit(36, 12 + yy3, wd, 3, 8, color5);
  drawColorBit(42, 16 + yy3, tianqisd, 5, 10);
  disSmallNumbers(wea_hm, 52, 21 + yy3, color4);
  //显示H
  drawSmBit(56, 18 + yy3, sd, 3, 8, color4);
  //室内湿度
  disSmallNumbers(humidity+hum_mod, 52, 15 + yy3, color5);
  //显示H
  drawSmBit(56, 12 + yy3, sd, 3, 8, color5);

  // dma_display->print(china_year);
  //dma_display->print(china_month);
  //dma_display->print(china_day);


}
