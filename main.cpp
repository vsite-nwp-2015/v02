#include "nwpwin.h"
#include "res.h"

//moji defineovi za velicinu glavnog prozora
#define X_ORIGIN 100
#define Y_ORIGIN 100
#define MAIN_WIDTH 250
#define MAIN_HEIGHT 300


class Edit : public Window
{
public:
	std::string ClassName() { return "EDIT"; }
};

class Button : public Window
{
public:
	std::string ClassName() { return "BUTTON"; }
};

class ListBox : public Window
{
public:
	std::string ClassName() { return "LISTBOX"; }
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
	Edit edit;
	edit.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, NULL, IDC_EDIT, 120, 10, 80, 20);
	
	Button btn_add, btn_rem;
	btn_add.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 120, 40, 80, 20);
	btn_rem.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 120, 70, 80, 20);

	ListBox listbox;
	listbox.Create(*this, WS_CHILD | WS_VISIBLE|WS_BORDER,NULL, IDC_LB, 10, 10, 100, 200);

	EnableWindow(btn_rem, false);

	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			
			MessageBox(*this, "About this app...", "About", MB_OK|MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			char edtxt[64];
			HWND remButt;
			if (GetDlgItemText(*this, IDC_EDIT, edtxt, 64)) {
				SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)edtxt);
				SetDlgItemText(*this, IDC_EDIT, "");
				int count;
				count = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
				if (count) {
					remButt = GetDlgItem(*this, IDC_REMOVE);
					EnableWindow(remButt, true);
				}
				
			}
			break;
		case IDC_REMOVE:
			int index;
			index = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, NULL, NULL);
			if (index >= 0) {
				SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)index, NULL);
			}
			int count;
			count = SendDlgItemMessage(*this, IDC_LB, LB_GETCOUNT, NULL, NULL);
			if (count<=0) {
				remButt = GetDlgItem(*this, IDC_REMOVE);
				EnableWindow(remButt, false);
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu,X_ORIGIN,Y_ORIGIN,MAIN_WIDTH,MAIN_HEIGHT);	
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}
