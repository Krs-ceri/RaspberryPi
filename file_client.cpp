#include<iostream>
#include<fstream>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <wiringPi.h>

using namespace std;

class Client_socket{
    fstream file;

    int PORT;
    
    int general_socket_descriptor;

    struct sockaddr_in address;
    int address_length;

    public:
        Client_socket(){
            create_socket();
            PORT = 8050;

            address.sin_family = AF_INET;
            address.sin_port = htons( PORT );
            address_length = sizeof(address);
            if(inet_pton(AF_INET, "51.68.86.120", &address.sin_addr)<=0) { 
                cout<<"[ERROR] : Invalid address\n";
            }

            create_connection();
            

        }
        bool FileExist(){
            file.open("serial/logs/log.json", ios::in | ios::binary);
            if(file.is_open()){
                file.close();
                return true;
            }
            else{
                file.close();
                return false;
            }
        }
        void create_socket(){
            if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
                perror("[ERROR] : Socket failed.\n");
                exit(EXIT_FAILURE);
            }
            cout<<"[LOG] : Socket Created Successfully.\n";
        }

        void create_connection(){
            if (connect(general_socket_descriptor, (struct sockaddr *)&address, sizeof(address)) < 0) { 
                perror("[ERROR] : connection attempt failed.\n");
                exit(EXIT_FAILURE);
            }
            cout<<"[LOG] : Connection Successfull.\n";
        }

        void blink_led() {
           /* wiringPiSetupGpio();

            pinMode(13, OUTPUT);

            digitalWrite(13, HIGH);
            delay(15);
            digitalWrite(13, LOW);
            delay(15);
            digitalWrite(13, HIGH);
            delay(15);
            digitalWrite(13, LOW);
            delay(15);*/
        }
        void receive_file(){
            char buffer[1024] = {};
            int valread = read(general_socket_descriptor , buffer, 1024);
            if(valread > 0){
                file.open("serial/logs/log.json", ios::out | ios::trunc | ios::binary);
                if(file.is_open())cout<<"[LOG] : File Created.\n";
                else{
                    cout<<"[ERROR] : File creation failed, Exititng.\n";
                    exit(EXIT_FAILURE);
                }
                cout<<"[LOG] : Data received "<<valread<<" bytes\n";
                cout<<"[LOG] : Saving data to file.\n";
            
                file<<buffer;
                cout<<"[LOG] : File Saved.\n";
                file.close();
            }
            else{
             //   cout<<"[ERROR] : Empty file\n";
            }

        }
        void transmit_file(){
            file.open("serial/logs/log.json", ios::in | ios::binary);
            std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            cout<<"[LOG] : Transmission Data Size "<<contents.length()<<" Bytes.\n";

            cout<<"[LOG] : Sending...\n";

            blink_led();
            int bytes_sent = send(general_socket_descriptor , contents.c_str() , contents.length() , 0 );
            cout<<"[LOG] : Transmitted Data Size "<<bytes_sent<<" Bytes.\n";

            cout<<"[LOG] : File Transfer Complete.\n";
            file.close();
        }
};

int main(){
    Client_socket C;
    while(true){
        if(C.FileExist()){
            C.transmit_file();
            if( remove( "serial/logs/log.json" ) != 0 )
                perror( "[ERROR] : Error deleting file" );
            else
                puts( "[LOG] : File successfully deleted" );
        }
    }
    return 0;
}