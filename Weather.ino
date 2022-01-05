
//***send http 获取天气
void getWeather() {
  HTTPClient http;
  // We now create a URI for the request
  String url = "https://devapi.heweather.net/v7/weather/now?key="+zx_key+"&location="+city+"&unit=m&lang=zh&gzip=n";;
  http.begin(url.c_str());
  String payload ;
  //发起http get请求
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println(payload);
    StaticJsonDocument<768> doc;

    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    } else {

      const char* code = doc["code"]; // "200"
      const char* updateTime = doc["updateTime"]; // "2021-11-16T22:47+08:00"
      const char* fxLink = doc["fxLink"]; // "http://hfx.link/2ax1"

      JsonObject now = doc["now"];
      const char* now_obsTime = now["obsTime"]; // "2021-11-16T22:36+08:00"
      const char* now_temp = now["temp"]; // "6"
      const char* now_feelsLike = now["feelsLike"]; // "4"
      const char* now_icon = now["icon"]; // "150"
      const char* now_text = now["text"]; // "晴"
      const char* now_wind360 = now["wind360"]; // "180"
      const char* now_windDir = now["windDir"]; // "南风"
      const char* now_windScale = now["windScale"]; // "1"
      const char* now_windSpeed = now["windSpeed"]; // "4"
      const char* now_humidity = now["humidity"]; // "84"
      const char* now_precip = now["precip"]; // "0.0"
      const char* now_pressure = now["pressure"]; // "1021"
      const char* now_vis = now["vis"]; // "6"
      const char* now_cloud = now["cloud"]; // "20"
      const char* now_dew = now["dew"]; // "3"

      JsonArray refer_sources = doc["refer"]["sources"];
      const char* refer_sources_0 = refer_sources[0]; // "QWeather"
      const char* refer_sources_1 = refer_sources[1]; // "NMC"
      const char* refer_sources_2 = refer_sources[2]; // "ECMWF"

      const char* refer_license_0 = doc["refer"]["license"][0]; // "no commercial use"
      wea_code = atoi(now_icon);
      wea_hm = atoi(now_humidity);
      strcpy(wea_temp1, now_temp);
      Serial.print("温度");
      Serial.println(now_temp);
      Serial.println(now_icon);
      if(wea_code==151){
        wea_code=101;
      }
    }

  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  //利用arduinoJson库解析心知返回的json天气数据
  //能够利用 https://arduinojson.org/v6/assistant/ Arduinojson助手生成相关json解析代码  很方便！！！
  // String input;

  // String input;


}
