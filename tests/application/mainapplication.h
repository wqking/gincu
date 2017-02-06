#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include "gincu/gapplication.h"

namespace gincu {

class MainApplication : public GameApplication
{
private:
	typedef GameApplication super;

public:
	static MainApplication * getInstance();

public:
	MainApplication();
	~MainApplication();

private:
	virtual void doInitialize() override;
	virtual void doFinalize() override;

};


} //namespace gincu

#endif
