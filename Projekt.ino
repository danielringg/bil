#define RIGHT_RELAY_PIN 7
#define LEFT_RELAY_PIN 6
//definierar inputen till båda relayerna som pin 7 och 6

//de tre sensorerna skickar sin signal till pinsen 8, 9 och 10
int sensorPinForward = 8;
int sensorPinRight = 9;
int sensorPinLeft = 10;
int val;

//I setupen definierar jag relaysen till outputs och sensorerna till inputs. Jag sätter även igång serial monitorn så jag kan hålla koll på vad som händer när jag testkör och lättare felsöka.
void setup() {
  pinMode(RIGHT_RELAY_PIN, OUTPUT);
  pinMode(LEFT_RELAY_PIN, OUTPUT);
  pinMode(sensorPinForward,INPUT);
  pinMode(sensorPinRight,INPUT);
  pinMode(sensorPinLeft,INPUT);
  Serial.begin(9600);
}
  
void loop() {
  //valF, valR och valL är variabler som beror på vilken signal sensorerna skickar. 
  int valF = analogRead(sensorPinForward);
  int valR = digitalRead(sensorPinRight);
  int valL = digitalRead(sensorPinLeft);
  Serial.print(valF + "   "); 
  Serial.print(valR + "   "); 
  Serial.print(valL + "   "); 
  
  if (valF == HIGH and valL == LOW and valR == LOW) {  //om valF är hög och de andra är låga innebär det att bilen känner av en linje framför sig och därför använder den funktionen drive(), jag skriver även ut "line detected forwards" i serial monitorn.
    //Serial.println("Line detected FORWARDS"); 
    drive();
  } 
  else if (valR == HIGH and valL == HIGH and valF == HIGH) { // om alla värden är höga känner bilen av linjen i alla riktningar och därför kör den framåt
    //Serial.println("Line detected [in all directions??]");
    drive();
  }
  else if (valR == HIGH and valL == LOW) { // om valR är HIGH och valL är LOW innebär det att den känner av en linje till höger och inte något till vänster, därför ska den svänga höger med hjälp av funktionen turnRight()
    //Serial.println("Line detected RIGHT");
    turnRight();
  }
  else if (valL == HIGH and valR == LOW) { // om valL är HIGH och valR är LOW känner bilen av att linjen svänger och därför svänger den vänster med hjälp av funktionen turnLeft().
    //Serial.println("Line detected LEFT");
    turnLeft();
  }
  else if (valL == HIGH and valR == HIGH and valF == LOW) { // om sensorerna känner av linjen på både höger och vänster sida kör den framåt.
    //Serial.println("Line detected left and right?");
    drive();
  }
  else { // om den inte känner av någon linje alls stannar bilen med funktionen brake()
    //Serial.println("Line not detected"); 
    brake();
  }
}

void drive(){ //denna funktionen skriver HIGH till båda relays vilket gör att båda motorerna kör (det funkade inte med HIGH men det gör det med LOW)
  digitalWrite(RIGHT_RELAY_PIN, LOW);
  digitalWrite(LEFT_RELAY_PIN, LOW);
  delay(10);
} 
void brake(){ //denna funktionen gör motsatsen till drive(), alltså stannar båda motorerna
  digitalWrite(RIGHT_RELAY_PIN, HIGH);
  digitalWrite(LEFT_RELAY_PIN, HIGH);
  delay(10);
}
void turnLeft(){ //här kör den högra motorn men inte den vänstra vilket skapar en svängade effekt
  digitalWrite(RIGHT_RELAY_PIN, HIGH);
  digitalWrite(LEFT_RELAY_PIN, LOW);
  delay(10);
}
void turnRight(){ //här kör den vänstra motorn men inte den högra vilket skapar en svängade effekt
  digitalWrite(RIGHT_RELAY_PIN, LOW);
  digitalWrite(LEFT_RELAY_PIN, HIGH);
  delay(10);
}
