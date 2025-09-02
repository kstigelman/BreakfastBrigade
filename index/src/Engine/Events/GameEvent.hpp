#pragma once
#include <SFML/Graphics.hpp>

#include "../GameSettings.hpp"
#include "../../Entity/Entity.hpp"


class GameEvent : public sf::Event {
    public:
        char* id;

        GameEvent (char id_[8]) : id(id_) {}
};


class EntityMoveEvent : public GameEvent {
    sf::Vector2f oldPosition;
    sf::Vector2f newPosition;

    Entity* owner;

    EntityMoveEvent (Entity* owner) : GameEvent ("EMOV"), owner(owner) {}
};

class EntityDamageEvent : public GameEvent {
    Entity* owner;
    Entity* source;

    EntityDamageEvent (Entity* source, Entity* target) : GameEvent ("EDMG"), owner(owner), source(source) {}
};

class EntityCollideEvent : public GameEvent {
    Entity* e1;
    Entity* e2;

    EntityCollideEvent (Entity* e1, Entity* e2) : GameEvent ("EECOLIDE"), e1(e1), e2(e2) {}
};


