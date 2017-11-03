/**********
 <연주하는 방법>
 1. notes 배열에 음계를 알파벳으로 써 넣습니다.
 2. length 변수에 총 음의 개수를 써 넣습니다.
 3. beat 배열에 음의 길이를 써 넣습니다.
 4. temp에 연주속도를 써 넣습니다.
 <음을 추가하는 방법>
 1. playNote 함수의 names 배열에 추가하고싶은 음을 알파벳으로 적습니다.
 2. tones 배열에 해당하는 음에 대한 높낮이를 결정합니다.
 3. 그 밑의 for문에서 조건식을 수정합니다.
 */

#include <Servo.h> //서보모터를 동작시킬 서보 라이브러리를 포함한다.
Servo myservo; //서보 라이브러리에 있는 함수를 사용할 수 있도록 변수를 선언한다.
int angle =0; // 각도를 조절할 변수

#define ledPin 8
#define buttonPin 2
#define light A3
int value = 0;
int buttonState = 0;
int j;
int Buzzer = 3;
int length = 76; // 음의 개수
char notes[] = "gcdefgc afgabCc fgfedefedcncdecd gcdefgc afgabCccfgfedefedcdedcnc ";
//음 연주 순서(알파벳에 해당하는 음 설정은 아래에 있음)
int beats[] = {2,1,1,1,1,2,1,2,
               2,1,1,1,1,2,2,2,
               2,1,1,1,1,2,1,1,1,1,2,
               1,1,1,1,2,2,
               2,1,1,1,1,2,1,1,
               2,1,1,1,1,2,1,1,
               2,1,1,1,1,2,1,1,1,1,2,
               1,1,1,1,2,1}; // 음의 길이 16분 음표를 1로 기준
int tempo = 200;  //연주 속도 (낮을수록 빠릅니다.)



void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(Buzzer, HIGH);
    delayMicroseconds(tone);   //듀티비
    digitalWrite(Buzzer, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'n', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D' };
                //  도   레   미   파   솔   라   시   도 순서입니다.
  int tones[] = { 2100, 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 850 };
  //도 = 1915, 레 = 170 ~ 높은 도 = 956 입니다.

  for (int i = 0; i < 10; i++) {
    if (names[i] == note) { //도레미파솔라시도 10개의 음 중에 작성한 음과 맞는 게 있다면
      angle = (i+1)*18; // 각도를 18도에서 180도까지 돌린다.
      myservo.write(angle); // 서보 모터를 angle 각도만큼 돌린다.
      playTone(tones[i], duration); //서보 모터가 도는 동시에 음이 나온다.
    }
  }
}

void setup() {
  pinMode(Buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(light, INPUT);
  Serial.begin(9600);
  
  myservo.attach(5); //서보 모터를 5번 핀에 연결한다.
}

void loop() {
  value = analogRead(A3);
  
  if(value < 100){
    for (j = 0; j < length; j++) {
      if (notes[j] == ' ') {
        delay(beats[j] * tempo);
        analogWrite(ledPin, 0);
        Serial.println(light);
      }
      else {
         value = analogRead(A3);
        playNote(notes[j], beats[j] * tempo);
        analogWrite(ledPin, 255);
        Serial.println(value);
      }
      delay(tempo / 2); 
    }
  }
}
