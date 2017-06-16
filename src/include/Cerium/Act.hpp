#ifndef CERIUM_ACT_HPP
#define CERIUM_ACT_HPP

#include <unordered_map>
#include <iostream>

namespace cerium
{
    class Person;
    class Act
    {
    public:
        /*
            ^[name][draw]
            ^[class][Act]
            ^[description][Draws all the persons in Act]
        */
        void draw(void); //^header
        /*
            ^[name][update]
            ^[class][Act]
            ^[description][Updates all the persons in Act]
            ^[argument]<deltaTime>[DeltaTime of main game clock]
        */
        virtual void update(const float & deltaTime); //^header
        /*
            ^[name][add]
            ^[class][Act]
            ^[description][Adding new person with given name]
            ^[argument]<name>[Name of new Person]
            ^[argument]<person>[Pointer to Person]
        */
        void add(const std::string & name, Person * person); //^header
        /*
            ^[name][remove]
            ^[class][Act]
            ^[description][Removing person with given name]
            ^[argument]<name>[Name of Person to remove]
        */
        void remove(const std::string name); //^header
        /*
            ^[name][clear]
            ^[class][Act]
            ^[description][Removing all Persons]
        */
        void clear(void); //^header
        /*
            ^[name][exist]
            ^[class][Act]
            ^[description][Checking existing of Person with given name]
            ^[argument]<name>[Name of Person to remove]
        */
        bool exist(const std::string & name); //^header
        /*
            ^[name][get]
            ^[class][Act]
            ^[description][Getting Person from Act with given name]
            ^[argument]<name>[Name of Person to remove]
            ^[returns][Pointer to Person with given name]
        */
        Person * get(const std::string & name); //^header
    protected:
        std::unordered_map<std::string, Person*> persons;
    };
}

#endif