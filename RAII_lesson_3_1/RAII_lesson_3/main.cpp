/*Задача 1. Умный массив
Описание

Вам нужно реализовать умный массив для данных типа int в духе идиомы RAII, который сам управляет своей памятью: самостоятельно выделяет её при создании и очищает, когда объект данного класса не используется.

Должны быть реализованы следующие функции:

    Конструктор, принмающий количество элементов, которое будет хранить массив.
    Функция добавления нового элемента в массив. Не забудьте обработать случай, когда количество элементов больше количества элементов, на которую выделена память.
    Функция получения элемента по индексу. Не забудьте проверку на корректность индекса.
    Деструктор.

Пример правильной работы программы

Работа с вашим классом должна происходить так:

try {
  smart_array arr(5);
  arr.add_element(1);
  arr.add_element(4);
  arr.add_element(155);
  arr.add_element(14);
  arr.add_element(15);
  std::cout << arr.get_element(1) << std::endl;
}
catch (const std::exception& ex) {
  std::cout << ex.what() << std::endl;
}

*/

//РЕШЕНИЕ:

#include <iostream>
#include <stdexcept>

class smart_array {
private:
int* arr; // указатель на массив
size_t size; // указатель на размер массива
size_t capacity; // максимальная вместимость массива

// функция для увеличения размера массива
void resize(size_t new_capacity){ // new_capacity - новый размер массива
  int* new_arr = new int [new_capacity]; // создаем новый массив
  for (size_t i = 0; i < size; i++){// копируем данные из старого массива в новый
    new_arr[i] = arr[i];
  }
  delete[] arr; // освобождаем память, занятую старым массивом
  arr = new_arr;
  capacity = new_capacity;
}

public:
// конструктор
smart_array(size_t initial_capacity):size(0), capacity(initial_capacity){
  if (initial_capacity == 0){
    throw std::invalid_argument("Initial capacity must be greater than zero.");
  }
  arr = new int [capacity];
}
// деструктор
~smart_array(){
  delete[] arr;
}
//функция добавления нового эллемента в массив
void add_element(int element){
  if (size >= capacity){ // если массив заполнен
    resize (capacity * 2); // увеличиваем его в 2 раза
  }
  arr[size++] = element; //добавлем новый элемент в конец масссива
}
// функция получения элемента по индексу
int get_element(size_t index) const{
  if (index >= size){ // если индекс выходит за пределы массива
    throw std::out_of_range("Index out of bounds.");
  }
  return arr[index];
}
};

int main(){
  try{
    smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);
    arr.add_element(14);
    arr.add_element(15);

    // добавим еще один элемент
    arr.add_element(20);

    // выводим элементы массива
    std::cout << arr.get_element(1) << std::endl;
     std::cout << arr.get_element(5) << std::endl;
  } catch (const std::exception& ex){
    std::cout << ex.what()<< std::endl;
  }
  return 0;
}


/*


   1) Конструктор smart_array(size_t initial_capacity): Инициализирует массив с указанной вместимостью и выделяет память. Если вместимость равна 0, выбрасывается исключение std::invalid_argument.

    2) Деструктор ~smart_array(): Освобождает память, выделенную для массива.

   3) Метод add_element(int element): Добавляет элемент в массив. Если массив заполнен, увеличивает его вместимость в два раза.

   4) Метод get_element(size_t index): Возвращает элемент по индексу. Если индекс выходит за пределы текущего размера массива, выбрасывается исключение std::out_of_range.

Этот класс реализует основные принципы RAII, управляя ресурсами (в данном случае памятью) на протяжении жизни объекта.
*/
