// lab1_sem3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include<list>
#include <iterator>
#include<ctime>
#include <fstream>

using namespace std;
int NOK(int x, int y)
{
    int max = (x > y) ? x : y;
    int nok = x * y;

    for (int i = max; i <= nok; i++)
        if (!(i % x) && !(i % y))
            return i;
    return nok;
}
int Nod(int a, int b)
{
    int t;
    if (a < b) { t = a; a = b; b = t; }
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}
/// Класс дробей с int 
class fract 
{
private:
    int chisl;
    int znam;
public:
    fract(int ch, int z)
    {
        chisl = ch; znam = z;
        int nod = Nod(chisl, znam);
        chisl = chisl / nod;
        znam = znam / nod;
        if (znam < 0 && chisl < 0)
        {
            znam = abs(znam);
            chisl = abs(chisl);
        }
        else if (znam < 0)
        {
            chisl = -chisl;
            znam = abs(znam);
        }
    }
    fract(int ch)
    {
        znam = 1;
        chisl = ch;
    }
    fract()
    {
        chisl = 0; znam = 1;
    }
    void tofract(double num)
    {
        chisl = num * 100;
        znam = 100;
        int nod = Nod(chisl, znam);
        chisl = chisl / nod;
        znam = znam / nod;
    }
    void print()
    {
        if (chisl == 0)
            cout << 0 << endl;
      /*  else if (znam == 1)
            cout << chisl << endl;*/
        else if (znam < 0 && chisl > 0 || znam > 0 && chisl < 0)
            cout << "-" << abs(chisl) << "/" << abs(znam) << endl;
        else
            cout << chisl << "/" << znam << endl;
    }
    
    int getChisl() { return chisl; };
    int getZnam() { return znam; };
    fract operator+(fract num)
    {
        int nok = NOK(znam, num.znam);
        int ch = nok / znam * chisl + nok / num.znam * num.chisl;
        fract res(ch, nok);
        return res;
    }
    fract operator-(fract num)
    {
        int nok = NOK(znam, num.znam);
        int ch = nok / znam * chisl - nok / num.znam * num.chisl;
        fract res(ch, nok);
        return res;
    }
    fract operator*(fract num)
    {
        fract res(chisl * num.chisl, znam * num.znam);
        return res;
    }
    fract operator/(fract num)
    {
        fract res(chisl * num.znam, znam * num.chisl);
        return res;
    }
    bool operator==(fract n)
    {
        return ((double)chisl / znam == (double)chisl / znam);
    }
    bool operator>(fract n)
    {
        double n1 = (double)chisl / znam;
        double n2 = (double)n.chisl / n.znam;
        return n1 > n2;
    }
    bool operator<(fract n)
    {
        double n1 = (double)chisl / znam;
        double n2 = (double)n.chisl / n.znam;
        return n1 < n2;
    }
    bool operator !=(fract n)
    {
        bool res = chisl != n.chisl || znam != n.znam;
        return res;
    }
    bool operator!=(int n)
    {
        fract f(n);
        return (chisl != f.chisl || znam != f.znam);
    }
};

// Задание 1.1
bool isPrime(int n) {
    if (n == 0) return false;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;
    return true;
}
list<fract> filter(list<fract> l)
{
    //Только дроби с числителями, представляющими простые числа.
    list<fract> res;
    for (fract& el : l)
    {
        if (isPrime(el.getChisl()))
        {
            res.push_back(el);
        }
    }
    return res;
}


