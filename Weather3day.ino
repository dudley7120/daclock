char * right(char *dst,char *src, int n)
{
    char *p = src;
    char *q = dst;
    int len = strlen(src);
    if(n>len) n = len;
    p += (len-n);   /*从右边第n个字符开始*/
    while(*(q++) = *(p++));
    return dst;
}
//***send http 获取天气
void show3dayWeather() {
  //第一行
  showTQ(wea_code_day1, 0+64, 0);
  drawChars(19+64,3,right(temp_day_date,day1_date,5), color4);
  //温度
  if (atoi(tem_day1_min) < -9) {
    drawChars(19+64, 10, tem_day1_min, color5);
    }else {
      drawChars(19+64, 10, tem_day1_min, color5);
      drawSmBit(27+64, 7, wd, 3, 8, color4);
    }
    if (atoi(tem_day1_max) < -9) {
      drawChars(33+64, 10, tem_day1_max, color5);
    } else {
      drawChars(33+64, 10, tem_day1_max, color5);
      drawSmBit(41+64, 7, wd, 3, 8, color4);
    }
        showTQ(wea_code_night1, 44+64, 0);
        
   // drawLine(0+64,21, 64, sec_one); //分隔线


    //第二行
    showTQ(wea_code_day2, 0+64,   22);
    drawChars(19+64, 3 + 22, right(temp_day_date,day2_date,5), color4);
    //温度
    if (atoi(tem_day2_min) < -9) {
      drawChars(19+64, 10 + 22, tem_day2_min, color5);
    } else {
      drawChars(19+64, 10 + 22, tem_day2_min, color5);
      drawSmBit(27+64, 7 + 22, wd, 3, 8, color4);
    }
    if (atoi(tem_day2_max) < -9) {
      drawChars(33+64, 10 + 22, tem_day2_max, color5);
    } else {
      drawChars(33+64, 10 + 22, tem_day2_max, color5);
      drawSmBit(41+64, 7 + 22, wd, 3, 8, color4);
    }
    showTQ(wea_code_night2, 44+64,  22);
    
    //第三行
    showTQ(wea_code_day3, 0+64,  22 + 21);
    drawChars(19+64, 3 + 22 + 21, right(temp_day_date,day3_date,5), color4);
    if (atoi(tem_day3_min)< -9) {
      drawChars(19+64, 10 + 22 + 21, tem_day3_min, color5);
    } else {
      drawChars(19+64, 10 + 22 + 21, tem_day3_min, color5);
      drawSmBit(27+64, 7 + 22 + 21, wd, 3, 8, color4);
    }
    if (atoi(tem_day3_max) < -9) {
      drawChars(33+64, 10 + 22 + 21,tem_day3_max, color5);
    } else {
      drawChars(33+64, 10 + 22 + 21,tem_day3_max, color5);
      drawSmBit(41+64, 7 + 22 + 21, wd, 3, 8, color4);
    }
    //disSmallNumbers(12,26, 16+22+21, color5);
    //disSmallNumbers(50, 47,16+22+21, color5);
    showTQ(wea_code_night3, 44+64,  22 + 21);
    
  //  drawHLine(19, 0, 64, sec_one); //左竖线
  //  drawHLine(46, 0, 64, sec_one); //左竖线

  }
  
