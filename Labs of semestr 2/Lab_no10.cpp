// Heap.cpp: определяет точку входа для консольного приложения.
#include <iostream>

using namespace std;

#include <iostream>
using namespace std;
class Country
{
private:
	string name, capital, lang;
	int population;
	double area;
public:
	Country()
	{
		name = "a"; capital = "b", lang = "c";
		population = area = 10000;
	}
	Country(string Name)
	{
		name = Name; capital = "b", lang = "c";
		population = area = 10000;
	}
	Country(string n, string c, string l, int p, double a)
	{
		name = n; capital = c; lang = l; population = p; area = a;
	}
	friend bool operator<(const Country& a, const  Country& b);
	friend bool operator>(const Country& a, const Country& b);
	friend bool operator<=(const Country& a, const Country& b);
	friend bool operator>=(const Country& a, const Country& b);
	bool operator ==(const Country& a)
	{
		return name == a.name;
	}
	void print()
	{
		cout << "Name : " << name << "\nCapital : " << capital << "\nLanguage : "
			<< lang << "\nPopulation : " << population << "\nArea : " << area << "km^2\n\n";
	}
	friend ostream& operator<< (ostream& stream, const Country& N);
};
ostream& operator<< (ostream& stream, const Country& N)
{
	stream << "Name : " << N.name << "\nCapital : " << N.capital << "\nLanguage : "
		<< N.lang << "\nPopulation : " << N.population << "\nArea : " << N.area << "km^2\n\n";
	return stream;
}
bool operator<(const Country& a, const Country& b)
{
	return a.name < b.name;
}
bool operator>(const Country& a, const Country& b)
{
	return a.name > b.name;
}
bool operator<=(const Country& a, const Country& b)
{
	return a.name <= b.name;
}
bool operator>=(const Country& a, const Country& b)
{
	return a.name >= b.name;
}

class Node
{
private:
	Country value;
public:
	//установить данные в узле
	Node(Country c)
	{
		value = c;
	}
	Node()
	{
		value = Country("a");
	}
	Country getValue() { return value; }
	void setValue(Country v) { value = v; }

	//сравнение узлов
	int operator<(Node N)
	{
		return (value < N.getValue());
	}

	int operator>(Node N)
	{
		return (value > N.getValue());
	}

	//вывод содержимого одного узла
	void print()
	{
		cout << value;
	}
};

