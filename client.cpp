#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

int main()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(clientSocket == -1)
    {
        cout<<"Socket creation failed"<<endl;
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(1234);

    if(connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        cout<<"Error connecting to server"<<endl;
        close(clientSocket);
        return 1;
    }

    char buffer[1024];

    while(1)
    {
        cout<<"CLIENT : ";
        cin.getline(buffer, sizeof(buffer));

        send(clientSocket, buffer, sizeof(buffer), 0);

        int recvLen = recv(clientSocket, buffer, sizeof(buffer), 0);
        if(recvLen <= 0)
        {
            cout<<"Error receiving message"<<endl;
            break;
        }


        buffer[recvLen] = '\0';

        cout<<"SERVER : "<<buffer<<endl;
    }

    close(clientSocket);
}
