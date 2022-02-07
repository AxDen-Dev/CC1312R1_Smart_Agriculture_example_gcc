# Sub-G Smart Agriculture

---
<img src="./asset/main_image.jpeg">

<br>
<br>

<table>
<tr align="center">
  <td> TOP </td>
  <td> BOTTOM </td>
</tr>
  <tr align="center">
    <td><img src="./asset/top_board.jpeg"></td>
    <td><img src="./asset/bottom_board.jpeg"></td>
  </tr>
</table>

----

Sub-G Smart Agriculture 은 AxDen 의 Aggregator Platform 를 이용하여 온도, 기압, 조도 와 같은 Smart Agriculture 에서 필요한 핵심적인 센서 정보를 수집합니다.
<br>
1Km 의 이상의 장거리 통신이 필요한 다양한 서비스 시나리오를 빠르게 테스트 할 수 있도록 제공하는 예제입니다.
<br>
<br>
Sub-G Smart Agriculture uses AxDen's Aggregator Platform to collect key sensor information necessary for Smart Agriculture such as temperature, barometric pressure, and illuminance.
<br>
This is an example that provides quick testing of various service scenarios that require long-distance communication of 1Km or more.
<br>
### Sub-G Smart Agriculture 의 주요 특징 및 기능

MCU | 설명
:-------------------------:|:-------------------------:
CC1312R1 | TI ROTS, EasyLink

*TI Sensor Controller 이용한 저전력 기술은 Production version 제품군에서 확인하실 수 있습니다.*

센서 | 설명
:-------------------------:|:-------------------------:
BME280 | Air pressure, temperature sensor
HDC1080 | Humidity, temperature sensor
VCNL4040 | ToF distance, ambient light sensor
Soil moisture sensor | On board

Sub-G Smart Agriculture 예제는 온도, 기압, 조도 와 같은 Smart Agriculture 에서 필요한 핵심적인 센서 정보를 수집하고 Sub-G 장거리 통신을 이용하여 전송합니다.
<br>
<br>
AxDen Aggregator Platform 과 연동하여 서버, DB 와 같은 인프라 구축 없이 Web 과 Mobile 에서 센서 정보를 확인합니다.
<br>
<br>
AxDen Aggregator Platform 에 저장된 센서 정보를 이용하여 Edge AI 를 학습시킵니다.
<br>

#### 터미널을 이용한 확인 방법
어댑터 보드가 있다면 터미널을 통해 통신 확인이 가능합니다.
<br>
<br>
어덥테 보드와 Sub-G Smart Agriculture 센서를 PC 에 연결합니다.
<br>
<br>
screen 및 putty 등 시리얼 프로그램을 통해서 확인할 수 있으며, Baudrate 는 9600 입니다.
<table>
  <tr align="center">
    <td>RF rx example terminal</td>
    <td>RF tx example terminal</td>
  </tr>
  <tr align="center">
    <td><img src="./asset/rx_screen.png"></td>
    <td><img src="./asset/tx_screen.png"></td>
  </tr>
</table>

#### AxDen Aggregator Platform 을 이용한 확인 방법
AxDen Aggregator 홈페이지에서 회원 가입 후 Sub-G Smart Agriculture 의 MAC Address 를 등록합니다.
<br>
AxDen Aggregator 홈페이지에서 제공하는 COMPANY ID, DEVICE ID 를 Protocol.h 파일의 COMPANY_ID, DEVICE_ID 에 입력합니다.
<br>
<br>
`#define COMPANY_ID 0`
<br>
`#define DEVICE_TYPE 0`
<br>
<br>
컴파일 후 플래싱을 합니다.
<br>
<br>
터미널을 통해 COMPANY_ID, DEVICE_ID 가 정상적으로 적용되었는지 확인합니다.
<br>
<br>
아래 이미지와 같이 센서 정보를 Web 또는 Mobile 에서 확인할 수 있습니다.
<br>
<br>
<img src="./asset/axden_aggregator_web.png">
<br>

### Hardware 핀맵
board_define.h 파일에서 확인 가능합니다.

### [펌웨어 설정 및 컴파일](https://github.com/AxDen-Dev/CC1312R1_Ping_Pong_example_gcc)

### [펌웨어 플래싱](https://github.com/AxDen-Dev/CC1312R1_Ping_Pong_example_gcc)
