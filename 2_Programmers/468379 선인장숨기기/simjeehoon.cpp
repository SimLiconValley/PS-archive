#include <string>
#include <vector>
#include <deque>
#include <climits>
#include <iostream>
using namespace std;

class Debug{
    static bool debug_mode;
    
    const vector<vector<int> > &grid;
    const vector<vector<int> > &row_min;
    
    public:
    Debug(vector<vector<int> > &grid, vector<vector<int> > &row_min)
        :grid(grid), row_min(row_min){}
    
    void print_grid(){
        if(Debug::debug_mode){
            cout << "grid:\n";
            for(int i = 0 ; i < grid.size() ; i++){
                cout << "[";
                for(int j = 0 ; j < grid[i].size() ; j++){
                    auto value = grid[i][j];
                    if(value == INT_MAX)
                        cout << "INF" << ", " ;
                    else
                        cout << grid[i][j] << ", ";
                }
                cout << "]\n";
            }
            cout << endl;
        }
    }
    
    void print(const deque<int> &dq){
        if(Debug::debug_mode){
            cout << "[";
            for(auto iter = dq.begin() ; iter != dq.end() ; iter++){
                cout << *iter << ", ";
            }
            cout << "]" << endl;
        }
    }
};

bool Debug::debug_mode=true;

vector<int> solution(int m, int n, int h, int w, vector<vector<int>> drops) {
    vector<vector<int>> grid(m,vector<int>(n, INT_MAX));
    
    for(int i = 0 ; i < drops.size() ; i++){
        grid[drops[i][0]][drops[i][1]] = i+1;
    }
    
    vector<vector<int>> row_min(m,vector<int>(n-w+1, 0));
    Debug d(grid, row_min);
    d.print_grid();
    for(int r = 0 ; r < m ; r++){
        deque<int> dq;
        for(int c = 0 ; c < n ; c++){
            while(!dq.empty() && grid[r][dq.back()] >= grid[r][c]) 
                dq.pop_back();
            
            dq.push_back(c);
            
            if(dq.front() <= c-w) // 밭 바깥으로 나갔다면 인덱스 제외
                dq.pop_front();
            if(c-w+1 >= 0){ // 밭의 너비가 충족되었다면
                row_min[r][c-w+1] = grid[r][dq.front()];
            }
            d.print(dq);
        }
    }
    
    //열단위
    int max_value=-1, ansy=0, ansx=0;
    for(int c = 0 ; c < n-w+1 ; c++){
        deque<int> dq;
        for(int r = 0 ; r < m ; r++){
            while(!dq.empty() && row_min[dq.back()][c] >= row_min[r][c])
                dq.pop_back();
            dq.push_back(r);
            
            if(dq.front()<=r-h)
                dq.pop_front();
            if(r-h+1 >= 0){
                int nh = r-h+1;
                int nw = c;
                int rainy = row_min[dq.front()][c];
                if(max_value < rainy){
                    max_value = rainy;
                    ansy = nh;
                    ansx = nw;
                }
                else if(max_value == rainy){
                    if((nh < ansy)||(ansy == nh && nw < ansx)){
                        ansy=nh;
                        ansx=nw;
                    }
                }
            }
        }
    }
    
    
    vector<int> answer={ansy,ansx};
    return answer;
}