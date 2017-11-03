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
#define ledPin 9
#define buttonPin 2
int buttonState = 0;
int j;
int Buzzer = 3;
int length = 60; // 음의 개수
char notes[] = "cfgagfg afgfdc cfgagfg afgdef gggfgaf DDCag Cagfgad cfefgf ";
//음 연주 순서(알파벳에 해당하는 음 설정은 아래에 있음)
int beats[] = {1,1,1,1,1,1,4,3,
               2,1,1,1,1,4,3,
               1,1,1,1,1,1,4,3,
               2,1,1,1,1,4,3,
               1,1,1,1,1,1,4,3,
               2,1,2,1,4,3,
               1,1,1,1,1,1,4,3,
               2,1,1,1,1,4,3}; // 음의 길이 16분 음표를 1로 기준
int tempo = 500;  //연주 속도 (낮을수록 빠릅니다.)

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(Buzzer, HIGH);
    delayMicroseconds(tone);   //듀티비
    digitalWrite(Buzzer, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D' };
                //  도   레   미   파   솔   라   시   도 순서입니다.
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 850 };
  //도 = 1915, 레 = 170 ~ 높은 도 = 956 입니다.

  for (int i = 0; i < 9; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  pinMode(Buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState=digitalRead(buttonPin);

  if(buttonState == HIGH)
  {
  for (j = 0; j < length; j++) {
    if (notes[j] == ' ') {
      delay(beats[j] * tempo);
      analogWrite(ledPin, 0);
    } else {
      playNote(notes[j], beats[j] * tempo);
      analogWrite(ledPin, 255);
    }
    
    delay(tempo / 2); 
  }
  }
}
