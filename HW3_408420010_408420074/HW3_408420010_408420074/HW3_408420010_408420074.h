
// HW3_408420010_408420074.h: HW3_408420010_408420074 應用程式的主要標頭檔
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // 主要符號


// CHW3_408420010_408420074App:
// 查看 HW3_408420010_408420074.cpp 以了解此類別的實作
//

class CHW3_408420010_408420074App : public CWinApp
{
public:
	CHW3_408420010_408420074App() noexcept;


// 覆寫
public:
	virtual BOOL InitInstance();

// 程式碼實作
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHW3_408420010_408420074App theApp;
