
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

void clear(SOCKET* socket = NULL, SOCKET socketValue = NULL, ADDRINFO* addrResult = NULL);

int main() {

    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult = NULL;
    SOCKET ConnectSocket = INVALID_SOCKET;

    const char* sendBuffer = "Hello from client!";
    char recvBuffer[512];

    int rc = 0;

    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc != 0)
    {
        cout << "WSAStartup failed, rc = " << rc << endl;
        return rc;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    rc = getaddrinfo("localhost", "444", &hints, &addrResult);
    if (rc != 0)
    {
        cout << "getaddrinfo failed, rc = " << rc << endl;
        WSACleanup();
        return rc;
    }

    ConnectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed" << endl;
        clear(NULL, NULL, addrResult);
        return -1;
    }

    rc = connect(ConnectSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (rc == SOCKET_ERROR)
    {
        cout << "Unable connect to server, rc = " << rc << endl;
        //closesocket(ConnectSocket);
        //ConnectSocket = INVALID_SOCKET;
        //freeaddrinfo(addrResult);
        //WSACleanup();
        clear(&ConnectSocket, INVALID_SOCKET, addrResult);
        return rc;
    }

    freeaddrinfo(addrResult);

    rc = send(ConnectSocket, sendBuffer, (int)strlen(sendBuffer), 0);
    if (rc == SOCKET_ERROR)
    {
        cout << "Send failed, rc = " << rc << endl;
        clear(&ConnectSocket, NULL, NULL);
        return rc;
    }

    cout << "Sent: " << rc << " bytes" << endl;

    rc = shutdown(ConnectSocket, SD_SEND);
    if (rc == SOCKET_ERROR)
    {
        cout << "shutdown failed, rc = " << rc << endl;
        clear(&ConnectSocket, NULL, NULL);
        return rc;
    }

    do
    {
        ZeroMemory(recvBuffer, sizeof(recvBuffer));
        rc = recv(ConnectSocket, recvBuffer, sizeof(recvBuffer), 0);
        if (rc > 0)
        {
            cout << "Recived " << rc << " bytes" << endl;
            cout << "Recived data: " << recvBuffer << endl;
        }
        else if (rc == 0)
        {
            cout << "Connection closed" << endl;
        }
        else
        {
            cout << "recv failed, rc = " << rc << endl;
        }

    } while (rc > 0);


    clear(&ConnectSocket, NULL, NULL);
    return 0;
}

void clear(SOCKET* socket, SOCKET socketValue, ADDRINFO* addrResult)
{
    if (socket != NULL)
    {
        closesocket(*socket);
    }
    if (socketValue != NULL)
    {
        *socket = socketValue;
    }
    if (addrResult != NULL)
    {
        freeaddrinfo(addrResult);
    }
    WSACleanup();
}