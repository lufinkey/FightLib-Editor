
#include "MainApplication.hpp"

int main(int argc, char *argv[])
{
	MainApplication*app = new MainApplication();
	int retVal = app->run();
	delete app;
	return retVal;
}
