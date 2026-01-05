#include "spawn.h"
#include <stdlib.h>
#include <sys/wait.h>

int main(int ac, char *av[], char *ep[]) {
  int stat = -1;
  const char *filename = av[1];

  pid_t pid = spawn(
    filename,
    --ac,
    (const uint8_t **)++av,
    (const uint8_t **)ep
  );

  if (pid == -1) {
    return (EXIT_FAILURE);
  }

  while (waitpid(pid, &stat, 0) != -1) {
    /* wait */
    ;
  }

  if (!WIFSIGNALED(stat)) {
    return (WEXITSTATUS(stat));
  }

  signal_error(WTERMSIG(stat));
  return (128 + WTERMSIG(stat));
}
