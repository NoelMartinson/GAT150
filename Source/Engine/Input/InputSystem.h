#pragma once
#include "../Math/Vector2.h"
#include <vector>
#include <array>

namespace fox {
	class InputSystem {
	public:
		enum class MouseButton : uint8_t {
			Left,
			Middle,
			Right
		};

	public:
		InputSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update();
		bool GetKeyDown(uint8_t key) const { return m_keyboardState[key]; }
		bool GetPrevKeyDown(uint8_t key) const { return m_previousKeyboardState[key]; }
		bool GetKeyPressed(uint8_t key) const { return !m_previousKeyboardState[key] && m_keyboardState[key]; }
		bool GetKeyReleased(uint8_t key) const { return m_previousKeyboardState[key] && !m_keyboardState[key]; }

		vec2 GetMousePosition() const { return m_mousePosition; }
		vec2 GetPreviousMousePosition() const { return m_previousMousePosition; }

		bool GetMouseButtonDown(MouseButton button) const {  return m_mouseButtonState[(uint8_t)button]; }
		bool GetPreviousMouseButtonDown(MouseButton button) const {  return m_mouseButtonState[(uint8_t)button]; }

	private:
		std::vector<bool> m_keyboardState{ 0, 0 };
		std::vector<bool> m_previousKeyboardState;

		vec2 m_mousePosition;
		vec2 m_previousMousePosition;

		std::array<bool, 3> m_mouseButtonState{ false, false, false };
		std::array<bool, 3> m_previousMouseButtonState{ false, false, false };
	};
}