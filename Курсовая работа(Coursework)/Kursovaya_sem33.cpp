// Kursovaya_sem33.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <fstream>
#include<vector>
#include<queue>
#include<unordered_map>
#define I INT_MAX
using namespace std;

class Edge
{
public:
    int from, to, weight;
    Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
    Edge(const Edge& Ed)
    {
        from = Ed.from;
        to = Ed.to;
        weight = Ed.weight;
    }
    int operator<(Edge& Ed)
    {
        return (weight < Ed.weight);
    }
    friend ostream& operator<<(ostream& s, Edge& e);
    friend istream& operator>>(istream& s, Edge& e);
    friend ofstream& operator<<(ofstream& s, Edge& e);
    friend ifstream& operator>>(ifstream& s, Edge& e);
};
ostream& operator<<(ostream& s, Edge& e)
{
    s << "[" << e.from << "] -- [" << e.to << "]   w=" << e.weight;
    return s;
}
istream& operator>>(istream& s, Edge& e)
{
    s >> e.from >> e.to >> e.weight;
    return s;
}
ofstream& operator<<(ofstream& s, Edge& e)
{
    s << e.from << " " << e.to << " " << e.weight << endl;
    return s;
}
ifstream& operator>>(ifstream& s, Edge& e)
{
    s >> e.from >> e.to >> e.weight;
    return s;

}

class Graph
{
private:
    class Row
    {
    public:
        int* row;
        Row()
        {
            row = nullptr;
        }
        Row(int N)
        {
            row = new int[N];
        }
        int& operator [](const int i)
        {
            return row[i];
        }
    };
    int n;
    Row* mat;
public:
    Graph()
    {
        n = 0;
    }
    Graph(int N)
    {
        mat = new Row[N];
        n = N;
        for (int i = 0; i < N; i++)
        {
            mat[i] = Row(N);
        }
    }
    Graph(int N,int num)
    {
        mat = new Row[N];
        n = N;
        for (int i = 0; i < N; i++)
        {
            mat[i] = Row(N);
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                mat[i][j] = num;
            }
        }
    }
    Graph(const Graph& M)
    {
        mat = new Row[M.n];
        n = M.n;
        for (int i = 0; i < n; i++)
        {
            mat[i] = Row(n);
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                mat[i][j] = M.mat[i][j];
            }
        }
    }
    int getN() { return n; }
    Row& operator [](const int i)
    {
        return mat[i];
    }
    friend ostream& operator <<(ostream& stream, Graph& M);
    friend istream& operator >>(istream& stream, Graph& M);
    friend ofstream& operator <<(ofstream& stream, Graph& M);
    friend ifstream& operator >>(ifstream& stream, Graph& M);
};

ostream& operator << (ostream& stream, Graph& M)
{
    stream << "Size: " << M.n << "*" << M.n << endl;

    for (int i = 0; i < M.n; i++)
    {
        for (int j = 0; j < M.n; j++)
        {
            if (M[i][j] == I)
                stream << "0 ";
            else
                stream << M[i][j] << " ";
        }
        cout << endl;
    }
    return stream;
}
istream& operator >>(istream& stream, Graph& M)
{
    cout << "Выведите " << M.n << "x" << M.n << " чисел\n";
    int n;
    for (int i = 0; i < M.n; i++)
    {
        for (int j = 0; j < M.n; j++)
        {
            stream >> n;
            (n == 0) ? n = I : n = n;
            M[i][j] = n;
        }
    }
    return stream;
}
ofstream& operator <<(ofstream& stream, Graph& M)
{
    stream << M.n << endl;
    int n;
    for (int i = 0; i < M.n; i++)
    {
        for (int j = 0; j < M.n; j++)
        {
            n = M[i][j];
            (n == I) ? n = 0 : n = n;

            stream << n << " ";
        }
        stream << endl;
    }
    return stream;

}
ifstream& operator >>(ifstream& stream, Graph& M)
{
    int n;
    stream >> n;
    M = Graph(n);
    for (int i = 0; i < M.n; i++)
    {
        for (int j = 0; j < M.n; j++)
        {
            stream >> n;
            (n == 0) ? n = I : n = n;// Инициализируем INT_MAX-ом для Алгоритма Прима
            M[i][j] = n;
        }
    }
    return stream;
}

vector<Edge> PrimsMST(Graph& G) 
{
    int u, v, V = G.getN(), min = I;
    vector<int> near(V);
    vector<Edge> T(V - 1, 0);
    
    for (int i = 0; i < V; i++)// Находим мин ребро
    {
        near[i] = I; 
        for (int j = i; j < V; j++)
        {
            if (G[i][j] < min)
            {
                min = G[i][j];
                u = i;
                v = j;
            }
        }
    }
    Edge e(u, v, min);
    T[0] = e;
    near[u] = near[v] = -1;
    // Иницализация массива ближайшим к i-той вершине вершиной 
    // т.е.  near[i] - ближайшее к  i  вершина из тех которую мы уже добавили в решение  
    for (int i = 0; i < V; i++)
    {
        if (near[i] != -1)
        {
            if (G[i][u] < G[i][v])
            {
                near[i] = u;
            }
            else
            {
                near[i] = v;
            }
        }
    }

    for (int i = 1; i < V - 1; i++)
    {
        int k;
        min = I;
        for (int j = 0; j < V; j++)
        {
            if (near[j] != -1 && G[j][near[j]] < min)
            {
                k = j;
                min = G[j][near[j]];
            }
        }
        e.from = k;
        e.to = near[k];
        e.weight = min;
        near[k] = -1;
        T[i] = e;
        // Обновим массив near 
        for (int j = 0; j < V; j++)
        {
            if (near[j] != -1 && G[j][k] < G[j][near[j]])
            {
                near[j] = k;
            }
        }
    }
    return T;
}

