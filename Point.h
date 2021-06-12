class Point {

public:
    Point(){};
    Point(double, double, double, unsigned);
	bool operator==(Point);
	void print();
	int getId();
	double getX();
	double getY();
	double getZ();
        Point setId(int);
        Point setX(double);
        Point setY(double);
        Point setZ(double);

private:
    double x;
    double y;
    double z;
    unsigned ident;
};

