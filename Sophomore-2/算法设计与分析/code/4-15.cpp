//4-15
/*
a+bΪ����ʱ��|a-b|��ԽС��abԽ��
������������������ȣ�����Ҫ��n�ֳɾ����ܶ����������1����
̰�Ĳ��ԣ���n�ֳɴ�2��ʼ��������Ȼ���ĺ͡�
������ʣ��һ������ǰ��ʹ�ù��ģ��ͽ��������ȷָ�ǰ�����Ӻ���ǰ����
*/
#include <iostream>

using namespace std;
int a[10050];//��ŷֽ����

void maxdivision(int n) {
	int k = 1;
	//���Ϸ�������
	if (n < 3) {
		a[1] = 0;
		return;
	}

	//n�Ƚ�Сʱֻ��һ�ַַ����������ۣ�
	if (n < 5) {
		a[k] = 1;
		a[++k] = n - 1;
	}

	a[1] = 2;
	n -= 2;
	while (n > a[k]) {
		k++;
		a[k] = a[k - 1] + 1;
		n -= a[k];
	}
	if (n == a[k]) {
		a[k]++;
		n--;
	}//����a[k]>k-1�������������

	for (int i = 0; i < n; i++) {
		a[k - i]++;
	}
	return;
}

int main() {
	int n;
	cin >> n;
	maxdivision(n);
	int ans = 1, idx = 1;
	while (a[idx]) {
		ans *= a[idx++];
	}
	cout << ans << endl;
}
