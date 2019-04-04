#include <stdio.h>

//Function Prototypes listed here.

int main() {
    //User interface printed
    printf("Please select a task to be completed: \n");
    printf(" a) Encrypt a message with a rotation cipher given the message text and rotation amount. \n");
    printf(" b) Decrypt a message encrypted with a rotation cipher given the cipher text and rotation amount. \n");
    printf(" c) Encrypt a message with a substitution cipher given the message text and alphabet substitution. \n");
    printf(" d) Decrypt a message encrypted with a substitution cipher given the the cipher text and substitutions. \n");
    printf(" e) Decrypt a message encrypted with a rotation cipher given the cipher text only. \n");
    printf(" f) Decrypt a message encrypted with a substitution cipher given the cipher text only. \n");
    
    char c;
    scanf("%c", &c);
    
    while (c < 'a' || c > 'f') {
        switch(c) {
            case 'a': /* function */; break;
            case 'b': /* function */; break;
            case 'c': /* function */; break;
            case 'd': /* function */; break;
            case 'e': /* function */; break;
            case 'f': /* function */; break;
            default: printf("Unknown Option %c\n Please enter a, b, c, d, e, f.\n", c);
        }
    }
  return 0;
}

//function definitions listed here.