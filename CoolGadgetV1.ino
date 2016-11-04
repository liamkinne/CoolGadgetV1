#include <LiquidCrystal.h>
#include "pitches.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Buttons
uint8_t buttonCurrent = 0;
uint8_t buttonLast = 0;
int buttonAnalog;

#define NONE 0
#define SELECT 1
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5

// Menu
int menuPos = 0;
int menuBarNum = 0;
long menuLastUpdate = 0;

// Sound
uint16_t soundDuration = 25; // In Milliseconds
uint8_t soundPulseLength = 128;
long soundStartTime;

void setup() {
	lcd.begin(16, 2);
	lcd.print("Ello World!!");
	tone(A1, 294, soundDuration);
}

void loop() {
	// Button Update
	buttonLast = buttonCurrent;
	buttonAnalog = analogRead(A0);

	if (buttonAnalog > 882) 		buttonCurrent = 0; // None
	else if (buttonAnalog > 627) 	buttonCurrent = 1; // Select
	else if (buttonAnalog > 420) 	buttonCurrent = 4; // Left
	else if (buttonAnalog > 232) 	buttonCurrent = 3; // Down
	else if (buttonAnalog > 70) 	buttonCurrent = 2; // Up
	else 							buttonCurrent = 5; // Right

	// Sound
	if (buttonLast != buttonCurrent) {
		if (buttonCurrent == UP) {
			if (menuPos < 1) {
				menuPos++;
			}
			else {
				menuPos = -1;
			}
			tone(A1, NOTE_C5, soundDuration);
			delay(soundDuration);
			noTone(A1);
			tone(A1, NOTE_E5, soundDuration);
		}
		else if (buttonCurrent == DOWN) {
			if (menuPos > -1) {
				menuPos--;
			}
			else {
				menuPos = 1;
			}
			tone(A1, NOTE_E5, soundDuration);
			delay(soundDuration);
			noTone(A1);
			tone(A1, NOTE_C5, soundDuration);
		}
		else if (buttonCurrent == SELECT) {
			tone(A1, NOTE_G5, 125);
			delay(200);
			noTone(A1);
			tone(A1, NOTE_G5, 125);
			delay(200);
			noTone(A1);
			tone(A1, NOTE_AS5, 125);
			delay(125);
			noTone(A1);
			tone(A1, NOTE_G5, 125);
			delay(150);
			noTone(A1);
		}
	}

	if (millis() - menuLastUpdate >= 300) {
		menuLastUpdate = millis();
		if (menuBarNum < 13) {
			menuBarNum++;
		}
		else {
			menuBarNum = 0;
		}
		if (menuPos == 0) {
			lcd.clear();
			lcd.setCursor(0, 0);
			lcd.print("CoolGadget  V1.0");
			lcd.setCursor(0, 1);
			lcd.print("[");
			lcd.setCursor(15, 1);
			lcd.print("]");
			lcd.setCursor(1, 1);
			for (int i = 0; i <= menuBarNum; i++) {
				if (i == menuBarNum) {
					lcd.print(">");
				}
				else {
					lcd.print("=");
				}
				

			}
		}
		
		
	}

	// Display
	if (buttonLast != buttonCurrent) {
		
	}
}