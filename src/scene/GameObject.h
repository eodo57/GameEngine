#pragma once

#include "../renderer/Model.h" // <-- Include Model.h
#include "TransformComponent.h"
#include <memory>
#include <unordered_map>

class GameObject {
public:
    using id_t = unsigned int;
    using Map = std::unordered_map<id_t, GameObject>;

    static GameObject createGameObject() {
        static id_t currentId = 0;
        return GameObject{currentId++};
    }

    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;
    GameObject(GameObject&&) = default;
    GameObject& operator=(GameObject&&) = default;

    id_t getId() const { return id; }

    TransformComponent transform{};
    std::shared_ptr<Model> model{}; 
    bool selected = false; // New member to track selection state
    bool isSelected = false; // New member to track if the object is currently selected
    glm::vec3 color{};
   

private:
    GameObject(id_t objId) : id(objId) {}
    id_t id;
};