﻿// LinkedList.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

class Element
{
	//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* next=NULL;
	Element* prev=NULL;
	//информация, хранимая в поле
	double field=0;
public:
	//доступ к полю *next
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	//доступ к полю *prev
	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

	//доступ к полю с хранимой информацией field

	virtual double getValue() { return field; }
	virtual void setValue(double value) { field = value; }
};

class LinkedListParent
{
protected:
	Element* begin;
	Element* end;
	int num;
public:
	virtual int Number() { return num; }
	virtual Element* getBegin() { return begin; }
	virtual Element* getEnd() { return end; }
	LinkedListParent()
	{
		//конструктор без параметров
		cout << "\nParent constructor\n";
		begin = NULL;
		end = NULL;
		num = 0;
	}
	LinkedListParent(const LinkedListParent& list) // конструктор копий 
	{
		begin = NULL;
		end = NULL;
		num = 0;
		Element* cur = list.begin;
		while (cur != NULL)
		{
			push(cur->getValue());
			cur = cur->getNext();
		}
		delete cur;
	}
	virtual LinkedListParent& operator=(const LinkedListParent& list)// оператор = 
	{

		begin = NULL;
		end = NULL;
		Element* cur = list.begin;
		while (cur != NULL)
		{
			push(cur->getValue());
			cur = cur->getNext();
		}
		delete cur;
		return *this;
	}

	virtual Element* push(double a)
	{
		//положить элемент в конец
		Element* cur = begin;
		if (begin == NULL)
		{
			//ничего в списке нет
			num = 1;
			begin = new Element;
			begin->setValue(a);
			begin->setNext(NULL);
			begin->setPrevious(NULL);
			end = begin;
			return begin;
		}
		//вставка элемента
		end->setNext(new Element);
		end->getNext()->setValue(a);
		end->getNext()->setNext(NULL);
		end->getNext()->setPrevious(end);
		end = end->getNext();

		num++;
		return end->getNext();
	}
	virtual Element* push_r(double a, Element* current = NULL)
	{
		//положить элемент в конец - рекурсивная версия

		//в списке нет элементов - цепляем в начало добавляемый элемент
		if (begin == NULL)
		{
			//ничего в списке нет
			num = 1;
			begin = new Element;
			end = begin;
			begin->setValue(a);
			begin->setNext(NULL);
			begin->setPrevious(NULL);
			return begin;
		}
		//ничего не передано в функцию - по умолчанию начинаем поиск свободного места с начала списка
		if (current == NULL)
			current = begin;

		//мы находимся где-то в списке - ищем последний элемент рекурсивно
		if (current->getNext() != NULL)
			return push_r(a, current->getNext());
		//указатель на следующий элемент свободен - цепляем туда новый. Здесь рекурсия закончится 
		if (current->getNext() == NULL)
		{
			current->setNext(new Element);
			current->getNext()->setValue(a);
			current->getNext()->setNext(NULL);
			current ->getNext()->setPrevious(current);
			num++;
			return current->getNext();
		}
	}
    virtual double pop_r(Element*current=NULL)
	{
		if (num == 1)
		{
			double res = begin->getValue();
			delete begin;
			begin = NULL;
			end = NULL;
			num--;
			return res;
		}
		if (current ==NULL)
			current = begin;
		//ничего не передано в функцию - по умолчанию начинаем поиск свободного места с начала списка
		//мы находимся где-то в списке - ищем последний элемент рекурсивно
		if (current->getNext() != NULL)
			return pop_r(current->getNext());
		//указатель на следующий элемент свободен - цепляем туда новый. Здесь рекурсия закончится 
		if (current->getNext() == NULL)
		{
			double res = current->getValue();
			current->getPrevious()->setNext(NULL);
			delete current;
			num--;
			return res;
		}
	}
	virtual double pop()
	{
		//отдельно рассмотрим случай 0/1 элементов
		if (begin == NULL)
		{
			return -1;
		}
		if (num == 1)
		{
			double res = begin->getValue();
			delete begin;
			begin = NULL;
			end = NULL;
			num--;
			return res;
		}
		//сохраняем результат
		double res = end->getValue();
		Element* prev = end->getPrevious();
		prev->setNext(NULL);
		//последнего стёрли
		delete end;
		end = prev;
		//число элементов снизилось на 1	
		num--;
		return res;
	}
	
