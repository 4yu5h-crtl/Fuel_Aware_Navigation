/*
 * Ultrasonic Sensor Calibration Sketch
 * 
 * This sketch helps calibrate an ultrasonic sensor for fuel level measurement.
 * It provides continuous distance readings and helps determine the empty and full
 * distances for your specific bottle setup.
 */

// Ultrasonic sensor pins
const int TRIG_PIN = 5;  // ESP32 GPIO pin for trigger
const int ECHO_PIN = 18; // ESP32 GPIO pin for echo

// Calibration mode
enum CalibrationMode {
  CONTINUOUS_READING,
  EMPTY_BOTTLE,
  FULL_BOTTLE,
  VOLUME_CALCULATION
};

CalibrationMode currentMode = CONTINUOUS_READING;

// Variables for measurements
float emptyDistance = 0.0;
float fullDistance = 0.0;
float bottleHeight = 0.0;
float bottleDiameter = 0.0;
float bottleVolume = 0.0;

// Variables for averaging
const int NUM_READINGS = 10;
float readings[NUM_READINGS];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  Serial.begin(115200);
  
  // Initialize ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize readings array
  for (int i = 0; i < NUM_READINGS; i++) {
    readings[i] = 0;
  }
  
  printInstructions();
}

void loop() {
  // Check for user input
  if (Serial.available() > 0) {
    char input = Serial.read();
    processUserInput(input);
  }
  
  // Take and display measurements based on current mode
  switch (currentMode) {
    case CONTINUOUS_READING:
      displayContinuousReading();
      break;
    case EMPTY_BOTTLE:
      calibrateEmptyBottle();
      break;
    case FULL_BOTTLE:
      calibrateFullBottle();
      break;
    case VOLUME_CALCULATION:
      calculateVolume();
      break;
  }
  
  delay(500); // Short delay between readings
}

void processUserInput(char input) {
  switch (input) {
    case 'c':
    case 'C':
      currentMode = CONTINUOUS_READING;
      Serial.println("\n--- Continuous Reading Mode ---");
      break;
    case 'e':
    case 'E':
      currentMode = EMPTY_BOTTLE;
      Serial.println("\n--- Empty Bottle Calibration Mode ---");
      Serial.println("Place the empty bottle under the sensor and press 's' to save the measurement.");
      break;
    case 'f':
    case 'F':
      currentMode = FULL_BOTTLE;
      Serial.println("\n--- Full Bottle Calibration Mode ---");
      Serial.println("Fill the bottle to the maximum level and press 's' to save the measurement.");
      break;
    case 'v':
    case 'V':
      currentMode = VOLUME_CALCULATION;
      Serial.println("\n--- Volume Calculation Mode ---");
      break;
    case 's':
    case 'S':
      saveMeasurement();
      break;
    case 'h':
    case 'H':
      printInstructions();
      break;
    case 'r':
    case 'R':
      printResults();
      break;
  }
}

void printInstructions() {
  Serial.println("\n===== Ultrasonic Sensor Calibration =====");
  Serial.println("Commands:");
  Serial.println("  c - Continuous reading mode");
  Serial.println("  e - Calibrate empty bottle");
  Serial.println("  f - Calibrate full bottle");
  Serial.println("  v - Calculate bottle volume");
  Serial.println("  s - Save current measurement");
  Serial.println("  r - Print calibration results");
  Serial.println("  h - Show these instructions");
  Serial.println("=======================================");
}

float measureDistance() {
  // Clear the TRIG_PIN
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Set the TRIG_PIN HIGH for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the ECHO_PIN, return the sound wave travel time in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance
  float distance = duration * 0.034 / 2;
  
  return distance;
}

void displayContinuousReading() {
  float distance = measureDistance();
  
  // Update the running average
  total = total - readings[readIndex];
  readings[readIndex] = distance;
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % NUM_READINGS;
  average = total / NUM_READINGS;
  
  // Display the current reading and average
  Serial.print("Current Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Average: ");
  Serial.print(average);
  Serial.println(" cm");
}

void calibrateEmptyBottle() {
  displayContinuousReading();
}

void calibrateFullBottle() {
  displayContinuousReading();
}

void calculateVolume() {
  Serial.println("\n--- Bottle Volume Calculation ---");
  Serial.println("Enter the following measurements:");
  
  // Get bottle height
  Serial.print("Bottle Height (cm): ");
  while (!Serial.available()) {
    delay(100);
  }
  bottleHeight = Serial.parseFloat();
  Serial.println(bottleHeight);
  
  // Clear input buffer
  while (Serial.available()) {
    Serial.read();
  }
  
  // Get bottle diameter
  Serial.print("Bottle Diameter (cm): ");
  while (!Serial.available()) {
    delay(100);
  }
  bottleDiameter = Serial.parseFloat();
  Serial.println(bottleDiameter);
  
  // Calculate volume in liters
  float radius = bottleDiameter / 2.0;
  float volumeCm3 = 3.14159 * radius * radius * bottleHeight;
  bottleVolume = volumeCm3 / 1000.0; // Convert to liters
  
  Serial.print("Calculated Volume: ");
  Serial.print(bottleVolume);
  Serial.println(" liters");
  
  // Return to continuous reading mode
  currentMode = CONTINUOUS_READING;
}

void saveMeasurement() {
  switch (currentMode) {
    case EMPTY_BOTTLE:
      emptyDistance = average;
      Serial.print("Empty bottle distance saved: ");
      Serial.print(emptyDistance);
      Serial.println(" cm");
      currentMode = CONTINUOUS_READING;
      break;
    case FULL_BOTTLE:
      fullDistance = average;
      Serial.print("Full bottle distance saved: ");
      Serial.print(fullDistance);
      Serial.println(" cm");
      currentMode = CONTINUOUS_READING;
      break;
    default:
      Serial.println("No measurement to save in current mode.");
      break;
  }
}

void printResults() {
  Serial.println("\n===== Calibration Results =====");
  Serial.print("Empty Bottle Distance: ");
  Serial.print(emptyDistance);
  Serial.println(" cm");
  
  Serial.print("Full Bottle Distance: ");
  Serial.print(fullDistance);
  Serial.println(" cm");
  
  Serial.print("Bottle Height: ");
  Serial.print(bottleHeight);
  Serial.println(" cm");
  
  Serial.print("Bottle Diameter: ");
  Serial.print(bottleDiameter);
  Serial.println(" cm");
  
  Serial.print("Bottle Volume: ");
  Serial.print(bottleVolume);
  Serial.println(" liters");
  
  Serial.println("\n--- Code Constants to Use ---");
  Serial.print("const float EMPTY_DISTANCE = ");
  Serial.print(emptyDistance);
  Serial.println(";  // Distance when bottle is empty (in cm)");
  
  Serial.print("const float FULL_DISTANCE = ");
  Serial.print(fullDistance);
  Serial.println(";  // Distance when bottle is full (in cm)");
  
  Serial.print("const float BOTTLE_HEIGHT = ");
  Serial.print(bottleHeight);
  Serial.println(";  // Height of the bottle (in cm)");
  
  Serial.print("const float BOTTLE_DIAMETER = ");
  Serial.print(bottleDiameter);
  Serial.println(";  // Diameter of the bottle (in cm)");
  
  Serial.print("const float BOTTLE_VOLUME = ");
  Serial.print(bottleVolume);
  Serial.println(";  // Total volume of the bottle (in liters)");
  
  Serial.println("===============================");
} 