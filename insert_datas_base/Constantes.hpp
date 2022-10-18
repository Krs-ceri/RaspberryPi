
#ifndef CONST_H_FILE
#define CONST_H_FILE


#include <string>


using namespace std;

namespace Manage
{
              class Constantes
              {
                     private:
                           string sql_insert = "INSERT INTO temp_datas(identite_capt, temperature, humidity, pressure , gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z, seconde, minute, heure, jour, mois, annee) VALUES ('";
                           //const char * path_data_base = "/usr/local/db/db_temperature.db";
                     public:
                            Constantes(){}
                            ~Constantes(){}
                            /*
                            const char * get_url_db()
                            {
                                   return this->path_data_base;
                            }
                            */
                            string get_query_insert()
                            {
                                   return this->sql_insert;
                            }
              };
}

#endif // CONST_H_FILE
