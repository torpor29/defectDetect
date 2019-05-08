// NMFC_SETTING.cpp : 实现文件
//

#include "stdafx.h"
#include "TRYimportPIC.h"
#include "NMFC_SETTING.h"
#include "afxdialogex.h"
#include "TRYimportPICDlg.h"



// NMFC_SETTING 对话框

IMPLEMENT_DYNAMIC(NMFC_SETTING, CDialogEx)

NMFC_SETTING::NMFC_SETTING(CWnd* pParent /*=NULL*/)
	: CDialogEx(NMFC_SETTING::IDD, pParent)
	, s_num(p_num)
	, s_erra(p_erra)//0.0182-0.098
	, s_cirlightmin(p_cirligntmin)
	, s_cirlightmax(p_cirlightmax)
	, s_backlightmin(p_backlightmin)
	, s_backlightmax(p_backlightmax)
	, s_cirratio(p_cirratio)
	, s_neeamin(p_neeamin)
	, s_neegreymin(p_neegreymin)
	, s_outerramin(p_outerramin)
	, s_outserramin(p_outserramin)
	, s_ballerramin(p_ballerramin)
	//, s_address(_T("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\x64\\Release\\GxSingleCamColorImages"))
	, s_address(p_adreass)
	, s_savetime(p_savetime)
{
	

}

NMFC_SETTING::~NMFC_SETTING()
{
}

void NMFC_SETTING::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM, s_num);
	DDX_Text(pDX, IDC_EDIT_ERRA, s_erra);
	DDX_Text(pDX, IDC_EDIT_CIRLIGHTMIN, s_cirlightmin);
	//  DDX_Text(pDX, IDC_EDIT_CIRLIGHTMAX, s_cirlight);
	//  DDX_Text(pDX, IDC_EDIT_BACKLIGHTMIN, s_backlight);
	DDX_Text(pDX, IDC_EDIT_CIRLIGHTMAX, s_cirlightmax);
	DDX_Text(pDX, IDC_EDIT_BACKLIGHTMIN, s_backlightmin);
	DDX_Text(pDX, IDC_EDIT_BACKLIGHTMAX, s_backlightmax);
	DDX_Text(pDX, IDC_EDIT_CIRRATIO, s_cirratio);
	DDX_Text(pDX, IDC_EDIT_NEEAMIN, s_neeamin);
	DDX_Text(pDX, IDC_EDIT_NEEGREYMIN, s_neegreymin);
	DDX_Text(pDX, IDC_EDIT_OUTERRAMIN, s_outerramin);
	DDX_Text(pDX, IDC_EDIT_OUTSERRAMIN, s_outserramin);
	DDX_Text(pDX, IDC_EDIT1_BALLERRAMIN, s_ballerramin);
	DDX_Text(pDX, IDC_EDIT1_ADDRESS, s_address);
	DDX_Text(pDX, IDC_EDIT1_SAVETIME, s_savetime);
}


BEGIN_MESSAGE_MAP(NMFC_SETTING, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BACKLIGHTMAX, &NMFC_SETTING::OnDeltaposSpinBacklightmax)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BACKLIGHTMIN, &NMFC_SETTING::OnDeltaposSpinBacklightmin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BALLERRAMIN, &NMFC_SETTING::OnDeltaposSpinBallerramin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CIRLIGHTMAX, &NMFC_SETTING::OnDeltaposSpinCirlightmax)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CIRLIGHTMIN, &NMFC_SETTING::OnDeltaposSpinCirlightmin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CIRRATIO, &NMFC_SETTING::OnDeltaposSpinCirratio)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ERRA, &NMFC_SETTING::OnDeltaposSpinErra)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_NEEAMIN, &NMFC_SETTING::OnDeltaposSpinNeeamin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_NEEGREYMIN, &NMFC_SETTING::OnDeltaposSpinNeegreymin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_NUM, &NMFC_SETTING::OnDeltaposSpinNum)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OUTERRAMIN, &NMFC_SETTING::OnDeltaposSpinOuterramin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OUTSERRAMIN, &NMFC_SETTING::OnDeltaposSpinOutserramin)
	ON_BN_CLICKED(IDOK, &NMFC_SETTING::OnBnClickedOk)
END_MESSAGE_MAP()


// NMFC_SETTING 消息处理程序


