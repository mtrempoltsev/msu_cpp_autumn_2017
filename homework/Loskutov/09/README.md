Домашнее задание №9
Задание:
Программе через аргументы командной строки передают два имени файлов. Первое имя - текстовый файл в котором слова разделены пробелами, его надо прочесть, составить частотный словарь "слово" - "сколько раз встречается". После этого надо отсортировать словарь по частоте и вывести во второй файл (его имя - второй аргумент).

Компиляция:
Программа sort_files компилируется с помощью команды: g++ sort_files.cpp -o sort_files --std=c++11

Пример
Вызов: ./sort_files input.txt output.txt

Файлы:
input.txt
трава дерево лес трава

output.txt
2 трава
1 дерево
1 лес