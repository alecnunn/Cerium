#include "../include/Cerium/vec2.hpp"
#include "../include/Cerium/Window.hpp"
#include "../include/Cerium/EventManager.hpp"
#include "../include/Cerium/Act.hpp"
#include "../include/Cerium/VertexArray.hpp"
#include "../include/Cerium/Scriptable.hpp"
#include "../include/Cerium/Camera.hpp"
#include "../include/Cerium/ActManager.hpp"
#include "../include/Cerium/ResourceManager.hpp"
#include "../include/Cerium/ShaderProgram.hpp"
#include "../include/Cerium/Person.hpp"
#include "../include/Cerium/Clock.hpp"
#include "../include/Cerium/Texture.hpp"
#include "../include/Cerium/TextureSource.hpp"

#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

class Player : public cerium::Person
{
public:
    Player(const std::string & name, cerium::Act * baseAct) : cerium::Person(name, baseAct)
    {
        setPosition({10});
        setSize({64});
        setRotation(0);

        addProp(new cerium::VertexArray(this));
        addProp(new cerium::Scriptable(this));
        addProp(new cerium::Texture(this, dynamic_cast<cerium::TextureSource*>(cerium::ResourceManager::get("texture"))));
    }
};

class Other : public cerium::Person
{
public:
    Other(const std::string & name, cerium::Act * baseAct) : cerium::Person(name, baseAct)
    {
        setPosition({100});
        setSize({64});
        setRotation(0);

        addProp(new cerium::VertexArray(this));
    }
};

class MyAct : public cerium::Act
{
public:
    MyAct()
    {
        add(new Other("other", this));
        add(new Player("player", this));
    }
};

cerium::vec2 size_of_window()
{
    rapidxml::file <> file("settings.xml");
    rapidxml::xml_document<> settings;
    settings.parse<0>(file.data());

    rapidxml::xml_node <> * size = settings.first_node("settings")->first_node("size");

    int width = atoi(size->first_attribute("width")->value());
    int height = atoi(size->first_attribute("height")->value());
    return { (float)width, (float)height};
}

int main()
{
    cerium::Window::setSize(size_of_window());
    cerium::Window::setTitle("Cerium");

    cerium::Window::init();
    cerium::Camera::init();

    cerium::ResourceManager::add("texture", new cerium::TextureSource("texture.png"));
    cerium::ResourceManager::add("shader", new cerium::ShaderProgram("vertexShader.glsl", "fragmentShader.glsl"));
    cerium::ResourceManager::add("timer", new cerium::Clock);

    cerium::ActManager::add("main", new MyAct);
    cerium::ActManager::setCurrent("main");

    while(!cerium::EventManager::isWindowClosed())
    {
        cerium::ResourceManager::get("timer")->use();
        cerium::EventManager::pollEvents();
        cerium::Window::clear();

        cerium::ActManager::updateCurrent(dynamic_cast<cerium::Clock*>(cerium::ResourceManager::get("timer"))->getDeltaTime());
        cerium::ActManager::drawCurrent();

        cerium::Window::render();
    }

    return 0;
}