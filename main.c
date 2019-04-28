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
    char ui = 'a';
    char message[1000] = "ATTACK AT SUNRISE";
	int Rotkey = 2;  
	char CipherKey[26];
	
	FILE *output = fopen("output.txt", "w");
	
	//USER INTERFACE.
	printf("Please select a task to be completed: \n");
	printf("(a) Encryption of a message with a rotation cipher given the message text and rotation amount\n");
	printf("(b) Decryption of a message encrypted with a rotation cipher given cipher text and rotation amount\n");
	printf("(c) Encryption of a message with a substitution cipher given message text and alphabet substitution\n");
	printf("(d) Decryption of a message encrypted with a substitution cipher given cipher text and substitutions\n");
	printf("(e) Decryption of a message encrypted with a rotation cipher given cipher text only\n");
	
	scanf("%c", &ui);
	
    switch(ui){
        case 'a' : 
            printf("Please enter a message to be encrypted:\n");
            scanf("%s", &message[1000]);
            printf("Please enter a cipher key for the rotation encryption:\n");
            scanf("%d", &Rotkey);
            printf("Message: %s\n", message);
            printf("Encrypted Message: %s\n", RotEncrypt(message, Rotkey));
            fprintf(output, "Message: %s\n", message);
            fprintf(output, "Encrypted Message: %s\n", RotEncrypt(message, Rotkey));
            break;
        case 'b' :
            printf("Please enter a message to be decrypted:\n");
            scanf("%s", &message[1000]);
            printf("Please enter a cipher key for the rotation decryption:\n");
            scanf("%d", &Rotkey);
            printf("Encrypted Message: %s\n", message);
            printf("Decrypted Message: %s\n", RotDecrypt(message, Rotkey));
            fprintf(output, "Encrypted Message: %s\n", message);
            fprintf(output, "Decrypted Message: %s\n", RotDecrypt(message, Rotkey));
            break;
        case 'c' :
            printf("Please enter a message to be encrypted:\n");
            scanf("%s", &message[1000]);
            printf("Please enter a cipher key for the substitution encryption:\n");
            scanf("%s", &CipherKey[26]);
            printf("Message: %s\n", message);
            printf("Encrypted Message: %s\n", SubEncrypt(message, CipherKey));
            fprintf(output, "Message: %s\n", message);
            fprintf(output, "Encrypted Message: %s\n", SubEncrypt(message, CipherKey));
            break;
        case 'd' :
            printf("Please enter a message to be decrypted:\n");
            scanf("%s", &message[1000]);
            printf("Please enter a cipher key for the substitution decryption:\n");
            scanf("%s", &CipherKey[26]);
            printf("Encrypted Message: %s\n", message);
            printf("Decrypted Message: %s\n", SubDecrypt(message, CipherKey));
            fprintf(output, "Encrypted Message: %s\n", message);
            fprintf(output, "Decrypted Message: %s\n", SubDecrypt(message, CipherKey));
            break;
        case 'e' :
            for(int RotAttack_Key = 0; RotAttack_Key <= 26; RotAttack_Key++){
                printf("Encrypted Message: %s\n", message);
                printf("Decrypted Message: %s\n", RotAttack(message, RotAttack_Key));
                printf("Attack Key = %d\n", RotAttack_Key);
                fprintf(output, "Encrypted Message: %s\n", message);
                fprintf(output, "Decrypted Message: %s\n", RotAttack(message, RotAttack_Key));
                fprintf(output, "Attack Key = %d\n", RotAttack_Key);
            }
        default : printf("Unknown Option %c\nPlease enter a, b, c, d, e, f.\n", ui); 
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
    char *decrypted_message = (char*) malloc(sizeof(char) *length);
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
