/*
   Вкладка для взаимодействия устройства с пользователем
*/
unsigned long EEPROM_Save_Timer = 0; // Таймер для сохранения в энергонезависимую память

void Buttons_Control()
{
  // Считываем текущую нажатую кнопку
  byte PressedKey = Keyboard_Button_Check();

  // Если нажата какая-то кнопка
  if (PressedKey != 0)
  {
    if (PressedKey == 1) // Select
    {
      Serial.println("Select");

      Display_Page++; // Перелистываем страницу

      if (Display_Page > 1) // Если перелистали слишком далеко
        Display_Page = 0; // Возвращаемся в начало
    }
    if (PressedKey == 2) // Left
      Serial.println("Left");
    if (PressedKey == 3) // Up
    {
      Serial.println("Up");

      if (Setted_Boost < BOOST_MAX - 0.1) // Если выставленное значение ниже предела
      {
        Setted_Boost += 0.1;  // Добавляем 0.1
        regulator.setpoint = Setted_Boost;
        EEPROM_Save_Timer = millis();
      }
    }
    if (PressedKey == 4) // Down
    {
      Serial.println("Down");

      if (Setted_Boost > BOOST_MIN + 0.1) // Если значение всё еще больше нуля
      {
        Setted_Boost -= 0.1;  // Отнимаем 0.1
        regulator.setpoint = Setted_Boost;
        EEPROM_Save_Timer = millis();
      }
    }
    if (PressedKey == 5) // Rigth
      Serial.println("Rigth");
  }

  // Если нажали на кнопку изменения надува, и с момента установки прошла секунда - сохраняем
  if (Last_Setted_Boost != Setted_Boost && millis() - EEPROM_Save_Timer > 1000)
  {
    Save_EEPROM();                          // Сохраняем значение надува в энергонезависимую память
    Last_Setted_Boost = Setted_Boost;       // Последнее значение надува равно текущему
    EEPROM_Save_Timer = millis();           // Сброс таймера ожидания
  }
}
