#ifndef MENU_H_FILE
#define MENU_H_FILE

#include "Console.hpp"


#include <iostream>

using namespace std;
#include <string>


namespace Manage
{

       class Menu
       {
              private:
                     Console * console;
             public:
                     Menu(){ console = new Console();}
                     ~Menu(){delete console; console = nullptr;}
                     int check_input_value(int limit_inf, int limit_max);
                     void launch_programm_manage_temperature();

       };
}

#endif // MENU_H_FILE
