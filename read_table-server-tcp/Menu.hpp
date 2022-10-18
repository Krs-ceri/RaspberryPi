#ifndef MENU_H_FILE
#define MENU_H_FILE

#include "Factory.hpp"


#include <iostream>

using namespace std;
#include <string>


namespace Manage
{

       class Menu
       {
              private:
                     Factory * factory;
             public:
                     Menu(){ factory = new Factory();}
                     ~Menu(){delete factory; factory = nullptr;}

                     vector<DatasCapteur *> launch_programm_manage_temperature(const char * path_data_base);

       };
}

#endif // MENU_H_FILE
