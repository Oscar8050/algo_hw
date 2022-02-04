#include <stdio.h>

int x, y, z;

void MS(int A[], int i, int j, long long arr[]);
void MCS(int A[], int i, int k, int j, long long arr[]);

int main(){
    
    int N;
    scanf("%d%d%d%d ", &N, &x, &y, &z);
    //printf("%d %d %d %d", N, x, y, z);
    
    int bar[N];
    
    for (int k = 0; k < N; k++){
        scanf("%d", &bar[k]);
    }
    
    long long arr[4];
    MS(bar, 0, N-1, arr);
    
    printf("%lld", arr[2]);
    //printf("\nl = %d r = %d", arr[0], arr[1]);
    
    
    
    
    
    return 0;
}

void MS(int A[], int i, int j, long long arr[]){
    
    if (j - i == 0){
        arr[0] = i;
        arr[1] = j;
        arr[2] = 0;
        arr[3] = 1;
        return;
    }else if(j - i == 1){
        arr[0] = i;
        arr[1] = j;
        arr[2] = (long long)A[i] * x + (long long)A[j] * z;
        arr[3] = 0;
        return;
    }
    
    int k = (i + j) / 2;
    long long larr[4], rarr[4], marr[4];
    MS(A, i, k, larr);
    MS(A, k+1, j, rarr);
    MCS(A, i, k, j, marr);
    
    if (larr[3] != 1 && (rarr[3] == 1 || larr[2] >= rarr[2]) && larr[2] >= marr[2]){
        arr[0] = larr[0];
        arr[1] = larr[1];
        arr[2] = larr[2];
        arr[3] = 0;
    }else if (rarr[3] != 1 && (larr[3] == 1 || rarr[2] >= larr[2]) && rarr[2] >= marr[2]){
        arr[0] = rarr[0];
        arr[1] = rarr[1];
        arr[2] = rarr[2];
        arr[3] = 0;
    }else{
        arr[0] = marr[0];
        arr[1] = marr[1];
        arr[2] = marr[2];
        arr[3] = 0;
    }
    //printf("arr[2] = %d\n", arr[2]);
    return;
}

void MCS(int A[], int i, int k, int j, long long arr[]){
    long long sum = 0;
    long long leftsum = -9223372036854775808;
    int ml;
    for (int w = k; w >= i; w--){
        sum += (long long)A[w] * x;
        if (w != k){
            sum += (long long)A[w+1] * y - (long long)A[w+1] * x;
        }
        
        if (sum > leftsum){
            leftsum = sum;
            ml = w;
        }
    }
    
    sum = 0;
    long long rightsum = -9223372036854775808;
    int mr;
    for (int w = k+1; w <= j; w++){
        sum += (long long)A[w] * z;
        if (w != k+1){
            sum += (long long)A[w-1] * y - (long long)A[w-1] * z;
        }
        
        if (sum > rightsum){
            rightsum = sum;
            mr = w;
        }
        
    }
    
    arr[0] = ml;
    arr[1] = mr;
    arr[2] = leftsum + rightsum;
    arr[3] = 0;
    
    return;
}



