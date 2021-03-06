
// MFC_VSTDlg.cpp: 實作檔案
//

#include "stdafx.h"
#include "MFC_VST.h"
#include "MFC_VSTDlg.h"
#include "afxdialogex.h"

#include "cvCamCapture.h"
#include "cvVideoPlayer.h"

CCamCapture m_Capture;
CVideoPlayer m_File;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCVSTDlg 對話方塊



CMFCVSTDlg::CMFCVSTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_VST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCVSTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CAPTURE, m_Button_Capture);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, m_Button_Pause);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_Button_Save);
	DDX_Control(pDX, IDC_BUTTON_FILE, m_Button_File);
	DDX_Control(pDX, IDC_BUTTON_RECOGNITION, m_Button_Recognition);
	DDX_Control(pDX, IDC_COMBO_METHOD, m_Combo_Method);
	DDX_Control(pDX, IDC_STATIC_FILE, m_Text_File);
	DDX_Control(pDX, IDC_STATIC_PARAM1, m_Text_Param1);
	DDX_Control(pDX, IDC_STATIC_PARAM2, m_Text_Param2);
	DDX_Control(pDX, IDC_STATIC_PARAM3, m_Text_Param3);
	DDX_Control(pDX, IDC_STATIC_VALUE1, m_Text_Value1);
	DDX_Control(pDX, IDC_STATIC_VALUE2, m_Text_Value2);
	DDX_Control(pDX, IDC_STATIC_VALUE3, m_Text_Value3);
	DDX_Control(pDX, IDC_SLIDER_PARAM1, m_Slider_Param1);
	DDX_Control(pDX, IDC_SLIDER_PARAM2, m_Slider_Param2);
	DDX_Control(pDX, IDC_SLIDER_PARAM3, m_Slider_Param3);
	m_Combo_Method.AddString(L"TemplateMatch");
	m_Combo_Method.AddString(L"MeanShift");
	m_Combo_Method.AddString(L"CamShift");
	//m_Combo_Method.SetCurSel(0);
	m_Button_Save.EnableWindow(FALSE);
	m_Button_Pause.EnableWindow(FALSE);
	m_Button_Recognition.EnableWindow(FALSE);
}

BEGIN_MESSAGE_MAP(CMFCVSTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAPTURE, &CMFCVSTDlg::OnBnClickedButtonCapture)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CMFCVSTDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMFCVSTDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CMFCVSTDlg::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_RECOGNITION, &CMFCVSTDlg::OnBnClickedButtonRecognition)
	ON_CBN_SELCHANGE(IDC_COMBO_METHOD, &CMFCVSTDlg::OnCbnSelchangeComboMethod)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_PARAM1, &CMFCVSTDlg::OnNMCustomdrawSliderParam1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_PARAM2, &CMFCVSTDlg::OnNMCustomdrawSliderParam2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_PARAM3, &CMFCVSTDlg::OnNMCustomdrawSliderParam3)
END_MESSAGE_MAP()


// CMFCVSTDlg 訊息處理常式

BOOL CMFCVSTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCVSTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFCVSTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFCVSTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCVSTDlg::OnDestroy() {
	if (m_Capture.GetCaptureState() != STOP)
		m_Capture.StopCapture();
	m_Capture.DestroyCapture();
}

void CMFCVSTDlg::OnBnClickedButtonCapture() {
	if (m_Capture.GetCaptureState() != STOP) {
		m_Capture.StopCapture();
		m_Button_Capture.SetWindowTextW(_T("Start Capture"));
		m_Button_Pause.SetWindowTextW(_T("Pause"));
		m_Text_File.SetWindowTextW(_T("No File Open."));
		m_Button_File.EnableWindow(TRUE);
		m_Button_Pause.EnableWindow(FALSE);
		m_Button_Save.EnableWindow(FALSE);
	}
	else {
		m_Capture.CreateCapture();
		m_Button_Capture.SetWindowTextW(_T("Stop Capture"));
		m_Text_File.SetWindowTextW(_T("Camera Capturing."));
		m_Text_File.SetWindowTextW(_T("Camera Capturing."));
		m_Button_File.EnableWindow(FALSE);
		m_Button_Pause.EnableWindow(TRUE);
		m_Button_Save.EnableWindow(TRUE);
	}
}

void CMFCVSTDlg::OnBnClickedButtonPause() {
	if (m_Capture.GetCaptureState() != START || m_File.GetCaptureState() != START) {
		m_Button_Pause.SetWindowTextW(_T("Pause"));
	}
	if (m_Capture.GetCaptureState() != PAUSE || m_File.GetCaptureState() != PAUSE) {
		m_Capture.PauseCapture();
		m_File.PauseCapture();
		m_Button_Pause.SetWindowTextW(_T("Continue"));
	}
	else {
		m_Capture.StartCapture();
		m_File.StartCapture();
		m_Button_Pause.SetWindowTextW(_T("Pause"));
	}
}

