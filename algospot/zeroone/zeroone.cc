#include <cstdio>

#define MAX_SEQ_LEN 1000000

int main()
{
  char s[MAX_SEQ_LEN];
  int c[MAX_SEQ_LEN], N, from, to;
  scanf("%s", s);

  c[0]=0;
  for (size_t i(1); s[i]; ++i) {
    c[i] = c[i-1];
    if (s[i-1] != s[i]) ++c[i];
  }

  scanf("%d", &N);
  while (N--) {
    scanf("%d %d", &from, &to);
    printf("%s\n", c[from] == c[to] ? "Yes" : "No");
  }
  return 0;
}
