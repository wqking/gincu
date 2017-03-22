#ifndef SCRIPTMAIN_H
#define SCRIPTMAIN_H

#include <memory>

class ScriptHelper;

class ScriptMain
{
public:
	static void runScript();

public:
	ScriptMain();
	~ScriptMain();
	
	void run();

private:
	std::unique_ptr<ScriptHelper> scriptHelper;
};


#endif
