#include <stdio.h>
#include <runcmd.h>

int main (int argc, char **argv)
{
  int result, n;
  char command[] = {"ls"};

  runcmd (command, &result, NULL);

  return 0;
}
