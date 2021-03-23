#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <stack>

using namespace std;

struct Edge
{
    Edge(): from(-1), to(-1), weight(0) {};
    Edge(int from_, int to_, int weight_): from(from_), to(to_), weight(weight_) {};

    int from, to, weight;//从哪里，到哪里， 权重
};

// 用邻接矩阵来表示图，即二维数组
struct GraphMatrix
{
    GraphMatrix(): vertexNum(0), graph({}) {};
    GraphMatrix(vector<Edge> edges, int vertexNum_) : vertexNum(vertexNum_)
    {
        if (edges.empty()) graph={};

        const int N = edges.size();

        graph.resize(vertexNum_);
        for (int i = 0; i < N; i++)
        {
            graph[edges[i].from].resize(vertexNum_);
            graph[edges[i].from][edges[i].to] = edges[i].weight;
        }
    }
    int vertexNum;
    vector<vector<int>> graph;
};

struct GraphNode
{
    GraphNode(char name_, int weight_ = 0): name(name_), weight(weight_), nextNode(NULL), visited(false) {};

    char name;
    int weight;//从上一个结点到该结点的边的权重
    bool visited;
    GraphNode* nextNode;
};


//用邻接表表示图
struct GraphList
{
    GraphList(vector<vector<char>> input, vector<vector<int>>& Weight)
    {
        vgnGraphList.clear();
        mniIndex.clear();
        vgnGraphList.reserve(input.size());

        const int N = input.size();
        for (int i = 0; i < N; i++)
        {
            // int weight = Weight.empty() ? 0 : Weight[i][0];
            GraphNode* root = new GraphNode(input[i][0], 0);
            GraphNode* temp = root;
            for (int j = 1; j < input[i].size(); j++)
            {
                int weight = Weight.empty() ? 0 : Weight[i][j-1];                
                GraphNode* nexti = new GraphNode(input[i][j], weight);
                root->nextNode = nexti;
                root = nexti;
            }
            vgnGraphList.push_back(temp);
            // mniIndex[temp->name] = i;
            mniIndex.insert(pair<char, int>(temp->name, i));
        }
    }

    // vector<vector<int>> Weight;   : Weight(Weight_)
    vector<GraphNode*> vgnGraphList;
    map<char, int> mniIndex;
};

struct Dist
{
    Dist(char name_, char pre_, int value_): name(name_), preName(pre_), minvalue(value_) {};
    Dist(char name_, char pre_): name(name_), preName(pre_), minvalue(100000) {};
    char name;
    char preName;
    int minvalue;
};





class Solution
{
public:
    Solution();
    ~Solution();

    //深度搜索

    //Dijkstra算法
    map<char, int> _mooc_Dijkstra(GraphList graph, Dist* &source, map<char,int> result)
    {
        vector<GraphNode*> &vGnGraph = graph.vgnGraphList;
        const int vertexNum = vGnGraph.size();
        vector<Dist> vDBar = {};//保持和vGnGraph的第一个结点同顺序

        // 新建一个Dist，记录每一个的最小值
        for (int i = 0; i < vertexNum; i++)
        {
            if (vGnGraph[i]->name == source->name)
            {
                Dist thisOne(vGnGraph[i]->name, source->name, 0);
                vDBar.push_back(thisOne);
                continue;
            }
            Dist thisOne(vGnGraph[i]->name, source->name);
            vDBar.push_back(thisOne);
        }

        stack<char> temp;
        temp.push(source->name);
        while (!temp.empty())
        {
            char name = temp.top();
            temp.pop();
            int index = graph.mniIndex[name];//计算出这个链的起始点的索引，根据这个索引就可以找到邻接表的链头，要从source开始
            GraphNode* firstNode = vGnGraph[index];//这个链表的第一个
            if (firstNode->visited)
                continue;
            else
            {
                firstNode->visited = true;
                while (firstNode->nextNode)
                {
                    temp.push(firstNode->nextNode->name);
                    int index_ = graph.mniIndex[firstNode->nextNode->name];
                    vDBar[index_].minvalue = min(vDBar[index_].minvalue, (vDBar[index].minvalue + firstNode->nextNode->weight));  
                    if (vDBar[index_].minvalue > (vDBar[index].minvalue + firstNode->nextNode->weight))//如果新的路径更小，就将上一个的name改成这个
                        vDBar[index_].preName = name;

                    firstNode = firstNode->nextNode;
                }            
            }
        }
        
        result.clear();
        for (int j = 0; j < vDBar.size(); j++)
        {
            result.insert(pair<char, int>(vDBar[j].name, vDBar[j].minvalue));
        }
    }
    
    void printHello()
    {
        cout<<"hello stupid"<<endl;
    }

