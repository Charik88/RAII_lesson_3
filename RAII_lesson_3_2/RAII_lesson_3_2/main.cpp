/*Задача 2. Копирование умных массивов
Описание

В этом задании вам нужно поработать с классом умных массивов, который вы реализовали в предыдущем задании. Сначала попробуйте создать два экземпляра вашего класса с различными элементами и присвоить один другому.

smart_array arr(5);
arr.add_element(1);
arr.add_element(4);
arr.add_element(155);

smart_array new_array(2);
new_array.add_element(44);
new_array.add_element(34);

arr = new_array
*/
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
  for (size_t i = 0; i < size; ++i){ // копируем данные из старого массива в новый
  new_arr[i] = arr[i]; // копируем элементы из старого массива в новый
  }

  delete[] arr; // освобождаем память, занятую старым массивом
  arr = new_arr; // переназначаем указатель на новый массив
  capacity = new_capacity; // обновляем максимальную вместимость массива
}

public:
// конструктор
smart_array(size_t initial_capacity): size(0), capacity(initial_capacity){
  if (initial_capacity == 0){ // если вместимость равна 0, выбрасываем исключение
    throw std::invalid_argument("Initial capacity must be greater than zero."); // исключение
  }
  arr = new int [capacity]; // выделяем память для массива
}
// деструктор
~smart_array(){
  delete[] arr;
}
// конструктор копирования
smart_array(const smart_array& other) : size(other.size), capacity(other.capacity){ // копируем размер и максимальную вместимость из другого обьекта
  arr = new int [capacity]; // выделяем память для нового массива
  for (size_t i = 0; i < size; ++i){ // копируем элементы из другого массива в новый
    arr[i] = other.arr[i];
  }
}
// оператор присваивания
smart_array& operator=(const smart_array& other) { // присваивание другому обьекту
  if (this != &other) { // проверяем, чтобы не было самоприсваивания
    delete[] arr; // освобождаем память, занятую текущим массивом
    size = other.size;
    capacity = other.capacity;
    arr = new int [capacity];
    for (size_t i = 0; i < size; ++i){
      arr[i] = other.arr[i];

  }
}
return *this;
}

// ф-ия добавления нового элемента в массив
void add_element(int element){
  if (size >= capacity){ // если массив заполнен
    resize(capacity * 2); // увеличиваем его в 2 раза
  }
  arr[size++] = element;
}

// ф-ия получения элемента по индексу
int get_element(size_t index) const{
  if (index >= size) {
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

    smart_array new_array(2);
    new_array.add_element(56);
    new_array.add_element(44);

    // присваивание другому обьекту
    arr = new_array;
    std::cout << "arr[0] = " << arr.get_element(0) << std::endl;
    std::cout << "arr[1] = " << arr.get_element(1) << std::endl;
  } catch (const std::exception& ex){
    std::cout << "Exception: " << ex.what() << std::endl;
  }
    return 0;
}


