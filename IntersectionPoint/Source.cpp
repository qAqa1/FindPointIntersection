#include <iostream>
#include <string>

template<class T>
struct Point
{
	T x, y;
	Point(T x, T y) : x(x), y(y) {}
	explicit operator std::string () const { return "{ x = " + std::to_string(x) + ", y = " + std::to_string(y) + " }"; }
};

using PointD = Point<double>;


//�����, ����������� ������������ �� 2 ������� [p1, p2] � [p3, p4]

bool PointIntersection(PointD p1, PointD p2, PointD p3, PointD p4, PointD& outPoint)
{
	//������� ��������� ����� �� �������, �.�. ����� ���� p1.x <= p2.x

	if (p2.x < p1.x)
	{
		PointD tmp = p1;
		p1 = p2;
		p2 = tmp;
	}

	//� p3.x <= p4.x

	if (p4.x < p3.x)
	{
		PointD tmp = p3;
		p3 = p4;
		p4 = tmp;
	}

	//�������� ������������� �������������� ��������� ��� ����� ����������� ��������

	if (p2.x < p3.x)
		return false; //��� � �������� ���� �������� ��������

	//���� ��� ������� ������������

	if ((p1.x - p2.x == 0) && (p3.x - p4.x == 0))
	{
		//���� ��� ����� �� ����� X
		if (p1.x == p3.x)
		{
			//�������� ������������ �� ���, �.�. ���� �� � ��� ����� Y

			//��� ����� ������ ��������� �� ������, ����� ��� �� ������������

			if (!((std::max(p1.y, p2.y) < std::min(p3.y, p4.y)) || (std::min(p1.y, p2.y) > std::max(p3.y, p4.y)))) return true;

		}
		return false;
	}

	//����� ������������ ���������, ���������� �������

	//f1(x) = A1*x + b1 = y

	//f2(x) = A2*x + b2 = y

	//���� ������ ������� ������������

	if (p1.x - p2.x == 0)
	{
		//����� Xa, Ya - ����� ����������� ���� ������
		double Xa = p1.x;
		double A2 = (p3.y - p4.y) / (p3.x - p4.x);
		double b2 = p3.y - A2 * p3.x;
		double Ya = A2 * Xa + b2;

		if (p3.x <= Xa && p4.x >= Xa && std::min(p1.y, p2.y) <= Ya && std::max(p1.y, p2.y) >= Ya)
		{
			outPoint.x = Xa;
			outPoint.y = Ya;
			return true;
		}

		return false;
	}

	//���� ������ ������� ������������

	if (p3.x - p4.x == 0)
	{
		//����� Xa, Ya - ����� ����������� ���� ������
		double Xa = p3.x;
		double A1 = (p1.y - p2.y) / (p1.x - p2.x);
		double b1 = p1.y - A1 * p1.x;
		double Ya = A1 * Xa + b1;

		if (p1.x <= Xa && p2.x >= Xa && std::min(p3.y, p4.y) <= Ya && std::max(p3.y, p4.y) >= Ya)
		{
			outPoint.x = Xa;
			outPoint.y = Ya;
			return true;
		}

		return false;

	}

	//��� ������� ��������������

	double A1 = (p1.y - p2.y) / (p1.x - p2.x);
	double A2 = (p3.y - p4.y) / (p3.x - p4.x);
	double b1 = p1.y - A1 * p1.x;
	double b2 = p3.y - A2 * p3.x;

	if (A1 == A2) return false; //������� �����������

	//Xa - �������� ����� ����������� ���� ������

	double Xa = (b2 - b1) / (A1 - A2);
	double Ya = A1 * Xa + b1;

	if ((Xa < std::max(p1.x, p3.x)) || (Xa > std::min(p2.x, p4.x)))
		return false; //����� Xa ��������� ��� ����������� �������� �������� �� ��� X
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
	PointIntersection(PointD(0, 0), PointD(2, 2), PointD(2, 0), PointD(0, 2), outputPoint);
	std::cout << (std::string)outputPoint;
}