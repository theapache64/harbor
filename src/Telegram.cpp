#include <map>
#include <string>
#include <Keys.h>
#include "NetworkClient.h"

class Telegram {
private:
    std::map<String, String> configCache;
    NetworkClient client;

    void send(String message, String token, String groupChatId) {
        // check if config cache is empty
        HTTPClient telegramSendMsgRequest;

        if (telegramSendMsgRequest.begin(*client.httpClient, "https://api.telegram.org/bot" + token + "/sendMessage?chat_id="+ groupChatId +"&text=" + message)) {  // HTTPS
            Serial.println("[HTTPS] GETing... " + message);
            // start connection and send HTTP header
            int responseCode = telegramSendMsgRequest.GET();
            // responseCode will be negative on error
            if (responseCode > 0) {
                // HTTP header has been send and Server response header has been
                // handled
                Serial.println("[HTTPS] GET... code: " + String(responseCode));
            } else {
                Serial.println("[HTTPS] GET... failed, error: " + String(responseCode));
            }

            telegramSendMsgRequest.end();
        }else {
            Serial.println("[HTTPS] Unable to connect");
        }
    }
public:
    void sendAlert(String message) {
        send(message, ALERT_BOT_TOKEN, ALERT_GROUP_CHAT_ID);
    }

    void sendHealth(String message) {
        send(message, HEALTH_BOT_TOKEN, HEALTH_GROUP_CHAT_ID);
    }
};