
class Point {
public:
    Point(double x, double y) 
        : mX{x}, mY{y} {}
    double getX() {return mX;}
    double getY() {return mY;}
    void increasePosition(double incX, double incY) {mX += incX; mY += incY};
    
private:
    double mX, mY;
};