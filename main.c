
//Function Prototypes listed here.

//Function for task (a)
/*
float a_RotEncrypt(float m_str);
float b_RotDecrypt(float m_str);
float c_SubEncrypt(float m_str);
float d_SubDecrypt(float m_str);
float e_RotDecrypt(float m_str);
float f_SubDecrypt(float m_str);
*/

int main(void) {
    
    //Necessary variable declaration
    char ui; //variable for user interface
    const char *UItext = "Please select a task to complete: ";
    
    //FILE opening and writing
    FILE *inputUI = fopen("intputUI.txt", "w");

    fprintf(inputUI, "%s\n", UItext);
    
    
   /*
    while (ui < 'a' || ui > 'f') {
        switch(ui) {
            case 'a': ... ; break;
            case 'b': ... ; break;
            case 'c': ... ; break;
            case 'd': ... ; break;
            case 'e': ... ; break;
            case 'f': ... ; break;
            default: printf("Unknown Option %c\nPlease enter a, b, c, d, e, f.\n", ui);
        }
    */
    } 
    fclose(inputUI);
  return 0;
}
