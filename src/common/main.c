#include "memory.h"
#include "target.h"

int main(void)
{
	memoryInitializeBss();
	memoryInitializeData();
	targetUp();

	while (1) {
	}
}
