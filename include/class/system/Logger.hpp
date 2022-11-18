#pragma once

#include "libs.hpp"

class Logger
{
    public:
        static void log(const string message);
        static void debug(const string message);
        static void warn(const string message);
        static void error(const string message);
};
