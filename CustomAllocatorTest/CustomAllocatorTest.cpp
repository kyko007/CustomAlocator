
#include "stdafx.h"

using namespace std;

#ifdef ALLOCATOR_DEBUGGER
	class AllocatorDebugger : public AllocatorEventDebugger
{
	int nextX;
	int nextY;

	int consoleWidth;

	HWND console;
	HDC hdc;

	struct BlockInformation
	{
		void* startingAddress;
		size_t length;

		int visualX, visualY;
	};

	std::vector<BlockInformation> blocks;


	void drawRange(char* startMemAddress, size_t block_length, char* key, size_t length, int xLeft, int yLeft, COLORREF COLOR)
	{
		const int MAX_SQRT = (int)sqrt(block_length);

		if ((int)length < MAX_SQRT)
		{
			for (size_t i = key - (char*)startMemAddress, j = (size_t)(i / MAX_SQRT) + yLeft;
				i < key - (char*)startMemAddress + length; i++)
			{
				SetPixel(hdc, xLeft + (i + 1) % MAX_SQRT, (int)j, COLOR);
				j += ((i + 1) % MAX_SQRT == 0);
			}
		}
		else
		{
			size_t i, j;
			for (i = key - (char*)startMemAddress, j = (size_t)(i / MAX_SQRT) + yLeft; ; i++)
			{
				SetPixel(hdc, xLeft + ((int)i + 1) % MAX_SQRT, (int)j, COLOR);
				length--;
				if ((i + 1) % MAX_SQRT == 0)
				{
					break;
				}
			}
			j++;

			RECT myRect = { xLeft, (int)j, xLeft + MAX_SQRT, (int)j + (int)length / MAX_SQRT };
			HBRUSH handler = CreateSolidBrush(COLOR);
			FillRect(hdc, &myRect, handler);
			DeleteObject(handler);

			j += (int)length / MAX_SQRT;
			length -= MAX_SQRT * ((int)length / MAX_SQRT);


			int k = 1;
			while (length--)
			{
				SetPixel(hdc, xLeft + k++, (int)j, COLOR);
			}
		}
	}

public:

	AllocatorDebugger() : nextX(0), nextY(0)
	{
		//Get a console handle
		console = GetConsoleWindow();
		//Get a handle to device context
		hdc = GetDC(console);
	

		RECT rect;

		GetWindowRect(console, &rect);


		consoleWidth = rect.right;
	}

	void onNewBlock(void *startBlockAddress, size_t length)
	{

		if (nextX + sqrt(length) + 1 < consoleWidth)
		{
			blocks.push_back({ startBlockAddress, length,nextX + 1, nextY + 50 });

			nextX += (int)(sqrt(length) + 1) + 1;

		}
		else
		{
			nextX = 0;
			nextY += (int)(sqrt(length)) + 3;
			blocks.push_back({ startBlockAddress, length,nextX + 1, nextY + 50 });
			nextX += (int)(sqrt(length) + 1) + 1;

		}

		int xLeft = blocks.back().visualX;
		int yLeft = blocks.back().visualY;

		const int MAX_SQRT = (int)sqrt(length);
		COLORREF COLOR = RGB(0, 139, 139);

		//Draw pixels
		RECT myRect = { xLeft, yLeft,xLeft + MAX_SQRT, MAX_SQRT + yLeft + 1 };
		HBRUSH handler = CreateSolidBrush(COLOR);
		FillRect(hdc, &myRect, handler);

		DeleteObject(handler);

		COLOR = RGB(255, 255, 102);

		myRect = { xLeft + MAX_SQRT , yLeft,xLeft + MAX_SQRT + 1, MAX_SQRT + yLeft + 1 };

		handler = CreateSolidBrush(COLOR);
		FillRect(hdc, &myRect, handler);

		DeleteObject(handler);

		COLOR = RGB(255, 255, 102);

		myRect = { xLeft ,  yLeft + MAX_SQRT + 1,xLeft + MAX_SQRT + 1, yLeft + MAX_SQRT + 2 };

		handler = CreateSolidBrush(COLOR);
		FillRect(hdc, &myRect, handler);

		DeleteObject(handler);

		COLOR = RGB(255, 255, 102);

		myRect = { xLeft ,  yLeft - 1,xLeft + MAX_SQRT + 1, yLeft + 1 };

		handler = CreateSolidBrush(COLOR);
		FillRect(hdc, &myRect, handler);

		DeleteObject(handler);

		COLOR = RGB(255, 255, 102);

		myRect = { xLeft - 1 , yLeft,xLeft, yLeft + MAX_SQRT + 1 };

		handler = CreateSolidBrush(COLOR);
		FillRect(hdc, &myRect, handler);

		DeleteObject(handler);

	}

