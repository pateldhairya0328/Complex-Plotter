#include "pch.h"
#include "opencv2/opencv.hpp"
#include "interpretFunction.h"
#include <string.h>
#include <complex>
#include <math.h>
#include <time.h>

int plot_func(int realNum, int imagNum, double realMin, double imagMin, double xstep, double ystep, bool equiAngleLines, int lineType, bool axis, int colorScheme, cv::Mat& plot);
int hsvToRGB(int n, double H, double S, double V);
cv::Vec3b getColor(int colorScheme, double sat, double mag, double arg);
float colormap[257][3] = { {255.0, 12.68, 24.52}, {255.0, 15.37, 20.91}, {255.0, 18.39, 17.63}, {255.0, 21.74, 14.69}, {255.0, 25.42, 12.09}, {255.0, 24.56, 12.09}, {255.0, 28.57, 9.83}, {255.0, 32.88, 7.88}, {255.0, 37.48, 6.23}, {255.0, 42.33, 4.85}, {255.0, 47.41, 3.72}, {255.0, 52.68, 2.81}, {255.0, 58.11, 2.08}, {255.0, 63.68, 1.52}, {255.0, 69.36, 1.08}, {255.0, 75.13, 0.76}, {255.0, 80.95, 0.51}, {255.0, 86.83, 0.34}, {255.0, 92.74, 0.22}, {255.0, 98.68, 0.13}, {255.0, 104.64, 0.07}, {255.0, 110.61, 0.04}, {255.0, 116.59, 0.01}, {255.0, 122.57, 0.0}, {255.0, 128.55, 0.0}, {255.0, 134.54, 0.0}, {255.0, 140.52, 0.0}, {255.0, 146.49, 0.0}, {255.0, 152.45, 0.0}, {255.0, 158.39, 0.0}, {255.0, 164.31, 0.0}, {255.0, 170.2, 0.0}, {254.88, 176.04, 0.0}, {254.66, 181.82, 0.0}, {254.37, 187.53, 0.0}, {253.98, 193.14, 0.0}, {253.47, 198.63, 0.0}, {252.81, 203.97, 0.0}, {251.97, 209.15, 0.0}, {250.92, 214.12, 0.0}, {249.64, 218.85, 0.0}, {248.09, 223.33, 0.0}, {246.25, 227.52, 0.0}, {244.09, 231.41, 0.0}, {241.61, 234.97, 0.0}, {238.79, 238.19, 0.0}, {235.63, 241.07, 0.0}, {232.13, 243.61, 0.0}, {228.31, 245.82, 0.0}, {224.17, 247.71, 0.0}, {219.74, 249.32, 0.0}, {215.04, 250.65, 0.0}, {210.11, 251.74, 0.0}, {204.97, 252.62, 0.0}, {199.65, 253.31, 0.0}, {194.19, 253.86, 0.0}, {188.6, 254.27, 0.0}, {182.91, 254.58, 0.0}, {177.14, 254.81, 0.0}, {171.31, 254.97, 0.0}, {165.43, 255.0, 0.0}, {159.52, 255.0, 0.0}, {153.59, 255.0, 0.0}, {147.64, 255.0, 0.0}, {141.67, 255.0, 0.0}, {135.7, 255.0, 0.0}, {129.72, 255.0, 0.0}, {123.73, 255.0, 0.0}, {117.75, 255.0, 0.0}, {111.78, 255.0, 0.0}, {105.81, 255.0, 0.02}, {99.86, 255.0, 0.05}, {93.93, 255.0, 0.1}, {88.03, 255.0, 0.17}, {82.17, 255.0, 0.29}, {76.35, 255.0, 0.45}, {70.61, 255.0, 0.67}, {64.95, 255.0, 0.98}, {59.39, 255.0, 1.39}, {53.97, 255.0, 1.93}, {48.71, 255.0, 2.62}, {43.64, 255.0, 3.49}, {38.78, 255.0, 4.58}, {34.17, 255.0, 5.91}, {29.83, 255.0, 7.51}, {25.8, 255.0, 9.4}, {22.07, 255.0, 11.61}, {18.68, 255.0, 14.14}, {15.63, 255.0, 17.02}, {12.92, 255.0, 20.24}, {10.55, 255.0, 23.79}, {8.5, 255.0, 27.67}, {6.75, 255.0, 31.86}, {5.28, 255.0, 36.33}, {4.07, 255.0, 41.07}, {3.09, 255.0, 46.03}, {2.31, 255.0, 51.2}, {1.69, 255.0, 56.54}, {1.21, 255.0, 62.03}, {0.85, 255.0, 67.64}, {0.59, 255.0, 73.34}, {0.39, 255.0, 79.12}, {0.25, 255.0, 84.96}, {0.15, 255.0, 90.84}, {0.09, 255.0, 96.75}, {0.05, 255.0, 102.69}, {0.02, 255.0, 108.64}, {0.01, 255.0, 114.61}, {0.0, 255.0, 120.59}, {0.0, 255.0, 126.57}, {0.0, 255.0, 132.55}, {0.0, 255.0, 138.53}, {0.0, 255.0, 144.5}, {0.0, 255.0, 150.47}, {0.0, 255.0, 156.41}, {0.0, 255.0, 162.34}, {0.0, 255.0, 168.24}, {0.0, 254.93, 174.09}, {0.0, 254.73, 179.9}, {0.0, 254.47, 185.63}, {0.0, 254.11, 191.27}, {0.0, 253.64, 196.8}, {0.0, 253.03, 202.2}, {0.0, 252.25, 207.43}, {0.0, 251.27, 212.47}, {0.0, 250.06, 217.29}, {0.0, 248.6, 221.85}, {0.0, 246.86, 226.14}, {0.0, 244.81, 230.13}, {0.0, 242.44, 233.8}, {0.0, 239.73, 237.13}, {0.0, 236.69, 240.13}, {0.0, 233.3, 242.78}, {0.0, 229.58, 245.1}, {0.0, 225.55, 247.1}, {0.0, 221.21, 248.8}, {0.0, 216.61, 250.22}, {0.0, 211.75, 251.39}, {0.0, 206.68, 252.34}, {0.0, 201.43, 253.09}, {0.0, 196.01, 253.68}, {0.0, 190.46, 254.14}, {0.0, 184.8, 254.48}, {0.0, 179.06, 254.74}, {0.0, 173.25, 254.92}, {0.0, 167.39, 255.0}, {0.0, 161.49, 255.0}, {0.0, 155.57, 255.0}, {0.0, 149.62, 255.0}, {0.0, 143.66, 255.0}, {0.0, 137.69, 255.0}, {0.0, 131.71, 255.0}, {0.0, 125.73, 255.0}, {0.0, 119.75, 255.0}, {0.0, 113.77, 255.0}, {0.01, 107.8, 255.0}, {0.04, 101.84, 255.0}, {0.08, 95.9, 255.0}, {0.15, 89.99, 255.0}, {0.24, 84.11, 255.0}, {0.39, 78.28, 255.0}, {0.59, 72.51, 255.0}, {0.87, 66.81, 255.0}, {1.24, 61.22, 255.0}, {1.73, 55.75, 255.0}, {2.37, 50.43, 255.0}, {3.18, 45.28, 255.0}, {4.19, 40.35, 255.0}, {5.44, 35.65, 255.0}, {6.94, 31.22, 255.0}, {8.74, 27.07, 255.0}, {10.84, 23.24, 255.0}, {13.26, 19.74, 255.0}, {16.02, 16.57, 255.0}, {19.13, 13.75, 255.0}, {22.57, 11.27, 255.0}, {26.34, 9.11, 255.0}, {30.43, 7.27, 255.0}, {34.81, 5.71, 255.0}, {39.46, 4.42, 255.0}, {44.36, 3.37, 255.0}, {49.46, 2.53, 255.0}, {54.75, 1.86, 255.0}, {60.19, 1.35, 255.0}, {65.76, 0.95, 255.0}, {71.43, 0.66, 255.0}, {77.19, 0.44, 255.0}, {83.01, 0.29, 255.0}, {88.87, 0.18, 255.0}, {94.78, 0.11, 255.0}, {100.71, 0.06, 255.0}, {106.66, 0.03, 255.0}, {112.62, 0.01, 255.0}, {118.59, 0.0, 255.0}, {124.57, 0.0, 255.0}, {130.56, 0.0, 255.0}, {136.54, 0.0, 255.0}, {142.51, 0.0, 255.0}, {148.48, 0.0, 255.0}, {154.44, 0.0, 255.0}, {160.37, 0.0, 255.0}, {166.28, 0.0, 255.0}, {172.15, 0.0, 254.98}, {177.97, 0.0, 254.81}, {183.73, 0.0, 254.57}, {189.41, 0.0, 254.24}, {194.98, 0.0, 253.81}, {200.43, 0.0, 253.25}, {205.72, 0.0, 252.53}, {210.83, 0.0, 251.62}, {215.72, 0.0, 250.49}, {220.38, 0.0, 249.12}, {224.76, 0.0, 247.47}, {228.85, 0.0, 245.53}, {232.63, 0.0, 243.27}, {236.08, 0.0, 240.67}, {239.18, 0.0, 237.74}, {241.95, 0.0, 234.47}, {244.38, 0.0, 230.86}, {246.48, 0.0, 226.93}, {248.28, 0.0, 222.69}, {249.79, 0.0, 218.17}, {251.04, 0.0, 213.4}, {252.06, 0.0, 208.4}, {252.87, 0.0, 203.2}, {253.51, 0.0, 197.83}, {254.01, 0.0, 192.32}, {254.38, 0.0, 186.7}, {254.67, 0.0, 180.98}, {254.87, 0.0, 175.2}, {255.0, 0.0, 169.35}, {255.0, 0.0, 163.46}, {255.0, 0.0, 157.55}, {255.0, 0.0, 151.61}, {255.0, 0.0, 145.65}, {255.0, 0.0, 139.68}, {255.0, 0.0, 133.7}, {255.0, 0.0, 127.72}, {255.0, 0.0, 121.74}, {255.0, 0.0, 115.76}, {255.0, 0.03, 109.79}, {255.0, 0.06, 103.83}, {255.0, 0.12, 97.88}, {255.0, 0.21, 91.96}, {255.0, 0.34, 86.07}, {255.0, 0.53, 80.22}, {255.0, 0.78, 74.43}, {255.0, 1.13, 68.71}, {255.0, 1.6, 63.08}, {255.0, 2.2, 57.57}, {255.0, 2.97, 52.2}, {255.0, 3.94, 47.0}, {255.0, 5.13, 41.99}, {255.0, 6.58, 37.22}, {255.0, 8.3, 32.69}, {255.0, 10.33, 28.45}, {255.0, 12.68, 24.52} };

