
// Direct2DGeometrySample.h : main header file for the Direct2DGeometrySample application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDirect2DGeometrySampleApp:
// See Direct2DGeometrySample.cpp for the implementation of this class
//

class CDirect2DGeometrySampleApp : public CWinAppEx
{
public:
	CDirect2DGeometrySampleApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDirect2DGeometrySampleApp theApp;
