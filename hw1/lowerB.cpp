#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    
    vector<pair<int, int> > v;
    pair<int, int> p;
    p.first = 6;
    p.second = 0;
    v.push_back(make_pair(5, 4));
    v.push_back(make_pair(4, 1));
    //cout << v[0] << v[1] << endl;
    vector<pair<int, int> >::iterator low1;
    low1 = lower_bound(v.begin(), v.end(), p);
    //cout << low1;
    cout << (low1 - v.begin());
    
    
    return 0;
}
