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
    char *str1Iterator = str1;
    char *str2Iterator = NULL;
    char *str1Index = NULL;
    while(str1Iterator != NULL && *str1Iterator != '\0')
    {
        str2Iterator = str2;
        str1Index = str1Iterator;
        while(str2Iterator != NULL && *str2Iterator != '\0')
        {
            // str1 ends
            if(*str1Index == '\0')
            {
                if(isCyclic != 0)
                {
                    str1Index = str1;
                }
                else
                {
                    break;
                }
            }
            //not equal
            if(*str2Iterator != *str1Index)
            {
                break;
            }
            ++str2Iterator;
            ++str1Index;
        }
        if(*str2Iterator == '\0')
        {
            occurences++;
        }
        ++str1Iterator;
    }
    return occurences;
}



int main()
{
	char *str1 = "abab";
	char *str2 = "aba";
	int res = countSubStr(str1,str2,0);
	if (1 != res)
	{
		printf("calling countSubStr with str1: \"abab\", str2: \"aba\" and isCyclic=0 should return 1\n");
		return 1;
	}

	res = countSubStr(str1,str2,1);
	if (2 != res)
	{
		printf("calling countSubStr with str1: \"abab\", str2: \"aba\" and isCyclic=1 should return 2\n");
		return 1;
	}

    str1 = "aaaa";
    str2 = "aa";
    res = countSubStr(str1, str2, 0);
    if(3 != res)
    {
        printf("calling countSubStr with str1: \"aaaa\", str2: \"aa\" and isCyclic=0 should return 3\n");
        return 1;

    }

    res = countSubStr(str1, str2, 1);
    if(4 != res)
    {
        printf("calling countSubStr with str1: \"aaaa\", str2: \"aa\" and isCyclic=1 should return 4\n");
        return 1;

    }

	printf("running example passed\n");

	return 0;
}
