#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

using namespace std;

void findK(int x, int y, int len);
pair<int, long long> **map;
vector<pair<pair<int, long long>, pair<int, int> > > **maps;
int n, m, k;

int main(){
    int T;
    cin >> T;
    while (T--){
        
        cin >> n >> m >> k;
        
        map = new pair<int, long long> *[n];
        for (int i = 0; i < n; i++)
            map[i] = new pair<int, long long> [m];
        maps = new vector<pair<pair<int, long long>, pair<int, int> > > *[n];
        for (int i = 0; i < n; i++)
            maps[i] = new vector<pair<pair<int, long long>, pair<int, int> > > [m];
        
        
        string input;
        
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> input;
                if (input.compare("X") != 0){
                    map[i][j] = make_pair(1, atoll(input.c_str()));
                }else{
                    map[i][j] = make_pair(0, 0);
                }
            }
        }
        
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                findK(i, j, k+1);
            }
        }
        
        int a = n-1, b = m-1, top = maps[0][0].size()-1;
        /*cout << "--------" << endl;
        cout << top << endl;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                printf("(%d %d) (%d %lld %d %d) ", i, j, maps[i][j][top].first.first, maps[i][j][top].first.second, maps[i][j][top].second.first, maps[i][j][top].second.second);
            }
            printf("\n");
        }
        cout << "--------" << endl;
        cout << top-1 << endl;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                printf("(%d %d) (%d %lld %d %d) ", i, j, maps[i][j][top-1].first.first, maps[i][j][top-1].first.second, maps[i][j][top-1].second.first, maps[i][j][top-1].second.second);
            }
            printf("\n");
        }
        cout << "--------" << endl;*/
        /*cout << top-2 << endl;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                printf("(%d %d) (%d %lld %d %d) ", i, j, maps[i][j][top-2].first.first, maps[i][j][top-2].first.second, maps[i][j][top-2].second.first, maps[i][j][top-2].second.second);
            }
            printf("\n");
        }
        cout << "--------" << endl;*/
        if (maps[a][b][top].first.first == 1){
            printf("Passable\n");
            printf("%lld\n", maps[a][b][top].first.second);
            vector <pair<int, int> > path;
            while (a != 0 || b != 0){
                //printf("%d %d\n", a, b);
                path.push_back(make_pair(a+1, b+1));
                int na, nb;
                na = maps[a][b][top].second.first;
                nb = maps[a][b][top].second.second;
                a = na;
                b = nb;
            }
            path.push_back(make_pair(1, 1));
            printf("%lu\n", path.size());
            for (int i = path.size()-1; i >= 0; i--)
                cout << path[i].first << " " << path[i].second << endl;
        }else{
            printf("Impassable\n");
        }
        
    }
    
    return 0;
}

