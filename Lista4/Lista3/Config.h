#pragma once

#include "Figure.h"
#include "Body.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

enum {
	BODYPARTS = 14,
	SPEED = 2,
	FULL_VIEW = 0,
	HEAD_VIEW = 1,
	OVER_CHAR_VIEW = 2
};