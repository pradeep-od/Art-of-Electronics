// Pin definitions based on your wiring
const int pinBeforeResistor = A0; // Connected to Potentiometer wiper & start of resistor
const int pinAfterResistor  = A1; // Connected to end of resistor & start of LED

// Circuit constants
const float V_SUPPLY = 5.0;       // Arduino 5V supply
const float R_VALUE  = 220.0;     // CHANGE THIS to your exact resistor value in Ohms (e.g., 220, 330, 1000)

void setup() {
  Serial.begin(9600);
  
  // Print CSV header for your website/serial parser
  Serial.println("Voltage_V,Current_mA");
}

void loop() {
  // 1. Read analog values from both sides of the resistor
  int rawA0 = analogRead(pinBeforeResistor);
  int rawA1 = analogRead(pinAfterResistor);

  // 2. Convert raw ADC values (0-1023) to actual Voltages
  float vA0 = (rawA0 * V_SUPPLY) / 1023.0;
  float vA1 = (rawA1 * V_SUPPLY) / 1023.0;

  // 3. Calculate the voltage drop strictly across the resistor (V = V_A0 - V_A1)
  float voltageAcrossResistor = vA0 - vA1;

  // Prevent tiny negative noise readings when potentiometer is at 0V
  if (voltageAcrossResistor < 0.0) {
    voltageAcrossResistor = 0.0;
  }

  // 4. Calculate Current using Ohm's Law (I = V / R)
  float currentAmps = voltageAcrossResistor / R_VALUE;
  float currentMilliAmps = currentAmps * 1000.0; // Convert to mA for cleaner graph numbers

  // 5. Output clean comma-separated values (Voltage, Current) for your website
  Serial.print(voltageAcrossResistor, 3);
  Serial.print(",");
  Serial.println(currentMilliAmps, 3);

  // Short delay for smooth real-time graphing as you turn the potentiometer
  delay(200); 
}
