int r11 = 2;
int r12 = 4;
int l11 = 7;
int l12 = 8;

void setup() {
pinMode(5 ,INPUT);
pinMode(3 ,INPUT);
pinMode(r11, OUTPUT);
pinMode(r12, OUTPUT);
pinMode(l11, OUTPUT);
pinMode(l12, OUTPUT);

Serial.begin(9600);

}

void loop() {
int f = pulseIn (3,HIGH);
int g = pulseIn (5,HIGH);

if (f > 1200&&f < 1500 && g > 1200 &&g < 1500)     //NEUTRAL
{
  digitalWrite(r11, LOW);   
  digitalWrite(r12, LOW);
  digitalWrite(l11, LOW);   
  digitalWrite(l12, LOW);
}
else if (f>1500 && g > 1200 &&g < 1500)            // FORWARD
{
  digitalWrite(r11, HIGH);   
  digitalWrite(r12, LOW);
  digitalWrite(l11, HIGH);   
  digitalWrite(l12, LOW);
}
else if(f<1200 && f> 100 && g > 1200 &&g < 1500)   //REVERSE
{
  digitalWrite(r11, LOW);   
  digitalWrite(r12, HIGH);
  digitalWrite(l11, LOW);   
  digitalWrite(l12, HIGH); 
}
//////////////////////////////
 
else if (g > 1500 && f>1200 && f <1500 )          //LEFT 
{
  digitalWrite(r11, LOW);   
  digitalWrite(r12, HIGH);
  digitalWrite(l11, HIGH);   
  digitalWrite(l12, LOW); 
}
else if(g<1200 && g> 100)                       //RIGHT
{
  digitalWrite(r11, HIGH);   
  digitalWrite(r12, LOW);
  digitalWrite(l11, LOW);   
  digitalWrite(l12, HIGH); 
}
Serial.println("f");
Serial.println(f);
Serial.println("g ");
Serial.println(g);
delay(5);
}
