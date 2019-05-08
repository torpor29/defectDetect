//#ifndef _TRYIMPORTPICDLG_H_
//#define _TRYIMPORTPICDLG_H_
#if !defined(AFX_GxSingleCamColorDLG_H__D8D963C2_3BE2_44EC_B0EB_FCE016DDD6FA__INCLUDED_)
#define AFX_GxSingleCamColorDLG_H__D8D963C2_3BE2_44EC_B0EB_FCE016DDD6FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


///< 错误提示函数宏定义
#define  GX_VERIFY(emStatus) \
	                        if (emStatus != GX_STATUS_SUCCESS)\
							{\
							ShowErrorString(emStatus); \
							return ;\
							 } 
///< 判断返回值宏定义
#define VERIFY_STATUS_RET(emStatus) \
	                               if (emStatus != GX_STATUS_SUCCESS) \
								   {\
								   return emStatus;\
								   }\

/////////////////////////////////////////////////////////////////////////////

// CGxSingleCamColorDlg dialog
#include "GxIAPI.h"
#include "DxImageProc.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\core\core.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <CTime>
#include <thread>
//#include "afxwin.h"
//#include "afx.h"

using namespace cv;
using namespace std;

#define TRUE true
#define FALSE false
class CTRYimportPICDlg : public CDialogEx
{
// 构造
public:
	CTRYimportPICDlg(CWnd* pParent = NULL);	// 标准构造函数

public:
	GX_DEV_HANDLE       m_hDevice;              ///< 设备句柄

	BITMAPINFO          *m_pBmpInfo;	        ///< BITMAPINFO 结构指针，显示图像时使用
	BYTE                *m_pBufferRaw;          ///< 原始图像数据
	BYTE                *m_pBufferRGB;	        ///< RGB图像数据，用于显示和保存bmp图像
    char                 m_chBmpBuf[2048];	    ///< BIMTAPINFO 存储缓冲区，m_pBmpInfo即指向此缓冲区

	BITMAPINFO          *m_pBmpInfonew1;
	BYTE                *m_pBufferRGBnew1;
	BITMAPINFO          *m_pBmpInfonew2;
	BYTE                *m_pBufferRGBnew2;


	int64_t             m_nPayLoadSize;         ///< 图像大小
	int64_t             m_nImageHeight;         ///< 原始图像高
    int64_t             m_nImageWidth;          ///< 原始图像宽
	int64_t             m_nImageWidthnew;          ///<显示图像宽
	int64_t             m_nImageHeightnew;         ///<显示图像高
	int64_t             m_nPixelColorFilter;    ///< Bayer格式
	bool                m_bColorFilter;         ///< 标识是否支持彩色

	CString             m_strFilePath;          ///< BMP图像默认保存路径
	BOOL                m_bIsSaveImg;           ///< 标识是否保存图像
	BOOL                m_bDevOpened;           ///< 标识是否已打开设备
	BOOL                m_bIsSnap;              ///< 标识是否开始采集
	BOOL                m_numOfnee;             ///< 标识滚针数是否OK
	BOOL                m_numOfball;            ///< 标识橡胶球是否OK
	BOOL                m_oilState;             ///< 标识油脂量是否OK

	CWnd                *m_pWnd;                ///< 显示图像窗口(控件)指针
	HDC                 m_hDC;                  ///< 绘制图像DC句柄

	CWnd                *m_pWnd2;               ///< 显示图像窗口(控件)指针
	HDC                 m_hDC2;                 ///< 绘制图像DC句柄

public:
	int *cur_class;                             ///<产品型号数
	int *cur_num;                               ///<OK品滚针数量
	int *cur_name;                              ///<产品名称

//public:
//	BOOL IO_in;                                 ///<IO口信号
//	BOOL IO_out;                                ///<IO输出信号
//	BOOL Process_state;                         ///<是否能进行下一张图片的拍摄处理

	public:
	///  为图像显示准备资源
	bool PrepareForShowImg();
	bool PrepareForShowImgnew();

	/// 获取设备参数,初始化界面控件
	void InitUI();

    /// 刷新UI界面
	void UpDateUI();

	/// 回调函数
	static void __stdcall OnFrameCallbackFun(GX_FRAME_CALLBACK_PARAM* pFrame);

	///  释放为图像显示准备资源
	void UnPrepareForShowImg();
	///  释放为图像显示准备资源
	void UnPrepareForShowImg1();


	/// 显示图像
	void DrawImg();

	/// 错误信息提示
	void ShowErrorString(GX_STATUS emErrorStatus);

	/// 初始化枚举类型UI界面
	void InitEnumUI(GX_FEATURE_ID_CMD emFeatureID, CComboBox *pComboBox, bool bIsImplement);
	
	/// 初始化相机:设置默认参数
	GX_STATUS InitDevice();

	/// 设置相机的数据格式为8bit
	GX_STATUS SetPixelFormat8bit();

	/// 获取设备的宽、高等属性信息
	GX_STATUS GetDeviceParam();

	/// 更新获取三个产品属性
	void ExchangePro();

	/// 保存图像（保存NG图）
	void SaveImage();

	/// 处理前保存图片
	void SaveImageForP(BOOL IO_Cir,BOOL IO_Back);

	/// 处理后删除图片
	void DeleteImage();

	///检测白色像素点占比
	//int wSums(Mat src);

	///图像处理
	//void Imgprocess();

	///结果显示
	void ShowResult();

	 void initCloseDevice();
	 void initOpenDevice();
	 void initStartSnap();
	 void initStopSnap();
// 对话框数据
	enum { IDD = IDD_TRYIMPORTPIC_DIALOG };

	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//afx_msg void OnClickedCloseDevice();
	//afx_msg void OnClickedOpenDevice();
	//afx_msg void OnClickedStartSnap();
	//afx_msg void OnClickedStopSnap();
public:
	
	afx_msg void OnClickedClearButton();
	afx_msg void OnClickedExchangeButton();
	afx_msg void OnClickedSaveButton();
	afx_msg void OnClickedSavePicButton();
	CComboBox m_classcombo;
	CComboBox m_namecombo;
	//CComboBox m_numcombo;
	afx_msg void OnClickedSaveCheck();
	afx_msg void OnClickedBackButton();
	afx_msg void OnClickedCircleButton();
	CStatic m_ballNG;
	CStatic m_numNG;
	CStatic m_oilNG;
//	CEdit NumofOk;
//	CString NumofOk;
	afx_msg void OnClickedButtonManager();
//	CStatic m_stateNG;
	CStatic m_stateNG;
	CFont font;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedStaticShowFrame();
};
extern void readPara();
extern void deletefiles();
extern volatile int p_num;
extern volatile float p_erra;
extern volatile float p_cirligntmin;
extern volatile float p_cirlightmax;
extern volatile float p_backlightmin;
extern volatile float p_backlightmax;
extern volatile int p_cirratio;
extern volatile int p_neeamin;
extern volatile int p_neegreymin;
extern volatile float p_outerramin;
extern volatile float p_outserramin;
extern volatile float p_ballerramin;
extern CString p_adreass;
extern volatile long p_savetime;
extern volatile BOOL p_checksave;
extern volatile BOOL p_checkNGimg;
extern volatile BOOL p_checkcirlight;
extern volatile BOOL p_checkbacklight;
extern volatile BOOL p_checkcirratio;
extern volatile BOOL p_checkneeamin;
extern volatile BOOL p_checkneegreymin;
extern volatile BOOL p_checkouterramin;
extern volatile BOOL p_checkoutserramin;
extern volatile BOOL p_checkballerramin;
extern volatile float cirraitooutput;
#endif
