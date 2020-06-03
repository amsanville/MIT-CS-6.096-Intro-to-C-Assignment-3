#include"geometry.h"
#include<iostream>
#include<string>
using namespace std;

/* 5.7
Write a small function that prints the area of the polygon and the (x,y) 
coordinates of all of its points
*/
void printAttributes(Polygon* poly) {
	// Print the area
	cout << "The area: " << poly->area() << " units" << endl;

	// Print the vertices
	cout << "The vertices: " << endl;
	const PointArray* temp = poly->getPoints();
	for (int i = 0; i < poly->getNumSides(); i++) {
		cout << "(" << temp->get(i)->getX() <<  ", " << temp->get(i)->getY() << ")" << endl;
	}
	cout << endl;
	// Note: temp is a pointer to the interior of Polygon, which is why it's
	// constant (we don't want it modified) and why we don't worry about
	// deleting what it points to at the end of the function.
}

/*
Write a program that prompts the user for a lower-left and upper-right
positions and creates a rectangle object, prompts the user for points of a
triangle, and uses the above to print their attributes.
*/
void exercise5_7() {
	// Prompts for points for rectangle
	int x, y;
	cout << "Enter data to construct rectangle:" << endl;
	cout << "Enter Lower-Left X:" << endl;
	cin >> x;
	cout << "Enter Lower-Left Y:" << endl;
	cin >> y;
	Point point1 = Point(x, y);
	cout << "Enter Upper-Right X:" << endl;
	cin >> x;
	cout << "Enter Upper-Right  Y:" << endl;
	cin >> y;
	Point point2 = Point(x, y);
	
	// Construct the rectangle
	Rectangle rect = Rectangle(point1, point2);

	// Prompts for points for triangle
	cout << "\nEnter data to construct triangle:" << endl;
	cout << "Vertex 1 X:" << endl;
	cin >> x;
	cout << "Vertex 1 Y:" << endl;
	cin >> y;
	point1 = Point(x, y);
	cout << "Vertex 2 X:" << endl;
	cin >> x;
	cout << "Vertex 2 Y:" << endl;
	cin >> y;
	point2 = Point(x, y);
	cout << "Vertex 3 X:" << endl;
	cin >> x;
	cout << "Vertex 3 Y:" << endl;
	cin >> y;
	Point point3 = Point(x, y);

	// Construct  the triangle
	Triangle tri = Triangle(point1, point2, point3);

	// Print out the attributes
	cout << "\nRectangle Attributes:" << endl;
	printAttributes(&rect);
	cout << "\nTriangle Attributes:" << endl;
	printAttributes(&tri);
	cout << endl;

}

/* 6 Strings
Write a function pigLatinify that takes a string object as an argument. (You
may assume that this string contains a single lowercase word.) Return the
Pig Latin version of the origin.
*/
string pigLatinify(string input) {
	// Handle the vowels and cases with q differently
	switch (input[0]) {
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'u':
	//case 'y': <- decided y sound too much like a consonant
		return input + "-way";
	case 'q':
		if (input[1] == 'u') {
			return input.substr(2) + "-quay";
		}
		else {
			return input.substr(1) + "-qay";
		}
	default:
		return input.substr(1) + "-" + input[0] + "ay";
	}
}

