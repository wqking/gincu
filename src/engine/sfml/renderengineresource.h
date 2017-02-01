#ifndef RENDERENGINERESOURCE_H
#define RENDERENGINERESOURCE_H

#include <SFML/Graphics.hpp>

#include <memory>

namespace gincu {

class RenderEngineResource
{
public:
	std::unique_ptr<sf::RenderWindow> window;
};


} //namespace gincu



#endif
