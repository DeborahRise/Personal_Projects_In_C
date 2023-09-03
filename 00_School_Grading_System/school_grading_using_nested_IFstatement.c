#include <stdio.h>
/* A school grading system
 * *A ranges from 80 to 100
 * *B ranges from 70 to 79
 * *C ranges from 60 to 69
 * *D ranges from 56 to 59
 * *E ranges from 50 to 55
 * *F ranges from 0 to 49
 * *Any other entry will be flagged as invalid */

int main() 
{
	int score;
	printf ("Enter your score!\n");
	if (scanf ("%d", &score) == 1)
	{
	if (score >= 0 && score <= 49)
		    printf ("you have an F\n");
	else if (score >= 50 && score <= 55)
		    printf ("you have an E\n");
	else if (score >= 56 && score <= 59)
		    printf ("you have a D\n");
	else if (score >=60 && score <= 69)
		    printf ("you have a C\n");
	else if (score >=70 && score <= 79)
		    printf ("you have a B\n");
	else if (score >= 80 && score <= 100)
		    printf ("you have an A\n");
	else printf ("you have entered an invalid score");
	}
	else
		printf("scanf failed\n");

	    return 0;
}
