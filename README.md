# MIT OCW 6.096 - Introduction to C++
## Assignment 3
Nominally, I would submit this file with the assignment. However, since this is all taken from MIT Open Course Ware, it will just be my version of the solutions posted there (https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-096-introduction-to-c-january-iap-2011/assignments/). I've answered the questions asked in the assignment here. I've constructed the solutions to the various parts of the assignment in the various files. The `geometry.h` file contains the class definitions for all the different objects created as part of this assignment with the implementations found in `geometry.cpp`. The file `mainA3.cpp` provides the tests I did to verify that my code works as expected as well as some of the solutions for part 5 and part 6. In addition verifying the code works as expected, I also tested with valgrind to make sure there were no memory leaks.

Since part 5.7 requires user input I've also included a text file, `input.txt` that can be piped in for testing. Thus, after compiling using the command:
`output < input.txt > output.txt`
Should run the code piping the output into a text file.

In addition to the code, I've answered the questions posed in the assignment document below.
### 2 Catch the Bug
Find the bugs in the following snippets.
#### 2.1
```
class Point{
private :
	int x, y;

public :
	Point(int u, int v) : x(u), y(v) {}
	int getX() { return x; }
	int getY() { return y; }
	void doubleVal(){
		x *= 2;
		y *= 2;
	}
};

int main(){
	const Point myPoint(5, 3);
	myPoint.doubleVal();
	cout << myPoint.getX() << " " << myPoint.getY() << "\n";
	return 0;
}
```
The `myPoint` is constant but `doubleVal`, `getX`, and `getY` are not constant functions. Even if the accessors were constant functions, `doubleVal` attempts to change the fields of the instance of the `Point` class. It could not be a constant function at all.
#### 2.2
```
class Point{
private :
	int x, y;

public :
	Point(int u, int v) : x(u), y(v) {}
	int getX() { return x; }
	int getY() { return y; }
	void setX(int newX) const { x = newX;}
};

int main(){
	Point p(5, 3);
	p. setX (9001) ;
	cout << p.getX () << ' ' << p.getY ();
	return 0;
}
```
The function `setX` claims to be constant when it attempts to change one of the fields. This is not allowed.
#### 2.3
```
class Point{
private :
	int x, y;

public :
	Point(int u, int v) : x(u), y(v) {}
	int getX() { return x; }
	int getY() { return y; }
};

int main(){
	Point p(5, 3);
	cout << p.x << " " << p.y << "\n";
	return 0;
}
```
The fields `x` and `y` are private and need to be accessed with `getX` and `getY` respectively. Calling `p.x` or `p.y` produces an error.
#### 2.4
```
class Point{
private:
	int x, y;

public:
	Point(int u, int v): x(u), y(v) {}
	int getX() { return x; }
	void setX(int newX );
};

void setX (int newX ){ x = newX; }

int main(){
	Point p(5, 3);
	p.setX (0);
	cout << p.getX () << " " << "\n";
	return 0;
}
```
The `setX` declared above is not scoped to the function. It is instead a brand new function called `setX` that effectively does nothing. To properly scope it put `Point::setX` instead of just `setX`.
#### 2.5
```
int size;
cin >> size;
int* nums = new int[ size ];
for(int i = 0; i < size; ++i){
	cin >> nums[i];
}
// Calculations with nums omitted
delete nums;
```
This is the wrong delete for arrays. You must use `delete[]` to properly clean up the memory associated with arrays.
#### 2.6
```
class Point{
private:
	int x, y;
public:
	Point(int u, int v) : x(u), y(v) {};
	int getX() { return x; }
	int getY() { return y; }
};

int main(){
	Point *p = new Point(5, 3);

	cout << p->getX() << ' ' << p->getY();
	return 0;
}
```
The solution says that the memory was created for `p` but never cleaned up. I understand why this is an important habit. Since the main method is closing and the program is terminating, the memory will automatically be cleaned up. This will be done by most, but not all systems. Thus, an explicit delete is a best practice.

### 5 Polygon
#### 5.2
PointArray is really just a pointer and an integer. C++ does not see the pointer as an array (even though it is). So, when we use the default Copy Constructor it will only shallow copy that pointer. Thus, the internals of each Polygon stored in the PointArray will actually point to the same data. Both Polygons will effectively be the same as the points cannot be separately manipulated.

#### 5.6
1. If the constructors were private, we would not be able to call them. This would create problems specifically for this class as we would always attempt to call one of the implemented constructors due to the default arguments. We would not ever be able to build a point as even `Point()` is private.
2. The `PointArray` is deleted using it's destructor and the count is decremented. Note, the count lives in static memory, so it isn't really carried around by any instance of the `Polygon` object. This also means it really does not get deallocated until the program quits. Static is forever.
3. Protected makes it so the child classes can access and modify the fields.
4. It would call the version from the Polygon class, because the function `getNumSides` is not virtual.