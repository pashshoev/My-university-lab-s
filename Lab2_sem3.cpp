#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <utility>
#include <cassert>

using namespace std;

///// Пункт 2.1 

template<typename K, typename V>
void printMap(const map<K, V>& Map)
{
	for (auto i : Map)
	{
		cout << "Key:\t" << i.first <<"\n"<< "Value:\t" << i.second<<"\n\n";
	}

	cout << endl;
}

template<typename K, typename V>
pair<K, V>* findByKey(const map<K, V>& Map, const K& key)
{
	try
	{
		cout << "Map[" << key << "] = " << Map.at(key) << endl;
		return new pair<K, V>(key, Map.at(key));
	}
	catch (const exception&)
	{
		cout << "Элемента с таким " << key << "не существует!" << endl;

		return nullptr;
	}
}

template<typename K, typename V>
vector<pair<K, V>> findByValue(const map<K, V>& Map, const V& value)
{
	vector<pair<K, V>> result;

	for (auto i : Map)
	{
		if (i.second == value)
		{
			result.push_back(i);
		}
	}
	return result;
	
}

template<typename V>
bool threshold(const V& value) // Предикат проверки порога численности населения
{
	return value =="Power";
}

template<typename K, typename V>
map<K, V> filter(const map<K, V>& Map, bool (*f)(const V&)) // Функция записи элементов контейнера map с определенным условием
{
	map<K, V> newMap;

	for (auto i : Map)
	{
		if (f(i.second))
			newMap.emplace(i);
	}
	return newMap;
}




///// Пункт 2.2 


void printQueue(priority_queue<pair<string, string>>& q)
{
	while (!q.empty()) // Вывод элементов очереди с приоритетом (приоритет по ключам)
	{
		string value = q.top().second;

		cout << "Key:\t\t" << q.top().first << endl;
		cout << "Value:\t\t" << q.top().second<<endl<<endl;
		q.pop();
	}
}



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
	bool operator <(SuperHero s)
	{
		return ps_name < s.ps_name;
	}
	bool operator > (SuperHero s)
	{
		return ps_name > s.ps_name;
	}
	bool operator ==(SuperHero s)
	{
		return ps_name == ps_name;
	}
	friend ostream& operator<< (ostream& ustream, SuperHero& obj);
};
 ostream& operator<< (ostream& ustream, SuperHero& obj)
{
	 ustream << obj.ps_name;
	 ustream << "\nСила: " << obj.power << "\nКоличетсво побед: " << obj.wins;
	 ustream << "\nНастоящее имя: " << obj.rl_name << "\nДата рождения: ";
	 obj.b.print();
	 ustream << "Пол:" << obj.sex << "\nCуперсила: " << obj.sp_power;
	 ustream << "\nСлабость: " << obj.weakness << "\n\n";
	 return ustream;
}

 template<class T>
class Node
{
protected:
	//закрытые переменные Node N; N.data = 10 вызовет ошибку
	//int data;
	T data;
	//не можем хранить Node, но имеем право хранить указатель
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;

	//переменная, необходимая для поддержания баланса дерева
	int height;
public:
	//доступные извне переменные и функции
	//virtual void setData(int d) { data = d; }
	virtual void setData(T d) { data = d; }
	virtual T getData() { return data; }
	int getHeight() { return height; }

	virtual Node<T>* getLeft() { return left; }
	virtual Node<T>* getRight() { return right; }
	virtual Node<T>* getParent() { return parent; }

	virtual void setLeft(Node<T>* N) { left = N; }
	virtual void setRight(Node<T>* N) { right = N; }
	virtual void setParent(Node<T>* N) { parent = N; }

	Node<T>(T c)
	{
		data = c;
		left = right = parent = NULL;
		height = 0;
	}
	Node<T>()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		data = T();
		//data = 0;
		height = 0;
	}
	virtual void setHeight(int h)
	{
		height = h;
	}
	bool operator<(const Node<T>& node) { return data < node.data; }

	bool operator>(const Node<T>& node) { return data > node.data; }

};

