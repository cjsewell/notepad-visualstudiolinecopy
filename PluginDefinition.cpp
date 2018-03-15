//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "PluginDefinition.h"
#include "menuCmdID.h"

//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE hModule)
{
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

ShortcutKey copyKey;
ShortcutKey cutKey;

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{
  copyKey._isCtrl = true;
  copyKey._key = 0x43; // C

  cutKey._isCtrl = true;
  cutKey._key = 0x58; // X

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
    setCommand(0, TEXT("CopyAllowLine"), copyAllowLine, &copyKey, false);
    setCommand(1, TEXT("CutAllowLine"), cutAllowLine, &cutKey, false);
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

bool getScintilla(HWND &curScintilla)
{
	int which = -1;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
	if (which == -1)
		return false;

	curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;
	return true;
}

bool IsEmptySelection(HWND curScintilla)
{
	int selectionStart = ::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
	int selectionEnd = ::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);

	return selectionStart == selectionEnd;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//
void copyAllowLine()
{
	HWND curScintilla;

	if (!getScintilla(curScintilla))
	{
		::MessageBox(NULL, TEXT("Not Valid"), TEXT("Notepad++ Plugin Template"), MB_OK);
        return;
	}

	::SendMessage(curScintilla, SCI_COPYALLOWLINE, 0, 0);
}

void cutAllowLine()
{
	HWND curScintilla;

	if (!getScintilla(curScintilla))
	{
		::MessageBox(NULL, TEXT("Not Valid"), TEXT("Notepad++ Plugin Template"), MB_OK);
		return;
	}

	if (IsEmptySelection(curScintilla)) // no selection, cut the line
	{
		// if we use just
		// ::SendMessage(curScintilla, SCI_LINECUT, 0, 0);
		// it won't copy the line indicator, making pasting different from visual studio.
		// So, if we're copying the line, simply do copy allow line, and then delete the current line
		::SendMessage(curScintilla, SCI_COPYALLOWLINE, 0, 0);
		::SendMessage(curScintilla, SCI_LINEDELETE, 0, 0);
	}
	else
	{
		::SendMessage(curScintilla, SCI_CUT, 0, 0);
	}
}
