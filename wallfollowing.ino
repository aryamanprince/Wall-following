int trig=7,echo=6;
long duration;
int distance,setpoint=10;
float kp=0.15;//0.18
float kd=0.2,error,proportion,oldproportion;
int rightmax=200,leftmax=200,rightmotor,leftmotor;
int m11 = 10;  //for left tyre moving backward when high
int m12 = 11;  //for left tyre moving forward when high
int m21 = 3;  //for right tyre moving backward when high
int m22 = 9;  //for right tyre moving forward when high
void setup() 
{
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
}
void pid();
void motorrun();
void erroradj();
void loop()
{ /* analogWrite(m11,0);
  analogWrite(m12,leftmax);
  analogWrite(m21,0);
  analogWrite(m22,rightmax);
  */
  digitalWrite(trig,LOW);
  delayMicroseconds(10);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=(duration/2)/29.1;
  Serial.println(distance);
  pid();
}
void pid()
{ proportion=(distance-setpoint)*100;
  error=kp*proportion + kd*(proportion-oldproportion);
  oldproportion=proportion;
  erroradj();
  motorrun();
}
void erroradj()
{ if(error>200)
   error=200;
  else if(error<-200)
   error=-200;
  if(error>0)
  { rightmotor=rightmax;
    leftmotor=leftmax-error;
  }
  else if(error<0)
  { rightmotor=rightmax+error;
    leftmotor=leftmax;
  }       
  Serial.print("error=");
  Serial.println(error);
}
void motorrun()
{ 
  analogWrite(m11,0);
  analogWrite(m12,leftmotor);
  analogWrite(m21,0);
  analogWrite(m22,rightmotor);
  Serial.println(leftmotor);
  Serial.println(rightmotor);
}
