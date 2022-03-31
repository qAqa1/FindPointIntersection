#include <iostream>
#include <string>
#include <array>

template<class T>
struct Point
{
	T x, y;
	Point(T x, T y) : x(x), y(y) {}
	explicit operator std::string () const { return "{ x = " + std::to_string(x) + ", y = " + std::to_string(y) + " }"; }
};

using PointD = Point<double>;


//метод, проверяющий пересекаются ли 2 отрезка [line1[0], line1[1]] и [line2[0], line2[1]]

template<class T>
bool PointIntersection(std::array<Point<T>, 2> line1, std::array<Point<T>, 2> line2, Point<T>& outPoint)
{
	//сначала расставим точки по порядку, т.е. чтобы было line1[0].x <= line1[1].x

	if (line1[1].x < line1[0].x)
	{
		auto tmp = line1[0];
		line1[0] = line1[1];
		line1[1] = tmp;
	}

	//и line2[0].x <= line2[1].x

	if (line2[1].x < line2[0].x)
	{
		auto tmp = line2[0];
		line2[0] = line2[1];
		line2[1] = tmp;
	}

	//проверим существование потенциального интервала для точки пересечения отрезков

	if (line1[1].x < line2[0].x)
		return false; //ибо у отрезков нету взаимной абсциссы

	//если оба отрезка вертикальные

	if ((line1[0].x - line1[1].x == 0) && (line2[0].x - line2[1].x == 0))
	{
		//если они лежат на одном X
		if (line1[0].x == line2[0].x)
		{
			//проверим пересекаются ли они, т.е. есть ли у них общий Y

			//для этого возьмём отрицание от случая, когда они НЕ пересекаются

			if (!((std::max(line1[0].y, line1[1].y) < std::min(line2[0].y, line2[1].y)) || (std::min(line1[0].y, line1[1].y) > std::max(line2[0].y, line2[1].y)))) return true;

		}
		return false;
	}

	//найдём коэффициенты уравнений, содержащих отрезки

	//f1(x) = A1*x + b1 = y

	//f2(x) = A2*x + b2 = y

	//если первый отрезок вертикальный

	if (line1[0].x - line1[1].x == 0)
	{
		//найдём Xa, Ya - точки пересечения двух прямых
		auto Xa = line1[0].x;
		auto A2 = (line2[0].y - line2[1].y) / (line2[0].x - line2[1].x);
		auto b2 = line2[0].y - A2 * line2[0].x;
		auto Ya = A2 * Xa + b2;

		if (line2[0].x <= Xa && line2[1].x >= Xa && std::min(line1[0].y, line1[1].y) <= Ya && std::max(line1[0].y, line1[1].y) >= Ya)
		{
			outPoint.x = Xa;
			outPoint.y = Ya;
			return true;
		}

		return false;
	}

	//если второй отрезок вертикальный

	if (line2[0].x - line2[1].x == 0)
	{
		//найдём Xa, Ya - точки пересечения двух прямых
		auto Xa = line2[0].x;
		auto A1 = (line1[0].y - line1[1].y) / (line1[0].x - line1[1].x);
		auto b1 = line1[0].y - A1 * line1[0].x;
		auto Ya = A1 * Xa + b1;

		if (line1[0].x <= Xa && line1[1].x >= Xa && std::min(line2[0].y, line2[1].y) <= Ya && std::max(line2[0].y, line2[1].y) >= Ya)
		{
			outPoint.x = Xa;
			outPoint.y = Ya;
			return true;
		}

		return false;

	}

	//оба отрезка невертикальные

	auto A1 = (line1[0].y - line1[1].y) / (line1[0].x - line1[1].x);
	auto A2 = (line2[0].y - line2[1].y) / (line2[0].x - line2[1].x);
	auto b1 = line1[0].y - A1 * line1[0].x;
	auto b2 = line2[0].y - A2 * line2[0].x;

	if (A1 == A2) return false; //отрезки параллельны

	//Xa - абсцисса точки пересечения двух прямых

	auto Xa = (b2 - b1) / (A1 - A2);
	auto Ya = A1 * Xa + b1;

	if ((Xa < std::max(line1[0].x, line2[0].x)) || (Xa > std::min(line1[1].x, line2[1].x)))
		return false; //точка Xa находится вне пересечения проекций отрезков на ось X
	else
	{
		outPoint.x = Xa;
		outPoint.y = Ya;
		return true;
	}
}

void main()
{
	PointD outputPoint(0, 0);
	//PointIntersection(PointD(0, 2), PointD(2, 2), PointD(2, 0), PointD(0, 2), outputPoint);
	//PointIntersection({ PointD(0, 2), PointD(2, 2) }, { PointD(2, 0), PointD(0, 2) }, outputPoint);
	PointIntersection({ PointD(0, 0), PointD(2, 2) }, { PointD(2, 0), PointD(0, 2) }, outputPoint);
	std::cout << (std::string)outputPoint;
}