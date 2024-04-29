# SmartCalc

Десктопное приложение для вычеслений и построения графика.</br>
График имеет настраиваемый маштаб.</br>
При разработке использовался архетектурный паттерн MVC с тонким контроллером. В контроллере производится валидация, введённой строки. В моделе строка разбивается на токены, производятся вычисления с помощью обратной польской нотации и возвращает ответ на вью. Многократным вызывом вычислений строится массив значений для графика.

![](pics/sin(x-4).png)</br>_Пример вывода графика №1_</br></br>
![](pics/sin(x)+cos(x)+x.png)</br>_Пример вывода графика №2_</br></br>
![](pics/sqrt(x).png)</br>_Пример вывода графика №3_</br></br>
![](pics/x^2.png)</br>_Пример вывода графика №4_</br></br>