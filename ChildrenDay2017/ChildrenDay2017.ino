#define echo_forward 2
#define echo_left 3
#define echo_right 4
#define trig 5
#define LED1 7
#define LED2 8
#define LED3 9
#define MALEFT 10
#define MARIGHT 11
#define MBLEFT 12
#define MBRIGHT 13  
#define delay_time 290
#define delay_forward 698
#define delay_turn 400
#define mm 100

unsigned int forward, left, right;
unsigned int Save_random;
unsigned int i, check;
int cnt, average_forward = 0, average_left = 0, average_right = 0;
int chk_f,chk_l,chk_r;

void setup() {
pinMode(echo_forward, INPUT);
pinMode(echo_left, INPUT);
pinMode(echo_right, INPUT);
pinMode(trig, OUTPUT);
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(MALEFT, OUTPUT);
pinMode(MARIGHT, OUTPUT);
pinMode(MBLEFT, OUTPUT);
pinMode(MBRIGHT, OUTPUT);
Serial.begin(9600);
}

void loop() {
chk_f = chk_l = chk_r = average_forward = average_left = average_right = cnt = 0;
delay(500);

ALL();
for(i=0;i<5;i++){
delayMicroseconds(100);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);
forward = pulseIn(echo_forward,HIGH) / 10;
if(forward != 0){
  average_forward += forward;
  chk_f++;
}

delayMicroseconds(100);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);
left = pulseIn(echo_left,HIGH) / 10;
average_left = average_left + left;
if(left != 0){
  average_left += left;
  chk_l++;
}

delayMicroseconds(100);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);
right = pulseIn(echo_right,HIGH) / 10;
if(right != 0){
  average_right += right;
  chk_r++;
}
}

if(chk_f == 0){
  average_forward = 0;
}else
{
average_forward /= chk_f;
}
if(chk_l == 0){
  average_left = 0;
}else
{
average_left /= chk_l;
}
if(chk_r == 0){
  average_right = 0;
}else
{
average_right /= chk_r;
}
/*
Serial.println();
Serial.print(forward);
Serial.print(" ");
Serial.print(left);
Serial.print(" ");
Serial.print(right);
Serial.print(" : ");
*/
int chk_cnt = 0;
int chk[4];
for(int i = 0;i<4;i++)chk[i] = 3;

 if(average_forward >= mm || average_forward == 0)chk[chk_cnt++] = 0;
if(average_left >= mm + 40 || average_left == 0)chk[chk_cnt++] = 1;
if(average_right >= mm + 40 || average_right == 0)chk[chk_cnt++] = 2;
/*
for(int i = 0;i<chk_cnt;i++)
{
  Serial.print(chk[i]);
  Serial.print(" ");
}
Serial.print(": ");
*/
if(chk_cnt > 0)
{
int n = 3;
n = chk[random(0,chk_cnt)];
//Serial.print(n);
switch(n)
{
  case 0:
    LEDA();
    MOVEA();
    delay(delay_forward);
    STOP();
    break;
  case 1:
    LEDB();
    MOVEB();
    delay(delay_time + 19);
    STOP();
    delay(delay_turn);
    MOVEA();
    delay(delay_forward + 16);
    STOP();
    break;
  case 2:
    LEDC();
    MOVEC();
    delay(delay_time + 12);
    STOP();
    delay(delay_turn);
    MOVEA();
    delay(delay_forward + 12);
    STOP();
    break;
   case 3:
   ALL();
   STOP();
   break;
}
}
}

void LEDA(){
  digitalWrite(LED1,HIGH);
  delay(400);
  digitalWrite(LED1,LOW);
}

void LEDB(){
  digitalWrite(LED2,HIGH);
  delay(400);
  digitalWrite(LED2,LOW);
}

void LEDC(){
  digitalWrite(LED3,HIGH);
  delay(400);
  digitalWrite(LED3,LOW);
}

void MOVEA(){
  digitalWrite(MALEFT,LOW);
  digitalWrite(MBLEFT,HIGH);
  digitalWrite(MARIGHT,HIGH);
  digitalWrite(MBRIGHT,LOW);
}

void MOVEB(){
  digitalWrite(MALEFT,HIGH);
  digitalWrite(MBLEFT,LOW);
  digitalWrite(MARIGHT,HIGH);
  digitalWrite(MBRIGHT,LOW);
}

void MOVEC(){
  digitalWrite(MALEFT,LOW);
  digitalWrite(MBLEFT,HIGH);
  digitalWrite(MARIGHT,LOW);
  digitalWrite(MBRIGHT,HIGH);
}

void STOP(){
  digitalWrite(MALEFT,0);
  digitalWrite(MBLEFT,0);
  digitalWrite(MARIGHT,0);
  digitalWrite(MBRIGHT,0);
}

void ALL(){
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED3,HIGH);
  delay(400);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
}

