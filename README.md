# Simple TLS Client Library for Wio-LTE
[Wio LTE for Arduino](https://github.com/SeeedJP/WioLTEforArduino/) で、AWS-IoTなどのクライアント証明書を必要とするTLS接続を行うためのライブラリです。
Wio LTE内臓のLTEモジュールでもTLS接続は可能ですが、なぜかAWSとうまく繋がらない（おそらく対応している暗号スイートのため）ので、つくってみました。
[mbedTLS](https://tls.mbed.org/)と、[Simple TLS Client library for Particle](https://github.com/hirotakaster/TlsTcpClient) をベースに開発しています。


## 注意
超初心者が、かなり危ない実装をしていますので、商用利用等、落ちたり鍵が漏れたりしたら困るような用途には使わないでください。
また、MQTTに対応するため、大きく改修を予定しています。
