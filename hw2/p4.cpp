#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
    int indexl, indexr, sum;
};

struct cmp{
    bool operator()(Node a, Node b){
        return a.sum > b.sum;
    }
};

int main() {
    
    int T, flag;
    cin >> T >> flag;
    while(T--) {
        
        int N;
        cin >> N;
        vector <int> ori_candies, sec_candies;
        priority_queue <Node, vector<Node>, cmp> firstCan, secCan;
        int sign = 1;
        int max;
        int input;
        cin >> input;
        if (input > 0)
            sign = 1;
        else
            sign = -1;
        
        max = input;
        
        for (int i = 1; i < N; i++){
            cin >> input;
            if (input * sign < 0){
                ori_candies.push_back(max);
                max = input;
                sign *= -1;
                continue;
            }
            if (input > max)
                max = input;
        }
        ori_candies.push_back(max);
        
        long long table[N];
        for (int i = 0; i < N; i++)
            table[i] = 0;
        
        if (ori_candies.size() == 1){
            table[0] = ori_candies[0];
            cout << table[0];
            for (int i = 1; i < N; i++)
                cout << " " << table[i];
            cout << endl;
            continue;
        }
        
        
        
        
        if (ori_candies[0] > ori_candies[ori_candies.size()-1]){
            sec_candies.assign(ori_candies.begin(), ori_candies.end()-1);
        }else{
            sec_candies.assign(ori_candies.begin()+1, ori_candies.end());
        }
        
        /*for (int i = 0; i < ori_candies.size(); i++){
            cout << ori_candies[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < sec_candies.size(); i++){
            cout << sec_candies[i] << " ";
        }
        cout << endl;*/
        
        Node node;
        for (int i = 0; i < ori_candies.size()-1; i++){
            node.indexl = i;
            node.indexr = i+1;
            node.sum = ori_candies[i] + ori_candies[i+1];
            firstCan.push(node);
        }
        node.indexl = ori_candies.size()-1;
        node.indexr = 0;
        node.sum = ori_candies[0] + ori_candies[ori_candies.size()-1];
        firstCan.push(node);
        for (int i = 0; i < sec_candies.size()-1; i++){
            node.indexl = i;
            node.indexr = i+1;
            node.sum = sec_candies[i] + sec_candies[i+1];
            secCan.push(node);
        }
        node.indexl = sec_candies.size()-1;
        node.indexr = 0;
        node.sum = sec_candies[0] + sec_candies[sec_candies.size()-1];
        secCan.push(node);
        
        
        
        
        long long orisum = 0, secsum = 0;
        for (int i = 0; i < ori_candies.size(); i++){
            orisum += (long long)ori_candies[i];
        }
        //printf("orisum=%lld\n", orisum);
        for (int i = 0; i < sec_candies.size(); i++){
            secsum += (long long)sec_candies[i];
        }
        
        table[ori_candies.size()-1] = orisum;
        table[sec_candies.size()-1] = secsum;
        
        /*for (int i = 0; i < N; i++){
            printf("%d=%lld\n", i, table[i]);
        }*/
        
        int oriIndexL[ori_candies.size()], oriIndexR[ori_candies.size()], secIndexL[sec_candies.size()], secIndexR[sec_candies.size()];
        int orilen = ori_candies.size(), seclen = sec_candies.size();
        
        
        for (int i = 1; i < ori_candies.size()-1; i++){
            oriIndexL[i] = i-1;
            oriIndexR[i] = i+1;
        }
        oriIndexL[0] = orilen-1;
        oriIndexL[orilen-1] = orilen-2;
        oriIndexR[0] = 1;
        oriIndexR[orilen-1] = 0;
        
        
        for (int i = 1; i < sec_candies.size()-1; i++){
            secIndexL[i] = i-1;
            secIndexR[i] = i+1;
        }
        secIndexL[0] = seclen-1;
        secIndexL[seclen-1] = seclen-2;
        secIndexR[0] = 1;
        secIndexR[seclen-1] = 0;
        
        
        /*int oripop[orilen], secpop[seclen];
        for (int i = 0; i < orilen; i++)
            oripop[i] = 0;
        for (int i = 0; i < seclen; i++)
            secpop[i] = 0;*/
        int len = orilen;
        Node newN;
        while (len > 1){
            //cout << "1";
            node = firstCan.top();
            //printf("nodel=%d noder=%d NodeL=%d NodeR=%d nodes=%d\n", node.indexl, node.indexr, oriIndexL[node.indexr], oriIndexR[node.indexl], node.sum);
            firstCan.pop();
            
            if (node.indexl != oriIndexL[node.indexr] || node.indexr != oriIndexR[node.indexl] )
                continue;
            //cout << "suceed" << endl;
            
            orisum -= node.sum;
            len -= 2;
            newN.indexl = oriIndexL[node.indexl];
            newN.indexr = oriIndexR[node.indexr];
            newN.sum = ori_candies[newN.indexl] + ori_candies[newN.indexr];
            firstCan.push(newN);
            oriIndexL[oriIndexR[node.indexr]] = oriIndexL[node.indexl];    //處理corner
            oriIndexR[oriIndexL[node.indexl]] = oriIndexR[node.indexr];
            //oripop[node.index] = 1;
            //oripop[oriIndexR[node.index]] = 1;
            table[len-1] = orisum;
        }
        
        len = seclen;
        while (len > 1){
            //cout << "2";
            node = secCan.top();
            //printf("node=%d\n", node.sum);
            secCan.pop();
            //printf("%d %d %d %d\n", node.index, (node.index+1)%seclen, secpop[node.index], secpop[(node.index+1)%seclen]);
            if (node.indexl != secIndexL[node.indexr] || node.indexr != secIndexR[node.indexl])
                continue;
            secsum -= node.sum;
            len -= 2;
            newN.indexl = secIndexL[node.indexl];
            newN.indexr = secIndexR[node.indexr];
            newN.sum = sec_candies[newN.indexl] + sec_candies[newN.indexr];
            secCan.push(newN);
            secIndexL[secIndexR[node.indexr]] = secIndexL[node.indexl];    //處理corner
            secIndexR[secIndexL[node.indexl]] = secIndexR[node.indexr];
            //secpop[node.index] = 1;
            //secpop[secIndexR[node.index]] = 1;
            //printf("secsum=%lld\n", secsum);
            table[len-1] = secsum;
        }
        
        table[0] = ori_candies[0];
        for(int i = 0; i < orilen; i++){
            if (ori_candies[i] > table[0])
                table[0] = ori_candies[i];
        }
                      
        
        cout << table[0];
        for (int i = 1; i < N; i++)
            cout << " " << table[i];
        cout << endl;
        
        
    }
    
    return 0;
}
