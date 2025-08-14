#pragma once
#include "Object.h"

namespace fox {
    class Actor;

    class Component : public Object {
    public:
        Actor* owner{ nullptr };

        Component() = default;
        virtual ~Component() = default;

        void Draw();

        virtual void Update(float dt) = 0;
    };
}
