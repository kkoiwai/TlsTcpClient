
#include <stdio.h>
#include <Wire.h>

#include <WioLTEforArduino.h>
#include <WioLteTlsClient.h>

#define APN               "soracom.io"
#define USERNAME          "sora"
#define PASSWORD          "sora"


const char pem_CA[] = "-----BEGIN CERTIFICATE-----\n"
                  "MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCB\n"
                  "yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL\n"
                  "ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp\n"
                  "U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW\n"
                  "ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0\n"
                  "aG9yaXR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjEL\n"
                  "MAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZW\n"
                  "ZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2ln\n"
                  "biwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp\n"
                  "U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9y\n"
                  "aXR5IC0gRzUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1\n"
                  "nmAMqudLO07cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbex\n"
                  "t0uz/o9+B1fs70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIz\n"
                  "SdhDY2pSS9KP6HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQG\n"
                  "BO+QueQA5N06tRn/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+\n"
                  "rCpSx4/VBEnkjWNHiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/\n"
                  "NIeWiu5T6CUVAgMBAAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8E\n"
                  "BAMCAQYwbQYIKwYBBQUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAH\n"
                  "BgUrDgMCGgQUj+XTGoasjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVy\n"
                  "aXNpZ24uY29tL3ZzbG9nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKv\n"
                  "MzEzMA0GCSqGSIb3DQEBBQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzE\n"
                  "p6B4Eq1iDkVwZMXnl2YtmAl+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y\n"
                  "5gaRQBi5+MHt39tBquCWIMnNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlK\n"
                  "WE9gyn6CagsCqiUXObXbf+eEZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ\n"
                  "4fQRbxC1lfznQgUy286dUV4otp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8N\n"
                  "hnacRHr2lVz2XTIIM6RUthg/aFzyQkqFOFSDX9HoLPKsEdao7WNq\n"
                  "-----END CERTIFICATE-----\n";

const char pem_cert[] = "-----BEGIN CERTIFICATE-----\n"
                    "==========================Add your certificate============================"
                    "-----END CERTIFICATE-----\n";

const char pem_pkey[] = "-----BEGIN RSA PRIVATE KEY-----\n"
                    "==========================Add your private key============================"
                    "-----END RSA PRIVATE KEY-----\n";

WioLTE Wio;
WioLTEClient WioClient(&Wio);

void setup() {
  SerialUSB.begin(9600);
  delay(200);

  SerialUSB.println("");
  SerialUSB.println("--- START ---------------------------------------------------");
  
  SerialUSB.println("### I/O Initialize.");
  Wio.Init();
  
  SerialUSB.println("### Power supply ON.");
  Wio.PowerSupplyLTE(true);
  delay(5000);

  SerialUSB.println("### Turn on or reset.");
  if (!Wio.TurnOnOrReset()) {
    SerialUSB.println("### ERROR! ###");
    return;
  }

  SerialUSB.println("### Connecting to \""APN"\".");
  delay(5000);
  if (!Wio.Activate(APN, USERNAME, PASSWORD)) {
    SerialUSB.println("### ERROR! ###");
    return;
  }

}

void loop() {
    unsigned char buff[256];
    
    WioLteTlsClient client(&WioClient);

    // setup pem.
   client.init(pem_CA, sizeof(pem_CA), pem_cert, sizeof(pem_cert), pem_pkey, sizeof(pem_pkey));

    // connect HTTPS server.
    client.connect("data.iot.ap-northeast-1.amazonaws.com", 8443);

    if (!client.verify()) {
      SerialUSB.println("Server Certificates is in-valid.");
    }else{
      SerialUSB.println("Server Certificates is valid.");
    }

    char data[100];
    sprintf(data, "{\"uptime\":%lu}", millis() / 1000);
    
    // Send request to HTTPS web server.
    int len = sprintf((char *)buff, "POST /topics/Wio?qos=1 HTTP/1.0\r\n" \
              "Host: data.iot.ap-northeast-1.amazonaws.com\r\nContent-Length: %d\r\n\r\n" \
              "%s\r\n\r\n",strlen(data),data);
              
    SerialUSB.println((char *)buff);
    client.write(buff, len );

    // POST HTTPS response.
    memset(buff, 0, sizeof(buff));
    bool isRead = false;
    while(1) {
        // read renponse.
        memset(buff, 0, sizeof(buff));
        int ret = client.read(buff, sizeof(buff) - 1);

        delay(2000);
        if (ret == MBEDTLS_ERR_SSL_WANT_READ) {
            if(isRead) break; // no more read
            delay(100);
            continue;
        } else if (ret <= 0) {
            // no more read.
            break;
        } else if (ret > 0){
            SerialUSB.println((char *)buff);
            isRead = true;
        }
    }
    client.close();

    delay(10000);
}



