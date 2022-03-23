void onlyShowTime() {
  /*显示时间*/
  GetTime();
  if (hou  < 10) {
    dis30Numbers(0,-2,2, color3);
    dis30Numbers(hou, 28,2, color3);
  } else {
    //displayNumbers(hou, 12, 40 + yy2, color);
    dis30Numbers(hou, 28,2, color3);
  }
  drawBit(48,-1, sz30_maohao,32, 63, color3);
  if (minu < 10) {
    dis30Numbers(0,70 ,2, color3);
    dis30Numbers(minu, 100,2, color3);
  } else {
    //displayNumbers(minu, 48, 40 + yy2, color);
    dis30Numbers(minu, 100,2, color3);
  }
  //产生光点
  
 //显示光点
  if (sec % 2 == 0&&isGeneralStar) {
    for (int i = 0; i < starnum; i++) {
      star_x[i] = rand() % 127;
      star_y[i] = rand() % 63;
      star_color[i] = rand() % 0xffff;
    }
    isGeneralStar=!isGeneralStar;
  }
  if(sec%2!=0 && isGeneralStar==false){
    isGeneralStar=true;
  }
  for (int i = 0; i < starnum; i++) {
    //dma_display->drawPixel(star_x[i], star_y[i], star_color[i]);
    fillTab(star_x[i]+1,star_y[i],star_color[i]);
    fillTab(star_x[i],star_y[i],star_color[i]);
    fillTab(star_x[i],star_y[i]+1,star_color[i]);
    fillTab(star_x[i]+1,star_y[i]+1,star_color[i]);
  }
  
}
