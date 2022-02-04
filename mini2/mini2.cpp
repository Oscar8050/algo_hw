#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void DFS(vector<vector<int> > &adj_list, vector<int> &D_route, int pos, int status[]);
void BFS(vector<vector<int> > &adj_list, vector<int> &B_route, int pos, int status[]);

int main() {
    ios_base:: sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;
    
    vector<vector<int> > adj_list(N);
    int v1, v2;
    for (int i = 0; i < M; i++){
        cin >> v1 >> v2;
        v1 -= 1;
        v2 -= 1;
        adj_list[v1].push_back(v2);
        adj_list[v2].push_back(v1);
    }
    
    /*for (int i = 0; i < N; i++){
        sort(adj_list[i].begin(), adj_list[i].end());
    }
    cout << "--------------" << endl;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < adj_list[i].size(); j++)
            cout << adj_list[i][j] << " ";
        cout << endl;
    }
    cout << "--------------" << endl;*/
    
    vector<int> D_route, B_route;
    int status[N];
    for (int i = 0; i < N; i++)
        status[i] = 0;
    DFS(adj_list, D_route, 0, status);
    for (int i = 0; i < N; i++)
        status[i] = 0;
    BFS(adj_list, B_route, 0, status);
    
    for (int i = 0; i < D_route.size(); i++)
        cout << D_route[i]+1 << " ";
    
    cout << endl;
    
    for (int i = 0; i < B_route.size(); i++)
        cout << B_route[i]+1 << " ";
    
    
    return 0;
}

void DFS(vector<vector<int> > &adj_list, vector<int> &D_route, int pos, int status[]) {
    status[pos] = 1;
    D_route.push_back(pos);
    vector<int> priority;
    for (int i = 0; i < adj_list[pos].size(); i++){
        if (status[adj_list[pos][i]] != 1){
            priority.push_back(adj_list[pos][i]);
        }
    }
    
    if (priority.size() == 0)
        return;
    sort(priority.begin(), priority.end());
    for (int i = 0; i < priority.size(); i++){
        if (status[priority[i]] != 1)
            DFS(adj_list, D_route, priority[i], status);
    }
    
    return;
}

void BFS(vector<vector<int> > &adj_list, vector<int> &B_route, int pos, int status[]){
    queue <int> priority;
    
    priority.push(pos);
    int len, out;
    while (priority.size() != 0) {
        len = priority.size();
        
        vector<int> ssort;
        for (int i = 0; i < len; i++){
            ssort.push_back(priority.front());
            priority.pop();
        }
        sort(ssort.begin(), ssort.end());
        for (int i = 0; i < len; i++){
            priority.push(ssort[i]);
        }
        
        for (int i = 0; i < len; i++){
            //cout << "2";
            
            out = priority.front();
            priority.pop();
            
            if (status[out] != 1){
                B_route.push_back(out);
                for (int j = 0; j < adj_list[out].size(); j++){
                    if (status[adj_list[out][j]] != 1){
                        priority.push(adj_list[out][j]);
                    }
                }
            }
            status[out] = 1;
        }
    }
}
