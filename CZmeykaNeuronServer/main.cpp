#include <iostream>
#include <WinSock2.h>
#include <string>
#include <SFML/System.hpp>
#include <thread>
//#include <amp.h>



#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
using namespace sf;
//using namespace concurrency;


class Zmeyka
{
public:

	int size = 1;
	int dir = 0;
	int s[1000][2];
	void key()
	{
		for (int i = size - 1;i >= 1;i--)
		{
			s[i][0] = s[i - 1][0];
			s[i][1] = s[i - 1][1];
		}
		if (dir == 1) s[0][1] -= 10;
		if (dir == 2) s[0][1] += 10;
		if (dir == 3) s[0][0] -= 10;
		if (dir == 4) s[0][0] += 10;

	}


private:
};
class Apple
{
public:
	
	int x;
	int y;
	int size = 1;
	void appcus(int w, int h)
	{
		/*if (s[0][0] == appx && s[0][1] == appy)
		{
			size++;
			appx = (rand() % w / 10 - 1) * 10;
			appy = (rand() % h / 10 - 1) * 10;
		}*/
	}
private:

};





bool playing;
SOCKET Con1;
SOCKET Con2;
SOCKET Con11;
SOCKET Con22;

int mas1[260][2];
int mas2[260][2];
char m1[2];
char m2[2];
bool closethread = true;
string message1;
string message2;



void thr11()
{
	while (closethread)
	{
		recv(Con11, (char*)&message1, sizeof(message1), NULL);
		//cout << message1 << endl;
		send(Con22, (char*)&message1, sizeof(message1), NULL);

	}
}
void thr22()
{
	while (closethread)
	{
		recv(Con22, (char*)&message2, sizeof(message2), NULL);
		//cout << message2 << endl;
		send(Con11, (char*)&message2, sizeof(message2), NULL);



	}
}










void thr1()
{
	while (closethread)
	{
		recv(Con1, m1, sizeof(m1), NULL);
		
		if (send(Con1, (char*)&mas1, sizeof(mas1), NULL) == SOCKET_ERROR) { playing = false; }
	}
}
void thr2()
{
	while (closethread)
	{
		recv(Con2, m2, sizeof(m2), NULL);
		if (send(Con2, (char*)&mas2, sizeof(mas2), NULL) == SOCKET_ERROR) { playing = false; }
	}
}







