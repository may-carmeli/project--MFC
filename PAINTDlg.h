
#include "afxwin.h"

// PAINTDlg.h : header file
//

#pragma once
#include "MyShape.h"
#include "MyEllipse.h"
#include "MyRectangle.h"
#include "MyLine.h"
#include"MyPen.h"
#include"PenFactory.h"
#include "EllipseFactory.h"
#include "LineFactory.h"
#include "RectangleFactory.h"
#include <vector>
#include "AddShape.h"
#include <stack>
#include "afxwin.h"


using namespace std;

// CPAINTDlg dialog
class CPAINTDlg : public CDialogEx
{
// Construction
public:
	CPAINTDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAINT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	/* name: may carmeli ,id: 313296204
	aviya midan id: 205441769
	*/
	


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
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CButton m_redo;
	CButton m_undo;
	CButton m_erase;
	CButton m_unerase;
	CButton SaveIcon;
	CButton loadIcon;
	CButton COLORS;
	CButton FILLCOLOR;
	COLORREF color;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	enum MODE { SHAPE, DRAG, PAINTER, FILL_COLOR, RESIZE };
	MODE mode;
	void ForDelta(CPoint p, MyShape *s);
private:
	CBrush c;
	int index;
	bool isPressed;
	bool IsPaint;
	CPoint /* start_p, end_p, */paint;
	CTypedPtrArray<CObArray, MyShape*> myShapes;
	stack<Command*> commands, undoes, temp, UnErase;
	ShapeFactory* shapeFactory;
public:
	
	
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedErase();
	afx_msg void OnBnClickedUnerace();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedColors();
	afx_msg void OnBnClickedFillcolor();
};
