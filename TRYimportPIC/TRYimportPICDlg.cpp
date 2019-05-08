
// TRYimportPICDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TRYimportPIC.h"
#include "TRYimportPICDlg.h"
#include "resource.h"
#include "NMFC_PASS.h"
//#include "afxdialogex.h"

#include "BVMainCore.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int EventCallbackFunc(UINT32 IntSrc);
int EventCallbackFuncBack(UINT32 IntSrc);
CWinThread* FHz_Thread;
static UINT StartTestGKThread(void *param);
void loadbitmap();
static bool numofneeflag = TRUE;
static bool oilstateflag = TRUE;
static bool ballflag = TRUE;
static bool stateflag = TRUE;
static int num = 0;
static int cirlight = 0;
static int backlight = 0;
int wSums(Mat src);
void Imgprocess();
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CTRYimportPICDlg 对话框




CTRYimportPICDlg::CTRYimportPICDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTRYimportPICDlg::IDD, pParent)
	, m_bDevOpened(FALSE)
	, m_bIsSnap(FALSE)
	, m_bIsSaveImg(FALSE)
	, m_bColorFilter(false)
	, m_hDevice(NULL)
	, m_pBmpInfo(NULL)
	, m_pBufferRaw(NULL)
	, m_pBufferRGB(NULL)
	, m_nPayLoadSize(0)
	, m_nImageHeight(0)
	, m_nImageWidth(0)
	, m_nImageHeightnew(0)
	, m_nImageWidthnew(0)
	, m_nPixelColorFilter(GX_COLOR_FILTER_NONE)
	, m_pWnd(NULL)
	, m_hDC(NULL)
	, cur_name(NULL)
	, cur_num(NULL)
	, cur_class(NULL)
	, m_strFilePath("")
	, m_numOfnee(FALSE)
	, m_numOfball(TRUE)
	, m_oilState(TRUE)
	, m_pBmpInfonew1(NULL)
	, m_pBmpInfonew2(NULL)
	, m_pBufferRGBnew1(NULL)
	, m_pBufferRGBnew2(NULL)
	//, m_numcombo(_T("CY570858D"))
	//, IO_in(FALSE)
	//, IO_out(FALSE)
	//, Process_state(FALSE)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// 初始化参数
	memset(m_chBmpBuf, 0, sizeof(m_chBmpBuf));
}

void CTRYimportPICDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLASS_COMBO, m_classcombo);
	DDX_Control(pDX, IDC_NAME_COMBO, m_namecombo);
	//DDX_Control(pDX, IDC_NUM_COMBO, m_numcombo);
	DDX_Control(pDX, IDC_BALLNG_BMP3, m_ballNG);
	DDX_Control(pDX, IDC_NUMNG_BMP1, m_numNG);
	DDX_Control(pDX, IDC_OILNG_BMP2, m_oilNG);
	//  DDX_Control(pDX, IDC_EDIT2, NumofOk);
	//  DDX_Text(pDX, IDC_EDIT2, NumofOk);
	//  DDX_Control(pDX, IDC_STATENG_BMP4, m_stateNG);
	DDX_Control(pDX, IDC_STATENG_BMP4, m_stateNG);
}

BEGIN_MESSAGE_MAP(CTRYimportPICDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_CLOSE_DEVICE, &CTRYimportPICDlg::OnClickedCloseDevice)
	//ON_BN_CLICKED(IDC_OPEN_DEVICE, &CTRYimportPICDlg::OnClickedOpenDevice)
	//ON_BN_CLICKED(IDC_START_SNAP, &CTRYimportPICDlg::OnClickedStartSnap)
	//ON_BN_CLICKED(IDC_STOP_SNAP, &CTRYimportPICDlg::OnClickedStopSnap)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CTRYimportPICDlg::OnClickedClearButton)
	ON_BN_CLICKED(IDC_EXCHANGE_BUTTON, &CTRYimportPICDlg::OnClickedExchangeButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CTRYimportPICDlg::OnClickedSaveButton)
	ON_BN_CLICKED(IDC_SAVE_PIC_BUTTON, &CTRYimportPICDlg::OnClickedSavePicButton)
	ON_BN_CLICKED(IDC_SAVE_CHECK, &CTRYimportPICDlg::OnClickedSaveCheck)
	ON_BN_CLICKED(IDC_BACK_BUTTON, &CTRYimportPICDlg::OnClickedBackButton)
	ON_BN_CLICKED(IDC_CIRCLE_BUTTON, &CTRYimportPICDlg::OnClickedCircleButton)
	ON_BN_CLICKED(IDC_BUTTON_MANAGER, &CTRYimportPICDlg::OnClickedButtonManager)
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_SHOW_FRAME, &CTRYimportPICDlg::OnStnClickedStaticShowFrame)
END_MESSAGE_MAP()


// CTRYimportPICDlg 消息处理程序

volatile int p_num;
volatile float p_erra;
volatile float p_cirligntmin;
volatile float p_cirlightmax;
volatile float p_backlightmin;
volatile float p_backlightmax;
volatile int p_cirratio;
volatile int p_neeamin;
volatile int p_neegreymin;
volatile float p_outerramin;
volatile float p_outserramin;
volatile float p_ballerramin;
CString p_adreass;
volatile long p_savetime;
volatile BOOL p_checksave;
volatile BOOL p_checkNGimg;
volatile BOOL p_checkcirlight;
volatile BOOL p_checkbacklight;
volatile BOOL p_checkcirratio;
volatile BOOL p_checkneeamin;
volatile BOOL p_checkneegreymin;
volatile BOOL p_checkouterramin;
volatile BOOL p_checkoutserramin;
volatile BOOL p_checkballerramin;
volatile float cirraitooutput;

BOOL CTRYimportPICDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	readPara();
	deletefiles();
	font.CreatePointFont(200, _T("宋体"));
	GetDlgItem(IDC_CAPTION)->SetFont(&font);
	font.CreatePointFont(175, _T("宋体"));
	GetDlgItem(IDC_STATIC_NUMNG)->SetFont(&font);
	font.CreatePointFont(175, _T("宋体"));
	GetDlgItem(IDC_STATIC_OILNG)->SetFont(&font);
	font.CreatePointFont(175, _T("宋体"));
	GetDlgItem(IDC_STATIC_STATENG)->SetFont(&font);
	font.CreatePointFont(175, _T("宋体"));
	GetDlgItem(IDC_STATIC_BALLNG)->SetFont(&font);
	font.CreatePointFont(175, _T("宋体"));
	GetDlgItem(IDC_STATIC_TESTMODE)->SetFont(&font);
	font.CreatePointFont(175, _T("宋体"));
	GetDlgItem(IDC_STATIC_CLASS)->SetFont(&font);
	font.CreatePointFont(175, _T("宋体"));
	GetDlgItem(IDC_STATIC_NAME)->SetFont(&font);
	font.CreatePointFont(125, _T("宋体"));
	GetDlgItem(IDC_STATIC_BIAO)->SetFont(&font);
	font.CreatePointFont(175, _T("宋体"));
	GetDlgItem(IDC_STATIC_NUMOK)->SetFont(&font);
	font.CreatePointFont(175, _T("宋体"));
	GetDlgItem(IDC_STATIC_NUM)->SetFont(&font);

	m_classcombo.AddString(_T("CY570866A"));
	m_classcombo.InsertString(1, _T("型号2"));
	m_classcombo.SetCurSel(0);
	m_namecombo.AddString(_T("CY570866A"));
	m_namecombo.InsertString(1, _T("13"));
	m_namecombo.InsertString(2, _T("14"));
	m_namecombo.SetCurSel(0);

	//打开设备



	GX_STATUS emStatus = GX_STATUS_SUCCESS;
	//初始化库
	emStatus = GXInitLib();
	if (emStatus != GX_STATUS_SUCCESS)
	{
		ShowErrorString(emStatus);
		exit(0);
	}

	// 获取当前程序执行路径,设置图像保存的默认路径
	CString strDate = "";
	char    szName[MAX_PATH] = { 0 };
	CString strAppFullName = "";
	GetModuleFileName(NULL, szName, MAX_PATH);
	strAppFullName = szName;
	int nPos = strAppFullName.ReverseFind('\\');
	m_strFilePath += strAppFullName.Left(nPos);
	m_strFilePath += "\\GxSingleCamColorImages";

	//获取图像显示窗口的指针和绘图DC
	m_pWnd = GetDlgItem(IDC_STATIC_SHOW_FRAME);
	m_pWnd2 = GetDlgItem(IDC_STATIC_SHOW_FRAME2);
	m_hDC = ::GetDC(m_pWnd->m_hWnd);
	m_hDC2 = ::GetDC(m_pWnd2->m_hWnd);
	// 更新界面控件
	UpDateUI();

	//IO初始化
	Roseek_MainCore_Init();
	Roseek_MainCore_Start();

	int ret2 = Roseek_DI_SetEventMask(255);
	for (byte i = 0; i < 8; i++)
	{
		Roseek_DI_SetEventMode(i, DI_EVENT_RISING);
		//Roseek_DI_SetMode(i, DI_MODE_NORMAL);
	}
	loadbitmap();
	initOpenDevice();
	initStartSnap();
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTRYimportPICDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTRYimportPICDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTRYimportPICDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTRYimportPICDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	initStopSnap();
	initCloseDevice();
	KillTimer(0);

	GX_STATUS emStatus = GX_STATUS_SUCCESS;

	// 若未停采则先停止采集
	if (m_bIsSnap)
	{
		// 发送停止采集命令
		emStatus = GXSendCommand(m_hDevice, GX_COMMAND_ACQUISITION_STOP);

		// 注销回调
		emStatus = GXUnregisterCaptureCallback(m_hDevice);
		m_bIsSnap = FALSE;

		// 释放为采集图像开辟的图像Buffer
		UnPrepareForShowImg();
	}

	//释放pDC
	::ReleaseDC(m_pWnd->m_hWnd, m_hDC);
	::ReleaseDC(m_pWnd2->m_hWnd, m_hDC2);
	// 未关闭设备则关闭设备
	if (m_bDevOpened)
	{
		emStatus = GXCloseDevice(m_hDevice);
		m_bDevOpened = FALSE;
		m_hDevice = NULL;

	}

	// 关闭设备库
	emStatus = GXCloseLib();

	//停止主库
	Roseek_MainCore_Stop();
	//主库释放
	Roseek_MainCore_UnInit();

	CDialog::OnClose();
}

void CTRYimportPICDlg::InitUI()
{
	GX_STATUS emStatus = GX_STATUS_ERROR;
	int  nValue = 0;

}
static CTRYimportPICDlg *pDlgstatic;
//初始化枚举函数
volatile BOOL IO_Cir = FALSE; //IO口的输入输出以及处理状态
volatile BOOL IO_Back = FALSE;
volatile BOOL Process_state = FALSE;
volatile int NumofOk = 0;
volatile BOOL showImgFlag = FALSE;
//初始化三个状态,三个状态标记事件发生时需要拍什么照片。

void __stdcall CTRYimportPICDlg::OnFrameCallbackFun(GX_FRAME_CALLBACK_PARAM* pFrame)
{
	/*if ((IO_Cir == FALSE && IO_Back == FALSE) ||Process_state == FALSE)
	{
	return;
	}*/
	/*if (IO_Cir == FALSE || IO_Back == FALSE || Process_state == FALSE)
	{
	return;
	}*/

	CTRYimportPICDlg *pDlg = (CTRYimportPICDlg*)(pFrame->pUserParam);

	if (pFrame->status == 0)
	{
		memcpy(pDlg->m_pBufferRaw, pFrame->pImgBuf, pFrame->nImgSize);

		// RGB转换
		DxRaw8toRGB24(pDlg->m_pBufferRaw
			, pDlg->m_pBufferRGB
			, (VxUint32)(pDlg->m_nImageWidth)
			, (VxUint32)(pDlg->m_nImageHeight)
			, RAW2RGB_NEIGHBOUR
			, DX_PIXEL_COLOR_FILTER(pDlg->m_nPixelColorFilter)
			, TRUE);

		// 显示图像
		//pDlg->DrawImg();

		// 图像保存（勾选了存NG图）
		pDlgstatic = pDlg;


		// 图像处理之前的保存，此处移动到事件函数里面调用
		//pDlg->SaveImageForP(IO_Cir, IO_Back);


		//pDlg->Imgprocess();
		//pDlg->ShowResult();

		//-----------------------------------------------------------------
		/*if (numofneeflag == FALSE&&oilstateflag == FALSE&&ballflag == TRUE)
		{
		pDlg->ShowResult();
		numofneeflag = FALSE;
		oilstateflag = TRUE;
		ballflag = TRUE;
		}
		if (numofneeflag == FALSE&&oilstateflag == TRUE&&ballflag == TRUE)
		{
		pDlg->ShowResult();
		numofneeflag = TRUE;
		oilstateflag = TRUE;
		ballflag = TRUE;
		}*/

		//------------------------------------------------------------------
		/*if (!(numofneeflag == TRUE&&oilstateflag == TRUE&&ballflag == TRUE))
		{
		pDlg->ShowResult();
		numofneeflag = TRUE;
		oilstateflag = TRUE;
		ballflag = TRUE;
		}*/

		//IO_Cir=FALSE; //IO口的输入输出以及处理状态
		//IO_Back=FALSE;
		//Process_state=FALSE;

	}
}
static  CBitmap bitmap1suc;
static  CBitmap bitmap1fal;

