//
// Created by Green on 19/11/2020.
//

#ifndef QUATERNIONTEST_QUATERNIONINTERPOLATION_H
#define QUATERNIONTEST_QUATERNIONINTERPOLATION_H

#include "../Vector/Float4.h"
#include "../Matrix/SquareMatrix.h"

class QuaternionInterpolation {
   //private not necessary
private:
   float angle;
   float t = 0;

   Float3 direction;
   Float3 vector;

   SquareMatrix rotation = std::move(SquareMatrix(3, {1,   0,   0,
                                                      0,   1,   0,
                                                      0,   0,   1}));

   void resetRotationMatrix();

public:
   QuaternionInterpolation(float angle, const Float3& direction, const Float3& vector);

   Float3 getInterpolation(float t);

   void setAngle(float startingAngle);

   void setDirection(const Float3 &direction);
};


#endif //QUATERNIONTEST_QUATERNIONINTERPOLATION_H
