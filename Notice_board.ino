#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with I2C address 0x27 (adjust if different), 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Start serial communication at 9600 baud (default for HC-05)
  Serial.begin(9600);
  
  // Initialize the LCD
  lcd.begin();
  lcd.backlight(); // Turn on backlight
  lcd.clear();     // Clear the display
  
  // Display initial message
  lcd.setCursor(0, 0);
  lcd.print("Wireless Notice");
  lcd.setCursor(0, 1);
  lcd.print("Board Ready");
  delay(5000); // Show for 5 seconds
  lcd.clear();
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available from Bluetooth
    lcd.clear(); // Clear previous message
    String message = Serial.readString(); // Read incoming string
    
    // Split message into two lines if longer than 16 characters
    if (message.length() > 16) {
      lcd.setCursor(0, 0);
      lcd.print(message.substring(0, 16)); // First 16 characters on line 1
      lcd.setCursor(0, 1);
      lcd.print(message.substring(16));    // Remaining on line 2
    } else {
      lcd.setCursor(0, 0);
      lcd.print(message); // Display full message on line 1 if short
    }
  }
}