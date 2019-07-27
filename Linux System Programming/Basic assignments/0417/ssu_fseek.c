#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define SECOND_TO_MICRO 1000000

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t);

int main(void)
{
  struct timeval begin_t, end_t;
  gettimeofday(&begin_t, NULL);

  char *fname = "ssu_test.txt";
  FILE *fp;

  long position;
  int character;

  if ((fp = fopen(fname, "r")) == NULL) {
    fprintf(stderr, "fopen error for %s\n", fname);
    exit(1);
  }

  printf("Input number >>");
  scanf("%ld", &position);
  fseek(fp, position - 1, SEEK_SET);
  character = getc(fp);
  printf("%ldth character => %c\n", position, character);

  gettimeofday(&end_t, NULL);
  ssu_runtime(&begin_t, &end_t);

  exit(0);
}

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t)
{
  end_t->tv_sec -= begin_t->tv_sec;

  if (end_t->tv_usec < begin_t->tv_usec) {
    end_t->tv_sec--;
    end_t->tv_usec += SECOND_TO_MICRO;
  }

  end_t->tv_usec -= begin_t->tv_usec;
  printf("Runtime: %ld:%06d(sec:usec)\n", end_t->tv_sec, end_t->tv_usec);
}
