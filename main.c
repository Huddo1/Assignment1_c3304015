#include <stdio.h>
#include <string.h>
//Function Prototypes listed here.
char *RotEncrypt(char *message, int Rotkey);
char *RotDecrypt(char *message, int Rotkey);
char *SubEncrypt(char *message, char *Cipherkey);

int main() {
    char ui = 'c';
    char message[] = "PLEASE GET MILK AT THE SHOPS";
	int Rotkey = 4;
	char Cipherkey[] = "QWERTYUIOPASDFGHJKLZXCVBNM" ;
	
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
            printf("message: %s\n", message);
            printf("Encrypted Message: %s\n", SubEncrypt(message, Cipherkey));
            break;
        default : printf("Unknown Option %c\nPlease enter a, b, c, d, e, f.\n", ui); 
    }	
	
  return 0;
}

char *RotEncrypt(char *message, int Rotkey){
    char letter;
    for(int i = 0; message[i] != '\0'; i++){
        letter = message[i];
        if(letter >= 'a' && letter <= 'z'){
            letter = letter + Rotkey;
            if(letter > 'z'){
                letter = letter - 'z' + 'a' - 1;
            }
            message [i] = letter;
        }
        else if(letter >= 'A' && letter <= 'Z'){
            letter = letter + Rotkey;
            if(letter > 'Z'){
                letter = letter - 'Z' + 'A' - 1;
            }
            message[i] = letter;
        }
    }
    return message;
}
char *RotDecrypt(char *message, int Rotkey){
    char letter;
    for(int i = 0; message[i] != '\0'; i++){
		letter = message[i];
		if(letter >= 'a' && letter <= 'z'){
			letter = letter - Rotkey;
			
			if(letter < 'a'){
				letter = letter + 'z' - 'a' + 1;
			}
			message[i] = letter;
		}
		else if(letter >= 'A' && letter <= 'Z'){
			letter = letter - Rotkey;
			if(letter < 'A'){
				letter = letter + 'Z' - 'A' + 1;
			}
			message[i] = letter;
		}
	}
    return message;
}
char *SubEncrypt(char *message, char *Cipherkey){
    int keyindex;
    for(int i = 0; message[i] != '\0'; i++){
        keyindex = message[i];
        if(keyindex >= 'A' && keyindex <= 'Z'){
            message[i] = Cipherkey[keyindex];
        }
        if(keyindex >= 'a' && keyindex <= 'z'){
            message[i] = Cipherkey[keyindex];
        }
        else {
            message[i] = message[i];
        }
    }
    return message;
}
