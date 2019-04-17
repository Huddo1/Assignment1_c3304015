#include <stdio.h>
//Function Prototypes listed here.
char *a_RotEncrypt(char *message, int key);

int main() {
    char message[100] = "ATTACK AT SUNRISE";
	int key = 1;
	
	/*for(i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			message[i] = ch;
		}
	} */
	printf("Message: ATTACK AT SUNRISE\n");
	printf("Encrypted message: %s", a_RotEncrypt(message, key));
    
  return 0;
}

char *a_RotEncrypt(char *message, int key){
    char letter;
    int i;
    for(i = 0; message[i] != '\0'; ++i){
        letter = message[i];
        if(letter >= 'a' && letter <= 'z'){
            letter = letter + key;
            if (letter > 'z'){
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
