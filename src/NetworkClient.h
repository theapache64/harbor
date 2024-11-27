#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <memory>


class NetworkClient {

public:
  NetworkClient();
  std::unique_ptr<BearSSL::WiFiClientSecure> httpClient;
};

#endif // NETWORKCLIENT_H