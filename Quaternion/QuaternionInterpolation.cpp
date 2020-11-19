//
// Created by Green on 19/11/2020.
//

#include <iostream>
#include "QuaternionInterpolation.h"
#include "../Matrix/StandardMatrix.h"

QuaternionInterpolation::QuaternionInterpolation(float angle, const Float3& direction, const Float3& vector)
      : angle(angle), direction(direction), vector(vector) {
   // Dimension = 3 because of quaternion rotation matrix

   float norm = direction.l2Norm();

   if (norm == 0) {
      std::string log("EXCEPTION: null direction . \nDirection: ");
      log.append(direction.toString());
      log.append("; Norm: ");
      log.append(std::to_string(norm));

      throw ExceptionNotifier(log.c_str());
   }
}

void QuaternionInterpolation::resetRotationMatrix() {
   if (t == 0) {
      rotation = std::move(SquareMatrix(3, {1,   0,   0,
                                            0,   1,   0,
                                            0,   0,   1}));
   } else {
      //TODO check normalization (to delete s)
      /*
      float sin = sinf(t* angle * 0.5f);
      float q1 = direction.getX() * sin;
      float q2 = direction.getY() * sin;
      float q3 = direction.getZ() * sin;
      float q4 = cosf(t* angle * 0.5f);
      float s = 2/(q1*q1 + q2*q2 + q3*q3 + q4*q4);

      rotation = std::move( SquareMatrix(3, {1-s*(q2*q2 + q3*q3),   s*(q1*q2 - q4*q3),   s*(q1*q3 + q4*q2),
                              s*(q1*q2 + q4*q3),   1-s*(q1*q1 + q3*q3), s*(q2*q3 - q4*q1),
                              s*(q1*q3 - q4*q2),   s*(q2*q3 + q4*q1),   1-s*(q1*q1 + q2*q2)}));
                              */

      float angle_2 = t * angle * 0.5f;
      float sin = sinf(angle_2);
      float q1 = direction.getX() * sin;
      float q2 = direction.getY() * sin;
      float q3 = direction.getZ() * sin;
      float q4 = cosf(angle_2);

      float q1q1 = q1*q1;
      float q2q2 = q2*q2;
      float q3q3 = q3*q3;

      float s = 2/(q1q1 + q2q2 + q3q3 + q4*q4);

      q1q1 *= s;
      q2q2 *= s;
      q3q3 *= s;

      float q1q2 = s*q1*q2;
      float q1q3 = s*q1*q3;
      float q1q4 = s*q1*q4;
      float q2q3 = s*q2*q3;
      float q2q4 = s*q2*q4;
      float q3q4 = s*q3*q4;

      rotation = std::move(SquareMatrix(3, {1-(q2q2 + q3q3),  q1q2 - q3q4,   q1q3 + q2q4,
                                            q1q2 + q3q4, 1-(q1q1 + q3q3), q2q3 - q1q4,
                                            q1q3 - q2q4, q2q3 + q1q4,   1-(q1q1 + q2q2)}));
   }
}

Float3 QuaternionInterpolation::getInterpolation(float t) {
   QuaternionInterpolation::t = t;

   resetRotationMatrix();

   return Float3(rotation.multiplyVector(vector));
}

void QuaternionInterpolation::setAngle(float angle) {
   QuaternionInterpolation::angle = angle;

   resetRotationMatrix();
}

void QuaternionInterpolation::setDirection(const Float3 &direction) {
   QuaternionInterpolation::direction = direction;

   resetRotationMatrix();
}
