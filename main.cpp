#include "bot.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
	CBot cb;

	cb.InitConnection("CBot2_s", "irc.eighthbit.net", "6667");
	printf("EOM\n");

	return 0;
}
