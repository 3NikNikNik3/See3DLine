#pragma once

#include "Graphics.hpp"

namespace See3DLine {
	namespace Screens {
		class Screen {
		public:
			virtual void draw(Rectangle rec) = 0;

			virtual void logic() = 0;
		};
	}
}