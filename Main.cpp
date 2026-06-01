#include <cstdio>
#include <iostream>
#include <filesystem>
#include <cstdlib>


// 표준입력 재정의 설정
//#define STDIN_REDIR "input.txt"

// 표준출력 재정의 설정
//#define STDOUT_REDIR "output.txt"

int main() {
	std::cout << "**프로그램 시작**" << std::endl;

#ifdef STDIN_REDIR
	// 표준입력 재정의 설정
	std::filesystem::path input_path = std::filesystem::current_path() / STDIN_REDIR;
	std::cout << "- 입력 재지정: " << input_path << std::endl;
	freopen(STDIN_REDIR, "r", stdin);
#else
	std::cout << "- 표준입력 사용" << std::endl;
#endif

#ifdef STDOUT_REDIR
	// 표준출력 재정의 설정
	std::filesystem::path output_path = std::filesystem::current_path() / STDOUT_REDIR;
	std::cout << "- 출력 저장위치: " << output_path << std::endl;
	freopen(STDOUT_REDIR, "w", stdout);
#else
	std::cout << "- 표준출력 사용" << std::endl;
#endif
	
//TEST_CASE
#include <string>
#include <sstream>
#include <vector>
	std::string s = "1,2,3,4,6";
	std::stringstream sstr(s);
	std::string dst;
	
	std::vector<int> vec;
	
	while (std::getline(sstr, dst, ',')) {
		vec.push_back(std::stoi(dst));
	}
	
	

//function declare
	void t1(std::vector<int> &);

//iterative call
	t1(vec);

	return 0;
}