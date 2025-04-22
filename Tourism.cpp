#include"Tourism.h"
#include<iostream>
#include"Graph.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;
  CGraph m_Graph;//����һ��ͼ
void CreateGraph() {
    std::vector<Vex> vexs;
    std::vector<Edge> edges;

    // ��ȡ������Ϣ
    std::ifstream vexFile("W:/Vex.txt");
    if (!vexFile.is_open()) {
        std::cerr << "无法打开Vex.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(vexFile, line)) {
        Vex vex;
        size_t pos1 = line.find(' ');
        size_t pos2 = line.find(' ', pos1 + 1);

        vex.num = std::stoi(line.substr(0, pos1));
        vex.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        vex.desc = line.substr(pos2 + 1);

        vexs.push_back(vex);
    }
    vexFile.close();

    // ��ȡ��·��Ϣ
    std::ifstream edgeFile("W:/Edge.txt");
    if (!edgeFile.is_open()) {
        std::cerr << "创建Edge.txt 失败" << std::endl;
        return;
    }

    while (std::getline(edgeFile, line)) {
        Edge edge;
        size_t pos1 = line.find(' ');
        size_t pos2 = line.find(' ', pos1 + 1);

        edge.vex1 = std::stoi(line.substr(0, pos1));
        edge.vex2 = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        edge.weight = std::stoi(line.substr(pos2 + 1));

        edges.push_back(edge);
    }
    edgeFile.close();

    //// �����ȡ������Ϣ
    std::cout << "景区介绍" << std::endl; 
    for (const auto& vex : vexs) {
        std::cout << "ID: " << vex.num << ",景点名: " << vex.name << ", 景点介绍: " << vex.desc << std::endl;
    }

    std::cout << "相邻景区" << std::endl;
    for (const auto& edge : edges) {
        std::cout << " 起始 " << edge.vex1 << " 终点 " << edge.vex2 << ", 距离: " << edge.weight << std::endl;
    }
   

     m_Graph.Init(20);
    for (auto vex : vexs) {  
        
        if (m_Graph.InsertVex(vex) == false) {
            cout << "景区已满" << endl;
        }
    }
    for (auto edge : edges) {
        m_Graph.InsertEdge(edge);
    }
    cout << "创建成功" << endl;

}

void printJQ() {
    m_Graph.printvex();
    m_Graph.printedge();
}

void checkvex() {
  m_Graph.printvex();
}
 
void GetSpotIfo(int x) {
    Vex pv = m_Graph.GetVex(x);
    cout << pv.name << endl << pv.desc << endl;
    vector<Edge>d;
    int k = m_Graph.FindEdge(x, d);
    cout << "-----边-----" << endl;
    for (int i = 0; i < k; i++) {
        cout << d[i].vex1 << "->" << d[i].vex2 << " " << d[i].weight << "m" << endl;
    }
}


void TravelPath(int v) {
    m_Graph.DFSTraverse(v);
}

void FindSortPath() {
    int x, y;
    cout << "请输入起始点和终点:";
    cin >> x >> y;
    int distance = m_Graph.FindShortPath(x, y);
    cout << "最短的距离为" << distance <<"m"<< endl;
}

void DesignPath() {
    int alldis = m_Graph.FindMinTree();
    cout << "总长度：" << alldis <<"m"<< endl;
}