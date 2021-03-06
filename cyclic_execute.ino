//Define pins
int SIGNALAPIN = 14;
int SIGNALBPIN = 2;
int analog_input = 4;
int digital_input = 12;

//Define variables used
int error_code = 0;
int average_analogue_in = 0;
int inputvalue = 0;
int analogvals[4] = {0,0,0,0}; 
int signalbdelay = 0.05 * 10;
int digitalval = 0;
int count = 0;
int timer = 0;
int frequency = 0;

void setup() {
  
  //Pins setup
  Serial.begin(9600);
  pinMode(SIGNALAPIN, OUTPUT);
  pinMode(SIGNALBPIN,OUTPUT);
  pinMode(analog_input,INPUT);
  pinMode(digital_input,INPUT);

}

//Cyclic execute of the tasks
void loop() {

  timer++;
  Task1();
  if (timer % 10 == 0){Task2();}
  if (timer % 50 == 0){Task3();}
  if (timer % 2 == 0){Task4(); Task5();}
  if (timer % 5 == 0){Task6();}
  if (timer % 16 == 0){Task7(); Task8();}
  if (timer % 250 == 0){Task9();}
  
}

void Task1(){
  
  //Create signal B
  digitalWrite(SIGNALBPIN,HIGH);
  delay(signalbdelay);
  digitalWrite(SIGNALBPIN,LOW);
  
}

//Read digital input
void Task2(){

  digitalval = digitalRead(digital_input);
  
}


void Task3(){
  
}

//Read the analog input and save them into a size 4 array to calculate average
void Task4(){

  analogvals[count] = analogRead(analog_input);
  count++;
  if (count = 4){
    count = 0;
  }
  
}

//Calculate the average of the analog input
void Task5(){
  int sum = 0;
  for(int i = 0; i < 4;i++){
    sum = sum + analogvals[i];
  }

  average_analogue_in = sum/4;
  
}

void Task6(){
  for (int i = 0; i < 1000; i++){
    __asm__ __volatile__ ("nop");
  }
}
//To make sure that the method works properly, the value used is 1000 however the half of the maximum value is 2047.5
//Check there is no error
void Task7(){

  if (average_analogue_in > 1000){
    error_code = 1;
  }
    
  else{
    error_code = 0;
  }

    
}

//Turn LED on or off depending on error
void Task8(){

  if (error_code == 1){
    digitalWrite(SIGNALAPIN,HIGH);
  }
    
  else{
    digitalWrite(SIGNALAPIN,LOW);
  }
  
}

//Print information obtained from the previous tasks
void Task9(){
  
  Serial.print("Digital value: ");
  Serial.println(digitalval);
  Serial.print("Frequency: ");
  Serial.println(frequency);
  Serial.print("Average: ");
  Serial.println(average_analogue_in);
  
}