void findK(int x, int y, int len){
    long long max = LONG_MIN;
    int pos[2];
    int flag = 0;
    int level = 0;
    int top = maps[0][0].size()-1;
    if (len == 2){
        if (x == 0 && y == 0){
            maps[x][y].push_back(make_pair(make_pair(1, map[x][y].second), make_pair(0, 0)));
            return;
        }
        /*if (x-1 >= 0 && maps[x-1][y][level].first.first == 1 && maps[x-1][y][level].first.second >= max){
            max = maps[x-1][y][level].first.second;
            pos[0] = x-1;
            pos[1] = y;
            flag = 1;
        }
        if (y-1 >= 0 && maps[x][y-1][level].first.first == 1 && maps[x][y-1][level].first.second >= max){
            max = maps[x][y-1][level].first.second;
            pos[0] = x;
            pos[1] = y-1;
            flag = 1;
        }*/
        
        if (x-1 >= 0 && maps[x-1][y][top].first.first == 1 && maps[x-1][y][top].first.second >= max){
            max = maps[x-1][y][top].first.second;
            pos[0] = x-1;
            pos[1] = y;
            flag = 1;
        }
        
        if (y-1 >= 0 && maps[x][y-1][top].first.first == 1 && maps[x][y-1][top].first.second >= max){
            max = maps[x][y-1][top].first.second;
            pos[0] = x;
            pos[1] = y-1;
            flag = 1;
        }
        
        if (flag == 1){
            max += map[x][y].second;
            if (map[x][y].first == 1)
                maps[x][y].push_back(make_pair(make_pair(1, max), make_pair(pos[0], pos[1])));
            else
                maps[x][y].push_back(make_pair(make_pair(0, max), make_pair(pos[0], pos[1])));
                
        }else{
            if (map[x][y].first == 1)
                maps[x][y].push_back(make_pair(make_pair(2, 0), make_pair(0, 0)));
            else
                maps[x][y].push_back(make_pair(make_pair(-1, 0), make_pair(0, 0)));
        }
        
        return;
    }
    int smaller = ceil(len*2.0/3.0);
    findK(x, y, smaller);
    int diff = len - smaller;
    level = maps[x][y].size()-1;
    
    /*if (x == 3 && y == 2){
        printf("here level=%d diff=%d\n", level, diff);
    }*/
    
    if (x == 0 && y == 0){
        maps[x][y].push_back(make_pair(make_pair(1, map[x][y].second), make_pair(0, 0)));
        return;
    }
    
    if ((maps[x][y][level].first.first == 0 || maps[x][y][level].first.first == 1) && maps[x][y][level].first.second >= max){
        int lastx = maps[x][y][level].second.first, lasty = maps[x][y][level].second.second;
        if (maps[lastx][lasty][top].first.second >= max){
            max = maps[lastx][lasty][top].first.second;
            pos[0] = lastx;
            pos[1] = lasty;
            flag = 1;
        }
        /*if (x == 3 && y == 2){
            printf("in1\n");
        }*/
    }
    
    if (x-diff >= 0 && (maps[x-diff][y][level].first.first == 0 || maps[x-diff][y][level].first.first == 1)){
        int lastx = maps[x-diff][y][level].second.first, lasty = maps[x-diff][y][level].second.second;
        if (maps[lastx][lasty][top].first.second >= max){
            max = maps[lastx][lasty][top].first.second;
            pos[0] = lastx;
            pos[1] = lasty;
            flag = 1;
        }
        /*if (x == 3 && y == 2){
            printf("in2 first=%d\n", maps[x-diff][y][level].first.first);
            printf("x=%d y=%d\n", x-diff, y);
        }*/
        
    }
    
    if (y-diff >= 0 && (maps[x][y-diff][level].first.first == 0 || maps[x][y-diff][level].first.first == 1)){
        int lastx = maps[x][y-diff][level].second.first, lasty = maps[x][y-diff][level].second.second;
        //printf("diff=%d levelll=%d %d\n", diff, maps[x][y-diff][level].second.first, maps[x][y-diff][level].second.second);
        if (maps[lastx][lasty][top].first.second >= max){
            max = maps[lastx][lasty][top].first.second;
            pos[0] = lastx;
            pos[1] = lasty;
            flag = 1;
            
        }
        /*if (x == 3 && y == 2){
            printf("in3\n");
        }*/
        
    }
    
    
    
    if (x-diff >= 0 && maps[x-diff][y][top].first.first == 1){
        if (maps[x-diff][y][top].first.second >= max){
            max = maps[x-diff][y][top].first.second;
            pos[0] = x-diff;
            pos[1] = y;
            flag = 1;
        }
        /*if (x == 3 && y == 2){
            printf("in4 x=%d y=%d flag=%d\n", x-diff, y, flag);
        }*/
    }
    
    if (y-diff >= 0 && maps[x][y-diff][top].first.first == 1){
        if (maps[x][y-diff][top].first.second >= max){
            max = maps[x][y-diff][top].first.second;
            pos[0] = x;
            pos[1] = y-diff;
            flag = 1;
        }
        /*if (x == 3 && y == 2){
            printf("in5\n");
        }*/
    }
    
    if (flag == 1){
        if (maps[x][y][level].first.first == 2 || maps[x][y][level].first.first == 1){
            max += map[x][y].second;
            maps[x][y].push_back(make_pair(make_pair(1, max), make_pair(pos[0], pos[1])));
            
        }else{
            maps[x][y].push_back(make_pair(make_pair(0, max), make_pair(pos[0], pos[1])));
            
        }
    }else{
        if (maps[x][y][level].first.first == 2 || maps[x][y][level].first.first == 1){
            maps[x][y].push_back(make_pair(make_pair(2, 0), make_pair(0, 0)));
        }else{
            maps[x][y].push_back(make_pair(make_pair(-1, 0), make_pair(0, 0)));
        }
    }
    
    return;
}