template<class T>
class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node<T>* root;
public:
	//доступ к корневому элементу
	virtual Node<T>* getRoot() { return root; }

	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree<T>() { root = NULL; }

	//итеративная функция добавления узла
	virtual Node<T>* Add(Node<T>* N)
	{
		if (root == NULL)
		{
			//в дереве нет узлов - добавляем узел в корень
			root = N;
			return N;
		}

		Node<T>* Current = root;
		while (Current != NULL)
		{
			//сравниваем данные в текущем узле с добавляемым. Идём влево или вправо
			if (Current->getData() < N->getData())
			{
				//если справа есть ветвь, идём туда
				if (Current->getRight() != NULL)
				{
					Current = Current->getRight();
					continue;
				}

				//вставляем новый узел, если встретили пустое место
				Current->setRight(N);
				N->setParent(Current);
				N->setHeight(Current->getHeight() + 1);
				break;
			}
			//аналогично для левой ветви
			if (Current->getData() > N->getData())
			{
				if (Current->getLeft() != NULL)
				{
					Current = Current->getLeft();
					continue;
				}

				Current->setLeft(N);
				N->setParent(Current);
				N->setHeight(Current->getHeight() + 1);
				break;
			}
		}
		return N;
	}
	virtual void Add(T n)
	{
		Node<T>* N = new Node<T>;
		N->setData(n);
		Tree<T>::Add(N);
	}
	void  fixHeight(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		if (hl != 0 || hr != 0)
			p->setHeight((hl > hr ? hl : hr) + 1);
		else
			p->setHeight(0);
	}
	void fixAllHights(Node<T>* p)
	{
		fixHeight(p);
		while (p->getParent())
		{
			fixHeight(p);
			p = p->getParent();
		}
	}
	//удаление узла
	virtual void Remove(Node<T>* N)
	{
		if (N == NULL) return;
		///////////////////Когда удаляемый элемент - корень//////////////////////
		if (N == root && N->getLeft() == NULL && N->getRight() == NULL)///Когда есть только один элемент
		{
			delete N;
			root = NULL;
			return;
		}
		else if (N == root && N->getLeft() != NULL && N->getRight() == NULL) // Когда есть только левый потомок
		{
			root = N->getLeft();
			root->setHeight(root->getHeight() - 1);
			root->setParent(NULL);
			delete N;
			return;
		}
		else if (N == root && N->getLeft() == NULL && N->getRight() != NULL) // Когда есть только правый потомок
		{
			root = N->getRight();
			root->setHeight(root->getHeight() - 1);
			root->setParent(NULL);
			delete N;
			return;
		}
		else if (N == root && N->getLeft() != NULL && N->getRight() != NULL)/// Когда есть два потомка 
		{
			Node<T>* maxLeft = Tree::Max(N->getLeft());
			if (maxLeft->getParent()->getRight() == maxLeft)///Когда он правый потомок отца
			{
				maxLeft->getParent()->setRight(maxLeft->getLeft());
				maxLeft->setRight(N->getRight());
				if (maxLeft->getLeft() != NULL)
					maxLeft->getLeft()->setParent(maxLeft->getParent());
				maxLeft->setLeft(N->getLeft());
				N->getLeft()->setParent(maxLeft);

			}
			else//Если левый потомок отца то он равен N.getLeft()
			{
				maxLeft->setRight(N->getRight());
			}
			N->getRight()->setParent(maxLeft);
			fixHeight(maxLeft);
			root = maxLeft;
			root->setParent(NULL);
			delete N;
			return;
		}
		////////////// Когда элемент - не корень ,тут нам надо разобраться с родителем ////////////////
		Node<T>* par = N->getParent();
		if (N->getLeft() == NULL && N->getRight() == NULL)/// Когда нет потомков 
		{
			if (par->getLeft() == N)
			{// Если сам - левый потомок parent'a
				par->setLeft(NULL);
			}
			else
			{
				par->setRight(NULL);
			}
			fixAllHights(par);
			delete N;
		}
		else if (N->getLeft() != NULL && N->getRight() == NULL)// Когда есть только левый потомок
		{
			if (par->getLeft() == N)// Если сам - левый потомок parent'a
			{
				par->setLeft(N->getLeft());
				N->getLeft()->setParent(par);
			}
			else
			{
				par->setRight(N->getLeft());
				N->getLeft()->setParent(par);
			}
			fixAllHights(par);
			delete N;
		}
		else if (N->getLeft() == NULL && N->getRight() != NULL) // Когда есть только правый потомок
		{
			if (par->getLeft() == N)// Если сам левый потомок parent'a
			{
				par->setLeft(N->getRight());
				N->getRight()->setParent(par);
			}
			else
			{
				par->setRight(N->getRight());
				N->getRight()->setParent(par);
			}
			fixAllHights(par);
			delete N;
		}
		else if (N->getLeft() != NULL && N->getRight() != NULL)/// Когда есть два потомка 
		{
			Node<T>* maxLeft = Tree::Max(N->getLeft());
			if (maxLeft->getParent()->getRight() == maxLeft) ///Когда правый потомок отца
			{
				maxLeft->getParent()->setRight(maxLeft->getLeft());
				maxLeft->setRight(N->getRight());
				if (maxLeft->getLeft() != NULL)
					maxLeft->getLeft()->setParent(maxLeft->getParent());
				maxLeft->setLeft(N->getLeft());
				N->getLeft()->setParent(maxLeft);
			}
			else// Когда левый сын тогда равен n.getLeft()
			{
				maxLeft->setRight(N->getRight());
			}
			N->getRight()->setParent(maxLeft);
			fixHeight(maxLeft);
			maxLeft->setParent(par);
			if (par->getLeft() == N)
				par->setLeft(maxLeft);
			else
				par->setRight(maxLeft);
			fixAllHights(par);
			delete N;
		}
	}

	virtual Node<T>* Min(Node<T>* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) return NULL;

		if (Current == NULL) Current = root;
		while (Current->getLeft() != NULL)
			Current = Current->getLeft();

		return Current;
	}

	virtual Node<T>* Max(Node<T>* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) return NULL;
		if (Current == NULL) Current = root;
		while (Current->getRight() != NULL)
			Current = Current->getRight();
		return Current;
	}
	virtual Node<T>* Find(T data, Node<T>* Current)
	{
		if (Current == NULL) return NULL;

		if (Current->getData() == data) return Current;

		if (Current->getData() > data) return Find(data, Current->getLeft());

		if (Current->getData() < data) return Find(data, Current->getRight());
	}

	//три обхода дерева
	virtual void PreOrder(Node<T>* N)
	{
		if (N != NULL)
			N->getData().print();

		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft());
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight());
	}

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node<T>* N)
	{
		if (root == NULL) return;

		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft());
		if (N != NULL)
			N->getData().print();
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight());

	}
	virtual void PostOrder(Node<T>* N)
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft());
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight());
		if (N != NULL)
			N->getData().print();

	}

	virtual Node<T>* Successor(Node<T>* current)
	{
		// Поиск - O(h)
		//Node<T>* current = Find(data, root);
		if (current == NULL) return NULL;
		if (current->getRight() != NULL)
		{
			return Min(current->getRight());  //Первый случай - O(h)
		}
		else
		{   //Второй случай - O(h)
			struct Node<T>* successor = NULL;
			struct Node<T>* ancestor = root;
			while (ancestor != current) {
				if (current->getData() < ancestor->getData()) {
					successor = ancestor;
					ancestor = ancestor->getLeft();
				}
				else
					ancestor = ancestor->getRight();
			}
			return successor;
		}
	}
	virtual Node<T>* Predcessor(Node<T>* current)
	{
		Node<T>* tmp = current;
		if (current == NULL) return NULL;
		else if (current == root && current->getLeft() == NULL) return NULL;
		else if (current->getLeft() != NULL)
		{
			return Max(current->getLeft());
		}
		else
		{
			while (tmp->getParent() && tmp->getParent()->getRight() != tmp)
			{
				tmp = tmp->getParent();
			}
			return tmp->getParent();
		}
	}
};