    //Prim算法，最小生成树

//==================================================================================================================
    //207、课程表，给定课程数目，[0,1]在学0之前要先学会1，判断是否可以完成所有课程的学习
    vector<int> visited;
    bool dfs(vector<vector<int>>& edges, int startIndex) 
    {
        if(visited[startIndex] == 1) //证明这条路又出现了这个节点，出现了环
            return false;
        if(visited[startIndex] == -1) //这条路之前走过，没有问题，现在没必要再走一遍了
            return true;
        
        //否则（=0）就是初始化的，都没走过，需要再走一遍
        visited[startIndex] = 1;
        for(auto idx : edges[startIndex])
        {
            if(!dfs(edges, idx))
                return false;
        }
        visited[startIndex] = -1;
        return true;
    }    

    bool _207_canFinish_dfs(int numCourses, vector<vector<int>>& prerequisites) 
    {
        //DFS
        visited = vector<int>(numCourses, 0);
        vector<vector<int>> edges(numCourses, vector<int>{});
        for(auto edge : prerequisites)
        {
            edges[edge[1]].push_back(edge[0]);
        }
        for(int i=0; i<edges.size(); i++)
        {
            if(!dfs(edges, i))
                return false;
        }
        return true;
    }    

    // 用BFS再实现一遍吧
    bool _207_canFinish_bfs(int numCourses, vector<vector<int>>& prerequisites) 
    {
        //BFS
        vector<vector<int>> edges(numCourses);
        vector<int> indegree(numCourses,0);

        for(auto edge : prerequisites)
        {
            edges[edge[1]].push_back(edge[0]);
            indegree[edge[0]]++;
        }

        queue<int> que;
        for (size_t i = 0; i < edges.size(); i++)
        {
            if(indegree[i]==0) 
                que.push(i);
        }

        int ans = 0;
        while (!que.empty())        
        {
            int i = que.front();
            que.pop();
            ans++;
            for(auto j : edges[i])
            {
                indegree[j]--;
                if(indegree[j] == 0)
                    que.push(j);
            }
        }
        return ans == numCourses;
        
    }   
    
//==============================================================================================================================
    //1162、分析陆地到海洋的最远曼哈顿距离
    int maxDistance(vector<vector<int>>& grid)
    {
        int direct[5] = {0,1,0,-1,0};
        queue<pair<int,int>> que;
        int gridsize = grid.size();
        for(int i=0; i<grid.size(); i++)
        {
            for(int j=0; j<grid.size(); j++)
            {
                if(grid[i][j]==1)
                    que.push({i,j});
            }
        }

        if(que.empty() || que.size()==gridsize*gridsize)
            return -1;

        pair<int,int> temp;
        while (!que.empty())
        {
            int size = que.size();
            for(int i=0; i<size; i++)
            {
                temp = que.front();
                que.pop();
                for(int j=0; j<4; j++)
                {
                    int x = temp.first + direct[j];
                    int y = temp.second + direct[j+1];
                    if(x<0 || y<0 || x>gridsize || y>gridsize)
                        continue;
                    grid[x][y] = grid[temp.first][temp.second] + 1;
                    que.push({x,y});
                }
            }
        }
        return grid[temp.first][temp.second]-1;
        
    }

};


int main()
{
    Solution* solution;

    vector<char> input1 = {'a', 'b', 'd'};
    vector<int> weight1 = {50, 10};
    vector<char> input2 = {'b', 'd', 'c'};
    vector<int> weight2 = {15, 50};
    vector<char> input3 = {'d', 'a', 'e'};
    vector<int> weight3 = {20, 15};
    vector<char> input4 = {'c', 'e'};
    vector<int> weight4 = {35};
    vector<char> input5 = {'e', 'c', 'b'};
    vector<int> weight5 = {30, 20};
    vector<char> input6 = {'f' ,'e'};
    vector<int> weight6 = {3};
    vector<vector<char>> input = {input1, input2, input3, input4, input5, input6};
    vector<vector<int>> weight = {weight1, weight2, weight3, weight4, weight5, weight6};
    GraphList graph(input, weight);

    
    Dist* source = new Dist('a', 'a');
    map<char, int> scores;
    // solution->_mooc_Dijkstra(graph, source, scores);

    vector<vector<int>> graph_207{};
    graph_207.push_back(vector<int>{3,0});
    graph_207.push_back(vector<int>{3,1});
    graph_207.push_back(vector<int>{4,1});
    graph_207.push_back(vector<int>{4,2});
    graph_207.push_back(vector<int>{5,3});
    graph_207.push_back(vector<int>{5,4});
    bool result_207 = solution->_207_canFinish_bfs(5, graph_207);

    return 1;
}