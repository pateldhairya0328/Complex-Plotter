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
magnitude. In the image below, you will notice the value continuously "reseting" and creating what is perceived as levels. This is done
intentionally, by taking the log of the magnitude and then taking the mod of the log magnitude. Using this approach, as opposed to just 
using the magnitude directly, allows for giving far more detail about the magnitude, and allows us to distinguish easily between a very
large range of magnitudes. If this approach was not taken, the graph will instead have blobs of black and white near singularities and 
zeros, and with the bias in human color perception, little more information about magnitudes in the rest of the function could be known.
Here, each "level curve", or the lines at the discontinuities of the values represent locations with the exact same magnitude. The log of
the magnitude was log base 1.5, so each level is either 1.5 times larger or smaller than a level next to it. Also, by 
seeing where these levels converge, the exact locations of singularities or zeros can be found. If the levels seem to be converging
towards the viewer, then it is a zero (like at the top, bottom, and three points in a triple petal formation), and if the levels seem 
to be sinking into the screen, it converges to a singularity (like at the center of the image, and the center of the three zeros making
a petal shape).

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
To help better analyze the phase, the `equiAngleLines` variable can be set to `true`. This will create white streaks in the image that 
connect equal phase points of f(z), as can be seen below, with streaks for each phase which is an integer multiple of π/6, giving 
precise information about the phase of points in the plot. 

<a href="https://imgur.com/RvtG1YR"><img src="https://i.imgur.com/RvtG1YR.jpg" title="source: imgur.com" /></a>

## Lines of Constant Real and Imaginary components

A grid can also be enabled, where the "lines" of the "grid" mark curves where either Re(f(z)) or Im(f(z)) are constant. Two such lines 
will coincide with the white streaks of constant phase - where the phase is 0 or π (constantly real), or π/2 or 3π/2 (constantly 
imaginary). The function can also be seen as analytic or not by checking if the crossing points of the grid are all at right angles. This
grid can be seen in the image below. The grid can be enabled by setting the `lines` variable can be set to `true`

<a href="https://imgur.com/wQLBEKY"><img src="https://i.imgur.com/wQLBEKY.jpg" title="source: imgur.com" /></a>

## Combining the above

Both the grid and the streaks can be enabled, to get all of the above information in the same image, although it may not always be a good
idea, since it can possibly make the image too busy.

<a href="https://imgur.com/wqybGnU"><img src="https://i.imgur.com/wqybGnU.jpg" title="source: imgur.com" /></a>

## Examples
Some more examples that illustrate various 

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{\left(z&plus;1\right)\left(z&plus;i\right)}{\left(z-1\right)\left(z-i\right)})
over [-1.5, -1.5]×[-1.5, -1.5]

<a href="https://imgur.com/CNtLLNU"><img src="https://i.imgur.com/CNtLLNU.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\exp\left(\frac{1}{z}\right))
over [-1.5, -1.5]×[-1.5, -1.5]

<a href="https://imgur.com/7u5jNpL"><img src="https://i.imgur.com/7u5jNpL.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{z^{2}&plus;1}{z^{2}-1})
over [-1.5, 1.5]×[-1.5, 1.5]

<a href="https://imgur.com/9ydcbxW"><img src="https://i.imgur.com/9ydcbxW.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{\left(z^{2}-1\right)\left(z-2-i\right)^{2}}{z^{2}&plus;2&plus;2i})
over [-1.5, 1.5]×[-1.5, 1.5]

<a href="https://imgur.com/h4gD6ai"><img src="https://i.imgur.com/h4gD6ai.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{1-z^{-10}}{1-0.9^{10}z^{-10}})
over [-1.5, 1.5]×[-1.5, 1.5]

<a href="https://imgur.com/m3zdfK6"><img src="https://i.imgur.com/m3zdfK6.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?z^{2}&plus;2\bar{z}&plus;1)
over [-3, 3]×[-3, 3]

<a href="https://imgur.com/6hjYJcS"><img src="https://i.imgur.com/6hjYJcS.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\Gamma(z))
over [-5, 5]×[-5, 5]

<a href="https://imgur.com/10uHSVH"><img src="https://i.imgur.com/10uHSVH.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{1}{\Gamma(z)})
over [-5, 5]×[-5, 5]

<a href="https://imgur.com/wkJab2X"><img src="https://i.imgur.com/wkJab2X.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\arcsin\left(z\right))
over [-5, 5]×[-5, 5]

<a href="https://imgur.com/V3XaqDo"><img src="https://i.imgur.com/V3XaqDo.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?z&plus;\frac{1}{z})
over [-4, 4]×[-4, 4]

<a href="https://imgur.com/qoT6Ngr"><img src="https://i.imgur.com/qoT6Ngr.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\ln\left(z\right))
over [-5, 5]×[-5, 5]

<a href="https://imgur.com/NQ4ilhZ"><img src="https://i.imgur.com/NQ4ilhZ.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\left(1&plus;z\right)\left(1&plus;0.445z&plus;z^{2}\right)\left(1&plus;1.247z&plus;z^{2}\right)\left(1&plus;1.8019z&plus;z^{2}\right))
over [-1.5, 1.5]×[-1.5, 1.5]

<a href="https://imgur.com/7VFcTRL"><img src="https://i.imgur.com/7VFcTRL.jpg" title="source: imgur.com" /></a>

* ![Equation](https://latex.codecogs.com/gif.latex?\frac{\sin\left(z^{3}-1\right)}{z})
over [-2, 2]×[-2, 2]

<a href="https://imgur.com/IF4PDJV"><img src="https://i.imgur.com/IF4PDJV.jpg" title="source: imgur.com" /></a>
