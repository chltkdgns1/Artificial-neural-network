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

double study = 0.1; // 학습률
double e = 0.000001; // 오차율 

double sigmoid(double net) {
	return 1 / double(1 + exp(-net));
}

double cal(vector<double> &a, const vector<double> &b) {
	double sum = 0;
	for (int i = 0; i < a.size(); i++) sum += a[i] * b[i];
	return sum; // ent
}

void chageBlack(Mat &image, Mat &image_gray) {

	cout << "흑백 변환 시작\n";
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
	cout << "흑백 변환 종료\n";
}


vector<string> getPathFileName(string path) {

	cout << "파일이름 가져오기 시작\n";
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
	cout << "파일이름 가져오기 종료\n";
	return ans;
}

void getImage(string path, vector<vector<double>> &v) {
	cout << "이미지 1차원 데이터 변환 시작\n";
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
	cout << "이미지 1차원 데이터 변환 종료\n";
}

int main() {
	cout << "신경망 시작 원기 얼굴 판별 프로그램 스타트\n";
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
	cout << "사이즈 : " << sz << "\n";

	srand(time(NULL));

	cout << "연결 강도 랜던값 생성중\n";
	for (int i = 0; i < sz; i++) {
		if (rand() % 2) w.push_back(double(rand() % 5 + 1) / 10);
		else  w.push_back(-double(rand() % 5 + 1) / 10);

		if (w[i] == 0) cout << "오류 발생\n";
	}
	cout << "생성 완료\n";

	int n = v.size();

	cout << "학습 시작\n";
	int cnt = 0;
	while (1) {

		bool ch = 0;

		for (int i = 0; i < n; i++) {
			double net = cal(v[i], w); // net 값
			double y = sigmoid(net); // 시그모이드 input 출력 y
			double sy = (r[i] - y) * y * (1 - y); // 오차신호
			double tempe = 1 / 2.0 * (r[i] - y) * (r[i] - y);

			for (int k = 0; k < sz; k++) {
				w[k] += sy * v[i][k] * study;
			}

			if (tempe < e) {
				ch = 1; break;
				// 학습 종료
			}
		}
		if (ch) break;
	}
	cout << "학습 완료\n";

	cout << "테스트 데이터 입력 시작\n";
	sv = getPathFileName(b);
	cout << "테스트 데이터 입력 끝\n";

	int m = sv.size();
	for (int i = 0; i < sv.size(); i++) getImage(sv[i], ve);

	cout << "신경망 판단 중\n";
	for (int i = 0; i < m; i++) {

		cout <<i + 1<<"번째 사진 : "<< sv[i] << "\n";
		double net = cal(ve[i], w); // net 값

		cout << "net 값 : " << net << "\n";
		double y = sigmoid(net);
		cout << "Y 값 : " << y << "\n";
		if (y >= 0.5) cout << "결과 : 민원기입니다." << "\n";
		else cout << "결과 : 민원기가 아닙니다." << "\n";
	}
	cout << "신경망 종료\n";
	waitKey();
	system("pause");
}