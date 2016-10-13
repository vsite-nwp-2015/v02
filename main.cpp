#include "nwpwin.h"
#include "res.h"

class Button : public Window {
public:
	std::string ClassName() { return "BUTTON"; }
};
class Edit : public Window {
	std::string ClassName() { return "EDIT"; }
};
class ListBox : public Window {
	std::string ClassName() { return "ListBox"; }
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
	Button bt1, bt2;
	Edit ed;
	ListBox lb;	
	ed.Create(*this, WS_CHILD | WS_VISIBLE |WS_BORDER,"", IDC_EDIT, 210, 10, 150, 35);
	bt1.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 210, 80, 150, 35);
	bt2.Create(*this, WS_CHILD | WS_VISIBLE | WS_DISABLED, "Remove", IDC_REMOVE, 210, 130, 150, 35);
	lb.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 10, 10, 180, 200);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			DestroyWindow(*this);
			break;
		case ID_HELP_ABOUT:
			MessageBox(NULL, "Nothing here, go back","Pop-Up!", MB_OK | MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			char msg[50];
			GetDlgItemText(*this, IDC_EDIT, msg, 50);		
			SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)msg);
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			break;
		case IDC_REMOVE:
			int zb_index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)zb_index, NULL);
			if (!SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL))
				EnableWindow(GetDlgItem(*this, IDC_REMOVE), false);
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu, CW_USEDEFAULT,CW_USEDEFAULT, 400,280);	
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}
