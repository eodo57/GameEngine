#pragma once

#include "../renderer/Mesh.h"

#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <unordered_map>

struct TransformComponent {
    glm::vec3 translation{};  // Position
    glm::vec3 scale{1.f, 1.f, 1.f};
    glm::vec3 rotation{}; // Euler angles

    // Matrix corresponds to translate * Ry * Rx * Rz * scale
    // Rotations correspond to Tait-bryan angles of Y(1), X(2), Z(3)
    // https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix
    glm::mat4 mat4();
};

class GameObject {
public:
    using id_t = unsigned int;
    using Map = std::unordered_map<id_t, GameObject>;

    static GameObject& createGameObject() {
        static id_t currentId = 0;
        GameObject gameObject{currentId++};
        GameObject& ref = gameObjects.emplace(gameObject.getId(), std::move(gameObject)).first->second;
        return ref;
    }

    static void destroyGameObject(id_t gameObjectId) {
        gameObjects.erase(gameObjectId);
    }
    
    static Map& getGameObjects() { return gameObjects; }

    // No copying or moving of game objects, must be handled by their IDs
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

    static Map gameObjects;
};
