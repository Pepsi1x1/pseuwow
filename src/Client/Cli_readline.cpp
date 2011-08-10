#include <readline/readline.h>

#include "common.h"
#include "DefScript/DefScript.h"
#include "PseuWoW.h"
#include "Cli.h"

CliRunnable::CliRunnable(PseuInstance *p)
{
    _stop = false;
    _instance = p;
}

void CliRunnable::run(void)
{
    char *in;

    while(!_stop)
    {
		in = readline("> ");
		_instance->AddCliCommand(in);
		free(in);
    }
}
