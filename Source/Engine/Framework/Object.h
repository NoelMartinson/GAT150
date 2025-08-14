#pragma once

namespace fox {
	class Object {
	public:
		std::string name;
		bool active{ true };


	protected:
		Object() = default;
		virtual ~Object() = default;
	};
}	