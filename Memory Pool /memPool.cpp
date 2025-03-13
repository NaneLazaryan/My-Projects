
#include "memPool.h"

class Test {
private:
	int x;
	double y;
public:
	Test(int x1, double y1) :x(x1), y(y1) {
		std::cout << "Test constructor" << std::endl;
		std::cout << "x = " << x << " y = " << y << std::endl;
	}

	~Test() {
		std::cout << "Test destructor" << std::endl;
	}
};

int main() {
	memPool<Test> pool(5);
	std::cout << "--------------------" << std::endl;
	Test* obj1 = pool.newElement(7, 8);
	std::cout << "--------------------" << std::endl;
	Test* obj2 = pool.newElement(0, 12);
	std::cout << "--------------------" << std::endl;


	pool.deleteElement(obj1);
	pool.deleteElement(obj2);

	return 0;
}
