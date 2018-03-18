int trigPin = 9; //초음파 발신핀 설정(9번핀으로 설정)
int echoPin = 8; //초음파 수신핀 설정(8번핀으로 설정)
int relay1 = 3; //디스플레이 제어 릴레이핀 설정(3번핀으로 설정)
int relay2 = 6; //전구 제어 릴레이핀 설정(6번핀으로 설정)
int count = 0; //count 초기값을 0으로 설정(relay1(디스플레이)에 사용)
int count1 = 0;//count1 초기값을 0으로 설정(realy2(전구 제어)에 사용)

void setup()
{
  Serial.begin(9600); //시리얼모니터 사용준비
  pinMode(trigPin, OUTPUT);//trigPin 전기신호 출력
  pinMode(echoPin, INPUT);//echoPin를 trigPin에서 내보낸 신호 받아드림
  pinMode(3, OUTPUT);//relay1(디스플레이) 출력
  pinMode(6, OUTPUT);//relay2(전구) 출력
}

void loop()
{
  float duration, distance; //자료형 float 변수 duration, distance 설정
  digitalWrite(trigPin, HIGH); //초음파 발신핀 켜기
  delay(10); //딜레이 0.1초
  digitalWrite(trigPin, LOW); //초음파 발신핀 끄기
  duration = pulseIn(echoPin, HIGH);
  distance = ((float)(340 * duration) / 10000) / 2; // 340은 초당 초음파(소리)의 속도 10000은 밀리세컨드를 세컨드(초)로 바꿈 왕복거리이므로 2로 나눈디

/*
  거리의 최소값을 20으로 정한 이유
  초음파 센서가 잴 수 있는 최소값과 최댓값을 넘어버리면
  엄청 작은 값과 엄청 큰 값을 출력하게 된다
  이런 일을 방지하기 위해 미리 if문에서 제어해주는 것이다.
*/

  if(distance>=20 && distance<=70) //만약 초음파 측정 거리가 20이상 70이하이면
  {
    for(count=0;count<=10;count++)//count를 10까지 1씩 추거한다
    {
     if(count<10)//만약 count의 값이 10 미만이면
     {
        digitalWrite(relay1, HIGH);//relay1(디스플레이)을 킨다
        Serial.print(distance);//시리얼 모니터에 거리 출력
        Serial.println();//시리얼 모니터에서 줄바꿈
        delay(1000);//1초 딜레이
     }
     else if(distance>70 && distance<20)//초음파 측정 거리가 20미만이나 70초과이면
     {
      digitalWrite(relay1, LOW);//relay1(디스플레이)을 끈다
     }
    }
    for(count1=0;count<=15;count++)//count1을 15까지 1씩 추가한다(아직if문(거리 20이상 70이하면) 안에 있다)
    {
     if(count1<15)//만약 count1의 값이 15미만이면
     {
        digitalWrite(relay2, HIGH);//relay2(전구)을 켜놓는다
        Serial.print(distance);//시리얼 모니터에 거리 출력
        Serial.println();//시리얼 모니터에서 줄바꿈
        delay(1000);//1초 딜레이
     }
     else if(distance<20 && distance>70)//만약 거리가 20미만이나 70초과이면
     {
      digitalWrite(relay2, LOW);//relay2(전구)를 끈다
     }
    }
  }
  else//거리가 20미만이나 70초과이면
  {
    digitalWrite(relay1, LOW);//relay1(디스플레이)을 끈다
    digitalWrite(relay2, LOW);//relay2(전구)를 끈다
    Serial.print(distance);//시리얼 모니터에 거리 출력
    Serial.println();//시리얼 모니터에서줄바꿈
  }
}

