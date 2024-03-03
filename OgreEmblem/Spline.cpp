#include "Spline.h"

CubicSpline::CubicSpline(std::vector<UTIL::ScreenCoord> knots)
{
	std::vector<float> u = getDistanceVector(knots);
	stepVector = u;
	step = u.at(1) - u.at(0);
	std::vector<std::vector<float>> M = constructM(u);
	std::vector<std::pair<float, float>> b = constructB(knots, u);
	
	std::vector<std::pair<float, float>> sigma = solveEqSystem(M, b);
	unsigned int i;
	std::vector<float> sigma_x, sigma_y;
	for (i = 0; i < sigma.size(); i++)
	{
		sigma_x.push_back(sigma.at(i).first);
		sigma_y.push_back(sigma.at(i).second);
	}

	std::pair< std::vector<CubicPolynomial>, std::vector<CubicPolynomial>> solution = findPolynomials(sigma_x, sigma_y, knots, u);
	xPolynomials = solution.first;
	yPolynomials = solution.second;
}

std::pair< std::vector<CubicPolynomial>, std::vector<CubicPolynomial>> CubicSpline::findPolynomials(std::vector<float> sigma_x, std::vector<float> sigma_y, std::vector<UTIL::ScreenCoord> knots, std::vector<float> u)
{
	int size = sigma_x.size();
	std::vector<CubicPolynomial> retVal1(size, CubicPolynomial());
	std::vector<CubicPolynomial> retVal2(size, CubicPolynomial());
	unsigned int i;

	for (i = 0; i < size - 1; i++)
	{
		float a, b, c, d;
		float yi = knots.at(i).y;
		float yip1 = knots.at(i + 1).y;
		float xi = knots.at(i).x;
		float xip1 = knots.at(i + 1).x;
		float h = u.at(i + 1) - u.at(i);

		a = (sigma_y.at(i + 1) - sigma_y.at(i)) / (6 * h);
		b = sigma_y.at(i) / 2;
		c = (yip1 - yi) / h - h * (2 * sigma_y.at(i) + sigma_y.at(i + 1)) / 6;
		d = yi;
		retVal2.at(i) = CubicPolynomial(a, b, c, d);

		a = (sigma_x.at(i + 1) - sigma_x.at(i)) / (6 * h);
		b = sigma_x.at(i) / 2;
		c = (xip1 - xi) / h - h * (2 * sigma_x.at(i) + sigma_x.at(i + 1)) / 6;
		d = xi;

		retVal1.at(i) = CubicPolynomial(a, b, c, d);
	}
	return std::make_pair(retVal1, retVal2);
}

std::vector<std::pair<float, float>> CubicSpline::solveEqSystem(std::vector<std::vector<float>> M, std::vector<std::pair<float, float>> b)
{
	int size = M.size();
	unsigned int i, j;
	std::vector<float> sigma_x(size, 0);
	std::vector<float> sigma_y(size, 0);
	std::vector<std::pair<float, float>> retVal(size, std::make_pair(0, 0));
	for (i = 0; i < size - 2; i++)
	{
		float factor =  M.at(i + 1).at(i) / M.at(i).at(i);
		for (j = 0; j < size; j++)
		{
			M.at(i + 1).at(j) = M.at(i + 1).at(j) - factor * M.at(i).at(j);
		}
		b.at(i + 1).first = b.at(i + 1).first - factor * b.at(i).first;
		b.at(i + 1).second = b.at(i + 1).second - factor * b.at(i).second;
	}

	for (i = 1; i < size; i++)
	{
		float factor = M.at(size - 1 - i).at(size - i) / M.at(size - i).at(size - i);
		for (j = 0; j < size; j++)
		{
			M.at(size - 1 - i).at(j) = M.at(size - 1 - i).at(j) - factor * M.at(size - i).at(j);
		}
		b.at(size - 1 - i).first = b.at(size - 1 - i).first - factor * b.at(size - i).first;
		b.at(size - 1 - i).second = b.at(size - 1 - i).second - factor * b.at(size - i).second;
	}

	for (i = 0; i < size; i++)
	{
		retVal.at(i).first = b.at(i).first / M.at(i).at(i);
		retVal.at(i).second = b.at(i).second / M.at(i).at(i);
	}
	return retVal;
}

std::vector<float> CubicSpline::getDistanceVector(std::vector<UTIL::ScreenCoord> sKnots)
{
	unsigned int i;
	std::vector<float> u;
	u.push_back(0);
	for (i = 1; i < sKnots.size(); i++)
	{
		u.push_back(u.at(i-1) + (sKnots.at(i - 1) - sKnots.at(i)).abs());
	}
	/*for (i = 0; i < sKnots.size(); i++)
	{
		u.at(i) = u.at(i) / u.at(sKnots.size() - 1);
	}*/
	return u;
}

std::vector<std::pair<float, float>> CubicSpline::constructB(std::vector<UTIL::ScreenCoord> splineKnots, std::vector<float> u)
{
	int n = splineKnots.size();
	std::vector<std::pair<float, float>> b;
	float h = splineKnots.at(1).x - splineKnots.at(0).x;
	b.push_back(std::make_pair(0.01, -0.01));

	unsigned int i;
	for (i = 1; i < n - 1; i++)
	{
		float hip1, hi;
		hip1 = u.at(i+1) - u.at(i);
		hi = u.at(i) - u.at(i-1);
		float y0, y1, y2, x0, x1, x2;
		y0 = splineKnots.at(i - 1).y;
		y1 = splineKnots.at(i).y;
		y2 = splineKnots.at(i + 1).y;
		x0 = splineKnots.at(i - 1).x;
		x1 = splineKnots.at(i).x;
		x2 = splineKnots.at(i + 1).x;
		float xEq = 6 * ((x2 - x1) / hip1 - (x1 - x0) / hi);
		float yEq = 6 * ((y2 - y1) / hip1 - (y1 - y0) / hi);
		b.push_back(std::make_pair(xEq, yEq));
	}
	float yn, ynm1, ynm2;
	yn = splineKnots.at(n-1).y;
	ynm1 = splineKnots.at(n - 2).y;
	ynm2 = splineKnots.at(n - 3).y;
	b.push_back(std::make_pair(0.01, -0.01));

	return b;
}

std::vector<std::vector<float>> CubicSpline::constructM(std::vector<float> u)
{
	std::vector<std::vector<float>> M;
	unsigned int i, j;
	std::vector<float> M0;
	std::vector<float> MN;
	M0.push_back(1);
	int n = u.size();

	for (i = 1; i < n; i++)
	{
		M0.push_back(0);
	}
	M.push_back(M0);

	for (i = 1; i < n - 1; i++)
	{
		std::vector<float> Mi;
		for (j = 0; j < n; j++)
		{
			float temp;
			float him1, hi;
			him1 = u.at(i) - u.at(i - 1);
			hi = u.at(i + 1) - u.at(i);
			if (j == (i - 1))
			{
				temp = him1;
			}
			else if (j == i)
			{
				temp = 2 * (him1 + hi);
			}
			else if (j == (i + 1))
			{
				temp = hi;
			}
			else
			{
				temp = 0;
			}
			Mi.push_back(temp);
		}
		M.push_back(Mi);
	}
	for (i = 0; i < n - 1; i++)
	{
		MN.push_back(0);
	}
	MN.push_back(1);
	M.push_back(MN);

	return M;
}