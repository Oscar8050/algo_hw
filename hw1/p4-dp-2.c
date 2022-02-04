#include <stdio.h>

int main(){
    int T, flag;
    scanf("%d%d", &T, &flag);
    while (T--){
        int N;
        scanf("%d", &N);
        int candies[N];
        for (int i = 0; i < N; i++)
            scanf("%d", &candies[i]);
        int zero = 0;
        int sign;
        int newC[N][2];
        for (int i = 0; i < N; i++){
            newC[i][0] = 0;
            newC[i][1] = 0;
        }
        int k = 0;
        while (candies[k] == 0){
            newC[k][0] = 0;
            newC[k][1] = k;
            k += 1;
        }
        if (candies[k] >= 1)
            sign = 1;
        else
            sign = -1;
        
        int max = 0, add = k, mi = 0;
        while (k < N){
            if (candies[k] == 0){
                newC[add][0] = 0;
                newC[add][1] = k;
                k += 1;
                add += 1;
                if (k != N){
                    sign = candies[k] > 0 ? 1 : -1;
                }
                continue;
            }
            if (sign * candies[k] > 0){
                max = candies[k];
                mi = k;
                sign *= -1;
            }else{
                if (candies[k] > max){
                    max = candies[k];
                    mi = k;
                }
                
            }
            k += 1;
            if (k == N || candies[k] * sign >= 0){
                newC[add][0] = max;
                newC[add][1] = mi;
                add += 1;
            }
            
        }
        /*for (int i = 0; i < add; i++){
            printf("%d ", newC[i][0]);
        }
        printf("\n");*/
        
        
        if (add > 1 && newC[add-1][0] < 0)
            add -= 1;
        
        if (add > 1 && newC[0][0] < 0){
            add -= 1;
            for (int i = 0; i < add; i++){
                newC[i][0] = newC[i+1][0];
                newC[i][1] = newC[i+1][1];
            }
        }
        
        int kick[add];
        for (int i = 0; i < add; i++)
            kick[i] = 0;
        for (int i = 1; i < add-1; i++){
            if (newC[i][0] < 0 && (newC[i-1][0] == 0 || newC[i+1][0] == 0))
                kick[i] = 1;
        }
        int rmi = 0;
        for (int i = 0; i < add; i++){
            if (kick[i] == 0){
                newC[rmi][0] = newC[i][0];
                newC[rmi][1] = newC[i][1];
                rmi += 1;
            }
        }
        add = rmi;
        
        long long pm = -2147483648, nm = -2147483648;
        //int pa[N], na[N];
        /*for (int i = 0; i < N; i++){
            pa[i] = 0;
            na[i] = 0;
        }*/
       
        for (int i = 0; i < add; i++){
            if (newC[i][0] == 0){
                zero = 1;
            }else if (newC[i][0] > 0 && zero == 0){
                if (newC[i][0] >= pm && nm <= 0){
                    pm = (long long)newC[i][0];
                }else if (nm >= 0 && nm + newC[i][0] >= pm){
                    pm = (long long)nm + (long long)newC[i][0];
                }
            }else if (newC[i][0] < 0 && zero == 0){
                if (newC[i][0] >= nm && pm <= 0){
                    nm = (long long)newC[i][0];
                }else if (pm >= 0 && pm + newC[i][0] >= nm){
                    nm = (long long)pm + (long long)newC[i][0];
                }
            }else{
                if (newC[i][0] > 0)
                    pm += (long long)newC[i][0];
                zero = 0;
            }
        }
        printf("%lld\n", pm > nm ? pm : nm);
       
            
    }
    
    
    
    return 0;
}
