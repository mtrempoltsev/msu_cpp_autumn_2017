# Результаты выполнения программ:

Компиляция:
anton@anton-VirtualBox:~/msu_cpp_autumn_2017/homework/Shevtsov/01$ g++ sum_by_rows.cpp -o sum_by_rows --std=c++11 -O2
anton@anton-VirtualBox:~/msu_cpp_autumn_2017/homework/Shevtsov/01$ g++ sum_by_columns.cpp -o sum_by_columns --std=c++11 -O2

По столбцам:
anton@anton-VirtualBox:~/msu_cpp_autumn_2017/homework/Shevtsov/01$ ./HW_by_columns
1624987us
По строкам:
anton@anton-VirtualBox:~/msu_cpp_autumn_2017/homework/Shevtsov/01$ ./HW_by_rows
277323us


По стобцам дольше в 5.8 раз, что и не удивительно, ведь процессор при выполнении программы
будет считывать информацию не последовательно идя по ячейкам памяти, а прыгать из одной области памяти в другую.

Изменил:
 - поставил volantile, чтобы компилятор не оптимизировал
 - использовал двумерный массив
 - поставил Timer t непосредственно перед запуском алгоритма, чтобы не считалось время не относящееся к выполнению счета
