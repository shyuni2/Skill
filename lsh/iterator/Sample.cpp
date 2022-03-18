#include <iostream>
#include <vector>
using namespace std;

int main() {

	vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	// 벡터 반복자 선언 및 시작점을 가리키도록 함
	vector<int>::iterator iter = v.begin();

	// for문
	// iter이 begin에서 시작, end까지 하나씩 추가
	for (iter = v.begin(); iter != v.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;
	// 현재 iterator는 v.end()를 가리킴

	// iterator는 v.begin()으로 다시 가리킴
	iter = v.begin();

	// 임의접근
	cout << "iter[0] : " << iter[0] << endl;
	cout << "iter[3] : " << iter[3] << endl << endl;

	// iterator는 v.begin() + 2 (3번째 원소)를 가리킴
	cout << "iterator가 3번째 원소를 가리키도록 변경" << endl;
	iter += 2;  // += 연산
	cout << "iter[0] : " << iter[0] << endl;
	cout << "*iter : " << *iter << endl;

	// 반복자를 통한 원소 값 변경
	*iter = 10;
	*(iter + 1) = 20;
	iter[2] = 30;
	// for문
	for (iter = v.begin(); iter != v.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;

	return 0;
}
