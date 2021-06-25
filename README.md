# Контроллер наддува на базе Arduino
Вывод информации про текущий и выставленный наддув, температуру на дисплей 1602
Возможность на лету менять выставленный наддув кнопками вверх и вниз
Перемещение между страницами дисплея осуществляется кнопкой select

## Датчик давления
Датчик наддува подключается к порту А2

## Датчик температуры
Датчик температуры подключается к порту А1.
Для считывания датчика необходимо подключать его вместе с постоянным или переменным резистором, с которым вместе они образуют делитель напряжения.
Сопротивление резистора должно быть равно сопротивлению термистора при 25 градусах цельсия, то есть, **1870 Ом**
Добиться такого точного значения можно подстроечным или переменным резистором