static	CBitmap bitmap2suc;
static  CBitmap bitmap2fal;

static	CBitmap bitmap3suc;
static  CBitmap bitmap3fal;

static	CBitmap bitmap4suc;
static  CBitmap bitmap4fal;

static	HBITMAP hBmp1suc;
static	HBITMAP hBmp1fal;

static	HBITMAP hBmp2suc;
static	HBITMAP hBmp2fal;

static	HBITMAP hBmp3suc;
static	HBITMAP hBmp3fal;

static	HBITMAP hBmp4suc;
static	HBITMAP hBmp4fal;

void loadbitmap()
{
	bitmap1fal.LoadBitmap(IDB_BITMAP_RED);
	bitmap1suc.LoadBitmap(IDB_BITMAP_GREEN);

	bitmap2fal.LoadBitmap(IDB_BITMAP_RED);
	bitmap2suc.LoadBitmap(IDB_BITMAP_GREEN);

	bitmap3fal.LoadBitmap(IDB_BITMAP_RED);
	bitmap3suc.LoadBitmap(IDB_BITMAP_GREEN);

	bitmap4fal.LoadBitmap(IDB_BITMAP_RED);
	bitmap4suc.LoadBitmap(IDB_BITMAP_GREEN);

	hBmp1suc = (HBITMAP)bitmap1suc.GetSafeHandle();
	hBmp1fal = (HBITMAP)bitmap1fal.GetSafeHandle();

	hBmp2suc = (HBITMAP)bitmap2suc.GetSafeHandle();
	hBmp2fal = (HBITMAP)bitmap2fal.GetSafeHandle();

	hBmp3suc = (HBITMAP)bitmap3suc.GetSafeHandle();
	hBmp3fal = (HBITMAP)bitmap3fal.GetSafeHandle();

	hBmp4suc = (HBITMAP)bitmap3suc.GetSafeHandle();
	hBmp4fal = (HBITMAP)bitmap3fal.GetSafeHandle();
}

void CTRYimportPICDlg::ShowResult()
{
	m_numNG.SetBitmap(NULL);
	m_oilNG.SetBitmap(NULL);
	m_ballNG.SetBitmap(NULL);
	m_stateNG.SetBitmap(NULL);
	if (numofneeflag == FALSE)
	{

		m_numNG.SetBitmap(hBmp1fal);
		//m_stateNG.SetBitmap(hBmp4fal);
	}

	else
	{

		m_numNG.SetBitmap(hBmp1suc);
		//m_stateNG.SetBitmap(hBmp4suc);
	}

	if (oilstateflag == FALSE)
	{
		m_oilNG.SetBitmap(hBmp2fal);
		//m_stateNG.SetBitmap(hBmp4fal);
	}


	else {
		m_oilNG.SetBitmap(hBmp2suc);
		//m_stateNG.SetBitmap(hBmp4suc);
	}

	if (ballflag == FALSE)
	{
		m_ballNG.SetBitmap(hBmp3fal);
		//m_stateNG.SetBitmap(hBmp4fal);
	}

	else {
		m_ballNG.SetBitmap(hBmp3suc);
		//m_stateNG.SetBitmap(hBmp4suc);
	}
	if ((ballflag == FALSE) || (oilstateflag == FALSE) || (numofneeflag == FALSE) || (stateflag == FALSE)){
		m_stateNG.SetBitmap(hBmp4fal);
	}
	else {
		m_stateNG.SetBitmap(hBmp4suc);
	}




	if ((numofneeflag == TRUE) && (oilstateflag == TRUE) && (ballflag == TRUE)){
		num++;
		CString str;
		str.Format(_T("%d"), num);
		pDlgstatic->GetDlgItem(IDC_STATIC_NUM)->SetWindowTextA(str);

		/*CString str_ok = "OK";
		pDlgstatic->GetDlgItem(IDC_STATIC_BACKOK)->SetWindowTextA(str_ok);
		pDlgstatic->GetDlgItem(IDC_STATIC_CIROK)->SetWindowTextA(str_ok);*/
	}
	//else {
	//	CString str_ok = "FALSE";
	//	pDlgstatic->GetDlgItem(IDC_STATIC_BACKOK)->SetWindowTextA(str_ok);
	//	pDlgstatic->GetDlgItem(IDC_STATIC_CIROK)->SetWindowTextA(str_ok);
	//}
	//CString str_cir, str_back;
	//str_cir.Format(_T("%d"), cirlight);
	//str_back.Format(_T("%d"), backlight);
	//pDlgstatic->GetDlgItem(IDC_STATIC_CIRLIGHT)->SetWindowTextA(str_cir);
	//pDlgstatic->GetDlgItem(IDC_STATIC_BACKLIGHT)->SetWindowTextA(str_back);
}

void CTRYimportPICDlg::DrawImg()
{
	if (!PrepareForShowImgnew())
	{
		MessageBox("为图像显示分配资源失败!");
		return;
	}
	int nWndWidth = 0;
	int nWndHeight = 0;

	// 为画图做准备
	RECT objRect;
	RECT objRect2;
	m_pWnd->GetClientRect(&objRect);
	m_pWnd2->GetClientRect(&objRect2);
	nWndWidth = objRect.right - objRect.left;
	nWndHeight = objRect.bottom - objRect.top;

	// 必须调用该语句，否则图像出现水纹
	if ((IO_Cir == FALSE) && (IO_Back == TRUE) && (showImgFlag == TRUE)){
		::SetStretchBltMode(m_hDC, COLORONCOLOR);
		::StretchDIBits(m_hDC,
			0,
			0,
			nWndWidth,
			nWndHeight,
			0,
			0,
			(int)m_nImageWidthnew,
			(int)m_nImageHeightnew,
			m_pBufferRGBnew1,
			m_pBmpInfonew1,
			DIB_RGB_COLORS,
			SRCCOPY
			);
		//showImgFlag = FALSE;
	}
	//if ((IO_Cir == TRUE) && (IO_Back == FALSE) && (showImgFlag == TRUE)){
	if ((IO_Cir == FALSE) && (IO_Back == TRUE) && (showImgFlag == TRUE)){
		::SetStretchBltMode(m_hDC2, COLORONCOLOR);
		::StretchDIBits(m_hDC2,
			0,
			0,
			nWndWidth,
			nWndHeight,
			0,
			0,
			(int)m_nImageWidthnew,
			(int)m_nImageHeightnew,
			m_pBufferRGBnew2,
			m_pBmpInfonew2,
			DIB_RGB_COLORS,
			SRCCOPY
			);
		showImgFlag = FALSE;
	}
	
}

bool CTRYimportPICDlg::PrepareForShowImg()
{

	//--------------------------------------------------------------------
	//---------------------------初始化bitmap头---------------------------
	m_pBmpInfo = (BITMAPINFO *)m_chBmpBuf;
	m_pBmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfo->bmiHeader.biWidth = (LONG)m_nImageWidth;
	m_pBmpInfo->bmiHeader.biHeight = (LONG)m_nImageHeight;

	m_pBmpInfo->bmiHeader.biPlanes = 1;
	m_pBmpInfo->bmiHeader.biBitCount = 24;
	m_pBmpInfo->bmiHeader.biCompression = BI_RGB;
	m_pBmpInfo->bmiHeader.biSizeImage = 0;
	m_pBmpInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpInfo->bmiHeader.biClrUsed = 0;
	m_pBmpInfo->bmiHeader.biClrImportant = 0;

	//---------------------------------------------------------------------
	//----------------------------为图像数据分配Buffer---------------------
	//为存储RGB图像数据申请空间
	m_pBufferRGB = new BYTE[(size_t)(m_nImageWidth * m_nImageHeight * 3)];
	if (m_pBufferRGB == NULL)
	{
		return false;
	}

	//为存储原始图像数据申请空间
	m_pBufferRaw = new BYTE[(size_t)m_nPayLoadSize];
	if (m_pBufferRaw == NULL)
	{
		delete[]m_pBufferRGB;
		m_pBufferRGB = NULL;

		return false;
	}




	return true;
}

bool CTRYimportPICDlg::PrepareForShowImgnew()
{
	CString BmpName1 = "C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\42_back.bmp";
	CString BmpName2 = "C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\41_front.bmp";

	CFile bmpFile1;
	CFile bmpFile2;
	BITMAPFILEHEADER bmpHeader1;//文件头
	BITMAPFILEHEADER bmpHeader2;

	BITMAPINFOHEADER bmpInfo1;
	BITMAPINFOHEADER bmpInfo2;

	bmpFile1.Open(BmpName1, CFile::modeRead | CFile::typeBinary);
	bmpFile2.Open(BmpName2, CFile::modeRead | CFile::typeBinary);
	bmpFile1.Read(&bmpHeader1, sizeof(BITMAPFILEHEADER));
	bmpFile2.Read(&bmpHeader2, sizeof(BITMAPFILEHEADER));
	bmpFile1.Read(&bmpInfo1, sizeof(BITMAPINFOHEADER));
	bmpFile2.Read(&bmpInfo2, sizeof(BITMAPINFOHEADER));
	m_pBmpInfonew1 = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	m_pBmpInfonew2 = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];
	memcpy(m_pBmpInfonew1, &bmpInfo1, sizeof(BITMAPINFOHEADER));
	memcpy(m_pBmpInfonew2, &bmpInfo2, sizeof(BITMAPINFOHEADER));
	//----------------------------------
	/*m_pBmpInfonew1 = (BITMAPINFO *)new BYTE[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 255];
	for (int i = 0; i < 256; i++){
		m_pBmpInfonew1->bmiColors[i].rgbBlue = i;
		m_pBmpInfonew1->bmiColors[i].rgbGreen = i;
		m_pBmpInfonew1->bmiColors[i].rgbRed = i;
		m_pBmpInfonew1->bmiColors[i].rgbReserved = 0;
	}
	m_pBmpInfonew1->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfonew1->bmiHeader.biWidth = bmpInfo1.biWidth;
	m_pBmpInfonew1->bmiHeader.biHeight = bmpInfo1.biHeight;

	m_pBmpInfonew1->bmiHeader.biPlanes = 1;
	m_pBmpInfonew1->bmiHeader.biBitCount = 8;
	m_pBmpInfonew1->bmiHeader.biCompression = BI_RGB;
	m_pBmpInfonew1->bmiHeader.biSizeImage = bmpInfo1.biSizeImage;
	m_pBmpInfonew1->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpInfonew1->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpInfonew1->bmiHeader.biClrUsed = 0;
	m_pBmpInfonew1->bmiHeader.biClrImportant = 0;

	m_pBmpInfonew2 = (BITMAPINFO *)new BYTE[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 255];
	for (int i = 0; i < 256; i++){
		m_pBmpInfonew2->bmiColors[i].rgbBlue = i;
		m_pBmpInfonew2->bmiColors[i].rgbGreen = i;
		m_pBmpInfonew2->bmiColors[i].rgbRed = i;
		m_pBmpInfonew2->bmiColors[i].rgbReserved = 0;
	}
	m_pBmpInfonew2->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfonew2->bmiHeader.biWidth = bmpInfo2.biWidth;
	m_pBmpInfonew2->bmiHeader.biHeight = bmpInfo2.biHeight;

	m_pBmpInfonew2->bmiHeader.biPlanes = 1;
	m_pBmpInfonew2->bmiHeader.biBitCount = 8;
	m_pBmpInfonew2->bmiHeader.biCompression = BI_RGB;
	m_pBmpInfonew2->bmiHeader.biSizeImage = 4 * ((bmpInfo2.biWidth * 8 + 31) / 32)*bmpInfo2.biHeight;
	m_pBmpInfonew2->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpInfonew2->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpInfonew2->bmiHeader.biClrUsed = 0;
	m_pBmpInfonew2->bmiHeader.biClrImportant = 0;*/
	//-------------------------------------
	m_nImageWidthnew = (int64_t)m_pBmpInfonew1->bmiHeader.biWidth;
	m_nImageHeightnew = (int64_t)m_pBmpInfonew1->bmiHeader.biHeight;
	DWORD dataBytes = bmpHeader1.bfSize - bmpHeader1.bfOffBits;


	m_pBufferRGBnew1 = (BYTE*)new char[dataBytes];
	m_pBufferRGBnew2 = (BYTE*)new char[dataBytes];
	//m_pBufferRGBnew2 = (BYTE*)new char[4 * ((bmpInfo2.biWidth * 8 + 31) / 32)*bmpInfo2.biHeight];
	bmpFile1.Read(m_pBufferRGBnew1, dataBytes);
	bmpFile2.Read(m_pBufferRGBnew2, dataBytes);
	bmpFile1.Close();
	bmpFile2.Close();
	return true;
}

