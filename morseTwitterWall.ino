int led = 11;
boolean DEBUG = true;

String message = "";
int messageSpeed = 100;

String tweetUser;
String tweetContent;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT); 
}

void loop() {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(200);

  boolean readANewTweet = readTweet();

  digitalWrite(led, readANewTweet ? HIGH : LOW);
  delay(1000);
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);

  for (int i = 0; i < message.length(); i++) {
    String morse = morseConvert(message.charAt(i));

    if (DEBUG) {
      Serial.print("char = ");
      Serial.print(message.charAt(i));
      Serial.print(", morse = ");
      Serial.print(morse);
      Serial.print("\n");
      Serial.flush();
    }

    for (int j = 0; j < morse.length(); j++) {
      if (morse.charAt(j) == '.') {
        digitalWrite(led, HIGH);
        delay(messageSpeed);
        digitalWrite(led, LOW);
        delay(messageSpeed);
      } 
      else if (morse.charAt(j) == '-') {
        digitalWrite(led, HIGH);
        delay(3 * messageSpeed);
        digitalWrite(led, LOW);
        delay(messageSpeed);
      } 
      else if (morse.charAt(j) == '*') {
        digitalWrite(led, LOW);
        delay(2 * messageSpeed); 
      }
    }

    delay(2 * messageSpeed);
  }

  delay(15 * messageSpeed);
}

boolean readTweet() {
  String inputString = "";
  int charCount = 0;

  while (Serial.available()) {
    char inChar = (char) Serial.read();
    inputString += inChar;
    ++charCount;

    if (inChar == '\n') {
      break;
    } 
  }

  if (charCount > 0) {
    message = inputString;
  }

  if (DEBUG) {
    Serial.print("message = ");
    Serial.println(message);  
  }

  return charCount > 0;
}





String morseConvert(char c) {
  // Convert to lower-case; just so we don't have to enter each letter twice.
  if (c >= 'A' && c <= 'Z') {
    c += 32; 
  }

  switch (c) {
  case 'a':
    return ".-";
  case 'b':
    return "-...";
  case 'c':
    return "-.-.";
  case 'd':
    return "-..";
  case 'e':
    return ".";
  case 'f':
    return "..-.";
  case 'g':
    return "--.";
  case 'h':
    return "....";
  case 'i':
    return "..";
  case 'j':
    return ".---";
  case 'k':
    return "-.-";
  case 'l':
    return ".-..";
  case 'm':
    return "--";
  case 'n':
    return "-.";
  case 'o':
    return "---";
  case 'p':
    return ".--.";
  case 'q':
    return "--.-";
  case 'r':
    return ".-.";
  case 's':
    return "...";
  case 't':
    return "-";
  case 'u':
    return "..-";
  case 'v':
    return "...-";
  case 'w':
    return ".--";
  case 'x':
    return "-..-";
  case 'y':
    return "-.--";
  case 'z':
    return "--..";
  case '1':
    return ".----";
  case '2':
    return "..---";
  case '3':
    return "...--";
  case '4':
    return "....-";
  case '5':
    return ".....";
  case '6':
    return "-....";
  case '7':
    return "--...";
  case '8':
    return "---..";
  case '9':
    return "----.";
  case '0':
    return "-----";
  case ' ':
    // Specify that we need to insert some extra time.
    return "*";
  case '.':
    return ".-.-.-";
  case ',':
    return "--..--";
  case '?':
    return "..--..";
  case '\'':
    return ".----.";
  case '!':
    return "-.-.--";
  case '/':
    return "-..-.";
  case '(':
    return "-.--.";
  case ')':
    return "-.--.-";
  case '&':
    return ".-...";
  case ':':
    return "---...";
  case ';':
    return "-.-.-.";
  case '=':
    return "-...-";
  case '+':
    return ".-.-.";
  case '-':
    return "-....-";
  case '"':
    return ".-..-.";
  default:
    return "........";  // Just ignore it.
  } 
}


