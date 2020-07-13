
// PAINTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PAINT.h"
#include "PAINTDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CPAINTDlg dialog



CPAINTDlg::CPAINTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAINT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	shapeFactory = LineFactory::getInstance();
	isPressed = false;
	IsPaint = false;
	index = 0;
}

void CPAINTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_redo);
	DDX_Control(pDX, IDC_BUTTON2, m_undo);
	DDX_Control(pDX, IDC_Erase, m_erase);
	DDX_Control(pDX, IDC_UnErace, m_unerase);
	DDX_Control(pDX, IDC_BUTTON3, SaveIcon);
	DDX_Control(pDX, IDC_LOAD, loadIcon);
	DDX_Control(pDX, IDC_Colors, COLORS);
	DDX_Control(pDX, IDC_FILLCOLOR, FILLCOLOR);
}

BEGIN_MESSAGE_MAP(CPAINTDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1, &CPAINTDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO6, &CPAINTDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO5, &CPAINTDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO4, &CPAINTDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO3, &CPAINTDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO2, &CPAINTDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CPAINTDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPAINTDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_Erase, &CPAINTDlg::OnBnClickedErase)
	ON_BN_CLICKED(IDC_BUTTON2, &CPAINTDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_Erase, &CPAINTDlg::OnBnClickedErase)
	ON_BN_CLICKED(IDC_UnErace, &CPAINTDlg::OnBnClickedUnerace)
	ON_BN_CLICKED(IDC_BUTTON3, &CPAINTDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_LOAD, &CPAINTDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_Colors, &CPAINTDlg::OnBnClickedColors)
	ON_BN_CLICKED(IDC_FILLCOLOR, &CPAINTDlg::OnBnClickedFillcolor)
END_MESSAGE_MAP()


// CPAINTDlg message handlers

