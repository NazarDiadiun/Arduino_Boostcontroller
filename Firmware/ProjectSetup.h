/*
   Файл настройки проекта, инициализации переменных, подключения бибилиотек
*/

//--------------LIBRARIES----------------

#ifdef LCD_I2C
// smth
#else
#include <LiquidCrystal.h> // Для дисплея (без I2C)
#endif

#include <EEPROM.h>                       // Библиотека для работы с энергонезависимой памятью
#include <AutoPID.h>                      // Библиотека для PID алгоритма

#include "GyverPID.h"


#define Keyboard_Pin A0                   // Пин подключения клавиатуры
#define Temperature_Sensor_Pin A1         // Пин подключения датчика температуры
#define Boost_Sensor_Pin A2               // Пин подключения датчика давления

#define PWM_OUTPUT 3                     // Пин для подключения клапана

char Display_First_Line[17] = {0};        // Первая строка дисплея
char Display_Second_Line[17] = {0};       // Вторая строка дисплея

double Current_Temperature = 0.00;         // Текущее значение температуры
double Current_Boost_Pressure = 0.00;      // Текущее значение давления

double Setted_Boost = 0.0;                 // Глобальная переменная для хранения выставленного значения наддува
double Last_Setted_Boost = 0.0;            // Переменная последнего выставленного значения надува для сохранения
double Setted_PID_Point = 0.00;            // Переменная отображает давление для PID алгоритма

byte Display_Page = 0;                     // Текущая страница на экране
double PWM_Valve_Output = 0;               // Значение сигнала, который открывает клапан

// Функция инициализации портов
void GPIO_Init()
{
  pinMode(Keyboard_Pin, INPUT);           // Пин для подключения клавиатуры
  pinMode(Temperature_Sensor_Pin, INPUT); // Пин для подключения датчика температуры
  pinMode(Boost_Sensor_Pin, INPUT);       // Пин для подключения датичка давления (надува)
  pinMode(PWM_OUTPUT, OUTPUT);            // Пин для подключения клапана
}
