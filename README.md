# Complex-Plotter

This is a repository for visualizing complex valued functions using domain coloring in C++ using OpenCV. The method of domain coloring 
used here gives information about four main properties of a complex number - magnitude, phase, as well as real and imaginary components -
as well as the singularities and zeros. I will present some examples of how to interpret the different pieces of  information from the domain colored
plot using the rational function:

![equation](https://latex.codecogs.com/gif.latex?\inline&space;f(z)=(z&plus;3&plus;5i)(z-7i)^2&space;\left&space;(&space;\frac{1}{z}&plus;\frac{i}{(z-5-3i)^3}&space;\right&space;))

in the domain [-10, 10] × [-10, 10] (In this README, [a, b]×[c, d] does NOT indicate an R^2 domain, but instead the domain of the 
complex rectangle with corners a+ic, a+id, b+ic and b+id)

## Magnitude

The magnitude is indicated by *value* of the color in the HSV color system, with lower value (darker shades) representing a smaller
magnitude. In the image below, you will notice the value continuously "reseting" and creating what is perceived as levels. This is done intentionally, by taking the log of the magnitude and then taking the mod of the log magnitude. Using this approach, as opposed to just using the magnitude directly, allows for giving far more detail about the magnitude, and allows us to distinguish easily between a very large range of magnitudes. If this approach was not taken, the graph will instead have blobs of black and white near singularities and zeros, and with the bias in human color perception, little more information about magnitudes in the rest of the function could be known. Here, each "level curve", or the lines at the discontinuities of the values represent locations with the exact same magnitude. The log of the magnitude was log base 1.5, so each level is either 1.5 times larger or smaller than a level next to it. Also, by seeing where these levels converge, the exact locations of singularities (poles or essential singularities) or zeros can be found. If the levels seem to be converging towards the viewer, then it is a zero (like at the top, bottom, and three points in a triple petal formation), and if the levels seem to be sinking into the screen, it converges to a singularity (like at the center of the image, and the center of the three zeros making a petal shape).

<a href="https://imgur.com/HV4QLSf"><img src="https://i.imgur.com/HV4QLSf.jpg" title="source: imgur.com" /></a>

## Phase

The phase, or argument, of the function is given by the *hue* of the color in the HSV color system, with arg(f(z) =
* 0: Red (positive real number)
* π/3: Yellow
* π/2: Chartreuse (light green) (positive imaginary number)
* 2π/3: Green 
* π: Cyan (negative real number)
* 4π/3: Blue
* 3π/2: Violet (negative imaginary number)
* 5π/3: Purple

While this is a useful tool, it can be quite hard to accurately distinguish hues, especially since humans don't interpret each hue equally.
To help better analyze the phase, equal angle lines can be enabled. This will create white streaks in the image that connect equal phase points of f(z), as can be seen below, with streaks for each phase which is an integer multiple of π/6, giving precise information about the phase of points in the plot. 

<a href="https://imgur.com/RvtG1YR"><img src="https://i.imgur.com/RvtG1YR.jpg" title="source: imgur.com" /></a>

## Lines of Constant Real and Imaginary components

A grid can also be enabled, where the "lines" of the "grid" mark curves where either Re(f(z)) or Im(f(z)) are constant. Two such lines 
will coincide with the white streaks of constant phase - where the phase is 0 or π (constantly real), or π/2 or 3π/2 (constantly 
imaginary). The function can also be seen as analytic or not by checking if the crossing points of the grid are all at right angles. This
grid can be seen in the image below. 

<a href="https://imgur.com/wQLBEKY"><img src="https://i.imgur.com/wQLBEKY.jpg" title="source: imgur.com" /></a>

## Combining the above

Both the grid and the streaks can be enabled, to get all of the above information in the same image, although it may not always be a good idea, since it can possibly make the image too busy in certain cases.

<a href="https://imgur.com/wqybGnU"><img src="https://i.imgur.com/wqybGnU.jpg" title="source: imgur.com" /></a>

## Technical Details

### Program Parameters
The step size, the domain of the plotted function, and equal angle lines, the grid and the function can all be controlled through command line arguments, with the format `-[identifier of argument] argument`. The following list outlines all of the available commands:
* `-realMin [decimal number]` (alias: `-a`)
* `-realMax [decimal number]` (alias: `-b`)
* `-imagMin [decimal number]` (alias: `-c`)
* `-imagMax [decimal number]` (alias: `-d`) 
* `-step [decimal number]` (alias: `-s`)
* `-grid [t/f]` (alias: `-g`)
* `-angleLines [t/f]` (alias: `-l`)
* `-func [function]` (alias: `-f`)

The domain is controlled through the arguments `realMin`, `realMax`, `imagMin` and `imagMax`, with the end
domain being [`realMin`, `realMax`]×[`imagMin`, `imagMax`]. The restrictions on `realMin`, `realMax`, `imagMin` and `imagMax` are that they must be *real decimal* quantities, and `realMax` and `imagMax` must be greater than `realMin` and `imagMin`, respectively.

The step size is controlled using the argument `step`, which should be ideally much smaller than the difference between minimum and maximum quantities of both the real and imaginary domains.

The constant angle lines can be turned on or off by using either `-l t` or `-l f`, respectively. Similarly, the grid can be turned on or off by using either `-g t` or `-g f`.

Passing the function is a bit more complicated, and must be done with a very specific syntax in order for the function to be properly interpreted. The parts of the function syntax are:
* numbers
* operators
* brackets
* inbuilt functions
* the variable

The syntax for numbers can be in one of three ways. The syntax for a *real positive integer* is simply the integer itself, with no additional components, such as `2`. The syntax for a general real number is a backslash and then the real number, such as `\-7.32`. The syntax for a general complex number is a backslash, and the real and imaginary components in brackets after seperated by a comma. For example, the real number 1.54+2.55i would be written as `\(1.54,2.55)`. Make sure there are NO SPACES. There are also 3 additional constants available, which can be inputed directly: π can be written as `\pi`, e (Euler's number) can be written as `e`, and the imaginary unit i can be written as `i`.

The five operators are +, -, \*, /, and ^, for addition, subtraction, division, multiplication and exponentiation, respectively. They can be inputed without any additional arguments. For example, π+3\*4 is inputed as `\pi+3/4`. Brackets are also input without any additional syntax, so (-1+e) squared is input as `(\-1+e)^2`. Multiplication must always be explicitly defined using \* (for example, `5(3+1)` will not be interpreted as 5 multiplied by 3+1, it must be `5*(3+1)`).

Functions are input with a backslash, the name of the function, and followed by brackets surrounding the argument of the function. For example, sin(π/4) is `\sin(\pi/4)`. Currently, all of the inbuilt functions available are single input (no min, max or mod function for example). The list of available functions is: 
* Miscellaneous Complex: `\Re`, `\Im`, `\abs`, `\arg`, `\conj`
* Trigonometric Functions: `\cos`, `\sin`, `\tan`, `\sec`, `\csc`, `\cot`
* Inverse Trigonometric Functions: `\acos`, `\asin`, `\atan`, `\asec`, `\acsc`, `\acot`
* Hyperbolic Trigonometric Functions: `\cosh`, `\sinh`, `\tanh`, `\sech`, `\csch`, `\coth`
* Inverse Hyperbolic Trigonometric Functions: `\acosh`, `\asinh`, `\atanh`, `\asech`, `\acsch`, `\acoth`
* Logarithms: `\log` (base 10), `\ln` (natural logarithm)
* Exponential: `\exp`

Possible functions available in the future may be square root (can currently be implemented by `^\0.5`), the Gamma function, and Bessel functions.

Lastly, a variable quantity can also be passed in, as `z`, which is what will be changed in the program to evaluate the function.

Combining this, we can input the function graphed above as `((z+3+5*i)*(z-7*i)^2)*(1/z+i/((z-5-3*i)^3))`.

### Other details

The equiangle lines are made by increasing the saturation massively when the point is close in phase to a multiple of π/6, which
is implemented by approximating a notch filter using some lines, which is why this creates streaks with a gradient fall off. The grid is made by first finding the mod of the real nad imaginary components of each pixel's function value, and then subtracting half the divisor, which roughly evenly splits both reals and imaginary numbers into half each. Then each location where the mod-subtracted-real and imaginary component are the same sign are made white, while the rest of the components are made black, making a checkerboard pattern. An edge detect filter is passed through, isolating only the edges and making the grid, and then grid is imposed onto the plot by darkening the respective elements of the plot. This gives solid equal width curves for the grid, instead of variable length gradient streaks, which would not be suited to visualizing a grid.

The HSV to RGB conversion is done according to the algorithm given on [Wikipedia](https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB)

## Examples
Some example plots I have made in order to illustrate the kinds of outputs.

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{\left(z&plus;1\right)\left(z&plus;i\right)}{\left(z-1\right)\left(z-i\right)})
over [-1.5, -1.5]×[-1.5, -1.5]

<a href="https://imgur.com/CNtLLNU"><img src="https://i.imgur.com/CNtLLNU.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\exp\left(\frac{1}{z}\right))
over [-1.5, -1.5]×[-1.5, -1.5]

Note the essential singularity in the center. It can be seen that it is an essential singularity as the behaviour from the right indicates that it converges to 0, whereas the behaviour from the right indicates it is diverging to infinity. The different types
of behaviour from different approaches shows that it cannot be a pole, and must be an essential singularity.

<a href="https://imgur.com/7u5jNpL"><img src="https://i.imgur.com/7u5jNpL.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{z^{2}&plus;1}{z^{2}-1})
over [-1.5, 1.5]×[-1.5, 1.5]

<a href="https://imgur.com/9ydcbxW"><img src="https://i.imgur.com/9ydcbxW.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{\left(z^{2}-1\right)\left(z-2-i\right)^{2}}{z^{2}&plus;2&plus;2i})
over [-1.5, 1.5]×[-1.5, 1.5]

This is the my version of (a plot very similar to) the example image on the Wikipedia page for [Domain Coloring](https://en.wikipedia.org/wiki/Domain_coloring)

<a href="https://imgur.com/h4gD6ai"><img src="https://i.imgur.com/h4gD6ai.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{1-z^{-10}}{1-0.9^{10}z^{-10}})
over [-1.5, 1.5]×[-1.5, 1.5]

This is the plot of the z-transform of a simple digital notch filter, with notches at 10 frequencies. Notice how the magnitude
is mostly constant around the unit circle except for at the notching frequencies where it drops to 0 suddenly, which is the intended behaviour of a notching filter (to filter out specific frequencies). Also, there is massive phase shifting near the notching frequencies, which could be an issue, with little phase shift everywhere else.

<a href="https://imgur.com/m3zdfK6"><img src="https://i.imgur.com/m3zdfK6.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?z^{2}&plus;2\bar{z}&plus;1)
over [-3, 3]×[-3, 3]

This example is a plot of a non-holomorphic complex function. This can be easily seen in the plot as the grid lines do not intersect at right angles everywhere, and also by noticing the conjugate of z in the function.

<a href="https://imgur.com/6hjYJcS"><img src="https://i.imgur.com/6hjYJcS.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\Gamma(z))
over [-5, 5]×[-5, 5]

The periodic poles at every non-positive integer for the gamma function can be seen in this case.

<a href="https://imgur.com/10uHSVH"><img src="https://i.imgur.com/10uHSVH.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{1}{\Gamma(z)})
over [-5, 5]×[-5, 5]

This plot is remarkably similar to the previous, since taking the inverse only changes the sign of the log of the magnitude, and the phase by π, which can easily be seen here by comparing the hues and values. You can also verify that the inverse of the gamma function is an entire function, as there is an absence of singularities.

<a href="https://imgur.com/wkJab2X"><img src="https://i.imgur.com/wkJab2X.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\arcsin\left(z\right))
over [-5, 5]×[-5, 5]

The location of where the branch cuts need to be made can be seen, along the real axis for abs(Re(z)) > 1,  here where there is an abrupt change in hue.

<a href="https://imgur.com/V3XaqDo"><img src="https://i.imgur.com/V3XaqDo.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?z&plus;\frac{1}{z})
over [-4, 4]×[-4, 4]

<a href="https://imgur.com/qoT6Ngr"><img src="https://i.imgur.com/qoT6Ngr.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\ln\left(z\right))
over [-5, 5]×[-5, 5]

Another example that illustrates where a branch cut would need to be made, along the real axis for Re(z) < 0

<a href="https://imgur.com/NQ4ilhZ"><img src="https://i.imgur.com/NQ4ilhZ.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\left(1&plus;z\right)\left(1&plus;0.445z&plus;z^{2}\right)\left(1&plus;1.247z&plus;z^{2}\right)\left(1&plus;1.8019z&plus;z^{2}\right))
over [-1.5, 1.5]×[-1.5, 1.5]

The plot for the 7th degree Butterworth polynomial of a low pass Butterworth filter, with the locaation of the 7 zeros being seen around the high frequencies. 

<a href="https://imgur.com/7VFcTRL"><img src="https://i.imgur.com/7VFcTRL.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{\sin\left(z^{3}-1\right)}{z})
over [-2, 2]×[-2, 2]

Just a fun function plot. The rotational symmetry with period 2π/3 can be seen, and the reason is the exponent of 3 on z for the argument to sine. The three zeros of the argument of sine (which also produce 0 for sine) can also be seen. Furthermore, it can be seen that the function behaves roughly like 1/z near the center, due to the small angle approximation and z^3 being more insignificant

<a href="https://imgur.com/IF4PDJV"><img src="https://i.imgur.com/IF4PDJV.jpg" title="source: imgur.com" /></a>