#include <stdio.h>
#include <string.h>



int isPalindrome (char *str)
{
    printf("%s\n",str);
    int length = strlen (str);
    if (length<1)
        return 1;
    if(!((str[length-1]>'A' && str[length-1]<'Z')||(str[length-1]>'a' && str[length-1]<'z'))){
        str[length-1]='\0';
        isPalindrome(str);
    }
    else if(!((str[0]>'A' && str[0]<'Z')||(str[0]>'a' && str[0]<'z')))
        isPalindrome(str+1);
    else if (str[0] == str[length-1])
    {
        str[length-1]='\0';
        return isPalindrome (str+1);/*Recursive call as the function isPalindrome
        is called again within itself*/
    }

    else
        return 0;
}
int main(){
    char str[10];

    gets(str);
    printf("%s\n", str);


    if(isPalindrome(str)==1)
        printf("palindrome");
    else
        printf("not palindrome");

    return 0;
}
