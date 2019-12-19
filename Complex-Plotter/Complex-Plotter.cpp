#include "pch.h"
#include "opencv2/opencv.hpp"
#include "interpretFunction.h"
#include <string.h>
#include <complex>
#include <math.h>
#include <time.h>

int plot_func(int realNum, int imagNum, double realMin, double imagMin, double step, bool equiAngleLines, int lineType, bool axis, cv::Mat& plot);
int hsvToRGB(int n, double H, double S, double V);

int main(int argc, char *argv[])
{
	double realMin = -1, imagMin = -1, realMax = 1, imagMax = 1;
	double step = 2/3840.0;
	bool equiAngleLines = false, axis = false;
	int lineType = -1; //only -1, 0, 1, 2
	std::string func = "z";
	std::string name = "saved";
	bool help = false;

	//Parsing Command Line Arguments
	for (int i = 1; i < argc; i++) {
		if (!std::strcmp(argv[i], "-realMin") || !std::strcmp(argv[i], "-a"))
			realMin = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-realMax") || !std::strcmp(argv[i], "-b"))
			realMax = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-imagMin") || !std::strcmp(argv[i], "-c"))
			imagMin = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-imagMax") || !std::strcmp(argv[i], "-d"))
			imagMax = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-step") || !std::strcmp(argv[i], "-s"))
			step = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-name") || !std::strcmp(argv[i], "-n"))
			name = argv[i + 1];
		else if (!std::strcmp(argv[i], "-axes") || !std::strcmp(argv[i], "-x")) {
			if (!std::strcmp(argv[i + 1], "t")) {
				axis = true;
			}
			if (!std::strcmp(argv[i + 1], "f")) {
				axis = false;
			}
		}
		else if (!std::strcmp(argv[i], "-help") || !std::strcmp(argv[i], "-h")) {
			help = true;
			std::cout << "Command Line Arguments: " << std::endl;
			std::cout << "\t-help (-h)" << std::endl;
			std::cout << "\t-realMin (-a) [decimal number]" << std::endl;
			std::cout << "\t-realMax (-b) [decimal number]" << std::endl;
			std::cout << "\t-imagMin (-c) [decimal number]" << std::endl;
			std::cout << "\t-imagMax (-d) [decimal number]" << std::endl;
			std::cout << "\t-step (-s) [decimal number]" << std::endl;
			std::cout << "\t-grid (-g) [f/s/m/b]" << std::endl;
			std::cout << "\t-angleLines (-l) [t/f]" << std::endl;
			std::cout << "\t-axes (-x) [t/f]" << std::endl;
			std::cout << "\t-name (-n) [string name]" << std::endl;
			std::cout << "\t-func (-f) [function expression]" << std::endl;
			std::cout << "\nFor more information about how to use the arguments and other features of the program, visit https://github.com/pateldhairya0328/Complex-Plotter" << std::endl;
		}
		else if (!std::strcmp(argv[i], "-grid") || !std::strcmp(argv[i], "-g")) {
			if (!std::strcmp(argv[i + 1], "f")) {
				lineType = -1;
			}
			else if (!std::strcmp(argv[i + 1], "s")) {
				lineType = 0;
			}
			else if (!std::strcmp(argv[i + 1], "m")) {
				lineType = 1;
			}
			else if (!std::strcmp(argv[i + 1], "b")) {
				lineType = 2;
			}
		}
		else if (!std::strcmp(argv[i], "-angleLines") || !std::strcmp(argv[i], "-l")) {
			if (!std::strcmp(argv[i + 1], "f")) {
				equiAngleLines = false;
			}
			if (!std::strcmp(argv[i + 1], "t")) {
				equiAngleLines = true;
			}
		}
		else if (!std::strcmp(argv[i], "-func") || !std::strcmp(argv[i], "-f")) {
			func = argv[i + 1];
		}
	}

	if (help) {
		return 0;
	}

	const int realNum = (int)((realMax - realMin) / step);
	const int imagNum = (int)((imagMax - imagMin) / step);

	//Writing the processed arguments to console so user can verify
	std::cout << "Input Function: " << func << std::endl;
	std::cout << "Domain: [" << realMin << ", " << realMax << "]x[" << imagMin << ", " << imagMax << "]"<< std::endl;
	std::cout << "Step: " << step << "; # Pixels real: "<< realNum << "; # Pixels imag: " << imagNum << std::endl;
	std::cout << "Grid: " << ((lineType != -1) ? "true" : "false") << "; Equal Angle lines: " << (equiAngleLines ? "true" : "false") << "; Axes: " << (axis ? "true" : "false") << std::endl;

	//Initializing the Function Interpreter to set up postfix expression of function
	initFunc(func);

	//Making and saving the plot
	cv::Mat plot(imagNum, realNum, CV_8UC3);
	clock_t t = clock();
	plot_func(realNum, imagNum, realMin, imagMin, step, equiAngleLines, lineType, axis, plot);

	//Writing out time it took to complete the plot in milliseconds
	std::cout << (float)(clock() - t) << " ms";
	cv::imwrite(name+".png", plot);

	return 0;
}

