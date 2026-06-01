#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int W_LEFT = 1;
const int W_HIGH = 1 << 1;
const int W_RIGHT = 1 << 2;
const int W_LOW = 1 << 3;
const int W_CROSS = 1 << 4;
const int W_OBS = 1 << 5;

void print(const vector<vector<int> > &matrix){
    bool flag = false;
    if(flag){
        for(int i = 0 ; i < matrix.size() ; i++){
            for(int j = 0 ; j < matrix[i].size() ; j++){
                if(matrix[i][j] & W_CROSS){
                    std::cout << "┼ ";
                }
                else if(matrix[i][j] == (W_LEFT | W_RIGHT)){
                    std::cout << "─ ";
                }
                else if(matrix[i][j] == (W_HIGH | W_LOW)){
                    std::cout << "| ";
                }
                else if(matrix[i][j] == (W_LEFT | W_HIGH)){
                    std::cout << "┘ ";
                }
                else if(matrix[i][j] == (W_LEFT | W_LOW)){
                    std::cout << "┐ ";
                }
                else if(matrix[i][j] == (W_RIGHT | W_HIGH)){
                    std::cout << "└ ";
                }
                else if(matrix[i][j] == (W_RIGHT | W_LOW)){
                    std::cout << "┌ ";
                }
                else if(matrix[i][j] == (W_OBS)){
                    std::cout << "× ";
                }
                else if(matrix[i][j] == 0){
                    std::cout << ". ";
                }
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
}

vector<vector<int>> maker(const vector<vector<int>> &origin) {
    vector<vector<int>> newone = origin;

    for(int i = 0 ; i < origin.size() ; i++){
        for(int j = 0 ; j < origin[i].size() ; j++){
            newone[i][j] = 0;
            switch(origin[i][j]){
            case 1://-
                newone[i][j] = W_LEFT | W_RIGHT;
                break;
            case 2://|
                newone[i][j] = W_HIGH | W_LOW;
                break;
            case 3://+
                newone[i][j] = W_LEFT | W_RIGHT | W_HIGH | W_LOW | W_CROSS;
                break;
            case 4://┘
                newone[i][j] = W_LEFT | W_HIGH;
                break;
            case 5://└
                newone[i][j] = W_RIGHT | W_HIGH;
                break;
            case 6://┌
                newone[i][j] = W_RIGHT | W_LOW;
                break;
            case 7://┐
                newone[i][j] = W_LEFT | W_LOW;
                break;
            case -1://x
                newone[i][j] = W_OBS;
                break;
            }
        }
    }

    return newone;
}
//1234 좌상우하
int dr[] = {0,0,-1,0,1};
int dc[] = {0,-1,0,1,0};
const int D_LEFT = 1;
const int D_HIGH = 2;
const int D_RIGHT = 3;
const int D_LOW = 4;

bool valid(vector<vector<int> > &data){
    for(int r = 0 ; r < data.size() ; r++){
        for(int c = 0 ; c < data[r].size() ; c++){
            if(r==0 && c==0) // 첫스타트
                continue;
            if(r==data.size()-1 && c==data[r].size()-1){ // 마지막
                if((data[r][c] & W_HIGH) && (data[r-1][c] & W_LOW)){ //세로연결
                    return true;
                }
                else if((data[r][c] & W_LEFT) && (data[r][c-1] & W_RIGHT)){ // 가로연결
                    return true;
                }
                else{
                    return false;
                }
            }
            if(data[r][c] & W_HIGH){ // 위탐색
                if(r-1 < 0)
                    return false;
                if(!(data[r-1][c] & W_LOW))
                    return false;
            }
            if(data[r][c] & W_LOW){ // 아래탐색
                if(r+1 >= data.size())
                    return false;
                if(!(data[r+1][c] & W_HIGH))
                    return false;
            }
            if(data[r][c] & W_LEFT){ // 왼쪽탐색
                if(c-1 < 0)
                    return false;
                if(!(data[r][c-1] & W_RIGHT))
                    return false;
            }
            if(data[r][c] & W_RIGHT){ // 오른쪽탐색
                if(c+1 >= data[0].size())
                    return false;
                if(!(data[r][c+1] & W_LEFT))
                    return false;
            }
        }
    }
    return true;
}

int answer=0;

void dfs(vector<vector<int> > &data, int r, int c, int d){
    if(!(0 <= r && r < data.size())){
        return;
    }
    if(!(0 <= c && c < data[0].size())){
        return;
    }


    if(r == 0 && c == 0){ // 처음 스타트
        if(d == D_RIGHT){
            dfs(data, r, c+1, D_RIGHT);
            return;
        }
        else
            return;
    }
    else if((r == data.size()-1) && (c == data[r].size() - 1)){ // 마지막 셀
        if(valid(data)) {
            ++answer;
        }
        return;
    }

    int nd = 0;
    if(data[r][c]){ // 이미 존재.
        if(data[r][c] & W_CROSS){ // 크로스
            dfs(data, r+dr[d], c+dc[d], d);
        }

        else if((data[r][c] == (W_LEFT | W_RIGHT))){ // -
            if (d == D_LEFT || d == D_RIGHT) {
                dfs(data, r+dr[d], c+dc[d], d);
            }
        }
        else if((data[r][c] == (W_HIGH | W_LOW))){ // |
            if (d == D_HIGH || d == D_LOW) {
                dfs(data, r+dr[d], c+dc[d], d);
            }
        }

        else if((data[r][c] == (W_LEFT | W_HIGH))){ //┘
            if (d == D_RIGHT){
                nd = D_HIGH;
                dfs(data, r+dr[nd], c+dc[nd], nd);
            }
            else if(d == D_LOW){
                nd = D_LEFT;
                dfs(data, r+dr[nd], c+dc[nd], nd);
            }
        }
        else if((data[r][c] == (W_LEFT | W_LOW))){ // ┐
            if (d == D_RIGHT){
                nd = D_LOW;
                dfs(data, r+dr[nd], c+dc[nd], nd);
            }
            else if(d == D_HIGH){
                nd = D_LEFT;
                dfs(data, r+dr[nd], c+dc[nd], nd);
            }
        }

        else if((data[r][c] == (W_RIGHT | W_HIGH))){ // └
            if (d == D_LEFT){
                nd = D_HIGH;
                dfs(data, r+dr[nd], c+dc[nd], nd);
            }
            else if(d == D_LOW){
                nd = D_RIGHT;
                dfs(data, r+dr[nd], c+dc[nd], nd);
            }
        }
        else if((data[r][c] == (W_RIGHT | W_LOW))){  // ┌
            if (d == D_LEFT){
                nd = D_LOW;
                dfs(data, r+dr[nd], c+dc[nd], nd);
            }
            else if(d == D_HIGH){
                nd = D_RIGHT;
                dfs(data, r+dr[nd], c+dc[nd], nd);
            }
        }

        else if(data[r][c] == W_OBS){  // x
            return;
        }
    }
    else{ // 빈칸
        
        if(d == D_LEFT){
            // 십자가
            data[r][c] = W_LEFT | W_RIGHT | W_HIGH | W_LOW | W_CROSS;
            nd = d;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);
            
            // -
            data[r][c] = W_RIGHT | W_LEFT;
            nd = d;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);

            // 우상
            data[r][c] = W_RIGHT | W_HIGH;
            nd = D_HIGH;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);
            
            // 우하
            data[r][c] = W_RIGHT | W_LOW;
            nd = D_LOW;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);
        }
        else if(d == D_HIGH){

            //십자가
            data[r][c] = W_LEFT | W_RIGHT | W_HIGH | W_LOW | W_CROSS;
            nd = d;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);

            // |
            data[r][c] = W_HIGH | W_LOW;
            nd = d;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);
            
            //우하
            data[r][c] = W_RIGHT | W_LOW;
            nd = D_RIGHT;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);
            
            //좌하
            data[r][c] = W_LEFT | W_LOW;
            nd = D_LEFT;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);
        }
        else if(d == D_RIGHT){
            //십자가
            data[r][c] = W_LEFT | W_RIGHT | W_HIGH | W_LOW | W_CROSS;
            nd = d;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);
            
            // -
            data[r][c] = W_RIGHT | W_LEFT;
            nd = d;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);
            
            //좌상
            data[r][c] = W_LEFT | W_HIGH;
            nd = D_HIGH;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);
            
            //좌하
            data[r][c] = W_LEFT | W_LOW;
            nd = D_LOW;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);

        }
        else if(d == D_LOW){
            data[r][c] = W_LEFT | W_RIGHT | W_HIGH | W_LOW | W_CROSS;
            nd = d;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);

            data[r][c] = W_HIGH | W_LOW;
            nd = d;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);

            //좌상
            data[r][c] = W_LEFT | W_HIGH;
            nd = D_LEFT;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);

            //우상
            data[r][c] = W_RIGHT | W_HIGH;
            nd = D_RIGHT;
            print(data);
            dfs(data, r+dr[nd], c+dc[nd], nd);
        }
        data[r][c] = 0;
    }

}

int solution(vector<vector<int>> grid) {
    vector<vector<int> > data = maker(grid);
    print(data);
    dfs(data,0,0,D_RIGHT);
    return answer;
}
