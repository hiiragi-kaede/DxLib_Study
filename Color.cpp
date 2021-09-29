#include "Color.hpp"
#include"DxLib.h"

static const unsigned Cr_white = GetColor(255, 255, 255);
static const unsigned Cr_orange = GetColor(255, 45, 00);

unsigned color::getWhite()
{
	return Cr_white;
}

unsigned color::getOrange()
{
	return Cr_orange;
}
