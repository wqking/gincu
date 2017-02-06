#ifndef COMPONENTCHESS_H
#define COMPONENTCHESS_H

#include "gincu/gcomponent.h"

namespace gincu {

enum class ChessColor;

class ComponentChess : public Component
{
private:
	typedef Component super;

public:
	inline static unsigned int getComponentType() {
		return componentIdRegister.getComponentId();
	}

public:
	explicit ComponentChess(const ChessColor color);
	~ComponentChess();

	ChessColor getColor() const { return color; }

private:
	ChessColor color;
	
private:
	static ComponentIdRegister componentIdRegister;
};


} //namespace gincu

#endif
