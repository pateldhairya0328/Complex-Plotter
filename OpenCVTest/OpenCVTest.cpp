// OpenCVTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "opencv2/opencv.hpp"

#include <complex>
#include <math.h>
#include <time.h>

constexpr double PI = 3.14159265358979323846;
constexpr double E = 2.71828182845904523536;
constexpr std::complex<double> I = std::complex<double>(0, 1.0);
constexpr double p[8] = {676.5203681218851, -1259.1392167224028, 771.32342877765313, -176.61502916214059, 12.507343278686905, -0.13857109526572012, 9.9843695780195716e-6, 1.5056327351493116e-7};

int plot_func(int realNum, int imagNum, double realMin, double imagMin, double step, cv::Mat& plot, bool lines, bool equiAngleLines);
std::complex<double> f(std::complex<double> z);
int hsvToRGB(int n, double H, double S, double V);
std::complex<double> gamma(std::complex<double> z);
std::complex<double> bessel_J(int alpha, std::complex<double> z);

int main(int argc, char *argv[])
{
	double realMin = -4, imagMin = -4, realMax = 4, imagMax = 4;
	double step = 4/3840.0;
	bool lines = true, equiAngleLines = true;

	/*for (int i = 1; i < argc; i++) {
		if (!std::strcmp(argv[i], "-realMin"))
			realMin = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-realMax"))
			realMax = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-imagMin"))
			imagMin = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-imagMax"))
			imagMax = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-step"))
			step = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-lines"))
			if (!std::strcmp(argv[i + 1], "f"))
				lines = false;
	}*/

	const int realNum = (int)((realMax - realMin) / step);
	const int imagNum = (int)((imagMax - imagMin) / step);
	
	cv::Mat plot(imagNum, realNum, CV_8UC3);
	clock_t t = clock();
	plot_func(realNum, imagNum, realMin, imagMin, step, plot, lines, equiAngleLines);
	std::cout << (float)(clock() - t);
	cv::imwrite("saved.png", plot);

	return 0;
}

