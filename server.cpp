#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
    if(serverSocket == -1)
    {
        cout<<"socket creation failed"<<endl;
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(1234);

    if(bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        cout<<"Binding of socket failed"<<endl;
        close(serverSocket);
        return 1;
    }

    cout<<"server listening on port 1234"<<endl;

    if(listen(serverSocket, SOMAXCONN) == -1)
    {
        cout<<"Error on listening"<<endl;
        close(serverSocket);
        return 1;
    }

    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
    if(clientSocket == -1)
    {
        cout<<"accepting of connection failed"<<endl;
        close(serverSocket);
        return 1;
    }

    cout<<"Client connected.."<<endl;

    char buffer[1024];

    while(1)
    {
        int recvLen = recv(clientSocket, buffer, sizeof(buffer), 0);

        if(recvLen <= 0)
        {
            cout<<"Error receiving message"<<endl;
            break;
        }
        buffer[recvLen] = '\0';

        cout<<"CLIENT : "<<buffer<<endl;

        cout<<"SERVER : ";
        std::cin.getline(buffer, sizeof(buffer));

        send(clientSocket, buffer, sizeof(buffer), 0);
    }

    close(clientSocket);
    close(serverSocket);
}


