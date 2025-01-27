#include <stdio.h> // basic I/O
#include <stdlib.h>
#include <sys/types.h> // standard system types
#include <netinet/in.h> // Internet address structures
#include <sys/socket.h> // socket API
#include <arpa/inet.h>
#include <netdb.h> // host to IP resolution
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#define HOSTNAMELEN 40 // maximal host name length; can make it variable if you want
#define BUFLEN 1024 // maximum response size; can make it variable if you want
#define BUFFER_SIZE 256
// prototype
void checkParameters(int argc, char *argv[]);
int openSocket(void);
void connect2Server(int sock_id, struct sockaddr_in srv_ad);
struct hostent* getHostName(char* hostname);
void recvMessage(int sock_id, char buff[], int buff_size);
void sendMessage(int sock_id, char buff[], int buff_size);
void clearBuffer(char buff[]);
void printClientDir(void);
string getFileName(char buff[]);
bool isExists(string filename);
bool createFile(string filename);
void sendFile(int c_sock_fd, char buff[], string filename);
void recvFile(int c_sock_fd, char buff[], string filename);

int main(int argc, char *argv[])
{
  	// variable definitions
	int c_sock_fd, port;
	struct sockaddr_in srv_ad;
	struct hostent *serv;
	char buff[BUFFER_SIZE];

  	// check that there are enough parameters
 	checkParameters(argc, argv);

    port = atoi(argv[2]);	// getting port no.

	c_sock_fd = openSocket();	// open socket
	
	char *hostname = argv[1];	
	serv = getHostName(hostname);	// get hostname

	// server details
	srv_ad.sin_family = AF_INET;
	srv_ad.sin_port = htons(port);
	int serv_l = serv->h_length;
	bcopy((char *)serv->h_addr, (char *) &srv_ad.sin_addr.s_addr, serv_l);
	
	connect2Server(c_sock_fd, srv_ad);	// Connect to server

	clearBuffer(buff);
	
	recvMessage(c_sock_fd, buff, BUFFER_SIZE);	// Welcome Message
	cout << endl << buff << endl << endl;

	bool flag = true;
	string cmd;
	do
	{
		clearBuffer(buff);
		cout << "\nc : ";
		fgets(buff, BUFFER_SIZE, stdin);

		if (strncmp(buff, "List client", 11) == 0)
		{
			clearBuffer(buff);
			cmd = "_noA";
			strcpy(buff, cmd.c_str());

			sendMessage(c_sock_fd, buff, strlen(buff));
			
			printClientDir();
			
		}
		else if (strncmp(buff, "List server", 11) == 0)
		{	
			clearBuffer(buff);
			cmd = "list";
			strcpy(buff, cmd.c_str());

			sendMessage(c_sock_fd, buff, strlen(buff));

			clearBuffer(buff);
			recvMessage(c_sock_fd, buff, BUFFER_SIZE);
			cout << buff << endl;

		}
		else if (strncmp(buff, "DELETE client", 13) == 0)
		{
			string filename = getFileName(buff);	
			
			clearBuffer(buff);
			cmd = "_noA";
			strcpy(buff, cmd.c_str());

			sendMessage(c_sock_fd, buff, strlen(buff));

			if (!isExists(filename))
			{
				cout << "Client: File '" << filename
					<< "' does not exist.\n";
			}
			else if (!remove(filename.c_str())) 
			{
				cout << "Client: File '" << filename
					<< "' has been deleted.\n";
			}
			else
			{
				cout << "Client: Failed to delete file.\n";
			}
		}
		else if (strncmp(buff, "DELETE server", 13) == 0)
		{
			string filename = getFileName(buff);

			clearBuffer(buff);
			cmd = "_del";
			strcpy(buff, cmd.c_str());
			
			sendMessage(c_sock_fd, buff, strlen(buff));
			
			clearBuffer(buff);
			strcpy(buff, filename.c_str());
			sendMessage(c_sock_fd, buff, strlen(buff));
			
			clearBuffer(buff);
			recvMessage(c_sock_fd, buff, BUFFER_SIZE);
			cout << buff << endl;

		}
		else if (strncmp(buff, "Create client", 13) == 0)
		{
			string filename = getFileName(buff);

			clearBuffer(buff);
			cmd = "_noA";
			strcpy(buff, cmd.c_str());

			sendMessage(c_sock_fd, buff, strlen(buff));


			if (isExists(filename))
			{
				cout << "Client: The file '" << filename << "' already exists.";
			}
			else if (createFile(filename))
			{
				cout << "Client: The file '" << filename << "' has been created.";
			}

		}
		else if (strncmp(buff, "Create server", 13) == 0)
		{
			string filename = getFileName(buff);

			clearBuffer(buff);
			cmd = "_cre";
			strcpy(buff, cmd.c_str());
			
			sendMessage(c_sock_fd, buff, strlen(buff));
			
			clearBuffer(buff);
			strcpy(buff, filename.c_str());
			sendMessage(c_sock_fd, buff, strlen(buff));
			
			clearBuffer(buff);
			recvMessage(c_sock_fd, buff, BUFFER_SIZE);
			cout << buff << endl;			

		}
		else if (strncmp(buff, "RECIEVE", 7) == 0)
		{
			string filename = getFileName(buff);
			bool isGet = true;

			if (isExists(filename))
			{
				cout << "Client: The file '" << filename 
					<< "' already exists on the client. "
					<< "Please choose to either Replace (R) "
					<< "or Keep (K) older? R/K?\n";
				
				string choice; 
				cin >> choice;
				cin.ignore();

				if (choice == "K")
				{
					isGet = false;

					clearBuffer(buff);
					cmd = "_noA";
					strcpy(buff, cmd.c_str());
				}
			}
			
			if (isGet)
			{
				clearBuffer(buff);
				cmd = "recv";
				strcpy(buff, cmd.c_str());

				sendMessage(c_sock_fd, buff, strlen(buff));

				clearBuffer(buff);
				strcpy(buff, filename.c_str());
				sendMessage(c_sock_fd, buff, strlen(buff));

				clearBuffer(buff);
				recvMessage(c_sock_fd, buff, 4);

				if (strncmp(buff, "n_ex", 4) == 0)
				{
					cout << "Server: File ' " << filename 
						<< "' does not exist.\n";
				}
				else
				{
					// recv File
					recvFile(c_sock_fd, buff, filename);
					cout << "Server: The file ' " << filename
						<< "' has been sent.";
				}	
			}
			

		}
		else if (strncmp(buff, "SEND", 4) == 0)
		{
			string filename = getFileName(buff);

			if (!isExists(filename))
			{
				clearBuffer(buff);
				cmd = "_noA";
				strcpy(buff, cmd.c_str());

				sendMessage(c_sock_fd, buff, strlen(buff));				
				cout << "Client: Filename does not exist on client.\n";
			}
			else
			{
				clearBuffer(buff);
				cmd = "send";
				strcpy(buff, cmd.c_str());
				
				sendMessage(c_sock_fd, buff, strlen(buff));	

				clearBuffer(buff);
				strcpy(buff, filename.c_str());
				sendMessage(c_sock_fd, buff, strlen(buff));

				clearBuffer(buff);
				recvMessage(c_sock_fd, buff, 3);

				if (strncmp(buff, "_ex", 3) == 0)
				{
					cout << "Server: File '" << filename << "' already exists on the server.\n";
				}
				else if (strncmp(buff, "_ok", 3) == 0)
				{
					// send file
					sendFile(c_sock_fd, buff, filename);
					cout << "Server: File '" << filename << "' recieved.\n";
				}
			}
		}
		else if (strncmp(buff, "exit", 4) == 0)
		{
			flag = false;

			clearBuffer(buff);
			cmd = "exit";
			strcpy(buff, cmd.c_str());
			
			sendMessage(c_sock_fd, buff, strlen(buff));	
		}
		else
		{
			clearBuffer(buff);
			cmd = "help";
			strcpy(buff, cmd.c_str());

			sendMessage(c_sock_fd, buff, strlen(buff));	

			clearBuffer(buff);
			recvMessage(c_sock_fd, buff, BUFFER_SIZE);
			cout << buff << endl;
		}

	} while (flag);

	close(c_sock_fd);

  return 0;
}

