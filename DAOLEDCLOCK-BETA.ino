#include <WiFi.h>
#include <TimeLib.h>
#include "time.h"
#include <HTTPClient.h>
#include <WiFiUdp.h>
#define ARDUINOJSON_USE_LONG_LONG 1
#include <ArduinoJson.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <SimpleDHT.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <EEPROM.h> 
#include <Update.h>
#include "MyFont.h"
//AP模式IP
IPAddress apIP(192,168,4,1);
const char* AP_SSID  = "DACLOCK" ;   //设置AP热点名称
String wifi_ssid = "";                    
String wifi_pass = "";     

//定义根目录首页网页HTML源代码
#define ROOT_HTML  "<!DOCTYPE html><html><head><title>DaClock ConnectWiFi</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head><style type=\"text/css\">.input{display: block; margin-top: 10px;}.input span{width: 100px; float: left; float: left; height: 36px; line-height: 36px;}.input input{height: 30px;width: 200px;}.btn{width: 120px; height: 35px; background-color: #000000; border:0px; color:#ffffff; margin-top:15px; margin-left:100px;}</style><body bgcolor=lightyellow><h1>DaClock网络设置</h1><form method=\"POST\" action=\"configwifi\"><label class=\"input\"><span>WiFi SSID</span><input type=\"text\" name=\"ssid\" value=\"\"></label><label class=\"input\"><span>WiFi PASS</span><input type=\"text\"  name=\"pass\"></label><input class=\"btn\" type=\"submit\" name=\"submit\" value=\"提交\"> <p><span> 附近的 wifi:</P></form>"
//定义成功页面HTML源代码
#define SUCCESS_HTML  "<html><body><font size=\"10\">连接成功！<br />请手动关闭当前页面.</font></body></html>"
String scanNetworksID = "";                //用于储存扫描到的WiFi ID

int pinDHT11 = 21; //IO2
SimpleDHT11 dht11(pinDHT11);
MatrixPanel_I2S_DMA *dma_display = nullptr;
WiFiUDP udp;
const char* ntpServerName = "time1.aliyun.com";
IPAddress timeServerIP;
const int timeZone = 8;
int hou, minu, sec, year1, month1, day1, week,sec_ten,sec_one;
char wea_temp1[]="";
char * wea_temp2;
int wea_code;
int yy1=0,yy2=0,yy3=0;//实现钟面不同布局
int i=0;//日期横向滚动
bool isFirst=true;
char * china_year;
char *china_month;
char *china_day;
char* wind_fx;
char * jieri;
char * jieqi;
int wind_level;
int  wea_hm;
String year_, month_, day_;
byte temperature = 0;
byte humidity = 0;//dht11读取
    uint16_t color = 0xf0b0; //时间
  uint16_t color2 = 0x780F; //日期
    uint16_t color3 = 0xf000;//农历
    uint16_t color4 = 0xfff0;//温度
    uint16_t color5 = 0xFDA0;
WebServer server(80);
const char* host = "esp32";
const char*username="admin";
const char*userpass="000000";
/*
 * Server Index Page
 */

int temp_mod=-3;   //温度微调参数
int hum_mod=0;    //湿度微调参数
String zx_key="";
String city="";
int len_city;
int len_key;

const char* serverIndex = 
"<!DOCTYPE HTML><html><head>"
"<script src='https://cdn.staticfile.org/jquery/1.10.2/jquery.min.js'></script>"
"<title>DAOLEDClockV1.0</title><meta name='viewport' content='width=device-width, initial-scale=1' charset='UTF-8'>"
"<script type='text/javascript'>function change(){var value =document.getElementById('temp').value;console.log(value);document.getElementById('value').innerHTML = value;};"
"function change2(){var value =document.getElementById('hum').value;console.log(value);document.getElementById('value2').innerHTML = value;};"
"function submit() {"     
"  $.ajax({ type: 'GET', url: '/get', data: { temp: $('#temp').val(), hum: $('#hum').val() ,chengshi:$('#chengshi').val(),tianqikey:$('#tianqikey').val()},"
"  dataType: 'html',"
"  success: function(result)"
"  {   alert('更新成功!')} }); };"  
"function submit2() {      $.ajax({ type: 'GET', url: '/get', data: {reboot:1 }, dataType: 'html', success: function(result) {   alert('已重启！');}     });   };"
"</script></head>"
"<body bgcolor=lightyellow>"
"<table border='1' bgcolor=lightblue><tr><td border='0' colspan='4'  align=center><h1>DaClock设置</h1></td>"
"<tr><td><form method='POST' action='configwifi'><label class='input'><span>WiFi SSID</span></td><td><input type='text' name='ssid' value=''></label></td></tr>"
"<tr><td><label><span>WiFi PASS</span></td><td><input type='text'  name='pass'></label></td></tr><tr><td><input  type='submit' name='submit' value='Submie'></td></tr></form>"
"<tr><td width=150>  温度修正:&nbsp;</td><td width=170 align=right><input id='temp' type='range' min='-10' max='10' value='-3' oninput='change()'/><span   id='value'>-3</span></td></tr>"
"<tr><td>  湿度修正:</td><td width=50 align=right><input id='hum' type='range' min='-10' max='10' value='0'   oninput='change2()'/><span id='value2'>0</span></td></tr>"
"<tr><td>城市：</td><td><input id='chengshi' type='text' value='beijing'/></td></tr>"
"<tr><td>天气key:</td><td><input id='tianqikey' type='text' value=''></td></tr>"
"<tr><td  align=center><input type='submit' value='保存设置' onclick='submit()'></td>"
"<td><input type='submit' value='重启时钟'/ onclick='submit2()'></input></td></tr>"
"<tr><td>更新固件：</td>"
"<td><form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
   "<input type='file' name='update'>"
        "<input type='submit' value='Update'>"
    "</form></br>"
 "<div id='prg'>progress: 0%</div><td></tr>"
