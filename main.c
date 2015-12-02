#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include "include/fsa.h"

int	main()
{
  char	buf[F_SIZE];

  buf[F_SIZE - 1] = '\0';
  fread(buf, sizeof(char), F_SIZE, stdin);
  printf("%s", buf);
  return (0);
}