void checkParameters(int argc, char* argv[])
{
	if (argc != 3)
    {
      fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
      exit(-1);
    }
}

int openSocket(void)
{
	int sock_id = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_id < 0)
	{
		cout << "Error : Opening Socket\n";
		exit(-1);
	}
	return sock_id;
}

void connect2Server(int sock_id, struct sockaddr_in srv_ad)
{
	int srv_size = sizeof(srv_ad);
	if (connect(sock_id, (struct sockaddr *) &srv_ad, srv_size) < 0)
	{
		cout << "Error : connection failed\n";
		exit(-1);
	}
}

struct hostent* getHostName(char* hostname)
{
	struct hostent *serv;
	serv = gethostbyname(hostname);
	if (serv == NULL)
	{
		cout << "Error : host not available\n";
		exit(-1);
	}
	return serv;
}

void recvMessage(int sock_id, char buff[], int buff_size)
{
	int x = read(sock_id, buff, buff_size);
	if (x < 0)
	{
		cout << "Error : reading from socket failed\n";
		exit(-1);
	}
}

void sendMessage(int sock_id, char buff[], int buff_size)
{
	int x = write(sock_id, buff, buff_size);
	if (x < 0)
	{
		cout << "Error : writing to socket failed\n";
		exit(-1);
	}
}

