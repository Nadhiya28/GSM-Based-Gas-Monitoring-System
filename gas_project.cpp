#include<HX711.h>
#include<SoftwareSerial.h>

// Pin configuration
#define DOUT  3  // HX711 data output pin
#define CLK   2  // HX711 clock pin
#define GSM_TX 7 // TX pin of GSM module
#define GSM_RX 8 // RX pin of GSM module
#define LOW_GAS_THRESHOLD 2000  // Set threshold for low gas weight in grams

HX711 scale;
SoftwareSerial gsm(GSM_TX, GSM_RX);

// Variables
float weight = 0;
bool alertSent = false;  // To avoid sending SMS repeatedly

void setup() {
  Serial.begin(9600);
  gsm.begin(9600);

  // Initialize HX711
  scale.begin(DOUT, CLK);
  scale.set_scale(2280.f);   // TODO: Set your actual calibration factor here
  scale.tare();              // Reset the scale to 0

  // GSM Module initialization
  delay(1000); // Allow GSM to initialize
  sendSMS("System initialized. Gas monitoring started.");
  Serial.println("System Initialized.");
}

void loop() {
  // Read weight from the load cell
  weight = scale.get_units(10); // Average of 10 readings

  // Display weight
  Serial.print("Gas Weight: ");
  Serial.print(weight);
  Serial.println(" g");

  // Check if the weight is below the threshold
  if (weight < LOW_GAS_THRESHOLD && !alertSent) {
    Serial.println("Low gas detected! Sending SMS for refill...");
    sendSMS("Low gas alert: Please book a refill.");
    alertSent = true;  // Avoid repeated alerts
  }

  // Reset alert flag if weight goes back above threshold
  if (weight >= LOW_GAS_THRESHOLD) {
    alertSent = false;
  }

  delay(5000); // Check every 5 seconds
}

// Function to send SMS using GSM module
void sendSMS(String message) {
  gsm.println("AT+CMGF=1");    // Set GSM module to text mode
  delay(1000);

  gsm.println("AT+CMGS=\"+91XXXXXXXXXX\"");  // Replace with gas agency number
  delay(1000);

  gsm.print(message);  // Message text
  delay(1000);

  gsm.write(26);  // ASCII code for Ctrl+Z to send the message
  delay(3000);    // Wait for SMS to send

  Serial.println("SMS sent.");
}

