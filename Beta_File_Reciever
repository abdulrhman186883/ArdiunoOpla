#include <Arduino_MKRIoTCarrier.h>
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>
#include "thingProperties.h"

MKRIoTCarrier carrier;
const int relayPin = 5; // Define the pin connected to the relay
const int BUTTON_PIN = 3; // Define the pushbutton pin

int lastButtonState = HIGH; // Variable to store previous button state
unsigned long lastDebounceTime = 0; // Last time the output pin was toggled
unsigned long debounceDelay = 50; // Debounce time in milliseconds
bool buttonPressed = false; // Flag to track button press state

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

  // Read the state of the button
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
      buttonState = reading; // Update buttonState with the actual reading

      // If the button state is LOW, the button is pressed
      if (buttonState == LOW) {
        if (!buttonPressed) { // Check if the button was not previously pressed
          Serial.println("Button pressed!");
          buttonPressed = true; // Set the flag to indicate the button is pressed
          onButtonStateChange();
        }
      } else {
        // Button is released
        buttonPressed = false; // Reset the flag when the button is released
      }
    }
  }

  // Update lastButtonState with the current reading for the next loop iteration
  lastButtonState = reading;
}

void onButtonStateChange() {
  // Toggle the local LED (A1 pin)
  digitalWrite(A1, !digitalRead(A1));
  
  // Update relay based on button state
  updateRelay();
}

void updateRelay() {
  // Power the relay
  digitalWrite(relayPin, HIGH);
  delay(3000); // Keep relay on for 3 seconds
  digitalWrite(relayPin, LOW); // Turn off the relay
}