// Find & Union функции для неперескающихся множеств чтобы обнаружить циклы в Алгоритме Крускала
void Union(int u, int v, vector<int>& s)
{
    if (s[u] < s[v])
    {
        s[u] += s[v];
        s[v] = u;
    }
    else
    {
        s[v] += s[u];
        s[u] = v;
    }
}

int Find(int u, vector<int>& s)
{
    int x = u;
    int v = 0;

    while (s[x] > 0)
    {
        x = s[x];
    }

    while (u != x)
    {
        v = s[u];
        s[u] = x;
        u = v;
    }
    return x;
}

vector<Edge> KruskalsMCST(vector<Edge> &G, int V)
{
    
    int E = G.size();// Количество ребер
    vector <Edge> T(V - 1);
    vector<int> track(E);  // Чтобы проверить добавили ли мы вершину или нет
    vector<int> set(V + 1, -1); // Для того чтобы проверить не получится ли цикл

    int i = 0;
    while (i < V - 1)
    {
        int p1, p2, k = 0;
        Edge min(0, 0, I);
        for (int j = 0; j < E; j++)
        {
            if (track[j] == 0 && G[j] < min)
            {
                min = G[j];
                k = j;
            }
        }
        p1 = Find(min.from, set);
        p2 = Find(min.to, set);
        if (p1 != p2)
        {
            T[i] = min;
            Union(p1, p2, set);
            i++;
        }
        track[k] = 1;
    }
    return T;
}

vector<Edge> GetPathBFS(Graph &edges, int v1, int v2 )
{
    int done =0,V = edges.getN();
    queue<int> q;
    vector<int> visited(V,0);
    unordered_map<int, int> t;
   
    q.push(v1);
    visited[v1] = 1;
    while (!q.empty() && done == 0)
    {
        int front = q.front();
        q.pop();
        for (int i = 0; i < V; i++)
        {
            if (edges[front][i] != 0 && visited[i] != 1)
            {
                q.push(i);
                t[i] = front;
                visited[i] = 1;
                if (i == v2)
                {
                    done = 1;
                    break;
                }
            }
        }
    }
    vector<Edge> a;
    if (done == 0)
        return a;
    else
    {
        int k = v2;
        int from = k,to=t[k];
        while (k != v1)
        {
            from = k;
            k = t[k];
            to = k;
            Edge e(from, to, edges[from][to]);
            a.push_back(e);
        }
        return a;
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    string path="";
    if (argc > 1)
         path = argv[1];
    else
    {
        cout << "Вы не ввели путь к файлу с графами";
        return 0;
    }
    for (int i = 0; i < path.length(); i++)
    {
        if (path[i] == '\\')
        {
            path[i] = '/';
        }
    }
    Graph G1;
    ifstream f1(path);
    int num;
    if (f1.is_open())
    {
        f1 >> num;
        for (int i = 0; i < num; i++)
        {
            cout << "\n\t\t\tПример "<<i+1<<"\n";
            
            f1 >> G1;
            vector<Edge> T = PrimsMST(G1);
            int sum = 0;
            cout << endl << "\n\n\t\t\tРезультат алгоритма Прима\n\n\n";
            for (Edge& e : T)
            {
                sum += e.weight;
                cout << e << endl;
            }
            cout << "sum = " << sum << endl;

            vector<Edge> Edges;
            for (int i = 0; i < G1.getN(); i++)
            {
                for (int j = i; j < G1.getN(); j++)
                {
                    if (G1[i][j] != I)
                    {
                        Edge e(i, j, G1[i][j]);
                        Edges.push_back(e);
                    }
                }
            }
            T = KruskalsMCST(Edges, G1.getN());
            sum = 0;
            cout << endl << "\n\n\t\t\tРезультат алгоритма Крускала" << endl << endl;
            for (Edge& e : T)
            {
                sum += e.weight;
                cout << e << endl;
            }
            cout << "sum = " << sum << endl;
            //// Запишу Вектор Еджес в виде матрицы смежностей для демонстрации нахождения пути 
            Graph G(G1.getN(), 0);
            for (int i = 0; i < T.size(); i++)
            {
                G[T[i].from][T[i].to] = T[i].weight;
                G[T[i].to][T[i].from] = T[i].weight;
            }
            vector<Edge> res = GetPathBFS(G, 0, 3);
            cout << "\n\n\n\t\t\tПуть из вершины 3 в вершину 0\n\n";
            for (int i = 0; i < res.size(); i++)
            {
                cout << res[i] << endl;
            }
            cout << "\n\n\n";
        }
    }
    f1.close();
    system("pause");
    return 0;
}