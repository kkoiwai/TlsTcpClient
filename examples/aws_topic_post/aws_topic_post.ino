
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
                    "MIIDWjCCAkKgAwIBAgIVAKEYCHd0fzf/+OTLX2zeGWqsxqInMA0GCSqGSIb3DQEB\n"
                    "CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"
                    "IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xNzExMTQxNDEy\n"
                    "MTJaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"
                    "dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDd+SwB34CePzJ36ntt\n"
                    "yyEISfJLZYTU/TKQCEPaeCzUgsvH/PHxnA162cUDTUmahYecS3TdJuGgJ48+E2PK\n"
                    "NxuYqXkJOnKBFNnf3AFZ5B6TrZ3WghGgjtI/qIWvbv2TMya4mfZww4SARQz7HbZ3\n"
                    "0qj14xbSyW/Ls4rd+JrzYTBdzH5I9kZWvWpRbJijWm3glT0RwgmKU+U3m6SuVQvR\n"
                    "dpik6/SFSohoJKEKUD9vj7anMCXyHDhYrYNfMu9btdDKzmq76N02WGXsAaApKqLC\n"
                    "ItDE1zMv6cSxqkWHm0vjX7YadhkR4jY/Jct1oF/waFgAVNu5O7bOjCmseC2l+vka\n"
                    "ugpjAgMBAAGjYDBeMB8GA1UdIwQYMBaAFPsrggyevSQGKBM8wrtlC8kkz1blMB0G\n"
                    "A1UdDgQWBBT/HaNa+aKquD7+TLhTgDPscJ2JIjAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"
                    "DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEARvYwSFO/vYAKdWV8GtzAjXP7\n"
                    "vZFggZAQBKeRe52yCXrp3hbniB6gnsbHFNS2BQQiJ74xzcZMOT6LjB++m28al2u+\n"
                    "ZhMb7sAizLpELq+O6p3jX/D8fwqTGvCr41mKZzJnTuhCz1PKHNEN/8kxqcLx28sp\n"
                    "LYVCw4gHTXLN8LMWA+VqMiJmLFfcvN7XDONLHcjxCcRvZrf0zu2l0d6PgBWGtXgQ\n"
                    "Vbslx/3JfapWz/VcE/5a7u5dEyy4n1kCbNvvLg8+Ar8SfKj+yjAg7btneSYTvcFx\n"
                    "A3nfivxFZuolG10/QQGpHQERHlG1qvAWRmteMP0Wx2zM0QturGCAOvwOt+na7w==\n"
                    "-----END CERTIFICATE-----\n";

const char pem_pkey[] = "-----BEGIN RSA PRIVATE KEY-----\n"
                    "MIIEpAIBAAKCAQEA3fksAd+Anj8yd+p7bcshCEnyS2WE1P0ykAhD2ngs1ILLx/zx\n"
                    "8ZwNetnFA01JmoWHnEt03SbhoCePPhNjyjcbmKl5CTpygRTZ39wBWeQek62d1oIR\n"
                    "oI7SP6iFr279kzMmuJn2cMOEgEUM+x22d9Ko9eMW0slvy7OK3fia82EwXcx+SPZG\n"
                    "Vr1qUWyYo1pt4JU9EcIJilPlN5ukrlUL0XaYpOv0hUqIaCShClA/b4+2pzAl8hw4\n"
                    "WK2DXzLvW7XQys5qu+jdNlhl7AGgKSqiwiLQxNczL+nEsapFh5tL41+2GnYZEeI2\n"
                    "PyXLdaBf8GhYAFTbuTu2zowprHgtpfr5GroKYwIDAQABAoIBAQCN5QiysdMgVbnH\n"
                    "WkdIqj8Vc1/FvsGo/api1EW71HKj7nCiCRoInv8m9yqvr6pLcux7hujPrlkw7djt\n"
                    "j6uMyqmDb2KF+azUwyV7qsHaWq8JLETnqQHnpyTTuMCsosDKZjpsa09USkfbT0i7\n"
                    "BgVsl2eWt3IRkN88UiuFNbSnvAsVCcD5qsLtZ++uE8e7UnR+ze/44Uj9Smar6OQK\n"
                    "UzpbEAHLAT2VDOnjMvl3ELIM7HlwmeJ2Iv/mstNTZQ9P5q062HabQDyu7L63c7/3\n"
                    "KS5VlAJhZn+PzYfctlFrh+3reU0CsZjBusjZ6RB7oa4C2q+RqY3pJVGw1IGHZ4zS\n"
                    "/LIPvLUBAoGBAPe7223SiXjWGiSIFnS7JveaJyWso5082J3GCFaw3uPNwg3rxI6f\n"
                    "RqGiMY0zwPFyx0nf8zaYGUnrjtlvDmdVOM+h0tj3SlyDUE/EgxxcQjf0tcYq0wPL\n"
                    "mkWZ3hRcmq0SnTe+7xDka8NsIse5/VrNtE2x8UavMvapsJAUNlFJWAUjAoGBAOVh\n"
                    "RMLiN1vOoDsvYXPBSV7Va6GMsH051rdA7uFawGww1mBuqP8NJHY1vh3VG9X0Hgvk\n"
                    "kNOkn9jEe44wRktfk19qKssRYAHhIYJikdwTthdnsasQ0I5pMjf231eZTUzPZKil\n"
                    "SaH1b9h3qjE+o3xSYi4Gli48hP+PRPr8Y9HR51nBAoGAfPj6wBM2oIu5knZIhcin\n"
                    "5r6QQxQtUbQRPr5ZFIqTVm5FF8q5VI2LDx0ITEgwbF1PpbfhNMhT8ZNwc8XviTdX\n"
                    "un7TI/rUO4lO6X6j+ZmdGidLz9VosAB1KeluO+1fZjH+t9GNPoNMzb/uZ70uzzD4\n"
                    "ZT2ADv1xAzglRvm7URRj3+sCgYEAzPXdO0ZnsOEwy7HKomRT6ylIw1GzYjIMajLb\n"
                    "QQKWbhY1eHVpDH3x1q6u8nk6JjO7pWTXBEZVjpwCy0rXhQIh7WAwXMNpxkQkbR0m\n"
                    "uD/ktYUyfGjJ8naNKPSvHNce+0NV7lvDL7Tf+8zxho8yBiSXFglMqIPrU2/xc1OS\n"
                    "3ilxUAECgYA4Wgl+6u5w517F5cNxXLj28A3/do1ceKw7pX9Jd+LZWlwwh3Ju1p0D\n"
                    "eZL4cEnXXHDaMwW5b73ghku575qyJLvKpbdL/LsFCvEBjAvTuEUx7U307etwy8I1\n"
                    "eKGB2+g2+99d0JJq11OVqm2Fnt0Tfk8dEMvkYiJ0CPCWasg3qrmZ6g==\n"
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



