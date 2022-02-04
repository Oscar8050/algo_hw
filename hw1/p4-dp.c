#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

int main(){
    int T, flag;
    scanf("%d%d", &T, &flag);
    while (T--){
        int N;
        scanf("%d", &N);
        int candies[N];
        for (int i = 0; i < N; i++)
            scanf("%d", &candies[i]);
        long long pm = -2147483648, nm = -2147483648;
        
        vector<int> pa;
        vector<int> na;
        
        for (int i = 0; i < N; i++){
            if (candies[i] > 0){
                if (candies[i] >= pm && nm <= 0){
                    pm = (long long)candies[i];
                    pa.clear();
                    pa.push_back(i);
                    
                }else if (nm >= 0 && nm + candies[i] >= pm){
                    pm = (long long)nm + (long long)candies[i];
                    pa.clear();
                    pa.assign(na.begin(), na.end());
                    pa.push_back(i);
                    
                }
            }else if (candies[i] <= 0){
                if (candies[i] >= nm && pm <= 0){
                    nm = (long long)candies[i];
                    na.clear();
                    na.push_back(i);
                    
                }else if (pm >= 0 && pm + candies[i] >= nm){
                    nm = (long long)pm + (long long)candies[i];
                    na.clear();
                    na.assign(pa.begin(), pa.end());
                    na.push_back(i);
                }
            }
            
                   
        }
        printf("%lld\n", pm > nm ? pm : nm);
        if (flag == 1){
            if (pm > nm){
                cout << pa.size() << " ";
                for (int i = 0; i < pa.size(); i++){
                    cout << pa[i]+1;
                    if (i == pa.size()-1)
                        cout << endl;
                    else
                        cout << " ";
                }
            }else{
                cout << na.size() << " ";
                for (int i = 0; i < na.size(); i++){
                    cout << na[i]+1;
                    if (i == na.size()-1)
                        cout << endl;
                    else
                        cout << " ";
                }
            }

        }
    }
    
    
    
    return 0;
}
