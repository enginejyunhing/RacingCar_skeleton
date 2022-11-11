// SENDER
#include <esp_now.h>
#include <WiFi.h>

// Define Pin Port and Preference
int VRy = 35; // initialize the joystick y axis pin port (forward and backward)
int LEFT = 33; // initialize the left button pin port
int RIGHT = 34; // initialize the right button pin port
int WIFI_CHANNEL = 0; // initialize the wifi channel
int MOTOR_MAX_SPEED = 255; // initialize motor max. speed (the maximum speed received by motor drive)
int MOTOR_MIN_SPEED = 60; // initialize motor max. speed (the speed under 60 will not be recognized at a formal motion)

// Set send target and send data structure
esp_now_peer_info_t peerInfo;
uint8_t sendTargetMAC[] = {0x10, 0x52, 0x1C, 0x5C, 0xD1, 0x74}; //the unique address to identify of the target (car) 

int defaultValue = 0; // for calibrating joystick

struct carData { // group x,y together and to be sent together at the same time  
    int x; // left right direction
    int y; // forward backward speed
};

void OnDataSent(const uint8_t *macAddress, esp_now_send_status_t status) {
    if (status == ESP_NOW_SEND_SUCCESS)
        return;  // only if the ESP_NOW_SEND_SUCCESS is success then this line will be run --> return: current function will be quit immediately 
    // the below two line will not be run if the IF block is ran  --> only if the ESP_NOW_SEND_SUCCESS is fail --> this two line of code will be 
    Serial.print("Failed sent to device, target MAC address: "); 
        for (int i = 0; i < 5; i++) {
        Serial.print(macAddress[i], HEX);
        Serial.print(":");
    }
    Serial.println(macAddress[6], HEX); // print the failed mac adress 
}

void setup() {
    Serial.begin(115200); // set serial monitor channel to 115200
    pinMode(VRy, INPUT); // define VRy as input 
    // define LEFT as input 
    // IT'S TIME TO TRY IT YOURSELF!!! 
    // define RIGHT as input
    // IT'S TIME TO TRY IT YOURSELF!!! 
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW, Please Restart board.");
        for (;;);
    }

    memcpy(peerInfo.peer_addr, sendTargetMAC, 6);
    peerInfo.channel = WIFI_CHANNEL;
    peerInfo.encrypt = false;
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer, Please Restart board.");
        for (;;);
    }

    for (int i = 0; i < 10; i++)
        defaultValue += analogRead(VRy); // add the reading of VRy for 10 times

    defaultValue /= 10; // find the mean of the reading of VRy

    Serial.println("Finish initialization, default joystick value: %d");
    Serial.println(defaultValue);

    // This function act as event listener
    esp_now_register_send_cb(OnDataSent);
}

void loop() {
    int x = 0; // initalize direction as 0 (center)
    int l = digitalRead(LEFT); // read the left button signal to the variabel l (high  = pressed , low = not being pressed)
    // read the right button signal to the variable r (high  = pressed , low = not being pressed)
    // IT'S TIME TO TRY IT YOURSELF!!! 
    int y = map(analogRead(VRy) - defaultValue, 0 - defaultValue, 4098 - defaultValue, -MOTOR_MAX_SPEED, MOTOR_MAX_SPEED);
    // analogRead(VRy) [input] - 1975[the value when at rest]
    // the range of input is from -1960 to 2160
    // the accepted range of input motor driver are using right now is -255 to 255 [recall the value that MOTOR_MAX_SPEED stored is 255]  
    // map(value, fromLow, fromHigh, toLow, toHigh) :  re-maps a number from one range to another

    // Limit output range (<= 60 -> 0, >MOTOR_MAX_SPEED -> MOTOR_MAX_SPEED)
    // the speed under MOTOR_MIN_SPEED will not be recognized at a formal motion
    if (abs(y) < MOTOR_MIN_SPEED)
        y = 0;
    // Turn LEFT (if left button == HIGH and right button == LOW, then x == -1)
    // IT'S TIME TO TRY IT YOURSELF!!! 
    // Turn RIGHT (if left button == LOW and right button == HIGH, then x == 1)
    // IT'S TIME TO TRY IT YOURSELF!!! 

    // Serial print x and y
    Serial.printf("X-direction: %d, Y-direction: %d\n", x, y);

    /* send data DELETE THIS LINE TO SEND DATA
    carData sendData;
    sendData.x = x; 
    sendData.y = y;
    Serial.printf("X-direction: %d, Y-direction: %d\n", sendData.x, sendData.y);

    // send sendData (sendData.x and sendData.y) to the target(car)
    esp_err_t result = esp_now_send(sendTargetMAC, (uint8_t *)&sendData, sizeof(sendData)); 
    DELETE THIS LINE TO SEND DATA */ 
}