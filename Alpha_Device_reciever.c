#include <Arduino_MKRIoTCarrier.h>
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>
#include "thingProperties.h" // Include thingProperties.h which should define buttonState

MKRIoTCarrier carrier;
const int relayPin = 5; // Define the pin connected to the relay
const int BUTTON_PIN = 3; // Define the pushbutton pin

int lastButtonState = HIGH; // Variable to store previous button state
unsigned long lastDebounceTime = 0; // Last time the output pin was toggled
unsigned long debounceDelay = 50; // Debounce time in milliseconds

void setup() {
  Serial.begin(9600);
  delay(1500);
  carrier.begin();
  pinMode(A1, OUTPUT); // Pin for local LED control
  pinMode(relayPin, OUTPUT); // Pin for relay control
  digitalWrite(relayPin, LOW); // Ensure relay is off initially
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Initialize the pushbutton pin as input with internal pull-up resistor
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  carrier.Buttons.update();

  // Read the state of the physical button
  int reading = digitalRead(BUTTON_PIN);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    // Reset the debounce timer
    lastDebounceTime = millis();
  }

  // After debounce delay, check the button state again
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has changed, update the button state
    if (reading != buttonState) {
      buttonState = !buttonState;

      // If the button state is LOW, the button is pressed
      if (buttonState == 1) {
        Serial.println("Physical button pressed!");
        // Perform actions on button press
        onButtonStateChange();
      }
    }
  }

  // Update lastButtonState with the current reading for the next loop iteration
  lastButtonState = reading;

  // Check if the capacitive button (TOUCH0) is touched
  if (carrier.Buttons.onTouchDown(TOUCH0)) {
    Serial.println("Touching Button 0");
    buttonState = !buttonState;
    onButtonStateChange();
  }
}

void onButtonStateChange() {
  // Toggle the local LED (A1 pin)
  digitalWrite(A1, !digitalRead(A1));
  
  // Update relay based on button state
  updateRelay();
  
}

void updateRelay() {
  if (buttonState == 1) {
    for (int i = 0; i < 5; i++) {
      // Turn on the relay
      digitalWrite(relayPin, HIGH);
      delay(500); // Keep relay on for 500 milliseconds
      // Turn off the relay
      digitalWrite(relayPin, LOW);
      delay(500); // Keep relay off for 500 milliseconds
    }
  } else {
    digitalWrite(relayPin, LOW); // Ensure relay is off
  }
}