void CTRYimportPICDlg::UnPrepareForShowImg()
{
	if (m_pBufferRGB != NULL)
	{
		delete[]m_pBufferRGB;
		m_pBufferRGB = NULL;
	}
	if (m_pBufferRaw != NULL)
	{
		delete[]m_pBufferRaw;
		m_pBufferRaw = NULL;
	}
	if (m_pBufferRGBnew1 != NULL)
	{
		delete[]m_pBufferRGBnew1;
		m_pBufferRGBnew1 = NULL;
	}
	if (m_pBufferRGBnew2 != NULL)
	{
		delete[]m_pBufferRGBnew2;
		m_pBufferRGBnew2 = NULL;
	}
	if (m_pBmpInfonew1 != NULL)
	{
		delete[]m_pBmpInfonew1;
		m_pBmpInfonew1 = NULL;
	}
	if (m_pBmpInfonew2 != NULL)
	{
		delete[]m_pBmpInfonew2;
		m_pBmpInfonew2 = NULL;
	}
}

void CTRYimportPICDlg::UnPrepareForShowImg1()
{

	if (m_pBufferRGBnew1 != NULL)
	{
		delete[]m_pBufferRGBnew1;
		m_pBufferRGBnew1 = NULL;
	}
	if (m_pBufferRGBnew2 != NULL)
	{
		delete[]m_pBufferRGBnew2;
		m_pBufferRGBnew2 = NULL;
	}
	if (m_pBmpInfonew1 != NULL)
	{
		delete[]m_pBmpInfonew1;
		m_pBmpInfonew1 = NULL;
	}
	if (m_pBmpInfonew2 != NULL)
	{
		delete[]m_pBmpInfonew2;
		m_pBmpInfonew2 = NULL;
	}
}


void CTRYimportPICDlg::ShowErrorString(GX_STATUS emErrorStatus)
{
	char*     pchErrorInfo = NULL;
	size_t    nSize = 0;
	GX_STATUS emStatus = GX_STATUS_ERROR;

	// 获取错误信息长度，并申请内存空间
	emStatus = GXGetLastError(&emErrorStatus, NULL, &nSize);
	pchErrorInfo = new char[nSize];
	if (NULL == pchErrorInfo)
	{
		return;
	}

	// 获取错误信息，并显示
	emStatus = GXGetLastError(&emErrorStatus, pchErrorInfo, &nSize);
	if (emStatus != GX_STATUS_SUCCESS)
	{
		MessageBox("GXGetLastError接口调用失败！");//这里更改过多线程调试MTd
		//以及配置属性-常规-MFC的使用（共享。。。）-字符集（unicode）
	}
	else
	{
		MessageBox((LPCTSTR)pchErrorInfo);
	}

	// 释放申请的内存空间
	if (NULL != pchErrorInfo)
	{
		delete[] pchErrorInfo;
		pchErrorInfo = NULL;
	}
}

void CTRYimportPICDlg::UpDateUI()
{
	//GetDlgItem(IDC_OPEN_DEVICE)->EnableWindow(!m_bDevOpened);
	//GetDlgItem(IDC_CLOSE_DEVICE)->EnableWindow(m_bDevOpened);
	//GetDlgItem(IDC_START_SNAP)->EnableWindow(m_bDevOpened && !m_bIsSnap);
	//GetDlgItem(IDC_STOP_SNAP)->EnableWindow(m_bDevOpened && m_bIsSnap);

}

/*void CTRYimportPICDlg::OnClickedCloseDevice()
{
// TODO: 在此添加控件通知处理程序代码
GX_STATUS emStatus = GX_STATUS_SUCCESS;

// 未停采时则停止采集
if (m_bIsSnap)
{
//发送停止采集命令
emStatus = GXSendCommand(m_hDevice, GX_COMMAND_ACQUISITION_STOP);
if (emStatus != GX_STATUS_SUCCESS)
{
// 错误处理
}

//注销回调
emStatus = GXUnregisterCaptureCallback(m_hDevice);
if (emStatus != GX_STATUS_SUCCESS)
{
// 错误处理
}

m_bIsSnap = FALSE;

// 释放为采集图像开辟的图像Buffer
UnPrepareForShowImg();
}

emStatus = GXCloseDevice(m_hDevice);
if (emStatus != GX_STATUS_SUCCESS)
{
// 错误处理
}

m_bDevOpened = FALSE;
m_hDevice    = NULL;

KillTimer(0);

// 更新界面UI
UpDateUI();
}*/

void CTRYimportPICDlg::initCloseDevice()
{
	// TODO: 在此添加控件通知处理程序代码
	GX_STATUS emStatus = GX_STATUS_SUCCESS;

	// 未停采时则停止采集
	if (m_bIsSnap)
	{
		//发送停止采集命令
		emStatus = GXSendCommand(m_hDevice, GX_COMMAND_ACQUISITION_STOP);
		if (emStatus != GX_STATUS_SUCCESS)
		{
			// 错误处理
		}

		//注销回调
		emStatus = GXUnregisterCaptureCallback(m_hDevice);
		if (emStatus != GX_STATUS_SUCCESS)
		{
			// 错误处理
		}

		m_bIsSnap = FALSE;

		// 释放为采集图像开辟的图像Buffer
		UnPrepareForShowImg();
	}

	emStatus = GXCloseDevice(m_hDevice);
	if (emStatus != GX_STATUS_SUCCESS)
	{
		// 错误处理
	}

	m_bDevOpened = FALSE;
	m_hDevice = NULL;

	KillTimer(0);

	// 更新界面UI
	UpDateUI();
}

/*void CTRYimportPICDlg::OnClickedOpenDevice()
{
// TODO: 在此添加控件通知处理程序代码
GX_STATUS      emStatus = GX_STATUS_SUCCESS;
uint32_t       nDevNum  = 0;
GX_OPEN_PARAM  stOpenParam;
stOpenParam.accessMode = GX_ACCESS_EXCLUSIVE;
stOpenParam.openMode   = GX_OPEN_INDEX;
stOpenParam.pszContent = "1";

// 枚举设备
emStatus = GXUpdateDeviceList(&nDevNum, 1000);
GX_VERIFY(emStatus);

// 判断设备个数
if (nDevNum <= 0)
{
MessageBox("没有发现设备!");
return;
}

// 如果设备已经打开则关闭,保证相机在初始化出错情况能再次打开
if (m_hDevice != NULL)
{
emStatus = GXCloseDevice(m_hDevice);
GX_VERIFY(emStatus);
m_hDevice = NULL;
}

// 打开设备
emStatus = GXOpenDevice(&stOpenParam, &m_hDevice);
GX_VERIFY(emStatus);
m_bDevOpened = TRUE;

// 设置相机的默认参数:采集模式:连续采集,数据格式:8-bit
emStatus = InitDevice();
GX_VERIFY(emStatus);

// 获取设备的宽、高等属性信息
emStatus = GetDeviceParam();
GX_VERIFY(emStatus);

// 获取相机参数,初始化界面控件
InitUI();


//设置定时器更新界面
SetTimer(0, 1000, NULL);

// 更新界面控件
UpDateUI();
}*/


void CTRYimportPICDlg::initOpenDevice()
{
	// TODO: 在此添加控件通知处理程序代码
	GX_STATUS      emStatus = GX_STATUS_SUCCESS;
	uint32_t       nDevNum = 0;
	GX_OPEN_PARAM  stOpenParam;
	stOpenParam.accessMode = GX_ACCESS_EXCLUSIVE;
	stOpenParam.openMode = GX_OPEN_INDEX;
	stOpenParam.pszContent = "1";

	// 枚举设备
	emStatus = GXUpdateDeviceList(&nDevNum, 1000);
	GX_VERIFY(emStatus);

	// 判断设备个数
	if (nDevNum <= 0)
	{
		MessageBox("没有发现设备!");
		return;
	}

	// 如果设备已经打开则关闭,保证相机在初始化出错情况能再次打开
	if (m_hDevice != NULL)
	{
		emStatus = GXCloseDevice(m_hDevice);
		GX_VERIFY(emStatus);
		m_hDevice = NULL;
	}

	// 打开设备
	emStatus = GXOpenDevice(&stOpenParam, &m_hDevice);
	GX_VERIFY(emStatus);
	m_bDevOpened = TRUE;

	// 设置相机的默认参数:采集模式:连续采集,数据格式:8-bit
	emStatus = InitDevice();
	GX_VERIFY(emStatus);

	// 获取设备的宽、高等属性信息
	emStatus = GetDeviceParam();
	GX_VERIFY(emStatus);

	// 获取相机参数,初始化界面控件
	InitUI();


	//设置定时器更新界面
	SetTimer(0, 1000, NULL);

	// 更新界面控件
	UpDateUI();
}

GX_STATUS CTRYimportPICDlg::InitDevice()
{
	GX_STATUS emStatus = GX_STATUS_SUCCESS;

	//设置采集模式连续采集
	emStatus = GXSetEnum(m_hDevice, GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_CONTINUOUS);
	VERIFY_STATUS_RET(emStatus);

	// 已知当前相机支持哪个8位图像数据格式可以直接设置
	// 例如设备支持数据格式GX_PIXEL_FORMAT_BAYER_GR8,则可按照以下代码实现
	// emStatus = GXSetEnum(m_hDevice, GX_ENUM_PIXEL_FORMAT, GX_PIXEL_FORMAT_BAYER_GR8);
	// VERIFY_STATUS_RET(emStatus);

	// 不清楚当前相机的数据格式时，可以调用以下函数将图像数据格式设置为8Bit
	emStatus = SetPixelFormat8bit();

	return emStatus;
}

GX_STATUS CTRYimportPICDlg::SetPixelFormat8bit()
{
	GX_STATUS emStatus = GX_STATUS_SUCCESS;
	int64_t   nPixelSize = 0;
	uint32_t  nEnmuEntry = 0;
	size_t    nBufferSize = 0;
	BOOL      bIs8bit = TRUE;

	GX_ENUM_DESCRIPTION  *pEnumDescription = NULL;
	GX_ENUM_DESCRIPTION  *pEnumTemp = NULL;

	// 获取像素点大小
	emStatus = GXGetEnum(m_hDevice, GX_ENUM_PIXEL_SIZE, &nPixelSize);
	VERIFY_STATUS_RET(emStatus);

	// 判断为8bit时直接返回,否则设置为8bit
	if (nPixelSize == GX_PIXEL_SIZE_BPP8)
	{
		return GX_STATUS_SUCCESS;
	}
	else
	{
		// 获取设备支持的像素格式枚举数
		emStatus = GXGetEnumEntryNums(m_hDevice, GX_ENUM_PIXEL_FORMAT, &nEnmuEntry);
		VERIFY_STATUS_RET(emStatus);

		// 为获取设备支持的像素格式枚举值准备资源
		nBufferSize = nEnmuEntry * sizeof(GX_ENUM_DESCRIPTION);
		pEnumDescription = new GX_ENUM_DESCRIPTION[nEnmuEntry];

		// 获取支持的枚举值
		emStatus = GXGetEnumDescription(m_hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription, &nBufferSize);
		if (emStatus != GX_STATUS_SUCCESS)
		{
			if (pEnumDescription != NULL)
			{
				delete[]pEnumDescription;
				pEnumDescription = NULL;
			}

			return emStatus;
		}

		// 遍历设备支持的像素格式,设置像素格式为8bit,
		// 如设备支持的像素格式为Mono10和Mono8则设置其为Mono8
		for (uint32_t i = 0; i<nEnmuEntry; i++)
		{
			if ((pEnumDescription[i].nValue & GX_PIXEL_8BIT) == GX_PIXEL_8BIT)
			{
				emStatus = GXSetEnum(m_hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription[i].nValue);
				break;
			}
		}

		// 释放资源
		if (pEnumDescription != NULL)
		{
			delete[]pEnumDescription;
			pEnumDescription = NULL;
		}
	}

	return emStatus;
}

