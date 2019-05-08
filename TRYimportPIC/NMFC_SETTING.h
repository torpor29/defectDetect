#pragma once


// NMFC_SETTING 对话框

class NMFC_SETTING : public CDialogEx
{
	DECLARE_DYNAMIC(NMFC_SETTING)

public:
	NMFC_SETTING(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~NMFC_SETTING();

// 对话框数据
	enum { IDD = IDD_DIALOG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int s_num;
	float s_erra;
	float s_cirlightmin;
//	float s_cirlight;
//	float s_backlight;
	float s_cirlightmax;
	float s_backlightmin;
	float s_backlightmax;
	int s_cirratio;
	int s_neeamin;
	int s_neegreymin;
	float s_outerramin;
	float s_outserramin;
	float s_ballerramin;
	afx_msg void OnDeltaposSpinBacklightmax(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinBacklightmin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinBallerramin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCirlightmax(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCirlightmin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCirratio(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinErra(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinNeeamin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinNeegreymin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinNum(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinOuterramin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinOutserramin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	CString s_address;
	long s_savetime;
};
