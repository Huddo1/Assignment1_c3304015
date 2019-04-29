#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//FUNCTION PROTOTYPES
char *RotEncrypt(char *message, int Rotkey);
char *RotDecrypt(char *message, int Rotkey);
char *SubEncrypt(char *message, char *CipherKey);
char *SubDecrypt(char *message, char *CipherKey);
char *RotAttack(char *message, char *encrypted_message, int AttackKey);

//MAIN
int main() {
    int ui;
    char message[1000];
    char encrypted_message[1000];
	int Rotkey;  
	char CipherKey[26];
	
	//USER INTERFACE AND FILE I/O
	FILE *input = fopen("input.txt", "r");
	FILE *output = fopen("output.txt", "w"); 
	
	fscanf(input, "%d\n", &ui);
	fscanf(input, "%[^\n]s", message);
	fscanf(input, "%d\n", &Rotkey);
	fscanf(input, "%[^\n]s", CipherKey);
	
	strcpy(encrypted_message, message);
	
    switch(ui){
        case 1 : 
            printf("Rotation Encryption Selected.\n");
            printf("Message: %s\n", message);
            printf("Rotation Key = %d\n", Rotkey);
            fprintf(output, "Message: %s\n", message);
            fprintf(output, "Rotation Key = %d\n", Rotkey);
            printf("Encrypted Message: %s\n", RotEncrypt(message, Rotkey));
            fprintf(output, "Encrypted Message: %s\n", message);
            break;
        case 2 :
            printf("Rotation Decryption Selected.\n");
            printf("Encrypted Message: %s\n", message);
            printf("Rotation Key = %d\n", Rotkey);
            fprintf(output, "Encrypted Message: %s\n", message);
            fprintf(output, "Rotation Key = %d\n", Rotkey);
            printf("Decrypted Message: %s\n", RotDecrypt(message, Rotkey));
            fprintf(output, "Decrypted Message: %s\n", message);
            break;
        case 3 :
            printf("Substitution Encryption Selected.\n");
            printf("Message: %s\n", message);
            fprintf(output, "Message: %s\n", message);
            printf("Encrypted Message: %s\n", SubEncrypt(message, CipherKey));
            fprintf(output, "Encrypted Message: %s\n", message);
            break;
        case 4 :
            printf("Substitution Decryption Selected.\n"); 
            printf("Encrypted Message: %s\n", message);
            fprintf(output, "Encrypted Message: %s\n", message);
            printf("Decrypted Message: %s\n", SubDecrypt(message, CipherKey));
            fprintf(output, "Decrypted Message: %s\n", message);
            break;
        case 5 :
            printf("Rotation Attack Selected.\n");
            for(int RotAttack_Key = 0; RotAttack_Key <= 26; RotAttack_Key++){
                printf("Encrypted Message: %s\n", encrypted_message);
                printf("Decrypted Message: %s\n", RotAttack(message, encrypted_message, RotAttack_Key));
                printf("Attack Key = %d\n", RotAttack_Key);
            }
            for(int RotAttack_Key = 0; RotAttack_Key <= 26; RotAttack_Key++){
                fprintf(output, "Encrypted Message: %s\n", encrypted_message);
                fprintf(output, "Decrypted Message: %s\n", RotAttack(message, encrypted_message, RotAttack_Key));
                fprintf(output, "Attack Key = %d\n", RotAttack_Key);
            }
            break;
        default : printf("Unknown Option %c\nPlease enter 1, 2, 3, 4, 5.\n", ui); 
    }
    fclose(output);
  return 0;
}
//FUNCTION DEFINITIONS

/* Rotation Encryption Function: This function accepts a string message from main. It stores
each character of the string in a char variables 'letter', which movies through each character
via a for loop. At the beginning of each loop the character that is being encrypted to turned
turned into a uppercase character so that the encryption can be done between the characters
'A' to 'Z'. If the character is between this define region it will add the rotation key onto
its ASCII value. To make sure that the rotation key when added keeps the character between 'A'
and 'Z' the character has 'Z' taken away with 'A' added then 1 taken away. At the end the changed
character is stored back in the string and a new loop is begun. The function will then return
the encrypted string once the loop conditions are met. */

