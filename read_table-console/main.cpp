#include "Menu.hpp"

using namespace Manage;
//Cette partie affichera les donnees retournees par le server TCP par l'appel Boost asio 
int main(int argc, char ** argv)
{
       Menu * menu = new Menu();
       menu->launch_programm_manage_temperature();
       return 0;
}
