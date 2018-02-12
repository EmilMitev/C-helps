#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *replace_str(const char *source, const char *search, const char *replace)
{
	char *result;
	int i, count = 0;
	int newlen = strlen(replace);
	int oldlen = strlen(search);

	// count how many times search is appear in source (no replace)
	for (i = 0; source[i] != '\0'; i++)    
	{
		if (strstr(&source[i], search) == &source[i]) 
		{
			count++;
			i += oldlen - 1;
		}
	}

	// dynamic alocate memory
	result = (char *)malloc(i + count * (newlen - oldlen));
	if (result == NULL)
		exit(EXIT_FAILURE);
	i = 0;

	// actual replacement
	while (*source)
	{
		if (strstr(source, search) == source) //compare the substring with the newstring
		{
			strcpy(&result[i], replace);
			i += newlen; //adding newlength to the new string
			source += oldlen;//adding the same old length the old string
		}
		else
			result[i++] = *source++;
	}

	result[i] = '\0';
	return result;
}

int main(void)
{
	char * source = "Show_Window( 'BOOT_WINDOW' );\n Go_Block( 'GDOSS' );\n -- IF NVL( Get_Application_Property(CALLING_FORM), '#' ) = 'ATT_TEL'\n --  THEN BEGIN\nShow_Window( 'BOOT_WINDOW' );\n Go_Block( 'GDOSS' );\n -- IF NVL( Get_Application_Property(CALLING_FORM), '#' ) = 'ATT_TEL'\n --  THEN BEGIN\nShow_Window( 'BOOT_WINDOW' );\n Go_Block( 'GDOSS' );\n -- IF NVL( Get_Application_Property(CALLING_FORM), '#' ) = 'ATT_TEL'\n --  THEN BEGIN";
	char * search = "Get_Application_Property(CALLING_FORM)";
	char * replace = "NVL(:PARAMETER.P_CALLING_FORM, Get_Application_Property(CALLING_FORM))";

	source = replace_str(source, search, replace);
	printf("%s\n", source);
	return 0;
}
