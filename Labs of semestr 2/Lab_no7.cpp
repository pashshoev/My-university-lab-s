
//В классе - обертке для массива(практическая работа №5) и связного списка
//(практическая работа 6) ввести операции для записи содержимого массива / связного списка
//в файл, чтения из файла, ввода и вывода информации в консоль.
//Сделайте различие между выводом в файл(выводить не только содержимое
//    контейнера, но и его длину) и выводом в консоль(сделать дружелюбный для пользователя
//        интерфейс с выводом содержимого контейнера в следующем ниже формате).
//    Size: …
//    arr[0] = …,
//    …
//    arr[i] = … .
//    Введите манипулятор, форматирующий вывод, и примените его при выводе
//    содержимого контейнера :
//    Вывод в научном виде, ширина поля – 5 символов, 2 знака после запятой


#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
class Exception
{
protected:
    char* str, * name1, * text1;
public:
    Exception(const char* s, const char* name, const char* text)
    {
        str = new char[strlen(s) + 1];
        strcpy_s(str, strlen(s) + 1, s);

        name1 = new char[strlen(name) + 1];
        strcpy_s(name1, strlen(name) + 1, name);

        text1 = new char[strlen(text) + 1];
        strcpy_s(text1, strlen(text) + 1, text);
    }
    ~Exception()
    {
        //delete[] str;
    }
    virtual void print()
    {
        cout << "Exception: " << str << endl << "in function: " << name1 << endl << "Сообщение: " << text1 << endl << endl;
    }
};
class IndexOutOfBounds :public Exception
{
private:
    char* name;
public:
    IndexOutOfBounds(const char* s, const char* name, const char* text) :Exception(s, name, text)
    {
    }
    void print()
    {
        Exception::print();
    }
};
class IndexMoreThanLength :public IndexOutOfBounds
{
private:
    int max_index;
public:
    IndexMoreThanLength(const char* name, int max_index)
        :IndexOutOfBounds("IndexMoreThanLength", name, "Индекс больше чем длина массива") {
    }
    int getMax_index() { return max_index; }
    void print()
    {
        IndexOutOfBounds::print();
        cout << "\tmax index " << max_index << endl;
    }
};
class NegativeIndex :public IndexOutOfBounds
{
public:
    NegativeIndex(const char* name) :IndexOutOfBounds("Negative Index", name, "Индекс меньше нуля")
    {
    }
    void print()
    {
        IndexOutOfBounds::print();
    }
};
class ZeroLengthArray :public IndexOutOfBounds
{
public:
    ZeroLengthArray(const char* name) :IndexOutOfBounds("ZeroLengthArray", name, "Длина массива равна нулю (len=0)") {
    }
    void print()
    {
        IndexOutOfBounds::print();
        cout << "Неверный индекс , длина массива равна нулю (len=0)\n";
    }
};
class CopyTooLargeArray :public Exception
{
private:
    int size;
    int max_capacity;
    char* name;
public:
    CopyTooLargeArray(int size, int max_capacity, const char* name) :Exception("CopyTooLargeArray", name, "Копирования \"большого\" массива в \"маленький\"")
    {
        this->size = size;
        this->max_capacity = max_capacity;
        this->name = new char[strlen(name) + 1];
        strcpy_s(this->name, strlen(name) + 1, name);
    }
    void print()
    {
        Exception::print();
        cout << "\tin function: " << name << endl;
        cout << "Копирования \"большого\" массива в \"маленький\" \n";
        cout << "Размер копируемого массива: " << size << "\tвместимость исходного массива: " << max_capacity << endl;
    }

};
class NoMatches :public Exception
{
public:
    NoMatches(const char* name) :Exception("NoMatches", name, "Такого элемента в наборе нет")
    {
    }
    void print()
    {
        Exception::print();
    }
};



