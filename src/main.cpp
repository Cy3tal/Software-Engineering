#include <iostream>
#include "../include/InputModule.h"
#include "../include/OutputModule.h"
#include "../include/StrategyA.h"
int main(int argc, char *argv[])
{
	InputModule im(argv[1]);
	OutputModule om(argv[1]);
	Package p;
	while(im>>p)
	{
		AbstractStrategy* s = new StrategyA;
		s->process(p);
		om<<p;
	}
}