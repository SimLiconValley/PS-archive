# C++로 BFS 및 DFS 설계

## BFS
BFS는 보통 큐(FIFO) 를 이용한다.
탐색 지점을 큐에 넣고
큐에서 빼게 되면 동일 depth로 탐색이 가능하다.
```c++
int main(){
	vector<vector<int> > v(4, vector<int>(5));

	queue<tuple<int, int, int>> q; // 큐 생성
	
	q.push(make_tuple(0,0,1)); // 최초 삽입
	
	while(!q.empty()){
		auto point = q.front();
		q.pop(); // 엘레먼트 추출
		if(v[get<0>(point)][get<1>(point)] == 0){ // 비어있다면
			v[get<0>(point)][get<1>(point)] = get<2>(point); // 셀에 값 할당
			if(get<0>(point) + 1 < v.size()){ // BFS 탐색 삽입
				q.push(make_tuple(get<0>(point) + 1, get<1>(point), get<2>(point)+1));
			}
			if(get<1>(point) + 1 < v[0].size()){ // BFS 탐색 삽입
				q.push(make_tuple(get<0>(point), get<1>(point)+1, get<2>(point)+1));
			}
		}
	}
	print(v);
	return 0;
}
/* 출력:
1 2 3 4 5 
2 3 4 5 6 
3 4 5 6 7 
4 5 6 7 8 
*/
```

## DFS
DFS는 스택을 이용하는데, 함수 콜스택이 적격이다.
파라미터로 데이터를 전달하고
종료 지점을 조건문으로 설정한다.
