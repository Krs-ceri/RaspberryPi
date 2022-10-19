#include "Factory.hpp"

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstring>
#include <bits/stdc++.h>

using namespace Manage;

string read_(tcp::socket &socket) {
	boost::asio::streambuf buf;
	boost::asio::read_until(socket, buf, "\n");

	string data = boost::asio::buffer_cast<const char*>(buf.data());
	return data;
}

void send_(tcp::socket &socket, const string &message) {
	const string msg = message + "\n";
	boost::asio::write(socket, boost::asio::buffer(message));
}

std::string traitement_chargement_donnees(int choix, int id,
		string capteur_name, int minute, int hour, int day, int month,
		int year) {

	Factory *factory = new Factory();
	vector<DatasCapteur*> vect_datas;
	vect_datas.clear();
	switch (choix)
	{
	case 1:
		vect_datas = factory->load_all_datas();
		break;
	case 2:
		vect_datas = factory->load_data_by_id(id);
		break;
	case 3:
		vect_datas = factory->load_data_by_capteur_name(capteur_name);
		break;
	case 4:
		vect_datas = factory->load_data_by_date(day, month, year);
		break;
	case 5:
		vect_datas = factory->load_data_by_hour(minute, hour);
		break;
	}
	std::vector < std::string > json_string_vect =
			factory->convert_object_to_json_string(vect_datas);
	delete factory;
	factory = nullptr;
	std::string json_string = "";
	if (json_string_vect.size() == 0)
		return json_string;
	for (std::string str : json_string_vect)
       {
		json_string += str + "\n";
	}
	return json_string;
}

std::string parser_message_request(std::string msg_request, char delimiter)
{
	stringstream inputString(msg_request);
	string choix_str;
	getline(inputString, choix_str, delimiter);
	int choix = stoi(choix_str);
	std::string json_response = "";

	if (choix == 1) {
		json_response = traitement_chargement_donnees(1, 0, "", 0, 0, 0, 0, 0);
	} else if (choix == 2) {
		string id_str;
		getline(inputString, id_str, delimiter);
		int id = stoi(id_str);
		json_response = traitement_chargement_donnees(2, id, "", 0, 0, 0, 0, 0);
	} else if (choix == 3) {
		string capteur_ident;
		getline(inputString, capteur_ident, delimiter);
		json_response = traitement_chargement_donnees(3, 0, capteur_ident, 0, 0,
				0, 0, 0);
	} else if (choix == 4) {
		string day_str;
		string month_str;
		string year_str;

		getline(inputString, day_str, delimiter);
		int day = stoi(day_str);

		getline(inputString, month_str, delimiter);
		int month = stoi(month_str);

		getline(inputString, year_str, delimiter);
		int year = stoi(year_str);

		json_response = traitement_chargement_donnees(2, 0, "", 0, 0, day,
				month, year);
	} else if (choix == 5) {
		string minute_str;
		getline(inputString, minute_str, delimiter);
		int minute = stoi(minute_str);

		string hour_str;
		getline(inputString, hour_str, delimiter);
		int hour = stoi(hour_str);

		json_response = traitement_chargement_donnees(2, 0, "", minute, hour, 0,
				0, 0);
	}
	return json_response;
}

int main()
{
	boost::asio::io_service io_service;
	while (1)
       {
		tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 2504));

		tcp::socket socket_(io_service);

		acceptor_.accept(socket_);

		string message_request = read_(socket_);

		string message_response = parser_message_request(message_request, ":");

		cout << "message_response : " << endl << message_response << endl;

		send_(socket_, message_response);

		cout << "Servent sent response to client!" << endl;
	}
	return 0;
}
