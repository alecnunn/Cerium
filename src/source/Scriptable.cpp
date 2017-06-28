#include "../include/Cerium/Scriptable.hpp"

#include "../include/Cerium/Person.hpp"

#include "../include/Cerium/EventManager.hpp"

#include <fstream>

namespace cerium
{
    Person * bPerson;

    void l_move(const float & x, const float & y)
    {
        bPerson->move({x ,y});
    }


    void l_setPosition(const float & x, const float & y)
    {
        bPerson->setPosition({x, y});
    }


    void l_rotate(const float & angle)
    {
        bPerson->rotate(angle);
    }


    void l_setRotation(const float & angle)
    {
        bPerson->setRotation(angle);
    }


    bool l_isKeyPressed(int key)
    {
        return EventManager::isKeyPressed(key);
    }


    Scriptable::Scriptable(Person * basePerson, Prop * parent, const std::string & name, const std::string & path)
            : Prop(basePerson, parent, name)
    {
        bPerson = basePerson;

        std::ifstream file(path.c_str());
        std::string content;
        std::string line;
        while(std::getline(file, line))
        {
            content += line + "\n";
        }

        file.close();

        state.open_libraries(sol::lib::base);
        state.script(content);

        state.set_function("move", l_move);
        state.set_function("rotate", l_rotate);

        state.set_function("setPosition", l_setPosition);
        state.set_function("setRotation", l_setRotation);

        state.set_function("isKeyPressed", l_isKeyPressed);

        state["init"]();
    }


    void Scriptable::update(const float & deltaTime)
    {
        bPerson = basePerson;
        state["update"](deltaTime);
    }
}