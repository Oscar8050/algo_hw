#include <iostream>

using namespace std;
typedef long long l;

l gcd(l a, l b){
    if (b==0)
        return a;
    return gcd(b, a%b);
}

int main() {
    int N;
    cin >> N;
    l A[N];
    for (int i = 0; i < N; i++)
        cin >> A[i];
    l comb[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < i; j++){
            l c = gcd(A[i], A[j]);
            comb[i][j] = c;
            comb[j][i] = c;
        }
    }
    l dp[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            dp[i][j] = 1;
        }
    }
    for (int j = 1; j < N; j++){
        for (int i = j-1; i >= 0; i--){
            if (j-i == 1){
                dp[i][j] = comb[i][j];
                continue;
            }else if (j-i == 2){
                if (dp[i][j-1] != 1 && dp[i+1][j] != 1 && comb[i][j] != 1)
                    dp[i][j] = dp[i][j-1] + dp[i+1][j];
                else
                    dp[i][j] = 1;
                continue;
            }
            
            dp[i][j] = 1;
            int m = i+1;
            while (m+1 < j){
                if (dp[i][m] > 1 && dp[m+1][j] > 1){
                    if (dp[i][m] + dp[m+1][j] > dp[i][j])
                        dp[i][j] = dp[i][m] + dp[m+1][j];
                    //cout << i << j << endl;
                }
                m += 1;
            }
            if (dp[i+1][j-1] > 1 && comb[i][j] > 1){
                //cout << "111" << endl;
                //cout << dp[i][j-1] << " " << comb[i][j] << endl;
                if (dp[i+1][j-1] + comb[i][j] > dp[i][j])
                    dp[i][j] = dp[i+1][j-1] + comb[i][j];
            }
            m = i + 3;
            while (m + 2 < j){
                if (dp[i+1][m-1] > 1 && dp[m+1][j-1] > 1 && comb[i][m] > 1 && comb[m][j] > 1 && comb[i][j] > 1){
                    if (dp[i+1][m-1] + dp[m+1][j-1] + comb[i][m] + comb[m][j] > dp[i][j])
                        dp[i][j] = dp[i+1][m-1] + dp[m+1][j-1] + comb[i][m] + comb[m][j];
                    //cout << i << j << endl;
                }
                m += 1;
            }
            if (dp[i+2][j-1] > 1 && comb[i][i+1] > 1 && comb[i+1][j] > 1 && comb[i][j] > 1){
                if (dp[i+2][j-1] + comb[i][i+1] + comb[i+1][j] > dp[i][j])
                    dp[i][j] = dp[i+2][j-1] + comb[i][i+1] + comb[i+1][j];
                //cout << i << j << endl;
            }
            if (dp[i+1][j-2] > 1 && comb[i][j-1] > 1 && comb[j-1][j] > 1 && comb[i][j] > 1){
                if (dp[i+1][j-2] + comb[i][j-1] + comb[j-1][j] > dp[i][j])
                    dp[i][j] = dp[i+1][j-2] + comb[i][j-1] + comb[j-1][j];
                //cout << i << j << endl;
            }
                
        }
    }
    
    if (dp[0][N-1] == 1)
        cout << -1;
    else
        cout << dp[0][N-1];
    
}