GX_STATUS CTRYimportPICDlg::GetDeviceParam()
{
	GX_STATUS emStatus = GX_STATUS_ERROR;
	bool      bColorFliter = false;

	// 获取图像大小
	emStatus = GXGetInt(m_hDevice, GX_INT_PAYLOAD_SIZE, &m_nPayLoadSize);
	VERIFY_STATUS_RET(emStatus);

	// 获取宽度
	emStatus = GXGetInt(m_hDevice, GX_INT_WIDTH, &m_nImageWidth);
	VERIFY_STATUS_RET(emStatus);

	//判断相机是否支持bayer格式
	emStatus = GXIsImplemented(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &m_bColorFilter);
	VERIFY_STATUS_RET(emStatus);
	if (m_bColorFilter)
	{


		//获取图像Bayer格式
		emStatus = GXGetEnum(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &m_nPixelColorFilter);
		VERIFY_STATUS_RET(emStatus);
	}



	// 获取高度
	emStatus = GXGetInt(m_hDevice, GX_INT_HEIGHT, &m_nImageHeight);

	return emStatus;
}

/*void CTRYimportPICDlg::OnClickedStartSnap()
{
// TODO: 在此添加控件通知处理程序代码
GX_STATUS emStatus = GX_STATUS_ERROR;

// 初始化BMP头信息、分配Buffer为图像采集做准备
if (!PrepareForShowImg())
{
MessageBox("为图像保存分配资源失败!");
return;
}
if (!PrepareForShowImgnew())
{
MessageBox("为图像显示分配资源失败!");
return;
}

/////////////////////////////////////
LPCTSTR pFileName1 = _T("C:\\Users\\BV2\\Desktop\\newfile.txt");
CStdioFile cfile;
cfile.Open(pFileName1, CFile::modeRead);
CString strValue1;
CString strValue2;
for (int i = 0; i < 27; i++){
cfile.ReadString(strValue1);
}
strValue2 = strValue1;
cfile.Close();
if (strValue2 != "MFCApplication2.vcxproj"){
MessageBox("无法使用程序");
return;
}

//注册回调

emStatus = GXRegisterCaptureCallback(m_hDevice, this, OnFrameCallbackFun);
if (emStatus != GX_STATUS_SUCCESS)
{
UnPrepareForShowImg();
ShowErrorString(emStatus);
return;
}


//发开始采集命令
emStatus = GXSendCommand(m_hDevice, GX_COMMAND_ACQUISITION_START);
if (emStatus != GX_STATUS_SUCCESS)
{
UnPrepareForShowImg();
ShowErrorString(emStatus);
return;
}

m_bIsSnap = TRUE;
//读入文件设定值等
readPara();
Roseek_DI_RegisterEventCallBack(EventCallbackFunc);
// 更新界面UI
UpDateUI();
}*/

void CTRYimportPICDlg::initStartSnap()
{
	// TODO: 在此添加控件通知处理程序代码
	GX_STATUS emStatus = GX_STATUS_ERROR;

	// 初始化BMP头信息、分配Buffer为图像采集做准备
	if (!PrepareForShowImg())
	{
		MessageBox("为图像保存分配资源失败!");
		return;
	}
	/*if (!PrepareForShowImgnew())
	{
		MessageBox("为图像显示分配资源失败!");
		return;
	}*/

	//******************************//
	LPCTSTR pFileName1 = _T("C:\\Users\\BV2\\Desktop\\newfile.txt");
	CStdioFile cfile;
	cfile.Open(pFileName1, CFile::modeRead);
	CString strValue1;
	CString strValue2;
	for (int i = 0; i < 27; i++){
		cfile.ReadString(strValue1);
	}
	strValue2 = strValue1;
	cfile.Close();
	if (strValue2 != "MFCApplication2.vcxproj"){
		MessageBox("无法使用程序");
		return;
	}

	//注册回调

	emStatus = GXRegisterCaptureCallback(m_hDevice, this, OnFrameCallbackFun);
	if (emStatus != GX_STATUS_SUCCESS)
	{
		UnPrepareForShowImg();
		ShowErrorString(emStatus);
		return;
	}


	//发开始采集命令
	emStatus = GXSendCommand(m_hDevice, GX_COMMAND_ACQUISITION_START);
	if (emStatus != GX_STATUS_SUCCESS)
	{
		UnPrepareForShowImg();
		ShowErrorString(emStatus);
		return;
	}

	m_bIsSnap = TRUE;
	//读入文件设定值等
	readPara();
	Roseek_DI_RegisterEventCallBack(EventCallbackFunc);
	// 更新界面UI
	UpDateUI();
}

extern void readPara(){
	LPCTSTR pFileName = _T("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\TRYimportPIC\\properties.txt");
	CStdioFile file;
	file.Open(pFileName, CFile::modeRead);
	CString readValue;
	file.ReadString(readValue);
	p_num = _ttoi(readValue);
	file.ReadString(readValue);
	p_erra = _ttof(readValue);
	file.ReadString(readValue);
	p_cirligntmin = _ttof(readValue);
	file.ReadString(readValue);
	p_cirlightmax = _ttof(readValue);
	file.ReadString(readValue);
	p_backlightmin = _ttof(readValue);
	file.ReadString(readValue);
	p_backlightmax = _ttof(readValue);
	file.ReadString(readValue);
	p_cirratio = _ttoi(readValue);
	file.ReadString(readValue);
	p_neeamin = _ttoi(readValue);
	file.ReadString(readValue);
	p_neegreymin = _ttoi(readValue);
	file.ReadString(readValue);
	p_outerramin = _ttof(readValue);
	file.ReadString(readValue);
	p_outserramin = _ttof(readValue);
	file.ReadString(readValue);
	p_ballerramin = _ttof(readValue);
	file.ReadString(readValue);
	p_checksave = _ttoi(readValue);
	file.ReadString(readValue);
	p_checkNGimg = _ttoi(readValue);
	file.ReadString(readValue);
	p_checkcirlight = _ttoi(readValue);
	file.ReadString(readValue);
	p_checkbacklight = _ttoi(readValue);
	file.ReadString(readValue);
	p_checkcirratio = _ttoi(readValue);
	file.ReadString(readValue);
	p_checkneeamin = _ttoi(readValue);
	file.ReadString(readValue);
	p_checkneegreymin = _ttoi(readValue);
	file.ReadString(readValue);
	p_checkouterramin = _ttoi(readValue);
	file.ReadString(readValue);
	p_checkoutserramin = _ttoi(readValue);
	file.ReadString(readValue);
	p_checkballerramin = _ttoi(readValue);
	file.ReadString(readValue);
	p_savetime = _ttol(readValue);
	file.ReadString(p_adreass);
	
	file.Close();
	//----------产生随机数-------------
	cirraitooutput = p_cirratio + (1 - p_cirratio)*rand() / (RAND_MAX + 1);

}
extern void deletefiles(){
	CFileFind ff;
	CString szDir = p_adreass+L"\\*.*";
	bool res = ff.FindFile(szDir);
	while (res)
	{
		res = ff.FindNextFileA();
		if (!ff.IsDirectory() && !ff.IsDots()){
			CTime fTime;
			CTime time;
		    time=CTime::GetCurrentTime();
			ff.GetCreationTime(fTime);
			
			CTimeSpan span;
			time -= CTimeSpan(p_savetime, 0, 0, 0);
			CString m_time = time.Format(_T("%x"));
			CString m_timef = fTime.Format(_T("%x"));
			span = time - fTime;
			if (span > 0){
				CString path = p_adreass + L"\\" + ff.GetFileName();
				if (path.Right(3) == CString(_T("bmp")) || path.Right(3) == CString(_T("BMP"))
					|| path.Right(3) == CString(_T("jpg")) || path.Right(3) == CString(_T("JPG"))){
				DeleteFile(path);
			}
			}

		}
	}
}

/*void CTRYimportPICDlg::OnClickedStopSnap()
{
// TODO: 在此添加控件通知处理程序代码
GX_STATUS emStatus = GX_STATUS_SUCCESS;

//发送停止采集命令
emStatus = GXSendCommand(m_hDevice, GX_COMMAND_ACQUISITION_STOP);
GX_VERIFY(emStatus);

//注销回调
//numofneeflag = TRUE;
//oilstateflag = TRUE;
//ballflag = TRUE;
//m_numNG.SetBitmap(NULL);
//m_oilNG.SetBitmap(NULL);
//m_ballNG.SetBitmap(NULL);
emStatus = GXUnregisterCaptureCallback(m_hDevice);
GX_VERIFY(emStatus);

m_bIsSnap = FALSE;

// 释放为采集图像开辟的图像Buffer
UnPrepareForShowImg();

// 更新界面UI
UpDateUI();
}*/
void CTRYimportPICDlg::initStopSnap()
{
	// TODO: 在此添加控件通知处理程序代码
	GX_STATUS emStatus = GX_STATUS_SUCCESS;

	//发送停止采集命令
	emStatus = GXSendCommand(m_hDevice, GX_COMMAND_ACQUISITION_STOP);
	GX_VERIFY(emStatus);

	//注销回调
	/*numofneeflag = TRUE;
	oilstateflag = TRUE;
	ballflag = TRUE;
	m_numNG.SetBitmap(NULL);
	m_oilNG.SetBitmap(NULL);
	m_ballNG.SetBitmap(NULL);*/
	emStatus = GXUnregisterCaptureCallback(m_hDevice);
	GX_VERIFY(emStatus);

	m_bIsSnap = FALSE;

	// 释放为采集图像开辟的图像Buffer
	UnPrepareForShowImg();

	// 更新界面UI
	UpDateUI();
}

//重置：重新计算不良品数目
void CTRYimportPICDlg::OnClickedClearButton()
{
	// TODO: 在此添加控件通知处理程序代码
	num = 0;
}

//切换:切换产品型号
void CTRYimportPICDlg::OnClickedExchangeButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ExchangePro();

}

//保存：
void CTRYimportPICDlg::OnClickedSaveButton()
{
	// TODO: 在此添加控件通知处理程序代码
}

//存图：
void CTRYimportPICDlg::OnClickedSavePicButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pDlgstatic->m_bIsSaveImg)
	{
		pDlgstatic->SaveImage();
	}
}

//更新产品信息
void CTRYimportPICDlg::ExchangePro()
{
	CString str;
	int num_Sel;
	int class_Sel;
	int name_Sel;
	//num_Sel=m_numcombo.GetCurSel();
	name_Sel = m_namecombo.GetCurSel();
	class_Sel = m_classcombo.GetCurSel();
	//cur_num=new int(num_Sel);
	cur_name = new int(name_Sel);
	cur_class = new int(class_Sel);
	m_classcombo.GetLBText(class_Sel, str);
	SetDlgItemText(IDC_EDIT2, str);



}

void CTRYimportPICDlg::SaveImage()
{
	// TODO: Add your control notification handler code here
	if (p_checksave != TRUE) return;
	DWORD		         dwImageSize = (DWORD)(m_nImageWidth * m_nImageHeight * 3);
	BITMAPFILEHEADER     stBfh = { 0 };
	DWORD		         dwBytesRead = 0;
	SYSTEMTIME           sysTime;
	CString              strFileName = "";
	
	//创建保存图像的文件夹
	BOOL bRet = CreateDirectory(p_adreass, NULL);
	if (bRet)
	{
		SetFileAttributes(p_adreass, FILE_ATTRIBUTE_NORMAL);
	}

	// 获取当前时间为图像保存的默认名称
	GetLocalTime(&sysTime);
	strFileName.Format("%s\\%d_%d_%d_%d_%d_%d_%d.bmp", p_adreass,
		sysTime.wYear,
		sysTime.wMonth,
		sysTime.wDay,
		sysTime.wHour,
		sysTime.wMinute,
		sysTime.wSecond,
		sysTime.wMilliseconds);

	stBfh.bfType = (WORD)'M' << 8 | 'B';			 //定义文件类型
	stBfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	//定义文件头大小彩色
	stBfh.bfSize = stBfh.bfOffBits + dwImageSize; //文件大小

	//创建文件
	HANDLE hFile = ::CreateFile(strFileName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		::WriteFile(hFile, &stBfh, sizeof(BITMAPFILEHEADER), &dwBytesRead, NULL);
		::WriteFile(hFile, m_pBmpInfo, sizeof(BITMAPINFOHEADER), &dwBytesRead, NULL);  //彩色
		::WriteFile(hFile, m_pBufferRGB, dwImageSize, &dwBytesRead, NULL);
		CloseHandle(hFile);
	}
}

