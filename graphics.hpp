#ifndef __GRAPHICS_HPP_INCLUDED__
#define __GRAPHICS_HPP_INCLUDED__

#include <Dxlib.h>
#include <map>
#include <string>

extern std::map<std::string, int> graphics;
extern std::map<std::string, int> sounds;

void loadGraphics();

void deleteGraphics();

#endif