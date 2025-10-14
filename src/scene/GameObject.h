#pragma once

#include "../renderer/Mesh.h"
#include "TransformComponent.h" // <-- Use the standalone TransformComponent
#include <memory>
#include <unordered_map>

class GameObject {
public:
    using id_t = unsigned int;
    using Map = std::unordered_map<id_t, GameObject>;

    static GameObject createGameObject() { // <-- Return by value for simplicity
        static id_t currentId = 0;
        return GameObject{currentId++};
    }

    // No copying, but allow moving
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;
    GameObject(GameObject&&) = default;
    GameObject& operator=(GameObject&&) = default;

    id_t getId() const { return id; }

    std::shared_ptr<Mesh> mesh{};
    glm::vec3 color{};
    TransformComponent transform{};

private:
    GameObject(id_t objId) : id(objId) {}
    id_t id;
};