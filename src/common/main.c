#include "application.h"
#include "memory.h"
#include "target.h"

int main(void)
{
	// System bringup
	memoryInitializeBss();
	memoryInitializeData();
	targetUp();

	// Run application
	ApplicationHandle application = applicationInitialize();
	applicationRun(application);

	while (1) {
	}
}
