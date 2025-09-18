#pragma once

class Collider;

class Collision {
    Collider* collider;
    bool bBlocking;
    std::string tag;
    Collision (Collider* collider, bool bBlocking, std::string tag = "null") : collider(collider), bBlocking(bBlocking), tag(tag) {
    }
    const std::string& getTag () {
        return tag;
    }
};