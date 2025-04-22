#ifndef Graph
#define Graph

#include<iostream>
#include<vector>
#include<queue>
#include <functional> // ✅ 需要这个头文件才能使用 std::function
using namespace std;
const int N = 20;
struct Vex {
	int num;//�������
	string name;//��������
	string desc;//��������
};

struct Edge {
	int vex1;//�ߵĵ�һ����
	int vex2;//�ߵĵڶ�����
	int weight;//Ȩֵ
};

typedef struct Path {
    int vexss[N];
    Path* next;
}*PathList;

class CGraph {

private: int n;//��������
       vector<vector<int>>Matrix;
       vector<Vex> vexs;
public:
    // �Ľ����Ĭ�Ϲ��캯��
    CGraph() : n(0), Matrix(), vexs() {
        // ����������������ʼ���߼��������Ҫ��
    }
    // ��ʼ��ͼ
    void Init(int vertexCount) {
        //n = vertexCount;  // ���ö�����
          // ��ʼ���ڽӾ���Ϊn x n��ȫ0����Ĭ���ޱߣ�
        CGraph();
        Matrix.resize(vertexCount);
        for (int i = 0; i < vertexCount; ++i) {
            Matrix[i].resize(vertexCount, 0);  // ��Ϊ��Ȩͼ���ɳ�ʼ��ΪINF
        }
        // ��ʼ�����㼯�ϣ�����Vex��Ĭ�Ϲ��캯����
        vexs.resize(vertexCount);
    }
    bool InsertVex(Vex vex) {
        if (n == N) {
            return false;
        }
        vexs[n++] = vex;
        return true;
    }

    bool InsertEdge(Edge edge) {
        if (edge.vex1 < 0 || edge.vex1 >= n || edge.vex2 < 0 || edge.vex2 >= n) {
            return false;
        }
        Matrix[edge.vex1][edge.vex2] = edge.weight;
        Matrix[edge.vex2][edge.vex1] = edge.weight;
        return true;
    }

    void printvex() {
        cout << "=====景区 =====" << endl;
        for (int i = 0; i < n; i++) {
            cout << i << " - " << vexs[i].name << endl;
        }

    }

    void printedge() {
        cout << "----- 边 -----" << endl;
        for (int i = 0; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                if (Matrix[i][j] != 0) {
                    cout << "(" << vexs[i].name << "," << vexs[j].name << ")" << " " << Matrix[i][j] << endl;
                }
            }
        }
    }

    Vex GetVex(int v) {
        return vexs[v];
    }

    int FindEdge(int v, vector<Edge>& a) {
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (Matrix[v][i] != 0) {
                a.push_back({ v,i,Matrix[v][i] });
                k++;
            }
        }
        return k;
    }

    void DFS(int v, bool bVisted[], vector<int>& path, vector<vector<int>>& paths) {
        path.push_back(v);
        bVisted[v] = true;  // 标记已访问

        if (path.size() == n) {  // 如果遍历了所有点，则记录路径
            paths.push_back(path);
        }
        else {
            for (int i = 0; i < n; i++) {
                if (Matrix[v][i] != 0 && !bVisted[i]) {
                    DFS(i, bVisted, path, paths);
                }
            }
        }

        // 回溯，撤销访问状态
        bVisted[v] = false;
        path.pop_back();
    }

    void DFSTraverse(int nVex) {
        bool bVisted[N] = { false };
        vector<int> path;
        vector<vector<int>> paths;

        DFS(nVex, bVisted, path, paths);

        // 输出所有路径
        for (const auto& p : paths) {
            for (size_t i = 0; i < p.size(); i++) {
                cout << vexs[p[i]].name << (i == p.size() - 1 ? "\n" : " -> ");
            }
        }
    }

    int FindShortPath(int vexstart, int vexend) {
        vector<int>vis(n, false);
        vector<int>dis(n,1e9);
        vector<int>path(n, -1);
        vis[vexstart] = true;
        dis[vexstart] = 0;
        priority_queue<pair<int, int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
        q.push({dis[vexstart],vexstart});
        while (!q.empty()) {
            int cost = q.top().first;
            int u = q.top().second;
            q.pop();
            vis[u] = true;
            for (int v = 0; v < n; v++) {
                if (Matrix[u][v] != 0 && !vis[v]) {
                    if (dis[v] > Matrix[u][v] + cost) {
                        dis[v] = Matrix[u][v] + cost;
                        path[v] = u;
                        q.push({ dis[v],v });
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            cout << i << " " << dis[i] << endl;
        }
        vector<int>ans;
        int k = vexend;
        while (path[k] != -1) {
            ans.push_back(k);
            k = path[k];
        }
        ans.push_back(k);
        cout << "最短路径为:";
        for (int i = ans.size() - 1; i >= 0; i--) {
            cout<< vexs[ans[i]].name <<((i!=0)? "->":"\n");
        }
        return dis[vexend];
    }

    int FindMinTree() {
        vector<int> father(n + 1, -1);
        for (int i = 0; i < n; i++) {
            father[i] = i;
        }

        // find1 递归函数
        function<int(int)> find1 = [&](int i) {
            if (i != father[i]) {
                father[i] = find1(father[i]); // 路径压缩
            }
            return father[i];
            };

        // is_sameset 判断是否在同一集合
        auto is_sameset = [&](int x, int y) {
            return find1(x) == find1(y);
            };

        auto unionSet = [&](int x, int y) {
            int fx = find1(x);
            int fy = find1(y);
            father[fx] = fy;
            };
        priority_queue<pair<int, pair<int, int>>, vector < pair<int, pair<int, int>>>, greater<pair<int, pair<int, int> > > >q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (Matrix[i][j] != 0) {
                    q.push({ Matrix[i][j],{i,j} });
                }
            }
        }
        vector<pair<int, pair<int, int>>>ans;
        while (!q.empty()) {
            int cost = q.top().first;
            int u = q.top().second.first;
            int v = q.top().second.second;
            q.pop();
            if (!is_sameset(u, v)) {
                unionSet(u, v);
                ans.push_back({ cost, { u,v } });
            }
        }
        int all = 0;
        for (auto x : ans) {
            int cost = x.first;
            int u = x.second.first;
            int v = x.second.second;
            cout << vexs[u].name << "->" << vexs[v].name <<"距离：" <<cost <<"m" << endl;
            all += cost;
        }
        return all;
    }

}; 
#endif // !Graph
