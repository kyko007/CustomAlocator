
#include "stdafx.h"

using namespace std;

struct A
{
	int a;
	int b;
	bool c;
	char r[48];

	A() = default;
	A(bool v) : a(5), b(v ? 1 : 0), c(v) {}
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

	printf("%lld\n", *d);*

	/*for (int i = 1; i <= 10000000; ++i)
	{
		char *a = new char[1];


		char *b = new char[1];

		char *c = new char[1];

		for (int j = 0; j < ; ++j)
			a[j] = 1, b[j] = 2, c[j] = 3;

		

		delete a;
		
		delete c;

		checkMem();
		printf("\n");
		Sleep(200);
		
	}*/

	
	beginSnapShot();
	char *a = new char[10000];
	a[0] = 'x';

	char *b = new char[10000];
	b[0] = 'x';

	char *c = new char[10000];
	c[0] = 'x';

	char *d = new char[10000];
	d[0] = 'x';

	char *e = new char[10000];
	e[0] = 'x';

	char *f = new char[10000];
	f[0] = 'x';

	int *g = new int[10000];
	g[0] = 7;
	
	

	int *h = new int[12345];
	h[0] = 8;

	

	delete a;
	delete b;
	delete c;
	delete d;
	delete e;
	delete f;
	delete g;
	delete h;

	printf("%d", endSnapShot());

	memoryVisualise();
	memoryUsage();
	
	system("pause");

  return 0;
}

