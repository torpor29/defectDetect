//#ifndef _TRYIMPORTPICDLG_H_
//#define _TRYIMPORTPICDLG_H_
#if !defined(AFX_GxSingleCamColorDLG_H__D8D963C2_3BE2_44EC_B0EB_FCE016DDD6FA__INCLUDED_)
#define AFX_GxSingleCamColorDLG_H__D8D963C2_3BE2_44EC_B0EB_FCE016DDD6FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


///< ������ʾ�����궨��
#define  GX_VERIFY(emStatus) \
	                        if (emStatus != GX_STATUS_SUCCESS)\
							{\
							ShowErrorString(emStatus); \
							return ;\
							 } 
///< �жϷ���ֵ�궨��
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
// ����
public:
	CTRYimportPICDlg(CWnd* pParent = NULL);	// ��׼���캯��

public:
	GX_DEV_HANDLE       m_hDevice;              ///< �豸���

	BITMAPINFO          *m_pBmpInfo;	        ///< BITMAPINFO �ṹָ�룬��ʾͼ��ʱʹ��
	BYTE                *m_pBufferRaw;          ///< ԭʼͼ������
	BYTE                *m_pBufferRGB;	        ///< RGBͼ�����ݣ�������ʾ�ͱ���bmpͼ��
    char                 m_chBmpBuf[2048];	    ///< BIMTAPINFO �洢��������m_pBmpInfo��ָ��˻�����

	BITMAPINFO          *m_pBmpInfonew1;
	BYTE                *m_pBufferRGBnew1;
	BITMAPINFO          *m_pBmpInfonew2;
	BYTE                *m_pBufferRGBnew2;


	int64_t             m_nPayLoadSize;         ///< ͼ���С
	int64_t             m_nImageHeight;         ///< ԭʼͼ���
    int64_t             m_nImageWidth;          ///< ԭʼͼ���
	int64_t             m_nImageWidthnew;          ///<��ʾͼ���
	int64_t             m_nImageHeightnew;         ///<��ʾͼ���
	int64_t             m_nPixelColorFilter;    ///< Bayer��ʽ
	bool                m_bColorFilter;         ///< ��ʶ�Ƿ�֧�ֲ�ɫ

	CString             m_strFilePath;          ///< BMPͼ��Ĭ�ϱ���·��
	BOOL                m_bIsSaveImg;           ///< ��ʶ�Ƿ񱣴�ͼ��
	BOOL                m_bDevOpened;           ///< ��ʶ�Ƿ��Ѵ��豸
	BOOL                m_bIsSnap;              ///< ��ʶ�Ƿ�ʼ�ɼ�
	BOOL                m_numOfnee;             ///< ��ʶ�������Ƿ�OK
	BOOL                m_numOfball;            ///< ��ʶ�����Ƿ�OK
	BOOL                m_oilState;             ///< ��ʶ��֬���Ƿ�OK

	CWnd                *m_pWnd;                ///< ��ʾͼ�񴰿�(�ؼ�)ָ��
	HDC                 m_hDC;                  ///< ����ͼ��DC���

	CWnd                *m_pWnd2;               ///< ��ʾͼ�񴰿�(�ؼ�)ָ��
	HDC                 m_hDC2;                 ///< ����ͼ��DC���

public:
	int *cur_class;                             ///<��Ʒ�ͺ���
	int *cur_num;                               ///<OKƷ��������
	int *cur_name;                              ///<��Ʒ����

//public:
//	BOOL IO_in;                                 ///<IO���ź�
//	BOOL IO_out;                                ///<IO����ź�
//	BOOL Process_state;                         ///<�Ƿ��ܽ�����һ��ͼƬ�����㴦��

	public:
	///  Ϊͼ����ʾ׼����Դ
	bool PrepareForShowImg();
	bool PrepareForShowImgnew();

	/// ��ȡ�豸����,��ʼ������ؼ�
	void InitUI();

    /// ˢ��UI����
	void UpDateUI();

	/// �ص�����
	static void __stdcall OnFrameCallbackFun(GX_FRAME_CALLBACK_PARAM* pFrame);

	///  �ͷ�Ϊͼ����ʾ׼����Դ
	void UnPrepareForShowImg();
	///  �ͷ�Ϊͼ����ʾ׼����Դ
	void UnPrepareForShowImg1();


	/// ��ʾͼ��
	void DrawImg();

	/// ������Ϣ��ʾ
	void ShowErrorString(GX_STATUS emErrorStatus);

	/// ��ʼ��ö������UI����
	void InitEnumUI(GX_FEATURE_ID_CMD emFeatureID, CComboBox *pComboBox, bool bIsImplement);
	
	/// ��ʼ�����:����Ĭ�ϲ���
	GX_STATUS InitDevice();

	/// ������������ݸ�ʽΪ8bit
	GX_STATUS SetPixelFormat8bit();

	/// ��ȡ�豸�Ŀ��ߵ�������Ϣ
	GX_STATUS GetDeviceParam();

	/// ���»�ȡ������Ʒ����
	void ExchangePro();

	/// ����ͼ�񣨱���NGͼ��
	void SaveImage();

	/// ����ǰ����ͼƬ
	void SaveImageForP(BOOL IO_Cir,BOOL IO_Back);

	/// �����ɾ��ͼƬ
	void DeleteImage();

	///����ɫ���ص�ռ��
	//int wSums(Mat src);

	///ͼ����
	//void Imgprocess();

	///�����ʾ
	void ShowResult();

	 void initCloseDevice();
	 void initOpenDevice();
	 void initStartSnap();
	 void initStopSnap();
// �Ի�������
	enum { IDD = IDD_TRYIMPORTPIC_DIALOG };

	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
