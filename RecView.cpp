// RecView.cpp : implementation of the RecView class
//

#include "stdafx.h"
#include "v10.h"

#include "Set.h"
#include "Doc.h"
#include "RecView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RecView

IMPLEMENT_DYNCREATE(RecView, CRecordView)

BEGIN_MESSAGE_MAP(RecView, CRecordView)
	//{{AFX_MSG_MAP(RecView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RecView construction/destruction

RecView::RecView()
	: CRecordView(RecView::IDD)
{
}

RecView::~RecView()
{
}

void RecView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RecView)
	//}}AFX_DATA_MAP
    DDX_FieldText(pDX, IDC_EDIT1, m_pSet->m_id, m_pSet);
    DDX_FieldText(pDX, IDC_EDIT2, m_pSet->m_name, m_pSet);
    DDX_FieldCheck(pDX, IDC_CHECK1, m_pSet->m_manager, m_pSet);
}

BOOL RecView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CRecordView::PreCreateWindow(cs);
}

void RecView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_set;
	CRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// RecView printing

BOOL RecView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void RecView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{

    Set rs;
    rs.Open();

    int pageWidth = pDC->GetDeviceCaps(HORZRES);
    int pageHeight = pDC->GetDeviceCaps(VERTRES);


    CFont font;
    font.CreatePointFont(100, _T("Arial"), pDC);

    CFont* pOldFont = pDC->SelectObject(&font);
    CSize textSize = pDC->GetTextExtent(_T("Test"));
    int lineHeight = textSize.cy + 10;

    int y = 100; 

    pDC->TextOut(100, y, _T("ID"));
    pDC->TextOut(200, y, _T("Name"));
    pDC->TextOut(500, y, _T("Manager"));
    y += lineHeight;

    CPen pen(PS_SOLID, 1, RGB(0, 0, 0)); 
    CPen* pOldPen = pDC->SelectObject(&pen);
    pDC->MoveTo(100, y);
    pDC->LineTo(pageWidth - 100, y);
    pDC->SelectObject(pOldPen);
    pen.DeleteObject();

    y += 5;

    while (!rs.IsEOF())
    {
        CString strId, strName, strManager;

        strId.Format(_T("%d"), rs.m_id);
        strName = rs.m_name;
        strManager = rs.m_manager ? _T("x") : _T("");

        pDC->TextOut(100, y, strId);
        pDC->TextOut(200, y, strName);
        pDC->TextOut(500, y, strManager);

        y += lineHeight;

        rs.MoveNext();
    }

    pDC->SelectObject(pOldFont);
    font.DeleteObject();

    rs.Close();
}

void RecView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void RecView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// RecView diagnostics

#ifdef _DEBUG
void RecView::AssertValid() const
{
	CRecordView::AssertValid();
}

void RecView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

Doc* RecView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Doc)));
	return (Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// RecView database support
CRecordset* RecView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// RecView message handlers



