#define PIN_A0 A0
#define PIN_2 2


bool send_one_value = false;
bool streaming = false;
long send_count;

int current_luminocity;
int previous_luminocity;
int switch_threshold = 10;  // experimentally

bool manually_enable_led = false;
bool manually_disable_led = false;

bool signalization_mode_enabled = false;


void setup()
{
  Serial.begin(9600);
  pinMode(PIN_2, OUTPUT);
}


void loop()
{
  long current_time = millis();
  //Serial.println(String(current_time) + " "
  //               + String(current_time / 100));
  
  read_data();
  
  if (send_one_value) {
    send_photo_data();
    send_one_value = false;
  } else if(streaming && current_time / 100 != send_count) {
    send_photo_data();
    
    // Ex. If send_count = 11 (1193) and current_time / 100 = 12 (1203)
    // that means that 100 milliseconds have passed
	send_count = current_time / 100;
    
    Serial.println("Time: " + String(millis()));
    Serial.println("Proceed to the next iteration\n");
  }
  
  
  // tasks
  // 2) auto mode
  current_luminocity = analogRead(PIN_A0);
  if (current_luminocity <= switch_threshold && previous_luminocity >= switch_threshold && !signalization_mode_enabled) {
    manually_enable_led = false;
    manually_disable_led = false;
    // Serial.println(!signalization_mode_enabled);
    Serial.println(previous_luminocity >= switch_threshold);
    digitalWrite(PIN_2, HIGH);
  } else if (current_luminocity > switch_threshold && previous_luminocity < switch_threshold && !signalization_mode_enabled) {
    manually_enable_led = false;
    manually_disable_led = false;
    digitalWrite(PIN_2, LOW);
  }
  previous_luminocity = current_luminocity;
  
  
  // 3) manual mode
  if (manually_enable_led) {
    Serial.println("User is turning on the led");
    signalization_mode_enabled = false;
    digitalWrite(PIN_2, HIGH);
  } else if (manually_disable_led) {
    Serial.println("User is turning off the led");
    signalization_mode_enabled = false;
    digitalWrite(PIN_2, LOW);
  }
  
  
  // 4) signalization
  if (signalization_mode_enabled) { 
    if (current_time / 1000 != send_count) {
      manually_enable_led = false;
      manually_disable_led = false;
      Serial.println("Signalization (led's turning on)");
      send_count = current_time / 1000;
      digitalWrite(PIN_2, HIGH);
  	} else {
      Serial.println("Signalization (led's turning off)");
      digitalWrite(PIN_2, LOW);
    }
  }

  delay(10);
}


void send_photo_data(){
  int value = analogRead(PIN_A0);
  Serial.println("Value: " + String(value));
}


void read_data() {
  if (Serial.available()){
    char command = Serial.read();
    switch (command) {
      case 's':
        send_one_value = true;
        streaming = false;
        break;
      case 'p':
        streaming = true;
        break;
      // enable led manually
      case 'q':
        manually_enable_led = true;
        manually_disable_led = false;
      	break;
      // disable led manually + disable when signalization works
      case 'd':
        manually_disable_led = true;
        manually_enable_led = false;
        break;
      // start signalization
      case 'a':
        signalization_mode_enabled = true;
        manually_disable_led = false;
        manually_enable_led = false;
        break;
      default:
        streaming = false;
        break;
    }
  }
}