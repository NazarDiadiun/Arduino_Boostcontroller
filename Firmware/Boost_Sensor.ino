/*
   Вкладка отвечает за обработку датчика давления
*/

unsigned long Boost_Timer = 0; // Таймер для опроса датчика давления

// Датчик давления имеет линейную зависимость напряжения на выходе от давления
// Можем используя математические преобразования получить из напряжения - давление в барах
// Напряжение на входе от 0.5В до 4.5В при 0.5 бар до 4 бар соответственно
// Разрешение АЦП ATmega328 - 10bit (0 - 1023) при напряжении питания 5В будем иметь разрешение 204.6 / 1V
// Таким образом, при значениях на входе АЦП от 102.3 до 920.7 будем иметь давление от 0.5 до 4 бар

// Функция возвращает значение давления с датчика
void Get_Boost(int Sensor_Frequency)
{
  if (millis() - Boost_Timer > (1000 / Sensor_Frequency))
  {
    int Boost_Analog_Value = analogRead(Boost_Sensor_Pin); // Получаем значение с порта

    // Преобразовываем значение с АЦП микроконтроллера в значение давления в барах
    Current_Boost_Pressure = mapfloat(Boost_Analog_Value, 102.3, 920.7, -0.5, 3.0);

    /*if (Current_Boost_Pressure < -0.5)
      Current_Boost_Pressure = -0.5;
    if (Current_Boost_Pressure > 3.0)
      Current_Boost_Pressure = 3.0;*/

    //Serial.print("Current Boost Value: ");
    //Serial.print(Current_Boost_Pressure);
    //Serial.println(" bar");

    Boost_Timer = millis(); // Сбрасываем таймер
  }
}

// Функция для преобразования числа в границы для чисел с плавающей точкой
float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}
