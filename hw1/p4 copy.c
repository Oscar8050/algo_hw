#include <stdio.h>

void mergeSort(int arr[][2], int l, int r);
void merge(int arr[][2], int l, int m, int r);


int main(){
    
    int T, flag;
    scanf("%d%d", &T, &flag);
    while(T--){
        int N;
        scanf("%d", &N);
        int candies[N];
        for (int i = 0; i < N; i++)
            scanf("%d", &candies[i]);
        int sign = 1;
        int newC[N][2];
        for (int i = 0; i < N; i++){
            newC[i][0] = 0;
            newC[i][1] = 0;
        }
        int k = 0, premax = candies[0], maxi = 0;
        while (candies[k] <= 0 && k < N){
            if (candies[k] > premax){
                premax = candies[k];
                maxi = k;
            }
            k += 1;
        }
        if (k == N){
            printf("%d\n", premax);
            if (flag == 1)
                printf("1 %d\n", maxi+1);
            continue;
        }
        
        int max = 0, add = 0, mi = 0;
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
       /* for (int i = 0; i < add; i++){
            printf("%d ", newC[i][0]);
        }
        printf("\n");*/
        
        
        if (add > 1 && newC[add-1][0] < 0)
            add -= 1;
        /*int del = 0;
        while (del < add && add - del > 1 && newC[del][0] <= 0){
            del += 1;
        }
        add -= del;
        //printf("del=%d add=%d\n", del, add);
        if (del > 0){
            for (int i = 0; i < add; i++){
                //printf("i=%d newC=%d ", i, newC[i+del][0]);
                newC[i][0] = newC[i+del][0];
                newC[i][1] = newC[i+del][1];
            }
        }*/
        /*if (add > 1 && newC[0][0] < 0){
            add -= 1;
            for (int i = 0; i < add; i++){
                newC[i][0] = newC[i+1][0];
                newC[i][1] = newC[i+1][1];
            }
        }*/
        /*for (int i = 0; i < add; i++){
            printf("%d ", newC[i][0]);
        }
        printf("\n");*/
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
        /*for (int i = 0; i < add; i++){
            printf("%d ", newC[i][0]);
        }
        printf("\n");*/
            
        if (add > 1){
            int calc[add-1][2];
            for (int i = 0; i < add-1; i++){
                calc[i][0] = newC[i][0] + newC[i+1][0];
                calc[i][1] = i;
            }
            mergeSort(calc, 0, add-2);
            /*for (int i = 0; i < add-1; i++){
                printf("add=%d pos=%d ", calc[i][0], calc[i][1]);
            }*/
            int pop[add];
            for (int i = 0; i < add; i++)
                pop[i] = 0;
            
            int p = 0;
            
            while (calc[p][0] < 0 && p < add-1){
                if (calc[p][1] == 0 && pop[calc[p][1]+1] == 0)
                    pop[calc[p][1]] = 1;
                else if (pop[calc[p][1]-1] == 0 && pop[calc[p][1]+1] == 0)
                    pop[calc[p][1]] = 1;
                p += 1;
            }
            /*for (int i = 0; i < add; i++){
                printf("pop=%d", pop[i]);
            }*/
            int sum = 0, ri = 0, result[add];
            for (int i = 0; i < add; i++)
                result[i] = 0;
            int f = 0;
            while (f < add){
                if (pop[f] == 0){
                    sum += newC[f][0];
                    result[ri] = newC[f][1];
                    ri += 1;
                }else
                    f += 1;
                f += 1;
            }
            
                
            printf("%d\n", sum);
            
            if (flag == 1){
                printf("%d ", ri);
                for (int i = 0; i < ri; i++){
                    printf("%d", result[i]+1);
                    if (i == ri-1)
                        printf("\n");
                    else
                        printf(" ");
                    
                }
            }
            
        }else if (add == 1){
            printf("%d\n", newC[0][0]);
            if (flag == 1)
                printf("1 %d\n", newC[0][1]+1);
        }
        
        
    }
    
    return 0;
}

void mergeSort(int arr[][2], int l, int r){
    if (r - l == 0)
        return;
    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);
    merge(arr, l, m, r);
    return;
}

void merge(int arr[][2], int l, int m, int r){
    int ls = l, rs = m+1;
    int combine[r - l + 1][2];
    for (int i = 0; i < r-l+1; i++){
        combine[i][0] = 0;
        combine[i][1] = 0;
    }
    int index = 0;
    while (index < r-l+1){
        if (rs > r || ls <= m && arr[ls][0] < arr[rs][0]){
            combine[index][0] = arr[ls][0];
            combine[index][1] = arr[ls][1];
            ls += 1;
            index += 1;
        }else if (ls > m || rs <= r && arr[rs][0] <= arr[ls][0]){
            combine[index][0] = arr[rs][0];
            combine[index][1] = arr[rs][1];
            rs += 1;
            index += 1;
        }
    }
    for (int i = l; i <= r; i++){
        arr[i][0] = combine[i-l][0];
        arr[i][1] = combine[i-l][1];
    }
}