	virtual Element*operator[](int i)
	{
		//индексация
		if (i<0 || i>num) return NULL;
		int k = 0;

		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element* cur = begin;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}
	virtual void print()
	{
		//итеративная версия вывода списка - стандартный цикл перебора всех элементов
		Element* cur = begin;
		while (cur != NULL)
		{
			cout << cur->getValue() << " ";
			cur = cur->getNext();
		}
		cout << endl;
	}
	virtual void clear()
	{
		while (num)
			pop();
	}
	~LinkedListParent()
	{
		//деструктор - освобождение памяти
		cout << "\nParent destructor";
		clear();
	}

};

class LinkedListChild : public LinkedListParent
{
public:
	LinkedListChild() : LinkedListParent() { cout << "\nChild constructor\n"; }

	LinkedListChild(const LinkedListChild& list)
	{
		begin = NULL;
		Element* cur = list.begin;
		while (cur != NULL)
		{
			push(cur->getValue());
			cur = cur->getNext();
		}
		delete cur;
	}
	LinkedListChild& operator=(const LinkedListChild& list)
	{
		begin = NULL;
		Element* cur = list.begin;
		while (cur != NULL)
		{
			push(cur->getValue());
			cur = cur->getNext();
		}
		delete cur;
		return *this;
	}
	~LinkedListChild() {

		cout << "\nChild destructor----";
	}
	virtual Element* insert(Element* current, double value)
	{
		if (current == end)
		{
			push(value);
			return end;
		}
		Element* newEl = new Element;
		current->getNext()->setPrevious(newEl);
		newEl->setNext(current->getNext());
		newEl->setValue(value);
		newEl->setPrevious(current);
		current->setNext(newEl);
		num++;
		return newEl;
	}
	virtual Element* insert(Element* current, Element* newElem)
	{
		if (current == NULL)
		{
			return 0;
		}
		if (current == end)
		{
			push(newElem->getValue());
			return end;
		}
		current->getNext()->setPrevious(newElem);
		newElem->setNext(current->getNext());
		newElem->setPrevious(current);
		current->setNext(newElem);
		num++;
		return current->getNext();
	}
	void remove(Element* current)
	{
		if (current != NULL)
		{
			if (current == begin || current==end)
			{
				pop();
				return;
			}
			else if (current->getNext() != nullptr)
			{
				current->getPrevious()->setNext(current->getNext());
				current->getNext()->setPrevious(current->getPrevious());
				delete current;
			}
			num--;
		}
	}
	Element* find(double value_to_find)
	{
		//поиск в списке. value_to_find - значение, которое мы сравниваем при поиске с полем find в элементе списка
		//если нашли, - возвращаем указатель на элемент списка
		Element* cur = begin;
		while (cur != NULL)
		{
			if (cur->getValue() == value_to_find)
				return cur;
			cur = cur->getNext();
		}
		return NULL;
	}
	Element* find_r(double key, Element* cur = NULL)
	{
		if (cur == NULL)
		{
			cur = begin;
		}
		if (cur->getValue() == key)// Если нашли возвращаем указатель на этот элемент
			return cur;
		else if (cur->getNext() != NULL)// Пока есть элементы
			return find_r(key, cur->getNext());
		return NULL;//Если дошел до этой строчки значит такого значения нет
	}
	void split(Element* border, LinkedListChild* List1, LinkedListChild* List2)
	{	
		if (border == NULL)
			throw exception();
		List1->begin = begin;
		List1->end = border;

		List2->begin = border->getNext();
		List2->end = end;

		List1->end->setNext(NULL);

	}
	void merge(LinkedListChild *l1, LinkedListChild *l2)
	{
		begin = l1->begin;
		end = l1->end;
		end->setNext(l2->begin);
		end = l2->end;
		num = l1->num + l2->num;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	if (1)
	{
		LinkedListChild L;
		LinkedListChild L4;

		LinkedListChild *L2=new LinkedListChild, *L3=new LinkedListChild;
		for (int i = 0; i < 10; i++)
			L.push(i);
		L.print();

	
		////////
		L.split(L[7], L2, L3);
		L2->print();
		L3->print();

		L4.merge(L2, L3);
		L4.print();
		
		cout << "size " << L4.Number() << endl;
		//////////////////
		////insert()
		//L.insert(L[2], 1000);
		//Element* el = new Element;
		//el->setValue(500);
		//L.insert(L[9], 500);
		//cout << "\ninsert() size = " << L.Number() << endl;
		//L.print();

		//////remove()
		//L.remove(L[10]);
		//L.remove(L[3]);
		//cout << "\nremove() size = " << L.Number() << endl;
		//L.print();

		//Element* res = L.find_r(77);// find()
		//if (res != NULL)
		//	cout << "\nFound\t" << res->getValue() << endl;
		//else
		//	cout << "\nNot_Found\n";
	}
	char c; cin >> c;
	return 0;
}
