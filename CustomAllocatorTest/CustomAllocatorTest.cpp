
#include "stdafx.h"

using namespace std;

struct A
{
  int a;
  int b;
  bool c;
  char r[48];

  A()
  {
	  a = 1;
	  b = 2;
	  c = true;
	  r[0] = 'a';
	  r[1] = 'b';
	  r[2] = '\0';
  }

};

int main()
{
  /*A * pA = new A();
  pA->b++;
  cout << pA->b << endl;
  delete pA;

  A * pA2 = new A(true);
  pA2->b++;
  cout << pA2->b << endl;
  delete pA2;

  A * parrA = new A[5];
  parrA[2].c = true;
  delete[] parrA;

  const int NO_STR = 5;
  if (auto p = (string*)malloc(NO_STR * sizeof(string)))
  {
    for (int i = 0; i != NO_STR; ++i) // populate the array
    {
      void * placement = p + i;
      new(placement) string(4, (char)('a' + i));
    }

    for (int j = 0; j != NO_STR; ++j)
      cout << "p[" << j << "] == " << p[j] << '\n';

    for (int i = NO_STR; i != 0; --i) // clean up
      p[i - 1].~string();

    free(p);
  }*/

	/*int *a =  new int[2];

	a[0] = 1;
	a[1] = 2;

	printf("%d\n", a[0]);
	printf("%d\n", a[1]);

	char *b = new char;

	*b = 'a';

	printf("%c\n", *b);

	double *c = new double(2.3);

	printf("%f\n", *c);

	long long *d = new long long(3);

	printf("%lld\n\n", *d);

	printf("%d\n", a[0]);
	printf("%d\n", a[1]);

	printf("%c\n", *b);

	printf("%f\n", *c);

	printf("%lld\n", *d);*/

	for (int i = 1; i <= 1000; ++i)
	{
		int *a = new int(2);

		*a = 2;
	}



  return 0;
}

