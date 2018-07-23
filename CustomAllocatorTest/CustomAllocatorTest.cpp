
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
  A * pA = new A();
  pA->b++;
  printf("%d\n",pA->b);
  delete pA;

  A * pA2 = new A(true);
  pA2->b++;
  printf("%d",pA2->b);
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
      printf("p[%d] == %d\n",j,p[j]);

    for (int i = NO_STR; i != 0; --i) // clean up
      p[i - 1].~string();

    free(p);
  }*/
 
	

	/*for (int i = 1; i <= 20; ++i)
	{
		char *a = new char[1];
		

		char *b = new char[1];
		
		char *c = new char[1];
		
		for (int j = 0; j < 1; ++j)
			a[j] = a[j], b[j] = b[j], c[j] = c[j];

		

		delete a;
		
		delete b;
		
		delete c;
		

		
	}*/

	
	startAnalytics();

	printf("%d",memCheck());



	system("pause");

  return 0;
}