// Задание 1.2
// Класс С :  «Супергерой».
//      Минимальный набор  полей : псевдоним, настоящее имя, дата рождения,
// пол, суперсила, слабости, количество побед, рейтинг силы.
//      Приоритет:   Рейтинг силы, количество побед; псевдоним (по возрастанию)
class SuperHero
{
private:
    string ps_name = "None";
    string rl_name = "None";
    string sp_power = "None";
    string weakness = "None";
    class Birth_day
    {
    public:
        int day;
        int month;
        int year;
        Birth_day()
        {
            day = 01; month = 01; year = 2000;
        }
        Birth_day(int d, int m, int y)
        {
            day = d;
            month = m;
            year = y;
        }
        void print()
        {
            cout << day << "/" << month << "/" << year << endl;
        }
    };
    Birth_day b;
    char sex = 'M';
    int wins = 0;
    int power = 0;
public:
    SuperHero(string pseudonynm, string real_name, string super_power,
        string weakness, int day, int month, int year,
        char sex, int wins, int power)
    {
        ps_name = pseudonynm;
        rl_name = real_name;
        sp_power = super_power;
        this->weakness = weakness;
        b.day = day;
        b.month = month;
        b.year = year;
        this->sex = sex;
        this->wins = wins;
        this->power = power;
    }
    SuperHero(string pseudonym, int power, int wins)
    {
        ps_name = pseudonym;
        this->power = power;
        this->wins = wins;
    }
    SuperHero() {};

    void print()
    {
        cout << ps_name;
        cout << "\nСила: " << power << "\nКоличетсво побед: " << wins;
        cout << "\nНастоящее имя: " << rl_name << "\nДата рождения: ";
        b.print();
        cout << "Пол:" << sex << "\nCуперсила: " << sp_power;
        cout << "\nСлабость: " << weakness << "\n\n";

    }
    bool operator >(SuperHero s)
    {
        if (power != s.power) return power < s.power;
        if (wins != s.wins) return wins < s.wins;
        return ps_name < s.ps_name;
    }
    bool operator < (SuperHero s)
    {
        if (power != s.power) return power > s.power;
        if (wins != s.wins) return wins > s.wins;
        return ps_name > s.ps_name;
    }
};

void pop(list<fract>& l)
{
    l.pop_back();
}
SuperHero pop(list<SuperHero>& l)
{
    SuperHero res = *l.begin();
    l.pop_front();
    return res;
}
template<class T>
void push(list<T>& lst, T& el)
{
    auto p = lst.begin();
    while (p != lst.end())
    {
        if (*p > el)
            break;
        p++;
    }
    lst.insert(p, el);
}


/// Задание 1.3 код связанный с Queue
template <class T>
class Element
{
    //элемент связного списка
private:
    //указатель на предыдущий и следующий элемент
    Element* next;
    Element* prev;

    //информация, хранимая в поле
    T field;
public:
    Element(T value)
    {
        field = value;
        next = prev = NULL;
    }
    //доступ к полю *next
    virtual Element* getNext() { return next; }
    virtual void setNext(Element* value) { next = value; }

    //доступ к полю *prev
    virtual Element* getPrevious() { return prev; }
    virtual void setPrevious(Element* value) { prev = value; }

    //доступ к полю с хранимой информацией field
    virtual T getValue() { return field; }
    virtual void setValue(T value) { field = value; }

    template<class T> 
    friend ostream& operator<< (ostream& ustream, Element<T>& obj);
};
template<class T>
ostream& operator << (ostream& ustream, Element<T>& obj)
{
    ustream << obj.field;
    return ustream;
}

/// Класс итератор 
template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
private:

