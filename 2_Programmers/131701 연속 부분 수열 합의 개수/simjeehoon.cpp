#include <string>
#include <vector>
#include <set>

using namespace std;

int solution(vector<int> elements) {
    int answer = 0;
    set<int> s;
    for(int start_idx = 0 ; start_idx < elements.size() ; start_idx++){
        int sum=0;
        int cur_idx = start_idx;
        for(int length = 1 ; length <= elements.size() ; length++){
            sum += elements[cur_idx];
            s.insert(sum);
            cur_idx = (cur_idx+1)%elements.size();
        }
    }
    return s.size();
}