int main() {
	///////////////////////////////////////////////////////////////////////////
	// POINT //////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	// Run tests of the implemented classes and class features
	cout << "For the following classes the actual result and then the expected" << endl;
	cout << "are listed. Verify that each call works as expected." << endl;

	// Test the Point class
	cout << "\nTest the Point Class:" << endl;
	// Constructors and accessors
	Point test1 = Point();
	cout << "Point 1: "<< test1.getX() << ", " << test1.getY() << endl;
	cout << "Expected Result: (0, 0)" << endl;
	Point test2 = Point(1, 2);
	cout << "Point 2: " << test2.getX() << ", " << test2.getY() << endl;
	cout << "Expected Result: (1, 2)" << endl;
	// Mutators
	test2.setX(10);
	test2.setY(10);
	cout << "Point 2: " << test2.getX() << ", " << test2.getY() << endl;
	cout << "Expected Result: (10, 10)" << endl;
	
	///////////////////////////////////////////////////////////////////////////
	// POINTARRAY /////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	// Test PointArray class
	cout << "\nTest the PointArray Class:" << endl;
	// Default Constructors
	PointArray test3 = PointArray();
	test3.print();
	cout << endl;
	cout << "Expected Result: Nothing to print" << endl;

	// Array of Points Constructor
	Point arrayOfPoints[] = { test1, test2 };
	PointArray test4 = PointArray(arrayOfPoints, 2);
	test4.print();
	cout << endl;
	cout << "Expected Result: (0, 0) (10, 10)" << endl;

	// Copy Constructor
	PointArray test5 = PointArray(test4);
	test4.push_back(test1);
	cout << "Make sure that PointArray test4 is distinct from PointArray test5:" << endl;
	cout << "Test 4: ";
	test4.print();
	cout << endl;
	cout << "Expected Result: (0, 0) (10, 10) (0, 0)" << endl;
	cout << "Test 5: " << endl;
	test5.print();
	cout << endl;
	cout << "Expected Result: (0, 0) (10, 10)" << endl;

	// Modify the initializing arrays
	arrayOfPoints[0].setX(100);
	cout << "Should remain unchanged if deep copied properly:" << endl;
	cout << "Test 4: " << endl;
	test4.print();
	cout << endl;
	cout << "Expected Result: (0, 0) (10, 10) (0, 0)" << endl;
	cout << endl;
	cout << "Test 5: ";
	test5.print();
	cout << endl;
	cout << "Expected Result: (0, 0) (10, 10)" << endl;

	// Insert
	test3.insert(5, test2);
	cout << "Check that inserted at proper place:" << endl;
	test3.print();
	cout << endl;
	cout << "Expected Result: (0, 0) (0, 0) (0, 0) (0, 0) (10, 10)" << endl;
	test2.setX(3);
	test2.setY(-3);
	test3.insert(0, test2);
	cout << "Check that inserted at proper place:" << endl;
	test3.print();
	cout << endl;
	cout << "Expected Result: (3, -3) (0, 0) (0, 0) (0, 0) (0, 0) (10, 10)" << endl;
	test2.setX(1);
	test2.setY(1);
	test3.insert(3, test2);
	cout << "Check that inserted at proper place:" << endl;
	test3.print();
	cout << endl;
	cout << "Expected Result: (3, -3) (0, 0) (0, 0) (1, 1) (0, 0) (0, 0) (10, 10)" << endl;

	// Remove
	test3.remove(-1);
	test3.remove(100);
	test3.remove(3);
	cout << "Check removed at proper place:" << endl;
	test3.print();
	cout << endl;
	cout << "Expected Result: (3, -3) (0, 0) (0, 0) (0, 0) (0, 0) (10, 10)" << endl;

	// getSize
	cout << "Current size: " << test3.getSize() << endl;
	cout << "Expected Result: 6" << endl;

	// Clear
	test3.clear();
	test3.print();
	cout << endl;
	cout << "Expected Result: Nothing to print" << endl;
	cout << "Current size: " << test3.getSize() << endl;
	cout << "Expected Result: 0" << endl;

	// get - non-constant
	Point test6 = Point(1, 2);
	test3.push_back(test6);
	Point* test7 = test3.get(0);
	test7->setX(0);
	test7->print();
	cout << endl;
	cout << "Expected Result: (0, 2)" << endl;
	test3.print();
	cout << endl;
	cout << "Expected Result: (0, 2)" << endl;
	cout << "Non-constant pointer pointing to contents of array should allow modification of array." << endl;

	// get - constant
	const Point* test8 = test3.get(0);
	test8->print();
	cout << endl;
	cout << "Expected Result: (0, 2)" << endl;
	cout << "Just want to make sure it works with the constant key word." << endl;

	cout << "DONE~\n" << endl;

	///////////////////////////////////////////////////////////////////////////
	// POLYGON ////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	// Test the program from 5.7
	// Note: because polygon is pure virtual, we can't actually test anything
	// directly in the Polygon class. Also, the constructors implemented there
	// are pointless unless we want to make a general polygon. They might have
	// a purpose if it is later decided that polygon class is not going to be
	// pure virtual.

	// Test Rectangle
	cout << "Test Rectangle/Polygon classes:" << endl;
	Point point1 = Point();
	Point point2 = Point(1, 1);
	Rectangle rect1 = Rectangle(point1, point2);
	Rectangle* rect2 = new Rectangle(0, 0, 1, 1);
	cout << "After initializing 2 rectangles:" << endl;
	cout << "Number of Polygons: " << rect1.getNumPolygons() << " (Expect 2)" << endl;
	cout << "First Rectagle:" << endl;
	cout << "Number of sides on rectangle:  " << rect1.getNumSides() << " (Expect 4)" << endl;
	cout << "Area: " << rect1.area() << " (Expect 1.)" << endl;
	// Print out all the points
	const PointArray* rect1Points = rect1.getPoints();
	cout << "Vertices in rect1: " << endl;
	cout << "Expect: (0, 0), (1, 0), (1, 1), (0, 1)" << endl;
	for (int i = 0; i < rect1.getNumSides(); i++) {
		cout << "(" << rect1Points->get(i)->getX() << ", " << rect1Points->get(i)->getY() << ")" << ", ";
	}
	cout << endl;

	// Repeat for second rectangle
	cout << "Second Rectangle:" << endl;
	cout << "Number of sides on rectangle:  " << rect2->getNumSides() << " (Expect 4)" << endl;
	cout << "Area: " << rect2->area() << " (Expect 1.)" << endl;
	// Print out all the points
	const PointArray* rect2Points = rect2->getPoints();
	cout << "Vertices in rect1: " << endl;
	cout << "Expect: (0, 0), (1, 0), (1, 1), (0, 1)" << endl;
	for (int i = 0; i < rect2->getNumSides(); i++) {
		cout << "(" << rect2Points->get(i)->getX() << ", " << rect2Points->get(i)->getY() << ")" << ", ";
	}
	cout << endl;

	// Delete the second rectangle and see if the number of polygons is correct
	cout << "After deleting one Polygon:" << endl;
	delete rect2;
	cout << "Number of Polygons: " << rect1.getNumPolygons() << " (Expect 1)" << endl;

	// Test Triangle
	Point point3 = Point(0, 2);
	Triangle tri1 = Triangle(point1, point2, point3);
	cout << "Triangle:" << endl;
	cout << "Number of Polygons: " << rect1.getNumPolygons() << " (Expect 2)" << endl;
	cout << "Number of sides on triangle:  " << tri1.getNumSides() << " (Expect 3)" << endl;
	cout << "Area: " << tri1.area() << " (Expect 1)" << endl;
	// Print out all the points
	const PointArray* tri1Points = tri1.getPoints();
	cout << "Vertices in rect1: " << endl;
	cout << "Expect: (0, 0), (1, 0), (0, 2)" << endl;
	for (int i = 0; i < tri1.getNumSides(); i++) {
		cout << "(" << tri1Points->get(i)->getX() << ", " << tri1Points->get(i)->getY() << ")" << ", ";
	}
	cout << endl;

	// Test part 5.7
	exercise5_7();

	///////////////////////////////////////////////////////////////////////////
	// PIG LATIN //////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	
	// Test Pig Latin code:
	cout << "Pig Latin versions of various test words:" << endl;
	cout << "test: " << pigLatinify("test") << endl;
	cout << "alleviate: " << pigLatinify("alleviate") << endl;
	cout << "quack: " << pigLatinify("quack") << endl;
	cout << "qabalistic: " << pigLatinify("qabalistic") << endl;
	// ^^^SCRABBLE!!!^^^ 
	cout << "island: " << pigLatinify("island") << endl;
	cout << "elevation: " << pigLatinify("elevation") << endl;
	cout << "opulence: " << pigLatinify("opulence") << endl;
	cout << "usual: " << pigLatinify("usual") << endl;
}