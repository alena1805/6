#ifndef NODE
#define NODE

#include "includes.h"

_clstyping  // класс объявление шаблона
class Node
{
private:
    _T data;
    Node<_T>* next;
    Node<_T>* prev;

public:
    Node(_T);
    ~Node();

    Node* get_next();
    _T get_data();

    void set_next(Node*);  // установить значение
    void set_prev(Node*);

    Node* get_prev();  // взять значение
    void set_data(_T);
};

_clstyping
Node<_T>::Node(_T _data)
{
    // классу присвоить значение
    this->data = _data;
    this->next = nullptr;  // пустой указатель
    this->prev = nullptr;
}

_clstyping
Node<_T>::~Node()  // деструктор вызывается, когда объект выходит из области видимости
{
}

_clstyping
Node<_T>* Node<_T>::get_next()  // обращение к next
{
    return this->next;
}

_clstyping
Node<_T>* Node<_T>::get_prev()// Метод для получения указателя на предыдущий узел в двусвязном списке
{
    return this->prev;
}

_clstyping// Метод для получения данных, хранящихся в текущем узле
_T Node<_T>::get_data()
{
    return this->data;
}

_clstyping
void Node<_T>::set_next(Node<_T>* _next)  // установить 
{
    this->next = _next;
}

_clstyping
void Node<_T>::set_prev(Node<_T>* _prev)
{
    this->prev = _prev;// Устанавливаем указатель prev текущего узла на переданный указатель _prev
}

#endif
