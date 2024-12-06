
#include "List.h"
#include "LinkedList.h"
#include "HashSet.h"


template <typename _T>
bool pair_searches(List<_T>& lst)
{
    int count = 0;
    _T elem; // Переменная для хранения текущего элемента из списка
    // Проходим по всем элементам списка
    for (int pos = 0; pos < lst.get_size(); ++pos)
    {
        elem = lst.get_by_pos(pos)->get_data(); // Получаем данные текущего узла по позиции pos
        // Ищем совпадения с текущим элементом среди последующих элементов списка
        for (Node<_T>* node = lst.get_by_pos(pos + 1);
            node != nullptr; node = node->get_next()
            )
        {   // Если находим элемент, равный текущему, возвращаем true
            if (node->get_data() == elem) return true; 
        }
    }
    return false;
}

template<typename _T>
void clean_occurrence(LinkedList<_T>& llst, _T elem)
{
    bool flag = true; // Флаг для отслеживания, было ли удалено хотя бы одно вхождение элемента
    for (int pos = 0; pos < llst.get_size() && flag; ++pos) // Проходим по всем элементам списка до тех пор, пока не достигнем конца списка или не удалим элемент
    {
        if (llst.get_by_pos(pos)->get_data() == elem) // Проверяем, равен ли текущий элемент искомому
        {
            llst.remove(pos); // Удаляем элемент, если он равен искомому
            flag = false;
        }
    }
}

void music()
{
    int meolomans = 500000;
    std::vector<std::pair<int, const char*>> mus_chart(
        {
            {1000, "Рэп из Камызяк"},
            {0, "Северокорейская попса"},
            {1, "Гимн Зибвабве"},
            {123000, "Шопен этюд 1"},
            {11300, "Мусоргской"},
            {123000, "Тор-100 2024"},
            {meolomans, "Кишлак"}
        }
    );

    std::cout << "Название трека : кол-во прослушиваний\n";
    for (const auto& data : mus_chart) // Проходим по всем элементам музыкального чарта
    {
        std::cout << data.second << " : " << data.first << std::endl;
    }
    std::cout << std::endl;
    // Создаем множество для хранения уникальных количеств прослушиваний
    HashSet<int> unique_audit;
    for (auto iter = mus_chart.begin(); iter != mus_chart.end(); ++iter)// Проходим по музыкальному чарту и добавляем количество прослушиваний в множество
    {
        unique_audit.append(iter->first); // Добавляем количество прослушиваний в уникальное множество
    }

    std::cout << "Кол-во меломанов: " << meolomans << std::endl;
    Node<int>* curr = unique_audit.get_begin();
    while (curr != nullptr) // Проходим по всем уникальным количествам прослушиваний
    {
        std::cout << "  Кол-во прослушиваний: " << curr->get_data() << std::endl; // Выводим текущее количество прослушиваний
        for (const auto& iter : mus_chart) // Проходим по музыкальному чарту для поиска треков с текущим количеством прослушиваний
        {
         // Если количество прослушиваний совпадает, выводим название трека
            if (iter.first == curr->get_data())
                std::cout << "      Название трека: "
                << iter.second << std::endl;
        }
        curr = curr->get_next();// Переходим к следующему элементу уникального множества
    }
}


int main()
{ 
    setlocale(LC_ALL, "ru-RU");
    using namespace std;

    List<int> lst({ 0, 1, 2, 3 });
    List<int> lst1({ -1, 2, 100, 3, 100 });

    cout << "Задание 1_6:\n";
    cout << "  Список 1: "; lst.println();
    cout << "       Наличие дубликатов (1-true, 0-false): " << pair_searches(lst) << endl;
    cout << "  Список 2: "; lst1.println();
    cout << "       Наличие дубликатов (1-true, 0-false): " << pair_searches(lst1) << endl;
    cout << endl << endl;

    // Создаем связный список с заданными значениями
    LinkedList<int> llst({ 0, 1, 2 });
    cout << "Задание 2_6:\n";
    // Выводим первый связный список
    cout << "  Список 1: "; llst.println();
    cout << "       Список 1 removed 2: ";
    clean_occurrence(llst, 1);
    llst.println(); // Печатаем содержимое связного списка
    // Пытаемся удалить элемент '-1', которого нет в списке, и выводим результат
    cout << "       Список 1 removed -1: ";
    clean_occurrence(llst, 11000);
    llst.println();
    // Выводим пустую строку для разделения вывода
    cout << endl;
    cout << endl;
    // Выводим заголовок для задания 3_6 и вызываем функцию music()
    cout << "Задание 3_6:\n";
    music(); // Выполняем функцию music(), которая, предположительно, выполняет какие-то действия с музыкой


    return 0;
}