void print(Node* N)
{
	cout << N->getValue() << "\n";
}
//куча (heap)
class Heap
{
private:
	//массив
	Node* arr;
	//сколько элементов добавлено
	int len;
	//сколько памяти выделено
	int size;
public:

	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }

	Node& operator[](int index)
	{
		if (index < 0 || index >= len)
			;//?

		return arr[index];
	}

	//конструктор
	Heap(int MemorySize = 100)
	{
		arr = new Node[MemorySize];
		len = 0;
		size = MemorySize;
	}

	//поменять местами элементы arr[index1], arr[index2]
	void Swap(int index1, int index2)
	{
		if (index1 <= 0 || index1 >= len)
			;
		if (index2 <= 0 || index2 >= len)
			;
		//здесь нужна защита от дурака

		Node temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}

	//скопировать данные между двумя узлами
	void Copy(Node* dest, Node* source)
	{
		dest->setValue(source->getValue());
	}

	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
	Node* GetLeftChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return &arr[index * 2 + 1];
	}

	Node* GetRightChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака

		return &arr[index * 2 + 2];
	}

	Node* GetParent(int index)
	{
		if (index <= 0 || index >= len)
			;
		//здесь нужна защита от дурака

		if (index % 2 == 0)
			return &arr[index / 2 - 1];
		return &arr[index / 2];
	}

	int GetLeftChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return index * 2 + 1;
	}

	int GetRightChildIndex(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака

		return index * 2 + 2;
	}

	int GetParentIndex(int index)
	{
		if (index <= 0 || index >= len)
			;
		//здесь нужна защита от дурака

		if (index % 2 == 0)
			return index / 2 - 1;
		return index / 2;
	}

	//просеить элемент вверх
	void SiftUp(int index = -1)
	{
		
		
		if (index == -1) index = len - 1;
		int parent = GetParentIndex(index);
		int index2 = GetLeftChildIndex(parent);
		if (index2 == index)
			index2 = GetRightChildIndex(parent);
		int max_index = index;

		if (index < len && index2 < len && parent >= 0)
		{
			if (arr[index] > arr[index2])
				max_index = index;
			if (arr[index] < arr[index2])
				max_index = index2;
		}
		if (parent < len && parent >= 0 && arr[max_index]>arr[parent])
		{
			//нужно просеивание вверх
			Swap(max_index, parent);
			SiftUp(parent);
		}
	}
	void heapify( int i)
	{
		int largest = i; 
		int l = GetLeftChildIndex(i); 
		int r =GetRightChildIndex(i); 
		if (l < len && r<len & arr[l] > arr[largest])
			largest = l;
		if (r < len && l< len && arr[r] > arr[largest])
			largest = r;
		if (l < len && r >= len) largest = l;
		if (largest != i) 
		{
			Swap(i, largest);
			heapify(largest);
		}
	}
	//добавление элемента - вставляем его в конец массива и просеиваем вверх
	void Add(Country v)
	{
		Node* N = new Node;
		N->setValue(v);
		Add(N);
	}
	void Add(Node* N)
	{
		if (len < size)
		{
			Copy(&arr[len], N);
			len++;
			SiftUp();
		}
	}

	Node ExtractMax()
	{
		//исключить максимум и запустить просеивание кучи
		Node last =arr[len - 1];
		Node max = arr[0];
		arr[0] = last;
		len--;
		heapify(0);
		return max;
	}

	//удаление элемента
	void Remove(Country v)
	{ 
		if (len == 0) return;
		int i = 0;
		while (i < len)
		{
			if (arr[i].getValue() == v)
				break;
			i++;
		}
		if (i != len)
		{
			int last = len - 1;
			Swap(i, last);
			len--;
			heapify(i);
		}
	}

	//перечислить элементы кучи и применить к ним функцию
	void Straight(void(*f)(Node*))
	{
		int i;
		for (i = 0; i < len; i++)
		{
			f(&arr[i]);
		}
	}

	//перебор элементов, аналогичный проходам бинарного дерева
	void PreOrder(void(*f)(Node*), int index = 0)
	{
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void InOrder(void(*f)(Node*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			InOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			InOrder(f, GetRightChildIndex(index));
	}

	void PostOrder(void(*f)(Node*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
	}

	void RemoveMax()
	{
		ExtractMax();
	}
};

int main()
{
	Heap Tree;
	Country A("A", "Moscow", "Russian", 14200000, 17000);
	Country B("B", "Kiev", "Ukrainian", 142000, 10000);
	Country C("C", "Minsk", "Belorussian", 142000, 12000);
	Country D("D", "Washington", "English", 3000000, 40000);
	Country E("E", "Berlin", "German", 230000, 123000);
	Country F("F", "Paris", "French", 3000000, 123000);
	Country G("G", "London", "English", 300000, 2230000);
	Country H("H"), N("N"), M("M"), K("K"), L("L"), O("O"), P("P");
	Country arr[12] = { D,F,G,E,B,A,C,L,K,M,N,O };
	
	for (int i = 0; i < 12; i++)
		Tree.Add(arr[i]);

	void(*f_ptr)(Node*); f_ptr = print;
	Tree.Remove(Country("A"));
	Tree.Remove(Country("C"));
	int len = Tree.getCount();
	cout << "\nlen = " << len << endl;

	for (int i = 0; i < len; i++)
	{
		cout << Tree.ExtractMax().getValue() << "\n";
	}

	char c; cin >> c;
	return 0;
}

