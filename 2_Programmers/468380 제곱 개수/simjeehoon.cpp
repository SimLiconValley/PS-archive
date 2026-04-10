#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> solution(vector<int> arr, long long l, long long r) {
    vector<long long> brrlen(arr.size()+1), brrsum(arr.size()+1);
    for(int i = 0 ; i < arr.size() ; i++){
        brrlen[i+1] = brrlen[i] + arr[i];
        brrsum[i+1] = brrsum[i] + (long long)arr[i]*arr[i];
    }
    auto get_i = [&](long long x) -> int{
        return lower_bound(brrlen.begin(), brrlen.end(), x)-brrlen.begin()-1;
    };
    auto get_sum = [&](long long x) -> long long{
        int i = get_i(x);
        return brrsum[i] + (x-brrlen[i]) * arr[i];
    };
    
    long long K=get_sum(r) - get_sum(l-1);
    long long C=0;
    
    long long idx_l = get_i(l);
    long long idx_r = get_i(r);
    
    // 덩어리 내 위치
    long long p_l = l-(brrlen[idx_l]+1);
    long long p_r = r-(brrlen[idx_r]+1);
    
    return {K,C};
}