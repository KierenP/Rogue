#include "MathLib.h"
#include <iostream>
#include <string>

using namespace::MathLib;

int main()
{
	Vector3 A(2, 3, 4);
	Vector3 B(5, 6, 7);
	Vector3 C = CrossProduct(A, B);

	std::cout << "Calculating Cross Product of (2, 3, 4) and (5, 6, 7):\n\n";
	std::cout << "X = " << C.x << ", Y = " << C.y << ", Z = " << C.z << "\n\n";

	std::string MyString;
	std::cin >> MyString;	//Delay the program closing

}