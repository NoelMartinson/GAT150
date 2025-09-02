#include "EnginePCH.h"
#include "Core/StringHelper.h"

namespace fox {
	void EventManager::AddObserver(const Event::id_t id, IObserver& observer) {
		observers[tolower(id)].push_back(&observer);
	}

	void EventManager::RemoveObserver(IObserver& observer) {
		IObserver* observerPtr = &observer;
		for (auto& eventType : observers) {
			auto& observerList = eventType.second;
			observerList.remove(observerPtr);

			std::erase_if(observerList, [observerPtr](auto observer) {
				return (observer == observerPtr);
			});
		}
	}

	void EventManager::Notify(const Event& event){
		auto it = observers.find(tolower(event.id));
		if (it != observers.end()) {
			auto& observers = it->second;
			for (auto& observer : observers) {
				observer->OnNotify(event);
			}
		}
		else {
			Logger::Warning("Could not find event '{}'", event.id);
		}
	}
}