void clearBuffer(char buff[])
{
	bzero(buff, BUFFER_SIZE);	
}

void printClientDir(void)
{
	cout << "\n> Client : File List\n";
	DIR *_dir;
	struct dirent *_files;

	_dir = opendir("./");
	if (_dir != NULL)
	{
		while (_files = readdir(_dir))
		{
			cout << "> " << _files->d_name << endl;
		}
	}
}

string getFileName(char buff[])
{
	vector<string> cmd;
	string temp = "";
	for (int i = 0; i < strlen(buff) - 1; i++)
	{
		if (buff[i] == ' ')
		{
			cmd.push_back(temp);
			temp = "";
		}
		else
		{
			temp += buff[i];
		}
	}
	cmd.push_back(temp);

	return cmd[cmd.size() - 1];
}

bool isExists(string filename)
{

	ifstream in_file;
	in_file.open(filename.c_str());
	if (in_file.fail())
	{
		return false;
	}
	
	in_file.close();
	return true;
}

bool createFile(string filename)
{
	ofstream of_file;
	of_file.open(filename.c_str());
	if (of_file.fail())
	{
		return false;
	}
	
	of_file.close();
	return true;
}

void sendFile(int c_sock_fd, char buff[], string filename)
{
	ifstream in_file;
	in_file.open(filename.c_str());
	string cmd;
	while (!in_file.eof())
	{	
		clearBuffer(buff);
		cmd = "_con";
		strcpy(buff, cmd.c_str());
		
		sendMessage(c_sock_fd, buff, strlen(buff));	

		string temp;
		getline(in_file, temp);
		temp += "\n";

		clearBuffer(buff);
		strcpy(buff, temp.c_str());

		sendMessage(c_sock_fd, buff, strlen(buff));

		clearBuffer(buff);
		recvMessage(c_sock_fd, buff, 3);
	}

	clearBuffer(buff);
	cmd = "_fin";
	strcpy(buff, cmd.c_str());

	sendMessage(c_sock_fd, buff, strlen(buff));	

	in_file.close();
}

void recvFile(int c_sock_fd, char buff[], string filename)
{
	ofstream out_file;
	out_file.open(filename.c_str());
	
	clearBuffer(buff);
	recvMessage(c_sock_fd, buff, 4);
	
	while (strncmp(buff, "_con", 4) == 0)
	{
		clearBuffer(buff);
		recvMessage(c_sock_fd, buff, BUFFER_SIZE);

		string temp = buff;
		out_file << temp;

		clearBuffer(buff);
		string ack = "_ok";
		strcpy(buff, ack.c_str());
		sendMessage(c_sock_fd, buff, strlen(buff));

		clearBuffer(buff);
		recvMessage(c_sock_fd, buff, 4);
	}

	out_file.close();
}
