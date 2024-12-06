#ifndef LLST
#define LLST

#include "includes.h"
#include "Node.h"
#include "List.h"
// Шаблонный класс для реализации двусвязного списка
_clstyping
class LinkedList
{
private:
    Node<_T>* head;
    Node<_T>* last;
    Node<_T>* current;
    int size;

public:
    // Конструктор, принимающий инициализатор списка для создания списка с начальными элементами
    LinkedList(std::initializer_list<_T>);
    LinkedList();
    ~LinkedList();

    bool is_empty();// Метод для проверки, пуст ли список

    Node<_T>* get_begin();
    Node<_T>* get_end();
    Node<_T>* get_current();

    Node<_T>* get_by_pos(int);

    int get_size();// Метод для получения размера списка (количества узлов)

    void insert(_T, int);
    void push_back(_T);

    void remove(int);

    void println();
};
// Конструктор класса LinkedList, который инициализирует список с помощью переданного списка инициализации
_clstyping
LinkedList<_T>::LinkedList(std::initializer_list<_T> _data)
{
    this->head = new Node<_T>(*(_data.begin()));// Создаем первый узел списка, используя первый элемент из инициализатора
    Node<_T>* curr = this->head;// Указатель curr будет использоваться для итерации по узлам списка
    this->size = 1;
    for (auto iter = _data.begin() + 1; // Итерируем по оставшимся элементам в инициализаторе, начиная со второго элемента
        iter != _data.end();
        ++iter)
    {
        curr->set_next(new Node<_T>(*iter));// Создаем новый узел для текущего элемента и устанавливаем его как следующий для curr
        curr = curr->get_next();
        this->size += 1; // Увеличиваем размер списка на 1
    }
    this->current = curr;
    this->last = curr;
}
// Метод для проверки, пуст ли список
_clstyping
bool LinkedList<_T>::is_empty()
{
    if (this->head == nullptr)// Если указатель head равен nullptr, значит список пуст
        return true;
    return false;
}
// Конструктор класса LinkedList, который инициализирует пустой связный список
_clstyping
LinkedList<_T>::LinkedList()
{
    this->head = nullptr;
    this->current = nullptr;
    this->last = nullptr;
    this->size = 0;
}
// Деструктор класса LinkedList, который освобождает память, занятую узлами списка
_clstyping
LinkedList<_T>::~LinkedList()
{// Проверяем, не пуст ли список перед удалением узлов
    if (!this->is_empty())
    { // Указатель candidat будет использоваться для удаления узлов списка, начиная с головы
        Node<_T>* candidat = this->head;
        if (this->size == 1)// Если в списке только один элемент, удаляем его
        {
            delete candidat;
        }
        else // Если в списке больше одного элемента, начинаем удаление узлов по очереди
        {
            Node<_T>* curr = candidat->get_next();// Получаем следующий узел после головы
            while (curr != nullptr)
            {
                delete candidat;
                candidat = curr;
                curr = curr->get_next();// Обновляем указатель curr на следующий узел
            }
            delete candidat;
        }
    }
}
// Метод для получения указателя на первый элемент списка (голову)
_clstyping
Node<_T>* LinkedList<_T>::get_begin()
{
    return this->head;
}
// Метод для получения указателя на последний элемент списка
_clstyping
Node<_T>* LinkedList<_T>::get_end()
{
    return this->last;
}
// Метод для получения указателя на текущий элемент списка
_clstyping
Node<_T>* LinkedList<_T>::get_current()
{
    return this->current;
}
// Метод для получения узла по заданной позиции (_pos)
_clstyping
Node<_T>* LinkedList<_T>::get_by_pos(int _pos)
{
    if (_pos < 0 || _pos >= this->size)// Проверка, находится ли позиция в допустимых границах
        return nullptr;

    Node<_T>* curr = this->head;
    int curr_pos = 0;
    while (curr_pos < _pos) // Проходим по списку до указанной позиции
    {
        curr = curr->get_next();// Переходим к следующему узлу
        ++curr_pos;
    }
    this->current = curr;// Обновляем указатель на текущий элемент
    return curr;
}
// Метод для получения текущего размера списка
_clstyping
int LinkedList<_T>::get_size()
{
    return this->size;
}
// Метод для добавления нового элемента в конец списка
_clstyping
void LinkedList<_T>::push_back(_T _data)
{
    Node<_T>* newnode = new Node<_T>(_data);// Создаем новый узел с переданными данными
    if (!this->is_empty()) // Проверяем, не пуст ли список
    {
        Node<_T>* endnode = this->get_end();
        endnode->set_next(newnode); // Устанавливаем следующий узел для последнего узла на новый узел
    }
    else // Если список пуст, новый узел становится головой списка
    {
        this->head = newnode;
    }
    this->last = newnode;
    this->current = newnode;
    this->size += 1;
}
// Метод для вставки нового элемента в заданную позицию списка
_clstyping
void LinkedList<_T>::insert(_T _data, int _pos)
{
    Node<_T>* newnode = new Node<_T>(_data);
    // Если позиция равна 0, вставляем новый узел в начало списка
    if (_pos == 0)
    {
        newnode->set_next(this->head); // Устанавливаем следующий узел для нового узла на текущую голову
        this->head = newnode;
    }
    else
    { // Получаем узел перед позицией, куда нужно вставить новый элемент
        Node<_T>* curr = this->get_by_pos(_pos - 1);

        newnode->set_next(curr->get_next());
        curr->set_next(newnode); // Устанавливаем следующий узел для текущего узла на новый узел
    }
    this->size += 1;
    this->current = newnode; // Устанавливаем текущий узел на новый узел
}
// Метод для удаления элемента из списка по заданной позиции
_clstyping
void LinkedList<_T>::remove(int pos)
{// Проверяем, находится ли позиция в допустимом диапазоне
    if (pos >= 0 && pos <= this->size)
    {
        Node<_T>* candidat = nullptr;
        if (pos == 0) // Если позиция равна 0, удаляем первый элемент списка
        {
            candidat = this->head;
            this->head = this->head->get_next();// Обновляем голову на следующий узел
        }
        else
        { // Получаем узел перед позицией, которую нужно удалить
            Node<_T>* curr = this->get_by_pos(pos - 1);
            candidat = curr->get_next();// Сохраняем указатель на узел, который нужно удалить

            curr->set_next(candidat->get_next());
            // Если удаляем не последний элемент, обновляем указатель предыдущего узла
            if (pos != this->size - 1)
                candidat->get_next()->set_prev(curr);
        }
        this->size -= 1;
        // Создаем новый узел с данными удаленного узла для текущего элемента
        this->current = new Node<_T>(candidat->get_data());
        this->current->set_prev(candidat->get_prev());
        this->current->set_next(candidat->get_next());

        delete candidat;// Освобождаем память, занятую удаляемым узлом
    }
}
// Метод для вывода всех элементов списка в консоль
_clstyping
void LinkedList<_T>::println()
{
    Node<_T>* curr = this->head;
    // Проходим по всем узлам до тех пор, пока не достигнем конца списка
    while (curr != nullptr)
    {
        std::cout << curr->get_data() << ' ';
        curr = curr->get_next();
    }
    std::cout << std::endl;// Печатаем перевод строки после вывода всех элементов
}

#endif
