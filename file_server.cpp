#include<iostream>
#include<fstream>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

class Server_socket{
    fstream file;

    int PORT;
    
    int general_socket_descriptor;
    int new_socket_descriptor;

    struct sockaddr_in address;
    int address_length;
    

    public:
        Server_socket(){
            create_socket();
            PORT = 8050;

            address.sin_family = AF_INET; 
            address.sin_addr.s_addr = INADDR_ANY; 
            address.sin_port = htons( PORT );
            address_length = sizeof(address);

            bind_socket();
            set_listen_set();
            accept_connection();


        }
        bool FileExist(){
            file.open("datas/log.json", ios::in | ios::binary);
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
            if ((general_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
                perror("[ERROR] : Socket failed");
                exit(EXIT_FAILURE);
            }
            cout<<"[LOG] : Socket Created Successfully.\n";
        }

        void bind_socket(){
            if (bind(general_socket_descriptor, (struct sockaddr *)&address, sizeof(address))<0) {
                perror("[ERROR] : Bind failed");
                exit(EXIT_FAILURE);
            }
            cout<<"[LOG] : Bind Successful.\n";
        }

        void set_listen_set(){
            if (listen(general_socket_descriptor, 3) < 0) {
                perror("[ERROR] : Listen");
                exit(EXIT_FAILURE);
            }
            cout<<"[LOG] : Socket in Listen State (Max Connection Queue: 3)\n";
        }

        void accept_connection(){
            if ((new_socket_descriptor = accept(general_socket_descriptor, (struct sockaddr *)&address, (socklen_t*)&address_length))<0) { 
                perror("[ERROR] : Accept");
                exit(EXIT_FAILURE);
            }
            cout<<"[LOG] : Connected to Client.\n";
        }

        void transmit_file(){
            file.open("datas/log.json", ios::in | ios::binary);
            std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            cout<<"[LOG] : Transmission Data Size "<<contents.length()<<" Bytes.\n";

            cout<<"[LOG] : Sending...\n";

            int bytes_sent = send(new_socket_descriptor , contents.c_str() , contents.length() , 0 );
            cout<<"[LOG] : Transmitted Data Size "<<bytes_sent<<" Bytes.\n";

            cout<<"[LOG] : File Transfer Complete.\n";
            file.close();
        }


        void receive_file(){
            char buffer[1024] = {};
            int valread = read(new_socket_descriptor , buffer, 1024);
            if(valread > 0){
                file.open("datas/log.json", ios::out | ios::trunc | ios::binary);
                if(file.is_open()){
                    cout<<"[LOG] : File Created.\n";
                    cout<<"[LOG] : Data received "<<valread<<" bytes\n";
                    cout<<"[LOG] : Saving data to file.\n";
            
                    file<<buffer;
                    cout<<"[LOG] : File Saved.\n";
                    file.close();
                }
                else{
                    cout<<"[ERROR] : File creation failed\n";
                }

            }
            else{
             //   cout<<"[ERROR] : Empty file\n";
            }

        }
};

int main(){
    Server_socket S;
    while(true)    S.receive_file();
    return 0;
}


