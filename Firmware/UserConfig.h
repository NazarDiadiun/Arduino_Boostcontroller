/*
   Файл пользовательской настройки проекта
*/

// Если какой-то из параметров или опций не нужен - закоментировать строку двойным слэшем

// #define LCD_I2C // Дисплей подключается по I2C шине

#define BOOST_MAX 3.0 // максимальное давление, которое можно выставить (бар)
#define BOOST_MIN -0.5 // минимальное давление, которое можно выставить (бар)

// Так как клавиатура представляет собой пять кнопок подключенных к одному порту через разные сопротивления
// В зависимости от нажатой кнопки будем иметь разное напряжение на входе. Измеряем его, и заносим сюда
#define SELECT_BUTTON    726
#define LEFT_BUTTON      486
#define UP_BUTTON        134
#define DOWN_BUTTON      312
#define RIGTH_BUTTON      0
