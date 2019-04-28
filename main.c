#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//FUNCTION PROTOTYPES
char *RotEncrypt(char *message, int Rotkey);
char *RotDecrypt(char *message, int Rotkey);
char *SubEncrypt(char *message, char *CipherKey);
char *SubDecrypt(char *message, char *CipherKey);
char *RotAttack(const char *message, int AttackKey);

//MAIN
int main() {
    int ui;
    char message[1000];
	int Rotkey;  
	char CipherKey[26];
	
	//USER INTERFACE
	FILE *output = fopen("output.txt", "w");
	FILE *input = fopen("input.txt", "r");
	fscanf(input, "%d\n", &ui);
	fscanf(input, "%[^\n]s", message);
	fscanf(input, "%d\n", &Rotkey);
	fscanf(input, "%[^\n]s", CipherKey);
	
    switch(ui){
        case 1 : 
            printf("Rotation Encryption Selected.\n");
            printf("Message: %s\n", message);
            fprintf(output, "Message: %s\n", message);
            printf("Encrypted Message: %s\n", RotEncrypt(message, Rotkey));
            fprintf(output, "Encrypted Message: %s\n", message);
            break;
        case 2 :
            printf("Rotation Decryption Selected.\n");
            printf("Encrypted Message: %s\n", message);
            fprintf(output, "Encrypted Message: %s\n", message);
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
                printf("Encrypted Message: %s\n", message);
                fprintf(output, "Encrypted Message: %s\n", message);
                printf("Decrypted Message: %s\n", RotAttack(message, RotAttack_Key));
                printf("Attack Key = %d\n", RotAttack_Key);
                fprintf(output, "Decrypted Message: %s\n", RotAttack(message, RotAttack_Key));
                fprintf(output, "Attack Key = %d\n", RotAttack_Key);
            }
        default : printf("Unknown Option %c\nPlease enter 1, 2, 3, 4, 5.\n", ui); 
    }
    fclose(output);
  return 0;
}
//FUNCTION DEFINITIONS
//Rotation encryption function:
char *RotEncrypt(char *message, int Rotkey){
    char letter;
    for(int i = 0; message[i] != '\0'; i++){
        letter = toupper(message[i]);
        if(letter >= 'A' && letter <= 'Z'){
            letter = letter + Rotkey;
            if(letter > 'Z'){
                letter = letter - 'Z' + 'A' - 1;
            }
            message[i] = letter;
        }
    }
    return message;
}
//Rotation decryption function:
char *RotDecrypt(char *message, int Rotkey){
    char letter;
    for(int i = 0; message[i] != '\0'; i++){
		letter = toupper(message[i]);
		if(letter >= 'A' && letter <= 'Z'){
			letter = letter - Rotkey;
			if(letter < 'A'){
				letter = letter + 'Z' - 'A' + 1;
			}
			message[i] = letter;
		}
	}
    return message;
}
//Substitution encryption function:
char *SubEncrypt(char *message, char *CipherKey){
  int message_index;
  for(int i = 0; message[i] != '\0'; i++){
    message_index = toupper(message[i]) - 'A';
    if(message_index >= 0 && message_index < 26){
      message[i] = CipherKey[message_index];
    }
    else{
      message[i] = message[i];
    }
  }
  return message;
}
//Substitution decryption function:
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
char *RotAttack(const char *message, int AttackKey){
    char letter;
    int length = strlen(message);
    char *decrypted_message = (char*) malloc(sizeof(char)*length);
    for(int i = 0; message[i] != '\0'; i++){
        letter = toupper(message[i]);
        if(letter >= 'A' && letter <= 'Z'){
            letter = letter - AttackKey;
            if(letter < 'A'){
                letter = letter + 'Z' - 'A' + 1;
            }
            decrypted_message[i] = letter;
        }
    }
    return decrypted_message;
}
