#include "nwpwin.h"
#include "res.h"

// TODO: prepare classes (Edit, Button, ListBox) for child windows
// TODO: derive from Window, override ClassName
class Button : public Window {
public:
	std::string ClassName() override { return "Button";}
};

class Edit : public Window {
public:
	std::string ClassName() override { return "Edit"; }
};

class ListBox : public Window {
public:
	std::string ClassName() override { return "ListBox"; }
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
	// TODO: create all child windows
	// TODO: disable "Remove" button
	Button c; c.Create(*this, WS_CHILD | WS_VISIBLE, "Add", IDC_ADD, 150, 100, 50, 30);
	Button a; a.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 200, 100, 50, 30);
	Edit e; e.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 250, 100, 50, 30);
	ListBox BL; BL.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 300, 100, 50, 100);
	EnableWindow(a, false);
	return 0;
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_FILE_EXIT:
			// TODO: close main window
			OnDestroy();
			break;
		case ID_HELP_ABOUT:
			// TODO: show dialog with text
			MessageBox(*this, "You can do some things here, I hope...", "About", MB_ICONINFORMATION);
			break;
		case IDC_ADD:
			// TODO: get text from edit control
			char chars[10];
			GetWindowText(GetDlgItem(*this, IDC_EDIT), chars, 10);
			// TODO: add string to listbox control
			SendMessage(GetDlgItem(*this, IDC_LB), LB_ADDSTRING, NULL, (LPARAM) chars);
			
			// TODO: enable "Remove" button
			EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
			
			break;
		case IDC_REMOVE:
			// TODO: get listbox selection
			// TODO: if there is a selection, delete selected string
			// TODO: disable "Remove" button if listbox is empty
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
