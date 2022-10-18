#ifndef CONSOLE_H_FILE
#define CONSOLE_H_FILE

#include "DatasCapteur.hpp"
#include "Display.hpp"
#include "Utils.hpp"
#include "Constantes.hpp"

#include <vector>

using namespace Datas;

namespace Manage
{

       class Console
       {
              private:
                     Display * display;
                     Utils * utils;
                     Constantes * constantes;

              public:
                     Console(){ display = new Display(); utils = new Utils(); constantes = new Constantes();}
                     ~Console(){ delete display; display = nullptr; delete utils; utils = nullptr;}
                     void load_all_datas();
                     void load_data_by_id();
                     void load_data_by_capteur_name();
                     void load_data_by_date();
                     void load_data_by_hour();
                     void load_data_by_day_month();
                     void read_datas_convert_to_object(std::string path_to_file);
       };
}
#endif // CONSOLE_H_FILE