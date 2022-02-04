#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int sum = 0;

bool compareX(pair<int, int> a, pair<int, int> b){
    return a.first < b.first;
}

void cut(vector<pair<int, int> > &part, int l, int r);
void countFT(vector<pair<int, int> > part, int l, int m, int r);
void countFB(vector<pair<int, int> > part, int l, int m, int r);
void merge(vector<pair<int, int> > &part, int l, int m, int r);

int main(){
    int N;
    cin >> N;
    vector<pair<int, int> > position;
    int x, y;
    for (int i = 0; i < N; i++){
        cin >> x >> y;
        position.push_back(make_pair(x, y));
    }
    
    sort(position.begin(), position.end(), compareX);
    cut(position, 0, position.size()-1);
    
    
    /*for (int i = 0; i < N; i++){
        cout << position[i].first << " "<< position[i].second << endl;
    }*/
    
    cout << sum;
    return 0;
}

void cut(vector<pair<int, int> > &part, int l, int r){
    if (l == r)
        return;
    //printf("l=%d r=%d\n", l, r);
    int m = (l + r) / 2;
    cut(part, l, m);
    cut(part, m+1, r);
    countFT(part, l, m, r);
    countFB(part, l, m, r);
    merge(part, l, m, r);
    /*for (int i = l; i <= r; i++){
        printf("x=%d y=%d sum=%d\n", part[i].first, part[i].second, sum);
    }*/
    
    return;
}

void countFT(vector<pair<int, int> > part, int l, int m, int r){
    vector<pair<int, int> > left, right;
    vector<int> rightX, rightY;
    //printf("countFT l=%d m=%d r=%d\n", l, m, r);
    int ls = 0, rs = 0, ri = m+1;
    for (int i = l; i <= m; i++){
        
        while (ls != 0 && part[i].first > left[ls-1].first){
            left.pop_back();
            ls -= 1;
        }
        
        while (ri <= r && part[ri].second > part[i].second){
            while (rs != 0 && part[ri].first < rightX[rs-1]){
                rightX.pop_back();
                rightY.pop_back();
                rs -= 1;
            }
            rightX.push_back(part[ri].first);
            rightY.push_back(part[ri].second);
            rs += 1;
            ri += 1;
        }
        if (ls == 0 || rs == 0)
            sum += rs;
        else{
            /*int lb = 0, rb = rs - 1; //-1
            int m = (lb + rb) / 2;
            if (right[rs-1].second > left[ls-1].second){
                m = rs - 1;
            }else if(right[0].second < left[ls-1].second){
                m = 0 - 1;
            }else{
                while(!(right[m].second > left[ls-1].second && right[m+1].second < left[ls-1].second)){
                    if (right[m].second < left[ls-1].second){
                        rb = m;
                        m = (lb + rb) / 2;
                    }else{
                        lb = m+1;   //m or m+1?
                        m = (lb + rb) / 2;
                    }
                }
            }*/
            
            vector<int>::iterator low;
            low = lower_bound(rightY.begin(), rightY.end(), left[ls-1].second);
            
            
            sum += low - rightY.begin();     //right[0] < left[ls-1]怎麼辦
        }
        left.push_back(part[i]);
        ls += 1;
        //printf("FT sum=%d\n", sum);
    }
    
    return;
}

void countFB(vector<pair<int, int> > part, int l, int m, int r){
    vector<pair<int, int> > left, right;
    vector<int> rightX, rightY;
    /*printf("countFB l=%d m=%d r=%d\n", l, m, r);
    for (int i = l; i <= r; i++){
        printf("x=%d y=%d\n", part[i].first, part[i].second);
    }*/
    int ls = 0, rs = 0, ri = r;
    for (int i = m; i >= l; i--){
        
        while (ls != 0 && part[i].first > left[ls-1].first){
            left.pop_back();
            ls -= 1;
        }
        //printf("1111\n");
        //printf("i=%d %d %d %d\n", i, part[i].first, part[i].second, part[ri].second);
        while (ri > m && part[ri].second < part[i].second){
            while (rs != 0 && part[ri].first < rightX[rs-1]){
                rightX.pop_back();
                rightY.pop_back();
                rs -= 1;
            }
            rightX.push_back(part[ri].first);
            rightY.push_back(part[ri].second);
            rs += 1;
            ri -= 1;
        }
        //printf("2222\n");
        //printf("rs=%d\n", rs);
        if (ls == 0 || rs == 0)
            sum += rs;
        else{
            /*int lb = 0, rb = rs - 1; //rs==0? -1?
            int m = (lb + rb) / 2;
            //printf("m=%d ls=%d\n ", m, ls);
            if (right[rs-1].second < left[ls-1].second){
                m = rs - 1;
            }else if(right[0].second > left[ls-1].second){
                m = 0 - 1;
            }else{
                while(!(right[m].second < left[ls-1].second && right[m+1].second > left[ls-1].second)){
                    //printf("3333\n");
                    if (right[m].second > left[ls-1].second){
                        rb = m;
                        m = (lb + rb) / 2;
                    }else{
                        lb = m+1;  // m or m+1
                        m = (lb + rb) / 2;
                    }
                }
                //printf("4444\n");
                
            }*/
            //printf("FB m=%d\n", m);
            vector<int>::iterator low;
            low = lower_bound(rightY.begin(), rightY.end(), left[ls-1].second);
            //cout << low - rightY.begin() << endl;
            //cout << "rs=" << rs << endl;
            //cout << "ls=" << left[ls-1].first << left[ls-1].second << endl;
            sum += rs - (low - rightY.begin());     //right[0] < left[ls-1]怎麼辦
        }
        //printf("5555\n");
        left.push_back(part[i]);
        ls += 1;
        
        //printf("FB sum=%d\n", sum);
        
    }
    
    return;
}




void merge(vector<pair<int, int> > &part, int l, int m, int r){
    vector<pair<int, int> > combine;
    combine.clear();
    //printf("merge l=%d m=%d r=%d\n", l, m, r);
    int ls = l, rs = m+1;
    /*for (int i = l; i <= r; i++){
        printf("mx=%d my=%d\n", part[i].first, part[i].second);
    }*/
    
    while (ls <= m || rs <= r){
        if (rs > r || (ls <= m && part[ls].second > part[rs].second)){
            //printf("in1\n");
            combine.push_back(part[ls]);
            ls += 1;
        }else if (ls > m || (rs <= r && part[ls].second <= part[rs].second)){
            //printf("in2\n");
            combine.push_back(part[rs]);
            rs += 1;
        }
    }
    for (int i = l; i <= r; i++){
        /*printf("combinex=%d combiney=%d\n", combine[i-l].first, combine[i-l].second);*/
        part[i] = combine[i-l];
        
    }
    
    return;
}
