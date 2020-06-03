#ifndef GEOMETRY_H
#define GEOMETRY_H
// 3
class Point {
private:
	int x, y;
public:
	// Constructors
	Point(int u = 0, int v = 0) : x(u), y(v) {}
	Point(const Point& p) : x(p.x), y(p.y) {}
	// Accessors
	int getX() const { return x; }
	int getY() const { return y; }
	// Mutators
	void setX(int new_x) { x = new_x; }
	void setY(int new_y) { y = new_y; }
	
	// For Debugging
	void print() const;
};

class PointArray {
private:
	Point* points;
	int size;
	// Resize the the array
	void resize(int n);
public:
	// Constructors
	PointArray();
	PointArray(const Point points[], const int size);
	PointArray(const PointArray& pv);
	// Destructor
	~PointArray();
	// Other Functions
	// add a point on the end
	void push_back(const Point& p);
	// add a point in the position specified
	void insert(const int position, const Point& p);
	// remove the point at the position specified
	void remove(const int pos);
	// get the size of the array
	const int getSize() const;
	// remove everything and set the size to zero
	void clear();
	// Get a pointer to the element at some arbitrary position, null if the
	// position is outside the array
	Point* get(const int position);
	const Point* get(const int position) const;
	/*
	From the solution:

	The reason to have a constant and non-constant version is to allow
	flexibility in the implementation. Normally, we would expect to use the
	constant version, as we don't want someone messing with the contents of the
	array at some other location in the code. Having the non-constant version
	gives us that flexibility.

	My understanding is that the compiler will use the non-constant one if we
	ask it to assign a value to a non-constant pointer (similiar for the const).
	We can think of the data type then as const Point* or Point* for the sake of
	which version will get called.
	*/

	// For Debugging
	void print() const;
};

class Polygon {
protected:
	// Keeps track of vertices in the Polygon
	PointArray vertices;
	// Keeps count of the number of Polygons instantiated
	static int count;
public:
	// Constructors
	// Default Constructor
	Polygon();
	// Constructor using array of points
	Polygon(const Point arr[], int size);
	// Constructor using PointArray
	Polygon(const PointArray &pa);
	// Copy Constructor
	Polygon(const Polygon &poly);

	// Destructor
	~Polygon() { count--; }
	// Calculate the area
	virtual double area() const = 0;
	// Returns the number of polygons
	int getNumPolygons() { return count; };
	// Returns the number of sides
	int getNumSides() { return vertices.getSize(); }
	// Returns the list of points
	const PointArray* getPoints() { return &vertices; }
};

class Rectangle : public Polygon {
public:
	// Constructor with two points, lower left and upper right
	Rectangle(Point lwrlft, Point uprrgt);
	// Constructor with four ints, two sets of xy coordinates
	Rectangle(int x1, int y1, int x2, int y2);
	// Calculate the area of the rectangle
	double area() const;
};

class Triangle : public Polygon {
public:
	// Constructor with three points
	Triangle(Point a, Point b, Point c);
	// Calculate the area of a triangle
	double area() const;
};


#endif