class MyVector
{
private:
    double* ptr;
    int capacity;
    int size;
public:
    int Capacity() { return capacity; }
    int Size() { return size; }
    MyVector(int dim = 100)
    {
        ptr = new double[dim];
        capacity = dim;
        size = 0;
    }
    void setCapacity(int dim)
    {
        double *old_ptr = ptr;
        ptr = new double[dim];
        for (int i = 0; i < size; ++i) {
            ptr[i] = old_ptr[i];
        }
        delete [] old_ptr;
        capacity = dim;
    }
    void setNewArr( double * arr, int len)
    {
        delete[] ptr;
        capacity = 2 * len;
        ptr = new double[capacity];
        size = len;
        for (int i = 0; i < size; i++)
        {
            ptr[i] = arr[i];
        }
    }
    MyVector(const MyVector& v)
    {
        capacity = v.capacity;
        size = v.size;
        ptr = new double[capacity];
        for (int i = 0; i < size; i++)
            ptr[i] = v.ptr[i];
    }
    MyVector(double* arr, int len)
    {
        capacity = 2 * len;
        ptr = new double[capacity];
        size = len;
        for (int i = 0; i < size; i++)
        {
            ptr[i] = arr[i];
        }
    }
    MyVector& operator=(const MyVector& v)
    {
        if (capacity < v.size)
        {
            throw CopyTooLargeArray(v.size, capacity, "operator =");
        }
        size = v.size;
        ptr = new double[capacity];
        for (int i = 0; i < size; i++)
            ptr[i] = v.ptr[i];
        return *this;
    }
    void print()
    {
        if (size == 0)
            return;
        for (int i = 0; i < size; i++)
        {
            cout << ptr[i] << " ";
        }
        cout << endl;
    }
    void push_back(double val)
    {
        if (size < capacity)
        {
            ptr[size] = val;
            size++;
        }
    }
    void push_front(double val)
    {
        if (size < capacity)
        {

            for (int i = size; i > 0; i--)
            {
                ptr[i] = ptr[i - 1];
            }
            ptr[0] = val;
            size++;
        }
    }
    double find(double val)
    {
        for (int i = 0; i < size; i++)
        {
            if (ptr[i] == val)
            {
                return i;
            }
        }
        return -1;
    }
    int frequency(double num)
    {
        int count = 0;
        for (int i = 0; i < size; i++)
        {
            if (num == ptr[i]) count++;
        }
        if (count == 0)
            throw NoMatches("frequency()");
        else
            return count;
    }
    void remove(int index)
    {
        int k = index;
        if (k < size && k>-1)
        {
            for (int i = k; i < size - 1; i++)
            {
                ptr[i] = ptr[i + 1];
            }
            size--;
            ptr[size] = NULL;
        }
        else
            throw exception("Неверный индекс !!!");
    }
    void insert(double val, int i)
    {
        if (i < size && i>-1)
        {
            for (int k = size; k > i; k--)
            {
                ptr[k] = ptr[k - 1];
            }
            ptr[i] = val;
            size++;
        }
        if (i == size)
        {
            ptr[i] = val;
            size++;
        }
        else
            throw exception("Неверный индекс !!!");
    }
    double& operator[](int i)
    {
        if (i < 0)
            throw NegativeIndex("operator []");
        else if (size == 0 && capacity == 0)
            throw ZeroLengthArray("operator []");
        else if (i >= size && capacity <= i)
            throw IndexMoreThanLength("operator []", size - 1);
        else
            return ptr[i];
    }
    MyVector operator+(MyVector& vec)
    {
        int s = size + vec.size > 100 ? 3 * (size + vec.size) / 2 : 100;
        MyVector res(s);
        for (int i = 0; i < size; i++)
        {
            res.push_back(ptr[i]);
        }
        for (int i = 0; i < vec.size; i++)
        {
            res.push_back(vec[i]);
        }
        return res;
    }
    ~MyVector()
    {

        if (ptr != NULL)
        {
            delete[] ptr; ptr = NULL;
        }
    }

    friend ostream& operator <<(ostream& ustream, MyVector& obj);
    friend istream& operator >>(istream& ustream, MyVector& obj);

};
ostream& operator <<(ostream& ustream, MyVector& obj)
{
    if (typeid(ustream).name() == typeid(ofstream).name())
    {
        if (obj.size > 0) 
        {
            ustream << obj.size << endl;
            for (int i = 0; i < obj.size; i++)
                ustream << obj[i] << " ";
            ustream << endl;
        }
        return ustream;
       
    }
    if (obj.size < 0)
    {
        cout << "Error\n"; return ustream;
    }
    ustream << "Size = " << obj.size << endl;
    for (int i = 0; i < obj.size; i++)
    {
        ustream << "arr[" << i << "] = " << obj[i] << endl;
    }
    return ustream;
}
istream& operator >>(istream& ustream, MyVector& obj)
{
    if (typeid(ustream).name() == typeid(ifstream).name())
    {
        double num;
        int size;
        ustream >> size;
        obj.setCapacity(  size * 2);
        for (int i = 0; i <size; i++)
        {
            ustream >> num;
            obj.push_back(num);
        }
        return ustream;
    }
    cout << "Size = ";
    ustream >> obj.size;
    if (obj.size < 0) 
    {
        cout << "Error!\n"; return ustream;
    }
    double* arr = new double[obj.size];
    for (int i = 0; i < obj.size; i++)
    {
        cout << "arr[" << i << "] = ";
       ustream >> arr[i];
    }
    obj.setNewArr(arr, obj.size);
    delete[] arr;
    return ustream;
}

ostream& manip(ostream& ustream)
{
    ustream.setf(ios::scientific);
    ustream.width(5);
    ustream.precision(2);
    return ustream;
}
int main()
{
    setlocale(LC_ALL, "ru");  
    if (true)
    {
        ofstream fout("array.txt" ,ios::out);
        MyVector v1, v2;
        cout << "\t\tВвод в Вектор №1:\n";
        cin >> v1;
        if (fout) 
        {
            cout << "\nЗапись данных из Вектора №1 в файл array.txt\n\t\t***\n\n";
            fout << manip <<v1;
            fout.close();
        }
        ifstream fin("array.txt");
        if (fin)
        {
            cout << "Чтение данных из файла  array.txt в Вектор №2 \n\t\t***\n\n";
             fin >> v2;
             fin.close();
        }
        cout << "\nВывод Вектора №2:\n"<< manip << v2;
        cout << endl;
    }
}