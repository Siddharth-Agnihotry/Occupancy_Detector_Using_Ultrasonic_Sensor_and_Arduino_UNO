#include <LiquidCrystal.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <NewPing.h>

#define TRIGGER_PIN 2          // Ultrasonic sensor trigger pin
#define ECHO_PIN 3             // Ultrasonic sensor echo pin
#define MAX_DISTANCE 200       // Maximum distance for measurement (in centimeters)
#define OCCUPANCY_THRESHOLD 50 // Threshold distance for occupancy (in centimeters)

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Create a NewPing object

Adafruit_SH1106 display(4); // Create an Adafruit_SH1106 object with the appropriate OLED display address

void setup()
{
    display.begin(SH1106_SWITCHCAPVCC);
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Occupancy:");
    display.display();

    Serial.begin(9600); // Initialize the serial communication
}

void loop()
{
    delay(50); // Delay for stability

    unsigned int distance = sonar.ping_cm(); // Measure the distance in centimeters

    display.setCursor(0, 10);
    display.print("                    "); // Clear the previous occupancy status
    display.setCursor(0, 10);
    // Check for occupancy
    if (distance < OCCUPANCY_THRESHOLD)
    {
        display.println("Occupied");
        Serial.println("Occupied");
        // We can add the code as per the need
    }
    else
    {
        display.println("Not occupied");
        Serial.println("Not Occupied");
        // We can add the code as per the need
    }

    display.display();

    Serial.print("Distance: ");
    Serial.print(distance);
    display.println(distance);
    Serial.println(" cm");

    delay(500); // Wait for a moment before taking the next measurement
}