void NMFC_SETTING::OnDeltaposSpinBacklightmax(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (s_backlightmax < s_backlightmin){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_backlightmax >0)
			s_backlightmax -=1;
	}
	else if (pNMUpDown->iDelta<0){
		if (s_backlightmax <255)
			s_backlightmax += 1;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnDeltaposSpinBacklightmin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (s_backlightmax < s_backlightmin){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_backlightmin > 0)
			s_backlightmin -= 1;
	}
	else if (pNMUpDown->iDelta<0){
		if (s_backlightmin< 255)
			s_backlightmin += 1;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnDeltaposSpinBallerramin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if ((s_ballerramin < 0)||(s_ballerramin>100)){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_ballerramin >0)
			s_ballerramin -= 1;
	}
	else if (pNMUpDown->iDelta < 0){
		if (s_ballerramin < 100)
			s_ballerramin += 1;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnDeltaposSpinCirlightmax(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (s_cirlightmax < s_cirlightmin){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_cirlightmax >0)
			s_cirlightmax -= 1;
	}
	else if (pNMUpDown->iDelta<0){
		if (s_cirlightmax < 255)
			s_cirlightmax += 1;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnDeltaposSpinCirlightmin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (s_cirlightmax < s_cirlightmin){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_cirlightmin > 0)
			s_cirlightmin -= 1;
	}
	else if (pNMUpDown->iDelta<0){
		if (s_cirlightmin < 255)
			s_cirlightmin += 1;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnDeltaposSpinCirratio(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if ((s_cirratio < 1) || (s_cirratio>13)){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_cirratio >2)
			s_cirratio -= 2;
	}
	else if (pNMUpDown->iDelta<0){
		if (s_cirratio <12)
			s_cirratio += 2;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnDeltaposSpinErra(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if ((s_erra < 0) || (s_erra>1)){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_erra >0)
			s_erra -= 0.001;
	}
	else if (pNMUpDown->iDelta<0){
		if (s_erra <0.098)
			s_erra += 0.001;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnDeltaposSpinNeeamin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if ((s_neeamin < 0) || (s_neeamin>20)){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_neeamin >0)
			s_neeamin -= 1;
	}
	else if (pNMUpDown->iDelta<0){
		if (s_neeamin <20)
			s_neeamin += 1;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnDeltaposSpinNeegreymin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	if ((s_neegreymin < 0) || (s_neegreymin>30)){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_neegreymin >0)
			s_neegreymin -= 1;
	}
	else if (pNMUpDown->iDelta<0){
		if (s_neegreymin < 30)
			s_neegreymin += 1;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnDeltaposSpinNum(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if ((s_num < 0) || (s_num>25)){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_num >0)
			s_num -= 1;
	}
	else if (pNMUpDown->iDelta<0){
		if (s_num <25)
			s_num += 1;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnDeltaposSpinOuterramin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if ((s_outerramin < 0) || (s_outerramin>20)){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_outerramin >0)
			s_outerramin -= 0.1;
	}
	else if (pNMUpDown->iDelta<0){
		if (s_outerramin <20)
			s_outerramin += 0.1;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnDeltaposSpinOutserramin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if ((s_outserramin < 0) || (s_outserramin>20)){
		MessageBox("参数错误");
		return;
	}
	if (pNMUpDown->iDelta > 0){
		if (s_outserramin >0)
			s_outserramin -= 0.1;
	}
	else if (pNMUpDown->iDelta<0){
		if (s_outserramin <20)
			s_outserramin += 0.1;
	}
	UpdateData(FALSE);
	*pResult = 0;
}


void NMFC_SETTING::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	if (s_backlightmax < s_backlightmin){
		MessageBox("背光参数错误");
		return;
	}
	if (s_cirlightmax < s_cirlightmin){
		MessageBox("环光参数错误");
		return;
	}
	if ((s_ballerramin < 0) || (s_ballerramin>100)){
		MessageBox("胶球参数错误");
		return;
	}
	
	if ((s_cirratio < 0) || (s_cirratio>13)){
		MessageBox("圆度参数错误");
		return;
	}
	if ((s_erra < 0) || (s_erra>1)){
		MessageBox("轴承缺陷面积参数错误");
		return;
	}
	if ((s_neeamin < 0) || (s_neeamin>20)){
		MessageBox("滚针面积参数错误");
		return;
	}
	if ((s_neegreymin < 0) || (s_neegreymin>30)){
		MessageBox("滚针灰度参数错误");
		return;
	}
	if ((s_num < 0) || (s_num>25)){
		MessageBox("参数错误");
		return;
	}
	if ((s_outerramin < 0) || (s_outerramin>20)){
		MessageBox("外圈异物参数错误");
		return;
	}
	if ((s_outserramin < 0) || (s_outserramin>20)){
		MessageBox("轴承外异物参数错误");
		return;
	}
	LPCTSTR pFileName = _T("C:\\Users\\BV2\\Desktop\\TRYimportPIC\\TRYimportPIC\\properties.txt");
	CFile file;
	USES_CONVERSION;
	char *enter = W2A(L"\r\n");
	file.Open(pFileName, CFile::modeCreate | CFile::modeWrite);
	//-----------写入滚针数量--------------
	CString str_num;
	str_num.Format("%d", s_num);
	file.Write(str_num, strlen(str_num));
	file.Write(enter, strlen(enter));
	//-----------写入轴承缺陷最小面积------
	CString str_erramin;
	str_erramin.Format("%.3f", s_erra);
	file.Write(str_erramin, strlen(str_erramin));
	file.Write(enter, strlen(enter));
	//-----------写入环形光最小值----------
	CString str_cirlightmin;
	str_cirlightmin.Format("%.0f", s_cirlightmin);
	file.Write(str_cirlightmin, strlen(str_cirlightmin));
	file.Write(enter, strlen(enter));
	//-----------写入环形光最大值----------
	CString str_cirlightmax;
	str_cirlightmax.Format("%.0f", s_cirlightmax);
	file.Write(str_cirlightmax, strlen(str_cirlightmax));
	file.Write(enter, strlen(enter));
	//-----------写入背光最小值------------
	CString str_backlightmin;
	str_backlightmin.Format("%.0f", s_backlightmin);
	file.Write(str_backlightmin, strlen(str_backlightmin));
	file.Write(enter, strlen(enter));
	//-----------写入背光最大值------------
	CString str_backlightmax;
	str_backlightmax.Format("%.0f", s_backlightmax);
	file.Write(str_backlightmax, strlen(str_backlightmax));
	file.Write(enter, strlen(enter));
	//-----------写入滚针圆度最小值--------
	CString str_cirratio;
	str_cirratio.Format("%d", s_cirratio);
	file.Write(str_cirratio, strlen(str_cirratio));
	file.Write(enter, strlen(enter));
	//-----------写入滚针面积最小值--------
	CString str_neeamin;
	str_neeamin.Format("%d", s_neeamin);
	file.Write(str_neeamin, strlen(str_neeamin));
	file.Write(enter, strlen(enter));
	//-----------写入滚针灰度最小值--------
	CString str_neegreymin;
	str_neegreymin.Format("%d", s_neegreymin);
	file.Write(str_neegreymin, strlen(str_neegreymin));
	file.Write(enter, strlen(enter));
	//-----------写入外圈异物面积最小值----
	CString str_outerramin;
	str_outerramin.Format("%.2f", s_outerramin);
	file.Write(str_outerramin, strlen(str_outerramin));
	file.Write(enter, strlen(enter));
	//-----------写入轴承外异物面积最小值--
	CString str_outserramin;
	str_outserramin.Format("%.2f", s_outserramin);
	file.Write(str_outserramin, strlen(str_outserramin));
	file.Write(enter, strlen(enter));
	//-----------写入胶球异物面积最小值----
	CString str_ballerramin;
	str_ballerramin.Format("%.2f", s_ballerramin);
	file.Write(str_ballerramin, strlen(str_ballerramin));
	file.Write(enter, strlen(enter));
	//-----------写入存图选框值------------
	CButton*pBtn_SaveIMG = (CButton*)GetDlgItem(IDC_CHECK_SaveIMG);
	int state = pBtn_SaveIMG->GetCheck();
	CString str_SaveIMG;
	str_SaveIMG.Format("%d", state);
	file.Write(str_SaveIMG, strlen(str_SaveIMG));
	file.Write(enter, strlen(enter));
	//-----------写入存NG图选框值----------
	CButton* pBtn_SaveNGIMG = (CButton*)GetDlgItem(IDC_CHECK_SAVENGIMG);
	state = pBtn_SaveNGIMG->GetCheck();
	CString str_SAVENGIMG;
	str_SAVENGIMG.Format("%d", state);
	file.Write(str_SAVENGIMG, strlen(str_SAVENGIMG));
	file.Write(enter, strlen(enter));
	//-----------写入环形光选框值----------
	CButton* pBtn_CIRLIGHT = (CButton*)GetDlgItem(IDC_CHECK_CIRLIGHT);
	state = pBtn_CIRLIGHT->GetCheck();
	CString str_CHECKCIRLIGHT;
	str_CHECKCIRLIGHT.Format("%d", state);
	file.Write(str_CHECKCIRLIGHT, strlen(str_CHECKCIRLIGHT));
	file.Write(enter, strlen(enter));
	//-----------写入背光选框值------------
	CButton* pBtn_BACKLIGHT = (CButton*)GetDlgItem(IDC_CHECK_BACKLIGHT);
	state = pBtn_BACKLIGHT->GetCheck();
	CString str_CHECKBACKLIGHT;
	str_CHECKBACKLIGHT.Format("%d", state);
	file.Write(str_CHECKBACKLIGHT, strlen(str_CHECKBACKLIGHT));
	file.Write(enter, strlen(enter));
	//-----------写入滚针圆度选框值--------
	CButton* pBtn_CIRRATIO = (CButton*)GetDlgItem(IDC_CHECK_CIRRATIO);
	state = pBtn_CIRRATIO->GetCheck();
	CString str_CHECKCIRRATIO;
	str_CHECKCIRRATIO.Format("%d", state);
	file.Write(str_CHECKCIRRATIO, strlen(str_CHECKCIRRATIO));
	file.Write(enter, strlen(enter));
	//-----------写入滚针面积选框值--------
	CButton* pBtn_NEEAMIN = (CButton*)GetDlgItem(IDC_CHECK_NEEAMIN);
	state = pBtn_NEEAMIN->GetCheck();
	CString str_CHECKNEEAMIN;
	str_CHECKNEEAMIN.Format("%d", state);
	file.Write(str_CHECKNEEAMIN, strlen(str_CHECKNEEAMIN));
	file.Write(enter, strlen(enter));
	//-----------写入滚针灰度选框值--------
	CButton* pBtn_NEEGREYMIN = (CButton*)GetDlgItem(IDC_CHECK_NEEGREYMIN);
	state = pBtn_NEEGREYMIN->GetCheck();
	CString str_CHECKNEEGREYMIN;
	str_CHECKNEEGREYMIN.Format("%d", state);
	file.Write(str_CHECKNEEGREYMIN, strlen(str_CHECKNEEGREYMIN));
	file.Write(enter, strlen(enter));
	//-----------写入外圈异物选框值--------
	CButton* pBtn_OUTAMIN = (CButton*)GetDlgItem(IDC_CHECK_OUTERRAMIN);
	state = pBtn_OUTAMIN->GetCheck();
	CString str_CHECKOUTAMIN;
	str_CHECKOUTAMIN.Format("%d", state);
	file.Write(str_CHECKOUTAMIN, strlen(str_CHECKOUTAMIN));
	file.Write(enter, strlen(enter));
	//-----------写入轴承外异物选框值------
	CButton* pBtn_OUTSAMIN = (CButton*)GetDlgItem(IDC_CHECK_OUTSERRAMIN);
	state = pBtn_OUTSAMIN->GetCheck();
	CString str_CHECKOUTSAMIN;
	str_CHECKOUTSAMIN.Format("%d", state);
	file.Write(str_CHECKOUTSAMIN, strlen(str_CHECKOUTSAMIN));
	file.Write(enter, strlen(enter));
	//-----------写入胶球选框值------------
	CButton* pBtn_BALLERRMIN = (CButton*)GetDlgItem(IDC_CHECK_BALLERRAMIN);
	state = pBtn_BALLERRMIN->GetCheck();
	CString str_CHECKBALLERRMIN;
	str_CHECKBALLERRMIN.Format("%d", state);
	file.Write(str_CHECKBALLERRMIN, strlen(str_CHECKBALLERRMIN));
	file.Write(enter, strlen(enter));
	//-----------写入存图时间--------------
	CString str_savetime;
	str_savetime.Format("%ld", s_savetime);
	file.Write(str_savetime, strlen(str_savetime));
	file.Write(enter, strlen(enter));
	//-----------写入地址------------------
	file.Write(s_address, strlen(s_address));
	file.Write(enter, strlen(enter));

	file.Flush();
	file.Close();
	readPara();
	deletefiles();
	CDialogEx::OnOK();
}
