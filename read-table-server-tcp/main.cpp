
#include "Factory.hpp"

using namespace Manage;
/**
*
*Cette partie répondera aux requetes reçues par boost.
*
*/
void traitement_chargement_donnees(int argc, char **argv)
{

	int choix = atoi(argv[1]);
	Factory *factory = new Factory();
	vector<DatasCapteur*> vect_datas;
	vect_datas.clear();
	switch (choix)
	{
              case 1:
                     vect_datas = factory->load_all_datas();
                     break;
              case 2:
                     vect_datas = factory->load_data_by_id(atoi(argv[2]));
                     break;
              case 3:
                     vect_datas = factory->load_data_by_capteur_name(argv[2]);
                     break;
              case 4:
                     vect_datas = factory->load_data_by_date(atoi(argv[2]), atoi(argv[3]),
                                   atoi(argv[4]));
                     break;
              case 5:
                     vect_datas = factory->load_data_by_hour(atoi(argv[2]), atoi(argv[3]));
                     break;
	}
	std::vector < std::string > json_string_vect =
			factory->convert_object_to_json_string(vect_datas);
	factory->create_json_file(json_string_vect, "datas.json");
	delete factory;
	factory = nullptr;
}

int main(int argc, char **argv)
{
      traitement_chargement_donnees(argc, argv);
      return 0;
}
