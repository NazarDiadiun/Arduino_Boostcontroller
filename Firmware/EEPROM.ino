/*
   Вкладка для работы с энергонезависимой памятью

   Карта адресов EEPROM памяти:
     1 - Выставленное значение давления (float)
*/

// Функция для записи значений в энергонезависимую память
void Save_EEPROM()
{
  EEPROM.put(1, Setted_Boost);
}

// Функция для считывания значений с энергонезависимой памяти микроконтроллера
void Read_EEPROM()
{
  EEPROM.get(1, Setted_Boost);

  Serial.println("Values From EEPROM:");
  Serial.print("Setted Boost Pressure: ");
  Serial.print(Setted_Boost);
  Serial.println(" bar;");
}
