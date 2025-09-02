#pragma once

namespace fox{
	class IObserver {
	public:
		virtual ~IObserver();

		virtual void OnNotify(const Event& event) = 0;
	};
}