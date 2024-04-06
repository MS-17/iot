#define PIN_7 7
#define PIN_8 8
#define PIN_11 11
#define PIN_12 12


int rowsStates[2][2] = {{0, 1}, {1, 0}};


void setup() 
{
  Serial.begin(9600);
  pinMode(PIN_7, OUTPUT);
  pinMode(PIN_8, OUTPUT);
  pinMode(PIN_11, INPUT_PULLUP);
  pinMode(PIN_12, INPUT_PULLUP);
  
  digitalWrite(PIN_7, LOW);
  digitalWrite(PIN_8, LOW);
  delay(3);
}



void loop()
{
  bool btn_pressed[4]{0, 0, 0, 0};
  for (int i = 0; i < 2; i++) {
    digitalWrite(PIN_7, rowsStates[i][0]);
    digitalWrite(PIN_8, rowsStates[i][1]);
    for (int i = 0; i < 4; i++){
      int row = digitalRead(i < 2 ? PIN_7 : PIN_8);
      int col = digitalRead(i % 2 == 0 ? PIN_11 : PIN_12);
      if (row == 0 && col == 0) {
        btn_pressed[i] = true;
      }
    }
  }
  
  bool pressedOnce = true;
  for (int i = 0; i < 4; i++) {
    if (btn_pressed[i]) {
      // to display the phrase only once
      if (pressedOnce) {
        Serial.println("\nPressed button: ");
        pressedOnce = false;
      }
      Serial.print(i + 1);
      delay(200);
    }
  }
  
  delay(100);
  //Serial.println("end loop");
}




