#define PIN_7 7
#define PIN_8 8
#define PIN_11 11
#define PIN_12 12


void setup()
{
  Serial.begin(9600);
  pinMode(PIN_7, OUTPUT);
  pinMode(PIN_8, OUTPUT);
  pinMode(PIN_11, OUTPUT);
  pinMode(PIN_12, OUTPUT);
  
  digitalWrite(PIN_7, LOW);
  digitalWrite(PIN_8, LOW);
  digitalWrite(PIN_11, LOW);
  digitalWrite(PIN_12, LOW);
}

//cathode is a small leg

int user_input = 0;
String input_string;

void loop()
{
  
  if (Serial.available()) {
    input_string = Serial.readStringUntil('\n');
    user_input = input_string.toInt();
    Serial.println(user_input);
  }
  
  switch(user_input) {
    // the problem with the fast blink of a wrong led is the following:
    // when I put 7 - HIHG, 8 - LOW, 11 - LOW, 12 - HIGH
    // some time passes between 7 and 12 and at this time
    // 12 is still low that's why led 2 turns on and immediately turns off
    // so we have to put digitalWrite(12) before everything 
    // I corrected everything according to this
    case 1:
      digitalWrite(PIN_12, HIGH);
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, LOW);
      digitalWrite(PIN_11, LOW);
      break;

    case 2:
      digitalWrite(PIN_11, HIGH);
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, LOW);
      digitalWrite(PIN_12, LOW);
      break; 
    
    case 3:
      digitalWrite(PIN_12, HIGH);
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_11, LOW);
      break;
	
    case 4:
      digitalWrite(PIN_11, HIGH);
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_12, LOW);
      break;
  
    case 12:
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, LOW);
      digitalWrite(PIN_11, LOW);
      digitalWrite(PIN_12, LOW);
      break;
  
    case 13:
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_11, LOW);
      digitalWrite(PIN_12, HIGH);
      break;
    
    case 14:
      // 1
      digitalWrite(PIN_12, HIGH);
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, LOW);
      digitalWrite(PIN_11, LOW);
      // 4
      digitalWrite(PIN_11, HIGH);
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_12, LOW);
      break;
    
    case 23:
      // 2
      digitalWrite(PIN_11, HIGH);
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, LOW);
      digitalWrite(PIN_12, LOW);
      // 3
      digitalWrite(PIN_12, HIGH);
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_11, LOW);
      break;
	    
    case 24:
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_11, HIGH);
      digitalWrite(PIN_12, LOW);
      break;
      
    case 34:
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_11, LOW);
      digitalWrite(PIN_12, LOW);
      break;
    
    case 123:
      // 12
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, LOW);
      digitalWrite(PIN_11, LOW);
      digitalWrite(PIN_12, LOW);
      // 3
      digitalWrite(PIN_12, HIGH);
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_11, LOW);
      break;
    
    case 234:
      // 2
      digitalWrite(PIN_11, HIGH);
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, LOW);
      digitalWrite(PIN_12, LOW);
      // 34
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_11, LOW);
      digitalWrite(PIN_12, LOW);
      break;
    
    case 341:
      // 34
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_11, LOW);
      digitalWrite(PIN_12, LOW);
      // 1
      digitalWrite(PIN_12, HIGH);
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, LOW);
      digitalWrite(PIN_11, LOW);
      break;
    
    case 412:
      // 4
      digitalWrite(PIN_11, HIGH);
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_12, LOW);
      // 12
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, LOW);
      digitalWrite(PIN_11, LOW);
      digitalWrite(PIN_12, LOW);
	  break;
    
    case 1234:
      digitalWrite(PIN_7, HIGH);
      digitalWrite(PIN_8, HIGH);
      digitalWrite(PIN_11, LOW);
      digitalWrite(PIN_12, LOW);
      break;
    
    default:
      digitalWrite(PIN_7, LOW);
      digitalWrite(PIN_8, LOW);
      digitalWrite(PIN_11, LOW);
      digitalWrite(PIN_12, LOW);
      break;
    
  }
   
  //delay(1);

}