public:
    //конструкторы
    ListIterator() { ptr = NULL; }
    ListIterator(Element<ValueType>* p) { ptr = p; }
    ListIterator(const ListIterator& it) { ptr = it.ptr; }

    //методы работы с итераторами
    //присваивание
    ListIterator& operator=(const ListIterator& it) { ptr = it.ptr; return *this; }
    ListIterator& operator=(Element<ValueType>* p) { ptr = p; return *this; }

    //проверка итераторов на равенство
    bool operator!=(ListIterator const& other) const { return ptr != other.ptr; }
    bool operator==(ListIterator const& other) const { return ptr == other.ptr; }
    //получить значение
    Element<ValueType>& operator*()
    {
        if (ptr != NULL)
            return *ptr;
    }
    //перемещение с помощью итераторов
    ListIterator& operator++()
    {
        if (ptr == NULL || ptr.getNext() == NULL)
            return *this;
        ptr = ptr->getNext();
        return *this;
    }
    ListIterator& operator++(int v)
    {
        if (ptr == NULL || ptr->getNext() == NULL)
            return *this;
        ptr = ptr->getNext();
        return *this;
    }
    ListIterator& operator--()
    {
        if (ptr != NULL || ptr->getPrevious() != NULL)
        {
            ptr = ptr->getPrevious();
        }
        return *this;
    }
    ListIterator& operator--(int v)
    {
        if (ptr != NULL || ptr->getPrevious() != NULL)
        {
            ptr = ptr->getPrevious();
        }
        return *this;
    }
private:
    //текущий элемент
    Element<ValueType>* ptr;
};
//// Класс связанный список
template <class T>
class LinkedListParent
{
protected:
    //достаточно хранить начало и конец
    Element<T>* head;
    Element<T>* tail;
    //для удобства храним количество элементов
    int num;
public:
    virtual int Number() { return num; }

    virtual Element<T>* getBegin() { return head; }

    virtual Element<T>* getEnd() { return tail; }

    LinkedListParent()
    {
        //конструктор без параметров
        //cout << "\nParent constructor";
        head = NULL;
        num = 0;
    }

    //чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
    virtual Element<T>* push(T value) = 0;

    //чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
    virtual Element<T>* pop() = 0;

    virtual ~LinkedListParent()
    {
        //деструктор - освобождение памяти
        //cout << "\nParent destructor";
    }

    //получение элемента по индексу - какова асимптотическая оценка этого действия?
    virtual Element<T>* operator[](int i)
    {
        //индексация
        if (i < 0 || i >= num) return NULL;
        int k = 0;

        //ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
        Element<T>* cur = head;
        for (k = 0; k < i; k++)
        {
            cur = cur->getNext();
        }
        return cur;
    }

    template<class T> friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj);
    template<class T> friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj);
    //ListIterator<T> iterator;

    ListIterator<T> begin() { ListIterator<T> it = head; return it; }
    ListIterator<T> end() { ListIterator<T> it = tail; return it; }
};
template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj)
{
    if (typeid(ustream).name() == typeid(ofstream).name())
    {
        ustream << obj.num << "\n";
        for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
            ustream << current->getValue() << " ";
        return ustream;
    }

    ustream << "\nLength: " << obj.num << "\n";
    int i = 0;
    for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
        ustream << "arr[" << i << "] = " << current->getValue() << "\n";

    return ustream;
}
template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{
    //чтение из файла и консоли совпадают
    int len;
    ustream >> len;
    //здесь надо очистить память под obj, установить obj.num = 0
    double v = 0;
    for (int i = 0; i < len; i++)
    {
        ustream >> v;
        obj.push(v);
    }
    return ustream;
}

///Класс очередь
template <class T>
class Queue :public LinkedListParent<T>
{
public:
    /*Queue() : LinkedListParent<T>() { cout << "\nQueue constructor\n"; }
    virtual ~Queue() { cout << "\nQueue destructor\n"; }*/
    
    virtual Element<T>* push(T value)
    {

        Element <T>* newEl = new Element<T>(value);
        if (LinkedListParent<T>::tail == NULL)
        {
            LinkedListParent<T>::tail = LinkedListParent<T>::head = newEl;
        }
        else
        {
            LinkedListParent<T>::tail->setNext(newEl);
            newEl->setPrevious(LinkedListParent<T>::tail);
            LinkedListParent<T>::tail = newEl;
        }
        LinkedListParent<T>::num++;
        return newEl;
    }
    Element<T>* pop()
    {
        if (LinkedListParent<T>::head == NULL)
            return NULL;
        Element<T>* res = LinkedListParent<T>::head;
        if (LinkedListParent<T>::head == LinkedListParent<T>::tail)
        {
            LinkedListParent<T>::head = LinkedListParent<T>::tail = NULL;
        }
        else
        {
            Element<T>* newH = LinkedListParent<T>::head->getNext();
            LinkedListParent<T>::head->setNext(NULL);
            newH->setPrevious(NULL);
            LinkedListParent<T>::head = newH;
        }
        LinkedListParent<T>::num--;
        return res;
    }
};

