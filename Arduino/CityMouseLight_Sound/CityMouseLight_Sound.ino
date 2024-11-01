// light and sound sketch for City Mouse experiment
// Gurleen Hothi, Ricardo Toledo-Crow, ASRC CUNY, Sep 2024
// Flashes led strip and plays sound


#include <Adafruit_NeoPixel.h>

#define NPPIN D5       // Activation pin for Neopixels
#define WAVPIN D0      // Audio Track Pin
#define WAVPIN1 D6     //
#define WAVPIN2 D7     //
#define WAVPIN3 D8     // Extra Audio Track Pin Not Used
#define VOLUP D1       //  Volume Up Pin
#define VOLDOWN D2     //  Volume Down Pin
#define VOL_LIMIT 100  // Volume Limit
#define NUMPIXELS 144  // NeoPixel strip size
#define DELAYVAL 100   // Time (in milliseconds) to pause between pixels


String inputString = "";
bool stringComplete = false;

Adafruit_NeoPixel pixels(NUMPIXELS, NPPIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(8000);
  Serial.println(__FILE__);

  // Set wavpins and volume pins to 3.3V
  pinMode(WAVPIN, OUTPUT);
  digitalWrite(WAVPIN, HIGH);

  pinMode(WAVPIN1, OUTPUT);
  digitalWrite(WAVPIN1, HIGH);

  pinMode(WAVPIN2, OUTPUT);
  digitalWrite(WAVPIN2, HIGH);

  pinMode(WAVPIN3, OUTPUT);
  digitalWrite(WAVPIN3, HIGH);

  pinMode(VOLDOWN, OUTPUT);
  digitalWrite(VOLDOWN, HIGH);

  pinMode(VOLUP, OUTPUT);
  digitalWrite(VOLUP, HIGH);

  pixels.begin();  // INITIALIZE NeoPixel strip (REQUIRED)
  pixels.show();   // Initialize all pixels to 'off'

  inputString.reserve(200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Enter Commands :");  //Reserves 200 bits of memory
}

void loop() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();  //Continuously reads input for commands
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
      Serial.print(inputString);
    }

    if (stringComplete) {
      parseCommand(inputString);
      inputString = "";
      stringComplete = false;  // Passes completed string
    }
  }
}

// Remove any trailing newline or carriage return characters
void parseCommand(String command) {

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
    Sound(WAVPIN1);
  } else if (command.startsWith("PLAY2")) {
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

// move pixels left to right three pixels every move
void lightLR(int wav) {
  theaterChase(pixels.Color(255, 255, 255, 255), 6, 52);
  pixels.show();
  pixels.clear();
}

// start track audio
void Sound(int wav) {
  pinMode(wav, OUTPUT);
  digitalWrite(wav, LOW);
  delay(300);
  digitalWrite(wav, HIGH);
}

//Adjust speaker volume
void Volume(int updown) {
  // start sound
  pinMode(updown, OUTPUT);
  for (int i = 0; i < VOL_LIMIT; i++) {
    digitalWrite(updown, LOW);
    delay(50);
    digitalWrite(updown, HIGH);
    delay(50);
    digitalWrite(updown, LOW);
    delay(50);
    digitalWrite(updown, HIGH);
  }
}

//light control
void theaterChase(uint32_t color, int gap, int wait) {
  for (int a = 0; a < 60; a++) {     //Repeat 60 times
    for (int b = 0; b < gap; b++) {  //'b' counts from 0 to 2
      pixels.clear();                //Set all pixels in RAM to 0 (off)

      // 'c' counts up from 'b' to the end of strip in steps of 3
      for (int c = b; c < pixels.numPixels(); c += gap) {
        pixels.setPixelColor(c, color);  // Set pixel 'c' to value 'color'
      }
      pixels.show();  // Update strip with new contents
      delay(wait);    // Pause for a moment
    }
  }
}
