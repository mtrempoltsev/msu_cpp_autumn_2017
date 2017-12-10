### Компиляция

make или g++ -std=c++11 -Wall -Werror -Wextra -pthread main.cpp -o ping_pong  -O2

### Запуск

./ping_pong

### Описание

Два потока по очереди выводят в консоль сообщение. Первый выводит ping, второй выводит pong.

Вывод: ping pong ping pong ping pong …


### Демонстрация

demo.sh компилирует и запускает на 3 секунды (с использованием timeout)





