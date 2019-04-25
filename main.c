#include <stdio.h>
#include <ctype.h>

//FUNCTION PROTOTYPES
char *RotEncrypt(char *message, int Rotkey);
char *RotDecrypt(char *message, int Rotkey);
char *SubEncrypt(char *message, char *CipherKey);
char *SubDecrypt(char *message, char *CipherKey);

//MAIN
int main() {
    char ui = 'd';
    char message[] = "qZzQEA QZ LXFKOLT";
	int Rotkey = 25;  
	char CipherKey[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
	
    switch(ui){
        case 'a' : 
            printf("Message: %s\n", message);
            printf("Encrypted Message: %s\n", RotEncrypt(message, Rotkey));
            break;
        case 'b' :
            printf("Encrypted Message: %s\n", message);
            printf("Decrypted Message: %s\n", RotDecrypt(message, Rotkey));
            break;
        case 'c' :
            printf("Message: %s\n", message);
            printf("Encrypted Message: %s\n", SubEncrypt(message, CipherKey));
            break;
        case 'd' :
            printf("Encrypted Message: %s\n", message);
            printf("Decrypted Message: %s\n", SubDecrypt(message, CipherKey));
            break;
        default : printf("Unknown Option %c\nPlease enter a, b, c, d, e, f.\n", ui); 
    }	
	
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

