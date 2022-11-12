#include "class/Logger.hpp"

void logCurrentDate()
{
    time_t t = time(NULL);
    string now = asctime(localtime(&t));
    now[now.size() - 1] = '\0';
    cout << "\033[90m" << now << " ";
}

void Logger::log(const string message)
{
    logCurrentDate();
    cout << "\033[37m\e[1m[LOG]\033[0m\e[0m ";
    cout << message << endl;
}

void Logger::debug(const string message)
{
    logCurrentDate();
    cout << "\033[36m\e[1m[DEBUG]\033[0m\e[0m ";
    cout << message << endl;
}

void Logger::warn(const string message)
{
    logCurrentDate();
    cout << "\033[33m\e[1m[WARN]\033[0m\e[0m ";
    cout << message << endl;
}

void Logger::error(const string message)
{
    logCurrentDate();
    cout << "\033[31m\e[1m[ERROR]\033[0m\e[0m ";
    cout << message << endl;
}
