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

    CFont font;
    font.CreatePointFont(100, _T("Arial"), pDC); 
    CFont* pOldFont = pDC->SelectObject(&font);

    CSize textSize = pDC->GetTextExtent(_T("Test"));
    int lineHeight = textSize.cy + 10;

    int margin = 50;
    int colID = margin;
    int colName = pageWidth / 3;
    int colManager = 2 * pageWidth / 3;

    int y = margin;

    pDC->TextOut(colID, y, _T("ID"));
    pDC->TextOut(colName, y, _T("Name"));
    pDC->TextOut(colManager, y, _T("Manager"));

    y += lineHeight;


    CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* pOldPen = pDC->SelectObject(&pen);
    pDC->MoveTo(margin, y - 5);
    pDC->LineTo(pageWidth - margin, y - 5);
    pDC->SelectObject(pOldPen); 

   
    while (!rs.IsEOF())
    {
        CString strId;
        strId.Format(_T("%d"), rs.m_id);

        pDC->TextOut(colID, y, strId);
        pDC->TextOut(colName, y, rs.m_name);
        if (rs.m_manager)
            pDC->TextOut(colManager, y, _T("x"));

        y += lineHeight;
        rs.MoveNext();
    }

    pDC->SelectObject(pOldFont);
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