void CMFCVSTDlg::OnBnClickedButtonSave() {
	if (m_Capture.GetCaptureState() != STOP)
		m_Capture.SaveCapture();
	if (m_File.GetCaptureState() != STOP)
		m_File.SaveCapture();
}

void CMFCVSTDlg::OnBnClickedButtonFile() {
	if (m_File.GetCaptureState() != STOP) {
		m_File.StopCapture();
		m_Text_File.SetWindowTextW(_T("No File Open."));
		m_Button_File.SetWindowTextW(_T("Open File"));
		m_Button_Pause.SetWindowTextW(_T("Pause"));
		m_Button_Capture.EnableWindow(TRUE);
		m_Button_Pause.EnableWindow(FALSE);
		m_Button_Save.EnableWindow(FALSE);
	}
	else {
		// szFilters is a text string that includes two file name filters:
		TCHAR szFilters[] = _T("Video Files (*.avi)|*.avi||");
		CFileDialog fileDlg(TRUE, _T(""), _T(""), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

		// Display the file dialog. When user clicks OK, fileDlg.DoModal() returns IDOK.
		if (fileDlg.DoModal() == IDOK) {
			CString pathName = fileDlg.GetPathName();  // Full path with file name and extension.
			//CString fileName = fileDlg.GetFileTitle(); // Only file name.
			CString extName = fileDlg.GetFileExt(); // Only file extension.

			m_File.ConvertPath(pathName); // Convert CString to std::string
			m_File.CreateCapture();

			m_Text_File.SetWindowTextW(pathName);
			m_Button_File.SetWindowTextW(_T("Close File"));
			m_Button_Capture.EnableWindow(FALSE);
			m_Button_Pause.EnableWindow(TRUE);
			m_Button_Save.EnableWindow(TRUE);
		}
	}
}

void CMFCVSTDlg::OnBnClickedButtonRecognition()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}

void CMFCVSTDlg::OnCbnSelchangeComboMethod() {
	if (m_Combo_Method.GetCurSel() == 0) {
		m_Text_Param1.SetWindowTextW(_T("TM"));
		m_Text_Param2.SetWindowTextW(_T(""));
		m_Text_Param3.SetWindowTextW(_T(""));
		m_Slider_Param1.EnableWindow(true);
		m_Slider_Param2.EnableWindow(false);
		m_Slider_Param3.EnableWindow(false);
		//m_Slider_Param1.SetRange();
		//m_Slider_Param1.SetPos();
	}
	if (m_Combo_Method.GetCurSel() == 1) {
		m_Text_Param1.SetWindowTextW(_T("Vmin"));
		m_Text_Param2.SetWindowTextW(_T("Vmax"));
		m_Text_Param3.SetWindowTextW(_T(""));
		m_Slider_Param1.EnableWindow(true);
		m_Slider_Param2.EnableWindow(true);
		m_Slider_Param3.EnableWindow(false);
		//m_Slider_Param1.SetRange();
		//m_Slider_Param1.SetPos();
		//m_Slider_Param2.SetRange();
		//m_Slider_Param2.SetPos();
	}
	if (m_Combo_Method.GetCurSel() == 2) {
		m_Text_Param1.SetWindowTextW(_T("Vmin"));
		m_Text_Param2.SetWindowTextW(_T("Vmax"));
		m_Text_Param3.SetWindowTextW(_T("Smin"));
		m_Slider_Param1.EnableWindow(true);
		m_Slider_Param2.EnableWindow(true);
		m_Slider_Param3.EnableWindow(true);
		//m_Slider_Param1.SetRange();
		//m_Slider_Param1.SetPos();
		//m_Slider_Param2.SetRange();
		//m_Slider_Param2.SetPos();
		//m_Slider_Param3.SetRange();
		//m_Slider_Param3.SetPos();
	}
}

void CMFCVSTDlg::OnNMCustomdrawSliderParam1(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int m_nKey;
	TCHAR ptcTemp[10];
	m_nKey = m_Slider_Param1.GetPos();
	wsprintf(ptcTemp, TEXT("%d"), m_nKey);
	m_Text_Value1.SetWindowText(ptcTemp);
	*pResult = 0;
}

void CMFCVSTDlg::OnNMCustomdrawSliderParam2(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int m_nKey;
	TCHAR ptcTemp[10];
	m_nKey = m_Slider_Param2.GetPos();
	wsprintf(ptcTemp, TEXT("%d"), m_nKey);
	m_Text_Value2.SetWindowText(ptcTemp);
	*pResult = 0;
}

void CMFCVSTDlg::OnNMCustomdrawSliderParam3(NMHDR *pNMHDR, LRESULT *pResult) {
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int m_nKey;
	TCHAR ptcTemp[10];
	m_nKey = m_Slider_Param3.GetPos();
	wsprintf(ptcTemp, TEXT("%d"), m_nKey);
	m_Text_Value3.SetWindowText(ptcTemp);
	*pResult = 0;
}
