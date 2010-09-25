
// Direct2DGeometrySampleView.h : interface of the CDirect2DGeometrySampleView class
//

#pragma once

class Direct2DHandler;
enum SHAPE
{
	SHAPE_RECT,
	SHAPE_RRECT,
	SHAPE_ELLIPSE
};

class CDirect2DGeometrySampleView : public CView
{
protected: // create from serialization only
	CDirect2DGeometrySampleView();
	DECLARE_DYNCREATE(CDirect2DGeometrySampleView)

// Attributes
public:
	CDirect2DGeometrySampleDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CDirect2DGeometrySampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	Direct2DHandler* m_pRender;
	SHAPE m_eShape;
	CPoint m_ptBeg;
	CPoint m_ptEnd;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnShapeRrect();
	afx_msg void OnShapeRectangle();
	afx_msg void OnShapeEllipse();
};

#ifndef _DEBUG  // debug version in Direct2DGeometrySampleView.cpp
inline CDirect2DGeometrySampleDoc* CDirect2DGeometrySampleView::GetDocument() const
   { return reinterpret_cast<CDirect2DGeometrySampleDoc*>(m_pDocument); }
#endif

