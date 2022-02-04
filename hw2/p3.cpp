#include <iostream>
#include <queue>
#include <utility>

using namespace std;

struct cmp{
    bool operator()(pair<int, int> a, pair<int, int> b){
        return a.first > b.first;
    }
};

int main(){
    int N;
    cin >> N;
    int task[N][4];
    for (int i = 0; i < N; i++){
        cin >> task[i][0] >> task[i][1] >> task[i][2] >> task[i][3];
    }
    
    priority_queue <pair<int, int>, vector<pair<int, int> >, cmp> sQ, eQ;
    for (int i = 0; i < N; i++){
        pair<int, int> start = make_pair(task[i][0], i);
        sQ.push(start);
    }
    
    long long profit = 0;
    
    int startDay = task[sQ.top().second][0];
    pair<int, int> out1;
    int r_b;
    while (sQ.size() > 0){
        out1 = sQ.top();
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
    
    
    /*while (sQ.size() > 1){
        out1 = sQ.top();
        sQ.pop();
        
        out2 = sQ.top();
        
        if (startDay != task[out2.second][0]){
            eQ.push(make_pair(task[out1.second][1], out1.second));
            pair<int, int> eout1;
            //cout << eout1.second;
        
            while (eQ.size() != 0){
                eout1 = eQ.top();
                eQ.pop();
                if (task[eout1.second][2] > task[out2.second][0] - startDay){
                    profit += task[out2.second][0] - startDay;
                    task[eout1.second][2] -= task[out2.second][0] - startDay;
                    task[eout1.second][0] = task[out2.second][0];
                    sQ.push(make_pair(task[eout1.second][0], eout1.second));
                    startDay = task[out2.second][0];
                }else{
                    profit += task[eout1.second][2];
                    startDay += task[eout1.second][2];
                }
            }
            continue;
        }
        startDay = task[out2.second][0];
        if (task[out1.second][1] < task[out2.second][0])
            profit += (long long)task[out1.second][2];
        else if (task[out1.second][0] + task[out1.second][2] - 1 < task[out2.second][0])
            profit += (long long)task[out1.second][2];
        else{
            int available = task[out2.second][0] - task[out1.second][0];
            profit += available;
            task[out1.second][2] -= available;
            task[out1.second][0] = task[out2.second][0];
            eQ.push(make_pair(task[out1.second][1], out1.second));
        }
        
    }*/
    //out1 = sQ.top();
    //profit += task[out1.second][2];
    //cout << "sqsize" << sQ.size() << endl;
    //cout << "eqsize" << eQ.size() << endl;
    
    cout << profit;
    
    
    
    
    return 0;
}
