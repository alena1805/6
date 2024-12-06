#ifndef HSET
#define HSET

#include "LinkedList.h"

_clstyping  // список с уникальными значениями 
class HashSet
{
private:
    LinkedList<_T>* llst; // Указатель на связный список для хранения элементов множества

public:
    HashSet(std::initializer_list<_T>);
    /* HashSet(auto, auto);*/
    HashSet();
    ~HashSet();

    bool is_empty();// Метод для проверки, пусто ли множество

    Node<_T>* get_begin();
    Node<_T>* get_end();

    bool append(_T);
    void remove(_T);

    LinkedList<_T>* get_keys();// Метод для получения всех ключей (элементов) множества в виде связного списка
    _T get_elem(_T);

    HashSet<_T>* union_with(HashSet<_T>*);
    void except(HashSet<_T>*);// Метод для исключения элементов другого множества из текущего
    HashSet<_T>* intersect(HashSet<_T>*);
    bool contains(_T);

    void println();
};

_clstyping  // проверяем, если вставляемый эл-нт на уникальность 
bool is_repeat(Node<_T>_begin, Node<_T> _end, _T _elem)
{
    // Проходим по всем узлам от начала до конца
    for (
        auto iter = _begin;
        iter != _end;
        ++iter
        )
    {// Если найден элемент с таким же значением, возвращаем true
        if (iter->get_data() == _elem) return true;
    }
    return false;
}

_clstyping  // удаляем элемент
void removed(LinkedList<_T>& llst, int _pos)
{
    if (_pos >= 0 && _pos < llst.get_size())
        llst.remove(_pos);
}

_clstyping  // создаем новый список
HashSet<_T>::HashSet()
{
    this->llst = new LinkedList<_T>();
}

_clstyping  // создаем список с элементами initializer_list
HashSet<_T>::HashSet(std::initializer_list<_T> _init)
{
    this->llst = new LinkedList<_T>();
    // Проходим по всем элементам инициализаторного списка
    for (
        auto iter = _init.begin();
        iter != _init.end();
        ++iter
        )
    { // Проверяем, существует ли уже элемент в списке
        if (!is_repeat(_init.begin(), _init.end(), *iter))
            this->llst->push_back(*iter);// Если элемент уникален, добавляем его в связный список
    }
}

_clstyping  // проверяем на существование списка
bool HashSet<_T>::is_empty()
{
    return this->llst->is_empty();
}

_clstyping  // чистим список
HashSet<_T>::~HashSet()
{
    delete this->llst;// Освобождаем память, занятую связным списком
}

_clstyping  // получаем начало списка
Node<_T>* HashSet<_T>::get_begin()
{
    return this->llst->get_begin();// Возвращаем указатель на начало связного списка
}

_clstyping  // получаем конец
Node<_T>* HashSet<_T>::get_end()
{
    return this->llst->get_end();
}

_clstyping  // добавляем новый элемент
bool HashSet<_T>::append(_T _elem)
{// Проверяем, содержится ли элемент уже
    if (!this->contains(_elem))
    {// Если элемент уникален, добавляем его в связный список
        this->llst->push_back(_elem);
        return true;
    }
    return false;
}

_clstyping  // удаляем элеменнт
void HashSet<_T>::remove(_T _elem)
{
    int pos = 0;
    bool is_find = false;// Флаг для отслеживания, найден ли элемент
    for (auto iter = this->get_begin(); // Проходим по всем элементам списка, начиная с первого
        iter != this->get_end() && !is_find; ++iter
        )
    {// Сравниваем текущий элемент со значением, которое нужно удалить
        if (*iter.get_data() == _elem) is_find = true;
        ++pos;
    }
    removed<_T>(this->llst, --pos);// Если элемент найден, удаляем его из связного списка по позиции
}

_clstyping  // получаем указатель на список
LinkedList<_T>* HashSet<_T>::get_keys()
{
    return this->llst;
}

_clstyping  // объединение двух списков 
HashSet<_T>* HashSet<_T>::union_with(HashSet<_T>* _h_set)
{
    LinkedList<_T>* tmp_lst = new LinkedList<_T>();// Создаем временный связный список для хранения уникальных элементов
    for ( // Проходим по всем элементам второго множеств
        auto iter = _h_set->get_begin();
        iter != _h_set->get_end();
        iter = iter->get_next()
        )
    { // Проверяем, не содержится ли элемент уже в текущем множестве
        if (!is_repeat(this->get_begin(),
            this->get_end(), *iter)
            )
            this->tmp_lst->push_back(*iter);
    }// Создаем новое множество на основе временного списка уникальных элементов
    HashSet<_T>* tmp_set = new HashSet<_T>(
        tmp_lst->get_begin(), tmp_lst->end()
    );
    delete tmp_lst;

    return tmp_set;
}

_clstyping  // удаляем из текущ списка элемент из HashSet
void HashSet<_T>::except(HashSet<_T>* _h_set)
{
    int pos = 0;
    for (// Проходим по всем элементам второго множества
        auto iter = _h_set->get_begin();
        iter != _h_set->get_end();
        )
    {// Проверяем, содержится ли элемент из второго множества в текущем множестве
        if (is_repeat(this->get_begin(), this->get_end(), *iter))
        {
            iter = iter->get_next(); // next step before remove
            this->llst->remove(pos); // because remove removed iter
        }
        else
        {// Если элемент не найден, переходим к следующему элементу и увеличиваем позицию
            iter = iter->get_next();
            ++pos;
        }
    }
}
_clstyping  // получаем новый список из совпадающих эл-ов
HashSet<_T>* HashSet<_T>::intersect(HashSet<_T>* _h_set)
{
    LinkedList<_T>* tmp_lst = new LinkedList<_T>();
    for (// Проходим по всем элементам второго множества
        auto iter = _h_set->get_begin();
        iter != _h_set->get_end();
        iter = iter->get_next()
        )
    {// Проверяем, содержится ли текущий элемент второго множества в первом множестве
        if (is_repeat(this->get_begin(),
            this->get_end(), *iter)
            )
            this->tmp_lst->push_back(*iter);// Если элемент найден, добавляем его во временный список
    }
    HashSet<_T>* tmp_set = new HashSet<_T>(
        tmp_lst->get_begin(), tmp_lst->end()
    );
    delete tmp_lst;

    return tmp_set;
}

_clstyping  // проверка на существование элемента в списке
bool HashSet<_T>::contains(_T _elem)
{
    Node<_T>* curr = this->get_begin();// Начинаем с первого элемента
    while (curr != nullptr)// Проходим по всем элементам списка
    {
        if (curr->get_data() == _elem) return true;// Если текущий элемент равен искомому, возвращаем true
        curr = curr->get_next();
    }

    return false;
}

_clstyping  // вывод
void HashSet<_T>::println()
{
    this->llst->println();// Вызываем метод вывода для связного списка, который хранит элементы множества
}

#endif