int plot_func(int realNum, int imagNum, double realMin, double imagMin, double step, cv::Mat& plot, bool lines, bool equiAngleLines) {
	double a = 0.5;
	std::vector<bool> change(realNum*imagNum);
	cv::Mat grid(imagNum, realNum, CV_8UC3);
	cv::Vec3b gridc;

	for (int y = 0; y < imagNum; y++) {
		cv::Vec3b* ptr = plot.ptr<cv::Vec3b>(imagNum - y - 1);
		cv::Vec3b* ptr1 = grid.ptr<cv::Vec3b>(imagNum - y - 1);
		double im = imagMin + step * y;

		for (int x = 0; x < realNum; x++) {
			std::complex<double> w = f(std::complex<double>(realMin + step * x, im));
			double arg = std::arg(w);
			double mag = std::abs(w);

			double argn = arg += 2 * PI;
			if (arg < 0)
				arg += 2 * PI;

			double t = std::abs(fmod(argn - PI / 12, PI / 6) - PI / 12);
			double sat = 0.9;
			if (t < 0.02 && equiAngleLines)
				sat = t * 45;
			//small step
			if (lines) {
				t = fmod(w.real() - 0.125 * realNum * step, 0.25 * realNum * step);
				if (t < 0)
					t += 0.25 * realNum * step;
				t -= 0.125 * realNum * step;
				double t1 = fmod(w.imag() + 0.125 * imagNum * step, 0.25 * imagNum * step);
				if (t1 < 0)
					t1 += 0.25 * imagNum * step;
				t1 -= 0.125 * imagNum * step;

				if ((t < 0 && t1 < 0) || (t > 0 && t1 > 0)) {
					gridc[0] = 255;
					gridc[1] = 255;
					gridc[2] = 255;
				}
				else {
					gridc[0] = 0;
					gridc[1] = 0;
					gridc[2] = 0;
				}
				ptr1[x] = gridc;
			}

			//big step
			/*
			if (lines) {
				t = fmod(w.real() - 0.25 * realNum * step, 0.5 * realNum * step);
				if (t < 0)
					t += 0.5 * realNum * step;
				t -= 0.25 * realNum * step;
				double t1 = fmod(w.imag() + 0.25 * imagNum * step, 0.5 * imagNum * step);
				if (t1 < 0)
					t1 += 0.5 * imagNum * step;
				t1 -= 0.25 * imagNum * step;

				if ((t < 0 && t1 < 0) || (t > 0 && t1 > 0)) {
					gridc[0] = 255;
					gridc[1] = 255;
					gridc[2] = 255;
				}
				else {
					gridc[0] = 0;
					gridc[1] = 0;
					gridc[2] = 0;
				}
				ptr1[x] = gridc;
			}
			*/

			//huge step
			/*
			if (lines) {
				t = fmod(w.real() - 0.5 * realNum * step, realNum * step);
				if (t < 0)
					t += realNum * step;
				t -= 0.5 * realNum * step;
				double t1 = fmod(w.imag() + 0.5 * imagNum * step, imagNum * step);
				if (t1 < 0)
					t1 += imagNum * step;
				t1 -= 0.5 * imagNum * step;

				if ((t < 0 && t1 < 0) || (t > 0 && t1 > 0)) {
					gridc[0] = 255;
					gridc[1] = 255;
					gridc[2] = 255;
				}
				else {
					gridc[0] = 0;
					gridc[1] = 0;
					gridc[2] = 0;
				}
				ptr1[x] = gridc;
			}
			*/
			mag = std::log(mag) / std::log(1.5);
			mag = fmod(mag, 1.5);
			if (mag < 0)
				mag += 1.5;
			mag = (mag + 1.5*(1 - sat)) / (2 - sat);
			mag += 1.5;

			double S = sat;
			double V = 1 - std::pow(a, mag);
			double H = 3 * arg / PI;
			cv::Vec3b color;
			color[0] = hsvToRGB(1, H, S, V);
			color[1] = hsvToRGB(3, H, S, V);
			color[2] = hsvToRGB(5, H, S, V);
			ptr[x] = color;
		}
	}

	cv::Mat A, g;
	cv::cvtColor(grid, g, 6);
	cv::Canny(g, A, 0, 255, 3);
	cv::GaussianBlur(A, A, cv::Size((int)(realNum / 500), (int)(realNum / 500)), 0, 0, cv::BORDER_DEFAULT);
	
	for (int y = 0; y < imagNum; y++) {
		cv::Vec3b* ptr = plot.ptr<cv::Vec3b>(imagNum - y - 1);
		for (int x = 0; x < realNum; x++) {
			if (A.data[A.step*(imagNum-y-1)+x] == 0)
				ptr[x] /= 0.85;
		}
	}
	cv::GaussianBlur(plot, plot, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
	return 0;
}

std::complex<double> f(std::complex<double> z) {
	//1. return ((z + 3.0 + 5.0*I)*(z - 7.0*I)*(z - 7.0*I))*((1.0 / z) + (1.0*I / ((z - 5.0 - 3.0*I)*(z - 5.0 - 3.0*I)*(z - 5.0 - 3.0*I))));
	//2. return ((z+1.0)*(z+ std::complex<double>(0, 1.0)))/((z-1.0)*(z-std::complex<double>(0,1.0)));
	//3. return std::exp(1.0 / z);
	//4. return (z*z + 1.0) / (z*z - 1.0);
	//5. return ((z*z - 1.0)*(z - 2.0 - I)*(z - 2.0 - I)) / (z*z + 2.0 + 2.0*I);
	//6. return (std::pow(z, 10) - 1.0) / (std::pow(z, 10) - 0.34867844);
	//7. return z*z+2.0*std::conj(z)+1.0;
	//8. return gamma(z);
	//9. return 1.0/gamma(z);
	//10. return std::asin(z);
	//11. return z + 1.0 / z;
	//12. return std::log(z);
	//13. return (1.0 + z)*(1.0 + 0.445*z + z * z)*(1.0 + 1.247*z + z * z)*(1.0 + 1.8019 * z + z * z);
	//14. return std::sin(z*z*z-1.0)/z;
	return std::sin(z*z) / (z*z);
}

std::complex<double> gamma(std::complex<double> z) {
	if (z.real() < 0.5) {
		return PI / (std::sin(PI*z) * gamma(1.0 - z));
	}
	else {
		z -= 1;
		std::complex<double> x = 0.99999999999980993;
		for (int n = 0; n <= 8; n++) {
			x += p[n] / (z + 1.0 + (double)n);
		}
		std::complex<double> t = z + 8.0 - 0.5;
		return std::sqrt(2 * PI)*std::pow(t, z + 0.5)*std::exp(-t)*x;
	}
}

std::complex<double> bessel_J(int alpha, std::complex<double> z) {
	std::complex<double> w = 1.0+std::cos(alpha*PI);
	double n = 100; //gives error on the order of magnitude of around 1e-8 for |z|<20
	double theta = 0;

	for (int i = 1; i < n; i++) {
		theta = i * PI / n;
		if (i % 2 == 1) {
			w += 4.0*std::cos(alpha*theta - z * std::sin(theta));
		}
		else {
			w += 2.0*std::cos(alpha*theta - z * std::sin(theta));
		}
	}
	w /= (3*n);
	return w;
}

int hsvToRGB(int n, double H, double S, double V) {
	double k = fmod(n + H, 6);
	return (int)(255.0*(V - V * S * std::max(std::min(std::min(k, 4 - k), 1.0), 0.0)));
}