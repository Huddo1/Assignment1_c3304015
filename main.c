#include <stdio.h>
//Function Prototypes listed here.
char *a_RotEncrypt(char *message, int key);
char *b_RotDecrypt(char *message, int key);
int main() {
    char ui = 'b';
    char message[100] = "DMBQXOS SGHR LDRRZFD";
	int key = 25;
	
    switch(ui){
        case 'a' : 
            printf("Message: %s\n", message);
            printf("Encrypted Message: %s\n", a_RotEncrypt(message, key));
            break;
        case 'b' :
            printf("Encrypted Message: %s\n", message);
            printf("Decrypted Message: %s\n", b_RotDecrypt(message, key));
            break;
        default : printf("Unknown Option %c\nPlease enter a, b, c, d, e, f.\n", ui); 
    }	
	
  return 0;
}

char *a_RotEncrypt(char *message, int key){
    char letter;
    int i;
    for(i = 0; message[i] != '\0'; ++i){
        letter = message[i];
        if(letter >= 'a' && letter <= 'z'){
            letter = letter + key;
            if(letter > 'z'){
                letter = letter - 'z' + 'a' - 1;
            }
            message [i] = letter;
        }
        else if(letter >= 'A' && letter <= 'Z'){
            letter = letter + key;
            if(letter > 'Z'){
                letter = letter - 'Z' + 'A' - 1;
            }
            message[i] = letter;
        }
    }
    return message;
}
char *b_RotDecrypt(char *message, int key){
    char letter;
    int i;
    for(i = 0; message[i] != '\0'; ++i){
		letter = message[i];
		if(letter >= 'a' && letter <= 'z'){
			letter = letter - key;
			
			if(letter < 'a'){
				letter = letter + 'z' - 'a' + 1;
			}
			message[i] = letter;
		}
		else if(letter >= 'A' && letter <= 'Z'){
			letter = letter - key;
			if(letter < 'A'){
				letter = letter + 'Z' - 'A' + 1;
			}
			message[i] = letter;
		}
	}
    return message;
}
