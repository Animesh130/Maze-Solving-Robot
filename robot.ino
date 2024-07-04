int in4 = 5;         //might need to exchange 5 and 6
int in3 = 6;
int motor_enableA = 11;

int in2 = 8;               //might need to exchange 8 and 10
int in1 = 10;
int motor_enableB = 3;

int trigger_front = A3;
int echo_front = A2;

int trigger_left = A4;
int echo_left = A5;

int trigger_right = A0;
int echo_right = A1;

int threshold = 40;
int fthreshold = 20;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(in4,OUTPUT);   //left motors forward
  pinMode(in3,OUTPUT);   //left motors reverse
  pinMode(motor_enableA, OUTPUT);

  pinMode(in2,OUTPUT);   //right motors forward
  pinMode(in1,OUTPUT);   //rignt motors reverse
  pinMode(motor_enableB, OUTPUT);

  pinMode(trigger_front,OUTPUT);
  pinMode(echo_front,INPUT);

  pinMode(trigger_left,OUTPUT);
  pinMode(echo_left,INPUT);

  pinMode(trigger_right,OUTPUT);
  pinMode(echo_right,INPUT);
  
                     // can enter value from 0 to 255 , to control speed
  

}

void loop() {
  // put your main code here, to run repeatedly:

  analogWrite(motor_enableA, 165);                //bcoz right motor ki speed temporarily change hogi
  analogWrite(motor_enableB, 150);
  
  long duration_front, distance_front, duration_left, distance_left, duration_right, distance_right,error;
    
  //Calculating distance
  
  distance_front= getDistance(trigger_front,echo_front);

  
  distance_left= getDistance(trigger_left,echo_left);

  
  distance_right= getDistance(trigger_right,echo_right);

  error = distance_left-distance_right;

 
 if (distance_left > threshold) {
    left();
    forward(900);
 }

   else if (distance_front > fthreshold) {

    if (distance_left!=0 && distance_right!=0 && distance_left<threshold && distance_right<threshold){
      if(error>0){
         analogWrite(motor_enableA,200+error);
         delay(125);
         analogWrite(motor_enableA,165);}

      else if(error<0){
        analogWrite(motor_enableB,200-error);
        delay(125);
        analogWrite(motor_enableB,150);
      }
    }

    forward(200);
    

    

  } else if (distance_right > threshold) {
    right();
    forward(900);
    }
  

  else {
    uTurn(error);
    stop(2000);
  }

 }

void forward(int fwdtime)
{
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in1,LOW);
  delay(fwdtime);
}


void right(){
  delay(400);                //detect karne ke baad bhi thodi der aage chale
  digitalWrite(in4,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in1,HIGH);
 delay(1100);               //kitni der wheels turn honge
}


void left(){
  delay(1100);
  digitalWrite(in4,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in2,HIGH);
  digitalWrite(in1,LOW);
  delay(1100);
}



void uTurn(int error)  {
  if (error>=0){
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  delay(2500);}

  if (error<0){
  digitalWrite(in4, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
  delay(2500);}

}


int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  int distance = duration * 0.034 / 2;

  return distance;
}



void stop(int stopTime){
  digitalWrite(in4,0);
  digitalWrite(in3,0);
  digitalWrite(in2,0);
  digitalWrite(in1,0);
  delay(stopTime);
}




  
  
    

   