char *RotEncrypt(char *message, int Rotkey){
    char letter; //char variable for the string character to be stored in.
    for(int i = 0; message[i] != '\0'; i++){
        letter = toupper(message[i]); //string character is stored in 'letter' and converted to uppercase.
        if(letter >= 'A' && letter <= 'Z'){ //IF statement to make sure char is betweem 'A' and 'Z'.
            letter = letter + Rotkey;//Rotation key is added on to char to create encryption.
            if(letter > 'Z'){
                letter = letter - 'Z' + 'A' - 1; //this equation keeps special characters from being substituted in to the string.
            }
            message[i] = letter; //encrypted char is then stored in string.
        }
    }
    return message; //encrypted string is returned to main.
}
/* Rotation Decryption Function: This function accepts an encrypted string message from main.
It stores each character of the string in a char variables 'letter', which movies through each character
via a for loop. At the beginning of each loop the character that is being decrypted to turned
turned into a uppercase character so that the decryption can be done between the characters
'A' to 'Z'. If the character is between this define region it will minus the rotation key subtracted from
its ASCII value. To make sure that the rotation key when added keeps the character between 'A'
and 'Z' the character has 'Z' added with 'A' subtracted then 1 added. At the end the decrypted
character is stored back in the string and a new loop is begun. The function will then return
the decrypted string once the loop conditions are met. */
char *RotDecrypt(char *message, int Rotkey){
    char letter; //char variable for the string character to be stored in.
    for(int i = 0; message[i] != '\0'; i++){
		letter = toupper(message[i]); //string character is stored in 'letter' and converted to uppercase.
		if(letter >= 'A' && letter <= 'Z'){ //IF statement to make sure char is betweem 'A' and 'Z'.
			letter = letter - Rotkey; //rotation key is subtracted away from 'letter' to decrypt original char.
			if(letter < 'A'){
				letter = letter + 'Z' - 'A' + 1;//this equation keeps special characters from being substituted in to the string.
			}
			message[i] = letter; //decrypted char is stored in the string
		}
	}
    return message; //decrypted string is returned to main
}
/*Substitution encryption function: This function accept a message from main for it to be encrypted
with a substitution cipher. It also accepts a cipher key which is the key to encrypting the message.
 An int variable, message_index, is declared which stores the ASCII value of the character we are encrypting. It is
 nested in a loop so that it moves to the next character of the string after each loop. An IF statement
 determines whether the conditions are correct for encryption. It checks if the ASCII value is between 0
 and 26. If it is it will then assign it encrypted value by calling the corresponding cipher key value 
 and then store that new character in the encrypted message. If the character does not meet conditions
 it will just be returned.*/
char *SubEncrypt(char *message, char *CipherKey){
  int message_index; //int variable to show which character we are encrypting in the string.
  for(int i = 0; message[i] != '\0'; i++){
    message_index = toupper(message[i]) - 'A'; //message_index stoes the character which is converted to uppercase and has 'A' ASCII value subtracted so that the message_index will now be 0 and 26.
    if(message_index >= 0 && message_index < 26){
      message[i] = CipherKey[message_index]; //the cipher key string then calls its corresponding index to the letter being encrypted and stores in it the encrypted string.
    }
    else{
      message[i] = message[i]; //character outside of conditions will be returned as it self.
    }
  }
  return message; //encrypted message is returned to main.
}
/*Substitution decryption function: This function accept a message from main for it to be decrypted
with a substitution cipher. It also accepts a cipher key which is the key to decrypting the message.
 An int variable, message_index, is declared which stores the ASCII value of the character we are 
 decrypting. An int variable, cipher_index, is declared which stores a value for which corresponding character
 will be used to decrypt the encrypted character. A char variable, letter, is declared which stores the
 character in which is being decrypted. */
char *SubDecrypt(char *message, char *CipherKey){
    int message_index, cipher_index;
    char letter;
    for(int i = 0; message[i] != '\0'; i++){
        message_index = toupper(message[i]) - 'A';
        if(message_index >= 0 && message_index < 26){
            letter = toupper(message[i]);
            for(int j = 0; j <26; j++){
                if(CipherKey[j] == letter){
                     cipher_index = j;
                }
            }
            message[i] = 'A' + cipher_index;
        }
        else{
            message[i] = message[i];
        }
    }
    return message;
}
//Rotation cipher attack function:
char *RotAttack(char *message, char *encrypted_message, int AttackKey){
    char letter;
    for(int i = 0; encrypted_message[i] != '\0'; i++){
        letter = toupper(encrypted_message[i]);
        if(letter >= 'A' && letter <= 'Z'){
            letter = letter - AttackKey;
            if(letter < 'A'){
                letter = letter + 'Z' - 'A' + 1;
            }
            message[i] = letter;
        }
    }
    return message;
}