template <class T>
class AVL_Tree : public Tree<T>
{
protected:
	int bfactor(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		return (hr - hl);
	}

	//при добавлении узлов в них нет информации о балансе, т.к. не ясно, куда в дереве они попадут
	//после добавления узла рассчитываем его высоту (расстояние до корня) и редактируем высоты в узлах, где это
	//значение могло поменяться
	void fixHeight(Node<T>* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		p->setHeight((hl > hr ? hl : hr) + 1);
	}
	//краеугольные камни АВЛ-деревьев - процедуры поворотов
	Node<T>* RotateRight(Node<T>* p) // правый поворот вокруг p
	{

		Node<T>* q = p->getLeft();
		p->setLeft(q->getRight());
		if (q->getRight())
			q->getRight()->setParent(p);
		q->setRight(p);
		q->setParent(p->getParent());
		if (p->getParent() && p->getParent()->getLeft() == p)
			p->getParent()->setLeft(q);
		else if (p->getParent())
			p->getParent()->setRight(q);
		p->setParent(q);

		if (p == Tree<T>::root)
		{
			Tree<T>::root = q;
			Tree<T>::root->setParent(NULL);
		}
		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node<T>* RotateLeft(Node<T>* q) // левый поворот вокруг q
	{
		Node<T>* p = q->getRight();
		q->setRight(p->getLeft());
		if (p->getLeft())
			p->getLeft()->setParent(q);

		p->setLeft(q);
		p->setParent(q->getParent());
		if (q->getParent() && q->getParent()->getLeft() == q)
			q->getParent()->setLeft(p);
		else if (q->getParent())
			q->getParent()->setRight(p);
		q->setParent(p);

		if (q == Tree<T>::root)
		{
			Tree<T>::root = p;
			Tree<T>::root->setParent(NULL);
		}
		fixHeight(q);
		fixHeight(p);
		return p;
	}

	//балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
	Node<T>* Balance(Node<T>* p) // балансировка узла p
	{
		fixHeight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->getRight()) < 0)
				p->setRight(RotateRight(p->getRight()));
			return RotateLeft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->getLeft()) > 0)
				p->setLeft(RotateLeft(p->getLeft()));
			return RotateRight(p);
		}
		return p; // балансировка не нужна
	}
	void BalanceAll(Node<T>* p)
	{
		Balance(p);
		while (p->getParent())
		{
			p = p->getParent();
			Balance(p);
		}
	}