//// Наследник очереда с переопределенной функцией push()
template <class T>
class Sorted_Q :public Queue <T>
{
public:
    Element<T> *push(T value)
    {
        Element <T>* newEl = new Element<T>(value);
        Element <T>* cur = LinkedListParent<T>::head;
        if (LinkedListParent<T>::tail == NULL)// Если очередь пустой
        {
            LinkedListParent<T>::tail = LinkedListParent<T>::head = newEl;
        }
        else if (LinkedListParent<T>::tail == LinkedListParent<T>::head)
        {
            // Если в очереди всего 1 элемент
            if (cur->getValue() > value)//Добавляем в начало
            {
                cur->setPrevious(newEl);
                newEl->setNext(cur);
                LinkedListParent<T>::tail = cur;
                LinkedListParent<T>::head = newEl;
                return newEl;
            }
            else
            {
                return Queue<T>::push(value);
            }
        }
        else// Если элементов много 
        {
            while (cur->getNext() != NULL)
            {
                if (cur->getValue() > value)
                    break;
                cur = cur->getNext();
            }

            if (cur->getNext() == NULL)// Когда добавляем в конец
            {
                return Queue<T>::push(value);
            }
            if (cur->getPrevious() == NULL)// Когда добавляем в начало
            {
                newEl->setNext(cur);
                cur->setPrevious(newEl);
                LinkedListParent<T>::head = newEl;
            }
            else// Когда добавляем в середину
            {
                Element<T>* prev = cur->getPrevious();
                cur->setPrevious(newEl);
                newEl->setNext(cur);
                prev->setNext(newEl);
                newEl->setPrevious(prev);
            }
        }
        LinkedListParent<T>::num++;
        return newEl;      
    }
    void print()
    {
        ListIterator<T> p = LinkedListParent<T>::begin();
        while (p != LinkedListParent<T>::end())
        {
            Element<T> el = *p;
            el.getValue().print();
            p++;
        }
        Element<T> el = *p;
        el.getValue().print();
    }
};
///////Переопределение функции filter() 
Sorted_Q<fract>filter(Sorted_Q<fract> q)
{
    // Только дроби с числителями, представляющими простые числа.
    Sorted_Q<fract> res;
    ListIterator<fract> it = q.begin();
    while(it!=q.end())
    {
        Element<fract> el = *it;
        if (isPrime(el.getValue().getChisl()))
        {
            res.push(el.getValue());
        }
        it++;
    }
    return res;


}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "ru");

    //////////////////////////    ПУНКТ 1.1
    /*Постройте связный список(используйте класс list библиотеки STL), который содержит
    объекты указанного в таблице типа T.Постройте функции добавления push() и удаления pop()  образом чтобы
    список оставался отсортированным выполнении этих операций.Постройте функцию filter(), 
    которая принимает предикат P и возвращает новый список с объектами, для которых предикат принимает 
    истинное  значение.Постройте функцию вывода содержимого списка с помощью итераторов.*/
    // class: Fraction
    //  Predikat: Только дроби с числителями, представляющими простые числа.
    cout << "\n\n\t\t\t ПУНКТ 1.1\n\n";

    list<fract> l;
    for (int i = 10; i>0; i--)
    {
        fract el(rand()%20, rand()%20+1);
        push(l, el);
    }
    cout << "\t\t\tЛист с дробьями\n";
    for (auto& el : l)
    {
        el.print();
    }
    // Демонстрация функции filter()
    list<fract> filtred=filter(l); 
    cout << "\n\n\t\t\tResult of filter(lst):\n";
    for (auto& el : filtred)
    {
        el.print();
    }

    ///////////////////////////           ПУНКТ 1.2
    /*Заполните список из пункта 1 объектами класса С, сохраняя убывание по приоритету :
    полю или группе полей, указанных в варианте.Функция pop() должна удалять объект из
    контейнера и возвращать как результат объект с наибольшим приоритетом*/
    // class C: «Супергерой».
   /* Минимальный набор полей : псевдоним, настоящее имя, дата рождения, пол, суперсила,
      слабости, количество побед, рейтинг силы.*/
    /* Приоритет: Рейтинг силы, количество  побед; псевдоним (по возрастанию)*/
    cout << "\n\n\t\t\t ПУНКТ 1.2\n\n";
    SuperHero s("F", 2000, 50);
    SuperHero s1("E", 9000, 40);
    SuperHero s2("D", 9000, 100);
    SuperHero s4("B", 10000, 60);
    SuperHero s5("C", 10000, 60);
    SuperHero s3("A", 10000, 90);
    SuperHero s6("G", 2500, 70);
    SuperHero heros[] = { s,s1,s2,s3,s4,s5,s6 };


    list<SuperHero> h;
    for (int i = 0; i < 6; i++)
        push(h, heros[i]);
    for (int i = 0; i < 3; i++)
    {
        cout << "\t\t\t\tpop()\n";
        pop(h).print();
    }
    cout << "\t\t\tУдалили первые 3 элемента из листа\n";
    for (auto& el : h)
        el.print();



    /////////                                   ПУНКТ 1.3 
    /*Постройте шаблон класса двусвязного списка путём наследования от класса LinkedListParent. 
    Реализуйте функции добавления элемента push() и удаления элемента pop() в классе-наследнике D 
    (для четных вариантов D – Стек, для нечетных – Очередь)
     Постройте наследник класса D. Переопределите функцию добавления нового элемента таким
     образом, чтобы контейнер оставался упорядоченным. Реализуйте функцию filter() из пункта 1.1 */
    /// Sorted_Q наследник Queue, элементы упорядочены

     //////////////////   ПУНКТ 1.5    
    /*Постройте шаблон класса списка D (из задания в пункте 3), который хранит
    объекты класса C (из задания в пункте 2), сохраняя упорядоченность по приоритету:
    полю или группе полей, указанных в варианте.*/
    cout << "\n\n\t\t\t ПУНКТ 1.3 и ПУНКТ 1.5 \n\n";

    Sorted_Q <SuperHero> S;
    cout << "\n\n\t\t\t Sorted_q with SuperHeros\n";
    for (int i = 0; i <6 ; i++)
    {       
        S.push(heros[i]);
    }
    S.print();
    // Функция filter() из пункта 1.1
    Sorted_Q<fract> q;
    for (int i = 10; i > 0; i--)
    {
        fract el(rand() % 20, rand() % 20 + 1);
        q.push(el);
    }
    cout << "\n\t\t\tSorted_q для демонстрации функции filter()\n";
    q.print();
    Sorted_Q<fract> filt = filter(q);

    /////////////////           ПУНКТ 1.4 
    /*Постройте итераторы для перемещения по списку. Переопределите функцию вывода
      содержимого списка с помощью итераторов.*/
    cout << "\n\n\t\t\t ПУНКТ 1.4\n\n";
    cout << "\t\t\tSorted_q after filtred():\n\n";

    ListIterator<fract> p = filt.begin();
    while (p != filt.end()) 
    {
        Element<fract> el=*p;
        el.getValue().print();
        p++;
    }
    Element<fract> el = *p;
    el.getValue().print();
}