BOOL CPAINTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	FILLCOLOR.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_FILLCOLOR)));
	COLORS.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_COLORS)));
	m_redo.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_REDO)));
	m_undo.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_UNDO)));
	m_erase.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_ERASE)));
	m_unerase.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_UNERASE)));
	loadIcon.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_LOAD)));
	SaveIcon.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SAVE)));

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);
	c.CreateSolidBrush(RGB(255,200,255));
	Invalidate();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPAINTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPAINTDlg::OnPaint()
{
	CPaintDC dc(this);
	for (int i = 0; i < myShapes.GetSize(); ++i)
		myShapes[i]->draw(&dc);
	CDialogEx::OnPaint();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPAINTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPAINTDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	isPressed = true;
	switch (mode)
	{
	case DRAG:
	{
		for (int i = myShapes.GetSize() - 1; i >= 0; --i)
			if (myShapes[i]->IsContained(point))
			{
				index = i;
				break;
			}
		break;
	}
	case PAINTER:
	{
		MyShape *s = shapeFactory->createShape();
		Command *c = new AddShape(myShapes, s);
		c->perform();
		commands.push(c);
		s->setBg(color);
		s->setStart(point);
		s->setEnd(point);
		Invalidate(false);
		break;
	}
	case FILL_COLOR:
	{
		for (int i = myShapes.GetSize() - 1; i >= 0; --i)
		{
			if (myShapes[i]->IsContained(point))
			{
				myShapes[i]->setBg(color);
				Invalidate();
				break;
			}
		}
		break;
	}
	case SHAPE:
	{
		MyShape *s = shapeFactory->createShape();
		Command *c = new AddShape(myShapes, s);
		c->perform();
		commands.push(c);
		s->setBg(color);
		s->setStart(point);
		s->setEnd(point);
		Invalidate();
		break;
	}
	case RESIZE:
	{
		for (int i = myShapes.GetSize() - 1; i >= 0; --i)
		{
			if (myShapes[i]->IsContained(point))
			{
				index = i;
				break;
			}
		}
		break;
	}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}



void CPAINTDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (mode == SHAPE)
		myShapes[myShapes.GetSize() - 1]->setEnd(point);
	Invalidate();
	IsPaint = false;
	isPressed = false;
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CPAINTDlg::OnMouseMove(UINT nFlags, CPoint point)
{

	m_undo.EnableWindow(true);
	m_redo.EnableWindow(true);
	if (isPressed)
	{
		switch (mode)
		{
		case SHAPE:
		{
			myShapes[myShapes.GetSize() - 1]->setEnd(point);
			Invalidate();
			break;
		}
		case DRAG:
		{//move
			ForDelta(point, myShapes[index]);
			//end_p = point;
			Invalidate();
			break;
		}
		case RESIZE:
		{
			myShapes[index]->end.x = point.x;
			myShapes[index]->end.y = point.y;
			Invalidate();
			break;
		}
		case PAINTER:
		{
			myShapes[myShapes.GetSize() - 1]->end = point;
			MyShape *s = shapeFactory->createShape();
			Command *c = new AddShape(myShapes, s);
			c->perform();
			commands.push(c);
			s->setBg(color);
			s->setStart(point);
			s->setEnd(point);
			Invalidate(false);
			break;
		}
		}

	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CPAINTDlg::OnBnClickedButton1()//redo
{
	Command *c;
	if (!undoes.empty())
	{
		c = undoes.top();
		c->perform();
		commands.push(c);
		undoes.pop();
		Invalidate();
	}
}


void CPAINTDlg::OnBnClickedRadio6()//resize
{
	mode = RESIZE;
}


void CPAINTDlg::OnBnClickedRadio5()//drag
{
	mode = DRAG;
}


void CPAINTDlg::OnBnClickedRadio4()//painter
{
	mode = PAINTER;
	shapeFactory = PenFactory::getInstance();
}


void CPAINTDlg::OnBnClickedRadio3()//elipse
{
	mode = SHAPE;
	shapeFactory = EllipseFactory::getInstance();
}


void CPAINTDlg::OnBnClickedRadio2()//Rectangle
{
	mode = SHAPE;
	shapeFactory = RectangleFactory::getInstance();
}


void CPAINTDlg::OnBnClickedRadio1()//line
{
	mode = SHAPE;
	shapeFactory = LineFactory::getInstance();
}

HBRUSH CPAINTDlg::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)////pink screen
{
	HBRUSH hbr;
	hbr = c;
	return hbr;
}

void CPAINTDlg::ForDelta(CPoint p, MyShape * s)//fordrag
{
	s->end.x += (p.x - s->start.x);
	s->end.y += (p.y - s->start.y);
	s->start.x = p.x;
	s->start.y = p.y;
}





	



void CPAINTDlg::OnBnClickedButton2()//undo
{
	Command *c;
	if (!commands.empty())
	{
		c = commands.top();
		c->rollback();
		undoes.push(c);
		commands.pop();
		Invalidate();
	}
}


void CPAINTDlg::OnBnClickedErase()//erase
{
	Command *c;
	for (int i = 0; i < myShapes.GetSize(); ++i)
	{

		Command *c = new AddShape(myShapes, myShapes[i]);
		temp.push(c);
	
	}
	myShapes.RemoveAll();
	Invalidate();
}


void CPAINTDlg::OnBnClickedUnerace()//unerse
{
	
	while (temp.empty() == false)
	{
		Command *c = temp.top();
		c->perform();
		temp.pop();
		Invalidate();
	}
}


void CPAINTDlg::OnBnClickedButton3()//save
{
	CFile file;
	CFileDialog FileDLG(false);
	FileDLG.m_ofn.lpstrFilter = _T("DATA Files (*.dat)\0.dat\0");
	FileDLG.m_ofn.lpstrTitle = _T("Save DATA File As");
	CString filename;
	if (FileDLG.DoModal() == IDOK)
	{
		filename = FileDLG.GetPathName();
		filename.Append(_T(".dat"));
	}
	if (file.Open(filename, CFile::modeCreate | CFile::modeWrite))
	{
		CArchive ar(&file, CArchive::store);
		myShapes.Serialize(ar);
		ar.Close();
	}
	else
		return;
	file.Close();
}


void CPAINTDlg::OnBnClickedLoad()//load
{
	CFile file;
	CFileDialog FileDLG(true);
	FileDLG.m_ofn.lpstrFilter = _T("DATA Files ( *.dat)");//type of file
	FileDLG.m_ofn.lpstrTitle = _T("Load DATA File As");//titel
	CString filename;
	CString file_end = _T(".dat");
	if (FileDLG.DoModal() == IDOK)
	filename = FileDLG.GetPathName();//put file in filename
	if (filename.Find(file_end) == string::npos)//check if .dat is proper
	{
		filename.Append(file_end);//Adds .dat To the end of the string
	}
	if (file.Open(filename, CFile::modeRead))//moderead :Requests read access only 
	{
		CArchive ar(&file, CArchive::load);//load:	Determines whether the archive is loading,
		myShapes.Serialize(ar);
		ar.Close();
	}
	else
		return;
	file.Close();
	Invalidate();
}


void CPAINTDlg::OnBnClickedColors()//colors
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
		color = dlg.GetColor();
}


void CPAINTDlg::OnBnClickedFillcolor()//fillcolor
{
	mode = FILL_COLOR;
}
