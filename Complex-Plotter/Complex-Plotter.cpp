#include "pch.h"
#include "opencv2/opencv.hpp"
#include "interpretFunction.h"
#include <string.h>
#include <complex>
#include <math.h>
#include <time.h>

int plot_func(int realNum, int imagNum, double realMin, double imagMin, double xstep, double ystep, bool equiAngleLines, int lineType, bool axis, cv::Mat& plot);
float colormap[257][3] = { {254.99, 46.01, 15.71}, {255.0, 49.52, 13.04}, {255.0, 53.29, 10.68}, {255.0, 57.3, 8.64}, {255.0, 61.55, 6.89}, {255.0, 66.01, 5.42}, {255.0, 70.65, 4.19}, {255.0, 75.46, 3.2}, {255.0, 80.4, 2.4}, {255.0, 85.46, 1.76}, {255.0, 90.62, 1.28}, {255.0, 95.86, 0.9}, {255.0, 101.15, 0.62}, {255.0, 106.5, 0.42}, {255.0, 111.88, 0.27}, {255.0, 117.28, 0.17}, {255.0, 122.7, 0.1}, {255.0, 128.14, 0.05}, {255.0, 133.59, 0.02}, {255.0, 139.04, 0.01}, {255.0, 144.5, 0.0}, {255.0, 149.96, 0.0}, {255.0, 155.41, 0.0}, {255.0, 160.84, 0.0}, {255.0, 166.27, 0.0}, {255.0, 171.67, 0.0}, {255.0, 177.05, 0.0}, {254.88, 182.38, 0.0}, {254.66, 187.67, 0.0}, {254.37, 192.88, 0.0}, {253.98, 198.02, 0.0}, {253.47, 203.04, 0.0}, {252.81, 207.94, 0.0}, {251.97, 212.68, 0.0}, {250.92, 217.24, 0.0}, {249.64, 221.59, 0.0}, {248.09, 225.7, 0.0}, {246.25, 229.56, 0.0}, {244.09, 233.14, 0.0}, {241.61, 236.42, 0.0}, {238.79, 239.39, 0.0}, {235.63, 242.05, 0.0}, {232.13, 244.4, 0.0}, {228.31, 246.45, 0.0}, {224.17, 248.21, 0.0}, {219.74, 249.7, 0.0}, {215.04, 250.94, 0.0}, {210.11, 251.96, 0.0}, {204.97, 252.78, 0.0}, {199.65, 253.43, 0.0}, {194.19, 253.94, 0.0}, {188.6, 254.33, 0.0}, {182.91, 254.62, 0.0}, {177.14, 254.83, 0.0}, {171.31, 254.99, 0.0}, {165.43, 255.0, 0.0}, {159.52, 255.0, 0.0}, {153.59, 255.0, 0.0}, {147.64, 255.0, 0.0}, {141.67, 255.0, 0.0}, {135.7, 255.0, 0.0}, {129.72, 255.0, 0.0}, {123.73, 255.0, 0.0}, {117.75, 255.0, 0.0}, {111.78, 255.0, 0.0}, {105.81, 255.0, 0.02}, {99.86, 255.0, 0.05}, {93.93, 255.0, 0.1}, {88.03, 255.0, 0.17}, {82.17, 255.0, 0.29}, {76.35, 255.0, 0.45}, {70.61, 255.0, 0.67}, {64.95, 255.0, 0.98}, {59.39, 255.0, 1.39}, {53.97, 255.0, 1.93}, {48.71, 255.0, 2.62}, {43.64, 255.0, 3.49}, {38.78, 255.0, 4.58}, {34.17, 255.0, 5.91}, {29.83, 255.0, 7.51}, {25.8, 255.0, 9.4}, {22.07, 255.0, 11.61}, {18.68, 255.0, 14.14}, {15.63, 255.0, 17.02}, {12.92, 255.0, 20.24}, {10.55, 255.0, 23.79}, {8.5, 255.0, 27.67}, {6.75, 255.0, 31.86}, {5.28, 255.0, 36.33}, {4.07, 255.0, 41.07}, {3.09, 255.0, 46.03}, {2.31, 255.0, 51.2}, {1.69, 255.0, 56.54}, {1.21, 255.0, 62.03}, {0.85, 255.0, 67.64}, {0.59, 255.0, 73.34}, {0.39, 255.0, 79.12}, {0.25, 255.0, 84.96}, {0.15, 255.0, 90.84}, {0.09, 255.0, 96.75}, {0.05, 255.0, 102.69}, {0.02, 255.0, 108.64}, {0.01, 255.0, 114.61}, {0.0, 255.0, 120.59}, {0.0, 255.0, 126.57}, {0.0, 255.0, 132.55}, {0.0, 255.0, 138.53}, {0.0, 255.0, 144.5}, {0.0, 255.0, 150.47}, {0.0, 255.0, 156.41}, {0.0, 255.0, 162.34}, {0.0, 255.0, 168.24}, {0.0, 254.93, 174.09}, {0.0, 254.73, 179.9}, {0.0, 254.47, 185.63}, {0.0, 254.11, 191.27}, {0.0, 253.64, 196.8}, {0.0, 253.03, 202.2}, {0.0, 252.25, 207.43}, {0.0, 251.27, 212.47}, {0.0, 250.06, 217.29}, {0.0, 248.6, 221.85}, {0.0, 246.86, 226.14}, {0.0, 244.81, 230.13}, {0.0, 242.44, 233.8}, {0.0, 239.73, 237.13}, {0.0, 236.69, 240.13}, {0.01, 233.31, 242.78}, {0.03, 229.61, 245.1}, {0.05, 225.61, 247.1}, {0.1, 221.32, 248.8}, {0.17, 216.78, 250.22}, {0.26, 212.02, 251.39}, {0.4, 207.09, 252.34}, {0.59, 202.02, 253.09}, {0.84, 196.85, 253.68}, {1.17, 191.64, 254.14}, {1.59, 186.41, 254.48}, {2.13, 181.21, 254.74}, {2.81, 176.08, 254.92}, {3.64, 171.05, 255.0}, {4.63, 166.15, 255.0}, {5.82, 161.41, 255.0}, {7.2, 156.86, 255.0}, {8.8, 152.5, 255.0}, {10.61, 148.35, 255.0}, {12.65, 144.41, 255.0}, {14.9, 140.69, 255.0}, {17.36, 137.18, 255.0}, {20.03, 133.87, 255.0}, {22.88, 130.75, 255.0}, {25.9, 127.8, 255.0}, {29.07, 125.01, 255.0}, {32.38, 122.34, 255.0}, {35.8, 119.8, 255.0}, {39.32, 117.34, 255.0}, {42.92, 114.97, 255.0}, {46.58, 112.67, 255.0}, {50.29, 110.41, 255.0}, {54.05, 108.19, 255.0}, {57.83, 106.0, 255.0}, {61.63, 103.84, 255.0}, {65.45, 101.69, 255.0}, {69.28, 99.55, 255.0}, {73.12, 97.43, 255.0}, {76.96, 95.3, 255.0}, {80.81, 93.18, 255.0}, {84.66, 91.06, 255.0}, {88.52, 88.95, 255.0}, {92.37, 86.83, 255.0}, {96.22, 84.71, 255.0}, {100.07, 82.6, 255.0}, {103.92, 80.48, 255.0}, {107.77, 78.36, 255.0}, {111.62, 76.24, 255.0}, {115.47, 74.13, 255.0}, {119.32, 72.01, 255.0}, {123.17, 69.89, 255.0}, {127.02, 67.78, 255.0}, {130.88, 65.66, 255.0}, {134.73, 63.54, 255.0}, {138.58, 61.42, 255.0}, {142.43, 59.31, 255.0}, {146.28, 57.19, 255.0}, {150.13, 55.07, 255.0}, {153.98, 52.95, 255.0}, {157.83, 50.84, 255.0}, {161.68, 48.72, 255.0}, {165.53, 46.6, 255.0}, {169.38, 44.49, 255.0}, {173.24, 42.37, 255.0}, {177.08, 40.25, 255.0}, {180.93, 38.14, 255.0}, {184.76, 36.04, 255.0}, {188.58, 33.94, 255.0}, {192.39, 31.86, 255.0}, {196.18, 29.79, 255.0}, {199.93, 27.74, 254.9}, {203.65, 25.72, 254.7}, {207.32, 23.74, 254.42}, {210.93, 21.8, 254.05}, {214.46, 19.93, 253.57}, {217.89, 18.12, 252.94}, {221.22, 16.39, 252.14}, {224.42, 14.76, 251.15}, {227.46, 13.24, 249.93}, {230.35, 11.84, 248.46}, {233.05, 10.58, 246.71}, {235.55, 9.46, 244.67}, {237.85, 8.5, 242.32}, {239.94, 7.69, 239.65}, {241.82, 7.05, 236.65}, {243.48, 6.56, 233.33}, {244.94, 6.22, 229.71}, {246.2, 6.03, 225.78}, {247.28, 5.97, 221.58}, {248.2, 6.03, 217.13}, {248.97, 6.21, 212.45}, {249.61, 6.48, 207.58}, {250.13, 6.84, 202.54}, {250.57, 7.26, 197.36}, {250.93, 7.74, 192.06}, {251.22, 8.27, 186.66}, {251.47, 8.84, 181.19}, {251.67, 9.43, 175.66}, {251.85, 10.04, 170.09}, {252.01, 10.68, 164.49}, {252.15, 11.32, 158.86}, {252.28, 11.97, 153.22}, {252.4, 12.62, 147.56}, {252.52, 13.28, 141.9}, {252.63, 13.95, 136.23}, {252.74, 14.61, 130.56}, {252.85, 15.28, 124.88}, {252.96, 15.94, 119.21}, {253.07, 16.61, 113.54}, {253.19, 17.28, 107.87}, {253.3, 17.97, 102.21}, {253.41, 18.66, 96.56}, {253.52, 19.38, 90.93}, {253.63, 20.12, 85.32}, {253.73, 20.9, 79.75}, {253.84, 21.73, 74.22}, {253.95, 22.62, 68.75}, {254.05, 23.59, 63.35}, {254.16, 24.66, 58.04}, {254.26, 25.85, 52.86}, {254.36, 27.18, 47.81}, {254.45, 28.68, 42.94}, {254.55, 30.37, 38.26}, {254.63, 32.29, 33.8}, {254.71, 34.43, 29.6}, {254.79, 36.84, 25.67}, {254.86, 39.51, 22.04}, {254.93, 42.47, 18.71}, {254.99, 45.7, 15.71}, {254.99, 46.01, 15.71} };

