#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdio.h>
#include <FoundationKit/FoundationKit.h>

int
main(void)
{
	IObject *obj;
	
	setbuf(stdout, NULL);
	printf("creating object\n");
	obj = Talisker_Object_createObject();
	printf("releasing object\n");
	IObject_release(obj);
	printf("done\n");
	return 0;
}
