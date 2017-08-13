#include "MyString.h"
#include <stdio.h>

/**
 * Counts the amount of str1 substrings that are equal to str2.
 * In case one (or two) of the strings is empty- returns 0.
 * @str1 - the string
 * @str2 -  the substring
 * @isCycic != 0 - search also for cyclic appearnce 
 * @return number appearance of str2 as substring of str1
 */
unsigned int countSubStr(const char* str1, const char* str2, int isCyclic)
{
    if(str1 == NULL || str2 == NULL)
    {
        return 0;
    }
    int occurences = 0;
    unsigned str1Iterator = 0;
    unsigned str2Iterator = 0;
    unsigned str1Index = 0;
    //char *str1Iterator = str1;
    //char *str2Iterator = NULL;
    //char *str1Index = NULL;
    while(str1[str1Iterator] != '\0')
    {
        str2Iterator = 0;
        str1Index = str1Iterator;
        while(str2[str2Iterator] != '\0')
        {
            // str1 ends
            if(str1[str1Index] == '\0')
            {
                if(isCyclic != 0)
                {
                    str1Index = 0;
                }
                else
                {
                    break;
                }
            }
            //not equal
            if(str2[str2Iterator] != str1[str1Index])
            {
                break;
            }
            ++str2Iterator;
            ++str1Index;
        }
        if(str2[str2Iterator] == '\0')
        {
            occurences++;
        }
        ++str1Iterator;
    }
    return occurences;
}