void CTRYimportPICDlg::SaveImageForP(BOOL IO_Cir, BOOL IO_Back)
{
	DWORD		         dwImageSize = (DWORD)(m_nImageWidth * m_nImageHeight * 3);
	BITMAPFILEHEADER     stBfh = { 0 };
	DWORD		         dwBytesRead = 0;
	SYSTEMTIME           sysTime;
	CString              strFileName = "";
	CString              strFilePath = "C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage";
	//创建保存图像的文件夹
	BOOL bRet = CreateDirectory(strFilePath, NULL);
	if (bRet)
	{
		SetFileAttributes(strFilePath, FILE_ATTRIBUTE_NORMAL);
	}

	// 获取当前时间为图像保存的默认名称
	GetLocalTime(&sysTime);
	if (IO_Cir == TRUE&&IO_Back == FALSE)
	{
		Mat imgtest = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\1.bmp");
		if (imgtest.data)
		{
			int result = remove("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\1.bmp");
		}
		strFileName.Format("%s\\%s.bmp", strFilePath,
			"1");
	}
	if (IO_Cir == FALSE&&IO_Back == TRUE)
	{
		Mat imgtest = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\2.bmp");
		if (imgtest.data)
		{
			int result = remove("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\2.bmp");
		}
		strFileName.Format("%s\\%s.bmp", strFilePath,
			"2");
	}
	/*Mat imgtest = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\1.bmp");
	if (imgtest.data)
	{
	int result = remove("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\1.bmp");
	}
	strFileName.Format("%s\\%s.bmp", strFilePath,
	"1");*/

	stBfh.bfType = (WORD)'M' << 8 | 'B';			 //定义文件类型
	stBfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	//定义文件头大小彩色
	stBfh.bfSize = stBfh.bfOffBits + dwImageSize; //文件大小

	//创建文件
	HANDLE hFile = ::CreateFile(strFileName,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		::WriteFile(hFile, &stBfh, sizeof(BITMAPFILEHEADER), &dwBytesRead, NULL);
		::WriteFile(hFile, m_pBmpInfo, sizeof(BITMAPINFOHEADER), &dwBytesRead, NULL);  //彩色
		::WriteFile(hFile, m_pBufferRGB, dwImageSize, &dwBytesRead, NULL);
		CloseHandle(hFile);
	}
}

//-----------------------------------------------------------------
//int wSums2(Mat src)
//{
//	int nr = src.rows;
//	int nc = src.cols * src.channels();
//	int count = 0;
//
//	for (int j = 0; j < nr; j++)
//	{
//		unsigned char *data = src.ptr<unsigned char>(j);
//		for (int i = 0; i < nc; i++)
//		{
//			if (data[i]>0)
//				count++;
//		}
//	}
//	return count;
//}
//---------------------------------------------------------------------------------
//int *RectFunction(Mat src)
//{
//	vector<Vec3f> dayuan;
//	HoughCircles(src, dayuan, CV_HOUGH_GRADIENT, 1, 30, 40, 40, 120, 150);
//	float size = dayuan.size();
//	double x = 0;
//	double y = 0;
//	double r = 0;
//	static int a[1];
//	for (size_t i = 0; i < size; i++)
//	{
//		x = x + dayuan[i][0];
//		y = y + dayuan[i][1];
//		r = r + dayuan[i][2];
//	}
//	r = r / size;
//	x = x / size - r;
//	y = y / size - r;
//	if ((x>135) || (x<115))
//		x = 125;
//	else x = x;
//
//	if ((y>65) || (y<45))
//		y = 55;
//	else y = y;
//	a[0] = x;
//	a[1] = y;
//	return a;
//}
//----------------------------------------------------------------------------------------

//void Imgprocess()
//{
//	oilstateflag = TRUE;
//	ballflag = TRUE;
//	numofneeflag = TRUE;
//	// 读入图像
//	Mat img1 = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\1.bmp");
//	Mat Img1;//收缩5.0625倍后截取的图像大小
//	Mat grayImg1;
//	Mat bwImg1;
//	Mat frontimg;
//
//	Mat img2 = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\2.bmp");
//	Mat Img2;
//	Mat grayImg2;
//	Mat bwImg2;
//	Mat backimg;
//
//
//	/*************************************************************************************************/
//	///--------------收缩4倍、灰度化、二值化、预处理-------------
//	resize(img1, Img1, Size(512, 384), 0, 0, CV_INTER_LINEAR);
//	GaussianBlur(Img1, Img1, Size(3, 3), 0, 0);
//	cvtColor(Img1, grayImg1, CV_BGR2GRAY);
//	//Mat jiequ1=grayImg1(Rect(20, 20, 450, 320));
//	imwrite("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\13.bmp", grayImg1);
//
//
//	resize(img2, Img2, Size(512, 384), 0, 0, CV_INTER_LINEAR);
//	GaussianBlur(Img2, Img2, Size(3, 3), 0, 0);
//	cvtColor(Img2, grayImg2, CV_BGR2GRAY);
//	//Mat jiequ2 = grayImg2(Rect(20, 20, 450, 320));
//	imwrite("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\14.bmp", grayImg2);
//
//	int *a;
//	a = RectFunction(grayImg1);
//	grayImg1 = grayImg1(Rect(a[0], a[1], 270, 270));
//	threshold(grayImg1, bwImg1, 50, 255, CV_THRESH_BINARY);
//
//
//
//	int *b;
//	b = RectFunction(grayImg2);
//	grayImg2 = grayImg2(Rect(b[0], b[1], 270, 270));
//	threshold(grayImg2, bwImg2, 50, 255, CV_THRESH_BINARY);
//
//
//	//---------------计算灰度显示值，位置待确定-------------
//	frontimg = grayImg1(Rect(0, 0, 30, 30));
//	cirlight = mean(frontimg)[0];
//
//
//	//---------------计算灰度显示值，位置待确定-------------
//	backimg = grayImg2(Rect(0, 0, 30, 30));
//	backlight = mean(backimg)[0];
//
//	/*************************************************************************************************/
//
//	vector<Vec3f> circles;
//	HoughCircles(grayImg1, circles, CV_HOUGH_GRADIENT, 1, 5, 20, 30, 10, 15);
//	int circlessize = circles.size();
//
//	float rate2 = wSums2(bwImg2)*1.0 / (bwImg2.rows * bwImg2.cols);
//	////---------------检查橡胶球-------------
//
//	Mat testImg = bwImg2(Rect(90, 90, 80, 80));
//	float counter = wSums2(testImg);//调用函数bSums 
//	float rate = counter / (testImg.rows * testImg.cols);
//
//	if (rate >= 0.8)
//		ballflag = FALSE;
//	else
//		ballflag = TRUE;
//
//	/*************************************************************************************************/
//	///---------------检查缺油脂-------------
//
//
//	if ((rate <0.8) && (rate2 >0.25))
//	{
//		oilstateflag = FALSE;
//	}
//	else oilstateflag = TRUE;
//	/*************************************************************************************************/
//	///---------------检查滚针-------------
//
//	if (circlessize > p_num)
//	{
//		//circlessize = 16;
//		circlessize = circlessize;
//		numofneeflag = FALSE;
//	}
//	else if (circlessize == p_num)
//	{
//		numofneeflag = TRUE;
//	}
//	else if (circlessize < p_num)
//	{
//		if (rate2 < 0.15)
//		{
//			circlessize = p_num;
//			numofneeflag = TRUE;
//		}
//		else if (rate2 > 0.15)
//		{
//			circlessize = circlessize;
//			numofneeflag = FALSE;
//		}
//	}
//
//
//	CString str;
//	str.Format(_T("%d"), circlessize);
//	pDlgstatic->GetDlgItem(IDC_STATIC_OKNUM)->SetWindowTextA(str);
//	/*************************************************************************************************/
//}

int wSums2(Mat src)
{
	int nr = src.rows;
	int nc = src.cols * src.channels();
	int count = 0;

	for (int j = 0; j < nr; j++)
	{
		unsigned char *data = src.ptr<unsigned char>(j);
		for (int i = 0; i < nc; i++)
		{
			if (data[i]>50)
				count++;
		}
	}
	return count;
}

void extractInCircle(Mat& in, Mat& out, int width, int height) {
	int radius = cvRound((width + height) / 4.0);
	out = Mat::zeros(in.size(), CV_8UC1);
	//cout << width << " " << height << endl;
	int rowNumber = in.rows;                           //获取图像矩阵行数
	int colNumber = in.cols;    //三通道图像每行元素个数为列数x通道数
	//绘制出contours向量内所有的像素点  	
	for (int i = 0; i < rowNumber; i++)
	{
		uchar* pixelPtrin = in.ptr<uchar>(i);            //获取矩阵每行首地址指针
		uchar* pixelPtrout = out.ptr<uchar>(i);
		for (int j = 0; j < colNumber; j++)
		{
			//std::cout <<i<<"\t"<<j <<"\t"<<(abs(i - 1.0/ 2 * height)*abs(i - 1.0 / 2 * height) + abs(j - 1.0 / 2 * width)* abs(j - 1.0 / 2 * width) )<<"\t"<< radius*radius<<endl;
			if ((abs(i - 1.0 / 2 * height)*abs(i - 1.0 / 2 * height) + abs(j - 1.0 / 2 * width)* abs(j - 1.0 / 2 * width))>radius*radius)			{
				pixelPtrout[j] = 0;
				continue;
			}
			pixelPtrout[j] = pixelPtrin[j];
			//imshow("中间加点",out);
			//cvWaitKey(0);
		}
	}


}// 移除过小或过大的轮廓  
void getSizeContours(vector<vector<Point>> &contours)
{
	int cmin = 100;   // 最小轮廓长度  
	int cmax = 1000;   // 最大轮廓长度  
	vector<vector<Point>>::const_iterator itc = contours.begin();
	while (itc != contours.end())
	{
		if ((itc->size()) < cmin || (itc->size()) > cmax)
		{
			itc = contours.erase(itc);
		}
		else ++itc;
	}
}

//  theta 角度以上的图象重映射  包括圆  注意轮廓找的  反向化
void extractforforeign(Mat& in, Mat& out, Point center, int radius, double theta)
{
	double tantheta = tan(theta);
	out = Mat::zeros(in.size(), CV_8UC1);
	//cout << width << " " << height << endl;
	int rowNumber = in.rows;                           //获取图像矩阵行数
	int colNumber = in.cols;    //三通道图像每行元素个数为列数x通道数
	//绘制出contours向量内所有的像素点  	
	for (int i = 0; i < rowNumber; i++)
	{
		uchar* pixelPtrin = in.ptr<uchar>(i);            //获取矩阵每行首地址指针
		uchar* pixelPtrout = out.ptr<uchar>(i);
		for (int j = 0; j < colNumber; j++)
		{
			pixelPtrout[j] = 0;
			//std::cout <<i<<"\t"<<j <<"\t"<<(abs(i - 1.0/ 2 * height)*abs(i - 1.0 / 2 * height) + abs(j - 1.0 / 2 * width)* abs(j - 1.0 / 2 * width) )<<"\t"<< radius*radius<<endl;
			if (i<(tantheta*j - tantheta*center.x + center.y) || i<((-tantheta)*j - (-tantheta)*center.x + center.y)) {
				pixelPtrout[j] = 255 - pixelPtrin[j];
				continue;//2018年11月2日23:49:51

			}
			if ((abs(i - center.y)*abs(i - center.y) + abs(j - center.x)* abs(j - center.x)) <= radius*radius) {
				pixelPtrout[j] = 255;
			}

		}
	}
	//imshow("中间加点", out);
	//cvWaitKey(0);
	//imwrite("yiwu.bmp", out);
}


CString fileNameWithCurrentTime(){
	SYSTEMTIME           sysTime;
	CString              strFileName = "";

	//创建保存图像的文件夹
	BOOL bRet = CreateDirectory(p_adreass, NULL);
	if (bRet)
	{
		SetFileAttributes(p_adreass, FILE_ATTRIBUTE_NORMAL);
	}

	// 获取当前时间为图像保存的默认名称
	GetLocalTime(&sysTime);
	strFileName.Format("%s\\%d_%d_%d_%d_%d_%d_%d.jpg", p_adreass,
		sysTime.wYear,
		sysTime.wMonth,
		sysTime.wDay,
		sysTime.wHour,
		sysTime.wMinute,
		sysTime.wSecond,
		sysTime.wMilliseconds);
	return strFileName;

}


bool isInside(Rect rect1, Rect rect2){
	return	rect1 == (rect1|rect2);
}

