#include <stdio.h>
#include <Windows.h>


// variable to store the HANDLE to the hook. Don't declare it anywhere else then globally
// or you will get problems since every function uses this variable.
HHOOK _hook;

// This struct contains the data received by the hook callback. As you see in the callback function
// it contains the thing you will need: vkCode = virtual key code.
MSLLHOOKSTRUCT msStruct;

// This is the callback function. Consider it the event that is raised when, in this case, 
// a key is pressed.
LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam){
	//printf("Before ncode check\n");
	if (nCode >= 0){
		// the action is valid: HC_ACTION.
		
		//  left mouse button is down
		if(wParam == WM_LBUTTONDOWN){
			// Verification of left button being pressed
			printf("LMouse pressed\n");
			
			// lParam is the pointer to the struct containing the data needed, so cast and assign it to msStruct.
			msStruct = *((MSLLHOOKSTRUCT*)lParam);

			// Print coordinates when left button was clicked
			printf("Coordinates: (%d,%d)\n", msStruct.pt.x, msStruct.pt.y);

			// Code to put coordinates in a text file
			/*
			FILE* file1;
			file1 = fopen("coordenadas.txt", "w");
			fprintf(file1, "oordinates: (%d,%d)\n", msStruct.pt.x, msStruct.pt.y);
			*/
		}
	}

	// call the next hook in the hook chain. This is nessecary or your hook chain will break and the hook stops
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
	// Set the hook and set it to use the callback function above
	// WH_MOUSE_LL means it will set a low level mouse hook. More information about it at MSDN.
	// The last 2 parameters are NULL, 0 because the callback function is in the same thread and window as the
	// function that sets and releases the hook. If you create a hack you will not need the callback function 
	// in another place then your own code file anyway. Read more about it at MSDN.
	if (!(_hook = SetWindowsHookEx(WH_MOUSE_LL, HookCallback, GetModuleHandle(NULL), 0)))
	{
		MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
	}
}


void main() {

	SetHook();
	printf("hook is setted\n");

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{

	}


}