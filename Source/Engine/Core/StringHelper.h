#pragma once
#include <string>

namespace fox {
	inline std::string tolower(const std::string& str) {
		std::string result = str;

		for (char c : result) {
			c = std::tolower(c);
		}

		return result;
	}

	inline std::string toupper(const std::string& str) {
		std::string result = str;

		for (char c : result) {
			c = std::toupper(c);
		}

		return result;
	}

	inline bool equalsIgnoreCase(const std::string& sA, const std::string& sB) {
		if (sA.length() != sB.length()) return false;

		return std::equal(sA.begin(), sA.end(), sB.begin(),[](char cA, char cB) {
			return (std::tolower(cA) == std::tolower(cB));
		});
	}
}
