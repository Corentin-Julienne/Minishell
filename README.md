# MINISHELL

## Notes about priority of redirections and pipes

In bash, you will 1) redirect to pipes, then 2) redirect STDIN/STDOUT, then 3) execute cmd.

So redirection of STDIN/STDOUT supersedes (so, basically, overrule) pipes. In pratical cases, sometimes the input of next pipes will receive nothing (as it will be hijacked by the redirection).

