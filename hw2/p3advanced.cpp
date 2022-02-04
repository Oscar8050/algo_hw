#include <iostream>
#include <queue>
#include <utility>

using namespace std;

struct cmp{
    bool operator()(pair<int, int> a, pair<int, int> b){
        return a.first > b.first;
    }
};


long long arrange(int ptask[][4], priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> sQ, int N);

int main(){
    int N;
    cin >> N;
    int otask[N][4];
    
    priority_queue <pair<int, int>, vector<pair<int, int> >, cmp> sQ;
    priority_queue <pair<int, int> > pQ;
    
    for (int i = 0; i < N; i++){
        cin >> otask[i][0] >> otask[i][1] >> otask[i][2] >> otask[i][3];
        pQ.push(make_pair(otask[i][3], i));
    }
    
    long long allprofit = 0;
    //int minusP = 0;
    int lastP = pQ.top().first;
    pair<int, int> out;
    for (int i = 0; i < N; i++){
        out = pQ.top();
        
        if (out.first != lastP){
            //cout << "1";
            allprofit += arrange(otask, sQ, N) * (lastP-out.first);
            //cout << allprofit << endl;
            //sQ = priority_queue <pair<int, int>, vector<pair<int, int> >, cmp>();
            //minusP = lastP;
        }
        lastP = out.first;
        //cout << "out" << lastP << endl;
        sQ.push(make_pair(otask[out.second][0], out.second));
        pQ.pop();
    }
    
    if (sQ.size() == N){
        allprofit += arrange(otask, sQ, N) * (out.first);
    }
    
    
    /*for (int i = 0; i < N; i++){
        pair<int, int> start = make_pair(task[i][0], i);
        sQ.push(start);
    }
    
    
    
    allprofit += arrange(task, sQ);*/
    
    cout << allprofit;
    
    
    
    
    return 0;
}

long long arrange(int ptask[][4], priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> sQ, int N){
    long long profit = 0;
    int **task = (int**)malloc(N*sizeof(int*));
    for (int i = 0; i < N; i++)
        task[i] = (int*)malloc(4 * sizeof(int));
        
    
    for (int i = 0; i < N; i++){
        task[i][0] = ptask[i][0];
        task[i][1] = ptask[i][1];
        task[i][2] = ptask[i][2];
        task[i][3] = ptask[i][3];
    }
    
    priority_queue <pair<int, int>, vector<pair<int, int> >, cmp> eQ;
    
    int startDay = task[sQ.top().second][0];
    pair<int, int> out1;
    int r_b;
    while (sQ.size() > 0){
        out1 = sQ.top();
        //cout << "out1" << out1.second << endl;
        //cout << "out1 " << out1.second << endl;
        sQ.pop();
        if (task[out1.second][0] != startDay){
            r_b = task[out1.second][0];
            pair<int, int> eout1;
            while (eQ.size() > 0){
                eout1 = eQ.top();
                if (task[eout1.second][1] < r_b || startDay + task[eout1.second][2] - 1 < r_b){
                    if (task[eout1.second][1]-startDay+1 >= task[eout1.second][2]){
                        profit += task[eout1.second][2];
                        startDay += task[eout1.second][2];
                    }else{
                        profit += task[eout1.second][1]-startDay+1;
                        startDay = task[eout1.second][1] + 1;
                    }
                }else{
                    profit += r_b - startDay;
                    task[eout1.second][2] -= r_b - startDay;
                    break;
                }
                eQ.pop();
            }
            startDay = r_b;
        }
        eQ.push(make_pair(task[out1.second][1], out1.second));
        //out1 = sQ.top();
        
    }
    //cout << "sqsize" << sQ.size() << endl;
    //cout << "eqsize" << eQ.size() << endl;
    //cout << startDay << endl;
    
    //cout << profit << endl;
    
    //if (eQ.size() > 0){
        //out1 = eQ.top();
        
    int l_b = startDay;
    while (eQ.size() > 0){
            //cout << "out1 " << out1.second << endl;
        out1 = eQ.top();
        if (task[out1.second][1] - l_b + 1 >= task[out1.second][2]){
            profit += task[out1.second][2];
            l_b += task[out1.second][2];
        }else{
            profit += task[out1.second][1] - l_b + 1;
            l_b = task[out1.second][1] + 1;
        }
        eQ.pop();
            //if (eQ.size() > 0)
                //out1 = eQ.top();
        }
    //}
    //out1 = sQ.top();
    //profit += task[out1.second][2];
    //cout << "sqsize" << sQ.size() << endl;
    //cout << "eqsize" << eQ.size() << endl;
    //cout << "profit" << profit << endl;
    return profit;
}
