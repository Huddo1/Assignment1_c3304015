/*
KEY FOR USER INPUT:
First line of input.txt determines which task is selected, which is selected by typing the single integer between 1-5.
The following tasking can be selected:
1. Encryption of a message with a rotation cipher given the message text and rotation amount.
2. Decryption of a message encrypted with a rotation cipher given cipher text and rotation amount.
3. Encryption of a message with a substitution cipher given message text and alphabet substitution.
4. Decryption of a message encrypted with a substitution cipher given cipher text and substitutions.
5. Decryption of a message encrypted with a rotation cipher given cipher text only.

Second line of input.txt is the message the user wants to be encrypted or decrypted. Type out the message you want to perform a task
on in one line. It must all fit entirely on the one line.

Third line of input.txt is the rotation cipher key the user wants to be used to perform a rotation encryption or decryption. It must
be an integer value between 1 and 26.

Fourth line of input.txt is the substitution cipher key the user wants to be used to perform a substitution encryption or
decryption. It must be 26 characters long and must fit entirely on the one line.
*/

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
    //Declarations neccessary for tasks to be completed.
    char message[10000]; //string which holds the message entered by the user, holds both encrypted and decrypted messages.
    char encrypted_message[10000]; //This is a copy of the string 'message', it is used in Task 5.
	int Rotkey; //rotation cipher key which stores the cipher key for the rotation encryption and decryption tasks.
	char CipherKey[25]; //substitution cipher key which stores the cipher key for the substitution encryption and decryption tasks.
	
	//USER INTERFACE AND FILE I/O
	
	FILE *input = fopen("input.txt", "r"); //input file is declared and opened so that the input from the user can be read.
	FILE *output = fopen("output.txt", "w"); //output file is created so that the output from the task can be written to it.
	
	int ui; //variable to store the task which is selected by the user.
	
	fscanf(input, "%d\n", &ui); //fscanf function to scan the input for which task will be completed.
	fscanf(input, "%[^\n]s", message); //fscanf function to scan the string that is encrypted or decrypted. [^\n] enables fscanf to ignore whitespaces in strings.
	fscanf(input, "%d\n", &Rotkey); //fscanf function to scan the rotation key that is used for rotation encryption and decryption.
	fscanf(input, "%[^\n]s", CipherKey); //fscanf function to scan the cipher key that is for substitution encryption and decryption.
	
	strcpy(encrypted_message, message); //strcpy, copys the contents of the 'message' string into 'encrypted_message' string.

	//Swtich case to selected which task will be completed based on the value of 'ui'.
    switch(ui){
        case 1 : //Case for rotation encryption with rotation cipher key.
            printf("Rotation Encryption Selected.\n");
            printf("Message: %s\n", message);
            printf("Rotation Key = %d\n", Rotkey);
            fprintf(output, "Message: %s\n", message);
            fprintf(output, "Rotation Key = %d\n", Rotkey);
            printf("Encrypted Message: %s\n", RotEncrypt(message, Rotkey)); //RotEncrypt Function called
            fprintf(output, "Encrypted Message: %s\n", message);
            break;
        case 2 : //Case for rotation decryption with rotation cipher key.
            printf("Rotation Decryption Selected.\n");
            printf("Encrypted Message: %s\n", message);
            printf("Rotation Key = %d\n", Rotkey);
            fprintf(output, "Encrypted Message: %s\n", message);
            fprintf(output, "Rotation Key = %d\n", Rotkey);
            printf("Decrypted Message: %s\n", RotDecrypt(message, Rotkey)); //RotDecrypt Function called
            fprintf(output, "Decrypted Message: %s\n", message);
            break;
        case 3 : //Case for substitution encryption with cipher key.
            printf("Substitution Encryption Selected.\n");
            printf("Message: %s\n", message);
            fprintf(output, "Message: %s\n", message);
            printf("Encrypted Message: %s\n", SubEncrypt(message, CipherKey)); //SubEncrypt Function called
            fprintf(output, "Encrypted Message: %s\n", message);
            break;
        case 4 : //Case for substitution decryption with cipher key.
            printf("Substitution Decryption Selected.\n"); 
            printf("Encrypted Message: %s\n", message);
            fprintf(output, "Encrypted Message: %s\n", message);
            printf("Decrypted Message: %s\n", SubDecrypt(message, CipherKey)); //SubDecrypt Function called
            fprintf(output, "Decrypted Message: %s\n", message);
            break;
        case 5 : //Case for rotation decryption attack without rotation cipher key.
            printf("Rotation Attack Selected.\n");
            //FOR loops to increment through the values of RotAttack_Key that will be tested to decrypt the encrypted message
            for(int RotAttack_Key = 0; RotAttack_Key <= 26; RotAttack_Key++){ //this loop prints to standard output
                printf("Encrypted Message: %s\n", encrypted_message);
                printf("Decrypted Message: %s\n", RotAttack(message, encrypted_message, RotAttack_Key)); //RotAttack Function called
                printf("Attack Key = %d\n", RotAttack_Key);
            }
            for(int RotAttack_Key = 0; RotAttack_Key <= 26; RotAttack_Key++){ //this loop prints to the file output.txt
                fprintf(output, "Encrypted Message: %s\n", encrypted_message);
                fprintf(output, "Decrypted Message: %s\n", RotAttack(message, encrypted_message, RotAttack_Key)); //RotAttack Function called
                fprintf(output, "Attack Key = %d\n", RotAttack_Key);
            }
            break;
        default : printf("Unknown Option %c\nPlease enter 1, 2, 3, 4, 5.\n", ui); //programs response if an invalid task is selected by the user.
    }
    fclose(output);
  return 0;
}
//FUNCTION DEFINITIONS

