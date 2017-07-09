#include <GL/glew.h>
#include "../include/Cerium/Act.hpp"

#include "../include/Cerium/Person.hpp"

namespace cerium
{
    void Act::draw(void)
    {
        for (auto & person : this->persons)
        {
            glBindTexture(GL_TEXTURE_2D, 0);
            person.second->draw();
        }
    }


    void Act::update(const float & deltaTime)
    {
        for (auto & person : this->persons)
        {
            person.second->update(deltaTime);
        }
    }


    void Act::add(Person * person)
    {
        if(!exist(person->getName()))
        {
            persons.push_back(std::pair<std::string, Person*>(person->getName(), person));
        }
    }


    void Act::remove(const std::string name)
    {
        for (auto & person : persons)
        {
            if (person.first == name) delete person.second;
        }
    }


    void Act::clear(void)
    {
        for(auto & person : this->persons)
        {
            delete person.second;
        }
    }


    bool Act::exist(const std::string & name)
    {
        for(auto & person : this->persons)
        {
            if(person.first == name) return true;
        }
        return false;
    }


    Person * Act::get(const std::string & name)
    {
        for(auto & person : this->persons)
        {
            if(person.first == name) return person.second;
        }
        return nullptr;
    }
}