#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <utility>
#include <limits>
#include <limits.h>
#include <climits>
using namespace std;

void divide(int n, int m, int len);
pair<pair<int, long long>, pair<int, int> > **map;

int main(){
    int T;
    cin >> T;
    while (T--){
        int n, m, k;
        cin >> n >> m >> k;
        //string str_map[n][m];
        //long long map[n][m];
        //pair<pair<int, long long>, pair<int, int> > map[n][m];
        map = new pair<pair<int, long long>, pair<int, int> > *[n];
        for (int i = 0; i < n; i++)
            map[i] = new pair<pair<int, long long>, pair<int, int> > [m];
        cout << LONG_MIN << endl;
        //cout << LONG_MAX << endl;
        string input;
        
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> input;
                if (input.compare("X") != 0)
                    map[i][j].first = make_pair(1, atoll(input.c_str()));
                else
                    map[i][j].first = (make_pair(0, 0));
            }
        }
        
        
        
        
        long long max = LONG_MIN;
        int max_bool = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                max = LONG_MIN;
                max_bool = 0;
                if (i == 0 && j == 0)
                    continue;
                //if (map[i][j].first.first == 0)
                    //continue;
                if (i-1 >= 0 && map[i-1][j].first.first == 1 && map[i-1][j].first.second >= max){
                    max = map[i-1][j].first.second;
                    map[i][j].second = make_pair(i-1, j);
                    max_bool = 1;
                }
                if (j-1 >= 0 && map[i][j-1].first.first == 1 && map[i][j-1].first.second >= max){
                    max = map[i][j-1].first.second;
                    map[i][j].second = make_pair(i, j-1);
                    max_bool = 1;
                }
                
                if (max_bool == 0 && map[i][j].first.first == 1){
                    map[i][j].first.first = 2;
                }else if (max_bool == 0 && map[i][j].first.first == 0){
                    map[i][j].first.first = -1;
                }else{
                    map[i][j].first.second += max;
                }
            }
        }
        /*cout << "------------" << endl;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                printf("(%d %d) ", i, j);
                printf("(%d %lld %d %d) ", map[i][j].first.first, map[i][j].first.second, map[i][j].second.first, map[i][j].second.second);
            }
            printf("\n");
        }*/
        //cout << "------------" << endl;
        //printf("%p\n", map);
        divide(n, m, k+1);
        
        /*for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                printf("(%d %d) ", i, j);
                printf("(%d %lld %d %d) ", map[i][j].first.first, map[i][j].first.second, map[i][j].second.first, map[i][j].second.second);
            }
            printf("\n");
        }*/
        
        
        
        if (map[n-1][m-1].first.first != 1){
            printf("Impassable\n");
        }else{
            printf("Passable\n");
            printf("%lld\n", map[n-1][m-1].first.second);
            int a = n-1, b = m-1;
            vector <pair<int, int> > path;
            while(a != 0 || b != 0){
                path.push_back(make_pair(a+1, b+1));
                //printf("%d %d\n", a+1, b+1);
                int ni, nj;
                ni = map[a][b].second.first;
                nj = map[a][b].second.second;
                a = ni;
                b = nj;
            }
            path.push_back(make_pair(1, 1));
            printf("%lu\n", path.size());
            for (int i = path.size()-1; i >= 0; i--){
                cout << path[i].first << " " << path[i].second << endl;
            }
        }
        
    }
    
    
    /*string str = "1234";
    int convert = atoll(str.c_str());
    printf("%d\n", convert);
                
    char str2[10] = "32223";
    int von = atoi(str2);
    printf("%d", von);*/
    
    
                

    
    //string in1, in2;
    //cin >> in1 >> in2;
    //cout << in1 << endl << in2 << endl;
    //long int i = atol("134567893928");
    //cout << i;
    
    return 0;
    

    
}

void divide(int n, int m, int len){
    if (len == 2)
        return;
    int smaller = ceil(len*2.0/3.0);
    int diff = len - smaller;
    divide(n, m, smaller);
    pair<pair<int, long long>, pair<int, int> > oldmap[n][m];
    //memcpy(oldmap, map, sizeof (pair<pair<int, long long>, pair<int, int> >)*n*m);
    
    
    /*for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("(%d %d) ", i, j);
            printf("(%d %lld %d %d) ", oldmap[i][j].first.first, oldmap[i][j].first.second, oldmap[i][j].second.first, oldmap[i][j].second.second);
        }
        printf("\n");
    }
    cout << "------------" << endl;*/
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            oldmap[i][j].first.first = map[i][j].first.first;
            oldmap[i][j].first.second = map[i][j].first.second;
            oldmap[i][j].second.first = map[i][j].second.first;
            oldmap[i][j].second.second = map[i][j].second.second;
            long long max = LONG_MIN;
            int flag = 0;
            int x, y;
            
            
            if (oldmap[i][j].first.first == 0 || oldmap[i][j].first.first == 1){
                int lasti = oldmap[i][j].second.first, lastj = oldmap[i][j].second.second;
                if (oldmap[lasti][lastj].first.second >= max){
                    max = oldmap[lasti][lastj].first.second;
                    x = lasti;
                    y = lastj;
                    flag = 1;
                }
               
            }
            if (i-diff >= 0 && (oldmap[i-diff][j].first.first == 0 || oldmap[i-diff][j].first.first == 1)){
                int lasti = oldmap[i-diff][j].second.first, lastj = oldmap[i-diff][j].second.second;
                if (oldmap[lasti][lastj].first.second >= max){
                    max = oldmap[lasti][lastj].first.second;
                    x = lasti;
                    y = lastj;
                    flag = 1;
                }
            }
            if (j-diff >= 0 && (oldmap[i][j-diff].first.first == 0 || oldmap[i][j-diff].first.first == 1)){
                int lasti = oldmap[i][j-diff].second.first, lastj = oldmap[i][j-diff].second.second;
                if (oldmap[lasti][lastj].first.second >= max){
                    max = oldmap[lasti][lastj].first.second;
                    x = lasti;
                    y = lastj;
                    flag = 1;
                }
            }
            
            if (i-diff >= 0 && (map[i-diff][j].first.first == 1)){
                if (map[i-diff][j].first.second >= max){
                    max = map[i-diff][j].first.second;
                    x = i-diff;
                    y = j;
                    flag = 1;
                }
            }
            
            if (j-diff >= 0 && (map[i][j-diff].first.first == 1)){
                if (map[i][j-diff].first.second >= max){
                    max = map[i][j-diff].first.second;
                    x = i;
                    y = j-diff;
                    flag = 1;
                }
            }
            
            if (flag == 1){
                if (map[i][j].first.first == -1){
                    map[i][j].first.first = 0;
                    map[i][j].first.second = max;     //be careful!
                }else if (map[i][j].first.first == 2){
                    map[i][j].first.first = 1;
                    map[i][j].first.second += max;     //be careful!
                }else if (map[i][j].first.first == 0){
                    map[i][j].first.second = max;
                }else if (map[i][j].first.first == 1){
                    int lasti = oldmap[i][j].second.first, lastj = oldmap[i][j].second.second;
                    map[i][j].first.second -= oldmap[lasti][lastj].first.second;
                    map[i][j].first.second += max;
                }
                map[i][j].second.first = x;
                map[i][j].second.second = y;
            }
            
        }
    }
    
    return;
}
