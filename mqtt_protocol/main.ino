#define sensor_pin A0

int led_pin = 2; // 13 for arduino

void setup() {
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  if (Serial.available() > 0){    // u = up, on
    char cmd = Serial.read();
    if (cmd == 'u'){
      digitalWrite(led_pin, HIGH);
      Serial.print("led on");
    }
    if (cmd == 'd'){    	 // d = down, off
      digitalWrite(led_pin, LOW);
      Serial.print("led off");
    }
  }
}