"<tr><td colspan=3><label>设置说明：<br/></label></td></tr></table>"
"</body>"
 "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')" 
 "},"
 "error: function (a, b, c) {"
 "}"
 "});"
 "});"
 "</script>";

union para_value{ //联合体，保存int
    int val;
    byte val_b[2];
};
para_value e_int;
//****载入配置
void myconfig(){
   EEPROM.begin(1024);
   e_int.val_b[0]=EEPROM.read(0);
   e_int.val_b[1]=EEPROM.read(1);
   temp_mod=e_int.val;
   if(temp_mod>=0&&temp_mod<32768)  temp_mod=temp_mod;
   if(temp_mod>=32768)  temp_mod=temp_mod-65536;
   e_int.val_b[0]=EEPROM.read(2);
   e_int.val_b[1]=EEPROM.read(3);
   hum_mod=e_int.val;
   if(hum_mod>=0&&hum_mod<32768)  hum_mod=hum_mod;
   if(hum_mod>=32768)  hum_mod=hum_mod-65536;

   //读取城市8~len_city
   len_city=EEPROM.read(4);
   len_key=EEPROM.read(5);
   city="";
   zx_key="";
   for(int i=0;i<len_city;i++){
    city+=char(EEPROM.read(6+i));
   }
   //读取key 11+len_city~11+len_city+len_key
    for(int i=0;i<len_key;i++){
    zx_key+=char(EEPROM.read(7+len_city+i));
   }
   Serial.print("load config success!");
   Serial.println(city);
   Serial.println(zx_key);
}
void saveconfig(){
  EEPROM.begin(1024);  
  e_int.val=temp_mod;
  EEPROM.write(0,e_int.val_b[0]);    //temo
  EEPROM.write(1,e_int.val_b[1]);
  e_int.val=hum_mod;
  EEPROM.write(2,e_int.val_b[0]);    //hum
  EEPROM.write(3,e_int.val_b[1]);
  
  //保存城市和key 用8，9存储长度
  int i=0;
  len_city=city.length();
  len_key=zx_key.length();
  EEPROM.write(4,len_city); 
  EEPROM.write(5,len_key); 
  char citychar[city.length()];
  strcpy(citychar,city.c_str());
  for (;i<strlen(citychar);i++){
    EEPROM.write(6+i,citychar[i]); 
  }
  Serial.println(city);
  //保存key
  char keychar[len_key];
  strcpy(keychar,zx_key.c_str());
  for (int j=0;j<strlen(keychar);j++){
    EEPROM.write(7+len_city+j,keychar[j]); 
  }
  EEPROM.commit();           
  Serial.print("save config success!");
}
 
