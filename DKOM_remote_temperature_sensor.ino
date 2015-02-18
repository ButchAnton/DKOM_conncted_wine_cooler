// Read a temperature sensor (TMP36) and wirelessly send the result to another
// computer using the XBee wireless radio.

// Use 3.3v as the reference voltage for the temperature sensor.
// This increases the accuracy of the sensor.
// However, we have to provide an external reference voltage to AREF.

#define aref_voltage 3.3

// TMP36 Pin Variables

int tempPin = 1;        // The analog pin the TMP36's Vout (sense) pin is connected to
                        // the resolution is 10 mV / degree centigrade with a
                        // 500 mV offset to allow for negative temperatures.
                        //
int tempReading;        // The analog reading from the sensor.

// Switch variables

int switchPin = 7;
int switchState = 0;

void setup(void) {

  // We'll send debugging information via the Serial monitor.
  // Because of how the Arduino FIO board is wired, the XBee
  // radio uses the RX/TX pins, so serial I/O goes over the
  // radio.

  Serial.begin(9600);

  // If we use a reference other than the built-in 5V reference, we need to
  // set this to EXTERNAL and provide that reference voltage on the AREF pin.

  analogReference(EXTERNAL);

  // Set up the switch pin to receive digital input.

  pinMode(switchPin, INPUT);
}


void loop(void) {

  // Send the time in milliseconds since power on.

  Serial.print("TIME: ");
  Serial.print(millis());
  Serial.print(",");

  // Read the analog value of the temperature pin.

  tempReading = analogRead(tempPin);

  // Serial.print("Temp reading = ");
  // Serial.print(tempReading);

  // Convert that reading to a voltage, which is based off the reference voltage.

  float voltage = tempReading * aref_voltage;
  voltage /= 1024.0;

  // Print out the voltage.

  // Serial.print(" - ");
  // Serial.print(voltage); Serial.println(" volts");

  // Print out the temperature.

  float temperatureC = (voltage - 0.5) * 100 ;  // Converting from 10 mv per degree with 500 mV offset
                                                // to degrees C ((volatge - 500mV) times 100).
  // Serial.print(temperatureC); Serial.println(" degrees C");

  // Convert to degrees Fahrenheit.

  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  // Serial.print(temperatureF); Serial.println(" degrees F");

  Serial.print("TEMP: ");
  Serial.print(temperatureF);
  Serial.print(",");

  // Read the state of the switch.

  switchState = digitalRead(switchPin);

  Serial.print("DOOR: ");

  if (HIGH == switchState) {
    Serial.println("OPEN");
  } else {
    Serial.println("CLOSED");
  }

  // Send readings every second.

  delay(1000);
}
