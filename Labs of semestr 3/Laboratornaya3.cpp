#include <iostream>
#include <vector>
#include<stack>
#include<queue>
#include<unordered_map>
#define I INT_MAX
using namespace std;
vector<int> DFS(int u, vector<vector<int>> &A)
{
    int N = A.size();
    vector<int> visited(N,0);
    vector<int> res;
    stack<int> stk;
    stk.emplace(u);

    while (!stk.empty()) 
    {
        u = stk.top();
        stk.pop();

        if (visited[u] != 1) {
            res.push_back(u);
            visited[u] = 1;

            for (int v = N-1; v >= 0; v--) 
            {
                if (A[u][v] > 0 && visited[v] == 0) 
                {
                    stk.emplace(v);
                }
            }
        }
    }
    return res;
}

vector<int> BFS( int vtx,vector<vector<int>>& A ) 
{
    int N = A.size();
    queue<int> Q;
    vector<int >visited(N,0);
    vector<int> count_of_adj(N, 0);

    visited[vtx] = 1;
    Q.emplace(vtx);

    while (!Q.empty()) 
    {
        int u = Q.front();  
        Q.pop();
        for (int v = 0; v < N; v++) 
        {  
            if (A[u][v] > 0) 
            {  
                count_of_adj[u] += 1;
                if (visited[v] == 0)
                {
                    visited[v] = 1;
                    Q.emplace(v);
                }
            }
        }
    }
    return count_of_adj;
}

vector<vector<int>> PrimsMST(vector<vector<int>>& G)
{
    int u, v,V=G.size(),min=INT_MAX;
    
    vector<int> near(V);
    vector<vector<int>> T(V,vector<int>(V,0));

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
    T[u][v] = T[v][u]=min;
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
        T[k][near[k]] = T[near[k]][k] = min;
        near[k] = -1;
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

vector<int> GetPathBFS(vector<vector<int>>& A, int v1, int v2)
{
    int done = 0, V = A.size();
    queue<int> q;
    vector<int> visited(V);
    unordered_map<int, int> t;

    q.push(v1);
    visited[v1] = 1;
    while (!q.empty() && done == 0)
    {
        int front = q.front();
        q.pop();
        for (int i = 0; i < V; i++)
        {
            if (A[front][i] != 0 && visited[i] != 1)
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
    vector<int> a;
    if (done == 0)
        return a;
    else
    {
        int k = v2;
        int from = k;
        while (k != v1)
        {
            from = k;
            k = t[k];
            a.push_back(from);
        }
        return a;
    }
}

vector<vector<int>> From_i_to_all(int i, vector<vector<int>>& A)
{
    vector<vector<int>> res;
    for (int j = 0; j < A.size(); j++)
    {
        if (j != i)
        {
            vector<int> path = GetPathBFS(A, i, j);
            res.push_back(path);

        }
    }
    return res;
}

void Count_of_adj_vertices(vector<vector<int>>& A)
{
    vector<int> count_of_adj;
    double avg_degree = 0;
    count_of_adj = BFS(0, A);
    cout << "\n\n\t\tЗадача 3.4  Степень вершин:\n\n";
    for (int i = 0; i < count_of_adj.size(); i++)
    {
        avg_degree += count_of_adj[i];
        cout << "deg[" << i << "] = " << count_of_adj[i] << "\n";
    }
    cout << "\nСредняя степень дерева avg_degree = " << avg_degree / count_of_adj.size() << "\n\n";
}

int main()
{
    setlocale(LC_ALL, "");
    vector<vector<int>> Graph =
    {
        {I, 9, 4, 3, 8, 7, 8, 2, 1},
        {9, I, 8, 2, 1, I, 7, 9, 5},
        {4, 8, I, 8, 4, 4, 7, 5, 5},
        {3, 2, 8, I, 3, 4, 6, 2, 6},
        {8, 1, 4, 3, I, 5, 3, 2, 2},
        {7, I, 4, 4, 5, I, 5, 2, 6},
        {8, 7, 7, 6, 3, 5, I, I, I},
        {2, 9, 5, 2, 2, 2, I, I, 6},
        {1, 5, 5, 6, 2, 6, I, 6, I},
    };
    vector<vector<int>> MST = PrimsMST(Graph);
    int sum = 0;
    
    int from = 3;
    vector<vector<int>> Paths;


    cout << "\n\n\t\tЗадача 3.1  Минимальное остовное дерево\n";
    for (int i=0;i<MST.size(); i++)
    {
        for (int j=i; j<MST.size();j++)
        {
            if (MST[i][j] != 0)
            {
                sum += MST[i][j];
                cout << "[" << i << "]---[" << j << "]  w=" << MST[i][j] << endl;
            }
        }
    }
    cout << "Сумма ребер MST = " << sum<<endl<<endl;

     //       0
     //     / | \
    //     7  8  2
    //    /   |      
    //   5    4   
    //       / \
    //      6   1
    //           \
    //            3 
    //9
    vector<int>  res = DFS(0,MST);
    cout << "\n\n\t\tЗадача 3.2  Результат алгоритма DFS()\n\n";
    for (int v : res)
    {
        cout << v << ",";
    }




    Paths = From_i_to_all(from, MST);
    cout << "\n\n\t\tЗадача 3.3  Путь из вершины [" << from << "] во все остальные:\n\n";
    for (int i = 0; i < Paths.size(); i++)
    {
        cout << "[" << from;
        for (int j = Paths[i].size() - 1; j > -1; j--)
        {
            cout << "] -> [" << Paths[i][j] << "";
        }
        cout << "]\n";
    }

    // Задача 3.4
    Count_of_adj_vertices(MST);
}