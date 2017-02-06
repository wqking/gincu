#ifndef GEVENTPROCESSOR_H
#define GEVENTPROCESSOR_H


namespace gincu {

class GApplication;

class GEventProcessor
{
public:
	explicit GEventProcessor(GApplication * application);
	
	void processEvents();

private:
	GApplication * application;
};


} //namespace gincu


#endif
