#ifndef LCD_H
#define LCD_H

void setupLCD();
void displayData(float temperature, float humidity, float temperatureInF);
void displayConnection(bool sucess);

#endif