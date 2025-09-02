#pragma once
#include "Object.h"

namespace fox {
    class Actor;

    class Component : public Object {
    public:
        Actor* owner{ nullptr };

        Component() = default;

        virtual void Start() {}
        virtual void Destroyed() {}
        virtual void Update(float dt) = 0;
    };
}
