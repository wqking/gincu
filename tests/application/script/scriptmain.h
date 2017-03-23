#ifndef SCRIPTMAIN_H
#define SCRIPTMAIN_H

#include <string>
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
	void doBindMethod(const std::string & methodName);

private:
	std::unique_ptr<ScriptHelper> scriptHelper;
};


#endif
