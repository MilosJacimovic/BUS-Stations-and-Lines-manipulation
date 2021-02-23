#include <iostream>
#include <string>
using namespace std;

class Lokacija {

private:
	double x, y;

public:

	Lokacija(double x, double y) {
		this->x = x;
		this->y = y;
	}

	double getX() const { return x; }
	double getY() const  { return y; }
	void setx(double x) { this->x = x; }
	void setY(double y) { this->y = y; }

	friend ostream& operator<<(ostream& it, const Lokacija &lok) {
		it << "(" << lok.getX() << ", " << lok.getY() << ")";
		return it;
	}
};