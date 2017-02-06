#include "matchthree/componentchess.h"

namespace gincu {

GComponentIdRegister ComponentChess::componentIdRegister("componentChess");

ComponentChess::ComponentChess(const ChessColor color)
	:
		super(this),
		color(color)
{

}

ComponentChess::~ComponentChess()
{

}


} //namespace gincu
