#include <SFML/System.hpp>

namespace gincu {

// C++11 std::this_thread::sleep_for always sleeps too much, so we use SFML instead.
void sleepMilliseconds(const unsigned int milliseconds)
{
	sf::sleep(sf::milliseconds(milliseconds));
}

unsigned int getMilliseconds()
{
	static sf::Clock clock;
	return clock.getElapsedTime().asMilliseconds();
}


} //namespace gincu

