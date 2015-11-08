
// myShopClient.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "myShopClient_i.h"


// CmyShopClientApp:
// See myShopClient.cpp for the implementation of this class
//

class CmyShopClientApp : public CWinApp
{
public:
	CmyShopClientApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	BOOL ExitInstance(void);
};

extern CmyShopClientApp theApp;