# Sub-G Smart Agriculture

---
<div align="center">
<img src="./asset/main_image.jpeg">
</div>
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

"Sub-G Smart Agriculture" 은 AxDen 의 Aggregator Platform 를 이용하여 온도, 기압, 조도 와 같은 Smart Agriculture 에서 필요한 핵심적인 센서 정보를 수집합니다.
<br>
1Km 의 이상의 장거리 통신이 필요한 다양한 서비스 시나리오를 빠르게 테스트 할 수 있도록 제공하는 예제입니다.
<br>
<br>
관련 하드웨어 키트는 네이버 스마트 스토어에서 구매 가능합니다.
<br>
[구매링크 : 네이버 스마트 스토어](https://smartstore.naver.com/axden)
<br>
<br>
"Sub-G Smart Agriculture" uses AxDen's Aggregator Platform to collect key sensor information necessary for Smart Agriculture such as temperature, barometric pressure, and illuminance.
<br>
This is an example that provides quick testing of various service scenarios that require long-distance communication of 1Km or more.
<br>
<br>
Related hardware kits can be purchased from the Naver Smart Store.
<br>
[Purchase Link : naver smart store](https://smartstore.naver.com/axden)
<br>
<br>
## Sub-G Smart Agriculture 의 주요 특징 및 기능
<table >
  <tr align="center">
    <td>MCU</td>
    <td>Description</td>
  </tr>
  <tr align="center">
    <td>CC1312R1</td>
    <td>TI ROTS, EasyLink</td>
  </tr>
</table>

*\* TI Sensor Controller 이용한 저전력 기술은 Production version 제품군에서 확인하실 수 있습니다.*
<br>
*\* Low-power technology with TI Sensor Controller is available in the Production version family.*

Sensor | Description
:-------------------------:|:-------------------------:
BME280 | Air pressure, temperature sensor
HDC1080 | Humidity, temperature sensor
VCNL4040 | ToF distance, ambient light sensor
Soil moisture sensor | On board

"Sub-G Smart Agriculture" 예제는 온도, 기압, 조도 와 같은 Smart Agriculture 에서 필요한 핵심적인 센서 정보를 수집하고 Sub-G 장거리 통신을 이용하여 전송합니다.
AxDen Aggregator Platform 과 연동하여 서버, DB 와 같은 인프라 구축 없이 Web 과 Mobile 에서 센서 정보를 확인할 수 있으며, 저장된 센서정보를 이용하여 Edge AI 를 학습시킵니다.  
<br>
"Sub-G Smart Agriculture" example collects key sensor information required in Smart Agriculture such as temperature, barometric pressure, and illuminance, and transmits it using Sub-G long-distance communication. In conjunction with the AxDen Aggregator Platform, you can check sensor information on the web and mobile without building infrastructure such as servers and DBs, and use the stored sensor information to learn Edge AI.
<br>
<br>
### **터미널을 이용한 확인 방법 (Check via terminal)**
어댑터 보드가 있다면 터미널을 통해 통신 확인이 가능합니다.
<br>
어댑터 보드와 Sub-G Smart Agriculture 센서를 PC에 연결한 후, screen 및 putty 등 시리얼 프로그램을 통해서 확인합니다. (Baudrate 는 9600 입니다)
<br>
<br>
If you have an adapter board, you can check the communication through the terminal.
<br>
After connecting the adapter board and the Sub-G Smart Agriculture sensor to the PC, check through serial programs such as screen and putty. (Baudrate is 9600)
<br>
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
<br>

### **AXDEN Aggregator Platform 을 이용한 확인 방법 (Check via AXDEN Aggregator platform)**
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

## Hardware 핀맵
board_define.h 파일에서 확인 가능합니다.

### [펌웨어 설정 및 컴파일](https://github.com/AxDen-Dev/CC1312R1_Ping_Pong_example_gcc)

### [펌웨어 플래싱](https://github.com/AxDen-Dev/CC1312R1_Ping_Pong_example_gcc)
