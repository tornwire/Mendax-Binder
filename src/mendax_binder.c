#include <windows.h>
#include <stdio.h>
#include "resources.h"

//gcc -o mendax_binder.exe mendax_binder.c mendax_rc.o icon.o menu.o dialog_about.o important.o confirm.o bg.o bindmore.o -mwindows

const char g_szClassName[] = "Mendax Binder GUI";
char *input1 = NULL;
char *input2 = NULL;
char *output = NULL;
HBITMAP g_hbmBall = NULL;

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
        return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK MoreInfoDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
        return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK ConfirmDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
        return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                break;
				case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK ImportantDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:

        return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                break;
				case IDCANCEL:
                    exit(0);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}

int generate(HWND hwnd, char *input1, char *input2, char *output)
{
	char command[MAX_PATH] = "";
	sprintf(command, "mendax.exe -1 %s -2 %s -o %s -s", input1, input2, output);
	if (system(command) == 0)
	{
		MessageBox(hwnd, "Binded File Successfully Generated!", "Success", MB_OK | MB_ICONINFORMATION);
		return 0;
	}
	MessageBox(hwnd, "An Unknown Error Occurred.  Please check the program directory's integrity or restart the program. If the issue persists, contact the developer.", "Failed", MB_OK | MB_ICONINFORMATION);
	return 1;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hButton1;
	HWND hButton2;
	HWND hButton3;
	HWND bind;
	HWND exit;
	HINSTANCE hInstance;
	OPENFILENAME ofn1;
	OPENFILENAME ofn2;
	OPENFILENAME ofn3;
	char szFileName[MAX_PATH] = "";
	HWND topText;
    switch(msg)
    {
		case WM_CREATE:
			hButton1 = CreateWindow("button", "Select the First File to Merge", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 225, 60, 191, 20, hwnd, (HMENU)ID_BUTTON_1, hInstance, NULL);
			hButton2 = CreateWindow("button", "Select the Second File to Merge", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 209, 110, 220, 20, hwnd, (HMENU)ID_BUTTON_2, hInstance, NULL);
			hButton3 = CreateWindow("button", "Select the Output File Name", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 223, 160, 195, 20, hwnd, (HMENU)ID_BUTTON_3, hInstance, NULL);
			bind = CreateWindow("button", "BIND!", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 265, 220, 120, 50, hwnd, (HMENU)ID_BIND, hInstance, NULL);
			bind = CreateWindow("button", "Exit", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 290, 310, 70, 20, hwnd, (HMENU)ID_EXIT, hInstance, NULL);
			topText = CreateWindow("STATIC", "This program is made by BitsByWill and is licensed under the GNU GPLv3", WS_VISIBLE | WS_CHILD | SS_LEFT, 3, 1, 500, 20, hwnd, NULL, hInstance, NULL);
			g_hbmBall = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BG));
		break;
		case WM_PAINT:
		{
			BITMAP bm;
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmOld;
			hbmOld = SelectObject(hdcMem, g_hbmBall);
			GetObject(g_hbmBall, sizeof(bm), &bm);
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hbmOld);
			DeleteDC(hdcMem);
			EndPaint(hwnd, &ps);
		}
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case ID_BUTTON_1:
						ZeroMemory(&ofn1, sizeof(ofn1));
						ofn1.lStructSize = sizeof(ofn1); 
						ofn1.hwndOwner = hwnd;
						ofn1.lpstrFilter = "Executable (*.exe)\0*.exe\0All Files (*.*)\0*.*\0";
						ofn1.lpstrFile = szFileName;
						ofn1.nMaxFile = MAX_PATH;
						ofn1.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn1.lpstrDefExt = "exe";
						if(GetOpenFileName(&ofn1))
						{
							input1 = strdup(szFileName);
						}
				break;
				case ID_BUTTON_2:
					ZeroMemory(&ofn2, sizeof(ofn2));
					ofn2.lStructSize = sizeof(ofn2); 
					ofn2.hwndOwner = hwnd;
					ofn2.lpstrFilter = "Executable (*.exe)\0*.exe\0All Files (*.*)\0*.*\0";
					ofn2.lpstrFile = szFileName;
					ofn2.nMaxFile = MAX_PATH;
					ofn2.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
					ofn2.lpstrDefExt = "exe";
					if(GetOpenFileName(&ofn2))
					{
						input2 = strdup(szFileName);
					}
				break;
				case ID_BUTTON_3:
					ZeroMemory(&ofn3, sizeof(ofn3));
					ofn3.lStructSize = sizeof(ofn3);
					ofn3.hwndOwner = hwnd;
					ofn3.lpstrFilter = "Executable (*.exe)\0*.exe\0All Files (*.*)\0*.*\0";
					ofn3.lpstrFile = szFileName;
					ofn3.nMaxFile = MAX_PATH;
					ofn3.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
					ofn3.lpstrDefExt = "exe";
					if(GetOpenFileName(&ofn3))
					{
						output = strdup(szFileName);
					}
				break;
				case ID_FILE_ABOUT:
				{
					int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_FILE_ABOUT), hwnd, AboutDlgProc);
					if(ret != IDOK)
					{
						MessageBox(hwnd, "An Unknown Error Occurred", "Error", MB_OK | MB_ICONINFORMATION);
					}
				}
				break;
				case ID_HELP_BIND_MORE:
				{
				    int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_HELP_BIND_MORE), hwnd, MoreInfoDlgProc);
					if(ret != IDOK)
					{
						MessageBox(hwnd, "An Unknown Error Occurred", "Error", MB_OK | MB_ICONINFORMATION);
					}
				}
				break;
				case ID_IMPORTANT:
				{
					int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_IMPORTANT), hwnd, ImportantDlgProc);
					if(ret != IDOK && ret != IDCANCEL)
					{
						MessageBox(hwnd, "An Unknown Error Occurred", "Error", MB_OK | MB_ICONINFORMATION);
					}
				}
				break;
				case ID_FILE_EXIT:
					PostMessage(hwnd, WM_CLOSE, 0, 0);
				break;
				case ID_BIND:
				{
					int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_CONFIRM), hwnd, ConfirmDlgProc);
					if(ret != IDOK && ret != IDCANCEL)
					{
						MessageBox(hwnd, "An Unknown Error Occurred", "Error", MB_OK | MB_ICONINFORMATION);
					}
					if (input1 == NULL || input2 == NULL || output == NULL)
					{
						MessageBox(hwnd, "Please make sure you select the input and output files.", "Error", MB_OK | MB_ICONINFORMATION);
					}
					else if (strcmp(input1, input2) == 0)
					{
						MessageBox(hwnd, "Please make sure you select distinct input files.", "Error", MB_OK | MB_ICONINFORMATION);
					}
					else
					{
						generate(hwnd, input1, input2, output);
					}
				}
				break;
				case ID_EXIT:
					PostMessage(hwnd, WM_CLOSE, 0, 0);
				break;
			}
		break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd, textbox1;
    MSG Msg;
	HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
	wc.hIcon  = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wc.lpszClassName = g_szClassName;
    wc.hIconSm  = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON), IMAGE_ICON, 16, 16, 0);
    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName,"Mendax Binder", WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, 620, 490, NULL, NULL, hInstance, NULL);	
    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
