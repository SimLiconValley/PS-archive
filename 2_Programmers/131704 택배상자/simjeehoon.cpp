#include <string>
#include <vector>
#include <numeric>
#include <stack>

using namespace std;

int solution(vector<int> order) {
    int answer = 0;
    
    vector<int> increasing_boxs(order.size());
    iota(increasing_boxs.begin(),increasing_boxs.end(),1);
    
    stack<int> st;
    
    int i = 0;
    while(i < increasing_boxs.size()){
        auto box = increasing_boxs[i];
        if(box == order[answer]){ // 그 박스야
            ++answer;
            ++i;
            continue;
        }
        else if(!st.empty() && st.top() == order[answer]){ // 보조 컨테이너에 있다.
            st.pop();
            ++answer;
        }
        else{ // 그 박스를 보조 컨테이너에 넣자
            st.push(box);
            ++i;
        }
    }
    while(!st.empty() && st.top() == order[answer]){
        ++answer;
        st.pop();
    }
    
    return answer;
}