public:
	//конструктор AVL_Tree вызывает конструктор базового класса Tree
	AVL_Tree() : Tree<T>() {}
	//переопределение функции базового класса, чтобы использовать обновлённую функцию Add_R
	virtual void Add(T n)
	{
		Node<T>* N = new Node<T>;
		N->setData(n);
		Node<T>* AddedNode=Tree<T>::Add(N);
		Balance(AddedNode);
	}

	virtual void Remove(Node<T>* N)
	{
		if (N == NULL) return;
		///////////////////Когда удаляемый элемент - корень//////////////////////
		if (N == Tree<T>::root && N->getLeft() == NULL && N->getRight() == NULL)///Когда есть только один элемент
		{
			delete N;
			Tree<T>::root = NULL;
			return;
		}
		else if (N == Tree<T>::root && N->getLeft() != NULL && N->getRight() == NULL) // Когда есть только левый потомок
		{
			Tree<T>::root = N->getLeft();
			Tree<T>::root->setHeight(0);
			Tree<T>::root->setParent(NULL);
			delete N;
			return;
		}
		else if (N == Tree<T>::root && N->getLeft() == NULL && N->getRight() != NULL) // Когда есть только правый потомок
		{
			Tree<T>::root = N->getRight();
			Tree<T>::root->setHeight(0);
			Tree<T>::root->setParent(NULL);
			delete N;
			return;
		}
		else if (N == Tree<T>::root&& N->getLeft() != NULL && N->getRight() != NULL)/// Когда есть два потомка 
		{
			Node<T>* maxLeft = Tree<T>::Max(N->getLeft());
			if (maxLeft->getParent()->getRight() == maxLeft)///Когда он правый потомок отца
			{
				maxLeft->getParent()->setRight(maxLeft->getLeft());
				maxLeft->setRight(N->getRight());
				if (maxLeft->getLeft() != NULL)
					maxLeft->getLeft()->setParent(maxLeft->getParent());
				maxLeft->setLeft(N->getLeft());
				N->getLeft()->setParent(maxLeft);

			}
			else//Если левый потомок отца то он равен N.getLeft()
			{
				maxLeft->setRight(N->getRight());
			}
			N->getRight()->setParent(maxLeft);
			Node<T>* par = maxLeft->getParent();
			maxLeft->setParent(NULL);
			Tree<T>::root = maxLeft;

			BalanceAll(par);
			delete N;
			return;
		}
		////////////// Когда элемент - не корень ,тут нам надо разобраться с родителем ////////////////
		Node<T>* par = N->getParent();
		if (N->getLeft() == NULL && N->getRight() == NULL)/// Когда нет потомков 
		{
			if (par->getLeft() == N)// Если сам - левый потомок parent'a
				par->setLeft(NULL);
			else
				par->setRight(NULL);
			Tree<T>::fixAllHights(par);
			BalanceAll(par);
			delete N;
		}
		else if (N->getLeft() != NULL && N->getRight() == NULL)// Когда есть только левый потомок
		{
			if (par->getLeft() == N)// Если сам - левый потомок parent'a
			{
				par->setLeft(N->getLeft());
				N->getLeft()->setParent(par);
			}
			else
			{
				par->setRight(N->getLeft());
				N->getLeft()->setParent(par);
			}
			Tree<T>::fixAllHights(par);
			BalanceAll(par);
			delete N;
		}
		else if (N->getLeft() == NULL && N->getRight() != NULL) // Когда есть только правый потомок
		{
			if (par->getLeft() == N)// Если сам левый потомок parent'a
			{
				par->setLeft(N->getRight());
				N->getRight()->setParent(par);
			}
			else
			{
				par->setRight(N->getRight());
				N->getRight()->setParent(par);
			}
			Tree<T>::fixAllHights(par);
			BalanceAll(par);
			delete N;
		}
		else if (N->getLeft() != NULL && N->getRight() != NULL)/// Когда есть два потомка 
		{
			Node<T>* maxLeft = Tree<T>::Max(N->getLeft());
			if (maxLeft->getParent()->getRight() == maxLeft) ///Когда правый потомок отца
			{
				maxLeft->getParent()->setRight(maxLeft->getLeft());
				maxLeft->setRight(N->getRight());
				if (maxLeft->getLeft() != NULL)
					maxLeft->getLeft()->setParent(maxLeft->getParent());
				maxLeft->setLeft(N->getLeft());
				N->getLeft()->setParent(maxLeft);
			}
			else// Когда левый сын тогда равен n.getLeft()
			{
				maxLeft->setRight(N->getRight());
			}
			N->getRight()->setParent(maxLeft);
			fixHeight(maxLeft);
			maxLeft->setParent(par);
			if (par->getLeft() == N)
				par->setLeft(maxLeft);
			else
				par->setRight(maxLeft);
			Tree<T>::fixAllHights(par);
			Balance(par);
			delete N;
		}
	}
	Node<T>* Successor(Node<T>* current)
	{
		return Tree<T>::Successor(current);
	}
	Node<T>* Predcessor(Node<T>* current)
	{
		return Tree<T>::Predcessor(current);
	}
	Node<T>* End()
	{
		Node<T>* end = new Node<T>();
		return end;
	}
};

