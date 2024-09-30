#include "hpp/Math.hpp"

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

	double Vector3::len() {
		return sqrt(x * x + y * y + z * z);
	}

	// Vector2
	Vector2 Vector2::operator+(Vector2 vec) {
		return { x + vec.x, y + vec.y };
	}

	Vector2 Vector2::operator-() {
		return { -x, -y };
	}

	Vector2 Vector2::operator-(Vector2 vec) {
		return { x - vec.x, y - vec.y };
	}

	double Vector2::len() {
		return sqrt(x * x + y * y);
	}
}