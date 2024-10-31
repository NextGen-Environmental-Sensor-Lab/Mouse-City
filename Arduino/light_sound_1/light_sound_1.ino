// light and sound sketch for City Mouse experiment
// Gurleen Hothi, Ricardo Toledo-Crow, ASRC CUNY, Sep 2024
// Flashes led strip and plays sound


#include <Adafruit_NeoPixel.h>

#define NPPIN D5       // Activation pin for Neopixels
#define WAVPIN D0      // Audio Track
#define WAVPIN1 D6     // Audio Track
#define WAVPIN2 D7     // Audio Track
#define WAVPIN3 D8     // Audio Tracks not used
#define VOLUP D1       //  Volume
#define VOLDOWN D2     //  Volume
#define VOL_LIMIT 100  // Volume Limit
#define NUMPIXELS 144  // Popular NeoPixel ring size
#define DELAYVAL 100   // Time (in milliseconds) to pause between pixels


String inputString = "";
bool stringComplete = false;

Adafruit_NeoPixel pixels(NUMPIXELS, NPPIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(8000);
  Serial.println(__FILE__);

  pinMode(WAVPIN, OUTPUT);  // Set wavpin to 5V
  digitalWrite(WAVPIN, HIGH);

  pinMode(WAVPIN1, OUTPUT);  // Set wavpin1 to 5V
  digitalWrite(WAVPIN1, HIGH);

  pinMode(WAVPIN2, OUTPUT);  // Set wavpin2 to 5V
  digitalWrite(WAVPIN2, HIGH);

  pinMode(WAVPIN3, OUTPUT);  // Set wavpin3 to 5V
  digitalWrite(WAVPIN3, HIGH);

  pinMode(VOLDOWN, OUTPUT);  // Set VOLUP pin to 5V
  digitalWrite(VOLDOWN, HIGH);

  pinMode(VOLUP, OUTPUT);  // Set VOLDOWN pin to 5V
  digitalWrite(VOLUP, HIGH);

  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();   // Initialize all pixels to 'off'

  inputString.reserve(200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Enter Commands :");  //Reserves 200 bits of memory
}

void loop() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();  //Read input for commands
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
      Serial.print(inputString);
    }

    if (stringComplete) {
      parseCommand(inputString);
      inputString = "";
      stringComplete = false;  // Continuously reads the Serial for inputs
    }
  }
}

void parseCommand(String command) {
  // Remove any trailing newline or carriage return characters
  command.trim();

  // Check for specific commands and execute accordingly
  if (command == "LED ON") {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LED turned ON");
  } else if (command == "LED OFF") {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED turned OFF");
  } else if (command.startsWith("SET PWM ")) {
    // Example command: SET PWM 128
    int pwmValue = command.substring(8).toInt();  // Extract the value after "SET PWM "
    analogWrite(LED_BUILTIN, pwmValue);
    Serial.print("PWM set to: ");
    Serial.println(pwmValue);  //?
  } else if (command.startsWith("PLAY0")) {
    // execute Sound()
    Sound(WAVPIN);
  } else if (command.startsWith("PLAY1")) {
    // execute Sound()
    Sound(WAVPIN1);
  } else if (command.startsWith("PLAY2")) {
    // execute Sound()
    Sound(WAVPIN2);
  } else if (command.startsWith("LIGHTON")) {
    // execute lighton()
    lighton(WAVPIN2);
  } else if (command.startsWith("LIGHTOFF")) {
    // execute lightoff()
    lightoff(WAVPIN2);
  } else if (command.startsWith("LIGHTLR")) {
    // execute lightLR()
    lightLR(WAVPIN2);
  } else if (command.startsWith("VOLUP")) {
    // execute Volume()
    Volume(VOLUP);
  } else if (command.startsWith("VOLDOWN")) {
    // execute Volume()
    Volume(VOLDOWN);
  } else {
    // Handle unknown commands
    Serial.print("Unknown command: ");
    Serial.println(command);
  }
}

// turn off all pixels
void lightoff(int wav) {
  pixels.clear();
  pixels.show();
}

// turn on all pixels to max values
void lighton(int wav) {
  static uint32_t maxWhite = pixels.Color(255, 255, 255, 255);
  for (int c = 0; c < pixels.numPixels(); c++) {
    pixels.setPixelColor(c, maxWhite);  // Set pixel 'c' to value 'color'
  }
 pixels.show();
}

void lightLR(int wav) {
  // start lights
  theaterChase(pixels.Color(255, 255, 255, 255), 6, 52);  // LED light on (Left to Right)
  pixels.show();
  pixels.clear();
}

void Sound(int wav) {
  // start sound
  pinMode(wav, OUTPUT);  // Play audio track
  digitalWrite(wav, LOW);
  delay(300);
  digitalWrite(wav, HIGH);
}

void lightSound(int wav) {
  // start sound
  pinMode(wav, OUTPUT);
  digitalWrite(wav, LOW);  // Play audio track
  delay(300);
  digitalWrite(wav, HIGH);
  // start lights
  theaterChase(pixels.Color(255, 255, 255, 255), 6, 52);  // LED light on (L to R 20seconds)
  pixels.show();
  pixels.clear();
  delay(500);
  theaterChase(pixels.Color(0, 0, 0, 0), 6, 52);
}

void Volume(int updown) {
  // start sound
  pinMode(updown, OUTPUT);
  for (int i = 0; i < VOL_LIMIT; i++) {  //Adjust speaker volume
    digitalWrite(updown, LOW);
    delay(50);
    digitalWrite(updown, HIGH);
    delay(50);
    digitalWrite(updown, LOW);
    delay(50);
    digitalWrite(updown, HIGH);
  }
}

void theaterChase(uint32_t color, int gap, int wait) {  //light control
  for (int a = 0; a < 60; a++) {                        // Repeat 10 times...
    for (int b = 0; b < gap; b++) {                     //  'b' counts from 0 to 2...
      pixels.clear();                                   //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < pixels.numPixels(); c += gap) {
        pixels.setPixelColor(c, color);  // Set pixel 'c' to value 'color'
      }
      pixels.show();  // Update strip with new contents
      delay(wait);    // Pause for a moment
    }
  }
}
