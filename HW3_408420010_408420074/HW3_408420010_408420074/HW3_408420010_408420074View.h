
// HW3_408420010_408420074View.h: CHW3_408420010_408420074View 類別的介面
//

#pragma once


class CHW3_408420010_408420074View : public CView
{
protected: // 僅從序列化建立
	CHW3_408420010_408420074View() noexcept;
	DECLARE_DYNCREATE(CHW3_408420010_408420074View)

// 屬性
public:
	CHW3_408420010_408420074Doc* GetDocument() const;
	int LineWidth;
	MyPoint TempPoint;
	MyLine TempLine;
	MyEllipse TempEllipse;
	MyRect TempRect;
	MyPolygon TempPolygon;
	COLORREF color = RGB(255, 0, 0);
	COLORREF fcolor = RGB(0, 0, 255);
	COLORREF BgColor = RGB(255, 255, 255);

// 作業
public:

// 覆寫
public:
	virtual void OnDraw(CDC* pDC);  // 覆寫以描繪此檢視
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 程式碼實作
public:
	virtual ~CHW3_408420010_408420074View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawPoint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDrawLine();
	afx_msg void OnDrawDotline();
	afx_msg void OnDrawEllipse();
	afx_msg void OnColorManualcolor();
	afx_msg void OnColorFillcolor();
	afx_msg void OnDrawRectangle();
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();
	afx_msg void OnDrawPolyline();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawPolygon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnColorBackgroung();
	afx_msg void OnFileNwe();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSavecvs();
	afx_msg void OnFileOpencvs();
};

#ifndef _DEBUG  // 對 HW3_408420010_408420074View.cpp 中的版本進行偵錯
inline CHW3_408420010_408420074Doc* CHW3_408420010_408420074View::GetDocument() const
   { return reinterpret_cast<CHW3_408420010_408420074Doc*>(m_pDocument); }
#endif

