#pragma warning ( disable : 4996 )
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
using namespace cv;
using namespace std;

vector<vector<double>> v, ve;
vector<int> r;

vector<double> w;

double study = 0.1; // �н���
double e = 0.000001; // ������ 

double sigmoid(double net) {
	return 1 / double(1 + exp(-net));
}

double cal(vector<double> &a, const vector<double> &b) {
	double sum = 0;
	for (int i = 0; i < a.size(); i++) sum += a[i] * b[i];
	return sum; // ent
}

void chageBlack(Mat &image, Mat &image_gray) {

	cout << "��� ��ȯ ����\n";
	int nRows = image.rows;
	int nCols = image.cols;

	float fGray = 0.0f;
	float chBlue, chGreen, chRed;

	for (int j = 0; j < nRows; j++) {

		for (int i = 0; i < nCols; i++) {

			chBlue = (float)(image.at<cv::Vec3b>(j, i)[0]);
			chGreen = (float)(image.at<cv::Vec3b>(j, i)[1]);
			chRed = (float)(image.at<cv::Vec3b>(j, i)[2]);

			fGray = 0.2126f * chRed + 0.7152f * chGreen + 0.0722f * chBlue;

			if (fGray < 0.0) fGray = 0.0f;
			if (fGray > 255.0) fGray = 255.0f;

			image_gray.at<cv::Vec3b>(j, i)[0] = (int)fGray;
			image_gray.at<cv::Vec3b>(j, i)[1] = (int)fGray;
			image_gray.at<cv::Vec3b>(j, i)[2] = (int)fGray;

		}
	}
	cout << "��� ��ȯ ����\n";
}


vector<string> getPathFileName(string path) {

	cout << "�����̸� �������� ����\n";
	_finddata_t fd;
	intptr_t hand;
	int res = 1;
	hand = _findfirst((path + "*.jpg").c_str(), &fd);

	vector<string> ans;
	if (hand == -1) return ans;

	while (res != -1) {
		ans.push_back(path + fd.name);
		res = _findnext(hand, &fd);
	}

	_findclose(hand);
	cout << "�����̸� �������� ����\n";
	return ans;
}

void getImage(string path, vector<vector<double>> &v) {
	cout << "�̹��� 1���� ������ ��ȯ ����\n";
	Mat image = imread(path), image_gray;
	image.copyTo(image_gray);
	chageBlack(image, image_gray);

	vector<double> inputdata;
	for (int i = 0; i < image_gray.rows; i++) {
		for (int k = 0; k < image_gray.cols; k++) {
			inputdata.push_back(image_gray.at<cv::Vec3b>(i, k)[0] / 1000.0);
		}
	}
	v.push_back(inputdata);
	cout << "�̹��� 1���� ������ ��ȯ ����\n";
}

int main() {
	cout << "�Ű�� ���� ���� �� �Ǻ� ���α׷� ��ŸƮ\n";
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<string> sv;

	string a = "C:\\Users\\chltk\\1111\\";
	string b = "C:\\Users\\chltk\\2222\\";

	sv = getPathFileName(a);

	cout << sv[0] << "\n";

	for (int i = 0; i < 15; i++) r.push_back(1);
	for (int i = 15; i < 46; i++) r.push_back(0);

	for (int i = 0; i < 46; i++) getImage(sv[i], v);


	int sz = v[0].size();
	cout << "������ : " << sz << "\n";

	srand(time(NULL));

	cout << "���� ���� ������ ������\n";
	for (int i = 0; i < sz; i++) {
		if (rand() % 2) w.push_back(double(rand() % 5 + 1) / 10);
		else  w.push_back(-double(rand() % 5 + 1) / 10);

		if (w[i] == 0) cout << "���� �߻�\n";
	}
	cout << "���� �Ϸ�\n";

	int n = v.size();

	cout << "�н� ����\n";
	int cnt = 0;
	while (1) {

		bool ch = 0;

		for (int i = 0; i < n; i++) {
			double net = cal(v[i], w); // net ��
			double y = sigmoid(net); // �ñ׸��̵� input ��� y
			double sy = (r[i] - y) * y * (1 - y); // ������ȣ
			double tempe = 1 / 2.0 * (r[i] - y) * (r[i] - y);

			for (int k = 0; k < sz; k++) {
				w[k] += sy * v[i][k] * study;
			}

			if (tempe < e) {
				ch = 1; break;
				// �н� ����
			}
		}
		if (ch) break;
	}
	cout << "�н� �Ϸ�\n";

	cout << "�׽�Ʈ ������ �Է� ����\n";
	sv = getPathFileName(b);
	cout << "�׽�Ʈ ������ �Է� ��\n";

	int m = sv.size();
	for (int i = 0; i < sv.size(); i++) getImage(sv[i], ve);

	cout << "�Ű�� �Ǵ� ��\n";
	for (int i = 0; i < m; i++) {

		cout <<i + 1<<"��° ���� : "<< sv[i] << "\n";
		double net = cal(ve[i], w); // net ��

		cout << "net �� : " << net << "\n";
		double y = sigmoid(net);
		cout << "Y �� : " << y << "\n";
		if (y >= 0.5) cout << "��� : �ο����Դϴ�." << "\n";
		else cout << "��� : �ο��Ⱑ �ƴմϴ�." << "\n";
	}
	cout << "�Ű�� ����\n";
	waitKey();
	system("pause");
}