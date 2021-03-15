// AVL_Tree_Inh.cpp: определяет точку входа для консольного приложения.
//Структура «Государство».
//Минимальный набор полей : 
//название,
//столица,
//язык,
//численность
//населения, площадь.
//Ключ – название страны.
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
protected:
	//закрытые переменные Node N; N.data = 10 вызовет ошибку
	//int data;
	Country data;
	//не можем хранить Node, но имеем право хранить указатель
	Node* left;
	Node* right;
	Node* parent;

	//переменная, необходимая для поддержания баланса дерева
	int height;
public:
	//доступные извне переменные и функции
	//virtual void setData(int d) { data = d; }
	virtual void setData(Country d) { data = d; }
	virtual Country getData() { return data; }
	int getHeight() { return height; }

	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getParent() { return parent; }

	virtual void setLeft(Node* N) { left = N; }
	virtual void setRight(Node* N) { right = N; }
	virtual void setParent(Node* N) { parent = N; }

	//Конструктор. Устанавливаем стартовые значения для указателей
	/*Node(int n)
	{
		data = n;
		left = right = parent = NULL;
		height = 1;
	}*/

	Node(Country c)
	{
		data = c;
		left = right = parent = NULL;
		height = 0;
	}
	Node()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		data = Country();
		//data = 0;
		height = 0;
	}


	virtual void print()
	{
		data.print();
	}

	virtual void setHeight(int h)
	{
		height = h;
	}
	friend ostream& operator<< (ostream& stream, Node& N);
};

ostream& operator<< (ostream& stream, Node& N)
{
	stream << "\nNode data: " << N.data << ", height: " << N.height;
	return stream;
}
void print(Node* N) { N->getData().print(); }



class Tree
{
protected:
	//корень - его достаточно для хранения всего дерева
	Node* root;
public:
	//доступ к корневому элементу
	virtual Node* getRoot() { return root; }

	//конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит в никуда
	Tree() { root = NULL; }

