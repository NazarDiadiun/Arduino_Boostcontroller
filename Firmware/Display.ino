/*
   Вкладка отвечающая за обработку дисплея
*/

unsigned int Keyboard_Request_Interval = 150;      // Интервал опроса клавиатуры
unsigned long Keyboard_Request_Timer = 0;          // Таймер для опроса клавиатуры

unsigned long Display_Update_Timer = 0;            // Таймер для обновления данных на дисплее

// Создаём объект класса для дисплея

#ifdef LCD_I2C
// smth
#else
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Для дисплея (без I2C)
#endif

// Функция проверки нажатой кнопки
byte Keyboard_Button_Check()
{
  // Если пришло время считывать состояние клавиатуры
  if (millis() - Keyboard_Request_Timer > Keyboard_Request_Interval)
  {
    // Считываем напряжение на входе аналогового порта
    int Keyboard_Analog_Value = analogRead(Keyboard_Pin); // Заносим в локальную переменную

    Keyboard_Request_Timer = millis(); // Сбрасываем таймер

    // Если считанное значение подходит под границы кнопки select
    if (Keyboard_Analog_Value > SELECT_BUTTON - 50 && Keyboard_Analog_Value < SELECT_BUTTON + 50)
      return 1; // Возвращаем единицу (первая кнопка)
    // Если значение подходит для кнопки влево
    else if (Keyboard_Analog_Value > LEFT_BUTTON - 50 && Keyboard_Analog_Value < LEFT_BUTTON + 50)
      return 2; // Возвращаем двойку (вторая кнопка)
    // Если под кнопку вверх
    else if (Keyboard_Analog_Value > UP_BUTTON - 50 && Keyboard_Analog_Value < UP_BUTTON + 50)
      return 3; // Возвращаем тройку (третья кнопка)
    // Вниз
    else if (Keyboard_Analog_Value > DOWN_BUTTON - 50 && Keyboard_Analog_Value < DOWN_BUTTON + 50)
      return 4; // Возвращаем четвёрку (четвёртая кнопка)
    // Вправо
    else if (Keyboard_Analog_Value < 20)
      return 5; // Возвращаем пятёрку (пятая кнопка)
    // Если не нажата кнопка, будем иметь постоянно 1023 (5в на входе)
    else if (Keyboard_Analog_Value > 1000)
      return 0; // Возвращаем ноль (не нажата кнопка)
  }

  return 0; // Если не нажата кнопка, или по какой либо причине не удалось считать состояние - возвращаем ноль
}

void Display_Preparing()
{
  if (Display_Page == 0) // Если страница для датчика давления
  {
    char PressureBuffer[5] = {0}; // Временный буфер для преобразования числа в строку
    dtostrf(Current_Boost_Pressure, 4, 2, PressureBuffer); // Преобразование числа в строку

    sprintf(Display_First_Line, "Boost: %s bar  ", PressureBuffer); // Собираем строку для вывода на дисплей
    memset(PressureBuffer, 0, 5);

    dtostrf(Setted_Boost, 3, 1, PressureBuffer); // Преобразование числа в строку
    sprintf(Display_Second_Line, "Set: %s bar  ", PressureBuffer); // Собираем строку для вывода на дисплей
  }
  else if(Display_Page == 1) // Если страница с температурой, клапаном
  {
    char TemperatureBuffer[7] = {0}; // Временный буфер для преобразования числа в строку
    dtostrf(Current_Temperature, 6, 2, TemperatureBuffer); // Преобразование числа в строку

    sprintf(Display_First_Line, "Temp: %s C  ", TemperatureBuffer); // Собираем строку для вывода на дисплей
    sprintf(Display_Second_Line, "Valve: %d%c    ", PWM_Valve_Output, '%'); // Собираем строку для вывода на дисплей
  }
}

// Функция для обновления данных на дисплее
void Update_Display(unsigned int Update_Interval)
{
  if (millis() - Display_Update_Timer > Update_Interval)
  {
    lcd.setCursor(0, 0); // Курсор на первую строку
    lcd.print(Display_First_Line); // Выводим строку
    lcd.setCursor(0, 1); // Курсор на вторую строку
    lcd.print(Display_Second_Line); // Выводим вторую строку

    Display_Update_Timer = millis(); // Обнуляем таймер до следующего "кадра"
  }
}

void Display_Init()
{
#ifdef LCD_I2C
  // smth
#else
  lcd.begin(16, 2); // Инициализация дисплея, 16 символов, 2 строки (без I2C)
#endif
}
