
// myShopClientDlg.h : header file
//


 
#pragma once
#include "afxwin.h"
#import "..\\myCOMShop\\Release\\myCOMShop.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids


// CmyShopClientDlg dialog
class CmyShopClientDlg : public CDialogEx
{
// Construction
public:
	CmyShopClientDlg(CWnd* pParent = NULL);	// standard constructor


// Dialog Data
	enum { IDD = IDD_MYSHOPCLIENT_DIALOG };

private :
	void UpdateShopList(void);

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	CComPtr<ImyShop> m_pShop;


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_shopList;
	CListBox m_cartList;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedRemove();
	afx_msg void OnBnClickedBuy();
};
