#ifdef INCLUDE_UP
	#include "../hpp/Math.hpp"
#else
	#include "hpp/Math.hpp"
#endif

namespace See3DLine::Math {
	// Vector3
	Vector3 Vector3::operator+ (Vector3 vec) {
		return { x + vec.x, y + vec.y, z + vec.z };
	}

	Vector3 Vector3::operator-() {
		return { -x, -y, -z };
	}

	Vector3 Vector3::operator-(Vector3 vec) {
		return { x - vec.x, y - vec.y, z - vec.z };
	}

	void Vector3::operator+=(Vector3 vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}

	Vector3 Vector3::operator*(float num) {
		return { x * num, y * num, z * num };
	}

	double Vector3::len() {
		return sqrt(x * x + y * y + z * z);
	}

	// Matrix
	Matrix::Matrix(float arr[3][3]) : i({ arr[0][0], arr[1][0], arr[2][0] }), j({ arr[0][1], arr[1][1], arr[2][1] }), k({ arr[0][2], arr[1][2], arr[2][2] }) {}

	Matrix Matrix::operator*(Matrix &matrix) {
		return { matrix.run(i), matrix.run(j), matrix.run(k) };
	}

	void Matrix::operator*=(Matrix matrix) {
		Matrix m_ = *this * matrix;
		i = m_.i;
		j = m_.j;
		k = m_.k;
	}

	Vector3 Matrix::run(Vector3 vec) {
		return { vec.x * i.x + vec.y * j.x + vec.z * k.x,
			     vec.x * i.y + vec.y * j.y + vec.z * k.y,
				 vec.x * i.z + vec.y * j.z + vec.z * k.z };
	}
}
