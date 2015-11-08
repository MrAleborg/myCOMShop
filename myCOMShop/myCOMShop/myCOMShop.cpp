// myCOMShop.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "myCOMShop_i.h"



class CmyCOMShopModule : public ATL::CAtlExeModuleT< CmyCOMShopModule >
	{
public :
	DECLARE_LIBID(LIBID_myCOMShopLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MYCOMSHOP, "{5C27EE08-F1C0-4947-AD67-DD6183F8CEF5}")
	};

CmyCOMShopModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

