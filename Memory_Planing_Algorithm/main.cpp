#include<iostream>
#include <windows.h>
using namespace std;

// --------------------------- Fullscreen mode ----------------------------------------- //
typedef BOOL(WINAPI *CHANGESTATECONSOLE)(HANDLE, DWORD, PCOORD);
#define CONSOLE_FULLSCREEN_MODE 1

int framesQuantity, pages[30], frames[10];   

void Fifo();
void Optimal();
void Lru();

void main(int argc, char* argv[])
{
// --------------------------- Fullscreen mode ------------------------------------ //

	COORD Mode;
	CHANGESTATECONSOLE SetConsoleDisplayMode;
	HMODULE hKernel32 = GetModuleHandle(L"kernel32"); // L в (L"kernel32") error C2664. В VS2015.
	SetConsoleDisplayMode = (CHANGESTATECONSOLE)
	GetProcAddress(hKernel32, "SetConsoleDisplayMode");
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, &Mode);

// --------------------------------------------------------------------------------- //
			//setlocale (LC_CTYPE, "Russian");
			short menu;
			cout << " " << endl;					
			cout << "---------- This program illustrate memory management algorithms. ----------" << endl;
			cout << "=======================================================================" << endl;
			cout << "\nEnter tottal frames quantity: " << endl;
			cin >> framesQuantity;
			cout << "\nEnter a sequence of frames: \n";		
			//Accepting sequence
			for(int i=0; i < framesQuantity; i++)				
			cin >> pages[i];
	do			{
					cout << "\n\t------------- MENU -------------\n" << endl;						
					cout << "\n1) FIFO algorithm (First in-First out)" << endl;						
					cout << "\n2) OPTIMAL algorithm" << endl;										
					cout << "\n3) LRU  algorithm(Least Recently Used)" << endl;						
					cout << "\n4) Exit" << endl;													
					cout << "\n\nChoose algorithm and enter number from 1 to 3: " << endl;			
					cout << "\nFor exit please enter number 4 " << endl;							
					cin >> menu; 
					system("cls");
	switch(menu) {

						case 1:		Fifo();			
						break;

						case 2:		Optimal();		
						break;

						case 3:		Lru();			// Least Recently Used;
						break;

				  }
	
				}

	while(menu != 4);
	cout << "\nUsed materials:\n" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "http://konstantinos777.narod.ru/21_30.htm" << endl;
	cout << "http://www.intuit.ru/studies/courses/2192/31/lecture/986?page=2" << endl;
	cout << "-----------------------------------------------------------------" << endl;
	system("pause");
}

void Fifo()
{
	int f = 0, r = 0, s = 0, count = 0, flag = 0, num, pSize;
	cout << "\nEnter frames quantities in pages: " << endl;
	cin >> pSize;

	for(int i=0; i < pSize; i++)
	{
		frames[i]=-1; 
	}

	while( s < framesQuantity) 
	{                             
		flag = 0;
		num = pages[s];
		for(int i = 0; i < pSize; i++)
		{
			if(num == frames[i])
			{
				s++;
				flag = 1;
				break;
			}
		}
		if(flag==0) 
		{
			if(r < pSize) 
			{
				frames[r] = pages[s];
				r++; 
				s++;
				count++;					//***  Errors in algorithm;
			}
				else 
				{
					if(f < pSize)
					{
						frames[f] = pages[s];
						s++; f++; count++;			   //***   Errors in algorithm;
					}
					else f = 0;
					
				}
		}
	cout << endl;
	for(int i = 0; i < pSize; i++) 
	{
		cout << frames[i] << "\t";					// Print frames;;
	}
}

	cout << " \nTotal errors " << count << endl;
	cin.get();
}

void Optimal()
{
	int count[10], k = 0, fault = 0, f, dist = 0;
	int max, m, cnt, p, x, flag, temp, current, c;
	cout << "\nEnter frames quantities in pages: \n";
	cin >> f;

	// Init frames in array;
		for(int i = 0; i < f; i++)
		{
			count[i] = 0;
			frames[i] =-1;							// Frames without Errors in algorithm;
		}
		for(int i = 0; i < framesQuantity; i++)
		{
			flag = 0;
			temp = pages[i];

			for(int j = 0; j < f; j++)
			{
				if(temp == frames[j])
				{
					flag = 1;
					break;
				}
			}
				if((flag == 0) && (k < f)) 
				{
					fault++;
					frames[k] = temp;
					k++;
				}
				else if((flag == 0) && (k == f)) 
				{
					fault++;
					for(cnt = 0; cnt < f; cnt++) 
					{
						current = frames[cnt];
							for(c=i; c< framesQuantity; c++)
							{
								if(current != pages[c])
									count[cnt]++;
								else
									break;
							}
					}
						max=0;
						for(m = 0; m < f; m++) 
						{
							if(count[m] > max) 
							{
								max = count[m];
								p = m;
							}
						}
							frames[p] = temp;
				}
		cout << endl;

		for(x = 0; x < f; x++) 
		{
			cout << frames[x] << "\t";				// Print frames;
		}
	}
		cout << "\nTotal errors = " << fault << endl;
		cin.get();
}


void Lru()
{
		int count[10];
		int	k, fault, f, flag, temp, current, c, dist, max, m, cnt, p, x;
		fault = 0;
		dist = 0;
		k = 0;
		cout << "\nEnter frames quantities in pages: " << endl;
		cin >> f;

			// Init frame in array;
			for(int i = 0; i < f; i++)
			{
				count[i] = 0;
				frames[i] =-1;
			}

			for(int i = 0; i < framesQuantity; i++)
			{
				flag = 0;
				temp = pages[i];

				for(int j = 0; j < f; j++)
				{
					if(temp == frames[j])
					{
						flag = 1;
						break;
					}
				}
					if((flag == 0) && (k < f))
					{
						fault++;
						frames[k] = temp;
						k++;
					}
					else if((flag == 0) && (k == f))
					{
						fault++;

							for(cnt = 0; cnt < f; cnt++)
							{
								current = frames[cnt];
								for(c = i; c > 0; c--)		// Errors in algorithm;
								{
									if(current != pages[c])
										count[cnt]++;
									else
										break;
								}
							}
								max=0;
									for(m = 0; m < f; m++)
									{
										if(count[m] > max)
										{
											max = count[m];
											p = m;
										}
									}

									frames[p] = temp;
							}
				
						cout << endl;

					for(x = 0; x < f; x++)
					{
						cout << frames[x] << "\t";					// Print frames;
					}
				}
	cout << "\nTotal errors = " << fault << endl;
	cin.get();
}

