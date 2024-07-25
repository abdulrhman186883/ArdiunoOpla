This project consists of two Arduino sketches, Sender (Alpha) and Receiver (Beta), that demonstrate a basic IoT setup using the Arduino MKR IoT Carrier and WiFiNINA library. The sketches include functionality for handling button inputs, controlling a relay, and interacting with the Arduino IoT Cloud. The main objective is to send and receive button press events between two devices, and control a relay and an LED based on these events.

#Hardware Required

2 x Arduino Opla
2 x Relays
Jumper wires
Sender (Alpha) Sketch
File: sender.ino
Description: This sketch is responsible for detecting button presses and sending the state to the Arduino IoT Cloud. It includes debounce logic to prevent multiple detections of a single button press. The button state change triggers a relay and a local LED (connected to pin A1) on the MKR IoT Carrier.

#Key Components:

Button Handling: Uses a physical button connected to pin 3 to detect presses. The state is debounced and then processed.
Capacitive Touch Handling: The carrier's capacitive touch button (TOUCH0) can also trigger events.
Relay Control: A relay connected to pin 5 is toggled based on the button state.
Cloud Integration: The state is synchronized with the Arduino IoT Cloud using ArduinoCloud.update().
Functional Overview
#Setup:
Initializes serial communication, MKR IoT Carrier, and the relay pin.
Begins the Arduino IoT Cloud connection.

Loop:
Continuously updates the Arduino Cloud and checks for button states.
Handles physical button presses and capacitive touch events.
Toggles the local LED and updates the relay state based on button presses.
Relay Behavior
The relay toggles five times (on/off with 500ms intervals) when the button is pressed.
Receiver (Beta) Sketch
File: receiver.ino
Description: This sketch listens for button state changes from the cloud, triggered by the Sender (Alpha). It controls a relay and a local LED in response to these events.

#Key Components:

#Button Handling: Monitors the physical button connected to pin 3, with debounce logic.
Relay Control: A relay connected to pin 5 is controlled based on the button state.
Cloud Integration: Similar to the Sender, it uses the Arduino IoT Cloud for state synchronization.
Functional Overview
Setup:
Initializes serial communication, MKR IoT Carrier, and the relay pin.
Begins the Arduino IoT Cloud connection.
Loop:
Updates the Arduino Cloud and monitors for button state changes.
Reacts to button presses by toggling the local LED and updating the relay state.
Relay Behavior
The relay is activated for 3 seconds when the button is pressed and then turned off.
Getting Started
Prerequisites
Install the required libraries: Arduino_MKRIoTCarrier, WiFiNINA, and Arduino IoT Cloud libraries.
Setup Instructions
Wiring:

Connect the relay modules to pin 5 on both devices.
Connect a physical button to pin 3 with a pull-up resistor.
Arduino IoT Cloud Configuration:

Set up your Arduino IoT Cloud Thing and variables according to your requirements.
Link the buttonState property to the cloud variable for both devices.
Upload Code:

Flash the sender.ino code to the first MKR WiFi 1010 board.
Flash the receiver.ino code to the second MKR WiFi 1010 board.
#Usage
Press the physical button or use the capacitive touch button on the Sender (Alpha) to trigger actions.
The Receiver (Beta) will react to these actions by controlling its relay and LED.


#Contributing
Feel free to contribute by opening issues or submitting pull requests. Please ensure that your contributions align with the coding style and guidelines of the project.

#Acknowledgements
Arduino MKR IoT Carrier and WiFiNINA libraries for enabling the hardware interaction.
The Arduino IoT Cloud for providing a platform for device communication.
For any questions or further information, please refer to the official Arduino documentation.
