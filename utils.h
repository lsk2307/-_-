#pragma once

#define PI 3.14159f
#define PI2 PI * 2

#define FLOAT_EPSILON 0.001f	//실수의 가장 작은 단위를 지칭하는 그리스어가 엡실론
#define FLOAT_EQUAL(f1, f2) (fabs(f1, f2) <= FLOAT_EPSILON)	//두 실수가 같은지 비교 가능
#define FLOAT_TO_INT(f1) static_cast<int>(f1 + FLOAT_EPSILON) //실수형을 정수형으로

namespace TTYONE_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY);

	float getAngle(float x1, float y1, float x2, float y2);
}