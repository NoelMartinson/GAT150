#include "Observer.h"

namespace fox {
	fox::IObserver::~IObserver() {
		OBSERVER_REMOVE_SELF;
	};
}