#include <iostream>
#include <vector>

double f(std::vector<double> vals) {
	return (vals[0] - 7) * (vals[0] - 7) +  (vals[1] + 1) * (vals[1] + 1) + (vals[2] + 1)* (vals[2] + 1);
}

struct Point {
	std::vector<double> props;

	Point(double arr[] , int n) {
		for (int i = 0; i < n; i++) {
			props.push_back(arr[i]);
		}
	}

	Point(std::vector<double> cProps) {
		props = cProps;
	}

	void log() {
		for (const auto& prop : props) {
			std::cout << prop << '\t';
		}
		std::cout << std::endl;
	}

	double len() {
		double sum = 0;
		for (const auto& prop : props) {
			sum += prop * prop;
		}
		return sqrt(sum);
	}

	Point operator-(Point const& other) {
		if (other.props.size() == this->props.size()) {
			std::vector<double> retProps;
			for (int i = 0; i < this->props.size(); i++) {
				retProps.push_back(this->props[i] - other.props[i]);
			}
			return Point(retProps);
		}	
	}

	Point& operator=(Point other) {
		this->props = std::vector<double>();
		
		for ( const auto& prop : other.props) {
			this->props.push_back(prop);
		}
		return *this;
	}

	Point operator*(double scalar) {
		std::vector<double> retProps;
		for (int i = 0; i < this->props.size(); i++) {
			retProps.push_back(this->props[i] * scalar);
		}
		return Point(retProps);
	}
};

Point gradF(Point p , double eps = 0.0001) {
	std::vector<double> diffs;

	for (int i = 0; i < p.props.size(); i++) {
		std::vector<double> temp = p.props;
		temp[i] += eps;
		double diffN = (f(temp) - f(p.props)) / eps;
		diffs.push_back(diffN);
	}

	return Point(diffs);
}


int main()
{
	double eps = 0.0001;

	double x0 = -10;
	double y0 = 10;
	double z0 = 10;
	
	double a = 2;
	double arr0[3] = { x0 , y0 , z0 };
	Point pI(std::vector<double>{-10, 10 , 10});
	Point pLast(std::vector<double>{-10, 10,10});
	

	while (true) {
		pLast = pI;
		Point t = ( gradF(pI) * a);
		pI = pI - t;
		pI.log();
	
		if (f(pI.props) < f(t.props)) {
			a /= 2;
		}else{
			pI = t;
		}
		if (abs(f(pI.props) - f(pLast.props)) < eps) {
			break;
		}
	}

}






/*
double f(double x, double y) {
	return (x -7)* (x - 7) + (y + 1)* (y + 1);
}*/
/*


double diffx(double x, double y, double eps = 0.0001) {
	return (f(x + eps, y) - f(x, y)) / eps;
}

double diffy(double x, double y, double eps = 0.0001) {
	return (f(x, y + eps) - f(x, y)) / eps;
}*/
