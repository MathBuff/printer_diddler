#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <termios.h>   // for struct termios, tcgetattr, tcsetattr, ICANON, ECHO, TCSANOW
#include <unistd.h>    // for STDIN_FILENO
#include <cstdio>      // for getchar()

void clear();
std::string getButton();
