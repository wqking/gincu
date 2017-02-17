#ifndef COMPONENTCHESS_H
#define COMPONENTCHESS_H

#include "gincu/gcomponent.h"

namespace gincu {

enum class ChessColor;

class ComponentChess : public GComponent
{
private:
	typedef GComponent super;

public:
	inline static GComponentType getComponentType() {
		return componentIdRegister.getComponentId();
	}

public:
	explicit ComponentChess(const ChessColor color);
	~ComponentChess();

	ChessColor getColor() const { return color; }

private:
	ChessColor color;
	
private:
	static GComponentIdRegister componentIdRegister;
};


} //namespace gincu

#endif
