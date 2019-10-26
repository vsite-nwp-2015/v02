﻿#include "nwpwin.h"
#include "res.h"


class Button :public Window {
public:
	std::string ClassName() { return "BUTTON"; }

};
class ListBox :public Window {
	std::string ClassName() { return "LISTBOX"; }

};
class Edit :public Window {
	std::string ClassName() { return "EDIT"; }

};
class MainWindow : public Window
{
protected:
	int OnCreate(CREATESTRUCT* pcs);
	void OnCommand(int id);
	void OnDestroy();
};

int MainWindow::OnCreate(CREATESTRUCT* pcs)
{
	Button b1, b2;
	ListBox lb1;
	Edit e1;
	e1.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "Input", IDC_EDIT, 200, 50, 100, 40);
	b1.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 200, 100, 100, 40);
	b1.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 200, 150, 100, 40);
	lb1.Create(*this, WS_CHILD | WS_VISIBLE | WS_CAPTION, "List", IDC_LB, 100, 50, 100, 200);
	EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
	return 0;
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_FILE_EXIT:
		if(MessageBox(*this, "Are you sure?", "Exit?", MB_YESNO| MB_ICONQUESTION)== IDYES) {
			SendMessage(*this, WM_CLOSE, NULL, NULL);
		}
		break;
	case ID_HELP_ABOUT:
		MessageBox(*this, "About this program", "About", MB_OK| MB_ICONINFORMATION);
		break;
	case IDC_ADD:
		char stringy[100];
		if (GetDlgItemTextA(*this, IDC_EDIT, stringy, 100) != 0) {
			SendDlgItemMessageA(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)stringy);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		}
		break;
	case IDC_REMOVE:
		LRESULT handleitem = SendDlgItemMessageA(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
		if (handleitem == LB_ERR) {
			MessageBox(*this, "No item selected", "Silly goose", MB_RIGHT);
			break;
		}
		else
		{
			SendDlgItemMessageA(*this, IDC_LB, LB_DELETESTRING, handleitem, NULL);
			if (SendDlgItemMessageA(*this, IDC_LB, LB_GETCOUNT, NULL, NULL) == 0){
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
			}
		}
		break;
	}
}

void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDM_V2));
	MainWindow wnd; 
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu);	
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}
