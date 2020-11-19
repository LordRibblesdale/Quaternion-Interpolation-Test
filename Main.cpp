#include <iostream>
#include "Quaternion/QuaternionInterpolation.h"
#include "Matrix/StandardMatrix.h"

int main() {
   Float3 direction(0, 0, 1);
   Float3 point(5, 1, 2);
   QuaternionInterpolation qi(degree2Radiants(50), direction, point);

   std::cout << "Rotation t=0\n";
   std::cout << qi.getInterpolation(0).toString();

   std::cout << "Rotation t=0.2\n";
   std::cout << qi.getInterpolation(0.2).toString();

   std::cout << "Rotation t=0.4\n";
   std::cout << qi.getInterpolation(0.4).toString();

   std::cout << "Rotation t=0.56\n";
   std::cout << qi.getInterpolation(0.56).toString();

   std::cout << "Rotation t=0.9\n";
   std::cout << qi.getInterpolation(0.9).toString();

   std::cout << "Rotation t=1\n";
   std::cout << qi.getInterpolation(1).toString();

   return 0;
}