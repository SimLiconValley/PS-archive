# 자주 쓰이는 C++ STL  정리 문서

## vector <vector>
### 생성자

```c++
    std::vector<Type>(벡터의 크기, 초기화값); // 초기화값으로 초기화

    std::vector<Type>(벡터의 크기); // 0으로 초기화
```
### assign

vector 자체에 assign 이라는 메서드가 있다.

```c++
    std::vector<Type> v;
    v.assign(length, 값); // 벡터의 크기를 length로 재설정하고, 값으로 전부 배정.
    v.assign(cont.begin(), cont.end()); // 컨테이너의 두 이터레이터 사이의 값으로 배정
```

### 값 증가 할당
- iota <numeric>

itoa 아님

```c++
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1); // numeric, 3번째인자는 시작값
    std::for_each(v.begin(), v.end(), [](int a){std::cout << a << ' ';}); //algorithm, iostream
    // 1 2 3 4 5 6 7 8 9 10
```

- generate <algorithm>
```c++
    std::vector<int> v(10);
    int a=1;
    std::generate(v.begin(), v.end(), [&a]{return a++;});
    std::for_each(v.begin(), v.end(), [](int a){std::cout << a << ' ';});
    // 1 2 3 4 5 6 7 8 9 10
```

### fill
```c++
    std::vector<int> v(10);
    std::fill(v.begin(), v.end(), 3);
    std::for_each(v.begin(), v.end(), [](int a){std::cout << a << ' ';});
    // 3 3 3 3 3 3 3 3 3 3
```

## string <string>
### Java는 immutable 이지만(값 수정 불가), C++은 mutable 이다.(값 수정 가능)
vector의 연산이 다 지원된다.

```c++
    std::string s = "hello, world!";
    s[0] = 'b';
    s.push_back('?');
    std::cout << s << std::endl; //bello, world!?
```

## stringstream <sstream>
### string을 stream으로 다룰 수 있다.
```c++
    std::string s = "hello, world!";
    std::stringstream ss1(s);

    std::string s1, s2;
    ss1 >> s1 >> s2; // in 예제
    std::cout << "one:" << s1 << "&" <<  std::endl; // one:hello,&
    std::cout << "two:" << s2 << "&" << std::endl; // two:world!&

    std::stringstream ss2;

    ss2 << 1 << '+' << 2. << "==" << 3; //out 예제
    std::cout << ss2.str() << std::endl; //1+2==3
    std::cout << ss1.str() << std::endl; //hello, world! (스트림내부의 스트링을 반환하는것이므로)
    
    ss1.str(""); //재설정방법
    std::cout << "empty:" << ss1.str() << std::endl; //이젠 아무것도 없음
```

결과값

```
one:hello,&
two:world!&
1+2==3
hello, world!
empty:
```

## queue <queue>

- push(1) : 넣는다
- pop() : 뺀다
- front() : 앞의 원소 얻는다
- empty() : 비었나

- back() : 방금 넣은 원소 얻는다.
- size() : 원소개수

```c++
    std::queue<int> q;
    q.push(2);
    q.push(4);
    q.push(6);
    int cnt=3;
    int number = 10;
    while(!q.empty()){
        auto value = q.front();
        q.pop();
        std::cout<< value << ' ';
        if(cnt-- > 0)
            q.push(number++);
    }

    // 2 4 6 10 11 12
```

## stack <stack>

- push(1) : 넣는다
- pop() : 뺀다
- top() : 원소 얻는다
- empty() : 비었나

- size() : 원소개수

```c++
    std::stack<int> s;
    s.push(2);
    s.push(4);
    s.push(6);
    int cnt=3;
    int number = 10;
    while(!s.empty()){
        auto value = s.top();
        s.pop();
        std::cout<< value << ' ';
        if(cnt-- > 0)
            s.push(number++);
    }

    // 6 10 11 12 4 2 
```

## priority_queue

- push :넣는다!
- pop :뺀다!
- top :뺄 녀석
- empty: 비었나?


```c++
#include <iostream>
#include <queue>

int main() {
    auto cmp = [](int a, int b){
        return a<b;
    }; // 람다를 이용한 비교함수 cmp. cmp의 타입을 추출하기 위한 decltype 사용(sizeof 와 같이 컴파일타임에 작동하는 연산자라고 함.)
    //std::priority_queue<int> pq;  
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp); //탬플릿인자로 decltype 넘기고 함수객체도 넘김
    std::priority_queue<int, std::vector<int>, std::greater<int> > rev_pq; // #include <functional> 의 grater 이용하면 역연산 가능

    auto f = [&pq, &rev_pq](int value){
        pq.push(value);
        rev_pq.emplace(value); // 생성자처럼 작동
    };
    f(4);    f(7);    f(2);    f(8);  //넣는다!

    while(!pq.empty()){
        std::cout << pq.top() << ' ';  
        pq.pop();
    }
    std::cout << std::endl;

    while(!rev_pq.empty()){
        std::cout << rev_pq.top() << ' ';
        rev_pq.pop();
    }
    std::cout << std::endl;
    
    //8 7 4 2 
    //2 4 7 8 
    
    return 0;
}
```

## unordered_map
### python의 딕셔너리랑 같은 효과

구현이 해쉬테이블임. `(삽입 및 검색 O(1))`

- 생성자 : `std::unordered_map<키,벨류>()`
- `insert({Key, Value})` : 넣는다. (이미 있는 Key이면 삽입을 무시한다.)
- `언오더드맵객체[Key] = Value` : 넣는다. (이미 있는 Key이면 덮어쓴다.)
- `find` : 찾으면 pair<Key, Value> 을 가리키는 iterator, 못찾으면 end() iterator 반환
- `size` : 원소개수

```c++
#include <iostream>
#include <unordered_map>
#include <string>

int main(){
    std::unordered_map<std::string, int> hash_table;
    hash_table.insert({{"Nam", 100},{"Lo", 10}});
    hash_table["Shim"] = 200;

    auto printer = [&](auto name){std::cout<< hash_table[name] << std::endl;};
    printer("Nam");
    printer("Shim");
    if(hash_table.find("Lo") != hash_table.end())
        std::cout << "Lo exist" << std::endl;
    std::cout << hash_table.size() << std::endl;
    return 0;
}
```