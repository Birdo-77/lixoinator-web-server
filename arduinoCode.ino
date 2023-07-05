#include <Keypad.h> // Teclado
#include <Servo.h> // Servo Motor
#include <TM1637Display.h> // Display
#include <Ultrasonic.h> // Sensor de Prox.

// Config Sensor
#define pino_trigger A0
#define pino_echo A1
Ultrasonic ultrasonic(pino_trigger, pino_echo);
float TempoEcho = 0;
const float VelocidadeSom_mpors = 340; // em metros por segundo
const float VelocidadeSom_mporus = 0.000340; // em metros por microsegundo

#define CLK 11
#define DIO 12
TM1637Display display(CLK, DIO);

// Config do Servo
const int SERVO = 10;
const int SERVO2 = 13;
Servo s;
Servo s2;

// Define a configurações do teclado
const byte ROWS = 4; 
const byte COLS = 4;

int analogPin = A0;
int val = 0;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Ler os numeros digitados
int typedKeys[4] = {0, 0, 0, 0};
int index = 0;

bool checkMetal = false;
bool openServo2 = false;

void setup(){
  display.setBrightness(0x0f);
  
  display.showNumberDec(0000, false);
  s.attach(SERVO);
  s2.attach(SERVO2);
  s.write(180);
  s2.write(90);
  
  pinMode(pino_trigger, OUTPUT);
  digitalWrite(pino_trigger, LOW);
  pinMode(pino_echo, INPUT);
  
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  // Le a tecla apertada
  if (customKey && !checkMetal){
    if (index < 4){
      typedKeys[index] = (int)customKey - 48;
      index++;
    }
    if (index >= 4){
      String pass = "";
      for (int x = 0; x < 4; x++){
        pass += String(typedKeys[x]);
      }
      Serial.println(pass);
      while (true){
        if (Serial.available() > 0) {
          String data = Serial.readStringUntil('\n');
          delay(100);
          if (data == "s1"){
            s.write(80);
            checkMetal = true;
            index = 0;
            break;
          } else if(data == "wps"){
            delay(100);
            index = 0;
            break;
          }
        }
      }
    }
  showKeys();
  }
  
  if (checkMetal){
    digitalWrite(pino_trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pino_trigger, LOW);
    TempoEcho = pulseIn(pino_echo, HIGH);
    openServo(CalculaDistancia(TempoEcho)*100);
    delay(200);
  }
}

void showKeys(){
  int num = 0;
  for (int x = 0; x < 4; x++){
      if (index > x){
        num *= 10;
        num += typedKeys[x];
      }
    }
  display.showNumberDec(num, false);
}

void openServo(float d){
  if (d < 30.0){
    Serial.println("s");
    s2.write(0);
    checkMetal = false;
    delay(3000);
    s.write(180);
    s2.write(90);
    showKeys();
  }
}

float CalculaDistancia(float tempo_us){
  return((tempo_us*VelocidadeSom_mporus)/2);
}
