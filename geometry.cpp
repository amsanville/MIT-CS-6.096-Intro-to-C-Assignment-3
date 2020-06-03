#include"geometry.h"
#include<math.h>
#include<iostream>

///////////////////////////////////////////////////////////////////////////////
// Point Array
// Constructor 1
PointArray::PointArray() {
	size = 0;
	points = new Point[0];
}

// Constructor 2
PointArray::PointArray(const Point points[], const int size) {
	// Initialize
	this->points = new Point[size];
	this->size = size;
	// Leap of faith that they are properly given to the constructor...

	// Use copy constructor created in Point to create a copy
	//
	// Note: could also use Point(points[i].x, points[i].y) to create a copy
	for (int i = 0; i < size; i++) {
		this->points[i] = Point(points[i]);
	}
}

// Copy Constructor
PointArray::PointArray(const PointArray& pv) {
	// Initialize
	size = pv.size;
	points = new Point[size];

	// Copy into the array
	for (int i = 0; i < size; i++) {
		points[i] = Point(pv.points[i]);
	}
}


// Destructor
PointArray::~PointArray() {
	delete[] points;
}

// Resize
void PointArray::resize(int n) {
	// Initialize
	Point* temp = new Point[n];

	// Determine which is smaller
	int stop = (size < n) ? size : n;

	// Copy all that is appropriate
	for (int i = 0; i < stop; i++) {
		temp[i] = Point(points[i]);
	}

	// Clean up and pointer shuffle
	delete[] points;
	points = temp;
	size = n;
}

// Push Back
void PointArray::push_back(const Point& p) {
	// First resize the array
	resize(size + 1);

	// Add at the end
	points[size - 1] = Point(p);

}

// Insert
void PointArray::insert(const int position, const Point& p) {
	// Bad position
	if (position < 0) {
		std::cout << "Error: negative position." << std::endl;
	}
	// If a position in the array
	else if (position <= size) {
		// First resize the array
		resize(size + 1);

		// Move everything to the right
		for (int i = size - 1; i > position; i--) {
			points[i] = points[i - 1];
		}

		// Make a copy of the point
		points[position] = Point(p);
	}
	// If not
	else {
		// Resize
		resize(position);
		points[position - 1] = Point(p);
	}
}

// Remove
void PointArray::remove(const int pos) {
	if (pos >= size) {
		// Nominally, should throw an index out of bounds exception
		std::cout << "Error: nothing to remove, position beyond end of the array." << std::endl;
	}
	else if (pos < 0) {
		std::cout << "Error: negative position." << std::endl;
	}
	else {
		// Shift the points
		for (int i = pos; i < size - 1; i++) {
			points[i] = points[i + 1];
		}

		// Resize
		resize(size - 1);
	}
}

// Get Size
const int PointArray::getSize() const {
	return size;
}

// Clear
void PointArray::clear() {
	resize(0);
}

// Get - non-constant
Point* PointArray::get(const int position) {
	if (position >= 0 &&  position < size) {
		return &points[position];
	}
	else {
		// Warning might not be necessary
		std::cout << "Warning: accessing beyond the end of the array" << std::endl;
		return nullptr;
	}
}

// Get - constant
const Point* PointArray::get(const int position) const {
	if (position >= 0 && position < size) {
		return &points[position];
	}
	else {
		// Warning might not be necessary
		std::cout << "Warning: accessing beyond the end of the array" << std::endl;
		return nullptr;
	}
}

// Print methods for debugging
void Point::print() const {
	std::cout << "(" << x << ", " << y << ")";
}

void PointArray::print() const {
	if (size == 0) {
		std::cout << "Nothing to print";
	}
	else {
		for (int i = 0; i < size; i++) {
			points[i].print();
			std::cout << " ";
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Polygon
// Initialize the static member
int Polygon::count = 0;

// Constructor 1
Polygon::Polygon() : vertices(){
	count++;
}

// Constructor 2
Polygon::Polygon(const Point arr[], int size) : vertices(arr, size) {
	count++;
};

// Constructor 3
Polygon::Polygon(const PointArray& pa) : vertices(pa) {
	count++;
}

// Constructor 4
Polygon::Polygon(const Polygon& poly) : vertices(poly.vertices) {
	count++;
}

// Rectangle
// Create an on-the-fly array constructor to allow for initializer list style
// constructors for rectangles. The idea is that we want to create a PointArray
// on the fly from a collection of points not in a PointArray. Nominally, we
// would just put all of those points into an array literal and construct a new
// PointArray from that. C++ does not let you do this. Thus, we hack our way
// around it by making a function that effectively does it for us.
Point constructorPoints[4];

Point* updateConstructorPoints(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
	constructorPoints[0] = p1;
	constructorPoints[1] = p2;
	constructorPoints[2] = p3;
	constructorPoints[3] = p4;
	return constructorPoints;
}

// Constructor 1
Rectangle::Rectangle(Point lwrlft, Point uprrgt) :
	Polygon(updateConstructorPoints(lwrlft, Point(uprrgt.getX(), lwrlft.getY()), uprrgt,	Point(lwrlft.getX(), uprrgt.getY())), 4) {
}
//^^^ Remember: derived classes use the base class constructors in initializer
// list style constructors.

// Constructor 2
Rectangle::Rectangle(int x1, int y1, int x2, int y2) :
	Polygon(updateConstructorPoints(Point(x1, y1), Point(x2, y1), Point(x2, y2), Point(x1, y2)), 4) {
}

// Area
double Rectangle::area() const {
	// Assume points are well ordered and form 90 degree angles, but can be
	// rotated
	
	// First side
	double delX = (double) vertices.get(0)->getX() - vertices.get(1)->getX();
	double delY = (double) vertices.get(0)->getY() - vertices.get(1)->getY();
	double length = pow(pow(delX, 2.) + pow(delY, 2.), 0.5);
	
	// Second side
	delX = (double) vertices.get(1)->getX() - vertices.get(2)->getX();
	delY = (double) vertices.get(1)->getY() - vertices.get(2)->getY();
	double width = pow(pow(delX, 2.) + pow(delY, 2.), 0.5);

	// Width times length
	return length * width;
}
// Triangle
Triangle::Triangle(Point a, Point b, Point c) :
	Polygon(updateConstructorPoints(a, b, c, Point(0, 0)), 3) {
}
// Area
double Triangle::area() const {
	// Assume the points form a triangle and not a line, however, Heron's
	// formula will just be zero if they are a line

	// Calculate a, b, and c:
	double delX = (double)vertices.get(0)->getX() - vertices.get(1)->getX();
	double delY = (double)vertices.get(0)->getY() - vertices.get(1)->getY();
	double a = pow(pow(delX, 2.) + pow(delY, 2.), 0.5);

	delX = (double)vertices.get(1)->getX() - vertices.get(2)->getX();
	delY = (double)vertices.get(1)->getY() - vertices.get(2)->getY();
	double b = pow(pow(delX, 2.) + pow(delY, 2.), 0.5);

	delX = (double)vertices.get(2)->getX() - vertices.get(0)->getX();
	delY = (double)vertices.get(2)->getY() - vertices.get(0)->getY();
	double c = pow(pow(delX, 2.) + pow(delY, 2.), 0.5);

	// Calculate s
	double s = (a + b + c) / 2.;

	// Plug into the formula
	return pow(s * (s - a) * (s - b) * (s - c), 0.5);
}