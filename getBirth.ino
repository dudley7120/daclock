//获取API里的纪念日
void getBirth() {
  HTTPClient http;
  // We now create a URI for the request
  String url = "http://82.157.26.5/getShowText?clockid="+macAddr;
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
       jieri=DATA_item_Title;
    }
  }
}
