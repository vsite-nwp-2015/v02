#include "nwpwin.h"
#include "res.h"

class Edit : public Window {
protected:
	std::string ClassName()override { return "EDIT"; }
};

class Button : public Window {
protected:
	std::string ClassName()override { return "BUTTON"; }
	
};

class ListBox : public Window {
protected:
	std::string ClassName()override { return "LISTBOX"; }
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
	Button add, remove;
	add.Create(*this, WS_CHILD|WS_VISIBLE, "Add", IDC_ADD, 200, 90, 80, 25);
	remove.Create(*this, WS_CHILD | WS_VISIBLE, "Remove", IDC_REMOVE, 200, 125, 80, 25);
	EnableWindow(remove, false);

	ListBox lBox;
	lBox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_LB, 70, 60, 100, 150);

	Edit ebox;
	ebox.Create(*this, WS_CHILD | WS_VISIBLE | WS_BORDER, "", IDC_EDIT, 200, 60, 80, 20);

	return 0;
}

void MainWindow::OnCommand(int id){
	
	switch (id) {
	case ID_FILE_EXIT:
		if (MessageBox(*this, "Are you sure you want to leave", "Exit", IDOK) == IDOK)
			DestroyWindow(*this);
		break;
	case ID_HELP_ABOUT:
		MessageBox(*this, "Use Add to add string to list.\nSelect element from the list and press Remove to remove it from list.", "Help", IDOK);
		break;
	case IDC_ADD: {
		TCHAR inpEBox[51];

		GetDlgItemText(*this, IDC_EDIT, inpEBox, sizeof(inpEBox) - 1);
		SendDlgItemMessage(*this, IDC_LB, LB_ADDSTRING, 0, (LPARAM)inpEBox);
		EnableWindow(GetDlgItem(*this, IDC_REMOVE), true);
		break;
	}
	case IDC_REMOVE:
		int lbSel = SendDlgItemMessage(*this, IDC_LB, LB_GETCURSEL, 0, 0);
		if (lbSel >= 0 && !SendDlgItemMessage(*this, IDC_LB, LB_DELETESTRING, (WPARAM)lbSel, 0))
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 2", (int)hMenu);	
	// set icons
	HICON hib = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hib));
	HICON his = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_V2), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	PostMessage(wnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(his));

	Application app; 
	return app.Run();
}
