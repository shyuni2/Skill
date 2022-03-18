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

	// ���� �ݺ��� ���� �� �������� ����Ű���� ��
	vector<int>::iterator iter = v.begin();

	// for��
	// iter�� begin���� ����, end���� �ϳ��� �߰�
	for (iter = v.begin(); iter != v.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;
	// ���� iterator�� v.end()�� ����Ŵ

	// iterator�� v.begin()���� �ٽ� ����Ŵ
	iter = v.begin();

	// ��������
	cout << "iter[0] : " << iter[0] << endl;
	cout << "iter[3] : " << iter[3] << endl << endl;

	// iterator�� v.begin() + 2 (3��° ����)�� ����Ŵ
	cout << "iterator�� 3��° ���Ҹ� ����Ű���� ����" << endl;
	iter += 2;  // += ����
	cout << "iter[0] : " << iter[0] << endl;
	cout << "*iter : " << *iter << endl;

	// �ݺ��ڸ� ���� ���� �� ����
	*iter = 10;
	*(iter + 1) = 20;
	iter[2] = 30;
	// for��
	for (iter = v.begin(); iter != v.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;

	return 0;
}
