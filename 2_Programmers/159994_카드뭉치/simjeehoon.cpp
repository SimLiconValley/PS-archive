#include string
#include vector

using namespace std;

string solution(vectorstring cards1, vectorstring cards2, vectorstring goal) {
    vectorstringsize_type c1=0, c2=0, g=0;
    for(;ggoal.size();g++){
        if(c1  cards1.size() && cards1[c1] == goal[g]){
            c1++;
        }
        else if(c2  cards2.size() && cards2[c2] == goal[g]){
            c2++;
        }
        else
            return No;
    }
    return Yes;
}