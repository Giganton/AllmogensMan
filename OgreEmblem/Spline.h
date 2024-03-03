#pragma once
#include<vector>
#include "GraphicsUtils.h"

class CubicPolynomial
{
public:
	CubicPolynomial() {};
	CubicPolynomial(float a, float b, float c, float d) { a1 = a; a2 = b; a3 = c; a4 = d; };
	float a1 = 0;
	float a2 = 0;
	float a3 = 0;
	float a4 = 0;

	float evaluate(float x) { return (a1 * pow(x, 3) + a2 * pow(x, 2) + a3 * x + a4); };
};

class CubicSpline
{
private:
	std::vector<CubicPolynomial> xPolynomials;
	std::vector<CubicPolynomial> yPolynomials;
	std::vector<float> stepVector;
	float step;

	std::vector<std::vector<float>> constructM(std::vector<float> u);
	std::vector<std::pair<float, float>> constructB(std::vector<UTIL::ScreenCoord> splineKnots, std::vector<float> u);
	std::vector<float> getDistanceVector(std::vector<UTIL::ScreenCoord> splineKnots);
	std::vector<std::pair<float, float>> solveEqSystem(std::vector<std::vector<float>> M, std::vector<std::pair<float, float>> b);
	std::pair< std::vector<CubicPolynomial>, std::vector<CubicPolynomial>> findPolynomials(std::vector<float> sigma_x, std::vector<float> sigma_y, std::vector<UTIL::ScreenCoord> knots, std::vector<float> u);
public:
	CubicSpline() {};
	CubicSpline(std::vector<UTIL::ScreenCoord> splineKnots);

	std::pair< std::vector<CubicPolynomial>, std::vector<CubicPolynomial>> getPolynomials() { return std::make_pair(xPolynomials, yPolynomials); };
	float getStepSize() { return step; };
	std::vector<float> getStepVector() { return stepVector; };
};