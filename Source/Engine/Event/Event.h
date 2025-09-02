#pragma once
#include <string>
#include <variant>

namespace fox{
	struct Event{
		using id_t = std::string;
		using data_t = std::variant<int, float, std::string>;

		id_t id;
		data_t data;
		Event(const id_t& id, const data_t& data) : 
			id{ id }, 
			data{ data } 
		{}
	};
}