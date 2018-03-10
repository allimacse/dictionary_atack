/*Created for allimacse*/

#include <stdio.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>

#define _XOPEN_SOURCE


void dictionary_atack(char[],char*);

int main(int argc, char const *argv[]){

	FILE *shadow;
	char line[150];
	char *username;
	char *fullpass;
	char salt[20];

	//Its for a format
	if (argc != 2)
    {
        printf("Usage: ./file <user>\n");
        return 1;
    }
	
	//create a file called shadow of /etx/shadow
	system(" sudo grep \'\\$6\\$\' /etc/shadow > shadow.txt");

	/***************Example crypt()
	char *pass;
	pass = crypt("password","$6$DKqiAQqSqrR.ylnk");
	printf("%s\n",pass );*/
	

	//open file shadow
	shadow = fopen("shadow.txt","r");
	
	while(fgets(line,150,shadow) !=NULL ){

		username = strtok(line,":");
		
		//know if there is a user
		if (strcmp(argv[1],username)==0)
		{
			//take a fullpass
			fullpass = strtok(NULL,":");
			int tmp;
			//create a salt
			for(tmp=0;tmp<19;tmp++)
				salt[tmp]=fullpass[tmp];

			dictionary_atack(salt,fullpass);
			exit(-1);
		}



		
	}
	fflush( stdin );
	fclose(shadow);
	printf("User no exist\n");
	return 0;
}



void dictionary_atack(char salt[20],char *fullpass){

	FILE *dictionary;
	char pass[20];

	//check if the dictionary exists
	if( (dictionary=fopen("dictionary.txt","r"))==NULL){
		printf("Dictionary not found\n");
		exit(-1);
	}
	//Read the diccionary
	while(fgets(pass,20,dictionary)!= NULL)
	{
		//get each one of the passwords
		pass[strlen(pass) - 1] = '\0';
		// compare the created hash with the fullpass
		if (strcmp(crypt(pass,salt),fullpass)==0)
		{
			//The password exist
			printf("The password is %s\n", pass);
			exit(-1);
		}
		
		
	}

	printf("the password is not in the dictionary\n" );

	fclose(dictionary);
}