/*Rotation Encryption Function: This function accepts a string message from main. It stores
each character of the string in a char variables 'letter', which movies through each character
via a for loop. At the beginning of each loop the character that is being encrypted to turned
turned into a uppercase character so that the encryption can be done between the characters
'A' to 'Z'. If the character is between this define region it will add the rotation key onto
its ASCII value. To make sure that the rotation key when added keeps the character between 'A'
and 'Z' the character has 'Z' taken away with 'A' added then 1 taken away. At the end the changed
character is stored back in the string and a new loop is begun. The function will then return
the encrypted string once the loop conditions are met.*/

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
/*Rotation Decryption Function: This function accepts an encrypted string message from main.
It stores each character of the string in a char variables 'letter', which movies through each character
via a for loop. At the beginning of each loop the character that is being decrypted to turned
turned into a uppercase character so that the decryption can be done between the characters
'A' to 'Z'. If the character is between this define region it will minus the rotation key subtracted from
its ASCII value. To make sure that the rotation key when added keeps the character between 'A'
and 'Z' the character has 'Z' added with 'A' subtracted then 1 added. At the end the decrypted
character is stored back in the string and a new loop is begun. The function will then return
the decrypted string once the loop conditions are met.*/

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
 character in which is being decrypted. A FOR loop runs the encryption incrementing through each character
 of the encrypted string. message_index stores the ASCII value of the encrypted character from the string
 and converts it to uppercase and subtracts the ASCII value for 'A'. A nested IF statement checks if
 the value for message_index is between 0 and 26. If met, the char variable, letter has character in which
 is being decrypted stored in it. A nested FOR loop runs through the CipherKey string to find the 
 corresponding character for which has to be substituted to decrypt the current character. Then the
 variable ciper_index takes the incremented value of the nest FOR loop and stores it. Then the character 
 will have the ASCII value of 'A' as well as cipher_index added to its value, giving its decrypted letter.*/

char *SubDecrypt(char *message, char *CipherKey){
    int message_index, cipher_index; //variables to store the index of the message string and cipherkey string.
    char letter; //variable to store the current character being decrypted
    for(int i = 0; message[i] != '\0'; i++){
        message_index = toupper(message[i]) - 'A'; //message_index stores the ASCII value of the current character being decrypted and adds 'A'
        if(message_index >= 0 && message_index < 26){ 
            letter = toupper(message[i]); //letter stores the current character being decrypted
            for(int j = 0; j <26; j++){
                if(CipherKey[j] == letter){ //IF statement to see if corresponding cipher character matches encrypted character.
                     cipher_index = j; //index value for cipherkey for corresponding encryptec character is stored in cipher_index.
                }
            }
            message[i] = 'A' + cipher_index; //character is decrypted by adding ASCII value of 'A' and cipher_index value.
        }
        else{
            message[i] = message[i]; //for characters outside of the cipherkey the character will be returned.
        }
    }
    return message; //decrypted message is returned to main.
}
/*Rotation Cipher Attack Function: This function accepts a encrypted message that has been encrypted with an unknown
rotation cipher key. This function is also called from a loop in main which holds the looped AttackKey, which is the
rotation key being used to decrypt the encrypted message. A char variable, letter, stores the current character from
the encrypted message which is being decrypted. That character will then have the AttackKey subtracted from it to test
whether it can be decrypted for that certain AttackKey value. It will complete this encryption with the AttackKey value
until the message string is ended. It will repeat this process until a decrypted message is produced correctly. */

char *RotAttack(char *message, char *encrypted_message, int AttackKey){
    char letter; //char variable to store character being decrypted.
    for(int i = 0; encrypted_message[i] != '\0'; i++){
        letter = toupper(encrypted_message[i]); //letter stores the character from encrypted message that is being decrypted
        if(letter >= 'A' && letter <= 'Z'){
            letter = letter - AttackKey; //encrypted character has the AttackKey subtracted to decrypt it
            if(letter < 'A'){
                letter = letter + 'Z' - 'A' + 1; //this IF statement ensures only characters between 'A' and 'Z' are being decrypted
            }
            message[i] = letter; //decrypted character is stored into the decrypted message
        }
    }
    return message; //decrypted message is return to the main.
}