int main()
{
	WSAData WsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &WsaData) != 0)
	{
		cout << "Oops! Error code 1" << endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(50000);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);


	SOCKADDR_IN addr1;
	int sizeofaddr1 = sizeof(addr1);
	addr1.sin_addr.s_addr = INADDR_ANY;
	addr1.sin_port = htons(50001);
	addr1.sin_family = AF_INET;

	SOCKET sListen1 = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen1, (SOCKADDR*)&addr1, sizeof(addr1));
	listen(sListen1, SOMAXCONN);

	while (true)
	{
		playing = true;
		cout << "---START---" << endl;
		
		int w = 800;
		int h = 800;
		
		
				
		srand(time(NULL));	

		char gopl[250] = "t";

		Con1 = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (Con1 == 0)
		{
			cout << "Error #2\n";
		}
		else
		{
			cout << "First Player Connected\n";
		}	

		Con11 = accept(sListen1, (SOCKADDR*)&addr1, &sizeofaddr1);

		if (Con11 == 0)
		{
			cout << "Error #2\n";
		}
		else
		{
			cout << "First Player Message Connected\n";
		}


		Con2 = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (Con2 == 0)
		{
			cout << "Error #2\n";
		}
		else
		{
			cout << "Second Player Connected\n";
		}


		Con22 = accept(sListen1, (SOCKADDR*)&addr1, &sizeofaddr1);

		if (Con22 == 0)
		{
			cout << "Error #2\n";
		}
		else
		{
			cout << "Second Player Message Connected\n";
		}






		send(Con1, gopl, sizeof(gopl), NULL);
		send(Con2, gopl, sizeof(gopl), NULL);

		Zmeyka zm1;
		Zmeyka zm2;
		zm1.s[0][0] = 200;
		zm1.s[0][1] = 400;
		zm2.s[0][0] = 600;
		zm2.s[0][1] = 400;
		Apple ap1;
		Apple ap2;
		ap1.x = (1 + rand() % w / 10 - 1) * 10;
		ap1.y = (1 + rand() % h / 10 - 1) * 10;
		ap2.x = (1 + rand() % w / 10 - 1) * 10;
		ap2.y = (1 + rand() % h / 10 - 1) * 10;
		Clock clock;	
		Time time;
		Clock cl;
		Time tm;
		int cltm = 0;
		
		int zmkill1 = 0;
		int zmkill2 = 0;

		int gold1 = rand() % 10;
		int gold2 = rand() % 10;
		closethread = true;
		HANDLE thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr1, 0, 0, NULL);
		HANDLE thread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr2, 0, 0, NULL);

		HANDLE thread11 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr11, 0, 0, NULL);
		HANDLE thread22 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr22, 0, 0, NULL);

		while (playing)
		{



			


			zm1.dir = m1[0];
			zm2.dir = m2[0];



			time = clock.getElapsedTime();
			tm = cl.getElapsedTime();
			if (time.asSeconds() >= 0.08)
			{

				time = clock.restart();
				if (m1[1] == m2[1])
				{
					if (cltm == 0)
					{
						cl.restart();
						cltm = 1;
					}					
					if (tm.asSeconds() >= 3)
					{
						zm1.key();
						zm2.key();
					}
				}
				else
				{
					cltm = 0;
				}
			}
			

			mas1[0][0] = zm1.size;
			mas1[0][1] = zm2.size;
			for (int i = 1;i <= zm1.size;i++)
			{
				mas1[i][0] = zm1.s[i - 1][0];
				mas1[i][1] = zm1.s[i - 1][1];
			}

			for (int i = zm1.size + 1;i <= zm1.size + zm2.size + 1;i++)
			{
				mas1[i][0] = zm2.s[i - zm1.size - 1][0];
				mas1[i][1] = zm2.s[i - zm1.size - 1][1];
			}
			mas1[zm1.size + zm2.size + 2][0] = ap1.x;
			mas1[zm1.size + zm2.size + 2][1] = ap1.y;
			mas1[zm1.size + zm2.size + 3][0] = ap2.x;
			mas1[zm1.size + zm2.size + 3][1] = ap2.y;
			mas1[zm1.size + zm2.size + 4][0] = ap1.size;
			mas1[zm1.size + zm2.size + 4][1] = ap2.size;

			if (cltm == 0)
			{
				mas1[zm1.size + zm2.size + 5][0] = 4;
			}
			else
			{
				if (tm.asSeconds() < 1)
				{
					mas1[zm1.size + zm2.size + 5][0] = 3;
				}
				else if (tm.asSeconds() < 2 && tm.asSeconds() > 1)
				{
					mas1[zm1.size + zm2.size + 5][0] = 2;
				}
				else if (tm.asSeconds() < 3 && tm.asSeconds() > 2)
				{
					mas1[zm1.size + zm2.size + 5][0] = 1;
				}
				else
				{
					mas1[zm1.size + zm2.size + 5][0] = 5;
				}
				
			}



			mas2[0][0] = zm1.size;
			mas2[0][1] = zm2.size;
			for (int i = 1;i <= zm1.size;i++)
			{
				mas2[i][0] = zm1.s[i - 1][0];
				mas2[i][1] = zm1.s[i - 1][1];
			}

			for (int i = zm1.size + 1;i <= zm1.size + zm2.size + 1;i++)
			{
				mas2[i][0] = zm2.s[i - zm1.size - 1][0];
				mas2[i][1] = zm2.s[i - zm1.size - 1][1];
			}
			mas2[zm1.size + zm2.size + 2][0] = ap1.x;
			mas2[zm1.size + zm2.size + 2][1] = ap1.y;
			mas2[zm1.size + zm2.size + 3][0] = ap2.x;
			mas2[zm1.size + zm2.size + 3][1] = ap2.y;
			mas2[zm1.size + zm2.size + 4][0] = ap1.size;
			mas2[zm1.size + zm2.size + 4][1] = ap2.size;

			if (cltm == 0)
			{
				mas2[zm1.size + zm2.size + 5][0] = 4;
			}
			else
			{
				if (tm.asSeconds() < 1)
				{
					mas2[zm1.size + zm2.size + 5][0] = 3;
				}
				else if (tm.asSeconds() < 2 && tm.asSeconds() > 1)
				{
					mas2[zm1.size + zm2.size + 5][0] = 2;
				}
				else if (tm.asSeconds() < 3 && tm.asSeconds() > 2)
				{
					mas2[zm1.size + zm2.size + 5][0] = 1;
				}
				else
				{
					mas2[zm1.size + zm2.size + 5][0] = 5;
				}

			}

			



			if (zm1.s[0][0] == ap1.x && zm1.s[0][1] == ap1.y)
			{
				zmkill1 = ap1.size;
				ap1.x = (1 + rand() % w / 10 - 1) * 10;
				ap1.y = (1 + rand() % h / 10 - 1) * 10;
				gold1 = rand() % 10;
				if (gold1 == 5)
					ap1.size = 7;
				else
					ap1.size = 1;
			}

			if (zm1.s[0][0] == ap2.x && zm1.s[0][1] == ap2.y)
			{

				zmkill1 = ap2.size;
				ap2.x = (1 + rand() % w / 10 - 1) * 10;
				ap2.y = (1 + rand() % h / 10 - 1) * 10;
				gold2 = rand() % 10;
				if (gold2 == 5)
					ap2.size = 7;
				else
					ap2.size = 1;
			}
			if (zm2.s[0][0] == ap1.x && zm2.s[0][1] == ap1.y)
			{
				zmkill2 = ap1.size;
				ap1.x = (1 + rand() % w / 10 - 1) * 10;
				ap1.y = (1 + rand() % h / 10 - 1) * 10;
				gold1 = rand() % 10;
				if (gold1 == 5)
					ap1.size = 7;
				else
					ap1.size = 1;

			}
			if (zm2.s[0][0] == ap2.x && zm2.s[0][1] == ap2.y)
			{

				zmkill2 = ap2.size;
				ap2.x = (1 + rand() % w / 10 - 1) * 10;
				ap2.y = (1 + rand() % h / 10 - 1) * 10;
				gold2 = rand() % 10;
				if (gold2 == 5)
					ap2.size = 7;
				else
					ap2.size = 1;
			}
			if (zm1.s[0][0] >= w || zm1.s[0][0] < 0 || zm1.s[0][1] >= h || zm1.s[0][1] < 0)
			{
				zm1.dir = 0;
				zm1.size = 1;
				zm1.s[0][0] = 200;
				zm1.s[0][1] = 400;
				for (int i = 1;i < 250;i++)
				{
					zm1.s[i][0] = 1000;
					zm1.s[i][1] = 1000;
				}
			}
			if (zm2.s[0][0] >= w || zm2.s[0][0] < 0 || zm2.s[0][1] >= h || zm2.s[0][1] < 0)
			{
				zm2.dir = 0;
				zm2.size = 1;
				zm2.s[0][0] = 600;
				zm2.s[0][1] = 400;
				for (int i = 1;i < 250;i++)
				{
					zm2.s[i][0] = 1000;
					zm2.s[i][1] = 1000;
				}

			}
			for (int i = 1;i <= zm1.size;i++)
			{
				if (zm1.s[0][0] == zm1.s[i][0] && zm1.s[0][1] == zm1.s[i][1])
				{
					zm1.dir = 0;
					zm1.size = 1;
					zm1.s[0][0] = 200;
					zm1.s[0][1] = 400;
					for (int i = 1;i < 250;i++)
					{
						zm1.s[i][0] = 1000;
						zm1.s[i][1] = 1000;
					}
				}
			}
			for (int i = 1;i <= zm2.size;i++)
			{
				if (zm2.s[0][0] == zm2.s[i][0] && zm2.s[0][1] == zm2.s[i][1])
				{
					zm2.dir = 0;
					zm2.size = 1;
					zm2.s[0][0] = 600;
					zm2.s[0][1] = 400;
					for (int i = 1;i < 250;i++)
					{
						zm2.s[i][0] = 1000;
						zm2.s[i][1] = 1000;
					}
				}

			}
			for (int i = 1;i <= zm2.size;i++)
			{
				if (zm1.s[0][0] == zm2.s[i][0] && zm1.s[0][1] == zm2.s[i][1])
				{
					zm1.dir = 0;
					zmkill2 = (zm1.size / 2) + 3;
					zm1.size = 1;
					zm1.s[0][0] = 200;
					zm1.s[0][1] = 400;
					for (int i = 1;i < 250;i++)
					{
						zm1.s[i][0] = 1000;
						zm1.s[i][1] = 1000;
					}
				}
			}
			if (zmkill2 > 0)
			{
				zm2.size++;
				zm2.s[zm2.size - 1][0] = 1000;
				zm2.s[zm2.size - 1][1] = 1000;
				zmkill2--;
			}
			

			for (int i = 1;i <= zm1.size;i++)
			{
				if (zm2.s[0][0] == zm1.s[i][0] && zm2.s[0][1] == zm1.s[i][1])
				{
					zm2.dir = 0;
					zmkill1 = (zm2.size / 2) + 3;
					zm2.size = 1;
					zm2.s[0][0] = 600;
					zm2.s[0][1] = 400;
					for (int i = 1;i < 250;i++)
					{
						zm2.s[i][0] = 1000;
						zm2.s[i][1] = 1000;
					}
				}
			}
			if (zmkill1 > 0)
			{
				zm1.size++;
				zmkill1--;
				zm1.s[zm1.size - 1][0] = 1000;
				zm1.s[zm1.size - 1][1] = 1000;
			}

		}
		
		closethread = false;
		WaitForSingleObject(thread1, INFINITE);
		CloseHandle(thread1);
		WaitForSingleObject(thread2, INFINITE);
		CloseHandle(thread2);

		WaitForSingleObject(thread11, INFINITE);
		CloseHandle(thread11);
		WaitForSingleObject(thread22, INFINITE);
		CloseHandle(thread22);
	
		
	}
	return 0;
}