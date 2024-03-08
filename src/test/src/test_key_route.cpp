#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <list>

using namespace std;

const int MAXN = 100;
vector<int> adjacency[MAXN];
int indegree[MAXN];
int critical_path[MAXN];
list<int> critical_path_list;

class KeyRoute {
public:
    KeyRoute() {
        for (int i = 0; i < MAXN; i++) {
            adjacency[i].clear();
            indegree[i] = 0;
            critical_path[i] = 0;
        }
        critical_path_list.clear();
    }

    void addEdge(int u, int v) {
        adjacency[u].push_back(v);
        indegree[v]++;
    }

    void topologicalSort() {
        queue<int> container;
        for (int i = 0; i < MAXN; i++) {
            if (indegree[i] == 0) {
                container.push(i);
                critical_path[i] = 1;
            }
        }

        while (!container.empty()) {
            int u = container.front();
            container.pop();
            for (int v : adjacency[u]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    container.push(v);
                }
                if (critical_path[u] + 1 > critical_path[v]) {
                    critical_path[v] = critical_path[u] + 1;
                }
            }
        }
    }

    void findCriticalPath() {
        for (int i = 0; i < MAXN; i++) {
            if (critical_path[i] != 0) {
                critical_path_list.push_back(i);
                findCriticalPath(i);
            }
        }
    }

    void findCriticalPath(int u) {
        for (int v : adjacency[u]) {
            if (critical_path[v] == critical_path[u] - 1) {
                critical_path_list.push_back(v);
                findCriticalPath(v);
            }
        }
    }

    void displayCriticalPath() {
        cout << "Critical path: ";
        for (int v : critical_path_list) {
            cout << v << " ";
        }
        cout << endl;
    }
};
void test_key_route() {

    vector<int> vec{3,6,7,1,8,2,5,4,9};
    priority_queue<int> order_queue(vec.begin(), vec.end());
    vector<int>result_vec;
    while (!order_queue.empty())
    {
        result_vec.push_back(order_queue.top());
        order_queue.pop();
    }
    priority_queue<int, vector<int>, greater<int>> sort_queue(result_vec.begin(), result_vec.end());

    priority_queue<int> unorder_queue(result_vec.begin(), result_vec.end());


    KeyRoute keyRoute;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        keyRoute.addEdge(u, v);
    }

    keyRoute.topologicalSort();
    keyRoute.findCriticalPath();
    keyRoute.displayCriticalPath();
    int a = 0;
}
