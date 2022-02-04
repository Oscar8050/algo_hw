#include <iostream>
#include <math.h>

using namespace std;

long long power(int n, int p);

int main(){
    
    int n, n1, n2, n3;
    cin >> n;
    int position[n];
    cin >> n1;
    int rod1[n1];
    for (int i = 0; i < n1; i++){
        cin >> rod1[i];
        position[rod1[i]-1] = 0;
    }
    cin >> n2;
    int rod2[n2];
    for (int i = 0; i < n2; i++){
        cin >> rod2[i];
        position[rod2[i]-1] = 1;
    }
    cin >> n3;
    int rod3[n3];
    for (int i = 0; i < n3; i++){
        cin >> rod3[i];
        position[rod3[i]-1] = 2;
    }
    int step = 0;
    int bad = 1, move = 0, last = 2;
    for (int i = n-1; i >= 0; i--){
        if (position[i] == bad){
            printf("-1\n");
            return 0;
        }
        
        if(move == 0 && position[i] != last){
            step = (power(2, i) + step) % 998244353;
            last = bad;
            move = 1;
        }else if (move == 0 && position[i] == last){
            last = position[i];
            move = 0;
        }else if (move == 1 && position[i] == last){
            last = position[i];
            move = 0;
        }else{
            step = (power(2, i) + step) % 998244353;
            move = 1;
            last = bad;
        }
        
        if ((position[i]+1)%3 == bad)
            bad = (position[i]+2) % 3;
        else
            bad = (position[i]+1) % 3;
                
    }
    
    printf("%d\n", step);
    
    return 0;
}

long long power(int n, int p){
    int times = p / 50;
    int mod = p % 50;
    long long multi = (long long)pow(n, 50) % 998244353;
    long long rs = 1;
    for (int i = 0; i < times; i++){
        rs = (rs * multi) % 998244353;
    }
    rs = (rs * ((long long)pow(n, mod) % 998244353)) % 998244353;
    return rs;
}
