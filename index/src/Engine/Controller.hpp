#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class Controller {
    private:
        std::map<std::string, sf::Keyboard::Key> actionMap;
    public:

        bool hasInputAction (std::string action) {
            return actionMap.find (action) != actionMap.end ();
        }

        bool isActionPressed (std::string action) {
            auto mapIter = actionMap.find (action);
            return (mapIter == actionMap.end() ? false : sf::Keyboard::isKeyPressed(mapIter->second));
        }

        void removeAction (std::string action) {
            auto mapIter = actionMap.find (action);

            if (mapIter == actionMap.end ())
                return;

            actionMap.erase (mapIter);
        }

        void setAction (std::string action, sf::Keyboard::Key key) {
            actionMap.insert (std::pair<std::string, sf::Keyboard::Key>(action, key));
        }
};
