#include "Time.h"

namespace fox {
	void Time::Tick() {
		clock::time_point now = clock::now();
		time = std::chrono::duration<float>(now - startTime).count();
		deltaTime = std::chrono::duration<float>(now - frameTime).count();
		frameTime = now;
	}
}