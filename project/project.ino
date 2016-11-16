int capteur = A0;
int led1= 3;
int led2=4;
int led3=5;
const int outPin = 9;
const float maxFreq = 16000000;
float freqq = 0.1;
float add = 0 ;
float moy = 0;
void setup() {
  
 Serial.begin(115200);
  pinMode(outPin,OUTPUT);
 pinMode(capteur, INPUT);
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
 setFrequency(100000);
}

void loop() {
 for(int i = 1 ; i < 160;i++)
 {
  setFrequency(100000*i);
  int etatcapteur = analogRead(capteur);
 // Serial.print("freq=");
  freqq = 0.1*i;
 // Serial.print(float(freqq));
  
  //Serial.print("Ghz       ");
  //Serial.println(etatcapteur);
  add=add+etatcapteur;
 // delay(100);


}

//Serial.println(add);
moy=add/160;
Serial.println(moy);
if(moy>24)
{
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
 // Serial.println("main");
}
else if (moy>18)
{
digitalWrite(led1,HIGH);
digitalWrite(led2,HIGH);
digitalWrite(led3,LOW);
//Serial.println("deux doigts");
}
else if (moy>3)
{
digitalWrite(led1,HIGH);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);
//Serial.println("1 doigt");
}
else
{
  digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);
 //Serial.println("rien");
}

add=0;
}



void setFrequency(float frequency)
{
 
  if(frequency >=0.24 || frequency <=16000000)
  {
    
    TCCR1A=0b10000010;        // Set up frequency generator, mode 14 (Fast PWM)
    //WGM11 = 1, COM1A1 = 1
    //Fast PWM: TOP=ICR1, update of OCR1x=BOTTOM, TOV1 Flag Set on TOP
    
  
    unsigned int v=0;
    int indscale=0;
    float prescale[] = {1.0,8.0,64.0,256.0,1024.0};
    float period=1/frequency;
    
    while(v==0)
    {
      float curfreq=maxFreq/prescale[indscale];
      float tickperiod=1/curfreq;
      float nbtick=period/tickperiod;
     
      if(nbtick>65535)
      {
        indscale=indscale+1;
      }
      else
      {
        v=nbtick;
      }

    }
    
    int c=prescale[indscale];
    
     switch (c) {
      
         case 1: TCCR1B=0b00011001; break;
         case 8: TCCR1B=0b00011010; break;
         case 64: TCCR1B=0b00011011; break;
         case 256: TCCR1B=0b00011100; break;
         case 1024: TCCR1B=0b00011101; break;
         default: TCCR1B=0b00011000;
     }
    
  
    
    ICR1=v; //pulse duration = ICR1 value x time per counter tick
   
    
    OCR1A=v/2; //Output Compare Register //low state

  }
  
  
}
