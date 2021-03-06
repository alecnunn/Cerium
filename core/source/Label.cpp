#include "../include/Cerium/Label.hpp"

#include "../include/Cerium/Font.hpp"
#include "../include/Cerium/Person.hpp"
#include "../include/Cerium/ShaderProgram.hpp"

namespace cerium
{
    Label::Label(Person * basePerson, Prop * parent, const std::string & name, Font * font, const std::string & text, const vec4 & color) 
		: Prop(basePerson, parent, name, "Label")
    {
        this->changed = true;
        this->text = text;
        this->color = color;
        this->font = font;

		basePerson->isTextured = true;
    }


    Label::~Label()
    {
		delete font;

		SDL_FreeSurface(rawSurface);
        glDeleteTextures(1, &texture);
    }


    void Label::setText(const std::string & text)
    {
        this->changed = true;
        this->text = text;
    }


    void Label::setColor(const vec4 & color)
    {
        this->changed = true;
        this->color = color;
    }


    void Label::setFont(Font * font)
    {
        this->changed = true;
        this->font = font;
    }


    void Label::update(const float & deltaTime)
    {
        if(changed)
        {
			rawSurface = TTF_RenderText_Blended(font->font, text.c_str(), {(Uint8)color.x, (Uint8)color.y, (Uint8)color.z, (Uint8)color.w});

            basePerson->setSize({(float)rawSurface->w, (float)rawSurface->h});

            glGenTextures(1, &texture);

            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            colorMode = GL_RGB;
            if (rawSurface->format->BytesPerPixel == 4)
                colorMode = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, colorMode, rawSurface->w, rawSurface->h, 0, colorMode, GL_UNSIGNED_BYTE, rawSurface->pixels);
            glGenerateMipmap(GL_TEXTURE_2D);

            SDL_FreeSurface(rawSurface);

            glBindTexture(GL_TEXTURE_2D, 0);

            changed = false;
        }
    }


    void Label::draw(void)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}