	//итеративная функция добавления узла
	virtual void Add(Node* N)
	{
		if (root == NULL)
		{
			//в дереве нет узлов - добавляем узел в корень
			root = N;
			return;
		}

		Node* Current = root;
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
			//что делать, если добавляем существующий узел
		}
	}

	//рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
	virtual Node* Add_R(Node* N, Node* Current = NULL)
	{
		if (N == NULL) return NULL;
		if (root == NULL)
		{
			root = N;
			root->setHeight(0);
			return N;
		}
		if (Current == NULL) Current = root;

		if (Current->getData() > N->getData())
		{
			if (Current->getLeft() != NULL)
			{
				Current->setLeft(Add_R(N, Current->getLeft()));
				//////////Балансировка высоты

				Current->setHeight(Current->getLeft()->getHeight());
				if (Current->getRight() && Current->getRight()->getHeight() > Current->getHeight())
					Current->setHeight(Current->getRight()->getHeight());
				Current->setHeight(Current->getHeight() + 1);
			}
			else
			{
				Current->setLeft(N);
				N->setParent(Current);
				if (Current->getRight() == NULL)
					Current->setHeight(Current->getHeight() + 1);
			}
		}

		if (Current->getData() < N->getData())
		{
			if (Current->getRight() != NULL)
			{
				Current->setRight(Add_R(N, Current->getRight()));
				//////////Балансировка высоты
				Current->setHeight(Current->getRight()->getHeight());
				if (Current->getLeft() && Current->getLeft()->getHeight() > Current->getHeight())
					Current->setHeight(Current->getLeft()->getHeight());
				Current->setHeight(Current->getHeight() + 1);

			}
			else
			{
				Current->setRight(N);
				N->setParent(Current);
				if (Current->getLeft() == NULL)
					Current->setHeight(Current->getHeight() + 1);
			}
		}
		//для несбалансированного дерева поиска
		return Current;
	}

	//функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
	virtual void Add(Country n)
	{
		Node* N = new Node;
		N->setData(n);
		Add_R(N);
	}
	void  fixHeight(Node* p)
	{
		int hl = 0;
		int hr = 0;
		if (p->getLeft() != NULL)
			hl = p->getLeft()->getHeight();
		if (p->getRight() != NULL)
			hr = p->getRight()->getHeight();
		if (hl!=0 || hr!=0)
			p->setHeight((hl > hr ? hl : hr) + 1);
		else 
			p->setHeight(0);
	}
	void fixAllHights(Node* p) 
	{
	    fixHeight(p);
		while (p->getParent())
		{
			fixHeight(p);
			p = p->getParent();
		}
	}
	//удаление узла
	virtual void Remove(Node* N)
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
			Node* maxLeft = Tree::Max(N->getLeft());
			if (maxLeft->getParent()->getRight() == maxLeft )///Когда он правый потомок отца
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
		Node* par = N->getParent();
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
			Node* maxLeft = Tree::Max(N->getLeft());
			if (maxLeft->getParent()->getRight() == maxLeft) ///Когда правый потомок отца
			{
				maxLeft->getParent()->setRight(maxLeft->getLeft());
				maxLeft->setRight(N->getRight());
				if (maxLeft->getLeft()!=NULL)
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

	virtual Node* Min(Node* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) return NULL;

		if (Current == NULL) Current = root;
		while (Current->getLeft() != NULL)
			Current = Current->getLeft();

		return Current;
	}

	virtual Node* Max(Node* Current = NULL)
	{
		//минимум - это самый "левый" узел. Идём по дереву всегда влево
		if (root == NULL) return NULL;
		if (Current == NULL) Current = root;
		while (Current->getRight() != NULL)
			Current = Current->getRight();
		return Current;
	}

	//поиск узла в дереве. Второй параметр - в каком поддереве искать, первый - что искать
	virtual Node* Find(Country data, Node* Current)
	{
		if (Current == NULL) return NULL;

		if (Current->getData() == data) return Current;

		if (Current->getData() > data) return Find(data, Current->getLeft());

		if (Current->getData() < data) return Find(data, Current->getRight());
	}

	//три обхода дерева
	virtual void PreOrder(Node* N, void (*f)(Node*))
	{
		if (N != NULL)
			f(N);
		if (N != NULL && N->getLeft() != NULL)
			PreOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PreOrder(N->getRight(), f);
	}

	//InOrder-обход даст отсортированную последовательность
	virtual void InOrder(Node* N, void (*f)(Node*))
	{
		if (root == NULL) return;

		if (N != NULL && N->getLeft() != NULL)
			InOrder(N->getLeft(), f);
		if (N != NULL)
			f(N);
		if (N != NULL && N->getRight() != NULL)
			InOrder(N->getRight(), f);

	}
	virtual void PostOrder(Node* N, void (*f)(Node*))
	{
		if (N != NULL && N->getLeft() != NULL)
			PostOrder(N->getLeft(), f);
		if (N != NULL && N->getRight() != NULL)
			PostOrder(N->getRight(), f);
		if (N != NULL)
			f(N);
	}
	
	/*virtual Node* LCA(Node* u, Node* v)
	{
	
		while (h1 != h2)
		{
			if (h1 > h2)
			{
				u = u->getParent();
				h1--;
			}
			else
			{
				v = v->getParent();
				h2--;
			}
		}
		while (u != v)
		{
			u = u->getParent();
			v = v->getParent();
		}
		return u;
	}*/
	virtual Node* Successor(Country data)
	{
		// Поиск - O(h)
		Node* current = Find(data, root);
		if (current == NULL) return NULL;
		if (current->getRight() != NULL)
		{
			return Min(current->getRight());  //Первый случай - O(h)
		}
		else
		{   //Второй случай - O(h)
			struct Node* successor = NULL;
			struct Node* ancestor = root;
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
	virtual Node* Predcessor(Country data)
	{
		Node* current = Find(data, root);
		Node* tmp = current;
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

class AVL_Tree : public Tree
{
protected:
	int bfactor(Node* p)
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
	void fixHeight(Node* p)
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
	Node* RotateRight(Node* p) // правый поворот вокруг p
	{
	
		Node* q = p->getLeft();
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
		
		if (p == root)
		{
			root = q;
			root->setParent(NULL);
		}
		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node* RotateLeft(Node* q) // левый поворот вокруг q
	{
		Node* p = q->getRight();
		q->setRight(p->getLeft());
		if (p->getLeft())
			p->getLeft()->setParent(q);

		p->setLeft(q);
		p->setParent(q->getParent());
		if ( q->getParent() && q->getParent()->getLeft()==q)
			q->getParent()->setLeft(p);
		else if (q->getParent())
			q->getParent()->setRight(p);
		q->setParent(p);
		
		if (q == root)
		{
			root = p;
			root->setParent(NULL);
		}
		fixHeight(q);
		fixHeight(p);
		return p;
	}

	//балансировка поддерева узла p - вызов нужных поворотов в зависимости от показателя баланса
	Node* Balance(Node* p) // балансировка узла p
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
	void BalanceAll(Node* p)
	{
		Balance(p);
		while (p->getParent())
		{
			p=p->getParent();
			Balance(p);
		}
	}
public:
	//конструктор AVL_Tree вызывает конструктор базового класса Tree
	AVL_Tree() : Tree() {}

	//переопределение функции Add_R
	virtual Node* Add_R(Node* N, Node* Current = NULL)
	{
		//вызываем функцию Add_R из базового класса
		Node* AddedNode = Tree::Add_R(N, Current);
		//применяем к добавленному узлу балансировку
		return Balance(AddedNode);
	}

	//переопределение функции базового класса, чтобы использовать обновлённую функцию Add_R
	virtual void Add(Country n)
	{
		Node* N = new Node;
		N->setData(n);
		Add_R(N);
	}

	virtual void Remove(Node* N)
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
			root->setHeight(0);
			root->setParent(NULL);
			delete N;
			return;
		}
		else if (N == root && N->getLeft() == NULL && N->getRight() != NULL) // Когда есть только правый потомок
		{
			root = N->getRight();
			root->setHeight(0);
			root->setParent(NULL);
			delete N;
			return;
		}
		else if (N == root && N->getLeft() != NULL && N->getRight() != NULL)/// Когда есть два потомка 
		{
			Node* maxLeft = Tree::Max(N->getLeft());
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
			Node* par = maxLeft->getParent();
			maxLeft->setParent(NULL);
			root = maxLeft;

			BalanceAll(par);
			delete N;
			return;
		}
		////////////// Когда элемент - не корень ,тут нам надо разобраться с родителем ////////////////
		Node* par = N->getParent();
		if (N->getLeft() == NULL && N->getRight() == NULL)/// Когда нет потомков 
		{
			if (par->getLeft() == N)// Если сам - левый потомок parent'a
				par->setLeft(NULL);
			else
				par->setRight(NULL);
			fixAllHights(par);
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
			fixAllHights(par);
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
			fixAllHights(par);
			BalanceAll(par);
			delete N;
		}
		else if (N->getLeft() != NULL && N->getRight() != NULL)/// Когда есть два потомка 
		{
			Node* maxLeft = Tree::Max(N->getLeft());
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
			Balance(par);
			delete N;
		}
	}

	virtual Node* LCA(Node* u, Node* v)
	{
		// O(logN)
		Node* P = root;
		Node* k1 = u->getData() < v->getData() ? u : v;
		Node* k2 = u->getData() > v->getData() ? u : v;
		while (true)
		{
			if (P->getData() >= k1->getData() && P->getData() <= k2->getData())
			{
				return P;
			}
			else if (P->getData() > k1->getData() && P->getData() > k2->getData())
				P = P->getLeft();
			else
				P = P->getRight();
		}
	}
};

int main()
{

	Country A("A", "Moscow", "Russian", 14200000, 17000);
	Country B("B", "Kiev", "Ukrainian", 142000, 10000);
	Country C("C", "Minsk", "Belorussian", 142000, 12000);
	Country D("D", "Washington", "English", 3000000, 40000);
	Country E("E", "Berlin", "German", 230000, 123000);
	Country F("F", "Paris", "French", 3000000, 123000);
	Country G("G", "London", "English", 300000, 2230000);
	Country H("H"), N("N"), M("M"), K("K"), L("L"), O("O"), P("P");
	Country Counrties[12] = { D,F,G,E,B,A,C,L,K,M,N,O };

	Tree T1;
	AVL_Tree T2;
	for (int i = 0; i < 12; i++)
	{
		T1.Add(Counrties[i]);
		T2.Add(Counrties[i]);
	}

	void (*f_ptr)(Node*); f_ptr = print;

	Node* rt = T1.getRoot();
	Node* rt2 = T2.getRoot();
	Node* n = T2.Find(Country("N"), rt2);
	Node* k = T2.Find(Country("K"), rt2);
	Node* a = T2.Find(Country("A"), rt2);
	Node* f = T2.Find(Country("F"), rt2);	
	Node* o = T2.Find(Country("O"), rt2);
	Node* cC = T2.Find(Country("C"), rt2);
	Node* res = T2.LCA(a, f);
	Node* res1 = T2.LCA(n, k);
	Node* res2 = T2.LCA(o, cC);
	Node* res3 = T2.LCA(rt2, cC);

	cout << "Ordinary Binary Tree:\n";
	cout << rt->getLeft()->getHeight() << "  <-- rightHight <- ROOT-> leftHight -->   " << rt->getRight()->getHeight() << "\n\n";

	cout << "AVL_Tree:\n";
	cout << rt2->getLeft()->getHeight() << "  <-- rightHight <- ROOT-> leftHight -->   " << rt2->getRight()->getHeight() << "\n\n";

	T2.InOrder(T1.getRoot(), f_ptr);

	cout << "\n\n\t\t\tRoot\n";
	cout << T2.getRoot()->getData();

	
	cout << "\n\n\t\t\tMax :\n";
	Node* mx = T2.Max();
	cout << mx->getData();

	cout << "\n\n\t\t\tMin :\n";
	Node* mn = T2.Min();
	cout << mn->getData();

	T2.Remove(mn);
	T2.Remove(rt2);
	T2.Remove(mx);
	rt2 = T2.getRoot();
	cout << "\n\n\t\t\tMin, Max, Root removed\n";
	cout << rt2->getLeft()->getHeight() << "  <-- rightHight <- ROOT-> leftHight -->   " << rt2->getRight()->getHeight() << endl;
	T2.InOrder(rt2,f_ptr);
	Node* p = T2.Predcessor(Country("D"));
	Node* s = T2.Successor(Country("D"));
	cout << "\n\nPredecessor(D):\n" << p->getData();
	cout << "\n\nSuccessor(D):\n" << s->getData();


	char c; cin >> c;
	return 0;
}
