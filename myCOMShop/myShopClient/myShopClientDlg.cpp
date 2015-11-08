
// myShopClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myShopClient.h"
#include "myShopClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmyShopClientDlg dialog




CmyShopClientDlg::CmyShopClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmyShopClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmyShopClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOP, m_shopList);
	DDX_Control(pDX, IDC_CART, m_cartList);
}

BEGIN_MESSAGE_MAP(CmyShopClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CmyShopClientDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_REMOVE, &CmyShopClientDlg::OnBnClickedRemove)
	ON_BN_CLICKED(IDC_BUY, &CmyShopClientDlg::OnBnClickedBuy)
END_MESSAGE_MAP()


// CmyShopClientDlg message handlers

BOOL CmyShopClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	UpdateShopList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmyShopClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CmyShopClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmyShopClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmyShopClientDlg::UpdateShopList(void)  
{
	m_shopList.ResetContent();
	long count;
	bool cond;
	if (cond=!m_pShop)
		m_pShop.CoCreateInstance(CLSID_myShop);
	HRESULT hr = m_pShop->get_Count(&count);
	USES_CONVERSION;
	for (long i = 0; i < count; i++)
	{
		CComBSTR name;
		HRESULT hr = m_pShop->getNamesByIndex(i,&name);
		if (FAILED(hr))
		{   
			m_shopList.AddString("Failed to read from Shop");
			break;  
		}    
		long itemCount; 
		hr = m_pShop->getCountByIndex(i,&itemCount);
		if (FAILED(hr)) 
		{ 
			m_shopList.AddString("Failed to read from Shop");  
			break; 
		}     
		char buf[200]; 
		sprintf(buf,"%s %d ", W2A(name),itemCount);    
		m_shopList.AddString(buf); 
		// The list is not sorted and the items in DB   
		// are numbered 0 through n for simplicity.  
	}
}



void CmyShopClientDlg::OnBnClickedAdd()
{
	int curSel = m_shopList.GetCurSel();
	if (curSel<0) return;
	CString selectedProduct;
	m_shopList.GetText(curSel,selectedProduct);
	char buf[200]; // Extract product name
	int count;     // Extract product count
	sscanf(selectedProduct,"%s %d",buf,&count);
	int cartIndex = m_cartList.AddString(buf);
	// curSel is also database key since the
	// m_shopList is not sorted.   
	m_cartList.SetItemData(cartIndex,curSel);
}


void CmyShopClientDlg::OnBnClickedRemove()
{
	int curSel = m_cartList.GetCurSel();
	if (curSel<0) return;
	m_cartList.DeleteString(curSel);
}


void CmyShopClientDlg::OnBnClickedBuy()
{
	int count = m_cartList.GetCount();
	for (int i =0; i < count; i++)
	{        
		long productId = m_cartList.GetItemData(i);
		HRESULT hr = m_pShop->buy(productId);   
	}    m_cartList.ResetContent();   
	UpdateShopList();
}