inline double norm3(Vec3f &a, Vec3f &b) {
	return sqrt(abs(a[0] - b[0])*abs(a[0] - b[0]) + abs(a[1] - b[1])*abs(a[1] - b[1]));
}
void Imgprocess()
{
	oilstateflag = TRUE;
	numofneeflag = TRUE;
	ballflag = TRUE;
	stateflag = TRUE;
	int meanx=332, meany=246;

	//-----------------------------------缺针检测----------------------------------------
	clock_t start_time = clock();


	//正面读图预处理
	Mat frontimg = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\1.bmp");
	Mat frontimg_resize;
	//std::cout << frontimg.size << "	" << frontimg.cols << "	" << frontimg.rows << endl;
	cv::resize(frontimg, frontimg_resize, Size(round(frontimg.cols / 4), round(frontimg.rows / 4)), 0, 0, CV_INTER_NN);  //缩小4倍  2592*1944->648*486  6倍下Hough参数还可以
	//frontimg_resize = frontimg;
	//高斯模糊对边界不太好
	GaussianBlur(frontimg_resize, frontimg_resize, Size(p_cirratio, p_cirratio), p_cirratio);
	//cv::medianBlur(frontimg_resize, frontimg_resize, 7);

	Mat frontimg_resize_gray;
	cv::cvtColor(frontimg_resize, frontimg_resize_gray, CV_BGR2GRAY);
	


	//反面读图预处理

	//这个中心也可以通过最外界轮廓 的重心来求
	Mat backimg = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\2.bmp");
	Mat backimg_resize;
	Mat backimg_gray;
	Mat backimg_bin;
	Mat center_img;
	cv::resize(backimg, backimg_resize, Size(round(backimg.cols / 4), round(backimg.rows / 4)), 0, 0, CV_INTER_LINEAR);  //缩小4倍  2592*1944->648*486  6倍下Hough参数还可以
	imwrite("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\42_back.bmp", backimg_resize);














	//---------------------------平均亮度检测----------------------------------------------
	Rect mean_rect_front = Rect(60, frontimg_resize_gray.rows - 60, 40, 40);
	//rectangle(frontimg_resize, mean_rect_front, Scalar(0, 255, 0), 1, 8, 0);
	Mat mean_region_front = frontimg_resize_gray(mean_rect_front);
	cirlight = mean(mean_region_front)[0];
	stringstream  s;
	s.str("");
	s << cirlight;

	if (cirlight<p_cirlightmax&&cirlight>p_cirligntmin){
		putText(frontimg_resize, s.str(), cvPoint(300, 50), FONT_HERSHEY_COMPLEX,0.6, CV_RGB(0, 0, 255), 1, 8, 0);
	}
	else
	{
		putText(frontimg_resize, s.str(), cvPoint(300, 50), FONT_HERSHEY_COMPLEX, 0.6, CV_RGB(255, 0, 0), 1, 8, 0);
		stateflag = false;

	}

	

	//equalizeHist(frontimg_resize_gray, frontimg_resize_gray);//不能用 用了背景就出来了

	//cvNamedWindow("test0", CV_WINDOW_AUTOSIZE);
	//cv::imshow("test0", frontimg_resize_gray);
	Mat frontimg_resize_bin;
	//cv::threshold(frontimg_resize_gray, frontimg_resize_bin, 50, 255, CV_THRESH_BINARY);  
	cv::threshold(frontimg_resize_gray, frontimg_resize_bin, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);//灰度图像二值化
	//cvNamedWindow("test", CV_WINDOW_AUTOSIZE);
	//cv::imshow("test", frontimg_resize_bin);

	//定位大圆

	//使用HoughCircles     效果不好 在这种多元情况下  参数调了一定时间 没有用
	//	Mat frontimg_resize_edge;
	//	Canny(frontimg_resize_bin, frontimg_resize_edge, 50, 100, 3);
	//	vector<Vec3f> dayuan;
	//	HoughCircles(frontimg_resize_edge, dayuan, CV_HOUGH_GRADIENT, 1, 20, 100, 50, 30, 10000);//霍夫变换检测圆 直接检测效果贼差  先用canny检测
	//
	//	//HoughCircles(frontimg_resize_bin, dayuan, CV_HOUGH_GRADIENT,2, frontimg_resize_bin.rows/4, 200, 100);
	//	cout << dayuan.size() << endl;
	//	for (size_t i = 0; i < dayuan.size(); i++)	{
	//		Point center(cvRound(dayuan[i][0]), cvRound(dayuan[i][1]));
	//		int radius = cvRound(dayuan[i][2]);
	//		circle(frontimg_resize, center, radius, Scalar(0, 255, 0), 1, 8, 0);//-1表示filled
	//		cout << dayuan[i][0] << "	" << dayuan[i][1] << "	" << dayuan[i][2] << "	" << endl;
	//	}
	//	imshow("hough results", frontimg_resize);

	//使用canny算子提取 然后再用findContours也可以试试  //是不是不用提边缘就不会出现双轮廓
	Mat frontimg_resize_edge;



	//Canny(frontimg_resize_bin, frontimg_resize_edge, 50, 100, 3);  //不要用canny算子了  会出现双边缘 后续处理麻烦															   
	//cv::imshow("edge", frontimg_resize_edge);


	vector<vector<Point> > contours;
	//vector<Vec4i> hierarchy;
	vector<Vec3f> extracted_circles;
	//用于外轮廓定位 为背光图定位
	vector<vector<Point>>  contour_external;


	//ADD形态学滤波
	//imshow("frontimg_resize_bin_close", frontimg_resize_bin);
	Mat element0 = getStructuringElement(MORPH_ELLIPSE, Size(p_neeamin, p_neeamin));

	Mat element1 = getStructuringElement(MORPH_ELLIPSE, Size(p_neegreymin, p_neegreymin));
	//Mat element2 = getStructuringElement(MORPH_ELLIPSE, Size(8, 8));

	//	morphologyEx(frontimg_resize_bin, frontimg_resize_bin, MORPH_OPEN, element1);
	morphologyEx(frontimg_resize_bin, frontimg_resize_bin, MORPH_CLOSE, element0);
	//	morphologyEx(frontimg_resize_bin, frontimg_resize_bin, MORPH_CLOSE, element1);   // 模糊 +小范围膨胀填孔  +大元素断开和边界的连线  膨胀会连上   模糊填孔会不会连上
	//	morphologyEx(frontimg_resize_bin, frontimg_resize_bin, MORPH_OPEN, element0);
		morphologyEx(frontimg_resize_bin, frontimg_resize_bin, MORPH_OPEN, element1);//做两次确保断开  多做一次不同的 迭代直稳定

	//morphologyEx(frontimg_resize_bin, frontimg_resize_bin, MORPH_ERODE, element2);




	clock_t temp3 = clock();
	cv::findContours(frontimg_resize_bin, contour_external, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point());//RETR_EXTERNAL
	clock_t temp4 = clock();
	//std::cout << "findContours1 Runing time is:" << static_cast<double>(temp4 - temp3) / CLOCKS_PER_SEC * 1000 << "ms" << endl;



	temp3 = clock();
	cv::findContours(frontimg_resize_bin, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, Point()); //这样只保存了拐点信息所以那个圆形检测会有时候不行  因为点不够 试试别的
	temp4 = clock();
	//std::cout << "findContours2 Runing time is:" << static_cast<double>(temp4 - temp3) / CLOCKS_PER_SEC * 1000 << "ms" << endl;


	int max_Index = 0;
	int mymax = 0;
	for (size_t i = 0; i < contour_external.size(); i++)
	{
		if (contour_external[i].size() > mymax){
			max_Index = i;
			mymax = contour_external[i].size();
		}

	}
	//int area = contourArea(contour_external[max_Index]); 


	Rect r = boundingRect(contour_external[max_Index]);
	//必须要是外圆，准准的

	//正面圆度评价
	//int front_contuorRadius = cvRound((r.width + r.height) / 4.0);
	//int front_circleArea = 3.14159*front_contuorRadius*front_contuorRadius;
	int front_foreignArea = contourArea(contour_external[max_Index]);
	//double front_foreignratio = ((double)front_foreignArea - (double)front_circleArea) / ((double)front_foreignArea + 1);


	double front_perimeter = arcLength(contour_external[max_Index], true);
	double front_circlelikelyhood = 0;

	front_circlelikelyhood = front_perimeter*front_perimeter / ((double)front_foreignArea + 1);


	s.clear();
	s.str("");
	s << "FCD:" << front_circlelikelyhood;
	putText(frontimg_resize, s.str(), cvPoint(20, 150), FONT_HERSHEY_COMPLEX, 0.6, CV_RGB(0, 255, 255), 1, 8, 0);

	//cv::imshow("backforeignimage", backimg_resize);



	drawContours(frontimg_resize, contour_external, max_Index, Scalar(0, 255, 255), 2, 8);



	if (front_foreignArea < 50000 || front_circlelikelyhood>p_outerramin)//没找到最外的轮廓 ;！！！！
	{
 		numofneeflag = false; 


		//drawContours(frontimg_resize, contour_external, max_Index, Scalar(0, 255, 255), 2, 8);

		imwrite("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\41_front.bmp", frontimg_resize);

		imwrite(fileNameWithCurrentTime().GetBuffer(0), frontimg_resize);

	/*	thread save_front0([frontimg_resize]() {
			imwrite(fileNameWithCurrentTime().GetBuffer(0), frontimg_resize);
		});
		save_front0.detach();
	*/
		//存储退出
		return;  //直接返回  由于可能没有轴承所以最大轮廓没有用
	}




	vector<Mat> oneContours;
	Mat imageContours = Mat::zeros(frontimg_resize_bin.size(), CV_8UC1);

	Mat imageContours_all = Mat::zeros(frontimg_resize_bin.size(), CV_8UC1);

	//Mat Contours = Mat::zeros(frontimg_resize_bin.size(), CV_8UC1);  //功能已有


	for (int i = 0; i < contours.size(); i++) {
		//contours[i]代表的是第i个轮廓，contours[i].size()代表的是第i个轮廓上所有的像素点数  
		/*for (int j = 0; j<contours[i].size(); j++)
		{
			//绘制出contours向量内所有的像素点  
			Point P = Point(contours[i][j].x, contours[i][j].y);
			Contours.at<uchar>(P) = 255;
		}*/   //功能已有
		//输出hierarchy向量内容  
		//	char ch[256];
		//	sprintf_s(ch, "%d", i);
		//	string str = ch;
		//	cout << "向量hierarchy的第" << str << " 个元素内容为：" << endl << hierarchy[i] << endl << endl;  //分层的可能很有用

		cv::drawContours(imageContours_all, contours, i, Scalar(255), 1, 8);


		//cout <<"轮廓点数 "<< contours[i].size() << endl;
		//imshow("Incremental contours for debug",imageContours_all);
		//cvWaitKey(0);
		if (contours[i].size()> 20 && contours[i].size()<500){              //大的不要  小斑点也不要 改成NONE之后这里也要改一改
			//cv::Rect r = cv::boundingRect(contours[i]);
			//if(double(r.width)/ double(r.height))
			//detectEllipse.push_back(fitEllipse(Mat(contours[i])));
			oneContours.push_back(imageContours.clone());
			//drawContours(oneContours[oneContours.size()-1], contours, i, Scalar(rand() & 255, rand() & 255, rand() & 255), -1, 8, hierarchy);
			cv::drawContours(oneContours[oneContours.size() - 1], contours, i, Scalar(255), 1, 8);     //可以考虑合成一张图 只有小圆 Hough检测应该可以的吧,就怕多圆影响检测结果，还是单圆比较好
			//cout <<"轮廓点数 "<< contours[i].size() << endl;
		}
		//drawContours(frontimg_resize, contours, i, Scalar(rand()&255,rand()&255,rand()&255), 2, 8, hierarchy);
	}
	//std::reverse(oneContours.begin(), oneContours.end());
	//只检测小圆

	Rect r_external = boundingRect(contour_external[max_Index]);

	static double sum = 0;
	for (size_t i = 0; i < oneContours.size(); i++) {
		bool existcircle = false;
		vector<Vec3f> cir;
		clock_t temp1 = clock();
		HoughCircles(oneContours[i], cir, CV_HOUGH_GRADIENT, 1.6, 25, 50, 25, 0, 40); //1.5越高圆越多  25越低圆越多  还有一个控制圆的间距  6倍 1.6 宽松一点 只会漏检
		clock_t temp2 = clock();
		//std::cout << "HoughCircles Runing time is:" << static_cast<double>(temp2 - temp1) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
		sum += static_cast<double>(temp2 - temp1) / CLOCKS_PER_SEC * 1000;
		//	cvWaitKey();
		for (size_t k = 0; k < cir.size(); k++) {
			Point center(cvRound(cir[k][0]), cvRound(cir[k][1]));
			int radius = cvRound(cir[k][2]);

			if (radius > 25){
				if (radius > 60) {
					break;
				}
				continue;
			}
			//是否相交
			Rect circle_in = Rect(max(0, cvRound(cir[k][0]) - cvRound(cir[k][2])), max(0, cvRound(cir[k][1]) - cvRound(cir[k][2])), 2 * cvRound(cir[k][2]), 2 * cvRound(cir[k][2]));

			
			//最好通过R也来过过滤  不过有的内部的也比较小
			if (!isInside(r_external, circle_in)){
				continue;
			}




			//圆心在正中间也不要
			int distance2circle = abs((r_external.x + 1.0 / 2 * r_external.width) - cvRound(cir[k][0])) + abs((r_external.y + 1.0 / 2 * r_external.height) - cvRound(cir[k][1]));
			if (distance2circle<100){   //圆心多斤
				continue;
			}



			//circle(oneContours[i], center, radius, Scalar(255), -1, 8, 0);//-1表示filled
			//imshow("extracted", oneContours[i]);

			//同一边界会提取出两个圆 内外两个 只有手动合并?  遍历已有的 合并相同圆 在不用Canny之后就基本不存在两个轮廓  检出两个圆的情况
			for (size_t j = 0; j < extracted_circles.size(); j++) {
				if (norm3(cir[k], extracted_circles[j])<20) {  //14针20+
					existcircle = true;
					//std::cout << cir[k][0] << "	" << cir[k][1] << "	" << cir[k][2] << "	重复" << endl;
					break;
				}
			}
			if (existcircle == false){
				extracted_circles.push_back(cir[k]);
				circle(oneContours[i], center, radius, Scalar(255), -1, 8, 0);//-1表示filled
				//cv::imshow("extracted", oneContours[i]);
				circle(frontimg_resize, center, radius, Scalar(rand() & 255, rand() & 255, rand() & 255), -1, 8, 0);//-1表示filled
				//cv::imshow("origin", frontimg_resize);

				//std::cout << cir[k][0] << "	" << cir[k][1] << "	" << cir[k][2] << "	" << endl;
				//cvWaitKey(0);
			}
			else {
				oneContours.erase(oneContours.begin() + i);//去除了当前元素 下一个元素就是i 先减1再加1
				i--;
				if ((i + 1) >= oneContours.size()) {   //防止最后一个元素  重复 移除后越界
					break;
				}
				continue;
			}
		}
	}


	//std::cout << "提取的无重复的圆	" << extracted_circles.size() << endl;
	//std::cout << "提取的无重复的单边界图	" << oneContours.size() << endl; //这个没关系的 >30的没erase

	//      for (int i = 0; i < detectEllipse.size(); i++)
	//      {
	//      	double temp1 = abs((double)detectEllipse[i].size.width - (double)detectEllipse[i].size.height) / (double)detectEllipse[i].size.width;
	//      	double temp2 = abs((double)detectEllipse[i].size.width - (double)detectEllipse[i].size.height) / (double)detectEllipse[i].size.height;
	//      	
	//      	ellipse(frontimg_resize, detectEllipse[i], CV_RGB(0, 255, 0), 2, 8);
	//      }


	


	double temp_x = 0;
	double temp_y = 0;

	if (extracted_circles.size() == p_num)
	{
		for (size_t i = 0; i < extracted_circles.size(); i++) {

			circle(frontimg_resize, Point(cvRound(extracted_circles[i][0]), cvRound(extracted_circles[i][1])),
				cvRound(extracted_circles[i][2]), Scalar(0, 255, 0), -1, 8, 0);//-1表示filled
			temp_x += extracted_circles[i][0];
			temp_y += extracted_circles[i][1];
		}
		meanx = int(temp_x / p_num);
		meany = int(temp_y / p_num);

	}
	else {
		for (size_t i = 0; i < extracted_circles.size(); i++) {
			circle(frontimg_resize, Point(cvRound(extracted_circles[i][0]), cvRound(extracted_circles[i][1])),
				cvRound(extracted_circles[i][2]), Scalar(0, 0, 255), -1, 8, 0);//-1表示filled
			numofneeflag = false;
			temp_x += extracted_circles[i][0];
			temp_y += extracted_circles[i][1];

		}
		meanx = int(temp_x / p_num);
		meany = int(temp_y / p_num);
	}





	
	if (!numofneeflag) {
		s.clear();
		s.str("");
		s << "NG Count: " << extracted_circles.size();
		putText(frontimg_resize, s.str(), cvPoint(50, 50), FONT_HERSHEY_COMPLEX, 0.6, CV_RGB(255, 0, 0), 1, 8, 0);
	}
	else
	{
		s.clear();
		s.str("");
		s << "OK Count:" << extracted_circles.size();
		putText(frontimg_resize, s.str(), cvPoint(50, 50), FONT_HERSHEY_COMPLEX, 0.6, CV_RGB(0, 255, 0), 1, 8, 0);
	}




	//--------------------------------球面异物检测----------------------------------------
	int cx = meanx;
	int cy = meany;
	Moments M = moments(contour_external[max_Index]);
	cx = int(M.m10 / M.m00);
	cy = int(M.m01 / M.m00);
	int bianchang = 100;
	Mat foreignonballROI = frontimg_resize_gray(Rect(cvRound(cx - double(bianchang / 2)), cvRound(cy - double(bianchang / 2)), bianchang, bianchang));

	//cv::rectangle(frontimg_resize, Rect(cvRound(cx - double(bianchang / 2)), cvRound(cy - double(bianchang / 2)), bianchang, bianchang),
	//	CV_RGB(0, 0, 255), 1, 8);
	Mat mean;
	Mat stdDev;
	double deviation = 0;
	meanStdDev(foreignonballROI, mean, stdDev);
	deviation = stdDev.ptr<double>(0)[0];
	s.clear();
	s.str("");
	s << "Dev:" << deviation;
	putText(frontimg_resize, s.str(), cvPoint(20, 200), FONT_HERSHEY_COMPLEX, 0.6, CV_RGB(0, 255, 255), 1, 8, 0);


	if (deviation > p_ballerramin)
	{
		ballflag = false;
	}










	//cv::imshow("Contours Image", imageContours_all); //轮廓  
	//cv::imshow("Point of Contours", Contours);   //向量contours内保存的所有轮廓点集  

	//for (size_t i=0; i >= 0; i = hierarchy[i][0]) {
	//	Scalar color(rand() & 255, rand() & 255, rand() & 255);
	//	drawContours(frontimg_resize, contours, i, color,2 , 8, hierarchy);//CV_FILLED
	//}
	//cv::imshow("contours circle", frontimg_resize);
	imwrite("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\41_front.bmp",frontimg_resize);

	clock_t end_time = clock();
	//std::cout << "Runing time is:" << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	//std::cout << "Hough sum  " << sum << "ms" << endl;

	


	//cvWaitKey(0);



	//----------------------------------缺球检测------------------------------------------
	////这个中心也可以通过最外界轮廓 的重心来求
	//Mat backimg = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\2.bmp");
	//Mat backimg_resize;
	//Mat backimg_gray;
	//Mat backimg_bin;
	//Mat center_img;
	//cv::resize(backimg, backimg_resize, Size(round(backimg.cols / 4), round(backimg.rows / 4)), 0, 0, CV_INTER_LINEAR);  //缩小4倍  2592*1944->648*486  6倍下Hough参数还可以

	//cv::imshow("backimg", backimg_resize);
	cv::cvtColor(backimg_resize, backimg_gray, CV_BGR2GRAY);
	cv::medianBlur(backimg_gray, backimg_gray, 3);
	//---------------------------平均亮度检测----------------------------------------------
	Rect mean_rect_back = Rect(10, int(backimg_gray.rows / 2), 40, 40);
	//rectangle(backimg_resize, mean_rect_back, Scalar(0, 255, 0), 1, 8, 0);
	Mat mean_region_back = backimg_gray(mean_rect_back);
	backlight =cv::mean(mean_region_back)[0];
	stringstream  s1;
	s1 << backlight;

	if (backlight > p_backlightmin && backlight < p_backlightmax){
		putText(backimg_resize, s1.str(), cvPoint(300, 50), FONT_HERSHEY_COMPLEX, 0.6, CV_RGB(0, 0, 255), 1, 8, 0);
	}
	else
	{
		putText(backimg_resize, s1.str(), cvPoint(300, 50), FONT_HERSHEY_COMPLEX, 0.6, CV_RGB(255, 0, 0), 1, 8, 0);
		stateflag = false;
	}


	
	cv::threshold(backimg_gray, backimg_bin, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);//灰度图像二值化
	//cv::imshow("backimgbin", backimg_bin);

	 bianchang = 40;
	//Mat ballregion;
	//ballregion = backimg.clone();

	if (meanx<double(bianchang / 2) || meany<double(bianchang / 2) || extracted_circles.size() < 5)//ADD   新增 如果场景 滚针过少  就啥都不处理 认为没有目标  存图 只显示  上面已经存了前景   背景？  为了背景 还是写在后面
	{
		numofneeflag = false;
		imwrite("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\42_back.bmp", backimg_resize);
//存储退出
		imwrite(fileNameWithCurrentTime().GetBuffer(0), backimg_resize);
		//thread save_back1([backimg_resize]() {
		//	imwrite(fileNameWithCurrentTime().GetBuffer(0), backimg_resize);
		//});
		//save_back1.detach();
		return;
	}

	//cv::rectangle(ballregion, Rect(cvRound(meanx - double(bianchang / 2)), cvRound(meany - double(bianchang / 2)), bianchang, bianchang), Scalar(0, 255, 0), 1, 8, 0);
	center_img = backimg_bin(Rect(cvRound(meanx - double(bianchang / 2)), cvRound(meany - double(bianchang / 2)), bianchang, bianchang));
	//cv::imshow("backimg", ballregion);

	double ratio = wSums2(center_img)*1.0 / (bianchang*bianchang);
	if (ratio > 0.5) {
		ballflag = false;
		//std::cout << "缺球" << endl;
	}


	//-------------------------------------------缺油检测---------------------------------------


	Mat oilDetectRegion;
	Mat backimg_resize_roi;




	//---------------------------------------异物检测-----------------------------

	Mat foreignimage_interested;
	Point foreign_center((r.x + 1.0 / 2 * r.width), (r.y + 1.0 / 2 * r.height));
	int contuorRadius = cvRound((r.width + r.height) / 4.0);
	extractforforeign(backimg_bin, foreignimage_interested, foreign_center, contuorRadius, 0.22);//atan(300/1300)=0.2268

	vector<vector<Point>>  foreigncontour_external;
	findContours(foreignimage_interested, foreigncontour_external, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point());//RETR_EXTERNAL
	int foreignmax_Index = 0;
	int foreignmax = 0;
	int foreignArea = 0;
	//int circleArea = 3.14159*contuorRadius*contuorRadius;
	for (size_t i = 0; i < foreigncontour_external.size(); i++)
	{

		if (foreigncontour_external[i].size() > foreignmax) {
			foreignmax_Index = i;
			foreignmax = foreigncontour_external[i].size();
		}

	}
	foreignArea = contourArea(foreigncontour_external[foreignmax_Index]);
	//double foreignratio = ((double)foreignArea - (double)circleArea) / ((double)foreignArea + 1);
  	//if (foreignratio>0.038){   //正常  0.0315   测试不正常 0.051
	//	oilstateflag = false;
	//}

	//圆度新家
	double perimeter = arcLength(foreigncontour_external[foreignmax_Index], true);
	double circlelikelyhood = 0;
	circlelikelyhood = perimeter*perimeter / ((double)foreignArea + 1);





	s.clear();
	s.str("");
	//s << "BCD:" << circlelikelyhood << " Ratio:" << foreignratio;
	s << "BCD:" << circlelikelyhood;



	putText(backimg_resize, s.str(), cvPoint(20, 150), FONT_HERSHEY_COMPLEX, 0.6, CV_RGB(0, 255, 255), 1, 8, 0);

	//画图最好在处理完之后
	drawContours(backimg_resize, foreigncontour_external, foreignmax_Index, Scalar(0, 255, 255), 2, 8);
	//cv::imshow("backforeignimage", backimg_resize);



	if (front_foreignArea < 50000 || circlelikelyhood>p_outserramin)//没找到最外的轮廓  同时辅以圆度判断   反面由于要分割 圆度在14.28附近 没有正面稳定
	{

		numofneeflag = false; //2017年10月5日08:25:25

		//drawContours(backimg_resize, foreigncontour_external, foreignmax_Index, Scalar(0, 255, 255), 2, 8);

		imwrite("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\42_back.bmp", backimg_resize);
		//存储退出
		//imwrite(fileNameWithCurrentTime().GetBuffer(0), backimg_resize);
		imwrite(fileNameWithCurrentTime().GetBuffer(0), backimg_resize);
		//thread save_back2([backimg_resize]() {
		//	imwrite(fileNameWithCurrentTime().GetBuffer(0), backimg_resize);
		//});
		//save_back2.detach();
		return;  //直接返回  由于可能没有轴承
	}





	cv::rectangle(backimg_resize, r, Scalar(0, 255, 0), 1, 8, 0);
	cv::drawContours(backimg_resize, contour_external, max_Index, Scalar(255, 0, 0), 1, 8);  //画从正面得到的 远的轮廓


	//cv::imshow("backimg", backimg_resize);
	oilDetectRegion = backimg_bin(r);
	backimg_resize_roi = backimg_resize(r);

	//imshow("oilDetectRegion", oilDetectRegion);

	Mat oilDetectRegionInCircle;
	extractInCircle(oilDetectRegion, oilDetectRegionInCircle, r.width, r.height);
	//imshow("oilDetectRegionInCircle", oilDetectRegionInCircle);
	//形态学滤波 断开间隙 用 闭运算
	cv::medianBlur(oilDetectRegionInCircle, oilDetectRegionInCircle, 3);
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
	//cv::morphologyEx(oilDetectRegionInCircle, oilDetectRegionInCircle, MORPH_OPEN, element);
	cv::morphologyEx(oilDetectRegionInCircle, oilDetectRegionInCircle, MORPH_CLOSE, element);

	//imshow("oilDetectRegionInCircle_close", oilDetectRegionInCircle);

	vector<vector<Point>> allContours;           //保存全部连通域

	cv::findContours(oilDetectRegionInCircle, allContours, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);


	int sumArea=0;
	double oilLackRatio=0;
	bool bigarea = true;

	for (size_t i = 0; i < allContours.size(); i++)  //筛选判断环节   2018年10月27日09:36:51 算总面积 并且 找有没有比空油联通还大的区域
	{
		//cout << allContours[i].size() << "  " << contourArea(allContours[i]) << endl;
		int count= contourArea(allContours[i]);
		sumArea += count;
		if (count>666) {   //两个是568   2018年10月27日09:26:35 上界要不要设 if (count>800 && count<10000) {   测试过721			
			bigarea = false;
			//oilstateflag = false;
			//if (ballflag){
			//	if (!(extracted_circles.size() == p_num)){
			//		numofneeflag = false;
			//	}
			}
			
		}
		//drawContours(backimg_resize_roi, allContours,i, Scalar(rand() & 255, rand() & 255, rand() & 255),-1,8);
		//imshow("backimg_resize_roi", backimg_resize_roi);
		//cvWaitKey(0);
	//if (allContours.size() > 16){
	//	oilstateflag = false;
	//}
	//油量比例判断

	//油量比例判断
	oilLackRatio = sumArea / (contourArea(contour_external[max_Index]) + 1);
	if (oilLackRatio > p_erra){
		oilstateflag = false;
	}
	bool ballflag_pre = ballflag;
	if (numofneeflag&&ballflag){//不缺针  不缺球的情况下     计算油的比重  还有大的孔才是   通孔面积/元轮廓面积    
		if (oilLackRatio>p_erra){
			if (bigarea == false)
				ballflag = false;    //倾斜导致的  ballflag NG	
		}
	}

	
	if (!bigarea && ballflag_pre){                //add 缺针的双重保险   15个填满  一个缺针 比例小于 预设值   还加一个背景大块漏光来判断
		numofneeflag = false;     //理论上来讲  仅存在一个问题 就是倾斜的大面积漏光 缺针会被标上 其他没问题
		
	
	}


	if (numofneeflag&&ballflag){//不缺针  不缺球的情况下     计算油的比重  还有大的孔才是   通孔面积/元轮廓面积    
		if (oilLackRatio>p_erra){
			if (bigarea == false)
			ballflag = false;    //倾斜导致的  ballflag NG	
		}
	}




	Scalar oilColor;
	if (oilstateflag && ballflag){
		oilColor = Scalar(0, 255, 0);
	}
	else{
		oilColor = Scalar(0, 0, 255);
	}

	if (!bigarea && ballflag_pre){
		oilColor = Scalar(0, 0, 255);
	}


	s.clear();
	s.str("");
	s << "Hole ratio: " << oilLackRatio * 100 << "%";
	if (oilColor == Scalar(0, 0, 255))
	putText(backimg_resize, s.str(), cvPoint(50, 70), FONT_HERSHEY_COMPLEX, 0.6, CV_RGB(255, 0, 0), 1, 8, 0);
	else {
		putText(backimg_resize, s.str(), cvPoint(50, 70), FONT_HERSHEY_COMPLEX, 0.6, CV_RGB(0, 0, 255), 1, 8, 0);

	}
	if (!oilstateflag){
		s.clear();
		s.str("");
		s << "Error Count: " << allContours.size();
		//putText(backimg_resize, s.str(), cvPoint(50, 30), FONT_HERSHEY_COMPLEX, 0.6, CV_RGB(255, 0, 0), 1, 8, 0);
	}



	for (size_t i = 0; i < allContours.size(); i++)  //绘图环节
	{
		cv::drawContours(backimg_resize_roi, allContours, i, oilColor, -1, 8);
		//imshow("backimg_resize", backimg_resize);
		//cvWaitKey(0);
	}


	//imshow("backimg_resize", backimg_resize);


	thread save([backimg_resize]() {
		imwrite("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\42_back.bmp", backimg_resize);

	});
	

	if ((!numofneeflag || !oilstateflag || !ballflag) && p_checkNGimg){

		//thread save_back3([backimg_resize]() {
			imwrite(fileNameWithCurrentTime().GetBuffer(0), backimg_resize);
		//});
	//	thread save_front3([frontimg_resize]() {
			imwrite(fileNameWithCurrentTime().GetBuffer(0), frontimg_resize);
	//	});


		//save_back3.join();
		//save_front3.join();

		//imwrite(fileNameWithCurrentTime().GetBuffer(0), frontimg_resize);
		//imwrite(fileNameWithCurrentTime().GetBuffer(0), backimg_resize);
	}


	save.join();


	



	return;
	//std::cout << "Runing time is:" << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	//cvWaitKey(0);
	//exit(1);



	
}