int main(int argc, char *argv[])
{
	double realMin = -1, imagMin = -1, realMax = 1, imagMax = 1;
	double step = 2/3840.0, xstep = -1, ystep = -1;
	bool ystepmod = false, xstepmod = false;
	bool equiAngleLines = false, axis = false;
	int colorScheme = 0;
	int lineType = -1; //only -1, 0, 1, 2
	std::string func = "z";
	std::string name = "saved";
	bool help = false;
	std::string temp = "";

	if (argc == 1) {
		std::cout << "Enter Function: ";
		std::cin >> func;
		std::cout << "\nDomain Parameters" << std::endl;
		std::cout << "Enter real min: ";
		std::cin >> realMin;
		std::cout << "Enter real max: ";
		std::cin >> realMax;
		std::cout << "Enter imag min: ";
		std::cin >> imagMin;
		std::cout << "Enter imag max: ";
		std::cin >> imagMax;
		std::cout << "\nPlot Parameters" << std::endl;
		std::cout << "x-step: ";
		std::cin >> xstep;
		xstepmod = true;
		std::cout << "y-step: ";
		std::cin >> ystep;
		ystepmod = true;
		std::cout << "Lines of constant real and imaginary components (f/s/m/b)?: ";
		std::cin >> temp;
		if (temp=="f") {
			lineType = -1;
		}
		else if (temp == "s") {
			lineType = 0;
		}
		else if (temp == "m") {
			lineType = 1;
		}
		else if (temp == "b") {
			lineType = 2;
		}
		std::cout << "Equal phase lines (t/f)?: ";
		std::cin >> temp;
		equiAngleLines = temp == "t" ? true : false;
		std::wcout << "Grid Parallel to axes lines (t/f)?: ";
		std::cin >> temp;
		axis = temp == "t" ? true : false;
		std::cout << "Use the smooth (s) or regular HSV (h) color scheme: ";
		std::cin >> temp;
		if (temp == "s") {
			colorScheme = 0;
		}
		else if (temp == "h") {
			colorScheme = 1;
		}
		std::cout << "\nFile name (Do NOT include file type like .png): ";
		std::cin >> name;
	}

	//Parsing Command Line Arguments
	for (int i = 1; i < argc; i++) {
		if (!std::strcmp(argv[i], "-realMin") || !std::strcmp(argv[i], "-x1"))
			realMin = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-realMax") || !std::strcmp(argv[i], "-x2"))
			realMax = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-imagMin") || !std::strcmp(argv[i], "-y1"))
			imagMin = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-imagMax") || !std::strcmp(argv[i], "-y2"))
			imagMax = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-step") || !std::strcmp(argv[i], "-s"))
			step = std::strtod(argv[i + 1], 0);
		else if (!std::strcmp(argv[i], "-xstep") || !std::strcmp(argv[i], "-xs")) {
			xstepmod = true;
			xstep = std::strtod(argv[i + 1], 0);
		}
		else if (!std::strcmp(argv[i], "-ystep") || !std::strcmp(argv[i], "-ys")) {
			ystepmod = true;
			ystep = std::strtod(argv[i + 1], 0);
		}
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
			std::cout << "\t-xstep (-xs) [decimal number]" << std::endl;
			std::cout << "\t-ystep (-ys) [decimal number]" << std::endl;
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
		else if (!std::strcmp(argv[i], "-cScheme") || !std::strcmp(argv[i], "-c")) {
			if (!std::strcmp(argv[i + 1], "s")) {
				colorScheme = 0;
			}
			else if (!std::strcmp(argv[i + 1], "h")) {
				colorScheme = 1;
			}
		}
	}

	if (help) {
		return 0;
	}

	if (!xstepmod) {
		xstep = step;
	}
	if (!ystepmod) {
		ystep = step;
	}

	const int realNum = std::round(((realMax - realMin) / xstep));
	const int imagNum = std::round(((imagMax - imagMin) / ystep));

	//Writing the processed arguments to console so user can verify
	std::cout << "Input Function: " << func << std::endl;
	std::cout << "Domain: [" << realMin << ", " << realMax << "]x[" << imagMin << ", " << imagMax << "]"<< std::endl;
	std::cout << "x-step: " << xstep << "; y-step: " << ystep << "; # Pixels real: "<< realNum << "; # Pixels imag: " << imagNum << std::endl;
	std::cout << "Grid: " << ((lineType != -1) ? "true" : "false") << "; Equal Angle lines: " << (equiAngleLines ? "true" : "false") << "; Axes: " << (axis ? "true" : "false") << std::endl;

	//Initializing the Function Interpreter to set up postfix expression of function
	setStep(std::max(xstep, ystep));
	initFunc(func);
	std::cout << std::endl;

	//Making and saving the plot
	cv::Mat plot(imagNum, realNum, CV_8UC3);
	clock_t t = clock();
	plot_func(realNum, imagNum, realMin, imagMin, xstep, ystep, equiAngleLines, lineType, axis, colorScheme, plot);

	//Writing out time it took to complete the plot in milliseconds
	std::cout << "Time taken: " << (float)(clock() - t) << " ms" << std::endl;
	std::cout << "Saving...";
	cv::imwrite(name+".png", plot);
	std::cout << "\rPlot saved as " << name << ".png" << std::endl;

	return 0;
}