template<typename T>
class TreeIterator : public iterator<input_iterator_tag, T>
{
public:
	TreeIterator<T>()
	{
		node = NULL;
		tree =AVL_Tree<T>();
	};

	TreeIterator<T>(Node<T>* node, AVL_Tree<T> tree) :
		node(node),
		tree(tree) {}

	TreeIterator<T>(const TreeIterator& i) :
		node(i.node),
		tree(i.tree) {}

	TreeIterator<T>& operator=(const TreeIterator& i)
	{
		node = i.node;
		tree = i.tree;

		return *this;
	}

	TreeIterator<T>& operator=(Node<T>* temp)
	{
		node = temp;

		return *this;
	}

	bool operator!=(const TreeIterator<T> const& other) const { return node != other.node; }
	//bool operator!=( Node<T> &other) const { return node != other; }

	bool operator==(const TreeIterator<T> const& other) const { return node == other.node; }

	bool operator!() const { return !node; }

	Node<T>& operator*() const { return *(node); }

	TreeIterator<T>& operator++()
	{
		node = tree.Successor(node);

		return *this;
	}

	TreeIterator<T>& operator++(int temp)
	{
		node = tree.Successor(node);

		return *this;
	}

	TreeIterator<T>& operator--()
	{
		node = tree.Predcessor(node);

		return *this;
	}

