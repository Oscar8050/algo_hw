#include <stdio.h>

void MS(int A[][2], int l, int r, int arr[], long long rc[]);
void merge(int A[][2], int larr[], long long lrc[], int rarr[], long long rrc[], int marr[], long long mrc[]);

int main(){
    int T, flag;
    scanf("%d%d", &T, &flag);
    while (T--){
        int N;
        scanf("%d", &N);
        int candies[N][2];
        for (int i = 0; i < N; i++){
            scanf("%d", &candies[i][0]);
            candies[i][1] = i;
        }
        int result[N];
        for (int i = 0; i < N; i++)
            result[i] = -1;
        long long allrc[4];
        for (int i = 0; i < 4; i++)
            allrc[i] = (long long)0;
        MS(candies, 0, N-1, result, allrc);
        long long sum = 0;
        for (int i = 0; i < allrc[3]; i++){
            sum += (long long)candies[result[i]][0];
        }
        printf("%lld\n", sum);
        //printf("%lld\n", allrc[2]);
        if (flag == 1){
            printf("%lld ", allrc[3]);
            for (int i = 0; i < allrc[3]; i++){
                printf("%d", result[i]+1);
                if (i != allrc[3]-1)
                    printf(" ");
                else
                    printf("\n");
            }
        }
        
    }
}

void MS(int A[][2], int l, int r, int arr[], long long rc[]){
    if (l == r){
        arr[0] = l;         //max subarray
        rc[0] = -1;         //largest left number <= 0 (index)
        rc[1] = -1;         //latgest right number <= 0 (index)
        rc[2] = (long long)A[l][0];    //sum
        rc[3] = 1;          //arr number
        return;
    }
    
    int m = (l + r) / 2;
    //printf("l=%d m=%d r=%d \n", l, m, r);
    int larr[m-l+1], rarr[r-m], marr[r-l+1];
    for (int i = 0; i < m-l+1; i++)
        larr[i] = -1;
    for (int i = 0; i < r-m; i++)
        rarr[i] = -1;
    for (int i = 0; i < r-l+1; i++)
        marr[i] = -1;
    long long lrc[4], rrc[4], mrc[4];
    for (int i = 0; i < 4; i++){
        lrc[i] = (long long)0;
        rrc[i] = (long long)0;
        mrc[i] = (long long)0;
    }
    MS(A, l, m, larr, lrc);
    MS(A, m+1, r, rarr, rrc);
    merge(A, larr, lrc, rarr, rrc, marr, mrc);
    /*for (int i = 0; i < lrc[3]; i++)
        printf("%d ", larr[i]);
    printf("\n");
    for (int i = 0; i < mrc[3]; i++)
        printf("%d ", marr[i]);
    printf("\n");
    for (int i = 0; i < rrc[3]; i++)
        printf("%d ", rarr[i]);
    printf("\n");
    printf("-------\n");*/
    if (lrc[2] >= mrc[2] && lrc[2] >= rrc[2]){
        for (int i = 0; i < lrc[3]; i++)
            arr[i] = larr[i];
        rc[0] = lrc[0];
        rc[1] = lrc[1];
        rc[2] = lrc[2];
        rc[3] = lrc[3];
        for (int i = m+1; i <= r; i++){
            if (A[i][0] <= 0 && (rc[1] == -1 || A[i][0] > A[rc[1]][0]))
                rc[1] = i;
        }
    }else if (rrc[2] >= mrc[2] && rrc[2] >= lrc[2]){
        for (int i = 0; i < rrc[3]; i++)
            arr[i] = rarr[i];
        rc[0] = rrc[0];
        rc[1] = rrc[1];
        rc[2] = rrc[2];
        rc[3] = rrc[3];
        for (int i = l; i <= m; i++){
            if (A[i][0] <= 0 && (rc[0] == -1 || A[i][0] > A[rc[0]][0]))
                rc[0] = i;
        }
    }else{
        for (int i = 0; i < mrc[3]; i++)
            arr[i] = marr[i];
        rc[0] = mrc[0];
        rc[1] = mrc[1];
        rc[2] = mrc[2];
        rc[3] = mrc[3];
    }
    return;
}

void merge(int A[][2], int larr[], long long lrc[], int rarr[], long long rrc[], int marr[], long long mrc[]){
    if (A[larr[lrc[3]-1]][0] * A[rarr[0]][0] <= 0){
        //printf("111\n");
        for (int i = 0; i < lrc[3]; i++)
            marr[i] = larr[i];
        int k = lrc[3];
        for (int i = 0; i < rrc[3]; i++)
            marr[k+i] = rarr[i];
        mrc[0] = lrc[0];
        mrc[1] = rrc[1];
        mrc[2] = lrc[2] + rrc[2];
        mrc[3] = lrc[3] + rrc[3];
    }else if (lrc[1] + rrc[0] == -2 || A[larr[lrc[3]-1]][0] < 0 && A[rarr[0]][0] < 0){
        //printf("222\n");
        mrc[0] = lrc[0];
        mrc[1] = rrc[1];
        mrc[2] = lrc[2] + rrc[2];
        mrc[3] = lrc[3] + rrc[3] - 1;
        for (int i = 0; i < lrc[3]-1; i++)
            marr[i] = larr[i];
        int k = lrc[3];
        if (A[larr[k-1]][0] > A[rarr[0]][0]){
            marr[k-1] = larr[k-1];
            mrc[2] -= A[rarr[0]][0];
        }else{
            marr[k-1] = rarr[0];
            mrc[2] -= A[larr[k-1]][0];
        }
        for (int i = 1; i < rrc[3]; i++)
            marr[k+i-1] = rarr[i];
    }else if (lrc[1] != -1 && rrc[0] != -1){
        //printf("333\n");
        mrc[0] = lrc[0];
        mrc[1] = rrc[1];
        mrc[2] = lrc[2] + rrc[2];
        mrc[3] = lrc[3] + rrc[3] + 1;
        for (int i = 0; i < lrc[3]; i++)
            marr[i] = larr[i];
        int k = lrc[3];
        if (A[lrc[1]][0] > A[rrc[0]][0]){
            marr[k] = lrc[1];
            mrc[2] += A[lrc[1]][0];
        }else{
            marr[k] = rrc[0];
            mrc[2] += A[rrc[0]][0];
        }
        k += 1;
        for (int i = 0; i < rrc[3]; i++)
            marr[k+i] = rarr[i];
    }else{
        //printf("444\n");
        mrc[0] = lrc[0];
        mrc[1] = rrc[1];
        mrc[2] = lrc[2] + rrc[2];
        mrc[3] = lrc[3] + rrc[3] + 1;
        for (int i = 0; i < lrc[3]; i++)
            marr[i] = larr[i];
        int k = lrc[3];
        if (lrc[1] != -1){
            marr[k] = lrc[1];
            mrc[2] += A[lrc[1]][0];
        }else{
            marr[k] = rrc[0];
            mrc[2] += A[rrc[0]][0];
        }
        k += 1;
        for (int i = 0; i < rrc[3]; i++)
            marr[k+i] = rarr[i];
    }
    return;
}
