#pragma once

#include <cmath>

namespace See3DLine {
	namespace Math {
		struct Vector3
		{
			float x, y, z;

			Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

			Vector3 operator+(Vector3 vec);

			Vector3 operator-(Vector3 vec);

			Vector3 operator-();

			void operator+=(Vector3 vec);

			Vector3 operator*(float num);

			double len();
		};

		struct Vector2
		{
			float x, y;

			Vector2(float x = 0, float y = 0) : x(x), y(y) {}

			static Vector2 Zero;

			Vector2 operator+(Vector2 vec);

			Vector2 operator-(Vector2 vec);

			Vector2 operator-();

			double len();
		};

		// It has little math's matrix, but it is comfortable!
		struct Matrix
		{
			Vector3 i, j, k;

			Matrix(float arr[3][3]);

			Matrix(Vector3 i, Vector3 j, Vector3 k) : i(i), j(j), k(k) {}

			Matrix operator*(Matrix& matrix);

			void operator*=(Matrix& matrix);

			Vector3 run(Vector3 vec);
		};
	}
}