
// Direct2DGeometrySampleView.cpp : implementation of the CDirect2DGeometrySampleView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Direct2DGeometrySample.h"
#endif

#include "Direct2DGeometrySampleDoc.h"
#include "Direct2DGeometrySampleView.h"
#include "Direct2DHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirect2DGeometrySampleView

IMPLEMENT_DYNCREATE(CDirect2DGeometrySampleView, CView)

BEGIN_MESSAGE_MAP(CDirect2DGeometrySampleView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDirect2DGeometrySampleView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_SHAPE_RRECT, &CDirect2DGeometrySampleView::OnShapeRrect)
	ON_COMMAND(ID_SHAPE_RECTANGLE, &CDirect2DGeometrySampleView::OnShapeRectangle)
	ON_COMMAND(ID_SHAPE_ELLIPSE, &CDirect2DGeometrySampleView::OnShapeEllipse)
END_MESSAGE_MAP()

// CDirect2DGeometrySampleView construction/destruction

CDirect2DGeometrySampleView::CDirect2DGeometrySampleView() : m_pRender ( NULL ), m_eShape( SHAPE_RECT )
{
	// TODO: add construction code here

}

CDirect2DGeometrySampleView::~CDirect2DGeometrySampleView()
{
}

BOOL CDirect2DGeometrySampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDirect2DGeometrySampleView drawing

void CDirect2DGeometrySampleView::OnDraw(CDC* /*pDC*/)
{
	/*
	CDirect2DGeometrySampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return; */

	if( m_pRender )
		m_pRender->OnRender();
}


// CDirect2DGeometrySampleView printing


void CDirect2DGeometrySampleView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDirect2DGeometrySampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDirect2DGeometrySampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDirect2DGeometrySampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDirect2DGeometrySampleView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CDirect2DGeometrySampleView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDirect2DGeometrySampleView diagnostics

#ifdef _DEBUG
void CDirect2DGeometrySampleView::AssertValid() const
{
	CView::AssertValid();
}

void CDirect2DGeometrySampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDirect2DGeometrySampleDoc* CDirect2DGeometrySampleView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDirect2DGeometrySampleDoc)));
	return (CDirect2DGeometrySampleDoc*)m_pDocument;
}
#endif //_DEBUG


// CDirect2DGeometrySampleView message handlers


int CDirect2DGeometrySampleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pRender = new Direct2DHandler( m_hWnd );
	m_pRender->Initialize();

	
	return 0;
}


void CDirect2DGeometrySampleView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if( m_pRender && cx && cy )
		m_pRender->OnResize( cx, cy );
}


void CDirect2DGeometrySampleView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ptBeg = point;
	CView::OnLButtonDown(nFlags, point);
}


void CDirect2DGeometrySampleView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_ptEnd = point;

	if( SHAPE_RECT == m_eShape )
		m_pRender->CreateRectangle( CRect( m_ptBeg, point ), true );
	else if( SHAPE_RRECT == m_eShape )
		m_pRender->CreateRoundedRectangle( CRect( m_ptBeg, point),10,10, true );
	else if( SHAPE_ELLIPSE == m_eShape )
		m_pRender->CreateEllipse( CRect( m_ptBeg, point ));
	else
		return;

	RedrawWindow();
}


void CDirect2DGeometrySampleView::OnShapeRrect()
{
	m_eShape = SHAPE_RRECT;	
}


void CDirect2DGeometrySampleView::OnShapeRectangle()
{
	m_eShape = SHAPE_RECT;	
}


void CDirect2DGeometrySampleView::OnShapeEllipse()
{
	m_eShape = SHAPE_ELLIPSE;	
}
