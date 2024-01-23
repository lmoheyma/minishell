#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>


int main ()
{
	

	int maxint = INT32_MAX;
	int minint = INT32_MIN;
	
	
	printf("\n\ntest 0:\n");
	   printf("Hello\n");
	ft_printf("Hello\n	");
	
	printf("\n\ntest 1:\n");
	   printf("Hello %c %c%c\n", 'I', '4', '2');
	ft_printf("Hello %c %c%c\n", 'I', '4', '2');
	/*
	printf("\n\ntest 2:\n");
	   printf("Hello %c %c%c\n%", 'I', '4', '2');
	ft_printf("Hello %c %c%c\n%", 'I', '4', '2');
	*/
	/*
	printf("\n\ntest 3:\n");
	   printf("Hello %c love\n", '	I');
	ft_printf("Hello %c love\n", 'I');
	*/
	/*
	printf("\n\ntest 4:\n");
	   printf("Hello%    zI love 42\n");
	ft_printf("Hello%    zI love 42\n");
	*/
/*
	printf("\n\ntest 5:\n");
	   printf("Hello%  \n   zI love 42\n");
	ft_printf("Hello%  \n   zI love 42\n");
*/
	printf("\n\ntest 6:\n");
	   printf("Hello %s %s\n","Ilove", "c");
	ft_printf("Hello %s %s\n","Ilove", "c");
/*
	printf("\n\ntest 7:\n");
	   printf("Hello %s %s\n","", NULL);
	ft_printf("Hello %s %s\n","", NULL);
*/
	printf("\n\ntest 8:\n");
	   printf("Hello %s %d\n","Ilove", -42);
	ft_printf("Hello %s %d\n","Ilove", -42);

	printf("\n\ntest 9:\n");
	   printf("Hello %x\n",maxint);
	ft_printf("Hello %x\n",maxint);

	printf("\n\ntest 10:\n");
	   printf("Hello %X\n",maxint);
	ft_printf("Hello %X\n",maxint);
/*
	printf("\n\ntest 11:\n");
	   printf("Hello %X\n",42949672540000);
	ft_printf("Hello %X\n",42949672540000);
*/
	printf("\n\ntest 12:\n");
	   printf("Hello %X\n",-42);
	ft_printf("Hello %X\n",-42);

	printf("\n\ntest 12:\n");
	   printf("Hello %X\n",6422280);
	ft_printf("Hello %X\n",6422280);
/*
	printf("\n\ntest 13:\n");
	   printf("Hello %p\n",10);
	ft_printf("Hello %p\n",10);
*/
/*
	printf("\n\ntest 13 u:\n");
	   printf("Hello %u\n",&maxint);
	ft_printf("Hello %u\n",&maxint);
*/
/*
	printf("\n\ntest 13 d:\n");
	   printf("Hello %d\n",&maxint);
	ft_printf("Hello %d\n",&maxint);
*/
	printf("\n\ntest 14:\n");
	   printf("Hello %u\n",12);
	ft_printf("Hello %u\n",12);
	
	printf("\n\ntest 15:\n");
	   printf("Hello %u\n",minint);
	ft_printf("Hello %u\n",minint);

	printf("\n\ntest 16:\n");
	   printf("Hello %i\n",minint - 1);
	ft_printf("Hello %i\n",minint - 1);

	printf("\n\ntest 17:\n");
	   printf("Hello %i\n",minint - 1	);
	ft_printf("Hello %i\n",minint - 1);

	printf("\n\ntest 18:\n");
	   printf("Hello I love %%%%\n");
	ft_printf("Hello I love %%%%\n");





	printf ("\n\nTEST RETURN VALUE\n\n");
	printf ("\ntest:rien\n");
	   printf("%d\n", printf("Hello\n"));
	printf("%d\n", ft_printf("Hello\n"));

	printf ("\n-----\ntest:rien\n");
	   printf("%d\n", printf(""));
	printf("%d\n", ft_printf(""));
	

	printf ("\n-----\ntest:rt lign:\n");
	   printf("std2:%d", printf("\n"));
	printf("ft2:%d", ft_printf("\n"));

	
	printf ("\n-----\ntest char:\n");
	   printf("std1:%d\n", printf("Hello%c %c", 'I', 'I'));
	printf("ft1:%d\n",  ft_printf("Hello%c %c", 'I', 'I'));

	printf ("\n-----\ntest char neg:\n");
	   printf("std1:%d\n", printf("Hello%c", -5));
	printf("ft1:%d\n",  ft_printf("Hello%c", -5));

	printf ("\n-----\ntest char > 256:\n");
	   printf("std1:%d\n", printf("Hello%c", '4' + 512));
	printf("ft1:%d\n",  ft_printf("Hello%c", '4' + 512	));

	/*printf ("\n-----\ntest1:\n");
	   printf("std1:%d\n", printf("Hello%c %c"));
	printf("ft1:%d\n",  ft_printf("Hello%c %c"));
	*/


	printf ("\n-----\ntest: string\n");
	   printf("std2:%d ", printf("H%s", "ello"));
	printf("ft2:%d",   ft_printf("H%s", "ello"));

	printf ("\n-----\ntest:string empty:\n");
	   printf("std2:%d ", printf("H%s", ""));
	printf("ft2:%d",   ft_printf("H%s", ""));

		printf ("\n-----\ntest string NULL ?\n");
	   printf("std2:%d ", printf(" NULL %s", ""));
	printf("ft2:%d",   ft_printf(" NULL %s", ""));


	printf ("\n-----\ntest dec int:\n");
	   printf("std2:%d", printf("H%d\n", -42));
	printf("ft2:%d",   ft_printf("H%d\n", -42));

	printf ("\n-----\ntest dec INT MAX:\n");
	   printf("std2:%d ", printf("H%d\n", INT32_MAX));
	printf("ft2:%d",   ft_printf("H%d\n", INT32_MAX));

	printf ("\n-----\ntest dec INT MIN:\n");
	   printf("std2:%d ", printf("H%d\n", INT32_MIN));
	printf("ft2:%d",   ft_printf("H%d\n", INT32_MIN));
	/*
	printf ("\n-----\ntest4:\n");
	   printf("std2:%d ", printf("H%d\n", INT32_MAX + 5));
	printf("ft2:%d",   ft_printf("H%d\n", INT32_MAX + 5));

	printf ("\n-----\ntest4:\n");
	   printf("std2:%d ", printf("H%d\n", INT32_MIN - 5));
	printf("ft2:%d",   ft_printf("H%d\n", INT32_MIN - 5));
*/


	printf ("\n-----\ntest int:\n");
	   printf("std2:%d ", printf("H%i\n", -42));
	printf("ft2:%d",   ft_printf("H%i\n", -42));

	printf ("\n-----\ntest  INT MAX:\n");
	   printf("std2:%d ", printf("H%i\n", INT32_MAX));
	printf("ft2:%d",   ft_printf("H%i\n", INT32_MAX));

	printf ("\n-----\ntest INT MIN:\n");
	   printf("std2:%d ", printf("H%i\n", INT32_MIN));
	printf("ft2:%d",   ft_printf("H%i\n", INT32_MIN));


	printf ("\n-----\ntest hexa :\n");
	   printf("std2:%d ", printf("H%x\n", 42));
	printf("ft2:%d",   ft_printf("H%x\n", 42));

	printf ("\n-----\ntest hexa0 :\n");
	   printf("std2:%d ", printf("H%x\n", 0));
	printf("ft2:%d",   ft_printf("H%x\n", 0));

printf ("\n-----\ntest hexa maxint MAJ:\n");
	   printf("std2:%d ", printf("H%X\n", INT32_MAX));
	printf("ft2:%d",   ft_printf("H%X\n", INT32_MAX));

printf ("\n-----\ntest hexa minint:\n");
	   printf("std2:%d ", printf("H%x\n", INT32_MIN));
	printf("ft2:%d",   ft_printf("H%x\n", INT32_MIN));

/*
printf ("\n-----\ntest hexa maxint MAJ:\n");
	   printf("std2:%d ", printf("H%X\n", INT64_MAX));
	printf("ft2:%d",   ft_printf("H%X\n", INT64_MAX));
*/

	printf ("\n-----\ntest hexa MAJ:\n");
	   printf("std2:%d ", printf("H%X\n", 42));
	printf("ft2:%d",   ft_printf("H%X\n", 42));

	printf ("\n-----\ntest hexa0 MAJ:\n");
	   printf("std2:%d ", printf("H%X\n", 0));
	printf("ft2:%d",   ft_printf("H%X\n", 0));


	printf ("\n-----\ntest pointer adress:\n");
	   printf("std2:%d ", printf("H%p\n", &maxint));
	printf("ft2:%d",   ft_printf("H%p\n", &maxint));

	printf ("\n-----\ntest pointer adress of int:\n");
	   printf("std2:%d ", printf("H%p\n", (void *)12));
	printf("ft2:%d",   ft_printf("H%p\n", (void *)12));

	printf ("\n-----\ntest uint:\n");
	   printf("std2:%d ", printf("H%u\n", 420));
	printf("ft2:%d",   ft_printf("H%u\n", 420));

	printf ("\n-----\ntest unimt max:\n");
	   printf("std2:%d ", printf("H%u\n", UINT32_MAX));
	printf("ft2:%d",   ft_printf("H%u\n", UINT32_MAX));

	printf ("\n-----\ntest uint neg :0 :\n");
	   printf("std2:%d ", printf("H%u\n", -420));
	printf("ft2:%d",   ft_printf("H%u\n", -420));
/*
	printf ("\n-----\ntest7:\n");
	   printf("std2:%d ", printf("%x", __LONG_LONG_MAX__));
	printf("ft2:%d",   ft_printf("%x", __LONG_LONG_MAX__));	
*/


	printf ("\n-----\ntest tout mixe :\n");
	   printf("std2:%d ", printf("Hello %s%s%c%c%s %d %%%x\n", "World", " i",' ', 'l', "ove ", 42, 42));
	printf("ft2:%d",   ft_printf("Hello %s%s%c%c%s %d %%%x\n", "World", " i",' ', 'l', "ove ", 42, 42));



	printf ("\n-----\ntest random :\n");
		printf("std2:%d \n", printf("%p", NULL));
	printf("ft2:%d \n",   ft_printf("%p", NULL));
	printf ("\n\n");
	    printf("std2:%d \n", printf("%s", (char 	*)NULL));
	printf("ft2:%d \n",   ft_printf("%s", NULL));


	

	// printf ("\n-----\ntest random2 :\n");
	// 	printf("std2:%d \n", printf("%T", 45));
	// printf("ft2:%d \n",   ft_printf("%T", 4,4));


		printf ("\n-----\ntest random3 :\n");
	ft_printf("%i\n", 020);
	printf("%i\n", 020);

	ft_printf(NULL);



}