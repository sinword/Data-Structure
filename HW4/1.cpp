#include <iostream>
#include <vector>
using namespace std;

template <class T>
void SWAP(T &a, T &b) {
	T tmp = a;
	a = b;
	b = tmp;
}

class Edge{
public:
	char a;
	char b;
	int w;
public:
	Edge(char a, char b, int w) {
		this->a = a;
		this->b = b;
		this->w = w;
	}
	void printEdge() {
		cout << a << " " << b << " " << w;
		return;
	}
 };

class Vertox {
public:
	char data;
	int subset;
public:
	Vertox(char c, int n) {
		data = c;
		subset = n;
	}
	
	void printVertox() {
		cout << data << " " << subset << endl;
	}
};

class MST {
public:
	vector<Edge> treeEdge;
	vector<Edge> prioQ;
	vector<Vertox> vList;
	int vertoxNum;
	int treeW;
public:
	MST(vector<Edge> edgeSet, int v) {
		treeW = 0;
		prioQ = edgeSet;
		vertoxNum = v;
		for (int i = 0; i < prioQ.size(); i++) {
			bool check1 = true;
			bool check2 = true;
			for (int j = 0; j < vList.size(); j++) {
				if (prioQ[i].a == vList[j].data) {
					check1 = false;
				}
				if (prioQ[i].b == vList[j].data) {
					check2 = false;
				}
			}
			if (check1) {
				vList.push_back(Vertox(prioQ[i].a, -1));
			}
			if (check2) {
				vList.push_back(Vertox(prioQ[i].b, -1));
			}
		}
	}

	void buildMST() {
		int cnt = 1;
		for (int i = 0; i < prioQ.size(); i++) {
			if (treeEdge.size() == vertoxNum - 1) {
				return;
			}
			Edge e = prioQ[i];
			int* s1 = NULL;
			int* s2 = NULL;
			for (int j = 0; j < vList.size(); j++) {
				if (e.a == vList[j].data) {
					s1 = &vList[j].subset;
				}
				if (e.b == vList[j].data) {
					s2 = &vList[j].subset;
				}
			}
			
			if (*s1 == -1 && *s2 == -1) {
				*s1 = *s2 = cnt;
				treeEdge.push_back(e);
				treeW += e.w;
				cnt++;
			}
			else if (*s1 != *s2) {
				if (*s1 != -1 && *s2 == -1) {
					*s2 = *s1;
				}
				else if (*s1 == -1 && *s2 != -1) {
					*s1 = *s2;
				}
				else {
					int NEW, OLD;
					if (*s1 < *s2) {
						NEW = *s1;
						OLD = *s2;
					}
					else {
						NEW = *s2;
						OLD = *s1;
					}
					for (int j = 0; j < vList.size(); j++) {
						if (vList[j].subset == OLD) {
							vList[j].subset = NEW;
						}
					}
				}
				
				treeEdge.push_back(e);
				treeW += e.w;
			}
		}
	}

	void printMST() {
		for (int i = 0; i < treeEdge.size(); i++) {
			char *v1 = &treeEdge[i].a;
			char *v2 = &treeEdge[i].b;
			if (int(*v1) > int(*v2)) {
				swap(*v1, *v2);
			}
		}
		for (int i = 0; i < treeEdge.size() - 1; i++) {
			Edge *e1 = &treeEdge[i];
			Edge *e2 = &treeEdge[i + 1];
			if (e1->w == e2->w) {
				if ((e1->a > e2->a) || (e1->a == e2->a && e1->b > e2->b)) {
					swap(*e1, *e2);
				}

			}
		}

		/*for (int i = 0; i < vList.size(); i++) {
			vList[i].printVertox();
		}*/
		cout << treeW << endl;
		for (int i = 0; i < treeEdge.size(); i++) {
			treeEdge[i].printEdge();
			if (i != treeEdge.size() - 1) {
				cout << endl;
			}
		}
	}
};

int main() {
	int vertoxNum, edgeNum, w;
	char a, b;
	vector<Edge> edgeSet;
	cin >> vertoxNum >> edgeNum;
	for (int i = 0; i < edgeNum; i++) {
		cin >> a >> b >> w;
		edgeSet.push_back(Edge(a, b, w));
	}
	for (int i = 0; i < edgeSet.size() - 1; i++) {
		for (int j = i + 1; j < edgeSet.size(); j++) {
			if (edgeSet[i].w > edgeSet[j].w) {
				SWAP(edgeSet[i], edgeSet[j]);
			}
		}
	}

	
	MST mst(edgeSet, vertoxNum);
	mst.buildMST();
	mst.printMST();
}

/*
6 9
A B 7
A C 6
B C 8
A D 1
C D 5
C E 3
D E 4
E F 2
D F 5

5 6
B E 11
B D 9
C B 4
C D 10
A B 7
A C 3
*/