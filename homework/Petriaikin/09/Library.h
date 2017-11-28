#ifndef LIBRARY_H
#define LIBRARY_H

//========================================================================

#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <exception>

//========================================================================

//Слово, частота
typedef std::map<std::string, size_t> map_type;
typedef std::pair<std::string, size_t> map_value_type;

//========================================================================

//Подсчитвывает частотность слов в документе, возвращая соответствющий map
map_type ParseFile(std::string file_name);

//Возвращает вектор из пар<ключ, элемент>, входящих в map, отсортированный по элементам, а потом по алфавиту (для сравнения с контролем)
std::vector<map_value_type> GetMapValuesSorted(const map_type& map, bool increase = false);

//Возвращает map из случайных слов (частоты случаеные)
map_type GetRandomMap(size_t count_words = 200, size_t max_frequency = 50, size_t max_len = 10);

//Записывает map в файл в виде слов в случайном порядке
void WriteFileFromMap(std::string file_name, const map_type& map);

//Записывает в файл отсортированный массив (ответ на задачу)
void WriteVectorToFile(std::string file_name, const std::vector<map_value_type>& map);

//========================================================================

#endif