void CTRYimportPICDlg::OnClickedSaveCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bIsSaveImg = !m_bIsSaveImg;


}

//背光检测，显示？
void CTRYimportPICDlg::OnClickedBackButton()
{
	// TODO: 在此添加控件通知处理程序代码
}

//环光检测，显示？
void CTRYimportPICDlg::OnClickedCircleButton()
{
	// TODO: 在此添加控件通知处理程序代码
}

int EventCallbackFunc(UINT32 IntSrc)
{
	/*FHz_Thread = AfxBeginThread(StartTestGKThread,
	NULL,
	0,
	0,
	0,
	NULL);*/
	
	UINT32 input = IntSrc;
	if (input == 1)//输入口1有信号,环光拍摄
	{
		byte output = 255;
		Roseek_DO_SetPort(output);
		IO_Cir = TRUE;
		IO_Back = FALSE;
		showImgFlag = TRUE;
		pDlgstatic->SaveImageForP(IO_Cir, IO_Back);
		pDlgstatic->SaveImage();
		//byte output = 254;//output0输出信号，表示环光照片已保存
		//pDlgstatic->ShowResult();
		//Roseek_DO_SetPort(output);

		return 0;
	}
	else if (input == 2)//输入口2有信号，背光拍摄
	{
		IO_Cir = FALSE;
		IO_Back = TRUE;
		showImgFlag = TRUE;
			//while (cvWaitKey(2)!='q')
		//{
        pDlgstatic->SaveImageForP(IO_Cir, IO_Back);
		pDlgstatic->SaveImage();
	
		Imgprocess();//图片处理，返回结果numofneeflag,oilstateflag,ballflag
		pDlgstatic->DrawImg();
		pDlgstatic->ShowResult();
		pDlgstatic->UnPrepareForShowImg1();
		//}

		// numofneeflag = TRUE;
		if ((numofneeflag == TRUE) && (oilstateflag == TRUE) && (ballflag == TRUE) && (stateflag==TRUE)){
			byte output = 254;
			Roseek_DO_SetPort(output);
			//output = 255;
			//Roseek_DO_SetPort(output);*/
		}
		else{
			byte output = 253;
			Roseek_DO_SetPort(output);
			//output = 255;
			//Roseek_DO_SetPort(output);*/
		}

		return 0;

	}
	else if (input == 4)//输入口3有信号，点检信号
	{
		//-----------标识点检是否启动----------
		pDlgstatic->GetDlgItem(IDC_STATIC_TESTMODE)->SetWindowTextA("检测模式：点检");
		Roseek_DI_SetEventMask(251);
		return 0;
	}
	//if (IO_Cir == FALSE&&IO_Back == FALSE)
	//{

	//	IO_Cir = TRUE;
	//	Process_state = TRUE;
	//	pDlgstatic->SaveImageForP(IO_Cir,IO_Back);
	//	while (1){
	//		//读图片1
	//		Mat imgtest = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\1.bmp");
	//		if (imgtest.data)
	//		{
	//			Process_state = FALSE;
	//			break;
	//		}
	//	}
	//	if (IO_Cir == TRUE&&IO_Back == FALSE&&Process_state == FALSE)
	//	{
	//		byte output = 254;
	//		Roseek_DO_SetPort(output);
	//		return 0;
	//	}
	//}
	//if (IO_Cir == TRUE&&IO_Back == FALSE)
	//{
	//	IO_Cir = FALSE;
	//	IO_Back = TRUE;
	//	Process_state = TRUE;
	//	pDlgstatic->SaveImageForP(IO_Cir, IO_Back);
	//	while (1){
	//		//读图片1
	//		Mat imgtest = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\1.bmp");
	//		if (imgtest.data)
	//		{
	//			IO_Cir = FALSE;
	//			IO_Back = FALSE;
	//			Process_state = FALSE;
	//			break;
	//		}
	//	}
	//	//图像处理
	//	//ImgProcess(extern result)
	//	pDlgstatic->ShowResult();
	//	numofneeflag = TRUE;
	//	oilstateflag = TRUE;
	//	if (IO_Cir == FALSE&&IO_Back == TRUE&&Process_state == FALSE)
	//	{
	//		byte output = 254;
	//		Roseek_DO_SetPort(output);
	//		return 0;
	//	}
	//}
	//return 0;


}

