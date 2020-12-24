#include <iostream>
#include <vector>
using namespace std;
#define double long double

vector<vector<int>> v;
vector<int> res;

vector<double> w;

double study = 1.0; // 학습률
double e = 0.00001; // 오차율 

double cal(vector<int> &a,vector<double> b) {
	double sum = 0;
	for (int i = 0; i < a.size(); i++) sum += a[i] * b[i];
	return sum; // ent
}

double sigmoid(double net) {
	return 1 / (1 + exp(-net));
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	int n; cin >> n;
	// 학습 데이터

	v.resize(n + 1), res.resize(n + 1);
	w.resize(20);
	for (int i = 0; i < n; i++) {
		vector<int> e;
		for (int k = 0; k < 20; k++) {
			int a; cin >> a; e.push_back(a);
		}
		cin >> res[i];
		v[i] = e;
	}
	
	w[0] = 0.1;
	w[1] = 0.2;
	w[2] = -0.3;
	w[3] = -0.1;
	w[4] = -0.2;
	w[5] = 0.1;
	w[6] = -0.2;
	w[7] = 0.1;
	w[8] = -0.2;
	w[9] = 0.1;
	w[10] = 0.2;
	w[11] = -0.2;
	w[12] = 0.1;
	w[13] = 0.2;
	w[14] = -0.2;
	w[15] = 0.3;
	w[16] = 0.2;
	w[17] = -0.1;
	w[18] = -0.2;
	w[19] = 0.1;

	while (1) {
		bool ch = 0;
		for (int i = 0; i < n; i++) {
			double net = cal(v[i],w); // net 값
			double y = sigmoid(net); // 시그모이드 input 출력 y
			double sy = (res[i] - y) * y * (1 - y); // 오차신호
			double tempe = 1 / 2.0 * (res[i] - y) * (res[i] - y);

			for (int k = 0; k < 20; k++) {
				w[k] += sy * v[i][k] * study;
			}

			if (tempe < e) {

				for (int i = 0; i < n; i++) {
					double net = cal(v[i], w); // net 값
					double y = sigmoid(net); // 시그모이드 input 출력 y
					double sy = (res[i] - y) * y * (1 - y); // 오차신호
					double tempe = 1 / 2.0 * (res[i] - y) * (res[i] - y);


					for (int k = 0; k < 20; k++) {
						w[k] += sy * v[i][k] * study;
					}
				}

				ch = 1; break;
				// 학습 종료
			}
		}
		if (ch) break;
	}

	int m; cin >> m; // 테스트 데이터

	for (int i = 0; i < m; i++) {
		vector<int> e;
		for (int k = 0; k < 20; k++) {
			int a; cin >> a; e.push_back(a);
		}
		double net = cal(e, w); // net 값
		double y = sigmoid(net);

		if (y >= 0.5) cout << 1 << "\n";
		else cout << 0 << "\n";
	}
	system("pause");
}