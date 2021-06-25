float PID_P = 2.0;
float PID_I = 1.0;
float PID_D = 0.2;

GyverPID regulator(PID_P, PID_I, PID_D, 10);  // коэф. П, коэф. И, коэф. Д, период дискретизации dt (мс)

void PID_Processing()
{

  regulator.input = Current_Boost_Pressure;   // сообщаем регулятору текущую температуру

  regulator.getResult();
  PWM_Valve_Output = regulator.output;
  Serial.println(PWM_Valve_Output);
  analogWrite(PWM_OUTPUT, PWM_Valve_Output);
}

void PID_Init()
{
  regulator.setDirection(NORMAL); // направление регулирования (NORMAL/REVERSE). ПО УМОЛЧАНИЮ СТОИТ NORMAL
  regulator.setLimits(0, 255);    // пределы (ставим для 8 битного ШИМ). ПО УМОЛЧАНИЮ СТОЯТ 0 И 255
  regulator.setpoint = Setted_Boost;        // сообщаем регулятору температуру, которую он должен поддерживать
}
