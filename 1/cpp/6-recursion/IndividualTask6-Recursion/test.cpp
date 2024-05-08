#include <iostream>
#include <cmath>

class Point{
public:
	Point(){
		this->x_=0.0;
		this->y_=0.0;
	}

	Point(double x, double y){
		this->x_ = x;
		this->y_ = y;
	}

	~Point(){
		delete &x_;
		delete &y_;
	}

	void setX(double x){
		this->x_=x;
	}

	void setY(double y){
		this->y_=y;
	}

	double getX() const{
		return this->x_;
	}
	
	double getY() const{
		return this->y_;
	}
	bool operator==(const Point & p) const{
		return (this->x_ == p.x_) && (this->y_ == p.y_);
	}
	double getDistance(const Point & p) const{
		double x = std::abs(this->x_ - p.x_);
		double y = abs(this->y_ - p.y_);
		return std::sqrt(x*x + y*y);
	}


private:
	double x_;
	double y_;
};

std::ostream& operator<<(std::ostream& os, const Point& p){
	os << "(" << p.getX() << "; " << p.getY() << ")"; 
}

int main(){
	Point p1 = Point(1,2);
	std::cout << p1.getX() << " " << p1.getY() << '\n';
	p1.setX(3);
	p1.setY(3);
	std::cout << p1.getX() << " " << p1.getY() << '\n';
	Point p2 = Point(1,1);
	std::cout << '\n' << (p1==p2);
	std::cout << "\n\n" << p1.getDistance(p2);
}