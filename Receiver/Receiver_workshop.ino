// RECEIVER
#include <esp_now.h>
#include <WiFi.h>

// Define Pin Port and Preference
int x, y; // initialize integer x, y
int MOTOR_BACK_WHEEL_PWM = 5; // control the back wheel speed
int MOTOR_BACK_WHEEL_FRONT = 16;	  // control the back wheel to go forward 
int MOTOR_BACK_WHEEL_BACK = 17;		  // control the back wheel to go backward
int MOTOR_FRONT_WHEEL_GO_PWM = 25; // control the front wheel power
int MOTOR_FRONT_WHEEL_GO_LEFT = 26;  // control the front wheel to go left
int MOTOR_FRONT_WHEEL_GO_RIGHT = 27; // control the front wheel to go right
// Set send target and receive data structure

struct carData { // group x,y together and to be sent together at the same time  
    int x; // left right direction
    int y; // forward backward speed
};

void OnDataRecv(const uint8_t *macAddress, const uint8_t *incomingData, int len) {
	// Get data
	carData receiveData;
	memcpy(&receiveData, incomingData, sizeof(receiveData)); // get data from the controller 
	// Adjust motor
	frontWheel(receiveData.x); // frontWheel(_input data_) is to call the fucntion with receiveData.x as input data; 
	backWheel(receiveData.y); // backWheel(_input data_) is to call the fucntion with receiveData.y as input data;
	Serial.printf("X-direction: %d, Y-direction: %d\n", receiveData.x, receiveData.y); // print out the two receieved data 
}

// == is to check is it is equal to the value
// = is to assign the variable value 
void frontWheel(int x) {
	// Set Direction (-1: Left, 0: Straight, 1: Right)
	// Motor A: Forward, Motor B: Backwards
	if (x == -1) { // when x == -1, this block will be executed (turn left)
    digitalWrite(MOTOR_FRONT_WHEEL_GO_PWM, HIGH);
		// set MOTOR_FRONT_WHEEL_GO_LEFT to HIGH
    // IT'S TIME TO TRY IT YOURSELF!!! 
		// set MOTOR_FRONT_WHEEL_GO_RIGHT to LOW
    // IT'S TIME TO TRY IT YOURSELF!!! 
	
  } else if (x == 1) { // when x == 1, this block will be executed (turn right)
    digitalWrite(MOTOR_FRONT_WHEEL_GO_PWM, HIGH);
		// set MOTOR_FRONT_WHEEL_GO_LEFT to LOW
    // IT'S TIME TO TRY IT YOURSELF!!! 
		// set MOTOR_FRONT_WHEEL_GO_RIGHT to HIGH
    // IT'S TIME TO TRY IT YOURSELF!!! 
	} else { // when x == 0, this block will be executed (centre)
    digitalWrite(MOTOR_FRONT_WHEEL_GO_PWM, LOW);
		// set MOTOR_FRONT_WHEEL_GO_LEFT to LOW
    // IT'S TIME TO TRY IT YOURSELF!!! 
		// set MOTOR_FRONT_WHEEL_GO_RIGHT to LOW
    // IT'S TIME TO TRY IT YOURSELF!!! 
	}
}

void backWheel(int y) {
	// Set Direction (-1: Backwards, 0: Stop, 1: Forward)
	// Motor A: Forward Speed, Motor B: Backwards Speed
	if (y > 0) { // when y > 0, this block will be executed (move foward)
    analogWrite(MOTOR_BACK_WHEEL_PWM, abs(y)); // set MOTOR_BACK_WHEEL_PWM as absolute y (ignore negative sign)
		digitalWrite(MOTOR_BACK_WHEEL_FRONT, HIGH); // set MOTOR_BACK_WHEEL_FRONT as HIGH
		digitalWrite(MOTOR_BACK_WHEEL_BACK, LOW); // set MOTOR_BACK_WHEEL_BACK as LOW
	} else if (y < 0) { // when y < 0, this block will be executed (move backward)
    analogWrite(MOTOR_BACK_WHEEL_PWM, abs(y)); // set MOTOR_BACK_WHEEL_PWM as absolute speed of y (ignore negative sign)
		// set MOTOR_BACK_WHEEL_FRONT as LOW
    // IT'S TIME TO TRY IT YOURSELF!!! 
		// set MOTOR_BACK_WHEEL_BACK as HIGH
    // IT'S TIME TO TRY IT YOURSELF!!! 
	} else{ // when y == 0, this block will be executed (stop)
		analogWrite(MOTOR_BACK_WHEEL_PWM, 0);
    // set MOTOR_BACK_WHEEL_FRONT as LOW
    // IT'S TIME TO TRY IT YOURSELF!!! 
		// set MOTOR_BACK_WHEEL_BACK as LOW
    // IT'S TIME TO TRY IT YOURSELF!!! 
	}
}

void setup() {
	Serial.begin(115200);
	pinMode(MOTOR_BACK_WHEEL_FRONT, OUTPUT); // define MOTOR_BACK_WHEEL_FRONT as output 
	pinMode(MOTOR_BACK_WHEEL_BACK, OUTPUT); // define MOTOR_BACK_WHEEL_BACK as output 
  // define MOTOR_BACK_WHEEL_PWM as output
	pinMode(MOTOR_FRONT_WHEEL_GO_LEFT, OUTPUT); // define MOTOR_FRONT_WHEEL_GO_LEFT as output 
	pinMode(MOTOR_FRONT_WHEEL_GO_RIGHT, OUTPUT); // define MOTOR_FRONT_WHEEL_GO_RIGHT as output 
  // define MOTOR_FRONT_WHEEL_PWM as output

  /* receive data DELETE THIS LINE TO RECEIVE DATA
	WiFi.mode(WIFI_STA);
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW, Please Restart board.");
		for(;;);
	}

	Serial.print("Finish initialization, local MAC: ");
	Serial.println(WiFi.macAddress());

	// The function act as Event Listener
	esp_now_register_recv_cb(OnDataRecv);
  DELETE THIS LINE TO RECEIVE DATA */
}

void loop() {
  // local adjust motor
  // TRY TO CHANGE THE VALUE OF x, y
  x = 0;
  y = 0;
  frontWheel(x); // frontWheel(_input data_) is to call the fucntion with receiveData.x as input data; 
	backWheel(y); // backWheel(_input data_) is to call the fucntion with receiveData.y as input data;
	Serial.printf("X-direction: %d, Y-direction: %d\n", x, y);  // print the value of x, y
}