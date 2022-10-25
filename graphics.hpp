#ifndef __GRAPHICS_HPP_INCLUDED__
#define __GRAPHICS_HPP_INCLUDED__

#include <Dxlib.h>
#include <map>
#include <string>

extern std::map<std::string, int> graphics;

void loadGraphics();

void deleteGraphics();

#endif