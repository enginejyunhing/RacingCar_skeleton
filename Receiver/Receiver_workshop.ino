// RECEIVER
#include <esp_now.h>
#include <WiFi.h>

// Define Pin Port and Preference
int x, y; // initialize integer x, y
int MOTOR_BACK_WHEEL_PWM = 5; // control the back wheel speed
int MOTOR_BACK_WHEEL_A = 16;	  // control the back wheel to go forward 
int MOTOR_BACK_WHEEL_B = 17;		  // control the back wheel to go backward
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
	// Adjust front motor ------------------------------------------------------------------
  // Set Direction (-1: Left, 0: Straight, 1: Right)
	// Motor A: Forward, Motor B: Backwards
  // == is to check is it is equal to the value
  // = is to assign the variable value 
  // !!!!!!!!!!!!!!!!!!!!!! IT'S TIME TO TRY IT YOURSELF !!!!!!!!!!!!!!!!!!!!!!

	// Set Direction (-1: Left, 0: Straight, 1: Right)
	// Motor A: Forward, Motor B: Backwards

  // if receiveData.x == -1, this block will be executed (turn left)
    // set MOTOR_FRONT_WHEEL_GO_PWM to HIGH
		// set MOTOR_FRONT_WHEEL_GO_LEFT to HIGH
    // IT'S TIME TO TRY IT YOURSELF!!! 
		// set MOTOR_FRONT_WHEEL_GO_RIGHT to LOW
	
  // else if receiveData.x == 1, this block will be executed (turn right)
    // set MOTOR_FRONT_WHEEL_GO_PWM to HIGH
		// set MOTOR_FRONT_WHEEL_GO_LEFT to LOW
		// set MOTOR_FRONT_WHEEL_GO_RIGHT to HIGH

  // else, this block will be executed (centre)
    // set MOTOR_FRONT_WHEEL_GO_PWM to LOW
		// set MOTOR_FRONT_WHEEL_GO_LEFT to LOW
		// set MOTOR_FRONT_WHEEL_GO_RIGHT to LOW

  // Adjust back motor ------------------------------------------------------------------
	// Set Direction (-1: Backwards, 0: Stop, 1: Forward)
	// Motor A: Forward Speed, Motor B: Backwards Speed
  // == is to check is it is equal to the value
  // = is to assign the variable value 
  // !!!!!!!!!!!!!!!!!!!!!! IT'S TIME TO TRY IT YOURSELF !!!!!!!!!!!!!!!!!!!!!!
  
	// if receiveData.y > 0, this block will be executed (move foward)
    // set MOTOR_BACK_WHEEL_PWM as abs(receiveData.y) (ignore negative sign)
		// set MOTOR_BACK_WHEEL_A as HIGH
		// set MOTOR_BACK_WHEEL_B as LOW

	// else if receiveData.y < 0, this block will be executed (move backward)
    // set MOTOR_BACK_WHEEL_PWM as abs(receiveData.y) (ignore negative sign)
		// set MOTOR_BACK_WHEEL_A as LOW
		// set MOTOR_BACK_WHEEL_B as HIGH

	// else, receiveData.y == 0, this block will be executed (stop)
		// set MOTOR_BACK_WHEEL_PWM as 0
    // set MOTOR_BACK_WHEEL_A as LOW
		// set MOTOR_BACK_WHEEL_B as LOW 	
  
	Serial.printf("X-direction: %d, Y-direction: %d\n", receiveData.x, receiveData.y); // print out the two receieved data 
}

void setup() {
	Serial.begin(115200);
	pinMode(MOTOR_BACK_WHEEL_A, OUTPUT); // define MOTOR_BACK_WHEEL_A as output 
	pinMode(MOTOR_BACK_WHEEL_B, OUTPUT); // define MOTOR_BACK_WHEEL_B as output 
  pinMode(MOTOR_BACK_WHEEL_PWM, OUTPUT); //define MOTOR_BACK_WHEEL_PWM as output 
	pinMode(MOTOR_FRONT_WHEEL_GO_LEFT, OUTPUT); // define MOTOR_FRONT_WHEEL_GO_LEFT as output 
	pinMode(MOTOR_FRONT_WHEEL_GO_RIGHT, OUTPUT); // define MOTOR_FRONT_WHEEL_GO_RIGHT as output 
  pinMode(MOTOR_FRONT_WHEEL_GO_PWM, OUTPUT); //define MOTOR_FRONT_WHEEL_PWM as output 

	WiFi.mode(WIFI_STA);
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW, Please Restart board.");
		for(;;);
	}

	Serial.print("Finish initialization, local MAC: ");
	Serial.println(WiFi.macAddress());

	// The function act as Event Listener
	esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}
