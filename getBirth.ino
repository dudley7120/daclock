//获取API里的纪念日
void getBirth() {
  HTTPClient http;
  // We now create a URI for the request
  String url = "http://82.157.26.5/getShowText?clockid=" + macAddr;
  Serial.print(url);
  http.begin(url.c_str());
  String payload ;
  //发起http get请求
  int httpResponseCode = http.GET();

  if (httpResponseCode == 200) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println(payload);
    // String input;
    StaticJsonDocument<192> doc;

    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    for (JsonObject DATA_item : doc["DATA"].as<JsonArray>()) {

      const char* DATA_item_Title = DATA_item["Title"]; // "爸爸生日", "妈妈生日"
      const char* DATA_item_Time = DATA_item["Time"]; // "三月二十", "八月二十九"
      jieri = DATA_item_Title;
    }
  }
}
/*
   获取配置信息
*/
void getConf() {
  HTTPClient http;
  String url = "http://82.157.26.5/index?clockid=" + macAddr;
  http.begin(url.c_str());
  String payload ;
  //发起http get请求
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println(payload);
    StaticJsonDocument<512> doc;

    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    JsonObject DATA = doc["DATA"];
    const char* DATA_isupdate = DATA["isupdate"]; // "0"
    const char* DATA_isnightmode = DATA["isnightmode"]; // "false"
    const char* DATA_temp = DATA["temp"]; // "-3"
    const char* DATA_hum = DATA["hum"]; // "0"
    const char* DATA_chengshi = DATA["chengshi"]; // "101011200"
    const char* DATA_tianqikey = DATA["tianqikey"]; // "6967b386afb341999ee91c0321176ab7"
    const char* DATA_light = DATA["light"]; // "10"
    const char* DATA_starnum = DATA["starnum"]; // "15"
    const char* DATA_soundon = DATA["soundon"]; // "true"
    const char* DATA_caidaion = DATA["caidaion"]; // "false"
    const char* DATA_isDoubleBuffer = DATA["isDoubleBuffer"]; // "false"
    const char* DATA_twopannel = DATA["twopannel"]; // "false"
    if (strcmp(DATA_isupdate,"true")==0) {
      Serial.println("run update");
      temp_mod = atoi(DATA_temp);
      hum_mod = atoi(DATA_hum);
      city=DATA_chengshi;
      zx_key=DATA_tianqikey;
      light = atoi(DATA_light);
      starnum = atoi(DATA_starnum);
      if (strcmp(DATA_soundon,"true")==0) {
        soundon = true;
      } else {
        soundon = false;
      }
      if (strcmp(DATA_caidaion,"true")==0) {
        caidaion = true;
      } else {
        caidaion = false;
      }
      if (strcmp(DATA_isDoubleBuffer,"true")==0) {
        isDoubleBuffer = true;
      } else {
        isDoubleBuffer = false;
      }
      if (strcmp(DATA_isnightmode,"true")==0) {
        isnightmode = true;
      } else {
        isnightmode = false;
      }
      if (strcmp(DATA_twopannel,"true")==0) {
        twopannel = true;
      } else {
        twopannel = false;
      }
      saveconfig();
    }
  }
}
