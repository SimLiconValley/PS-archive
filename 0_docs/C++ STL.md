# 자주 쓰이는 C++ STL  정리 문서

## vector <vector>
### 생성자

```c++
std::vector<Type>(벡터의 크기, 초기화값); // 초기화값으로 초기화

std::vector<Type>(벡터의 크기); // 0으로 초기화
```
### assign
```c++
std::vector<Type> v;
v.assign(length, 값); // 벡터의 크기를 length로 재설정하고, 값으로 전부 배정.
v.assign(cont.begin(), cont.end()); // 컨테이너의 두 이터레이터 사이의 값으로 배정
```