//Calculates every pixel's RGB value and saves it into the matrix plot
int plot_func(int realNum, int imagNum, double realMin, double imagMin, double step, bool equiAngleLines, int lineType, bool axis, cv::Mat& plot) {
	cv::Mat grid(imagNum, realNum, CV_8UC3);
	cv::Vec3b gridc;

	for (int y = 0; y < imagNum; y++) {
		cv::Vec3b* ptr = plot.ptr<cv::Vec3b>(imagNum - y - 1);
		cv::Vec3b* ptr1 = grid.ptr<cv::Vec3b>(imagNum - y - 1);
		double im = imagMin + step * y;

		for (int x = 0; x < realNum; x++) {
			//evaluate function
			std::complex<double> w = f(std::complex<double>(realMin + step * x, im));
			double arg = std::arg(w);
			double mag = std::abs(w);

			//positive mod of argument
			double argn = arg += 2 * PI;
			if (arg < 0)
				arg += 2 * PI;

			//decreases the saturation near regions where the argument is close to a multiple of pi/6
			double t = std::abs(fmod(argn - PI / 12, PI / 6) - PI / 12);
			double sat = 0.9;
			if (t < 0.02 && equiAngleLines)
				sat = t * 45;

			//makes black and white grid
			//small step
			if (lineType == 0) {
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

			//medium step
			if (lineType == 1) {
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

			//big step
			if (lineType == 2) {
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

			mag = std::log(mag) / std::log(1.5);
			mag = fmod(mag, 1.5);
			if (mag < 0)
				mag += 1.5;
			mag = (mag + 1.5*(1 - sat)) / (2 - sat);
			mag += 1.5;

			//Saturation, Value, Hue
			double S = sat;
			double V = 1 - std::pow(0.5, mag);//0.5 is just a magic number, can choose numbers in (0,1) for varying gradients of values
			double H = 3 * arg / PI;
			cv::Vec3b color;
			color[0] = hsvToRGB(1, H, S, V);
			color[1] = hsvToRGB(3, H, S, V);
			color[2] = hsvToRGB(5, H, S, V);
			ptr[x] = color;
		}
	}

	if (lineType != -1) {
		//Edge detects checkerboard pattern, and then widens the edges using a blur
		cv::Mat A, g;
		cv::cvtColor(grid, g, 6);
		cv::Canny(g, A, 0, 255, 3);
		cv::GaussianBlur(A, A, cv::Size((int)(realNum / 500), (int)(realNum / 500)), 0, 0, cv::BORDER_DEFAULT);

		//Makes regions where an edge should appear darker
		for (int y = 0; y < imagNum; y++) {
			cv::Vec3b* ptr = plot.ptr<cv::Vec3b>(imagNum - y - 1);
			for (int x = 0; x < realNum; x++) {
				if (A.data[A.step*(imagNum - y - 1) + x] == 0)
					ptr[x] /= 0.85;
			}
		}
		cv::GaussianBlur(plot, plot, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
	}

	if (axis) {
		double axisStep = step * realNum / 10.0;
		double scale = std::pow(10.0, std::ceil(std::log10(std::abs(axisStep))) + 1);
		axisStep = std::round(axisStep*2*scale) / (2*scale * step);
		double x = std::round(realMin * 2 * scale) / (2 * scale);
		if (x == realMin) {
			x += axisStep * step;
		}

		for (x = (x - realMin) / step; x < realNum; x += axisStep) {
			cv::line(plot, cv::Point(0, x), cv::Point(imagNum - 1, x), cv::Scalar(50, 50, 50), std::round(realNum/1000.0));
		}
		
		axisStep = step * imagNum / 10.0;
		scale = std::pow(10.0, std::ceil(std::log10(std::abs(axisStep))) + 1);
		axisStep = std::round(axisStep * 2 * scale) / (2 * scale * step);
		x = std::round(imagMin * 2 * scale) / (2 * scale * step);
		if (x == realMin) {
			x += axisStep * step;
		}

		for (x = (x - imagMin) / step; x < imagNum; x += axisStep) {
			cv::line(plot, cv::Point(x, 0), cv::Point(x, realNum - 1), cv::Scalar(50, 50, 50), std::round(imagNum / 1000.0));
		}
	}

	return 0;
}

//Converts HSV to one of R, G or B based on argument n
//Conversion done as per the process on https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
int hsvToRGB(int n, double H, double S, double V) {
	double k = fmod(n + H, 6);
	return (int)(255.0*(V - V * S * std::max(std::min(std::min(k, 4 - k), 1.0), 0.0)));
}

//Test Cases

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