//Calculates every pixel's RGB value and saves it into the matrix plot
int plot_func(int realNum, int imagNum, double realMin, double imagMin, double xstep, double ystep, bool equiAngleLines, int lineType, bool axis, int colorScheme, cv::Mat& plot) {
	cv::Mat grid(imagNum, realNum, CV_8UC1);
	cv::Mat A;

	double meanVal = 0, max = std::abs(f(std::complex<double>(realMin, imagMin))), min = max;
	int n = 0;

	clock_t time = clock();
	//Find an approximate average value for the function over the region in order to find an appropriate grid size
	for (int y = 0; y <= imagNum; y+=imagNum/10) {
		double im = imagMin + ystep * y;
		for (int x = 0; x <= realNum; x+=realNum/10) {
			double w = std::abs(f(std::complex<double>(realMin + xstep * x, im)));
			if (!std::isnan(w)) {
				meanVal += w;
				if (w > max) {
					max = w;
				}
				if (w < min) {
					min = w;
				}
				n++;
			}
		}
	}

	meanVal = 0.5 * (meanVal - max - min) / n;

	//declaring some variabless we will use
	std::complex<double> w;
	double arg = 0, mag = 1, im = 0, argn = 0, temp = 0, temp1 = 0, sat = 0;

	//higher value of linetype means larger value of modval, which means the end grid is more separated
	double modVal = meanVal * std::pow(2, lineType - 2), modVal2 = modVal / 2.0; 

	for (int y = 0; y < imagNum; y++) {
		cv::Vec3b* ptr = plot.ptr<cv::Vec3b>(imagNum - y - 1);
		im = imagMin + ystep * y;

		for (int x = 0; x < realNum; x++) {
			//evaluate function
			w = f(std::complex<double>(realMin + xstep * x, im));
			if (!std::isnan(std::abs(w))) {
				arg = std::arg(w);
				mag = std::abs(w);
			}

			//positive mod of argument
			argn = arg + 2 * PI;
			if (arg < 0)
				arg += 2 * PI;

			//decreases the saturation near regions where the argument is close to a multiple of pi/6
			temp = std::abs(fmod(argn - PI / 12, PI / 6) - PI / 12);
			sat = 0.9;
			if (temp < 0.02 && equiAngleLines)
				sat = temp * 45;

			//makes black and white checkerboard, which will be used to make the grid later on
			if (lineType != -1) {
				temp = fmod(w.real() - modVal2, modVal);
				if (temp < 0)
					temp += modVal;
				temp -= modVal2;
				temp1 = fmod(w.imag() - modVal2, modVal);
				if (temp1 < 0)
					temp1 += modVal;
				temp1 -= modVal2;

				if (temp * temp1 > 0) {
					grid.at<uchar>(imagNum - y - 1, x) = 255;
				}
				else {
					grid.at<uchar>(imagNum - y - 1, x) = 0;
				}
			}

			//work with mod of log of the magnitude, as it allows for a larger range of magnitudes
			//to be easily distinguished in the final plot
			mag = std::log(mag) / std::log(1.5);
			mag = fmod(mag, 1.5);
			if (mag < 0)
				mag += 1.5;

			mag = (mag + 1.5 * (1 - sat)) / (2 - sat);
			mag += 1.5;

			ptr[x] = getColor(colorScheme, sat, mag, arg);
		}
		if (y % (imagNum/100) == 0) {
			std::cout << "\rProgress: " << 100 * y / imagNum << "%\t\u2502";
			for (int k = 0; k < 20; k++) {
				std::cout << (k < 20 * y / imagNum ? "\u2588": " ");
			}
			std::cout << "\u2502     ; Time so far: " << (float)(clock() - time) << " ms     ";
		}
	}

	if (lineType != -1) {
		//Edge detects checkerboard pattern, and then widens the edges using a blur
		int kernelSize = std::min(realNum, imagNum) / 500;
		if (kernelSize % 2 == 0) {
			kernelSize += 1;
		}

		cv::Mat A;
		//cv::GaussianBlur(grid, grid, cv::Size(kernelSize * 2 + 1, kernelSize * 2 + 1), 0, 0, cv::BORDER_DEFAULT);
		cv::Canny(grid, A, 0, 50, 3);
		cv::GaussianBlur(A, A, cv::Size(kernelSize, kernelSize), 0, 0, cv::BORDER_DEFAULT);

		//Makes regions where an edge is appear darker
		for (int y = 0; y < A.rows; y++) {
			cv::Vec3b* ptr = plot.ptr<cv::Vec3b>(y);
			const unsigned char* row = A.ptr<unsigned char>(y);
			for (int x = 0; x < A.cols; x++) {
				if (row[x] == 0) {
					ptr[x] /= 0.85;
				}
			}
		}
		
		cv::GaussianBlur(plot, plot, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
	}

	if (axis) {
		double axisStep = xstep * realNum / 10.0;
		double scale = std::pow(10.0, std::ceil(std::log10(std::abs(axisStep))) + 1);
		axisStep = std::round(axisStep*2*scale) / (2*scale * xstep);
		double x = std::round(realMin * 2 * scale) / (2 * scale);
		if (x == realMin) {
			x += axisStep * xstep;
		}

		for (x = (x - realMin) / xstep; x < realNum; x += axisStep) {
			cv::line(plot, cv::Point(0, x), cv::Point(imagNum - 1, x), cv::Scalar(50, 50, 50), std::round(realNum/1000.0));
		}
		
		axisStep = ystep * imagNum / 10.0;
		scale = std::pow(10.0, std::ceil(std::log10(std::abs(axisStep))) + 1);
		axisStep = std::round(axisStep * 2 * scale) / (2 * scale * ystep);
		x = std::round(imagMin * 2 * scale) / (2 * scale * ystep);
		if (x == realMin) {
			x += axisStep * ystep;
		}

		for (x = (x - imagMin) / ystep; x < imagNum; x += axisStep) {
			cv::line(plot, cv::Point(x, 0), cv::Point(x, realNum - 1), cv::Scalar(50, 50, 50), std::round(imagNum / 1000.0));
		}
	}

	std::cout << "\rProgress: 100%\t\u2502\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2502" << std::endl;

	return 0;
}

cv::Vec3b getColor(int colorScheme, double sat, double mag, double arg) {
	if (colorScheme == 0) {
		//Saturation, Value, Hue
		float S = sat;
		float V = 1 - std::pow(0.5, mag);//0.5 is just a magic number, can choose numbers in (0,1) for varying gradients of values
		float H = 128 * arg / PI;
		int HLo = std::floor(H), HHi = std::ceil(H);

		//Explanation of how the color is calculated
		//(HHi - H) * colormap[HLo] + (H - HLo) * colormap[HHi] linearly interpolates the color associated with the hue 
		//From the look up table of colors
		//S * color + (1 - S) * 255 finds the weighted average of the color and white, with the color being whiter as 
		//the value of S goes down (so higher S results in a more saturated color, S = 1 is most saturated)
		//V * color at the end averages the color with black (the (1 - V) * 0 is always 0 so it is left out), so the color 
		//becomes blacker as the value decreases

		//The color is converted to HSV in this method instead of a more typical HSV to RGB conversion since the normal
		//method results in a very perceptually uneven output (there are visible streaks at yellow, cyan and magenta). 
		//This method instead uses a lookup table of values which are not exactly the correct RGB values, but are a 
		//smoothed out version, which results in a more perceptually smoother plot that will convey less incorrect 
		//information about the plotted data. The HSLuv was not used to create a perceptually uniform colormap, since it
		//looks kinda ugly
		if (HLo != HHi) {
			cv::Vec3b color;
			color[0] = V * (S * ((HHi - H) * colormap[HLo][2] + (H - HLo) * colormap[HHi][2]) + (1 - S) * 255);
			color[1] = V * (S * ((HHi - H) * colormap[HLo][1] + (H - HLo) * colormap[HHi][1]) + (1 - S) * 255);
			color[2] = V * (S * ((HHi - H) * colormap[HLo][0] + (H - HLo) * colormap[HHi][0]) + (1 - S) * 255);
			return color;
		}
		else {
			cv::Vec3b color;
			color[0] = V * (S * colormap[HLo][2] + (1 - S) * 255);
			color[1] = V * (S * colormap[HLo][1] + (1 - S) * 255);
			color[2] = V * (S * colormap[HLo][0] + (1 - S) * 255);
			return color;
		}
	}
	else if (colorScheme == 1) {
		//Saturation, Value, Hue
		double S = sat;
		double V = 1 - std::pow(0.5, mag);//0.5 is just a magic number, can choose numbers in (0,1) for varying gradients of values
		double H = 3 * arg / PI;
		cv::Vec3b color;
		color[0] = hsvToRGB(1, H, S, V);
		color[1] = hsvToRGB(3, H, S, V);
		color[2] = hsvToRGB(5, H, S, V);
		return color;
	}
}

//Converts HSV to one of R, G or B based on argument n
//Conversion done as per the process on https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
int hsvToRGB(int n, double H, double S, double V) {
	double k = fmod(n + H, 6);
	return (int)(255.0 * (V - V * S * std::max(std::min(std::min(k, 4 - k), 1.0), 0.0)));
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