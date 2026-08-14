#ifndef VALID_INPUT_H
#define VALID_INPUT_H
#include<iostream>
#include <string>

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#else
#ifndef EMSCRIPTEN_KEEPALIVE
#define EMSCRIPTEN_KEEPALIVE
#endif
#endif

extern std::string g_webName;
extern "C" EMSCRIPTEN_KEEPALIVE void SetNameFromJS(const char* name);

void input(char &c);
void input(int &i);
void input(std::string &s);
#endif 
