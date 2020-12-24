#include <iostream>
#include <vector>
using namespace std;

class Data {
public:
	double a, b, c;
};

vector<Data> v;
vector<int> res;

Data w[2]; // ���� ����
Data r;
double study = 2; // �н���
double e = 0.0001; // ������ 


double cal(Data &a, Data &b) {
	return a.a * b.a + a.b * b.b + a.c * b.c; // �Է� ������
}

double sigmoid(double net) {
	return 1 / (1 + exp(-net));
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	int n; cin >> n;
	// �н� ������

	v.resize(n);
	for (int i = 0; i < n; i++) { // �н� ������
		double a, b, c; cin >> a >> b >> c;
		v[i] = { a,b,1 }; res.push_back(c);
		// v �� 3��° ���ڴ� ���̾
	}

	w[0] = { 0.1,-0.2,0.3 };
	w[1] = { -0.2,0.3,0.2 };
	r = { -0.1,-0.2,0.3 };

	while (1) {
		bool ch = 0;
		for (int i = 0; i < n; i++) {
			vector<double> t;
			for (int k = 0; k < 2; k++) {
				double net = cal(v[i], w[k]); // net ��
				double y = sigmoid(net); // �ñ׸��̵� input ��� y Ȱ��ȭ �Լ�
				t.push_back(y);
			}

			Data z = { t[0],t[1], 1 };

			double net = cal(z, r);
			double y = sigmoid(net);

			double tempe = 1 / 2.0 * (res[i] - y) * (res[i] - y);

			double sy = (res[i] - y) * y * (1 - y);

			double z1 = t[0] * (1 - t[0]) * sy * r.a; // sy y �� �������� ����ؼ� z1 �� ������ ���Ѵ�.
			double z2 = t[1] * (1 - t[1]) * sy * r.b;

			r.a += sy * study * t[0];
			r.b += sy * study * t[1];
			r.c += sy * study * 1; // ������ ���̾

			w[0].a += z1 * study * v[i].a;
			w[0].b += z1 * study * v[i].b;
			w[0].c += z1 * study * 1;

			w[1].a += z2 * study * v[i].a;
			w[1].b += z2 * study * v[i].b;
			w[1].c += z2 * study * 1;

			if (tempe < e) {
				ch = 1; break;
			}
		}
		if (ch) break;
	}

	int m; cin >> m; // �׽�Ʈ ������

	for (int i = 0; i < m; i++) {
		double a, b; cin >> a >> b;
		Data d = { a,b , 1 };

		vector<double> t;
		for (int k = 0; k < 2; k++) {
			double net = cal(d, w[k]); // net ��
			double y = sigmoid(net); // �ñ׸��̵� input ��� y Ȱ��ȭ �Լ�
			t.push_back(y);
		}

		Data z = { t[0],t[1] , 1 };

		double net = cal(z, r);
		double y = sigmoid(net);

		if (y >= 0.5) cout << 1 << "\n";
		else cout << 0 << "\n";
	}

	system("pause");
}