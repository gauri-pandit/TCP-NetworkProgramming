#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main()
{
	string ipaddress = "127.0.0.1";   // IP Address of the server
	int port = 54000;				  //Listening port # on the server
	//Intialize Winsock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "can't start Winsock" << wsResult << endl;
		return;
	}
	//Create cocket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "can't create socket" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}
	// Fill in hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipaddress.c_str(), &hint.sin_addr);

	//Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	// Do-while loop to send and receive data
	char buf[4096];
	string userInput;
	do
	{
		//user enters text
		cout << "enter the values in the table in following format.(Date,Time,Temprature,Humidity)" << endl;
		getline(cin, userInput);

		if (userInput.size() > 0)  //make sure user send some text
		{
			//send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				//wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					//Echo response to console
					cout << "SERVER>" << string(buf, 0, bytesReceived) << endl;
				}
			}
		}
	} while (userInput.size() > 0);

	// close down everything
	closesocket(sock);
	WSACleanup();
}
