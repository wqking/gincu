#ifndef GMATRIX_H
#define GMATRIX_H

#include "gincu/ggeometry.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

namespace gincu {

typedef glm::mat4 GMatrix44;

extern const GMatrix44 identityMatrix;

inline GMatrix44 translateMatrix(const GMatrix44 & matrix, const GPoint & p)
{
	return glm::translate(matrix, { p.x, p.y, 0 });
}

inline GMatrix44 scaleMatrix(const GMatrix44 & matrix, const GScale & scale)
{
	return glm::scale(matrix, { scale.x, scale.y, 1 });
}

inline GMatrix44 inverseMatrix(const GMatrix44 & matrix)
{
	return glm::inverse(matrix);
}

inline GPoint transformPoint(const GMatrix44 & matrix, const GPoint & point)
{
	auto p = matrix * glm::vec4 { point.x, point.y, 0, 1 };
	return { p.x, p.y };
}


} //namespace gincu




#endif

