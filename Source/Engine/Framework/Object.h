#pragma once
#include <string>
#include "Core/Serializable.h"

namespace fox {
	class Object : public Serializable {
	public:
		std::string name;
		bool active{ true };

	public:
		Object() = default;
		virtual ~Object() = default;

		// Inherited via Serializable
		void Read(const json::value_t& value) override;
	};
}	