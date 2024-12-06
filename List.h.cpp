#ifndef LST
#define LST

#include "includes.h"
#include "Node.h"

_clstyping
class List
{
private:
    Node<_T>* head; // Указатель на первый элемент списка (голову)
    int size;

public:
    // Конструктор, который принимает список инициализации для создания списка
    List(std::initializer_list<_T>);
    ~List();

    Node<_T>* get_begin(); // Метод для получения указателя на первый элемент списка
    Node<_T>* get_end();
    Node<_T>* get_by_pos(int);

    int get_size();// Метод для получения текущего размера списка (количества элементов)

    void insert(_T, int);// Метод для вставки элемента в список по заданной позиции
    void push_back(_T);

    void remove(int); // Метод для удаления элемента по заданной позиции

    void println();
};


_clstyping
List<_T>::List(std::initializer_list<_T> _data)
{
    // Создаем новый узел (Node) и устанавливаем его как голову списка,
    // инициализируя его значением первого элемента из _data.
    this->head = new Node<_T>(*(_data.begin()));
    Node<_T>* current = this->head;
    this->size = 1;
    // Проходим по оставшимся элементам в _data, начиная со второго элемента.
    for (auto iter = _data.begin() + 1;
        iter != _data.end();
        ++iter)
    {   // Создаем новый узел с текущим элементом и устанавливаем его как следующий для текущего узла
        current->set_next(new Node<_T>(*iter));
        current = current->get_next();
        this->size += 1; // Увеличиваем размер списка на 1 для каждого добавленного элемента
    }
}

_clstyping
List<_T>::~List()
{   // Указатель для обхода списка, начинаем с головы
    Node<_T>* candidat = this->head;
    if (this->size == 1) // Проверяем, если размер списка равен 1
    {
        delete candidat;
    }
    else
    {    // Если в списке больше одного элемента, начинаем обход
        Node<_T>* current = candidat->get_next();
        while (current != nullptr) // Цикл для удаления всех узлов в списке
        {
            delete candidat;
            candidat = current;
            current = current->get_next(); // Перемещаем указатель current на следующий узел
        }
        delete candidat;
    }
}
// Функция для получения указателя на первый элемент списка
_clstyping
Node<_T>* List<_T>::get_begin()
{
    return this->head;
}
// Функция для получения указателя на последний элемент списка
_clstyping
Node<_T>* List<_T>::get_end()
{
    Node<_T>* current = this->head;
    // Цикл для обхода списка до конца.
    // Продолжаем, пока следующий узел не равен nullptr (т.е. не достигли конца списка)
    while (current->get_next() != nullptr)
        current = current->get_next();
    return current; // Возвращаем указатель на последний узел, на который указывает current
}
// Функция для получения указателя на узел по заданной позиции
_clstyping
Node<_T>* List<_T>::get_by_pos(int _pos)
{
    // Проверяем, что позиция _pos находится в допустимом диапазоне.
    // Если _pos меньше 0 или больше или равен размеру списка, возвращаем nullptr
    if (_pos < 0 || _pos >= this->size)
        return nullptr;

    Node<_T>* current = this->head;
    int curr_pos = 0;
    // Цикл для обхода списка до заданной позиции _pos
    while (curr_pos < _pos)
    {   // Перемещаем указатель current на следующий узел
        current = current->get_next();
        ++curr_pos; // Увеличиваем текущую позицию на 1
    }
    return current;
}
// Функция для получения размера списка
_clstyping
int List<_T>::get_size()
{
    return this->size;
}
// Функция для добавления нового элемента в конец списка
_clstyping
void List<_T>::push_back(_T _data)
{
    // Создаем новый узел с переданными данными _data
    Node<_T>* newnode = new Node<_T>(_data);
    // Получаем указатель на последний узел списка
    Node<_T>* endnode = this->get_end();
    // Устанавливаем следующий узел последнего узла на новый узел
    endnode->set_next(newnode);
}
// Функция для вставки нового элемента в список по заданной позиции
_clstyping
void List<_T>::insert(_T _data, int _pos)
{// Создаем новый узел с переданными данными _data
    Node<_T>* newnode = new Node<_T>(_data);
    // Проверяем, если позиция вставки равна 0 (вставка в начало списка)
    if (_pos == 0)
    {
        newnode->set_next(this->head);
        this->head = newnode;
    }
    else
    {    // Получаем указатель на узел, предшествующий позиции вставки
        Node<_T>* current = this->get_by_pos(_pos - 1);

        newnode->set_next(current->get_next());
        current->set_next(newnode);
    }
    this->size += 1;// Увеличиваем размер списка на 1 после вставки нового узла
}
// Функция для удаления узла из списка по заданной позиции
_clstyping
void List<_T>::remove(int pos)
{
    Node<_T>* candidat = nullptr;
    if (pos == 0) // Проверяем, если позиция равна 0 (удаление первого элемента)
    {
        candidat = this->head;
        this->head = this->head->get_next();// Обновляем голову списка на следующий узел
    }
    else
    {
        Node<_T>* current = this->get_by_pos(pos - 1);// Получаем указатель на узел, предшествующий позиции удаления
        candidat = current->get_next(); // Сохраняем указатель на узел, который нужно удалить
        current->set_next(candidat->get_next());
    }
    this->size -= 1;// Уменьшаем размер списка на 1 после удаления узла

    delete candidat;
}
// Функция для вывода всех элементов списка в консоль
_clstyping
void List<_T>::println()
{
    Node<_T>* current = this->head;// Указатель на текущий узел, начинаем с головы списка
    while (current != nullptr)// Цикл для перебора всех узлов до конца списка
    {
        std::cout << current->get_data() << ' ';
        current = current->get_next();
    }
    std::cout << std::endl;// Печатаем перевод строки после вывода всех данных
}

#endif