	TreeIterator<T>& operator--(int temp)
	{
		node = tree.Predcessor(node);

		return *this;
	}
	
	template<class T>
	friend ostream& operator<< (ostream& ustream, TreeIterator<T>& obj);
private:
	Node<T>* node;
	AVL_Tree<T> tree;
};

template<class T>
ostream& operator<< (ostream& ustream, TreeIterator<T>& obj)
{
	obj.node->getData().print();
	return ustream;
}

template<class T>
class Heap
{
private:
	//массив
	Node<T>* arr;
	//сколько элементов добавлено
	int len;
	//сколько памяти выделено
	int size;
public:

	//доступ к вспомогательным полям кучи и оператор индекса
	int getCapacity() { return size; }
	int getCount() { return len; }

	Node<T>& operator[](int index)
	{
		if (index < 0 || index >= len)

		return arr[index];
	}

	//конструктор
	Heap<T>(int MemorySize = 100)
	{
		arr = new Node<T>[MemorySize];
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

		Node<T> temp;
		temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;
	}

	//скопировать данные между двумя узлами
	void Copy(Node<T>* dest, Node<T>* source)
	{
		dest->setData(source->getData());
	}

	//функции получения левого, правого дочернего элемента, родителя или их индексов в массиве
	Node<T>* GetLeftChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака
		return &arr[index * 2 + 1];
	}

	Node<T>* GetRightChild(int index)
	{
		if (index < 0 || index * 2 >= len)
			;
		//здесь нужна защита от дурака

		return &arr[index * 2 + 2];
	}

	Node<T>* GetParent(int index)
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
	void heapify(int i)
	{
		int largest = i;
		int l = GetLeftChildIndex(i);
		int r = GetRightChildIndex(i);
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
	void Add(T v)
	{
		Node<T>* N = new Node<T>;
		N->setData(v);
		Add(N);
	}
	void Add(Node<T>* N)
	{
		if (len < size)
		{
			Copy(&arr[len], N);
			len++;
			SiftUp();
		}
	}

	Node<T> ExtractMax()
	{
		//исключить максимум и запустить просеивание кучи
		Node<T> last = arr[len - 1];
		Node<T> max = arr[0];
		arr[0] = last;
		len--;
		heapify(0);
		return max;
	}

	//удаление элемента
	void Remove(T v)
	{
		if (len == 0) return;
		int i = 0;
		while (i < len)
		{
			if (arr[i].getData() == v)
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
	void Straight(void(*f)(Node<T>*))
	{
		int i;
		for (i = 0; i < len; i++)
		{
			f(&arr[i]);
		}
	}

	//перебор элементов, аналогичный проходам бинарного дерева
	void PreOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetLeftChildIndex(index) < len)
			PreOrder(f, GetLeftChildIndex(index));
		if (GetRightChildIndex(index) < len)
			PreOrder(f, GetRightChildIndex(index));
	}

	void InOrder(void(*f)(Node<T>*), int index = 0)
	{
		if (GetLeftChildIndex(index) < len)
			InOrder(f, GetLeftChildIndex(index));
		if (index >= 0 && index < len)
			f(&arr[index]);
		if (GetRightChildIndex(index) < len)
			InOrder(f, GetRightChildIndex(index));
	}

	void PostOrder(void(*f)(Node<T>*), int index = 0)
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
	setlocale(LC_ALL, "Russian");
	////Пункт 2.1  
	//К - Псевдоним     V - СуперСила

	map<string, string> mp;
	mp.emplace("SuperMan", "Power");
	mp.emplace("Hulk", "Power");
	mp.emplace("IronMan", "Technologies");
	mp.emplace("Capitan America", "Power");
	mp.emplace("SpiderMan", "Pautina");
	mp.emplace("Tor", "Lightning");
	mp.emplace("Flash", "Speed");
	mp.emplace("Dr.Strange", "Magic");

	cout << "====================================" << endl;
	cout << "Функция - printMap():" << endl;
	cout << "====================================" << endl;
	printMap(mp);

	cout << "====================================" << endl;
	cout << "Функция - findByKey(Key):" << endl;
	cout << "====================================\n" << endl;
	auto res=findByKey(mp,(string)"Flash");

	cout << "\n====================================" << endl;
	cout << "Функция - findByValue(Value):" << endl;
	cout << "====================================\n" << endl;
	auto res1 = findByValue(mp,(string)"Power");
	for (auto i : res1)
	{
		cout << i.second<<"= Map["<<i.first<<"]\n";
	}

	cout << "\n====================================" << endl;
	cout << "Функция - filter():" << endl;
	cout << "====================================\n" << endl;

	map<string, string> filteredMap = filter(mp, threshold);

	printMap(filteredMap);
	

	////// Пункт 2.2 priority queue

	//priority_queue<pair<string, string>> q;
	//q.push(pair<string, string>("SuperMan", "Power"));
	//q.push(pair<string, string>("Hulk", "Power"));
	//q.push(pair<string, string>("IronMan", "Technologies"));
	//q.push(pair<string, string>("Capitan America", "Power"));
	//q.push(pair<string, string>("SpiderMan", "Pautina"));
	//q.push(pair<string, string>("Tor", "Lightning"));
	//q.push(pair<string, string>("Flash", "Speed"));
	//q.push(pair<string, string>("Dr.Strange", "Magic"));


	//cout << "\n====================================" << endl;
	//cout << "Функция - printQueue():" << endl;
	//cout << "====================================\n" << endl;
	//printQueue(q);
	// 
	//
	///// Пункт 2.3

	//SuperHero s("F", 2000, 50);
	//SuperHero s1("E", 9000, 40);
	//SuperHero s2("D", 9000, 100);
	//SuperHero s4("B", 10000, 60);
	//SuperHero s5("C", 10000, 60);
	//SuperHero s3("A", 10000, 90);
	//SuperHero s6("G", 2500, 70);
	//SuperHero heros[] = { s,s1,s2,s3,s4,s5,s6 };

	//AVL_Tree<SuperHero> T;
	//for (auto& el : heros)
	//{
	//	T.Add(el);
	//}

	//TreeIterator<SuperHero> Iter(T.Min(), T);
	//TreeIterator<SuperHero> Null;
	//while (Iter != Null )
	//{
	//	cout << Iter;
	//	Iter++;
	//}

	//TreeIterator<SuperHero> Iter1(T.Max(), T);
	//while (Iter1 != Null)
	//{
	//	cout << Iter1;
	//	Iter1--;
	//}
	//


	////// Пункт 2.4 Heap
	//Heap<SuperHero> heap;
	//for (auto& el : heros)
	//{
	//	heap.Add(el);
	//}
	//int len = heap.getCount();
	//for (int i = 1; i < len; i++)
	//{
	//	heap.ExtractMax().getData().print();
	//}
}