	void onNewMemory(void *startBlockAddress, void *address, size_t length)
	{

		for (const auto &block : blocks)
		{
			if (block.startingAddress == startBlockAddress)
			{

				drawRange((char*)block.startingAddress,block.length,
							(char*)address, length, block.visualX, block.visualY, RGB(139, 0, 0));

				break;
			}
		}

	};

	void onDeleteMemory(void *startBlockAddress, void *address, size_t length)
	{
		for (const auto &block : blocks)
		{
			if (block.startingAddress == startBlockAddress)
			{

				drawRange((char*)block.startingAddress,block.length,
						  (char*)address, length, block.visualX, block.visualY, RGB(0, 139, 139));

				break;
			}
		}
	};
};
#endif

char* p[2'500'00];



int main()
{
#ifdef ALLOCATOR_DEBUGGER
	AllocatorDebugger ev;

	setEventDebugger(&ev);
#endif


	
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

	/*

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
	Sleep(100);
	delete b;
	Sleep(100);
	delete c;
	Sleep(100);
	delete d;
	Sleep(100);
	delete e;
	Sleep(100);
	delete f;
	Sleep(100);
	delete g;
	Sleep(100);
	delete h;
	Sleep(100);
	long long *x = new long long[61000];
	x[0] = 10;
	Sleep(100);
	delete x;

	long long *l1 = new long long[10];
	l1[0] = 1;
	Sleep(100);
	delete l1;

	long long *l2 = new long long[200];
	l2[0] = 2;
	Sleep(100);
	delete l2;

	long long *l3 = new long long[30];
	l3[0] = 4;
	delete l3;

	Sleep(100);

	*/
	srand(53545);

	
//	int k = 0;

	/*for (int i = 0; i < 2'500'00; ++i)
	p[i] = new char[1];

	for (int i = 0; i < 2'500'00; i += 2)
	{
	delete[] p[i];

	printf("matrix fragmentation:%f\n            ",metricFragmentation());



	COORD coord;

	coord.X = 0;

	coord.Y = 0;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	}*/


	/*while (true)
	{

		if (rand() % 5 > 1)
		{
			if (rand() % 4 == 0)
				p[k] = new char[rand() % 5000 + 10 + 1];
			else
			{
				p[k] = new char[rand() % 100 + 1];
			}

			if (p[k] != 0)
			{
				++k;
			}
			else
			{
				break;

			}


		}
		else if (k != 0)
		{
			int x = rand() % (k / 2 + 1) + k / 2;

			delete[] p[x];

			for (int j = x + 1; j < k; ++j)
			{
				p[j - 1] = p[j];
			}
			--k;
		}

		memoryUsage();
		cout << "max available space:" << maxAvailable() << " bytes          \n";

		cout << "fragmentation metric:" << metricFragmentation(0) << "            ";



		COORD coord;

		coord.X = 0;

		coord.Y = 0;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);



	}*/

	set<int> st;
	vector<int> vec1,vec2;
	deque<int> dq;
	queue<int > qq;
	unordered_map<int, int> ump;
	for (int i = 1; i <= 30000; ++i)
	{
		if (i % 1000 == 0)
		{
			Sleep(100);
		}

		i % 2 ? dq.push_back(i) : dq.push_front(i);
		

	}

	//memoryUsage();

	//cout << "Max memory block available: " << maxAvailable() << " Bytes \n";




	system("pause");

	return 0;
}

