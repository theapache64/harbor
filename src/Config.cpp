#include <ESP8266WiFi.h>
#include <map>
#include <string>
#include "NetworkClient.h"


class Config {
private:
    std::map<String, String> configCache;

public:
    String getConfig(String key, String defval) {
        // check if config cache is empty
        if (configCache.empty()) {
            loadConfig();
        }

        std::map<String,String>::const_iterator it = configCache.find( key );
        if ( it == configCache.end()) {
            return defval;
        } else {
            return it->second;
        }
    }

    void loadConfig(){
      HTTPClient request;
      NetworkClient client;
      if(request.begin(*client.httpClient, "https://docs.google.com/spreadsheets/d/1OzhdDoPW-slnVct42AsFLe2zNJJrFReHDz5Gv6hccsA/gviz/tq?tqx=out:csv&sheet=config")) {
          int responseCode = request.GET();
          if (responseCode > 0) {
              String payload = request.getString();
              // Parse the payload and populate the data map  
              
              int startPos = 0;
              int endPos = payload.indexOf('\n');
              bool isLastItem = false;
              while (endPos != -1) {
                  Serial.println("---------------");
              
                  String line = payload.substring(startPos, endPos);

                  int commaPos = line.indexOf(',');
                  if (commaPos != -1) {
                      String key = line.substring(1, commaPos - 1);
                      key.replace("\"", "");
                      String value = line.substring(commaPos + 2, line.length() - 1);
                      value.replace("\"", "");
                      
                      configCache[key] = value;
                  }
                  startPos = endPos + 1;
                  endPos = payload.indexOf('\n', startPos);
                  if(isLastItem){
                      break;
                  }

                  if(endPos == -1) {
                      endPos = payload.length();
                      isLastItem = true;
                  }
              }
          }
      }
    }

    String allConfigs(){
      String str = "";
      for (std::map<String, String>::iterator it = configCache.begin(); it != configCache.end(); ++it) {
          str += it->first + "=" + it->second + ";";
      }
      return str;
    }
};