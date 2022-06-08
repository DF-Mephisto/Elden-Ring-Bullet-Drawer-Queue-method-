#include "VectorTransformer.h"

fPOINT VectorTransformer::rotate2D(float angle, fPOINT p)
{
	float rotationMatrix[][2] = {
		{cos(angle), sin(angle)},
		{-sin(angle), cos(angle)}
	};

	float coordMatrix[] = { p.x, p.y };
	float resMatrix[2] = { 0 };

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			resMatrix[i] += rotationMatrix[i][j] * coordMatrix[j];
		}
	}

	return fPOINT{ resMatrix[0], resMatrix[1] };
}