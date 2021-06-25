/*
   Вкладка для обработки датчика температуры

    Калькулятор для расчёта значений Стейнхарта-Харта для термистора:
    https://www.thinksrs.com/downloads/programs/Therm%20Calc/NTCCalibrator/NTCcalculator.htm
*/

unsigned long Temperature_Timer = 0; // Таймер для опроса датчика температуры
float Sensor_25Degrees_Resistance = 1870; // Сопротивление датчика при 25 градусах цельсия

// Коэффициенты Стейнхарта-Харта
float A_Coef = 1.275079634e-03;
float B_Coef = 2.638161228e-04;
float C_Coef = 1.790094351e-07;

// Для замера температуры, помимо значений коеффициентов и сопротивления при 25 градусах, необходимо создать делитель напряжения
// Чтобы АЦП микроконтроллера мог замерить его, и исходя из полученых сырых данных - рассчитывать температуру используя уравнения
// Для повышения точности измерения, необходимо точно подобрать резистор во втором плече делителя. Его сопротивление
// Должно быть таким же, или максимально приближенным к сопротивлению датчика при 25 градусах цельсия, то есть
// Сопротивление второго резистора в делителе, в нашем случае, должно быть 1870 Ом.
// Добиться такой точности можно использовав переменный или подстроечный резистор, постоянно контроллируя сопротивление мультиметром

void Get_Temperature(int Request_Frequency)
{
  if (millis() - Temperature_Timer > (1000 / Request_Frequency))
  {
    // Снимаем сырое значение с аналогового порта микроконтроллера
    int Temperature_Analog_Value = analogRead(Temperature_Sensor_Pin);

    // Затем, зная, что сопротивление второго плеча делителя у нас такое же, как и у датчика при 25 градусах - находим сопротивление
    // Термистора в данный момент времени
    float Temperature_Sensor_Resistance = Sensor_25Degrees_Resistance * (1023.0 / (float)Temperature_Analog_Value - 1.0);

    // После чего получаем логарифм от сопротивления, который будем использовать в уравнении
    float Log_Temperature_Sensor_Resistance = log(Temperature_Sensor_Resistance);

    // Используя уравнение Стейнхарта-Харта (T  = 1 / {A + B[ln(R)] + C[ln(R)]^3}) - рассчитываем температуру
    Current_Temperature = (1.0 / (A_Coef + Log_Temperature_Sensor_Resistance * Log_Temperature_Sensor_Resistance + C_Coef *
                                  Log_Temperature_Sensor_Resistance * Log_Temperature_Sensor_Resistance * Log_Temperature_Sensor_Resistance));

    // Так как температуру мы получили в кельвинах - отнимаем 273, чтобы преобразовать в цельсий
    Current_Temperature -= 273.15;

    // Сбрасываем таймер
    Temperature_Timer = millis();
  }
}
