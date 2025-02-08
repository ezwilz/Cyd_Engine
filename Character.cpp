#include "Character.h"
#include <SDL.h>

void Character:: passive()
{
	food -= 0.5 * foodMultiplier;
	bladder -= 0.5 * bladderMultiplier;
	hygeine -= 0.5 * hygeineMultiplier;
	sleep -= 0.5 * sleepMultiplier;
}