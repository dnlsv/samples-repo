
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
    SOCKET ClientSocket = INVALID_SOCKET;
    SOCKET ListenSocket = INVALID_SOCKET;

    const char* sendBuffer = "Hello from server!";
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
    hints.ai_flags = AI_PASSIVE;

    rc = getaddrinfo(NULL, "444", &hints, &addrResult);
    if (rc != 0)
    {
        cout << "getaddrinfo failed, rc = " << rc << endl;
        WSACleanup();
        return rc;
    }

    ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
        cout << "Socket creation failed" << endl;
        clear(NULL, NULL, addrResult);
        return -1;
    }

    rc = bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    if (rc == SOCKET_ERROR)
    {
        cout << "Binding socket failed, rc = " << rc << endl;
        clear(&ListenSocket, INVALID_SOCKET, addrResult);
        return rc;
    }

    freeaddrinfo(addrResult);

    rc = listen(ListenSocket, SOMAXCONN);
    if (rc == SOCKET_ERROR)
    {
        cout << "Listenig socket failed, rc = " << rc << endl;
        clear(&ListenSocket, NULL, NULL);
        return rc;
    }


    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET)
    {
        cout << "Accepting socket failed, rc = " << rc << endl;
        clear(&ClientSocket, NULL, NULL);
        return rc;
    }

    closesocket(ListenSocket);

    do
    {
        ZeroMemory(recvBuffer, sizeof(recvBuffer));
        rc = recv(ClientSocket, recvBuffer, sizeof(recvBuffer), 0);
        if (rc > 0)
        {
            cout << "Recived " << rc << " bytes" << endl;
            cout << "Recived data: " << recvBuffer << endl;

            rc = send(ClientSocket, sendBuffer, (int)strlen(sendBuffer), 0);
            if (rc == SOCKET_ERROR)
            {
                cout << "Send data back failed, rc = " << rc << endl;
                clear(&ClientSocket, NULL, NULL);
                return rc;
            }
        }
        else if (rc == 0)
        {
            cout << "Connection closing..." << endl;
        }
        else
        {
            cout << "recv failed, rc = " << rc << endl;
            clear(&ClientSocket, NULL, NULL);
            return rc;
        }

    } while (rc > 0);

    rc = shutdown(ClientSocket, SD_SEND);
    if (rc == SOCKET_ERROR)
    {
        cout << "shutdown failed, rc = " << rc << endl;
        clear(&ClientSocket, NULL, NULL);
        return rc;
    }

    clear(&ClientSocket, NULL, NULL);

    system("pause");
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