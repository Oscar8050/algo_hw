#include <stdio.h>

void mergeSort(int carr[], int arr[], int l, int r, int o);
void merge(int carr[], int arr[], int l, int m, int r);
void count(int carr[], int arr[], int l, int m, int r);
void repeat(int carr[], int arr[], int size);
void minus(int arr[], int l, int r);

int a, b, c;
long long d;

int main(){
    
    int N;
    scanf("%d%d%d%d", &N, &a, &b, &c);
    int p[N];
    int z[N];
    for (int i = 0; i < N; i++){
        scanf("%d%d", &p[i], &z[i]);
    }
    d = 0;
    mergeSort(z, p, 0, N-1, 0);
    repeat(z, p, N);
    mergeSort(p, z, 0, N-1, 1);
    /*for (int i = 0; i < N; i++){
        printf("z=%d ", z[i]);
    }
    for (int i = 0; i < N; i++){
        printf("p=%d ", p[i]);
    }*/
    printf("%lld", d);
    
    return 0;
}

void mergeSort(int carr[], int arr[], int l, int r, int o){
    //printf("%d\n", r - l);
    if (r - l == 0)
        return;
    int m = (r + l) / 2;
    mergeSort(carr, arr, l, m, o);
    mergeSort(carr, arr, m+1, r, o);
    
    if (o == 1)
        count(carr, arr, l, m, r);
    merge(carr, arr, l, m, r);
    return;
}

void merge(int carr[], int arr[], int l, int m, int r){
    int combine[r - l + 1][2];
    int ls = l, rs = m + 1, index = 0;
    while (index < r - l + 1){
        if (rs > r || (ls <= m && carr[ls] < carr[rs])){
            combine[index][0] = carr[ls];
            combine[index][1] = arr[ls];
            ls += 1;
            index += 1;
        }else if (ls > m || (rs <= r && carr[rs] < carr[ls])){
            combine[index][0] = carr[rs];
            combine[index][1] = arr[rs];
            rs += 1;
            index += 1;
        }else{
            if (arr[ls] < arr[rs]){
                combine[index][0] = carr[ls];
                combine[index][1] = arr[ls];
                ls += 1;
                index += 1;
            }else{
                combine[index][0] = carr[rs];
                combine[index][1] = arr[rs];
                rs += 1;
                index += 1;
            }
        }
    }
    for (int i = l; i <= r; i++){
        carr[i] = combine[i-l][0];
        arr[i] = combine[i-l][1];
    }
    return;
}

void count(int carr[], int arr[], int l, int m, int r){
    //printf("\nl=%d m=%d r=%d\n", l, m, r);
    long long left, right;
    int ls = l, rs = m + 1;
    while (ls <= m && rs <= r){
        left = (long long)carr[ls] * b + (long long)c;
        right = (long long)carr[rs] * a;
        if (right > left){
            //printf("\nls=%d\n", ls);
            d += r - rs + 1;
            ls += 1;
        }else{
            //printf("\nrs=%d\n", rs);
            rs += 1;
        }
    }
    return;
}

void repeat(int carr[], int arr[], int size){
    int l = 0, r = 1;
    while (r < size){
        if (carr[l] != carr[r] && r-l == 1){
            l += 1;
            r += 1;
        }else if (carr[l] == carr[r]){
            r += 1;
            if (r == size)
                minus(arr, l, r-1);
        }else{
            minus(arr, l, r-1);
            l = r;
            r += 1;
        }
    }
    return;
}

void minus(int arr[], int l, int r){
    
    if(r - l == 0)
        return;
    int m = (r + l) / 2;
    minus(arr, l, m);
    minus(arr, m+1, r);
    int ls = l, rs = m + 1;
    while (ls <= m && rs <= r){
        if ((long long)arr[rs] * a > (long long)arr[ls] * b + c){
            d -= r - rs + 1;
            ls += 1;
        }else{
            rs += 1;
        }
    }
    
    /*for (int i = l+1; i <= r; i++){
        for (int j = l; j < i; j++){
            if ((long long)arr[i] * a > (long long)arr[j] * b + c)
                d -= 1;
        }
    }*/
    
    return;
}