void dht11read() {
  int err = SimpleDHTErrSuccess;
  Serial.print(err);
  dht11.read(&temperature, &humidity, NULL);
}
void GetTime()
{
  year1 = year();
  month1 = month();
  day1 = day();

  hou = hour();
  minu = minute();
  sec = second();
  week = weekday() - 1;           //星期日数据是1
  if (week == 0) week = 15;       //星期日 显示'日'

  sec_ten=second()/10;
  sec_one=second()%10;
  //Conversion();                   //阴历转换
  //temp1=abs(TEMP)/10;             //温度
  //temp2=abs(TEMP)%10;
  //if(temp1==0) temp1=63;          //1-9 首位消0
  //if(TEMP<0) temp1=67;            //0度以下显示"-" 未验证，本地室温没有0度以下
  //if(hour1<6||hour1>18) t4=10; else t4=50;  //亮度控制 6-19点高，其他低，自行设定，或者多档比如增加 if(hour==7||hour==19) t4=10
}
/*-------- NTP code ----------*/
const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address
  while (udp.parsePacket() > 0) ; // discard any previously received packets
  WiFi.hostByName(ntpServerName, ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  return 0; // return 0 if unable to get the time
}
// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}
//***send http 获取农历
void getNongli(String nian, String yue, String ri) {
  HTTPClient http;
  // We now create a URI for the request
  String url = "http://www.autmone.com/openapi/icalendar/queryDate?date=" + nian + "-" + yue + "-" + ri;
  Serial.print(url);
  http.begin(url.c_str());
  String payload ;
  //发起http get请求
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println(payload);
  //  drawText(payload,0,20);

  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
  //利用arduinoJson库解析心知返回的json天气数据
  //能够利用 https://arduinojson.org/v6/assistant/ Arduinojson助手生成相关json解析代码  很方便！！！
  StaticJsonDocument<768> doc;
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  int code = doc["code"]; // 0
  const char* msg = doc["msg"]; // "SUCCESS"
  long long time = doc["time"]; // 1631449659945
  JsonObject data = doc["data"];
  int data_iYear = data["iYear"]; // 2021
  int data_iMonth = data["iMonth"]; // 11
  int data_iDay = data["iDay"]; // 6
  const char* data_iMonthChinese = data["iMonthChinese"]; // "十一月"
  const char* data_iDayChinese = data["iDayChinese"]; // "初六"
  int data_sYear = data["sYear"]; // 2021
  int data_sMonth = data["sMonth"]; // 12
  int data_sDay = data["sDay"]; // 9
  const char* data_cYear = data["cYear"]; // "辛丑年"
  china_year = new char[strlen(data_cYear) + 1];
  strcpy(china_year, data_cYear);
  china_month = new char[strlen(data_iMonthChinese) + 1];
  strcpy(china_month, data_iMonthChinese);
  china_day = new char[strlen(data_iDayChinese) + 1];
  strcpy(china_day, data_iDayChinese);
  Serial.print(china_year);
  Serial.print(china_month);
  Serial.print(china_day);
  /*const char* data_cMonth = data["cMonth"]; // "庚子"
    const char* data_cDay = data["cDay"]; // "辛卯"
    bool data_isHoliday = data["isHoliday"]; // false
    bool data_isLeap = data["isLeap"]; // false*/
    const char* data_solarFestival = data["solarFestival"]; // " 世界足球日"
    jieri=new char[strlen(data_solarFestival)+1];
    strcpy(jieri,data_solarFestival);
    const char* data_solarTerms = data["solarTerms"]; // nullptr节气
    const char* data_lunarFestival = data["lunarFestival"]; // nullptr
    jieqi=new char[strlen(data_solarTerms)+1];
    strcpy(jieqi,data_solarTerms);
    //Serial.print(sizeof(jieqi));
    const char* data_week = data["week"]; // "四"
    if(strcmp(china_month,"十一月")==0){
    china_month="冬月";
  }
  if(strcmp(china_month,"十二月")==0){
    china_month="腊月";
  }
}
void dologin(){
  if(!server.authenticate(username,userpass)){
    return server.requestAuthentication();
  }
  server.sendHeader("Connection", "close");
  server.send(200,"text/html",serverIndex);
}
void updateServer(){
  
  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
  /*return index page which is stored in serverIndex */
  server.on("/",dologin);
  server.on("/serverIndex", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  server.on("/update", HTTP_POST, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
  server.on("/get", HTTP_GET, handleSet);
  server.begin();
}
void handleSet() //回调函数
{
 
    if (server.hasArg("temp")) {
    temp_mod= server.arg("temp").toInt();
    }
    if (server.hasArg("hum")) {
    hum_mod= server.arg("hum").toInt();
    } 
    if(server.hasArg("reboot")){
      ESP.restart();
    }
    if (server.hasArg("chengshi")) {
    city=server.arg("chengshi");
    }
    if (server.hasArg("tianqikey")) {
    zx_key=server.arg("tianqikey");
    }
    saveconfig();

    //server.send(200, "text/plain", "这是链接/p/{}/d/{}，参数是： " + arg0 + " 、 " + arg1);
}
float sensor_Read() {
  int sensorValue = analogRead(34); // 读取模拟引脚34上的输入
  float voltage = sensorValue * (5.0 / 1023.0); // 将模拟读数（从0 - 1023变为0）转换为电压（0 - 5V）
  //  Serial.print("电压：");
  //  Serial.println(voltage); // 打印出模拟口读取的值
  return voltage;
}
void setup()
{
  Serial.begin(115200);
  initOLED();
    myconfig();
  int i=0;
  //connect to WiFi
    drawText("Try to connect WIFI!",0,0);
 
   connectToWiFi(15);   //apConfig();
 
  if(WiFi.status() == WL_CONNECTED){
    updateServer();
    clearOLED();
  Serial.println(" CONNECTED");
  drawText("CONNECTED!",0,0);
  drawText(WiFi.localIP().toString().c_str(),0,20);
  Serial.print(WiFi.localIP());
  //init and get the time
  setSyncProvider(getNtpTime);
  GetTime();
  year_=String(year1);
  month_=String(month1);
  day_=String(day1);
    getNongli( year_, month_, day_);
    getWeather();
        dht11read();
        showTime();
   //   drawHanziS(0,9,china_year,0xff0a);
  }

}

void loop()
{
   server.handleClient();
    if(WiFi.status() == WL_CONNECTED){
    xTaskCreate(
    refreshData,   /* Task function. */
    "refreshData", /* String with name of task. */
    100000,     /* Stack size in bytes. */
    NULL,      /* Parameter passed as input of the task */
    1,         /* Priority of the task. */
    NULL);     /* Task handle. */
  clearOLED();
//  dma_display->fillScreen(0xf7be);
  showTime();
    }
      delay(1000);

}