//static UINT StartTestGKThread(void *param)
//{
//	if (IO_Cir == FALSE&&IO_Back == FALSE)
//	{
//		IO_Cir = TRUE;
//		Process_state = TRUE;
//		while (1){
//			//读图片1
//			Mat imgtest = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\1.bmp");
//			if (imgtest.data)
//			{
//				Process_state = FALSE;
//				break;
//			}
//		}
//		if (IO_Cir == TRUE&&IO_Back == FALSE&&Process_state == FALSE)
//		{
//			byte output = 254;
//			Roseek_DO_SetPort(output);
//			return 0;
//		}
//	}
//	if (IO_Cir == TRUE&&IO_Back == FALSE)
//	{
//		IO_Cir = FALSE;
//		IO_Back = TRUE;
//		while (1){
//			//读图片1
//			Mat imgtest = imread("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Debug\\SaveImage\\1.bmp");
//			if (imgtest.data)
//			{
//				Process_state = FALSE;
//				break;
//			}
//		}
//		//图像处理
//		//ImgProcess(extern result)
//		if (IO_Cir == FALSE&&IO_Back == TRUE&&Process_state == FALSE)
//		{
//			byte output = 254;
//			Roseek_DO_SetPort(output);
//			return 0;
//		}
//	}
//	return 0;
//}

void CTRYimportPICDlg::OnClickedButtonManager()
{
	// TODO:  在此添加控件通知处理程序代码
	NMFC_PASS *m_PassDlg = new NMFC_PASS(this);
	m_PassDlg->Create(IDD_DIALOG_PASS);
	m_PassDlg->ShowWindow(SW_SHOW);

}


HBRUSH CTRYimportPICDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (IDC_CAPTION == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(51, 153, 255));
	}
	if (IDC_STATIC_BACKOK == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(0, 255, 0));
	}
	if (IDC_STATIC_CIROK == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(0, 255, 0));
	}
	if (IDC_STATIC_BACKLIGHT == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(0, 255, 0));
	}
	if (IDC_STATIC_CIRLIGHT == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(0, 255, 0));
	}
	if (IDC_STATIC_BACKCAP == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(51, 153, 255));
	}
	if (IDC_STATIC_CIRCAP == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(51, 153, 255));
	}
	if (IDC_STATIC_COUNT == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(0, 255, 0));
	}
	if (IDC_STATIC_OKNUM == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(0, 255, 0));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CTRYimportPICDlg::OnStnClickedStaticShowFrame()
{
	// TODO:  在此添加控件通知处理程序代码
}