int main(int argc, char *argv[])
{
	double realMin = -1, imagMin = -1, realMax = 1, imagMax = 1;
	double step = 2/3840.0, xstep = -1, ystep = -1;
	bool ystepmod = false, xstepmod = false;
	bool equiAngleLines = false, axis = false;
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
		std::cout << "\nFile name (Do NOT include file type like .png): ";
		std::cin >> name;
	}

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
	plot_func(realNum, imagNum, realMin, imagMin, xstep, ystep, equiAngleLines, lineType, axis, plot);

	//Writing out time it took to complete the plot in milliseconds
	std::cout << "Time taken: " << (float)(clock() - t) << " ms" << std::endl;
	std::cout << "Saving...";
	cv::imwrite(name+".png", plot);
	std::cout << "\rPlot saved as " << name << ".png" << std::endl;

	return 0;
}

//Calculates every pixel's RGB value and saves it into the matrix plot
int plot_func(int realNum, int imagNum, double realMin, double imagMin, double xstep, double ystep, bool equiAngleLines, int lineType, bool axis, cv::Mat& plot) {
	cv::Mat grid(imagNum, realNum, CV_8UC3);
	cv::Vec3b gridc;

	std::cout << "0%";

	for (int y = 0; y < imagNum; y++) {
		cv::Vec3b* ptr = plot.ptr<cv::Vec3b>(imagNum - y - 1);
		cv::Vec3b* ptr1 = grid.ptr<cv::Vec3b>(imagNum - y - 1);
		double im = imagMin + ystep * y;

		for (int x = 0; x < realNum; x++) {
			//evaluate function
			std::complex<double> w = f(std::complex<double>(realMin + xstep * x, im));
			double arg = std::arg(w);
			double mag = std::abs(w);

			//positive mod of argument
			double argn = arg + 2 * PI;
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
				t = fmod(w.real() - 0.125 * realNum * xstep, 0.25 * realNum * xstep);
				if (t < 0)
					t += 0.25 * realNum * xstep;
				t -= 0.125 * realNum * xstep;
				double t1 = fmod(w.imag() + 0.125 * imagNum * ystep, 0.25 * imagNum * ystep);
				if (t1 < 0)
					t1 += 0.25 * imagNum * ystep;
				t1 -= 0.125 * imagNum * ystep;

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
				t = fmod(w.real() - 0.25 * realNum * xstep, 0.5 * realNum * xstep);
				if (t < 0)
					t += 0.5 * realNum * xstep;
				t -= 0.25 * realNum * xstep;
				double t1 = fmod(w.imag() + 0.25 * imagNum * ystep, 0.5 * imagNum * ystep);
				if (t1 < 0)
					t1 += 0.5 * imagNum * ystep;
				t1 -= 0.25 * imagNum * ystep;

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
				t = fmod(w.real() - 0.5 * realNum * xstep, realNum * xstep);
				if (t < 0)
					t += realNum * xstep;
				t -= 0.5 * realNum * xstep;
				double t1 = fmod(w.imag() + 0.5 * imagNum * ystep, imagNum * ystep);
				if (t1 < 0)
					t1 += imagNum * ystep;
				t1 -= 0.5 * imagNum * ystep;

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
			float S = sat;
			float V = 1 - std::pow(0.5, mag);//0.5 is just a magic number, can choose numbers in (0,1) for varying gradients of values
			float H = 128 * arg / PI;
			int HLo = std::floor(H), HHi = std::ceil(H);

			//Explanation of how the color is calculated
			//(HHi - H) * colormap[HLo] + (H - HLo) * colormap[HHi] linearly interpolates the color associated with the hue 
			//From the look up table of colors
			//S * color + (1 - S) * 255 finds the weighted average of the color and white, with the color being whiter as 
			//the value of S goes down (so higher S results in a more saturated color, S=1 is most saturated)
			//V * color at the end averages the color with black (the (1 - V) * 0 is always so it is left out), so the color 
			//becomes blacker as the value decreases
			//
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
				ptr[x] = color;
			}
			else {
				cv::Vec3b color;
				color[0] = V * (S * colormap[HLo][2] + (1 - S) * 255);
				color[1] = V * (S * colormap[HLo][1] + (1 - S) * 255);
				color[2] = V * (S * colormap[HLo][0] + (1 - S) * 255);
				ptr[x] = color;
			}
		}
		if (y % (imagNum/100) == 0) {
			std::cout << "\rProgress: " << 100 * y / imagNum << "%\t\u2502";
			for (int k = 0; k < 20; k++) {
				std::cout << (k < 20 * y / imagNum ? "\u2588": " ");
			}
			std::cout << "\u2502";
		}
	}
	if (lineType != -1) {
		//Edge detects checkerboard pattern, and then widens the edges using a blur
		cv::Mat A, B, g;
		cv::cvtColor(grid, g, 6);
		cv::Canny(g, B, 0, 255, 3);
		int kernelSize = std::max(realNum, imagNum)/500;
		if (kernelSize % 2 == 0) {
			kernelSize += 1;
		}
		cv::GaussianBlur(B, A, cv::Size(kernelSize,kernelSize), 0, 0, cv::BORDER_DEFAULT);

		//Makes regions where an edge should appear darker
		for (int y = 0; y < A.rows; y++) {
			cv::Vec3b* ptr = plot.ptr<cv::Vec3b>(y);
			const unsigned char* row = A.ptr<unsigned char>(y);
			for (int x = 0; x < A.cols; x++) {
				if (row[x] == 0)
					ptr[x] /= 0.85;
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