

int hitCount = 0;
void setup() {
  //player 1 (left player)

  //red
  pinMode(38,INPUT);
  //yellow
  pinMode(39,INPUT);

  //down
  pinMode(40,INPUT);
  //right
  pinMode(41,INPUT);
  //up
  pinMode(42,INPUT);
  //left
  pinMode(43,INPUT);
 

  
  // player 2 (right player)
  //yellow
  pinMode(46,INPUT);
  //left
  pinMode(47,INPUT);
  //down
  pinMode(48,INPUT);
  //red
  pinMode(49,INPUT);
  //right
  pinMode(50,INPUT);
  //up
  pinMode(51,INPUT);

  
  Serial.begin(9600);

}

void loop() {
  int val14 = digitalRead(38);
  int val15 = digitalRead(39);
  int val0 = digitalRead(40);
  int val1 = digitalRead(41);
  int val2 = digitalRead(42);
  int val3 = digitalRead(43);

  int val6 = digitalRead(46);
  int val7 = digitalRead(47);
  int val8 = digitalRead(48);
  int val9 = digitalRead(49);
  int val10 = digitalRead(50);
  int val11 = digitalRead(51);
 // int val12 = digitalRead(52);
 // int val13 = digitalRead(53);
  
  
  //Serial.println(val);
  if(val0 == LOW)
  {
    hitCount++;
    Serial.println("val0");
    //Serial.println(hitCount);
    
  }
  
  if(val1 == LOW)
  {
    hitCount++;
    Serial.println("val1");
    //Serial.println(hitCount);
    
  }
  
  if(val2 == LOW)
  {
    hitCount++;
    Serial.println("val2");
    //Serial.println(hitCount);
    
  }
  
  if(val3 == LOW)
  {
    hitCount++;
    Serial.println("val3");
    //Serial.println(hitCount);
    
  }
  

if(val6 == LOW)
  {
    hitCount++;
    Serial.println("val6");
    //Serial.println(hitCount);
    
  }
  if(val7 == LOW)
  {
    hitCount++;
    Serial.println("val7");
    //Serial.println(hitCount);
    
  }
  if(val8 == LOW)
  {
    hitCount++;
    Serial.println("val8");
    //Serial.println(hitCount);
    
  }

  
  if(val9 == LOW)
  {
    hitCount++;
    Serial.println("val9");
    //Serial.println(hitCount);
    
  }
  
  if(val10 == LOW)
  {
    hitCount++;
    Serial.println("val10");
    //Serial.println(hitCount);
    
  }
  
  if(val11 == LOW)
  {
    hitCount++;
    Serial.println("val11");
    //Serial.println(hitCount);
    
  }
  if(val14 == LOW)
  {
    hitCount++;
    Serial.println("val14");
    //Serial.println(hitCount);
    
  }
  if(val15 == LOW)
  {
    hitCount++;
    Serial.println("val15");
    //Serial.println(hitCount);
    
  }

  
  
  //delay(50);

}
