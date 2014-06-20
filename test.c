#include <stdio.h>
#include "String.h"

int
main() {
	String *s1 = newString(3);
	String *s2 = newString(2);

	stringAppendChar(s1, 'a');	
	stringAppendChar(s1, 'a');	

	puts(stringAsCString(s1));

	stringAppendChar(s1, 'b');	
	stringAppendChar(s1, 'b');	
	stringAppendChar(s1, 'b');	

	puts(stringAsCString(s1));

	deleteString(s1);
	deleteString(s2);
}
