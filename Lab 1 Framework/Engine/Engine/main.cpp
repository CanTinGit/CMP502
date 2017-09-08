////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"
#include <exception>
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;
	bool result_system = true;
	
	// Create the system object.
	//System = new SystemClass;
	//if(!System)
	//{
	//	MessageBox(NULL, TEXT("ERROR"), TEXT("System didn't exist"), MB_OK);
	//	return 0;
	//}

	while (result_system)
	{
		try
		{
			System = new SystemClass;
			if (!System)
			{
				throw 1;
				return 0;
			}

			//Initialize and run
			result = System->Initialize();
			if (result)
			{
				System->Run();
				result_system = false;
			}
			else
			{
				throw 2;
				return 0;
			}
			result_system = false;
		}

		catch (int e)
		{
			if (e == 1)
			{
				int tempResult = MessageBox(NULL, L"Can't create system class", L"Error", MB_RETRYCANCEL);
				switch (tempResult)
				{
				case IDRETRY: break;
				case IDCANCEL: result_system = false; break;
				default: break;
				}
			}

			if (e == 2) 
			{
				int tempResult = MessageBox(NULL, TEXT("System class can initialize"), TEXT("Error"), MB_RETRYCANCEL);
				switch (tempResult)
				{
				case IDRETRY: break;
				case IDCANCEL: result_system = false; break;
				default: break;
				}
			}
		}
	}


	//// Initialize and run the system object.
	//result = System->Initialize();
	//if(result)
	//{
	//	System->Run();
	//}
	//else 
	//{
	//	MessageBox(NULL, TEXT("ERROR"), TEXT("initializing fail"), MB_OK);
	//}
	// Shutdown and release the system object.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}