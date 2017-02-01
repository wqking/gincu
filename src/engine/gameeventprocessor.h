#ifndef GAMEEVENTPROCESSOR_H
#define GAMEEVENTPROCESSOR_H


namespace gincu {

class GameApplication;

class GameEventProcessor
{
public:
	explicit GameEventProcessor(GameApplication * application);
	
	void processEvents();

private:
	GameApplication * application;
};


} //namespace gincu


#endif
