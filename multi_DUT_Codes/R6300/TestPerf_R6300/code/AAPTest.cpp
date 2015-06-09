
/*
	do the act test in process function definition.
*/

#include "AAPTest.h"


/*
	Parser the test items
*/
int ParseTestItem(const char *p1, const char *p2)
{
	size_t len;
	len=strlen(p1);
	if (strlen(p2)>len)
	{
		len=strlen(p2);
	}
	int reVal=strncmp(p1,p2,len);
	return reVal;
}
