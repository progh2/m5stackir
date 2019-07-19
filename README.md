# M5Stack 리모컨 리더기 만들기
## 소개
생활 가전 중에는 적외선 리모컨을 가지고 조작하는 기기들이 참 많습니다. 하지만 기기의 수 만큼 리모컨 수가 늘어나면 기기를 조작할 때마다 리모컨을 찾아야 하고 리모컨이란 존재는 필요한 때가 되면 스스로 숨는 버릇을 가지고 있기 마련이죠. 이러한 스트레스에서 벗어나려면? 하나의 적외선 기기로 제어를 할 수 있는 만능 리모컨을 만들면 어떨까요? 그래서 여기에서는 직접 만능 리모컨을 만들 수 있도록, 기존 리모컨의 명령값을 읽어들여서 출력하는 실습을 해보고자 합니다. 이 튜터리얼에서는 다음과 같은 것들을 배울 수 있습니다.

## 배울 수 있는 것들
- 아두이노 기반 개발환경 구축 방법
- M5Stack의 LCD 화면을 꾸미고 글자를 출력하는 법
- IR Unit의 적외선 수신 값을 가져오는 법

## 준비물
- M5Go Kit  [[구매]()]  [[상세정보](https://docs.m5stack.com/#/en/core/m5go)]
또는
- M5Stack Core [[구매]()]  [[상세정보](https://docs.m5stack.com/#/en/core/m5go)] 와 IR Unit  [[구매]()]  [[상세정보](https://docs.m5stack.com/#/en/unit/ir)]

## 레퍼런스
- [M5Core Quick Start 가이드]()
- M5Stack Arduino API : [LCD](https://docs.m5stack.com/#/en/api/lcd), [IR Unit](https://docs.m5stack.com/#/en/unit/ir)
- [M5Stack Core IR Detect Example](https://github.com/m5stack/M5-ProductExampleCodes/blob/master/Unit/IR/Arduino/ir_dectect/ir_dectect.ino)

## 하드웨어 연결하기
  - M5Go Kit 안에 있는 M5Stack Core 기기와 IR Unit, 그루브 케이블, USB-C 케이블을 준비합니다.
  - M5Stack Core의 B포트에 IR Unit를 그루브 케이블을 사용해서 연결합니다.
  - USB-C 케이블을 M5Stack Core와 노트북 본체를 연결합니다.

## 개발환경 구축하기
> [Quick Start 가이드](https://docs.makerfactory.io/m5stack/core/quickstart/windows/) 내용을 참고하여 구축할 수도 있습니다.

### 드라이버 설치하기
- [M5Stack 다운로드 페이지(Support -> Download)](https://m5stack.com/pages/download)로 갑니다.
- [CP210X Driver](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/drivers/CP210x_VCP_Windows.zip)를 다운받아 압축을 푼 후 설치합니다.
![image](https://user-images.githubusercontent.com/1307187/61534081-8fa8c080-aa69-11e9-95da-87b87c2174aa.png)

### 아두이노 스케치 IDE 설치하기
M5Stack의 다운로드 페이지에 있는 아두이노를 받아도 되긴 하지만 이왕 하는 김에 최신 버전을 [공식 홈페이지](https://www.arduino.cc/en/Main/Software)에 가서 다운받도록 합니다. 아래 링크로 접속 후 화면을 살짝 내리면 다운받는 링크가 있습니다. 운영체제만 맞으면 어떤걸 받아도 상관 없지만 여기서는 Windows Installer, for Windows XP and up 라고 써있는 설치 파일을 다운받아 실행하여 설치를 진행합니다.
> 다운로드 : https://www.arduino.cc/en/Main/Software

![image](https://user-images.githubusercontent.com/1307187/61534384-676d9180-aa6a-11e9-8e18-db07dff4010f.png)


### ESP32 BOARDS MANAGER 설치하기

- 아두이노 IDE 설치 후 실행해서 [파일] -> [환경설정] -> [설정] 으로 들어갑니다.
![image](https://user-images.githubusercontent.com/1307187/61534479-ad2a5a00-aa6a-11e9-9815-13c1721834f7.png)

> https://dl.espressif.com/dl/package_esp32_index.json

- 추가적인 보드 매니저 URLs: 라고 써있는 항목 우측에 잇는 아이콘을 클릭하여 나타난 주소 입력 창에 https://dl.espressif.com/dl/package_esp32_index.json 를 집어넣고 [확인]을 누릅니다.
![image](https://user-images.githubusercontent.com/1307187/61534552-e2cf4300-aa6a-11e9-9831-a7d8edc33ca6.png)
![image](https://user-images.githubusercontent.com/1307187/61534583-f37fb900-aa6a-11e9-8510-ea9d3e3e0f88.png)

- 이번에는 메뉴의 [툴] -> [보드:] -> [보드 매니저...] 를 클릭합니다.
![image](https://user-images.githubusercontent.com/1307187/61535009-165e9d00-aa6c-11e9-82e8-6ea27c4b5016.png)

- esp32를 검색해서 esp32 by Espressif Systems가 보이면 Install 버튼을 클릭합니다. 버전은 기본적으로 선택되어있는 최신 버전으로 냅두면 됩니다.
![image](https://user-images.githubusercontent.com/1307187/61535133-705f6280-aa6c-11e9-9b4c-44526a51c32e.png)

### M5Stack 라이브러리 설치하기
- M5Stack의 라이브러리를 사용하기 위한 전용 라이브러리들을 설치합니다. [스케치] -> [라이브러리 포함하기] -> [라이브러리 관리...] 를 클릭합니다.
![image](https://user-images.githubusercontent.com/1307187/61535268-cfbd7280-aa6c-11e9-9eee-46e1b0d4edb3.png)

- M5Stack을 검색해서 나오는 M5Stack by M5Stack 항목을 설치해줍니다. 역시 버전은 최신 버전인 기본값 대로 냅둬서 설치합니다.
![image](https://user-images.githubusercontent.com/1307187/61535418-33e03680-aa6d-11e9-9096-6c72a768ea97.png)

- 여기까지 하면 M5Stack에서 코드를 실행하기 위해 필요한 프로그램들을 모두 설치하였습니다.

### 기기 연결하기
  - M5Stack이 USB-c 케이블로 정상적으로 연결이 되어있는지 확인합니다. 정상적으로 연결되어 있어야 다음 진행 사항으로 진행이 가능합니다.
  - 아두이노 스케치 IDE의 [툴] 메뉴를 클릭해서 [보드:] 값이  M5Stack-Core-ESP32로 되어있으며 Upload Speed:가 921600 로 되어있는지 확인합니다.
![image](https://user-images.githubusercontent.com/1307187/61535652-bcf76d80-aa6d-11e9-84a7-019cbaf18b58.png)

  - 윈도우 돋보기 아이콘을 클릭하여 "장치 관리자"를 검색합니다.(가운데 띄어쓰기를 안하면 검색이 안되니 주의하세요.) 나타나는 장치들에서 포트(COM & LPT) 항목을 찾으면 안에 Silicon .. 으로 잡혀있는 장치가 보일 것입니다. 그 항목 옆에 괄호 안에 써있는 포트가 M5Stack의 연결 포트입니다.
![image](https://user-images.githubusercontent.com/1307187/61535530-7bff5900-aa6d-11e9-8711-d0bf33b62dfc.png)

  - 참고로 이 포트 번호는 같은 종류의 장비라도 각기 다른 포트를 사용할 수 있으니 주의하세요. 예를 들어 M5Stack 기기가 2대가 있는데 하나는 COM5, 하나는 COM7을 사용할 수 있습니다.
  - 연결 포트를 확인했다면 Tools 메뉴에 가서 포트를 기기의 연결 포트로 지정해줍니다. 대부분의 연결 불량은 포트 번호가 틀려서 일어납니다. 만약 해당 포트가 없다면 제대로 컴퓨터와 연결되어 있는지 케이블을 확인하기 바랍니다.
  - 포트까지 잡혔으면 이제 프로그래밍을 할 준비가 끝났습니다. 이제 시작해볼까요?

## 디자인 작업
### 파일 생성
> 여기서 작업한 소스를 보고 싶다면 [여기](https://github.com/progh2/m5stackir/blob/b6621f04391e33060dd827e0fe5eade1728b8cb3/M5StackIR.ino)를 클릭하세요

이제 개발을 시작해 봅시다. 아두이노 스케치 IDE 메뉴에서 [파일] -> [새 파일] 을 클릭합니다. 여기서는 파일 이름을 M5StackIr이라 하도록 하겠습니다. 그러면 아래와 같은 코드가 생성됩니다.

```C    
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
```

![image](https://user-images.githubusercontent.com/1307187/61535842-342d0180-aa6e-11e9-9529-3490a04d785e.png)

### M5 라이브러리 초기화
> 여기서 작업한 소스를 보고 싶다면 [여기](https://github.com/progh2/m5stackir/blob/8d7fa158ea07f3ed9675cb6f0017e3ec4d845529/M5StackIR.ino), 이전 단계 소스와의 차이를 보고 싶다면 [여기](https://github.com/progh2/m5stackir/commit/8d7fa158ea07f3ed9675cb6f0017e3ec4d845529?diff=split)를 클릭하세요

```C    
#include <M5Stack.h>

void setup() {
  M5.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
```
![image](https://user-images.githubusercontent.com/1307187/61536291-45c2d900-aa6f-11e9-9352-678975091011.png)


M5 라이브러리를 사용하기 위해서는 라이브러리를 임포트하고 초기화 함수를 호출해주어야 합니다. 다음과 같이 코드를 추가해 줍니다. 

- 함수들
  - #include <M5Stack.h> M5Stack의 전용 라이브러리를 포함합니다.
  - M5.begin();  M5Stack의 라이브러리를 사용하기 위해서는 제일 먼저 실행되어야 하는 초기화 코드입니다. 이 함수를 호출하고 나면 M5의 다른 함수들을 호출할 수 있습니다.
- 코드의 상단에 라이브러리를 불러오는 코드를 적고, setup() 함수 안에 초기화 코드를 넣어줍니다.

### 글자 출력하기
> 여기서 작업한 소스를 보고 싶다면 [여기](https://github.com/progh2/m5stackir/blob/4b5c30595f246774854489cb674d214a43bad3d6/M5StackIR.ino), 이전 단계 소스와의 차이를 보고 싶다면 [여기](https://github.com/progh2/m5stackir/commit/4b5c30595f246774854489cb674d214a43bad3d6?diff=split)를 클릭하세요

```C    
#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Lcd.println("IR Code Reader");
  M5.Lcd.println("Ready...");
}

void loop() {
  // put your main code here, to run repeatedly:

}
```
![image](https://user-images.githubusercontent.com/1307187/61536347-612de400-aa6f-11e9-9b4d-c8cc51d59ce4.png)

이제 글자를 출력해 보도록 합니다. 
- 함수들
  - M5.Lcd.println("문자열")
- 먼저 프로그램 이름을 출력하고 준비 중임을 표시하도록 Ready... 라고 표시합니다. 다른 프로그래밍 언어와 비슷하게 M5.Lcd.println("문자열"); 함수를 사용하여 글자를 출력할 수 있습니다. 이 부분은 여러번 출력될 필요가 없이 1번만 출력되면 되기 때문에 setup() 함수 내에서 출력하도록 합니다. 다만 출력해보면 글자가 너무 작아서 보기 힘들며 그다지 예쁘지도 않다는 것을 확인할 수 있습니다. 그리고 테스트 해본 사람도 있을지 모르겠지만 한글을 넣으면 출력되지 않음을 알 수 있습니다. 한글은 따로 폰트를 지정해줘야지만 나타나므로 참고하기 바랍니다.

### 배경색, 글자색, 글자 크기 바꾸기
> 여기서 작업한 소스를 보고 싶다면 [여기](https://github.com/progh2/m5stackir/blob/a59e0cea34aafa67ee0994f7385aca15d8fae4ed/M5StackIR.ino), 이전 단계 소스와의 차이를 보고 싶다면 [여기](https://github.com/progh2/m5stackir/commit/a59e0cea34aafa67ee0994f7385aca15d8fae4ed?diff=split)를 클릭하세요

```C    
#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("IR Code Reader");
  M5.Lcd.setCursor(0,40);
  M5.Lcd.println("Ready...");
}

void loop() {
  // put your main code here, to run repeatedly:

}
```

좀 더 볼만하게 변경해보기로 하겠습니다. 화면을 꾸미기 위한 기본적은 함수로 다음과 같은 것들이 있습니다. 

- 함수들
  - M5.Lcd.fillScreen(색깔) 화면 전체를 특정 색으로 칠합니다.
  - M5.Lcd.setTextColor(색깔) 글자 색을 바꿉니다.
  - M5.Lcd.setTextSize(크기) 글자 크기를 변경합니다. 기본 값인 1부터 최대 4까지의 크기를 지정할 수 있습니다.
  - M5.Lcd.SetCursor(x, y) 글자를 출력할 '커서' 위치를 변경합니다. 텍스트편집기에서 커서를 움직여서 원하는 곳에 글자를 출력하는 것처럼, LCD에서 원하는 위치로 옮겨서 글자를 출력하기 위해서는 이 함수를 이용해야 합니다. x, y는 픽셀 위치로 생각하면 됩니다.
- 화면을 파란색으로 초기화하고 글자 색은 흰색으로, 글자 크기는 3으로 약간 크게 지정합니다. 그런 후 "IR Code Reader"라는 프로그램 제목을 적고, 다음줄 위치로 커서를 이동한 후 대기중이라는 의미의 "Ready..."를 출력합니다. 기존 코드도 다음줄로 넘어가서 출력시켜주지만 정확히 원하는 간격을 줄 수 없기 때문에 M5.Lcd.setCursor() 함수를 사용해서 원하는 위치에 출력하도록 해주는 편이 화면을 표현하는데 편리합니다. 

> 참고 - LED API  :  https://docs.makerfactory.io/m5stack/api/lcd/

## IR Unit 활용하기
### IR 라이브러리 초기화
> 여기서 작업한 소스를 보고 싶다면 [여기](https://github.com/progh2/m5stackir/blob/a20891faac98dfd4ef2556dcca3796c8fb930d56/M5StackIR.ino), 이전 단계 소스와의 차이를 보고 싶다면 [여기](https://github.com/progh2/m5stackir/commit/a20891faac98dfd4ef2556dcca3796c8fb930d56?diff=split)를 클릭하세요

```C    
#include <M5Stack.h>
#include <IRremote.h>

int RECV_PIN = 36; 
IRrecv irrecv(RECV_PIN); 

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("IR Code Reader");
  M5.Lcd.setCursor(0,40);
  M5.Lcd.println("Ready...");
  irrecv.enableIRIn(); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
```

IR Unit의 기능을 사용하기 위해서 IRremote라는 유명한 라이브러리를 사용하기로 합니다. 
- 함수들
  - #include<IRremote.h> IR센서를 편리하게 다루도록 해주는 IRremote 라이브러리를 불러옵니다.
  - IRrecv irrecv(IR핀번호) IR 수신 센서의 핀번호를 지정하여(M5Stack에서 IR Unit의 수신 센서의 핀번호는 36번입니다.) 객체를 생성합니다.
  - irrecv.enableIRIn()  IR 수신 센서 동작을 시작합니다.
- 코드 상단에 IRremote 라이브러리를 불러오고 IR센서가 사용하는 핀번호를 지정하여 IR센서를 다룰 객체를 생성합니다. 그런 후 setup()에서 해당 객체를 시작하도록 합니다.

### IR 수신값 읽어서 화면에 출력하기
> 여기서 작업한 소스를 보고 싶다면 [여기](https://github.com/progh2/m5stackir/blob/b06873abc54792c408f15fe7dcb7de807def0bf0/M5StackIR.ino), 이전 단계 소스와의 차이를 보고 싶다면 [여기](https://github.com/progh2/m5stackir/commit/b06873abc54792c408f15fe7dcb7de807def0bf0?diff=split)를 클릭하세요

```C    
#include <M5Stack.h>
#include <IRremote.h>

int RECV_PIN = 36; 
IRrecv irrecv(RECV_PIN); 
decode_results results; 

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("IR Code Reader");
  M5.Lcd.setCursor(0,40);
  M5.Lcd.println("Ready...");
  irrecv.enableIRIn(); 
}

void loop() {
  if (irrecv.decode(&results)) {  
    M5.Lcd.fillRect(0,40,200,30, GREEN);
    M5.Lcd.setCursor(0,40);
    M5.Lcd.println(results.value, HEX);
    irrecv.resume(); 
  }
  delay(100);   
}
```

IR 수신값 읽어서 "Ready..."가 표시되어있는 영역의 글자를 지우고 해당 위치에 IR수신값을 글자를 출력하도록 합니다. 출력 후 다시 신호를 받도록 하는 함수를 호출하고 잠시 대기했다가 다시 신호를 받습니다.

- 함수들
  - decode_results results 결과를 저장할 변수를 생성합니다.
  - if (irrecv.decode(&results)) { } loop()를 돌 때마다 IR수신값이 있는지 확인합니다. IR신호가 발생하면 안에 코드를 실행합니다.
  - M5.Lcd.println(results.value, HEX) IR수신 결과 값을 16진수로 표현합니다.
  - M5.Lcd.fillRect(x, y, 가로크기, 세로크기, 색깔) x, y 픽셀 위치에 가로, 세로크기만큼의 사각형을 만들어 색칠합니다. 바탕색과 같은 색으로 박스를 만들어 덮는다면 해당 부위를 지운 것처럼 효과를 낼 수 있습니다.
  - delay(100) 0.1초동안 대기합니다. 1000을 넣으면 1초동안 대기합니다.
- "Ready..." 가 있는 영역에 배경색과 같은 박스를 칙해서 글자를 지운 것과 같은 효과를 내고, 다시 글자가 있던 위치에 코드 값을 출력해줍니다.

## 실행하기
- 전원을 켜면 화면에 Ready... 글자가 출력됩니다.
- 리모콘을 가져와서 버튼을 누르면 Ready... 글자가 지워지고 해당 버튼의 IR 코드 값이 화면에 출력됩니다.
