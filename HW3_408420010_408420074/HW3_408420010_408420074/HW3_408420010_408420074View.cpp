
// HW3_408420010_408420074View.cpp: CHW3_408420010_408420074View 類別的實作
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "HW3_408420010_408420074.h"
#endif

#include "HW3_408420010_408420074Doc.h"
#include "HW3_408420010_408420074View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHW3_408420010_408420074View

IMPLEMENT_DYNCREATE(CHW3_408420010_408420074View, CView)

BEGIN_MESSAGE_MAP(CHW3_408420010_408420074View, CView)
	ON_COMMAND(ID_DRAW_POINT, &CHW3_408420010_408420074View::OnDrawPoint)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DRAW_LINE, &CHW3_408420010_408420074View::OnDrawLine)
	ON_COMMAND(ID_DRAW_DOTLINE, &CHW3_408420010_408420074View::OnDrawDotline)
	ON_COMMAND(ID_DRAW_ELLIPSE, &CHW3_408420010_408420074View::OnDrawEllipse)
	ON_COMMAND(ID_COLOR_MANUALCOLOR, &CHW3_408420010_408420074View::OnColorManualcolor)
	ON_COMMAND(ID_COLOR_FILLCOLOR, &CHW3_408420010_408420074View::OnColorFillcolor)
	ON_COMMAND(ID_DRAW_RECTANGLE, &CHW3_408420010_408420074View::OnDrawRectangle)
	ON_COMMAND(ID_COLOR_RED, &CHW3_408420010_408420074View::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CHW3_408420010_408420074View::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CHW3_408420010_408420074View::OnColorBlue)
	ON_COMMAND(ID_DRAW_POLYLINE, &CHW3_408420010_408420074View::OnDrawPolyline)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_DRAW_POLYGON, &CHW3_408420010_408420074View::OnDrawPolygon)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_COLOR_BACKGROUNG, &CHW3_408420010_408420074View::OnColorBackgroung)
	ON_COMMAND(ID_FILE_NWE, &CHW3_408420010_408420074View::OnFileNwe)
	ON_COMMAND(ID_FILE_OPEN, &CHW3_408420010_408420074View::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CHW3_408420010_408420074View::OnFileSave)
	ON_COMMAND(ID_FILE_SAVECVS, &CHW3_408420010_408420074View::OnFileSavecvs)
	ON_COMMAND(ID_FILE_OPENCVS, &CHW3_408420010_408420074View::OnFileOpencvs)
END_MESSAGE_MAP()

// CHW3_408420010_408420074View 建構/解構

CHW3_408420010_408420074View::CHW3_408420010_408420074View() noexcept
{
	// TODO: 在此加入建構程式碼
	LineWidth = 10;
	color = RGB(255, 0, 0);
	fcolor = RGB(0, 0, 255);
	BgColor = RGB(255, 255, 255);
}

CHW3_408420010_408420074View::~CHW3_408420010_408420074View()
{
}

BOOL CHW3_408420010_408420074View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CView::PreCreateWindow(cs);
}

// CHW3_408420010_408420074View 繪圖

void CHW3_408420010_408420074View::OnDraw(CDC* pDC)
{
	CHW3_408420010_408420074Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此加入原生資料的描繪程式碼

	int Pnum = pDoc->pArray.GetSize();
	for (int i = 0; i < Pnum; i++) {
		if (pDoc->pArray[i].Tpye == 0)
		{
			pDC->SetPixel(pDoc->pArray[i].point, pDoc->pArray[i].color);
		}
		else
		{
			pDC->Ellipse(pDoc->pArray[i].point.x - 3,
				pDoc->pArray[i].point.y - 3,
				pDoc->pArray[i].point.x + 3,
				pDoc->pArray[i].point.y + 3);
		}
	}

	int Lnum = pDoc->lArray.GetCount();
	for (int i = 0; i < Lnum; i++)
	{
		if ((pDoc->lArray.GetAt(i).Type) == 0)
		{
			CPen pen(PS_SOLID, 2, pDoc->lArray.GetAt(i).color);
			CPen *oldPen = pDC->SelectObject(&pen);
			pDoc->lArray.GetAt(i).draw2(*pDC);
		}
		else if ((pDoc->lArray.GetAt(i).Type) == 1)
		{
			CPen pen(PS_DASHDOT, 1, pDoc->lArray.GetAt(i).color);
			CPen *oldPen = pDC->SelectObject(&pen);
			pDoc->lArray.GetAt(i).drawDashDot(*pDC);
		}
		int a = pDoc->lArray.GetAt(i).Type;
	}

	int Enum = pDoc->eArray.GetCount();
	for (int i = 0; i < Enum; i++)
	{
		CPen pen(PS_SOLID, 2, pDoc->eArray.GetAt(i).color);
		CPen *oldPen = pDC->SelectObject(&pen);
		if (pDoc->eArray.GetAt(i).Filled)
		{
			// m_newbrush.CreateSolidBrush(fcolor);
			CBrush m_newbrush;
			m_newbrush.CreateHatchBrush(HS_FDIAGONAL, fcolor);
			pDC->SelectObject(&m_newbrush);
		}
		pDoc->eArray.GetAt(i).draw2(*pDC);
	}

	int Rnum = pDoc->rArray.GetCount();
	for (int i = 0; i < Rnum; i++)
	{
		CPen pen(PS_SOLID, 2, pDoc->rArray.GetAt(i).color);
		CPen *oldPen = pDC->SelectObject(&pen);
		if (pDoc->rArray.GetAt(i).Filled)
		{
			// m_newbrush.CreateSolidBrush(fcolor);
			CBrush m_newbrush;
			m_newbrush.CreateHatchBrush(HS_FDIAGONAL, fcolor);
			pDC->SelectObject(&m_newbrush);
		}
		pDoc->rArray.GetAt(i).draw2(*pDC);
	}

	int PolyNum = pDoc->polyArray.GetCount();
	for (int i = 0; i < PolyNum; i++)
	{
		CPen pen(PS_SOLID, 2, pDoc->polyArray.GetAt(i).color);
		CPen *oldPen = pDC->SelectObject(&pen);
		if (pDoc->polyArray.GetAt(i).Filled)
		{
			// m_newbrush.CreateSolidBrush(fcolor);
			CBrush m_newbrush;
			m_newbrush.CreateHatchBrush(HS_FDIAGONAL, fcolor);
			pDC->SelectObject(&m_newbrush);
		}
		pDoc->polyArray.GetAt(i).draw2(*pDC);
	}
}


// CHW3_408420010_408420074View 診斷

#ifdef _DEBUG
void CHW3_408420010_408420074View::AssertValid() const
{
	CView::AssertValid();
}

void CHW3_408420010_408420074View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHW3_408420010_408420074Doc* CHW3_408420010_408420074View::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHW3_408420010_408420074Doc)));
	return (CHW3_408420010_408420074Doc*)m_pDocument;
}
#endif //_DEBUG


// CHW3_408420010_408420074View 訊息處理常式


void CHW3_408420010_408420074View::OnDrawPoint()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = (CHW3_408420010_408420074Doc *)GetDocument();
	doc->shapeNum = 0;
	doc->Obj_Color = RGB(0, 0, 255);
	doc->P_Type = 0;
}


void CHW3_408420010_408420074View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CView::OnLButtonDown(nFlags, point);
	SetCapture();
	CHW3_408420010_408420074Doc *doc = (CHW3_408420010_408420074Doc *)GetDocument();
	doc->Obj_Color = color;
	doc->Obj_fColor = fcolor;
	if (doc->onPolygon)
	{
		CClientDC aDC(this);
		if (doc->shapeNum == 1)//for line polyline
		{
			TempLine.EndPnt = point;
			TempLine.draw2(aDC);
			TempLine.Type = 0;
			doc->lArray.Add(TempLine);
		}
		else if (doc->shapeNum == 4)//for polygon
		{
			TempPolygon.EndPnt = point;
			TempPolygon.drawTempFrame(aDC);
			//TempPolygon.pts.Add(point);	this had already done later
		}
	}

	if (doc->shapeNum == 1)//draw line start
	{
		if (doc->L_Type == 0) {//for solid line
			TempLine.StartPnt = point;
			TempLine.EndPnt = point; //設定新物件座標點
			TempLine.color = doc->Obj_Color;
			TempLine.LineWidth = LineWidth;
			TempLine.Type = 0;
		}
		else if (doc->L_Type == 1) {//for dot line
			TempLine.StartPnt = point;
			TempLine.EndPnt = point; //設定新物件座標點
			TempLine.color = doc->Obj_Color;
			TempLine.LineWidth = LineWidth;
			TempLine.Type = 1;
		}
		else if (doc->L_Type)//for poly line
		{
			doc->onPolygon = true;
			TempLine.StartPnt = point;
			TempLine.EndPnt = point; //設定新物件座標點
			TempLine.color = doc->Obj_Color;
			TempLine.LineWidth = LineWidth;
			TempLine.Type = 1;
		}
	}
	else if (doc->shapeNum == 2)//draw ellipse start
	{
		TempEllipse.StartPnt = point;
		TempEllipse.EndPnt = point; //設定新物件座標點
		TempEllipse.color = doc->Obj_Color;
		TempEllipse.fcolor = doc->Obj_fColor;
		TempEllipse.LineWidth = LineWidth;
	}
	else if (doc->shapeNum == 3)//draw erct start
	{
		TempRect.StartPnt = point;
		TempRect.EndPnt = point; //設定新物件座標點
		TempRect.color = doc->Obj_Color;
		TempRect.fcolor = doc->Obj_fColor;
		TempRect.LineWidth = LineWidth;
	}
	else if (doc->shapeNum == 4)//draw polygon start
	{
		doc->onPolygon = true;
		TempPolygon.StartPnt = point;
		TempPolygon.EndPnt = point; //設定新物件座標點
		TempPolygon.pts.Add(point);
		TempPolygon.color = doc->Obj_Color;
		TempPolygon.fcolor = doc->Obj_fColor;
		TempPolygon.LineWidth = LineWidth;
	}
}


void CHW3_408420010_408420074View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CView::OnMouseMove(nFlags, point);
	MyPoint temppoint;
	CHW3_408420010_408420074Doc *doc = (CHW3_408420010_408420074Doc *)GetDocument();
	CClientDC aDC(this);
	if (this == GetCapture())
	{

		if (doc->shapeNum == 0) //for point
		{
			if (doc->P_Type == 0)
			{
				aDC.SetPixel(point, doc->Obj_Color);
				temppoint.point = point;
				temppoint.color = doc->Obj_Color;
				temppoint.Tpye = doc->P_Type;
				doc->pArray.Add(temppoint);
			}
		}
		else if (doc->shapeNum == 1)//for line
		{
			aDC.SetROP2(R2_NOTXORPEN); //設定繪圖模式 R2_NOT R2_NOTXORPEN 
			if (doc->L_Type == 0) {//for solid line
				TempLine.draw2(aDC); //清除上一筆
				TempLine.EndPnt = point; //設定新物件座標點
				TempLine.draw2(aDC); //再畫出新形狀物

			}
			else if (doc->L_Type == 1) {//for dot line
				TempLine.drawDashDot(aDC); //清除上一筆
				TempLine.EndPnt = point; //設定新物件座標點
				TempLine.drawDashDot(aDC); //再畫出新形狀物

			}
			else if (doc->L_Type)//for poly line
			{
				//process later 
				//TempLine.draw2(aDC); //清除上一筆
				//TempLine.EndPnt = point; //設定新物件座標點
				//TempLine.draw2(aDC); //再畫出新形狀物

			}
		}
		else if (doc->shapeNum == 2)//for ellipse
		{
			aDC.SetROP2(R2_NOTXORPEN); //設定繪圖模式 R2_NOT R2_NOTXORPEN 
			TempEllipse.draw2(aDC); //清除上一筆
			TempEllipse.EndPnt = point; //設定新物件座標點
			TempEllipse.draw2(aDC); //再畫出新形狀物
		}
		else if (doc->shapeNum == 3)//for rect
		{
			aDC.SetROP2(R2_NOTXORPEN); //設定繪圖模式 R2_NOT R2_NOTXORPEN 
			TempRect.draw2(aDC); //清除上一筆
			TempRect.EndPnt = point; //設定新物件座標點
			TempRect.draw2(aDC); //再畫出新形狀物
		}
		else if (doc->shapeNum == 4)//for polygon
		{
			//process later 
		}
	}

	if (doc->onPolygon)
	{
		aDC.SetROP2(R2_NOTXORPEN); //設定繪圖模式 R2_NOT R2_NOTXORPEN 
		if (doc->shapeNum == 1)//for line
		{
			TempLine.draw2(aDC); //清除上一筆
			TempLine.EndPnt = point; //設定新物件座標點
			TempLine.draw2(aDC); //再畫出新形狀物
		}
		else if (doc->shapeNum == 4)//for polygon
		{
			TempPolygon.drawTempFrame(aDC); //清除上一筆
			TempPolygon.EndPnt = point; //設定新物件座標點
			TempPolygon.drawTempFrame(aDC); //再畫出新形狀物
		}
	}
	//for (int i = 0; i < TempPolygon.pts.GetCount(); i++) {
	//	CString s;
	//	s.Format(_T("(%d,%d)"), TempPolygon.pts[i].x, TempPolygon.pts[i].y);
	//	aDC.TextOut(100, 100+i*30, s);
	//}

}


void CHW3_408420010_408420074View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CView::OnLButtonUp(nFlags, point);
	ReleaseCapture();
	CHW3_408420010_408420074Doc *doc = (CHW3_408420010_408420074Doc *)GetDocument();
	CClientDC aDC(this);
	if (doc->shapeNum == 0) {//draw point end
		//already done in mouseOnMove
	}
	else if (doc->shapeNum == 1)//draw line end
	{
		if (doc->L_Type == 0) {//for solid line
			TempLine.EndPnt = point;
			TempLine.draw2(aDC);
			TempLine.Type = 0;
			doc->lArray.Add(TempLine);
		}
		else if (doc->L_Type == 1)//for dot line
		{
			TempLine.EndPnt = point;
			TempLine.drawDashDot(aDC);
			TempLine.Type = 1;
			doc->lArray.Add(TempLine);
		}
		else if (doc->L_Type == 2)//for poly line
		{
			//PASS
			//TempLine.EndPnt = point;
			//TempLine.drawDashDot(aDC);
			//TempLine.Type == 1;
			//doc->lArray.Add(TempLine);
		}
	}
	else if (doc->shapeNum == 2)//draw ellipse end
	{
		if (TempEllipse.Filled)
		{
			// m_newbrush.CreateSolidBrush(fcolor);
			CBrush m_newbrush;
			m_newbrush.CreateHatchBrush(HS_FDIAGONAL, fcolor);
			aDC.SelectObject(&m_newbrush);
		}
		TempEllipse.EndPnt = point;
		TempEllipse.draw2(aDC);
		doc->eArray.Add(TempEllipse);
	}
	else if (doc->shapeNum == 3)//draw rect end
	{
		if (TempEllipse.Filled)
		{
			// m_newbrush.CreateSolidBrush(fcolor);
			CBrush m_newbrush;
			m_newbrush.CreateHatchBrush(HS_FDIAGONAL, fcolor);
			aDC.SelectObject(&m_newbrush);
		}
		TempRect.EndPnt = point;
		TempRect.draw2(aDC);
		doc->rArray.Add(TempRect);
	}
	else if (doc->shapeNum == 4)//for polygon
	{
		//PASS
	}
}


void CHW3_408420010_408420074View::OnDrawLine()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	doc->shapeNum = 1;
	doc->L_Type = 0;
}


void CHW3_408420010_408420074View::OnDrawDotline()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	doc->shapeNum = 1;
	doc->L_Type = 1;
}


void CHW3_408420010_408420074View::OnDrawEllipse()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	doc->shapeNum = 2;
}


void CHW3_408420010_408420074View::OnColorManualcolor()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	CColorDialog dlgColor(color);
	if (dlgColor.DoModal() == IDOK)
	{
		color = dlgColor.GetColor();
		doc->Obj_fColor = dlgColor.GetColor();;
	}
}


void CHW3_408420010_408420074View::OnColorFillcolor()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	CColorDialog dlgColor(color);
	if (dlgColor.DoModal() == IDOK)
	{
		fcolor = dlgColor.GetColor();
		doc->Obj_fColor = dlgColor.GetColor();;
	}
}


void CHW3_408420010_408420074View::OnDrawRectangle()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	doc->shapeNum = 3;
}


void CHW3_408420010_408420074View::OnColorRed()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	doc->Obj_Color = RGB(255, 0, 0);
	color = RGB(255, 0, 0);
}


void CHW3_408420010_408420074View::OnColorGreen()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	doc->Obj_Color = RGB(0, 255, 0);
	color = RGB(0, 255, 0);
}


void CHW3_408420010_408420074View::OnColorBlue()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	doc->Obj_Color = RGB(0, 0, 255);
	color = RGB(0, 0, 255);
}


void CHW3_408420010_408420074View::OnDrawPolyline()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	doc->shapeNum = 1;
	doc->L_Type = 2;
}


void CHW3_408420010_408420074View::OnRButtonDown(UINT nFlags, CPoint point)
{
	CView::OnRButtonDown(nFlags, point);
	CHW3_408420010_408420074Doc *doc = (CHW3_408420010_408420074Doc *)GetDocument();
	CClientDC aDC(this);
	if (doc->onPolygon) {
		doc->onPolygon = false;
	}
	if (doc->shapeNum == 1)//for line
	{
		aDC.SetROP2(R2_NOTXORPEN); //設定繪圖模式 R2_NOT R2_NOTXORPEN 
		TempLine.draw2(aDC); //清除上一筆	
	}
	else if (doc->shapeNum == 4)//for polygon
	{
		aDC.SetROP2(R2_NOTXORPEN); //設定繪圖模式 R2_NOT R2_NOTXORPEN 
		TempPolygon.drawTempFrame(aDC);//清除上一筆	
		TempPolygon.draw2(aDC); //polygon stroke
		doc->polyArray.Add(TempPolygon);//save this hot born polygon
		TempPolygon.pts.RemoveAll();
	}
	Invalidate();//順便確認重繪成功

}


void CHW3_408420010_408420074View::OnDrawPolygon()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	doc->shapeNum = 4;
}


BOOL CHW3_408420010_408420074View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CRect r;
	GetClientRect(&r);
	CBrush br(BgColor);
	pDC->SelectObject(br);
	pDC->FillRect(r, &br);
	return TRUE;

	return CView::OnEraseBkgnd(pDC);
}


void CHW3_408420010_408420074View::OnColorBackgroung()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	CColorDialog dlgColor(color);
	if (dlgColor.DoModal() == IDOK)
	{
		BgColor = dlgColor.GetColor();
		doc->Obj_BgColor = dlgColor.GetColor();
		Invalidate();
	}
}


void CHW3_408420010_408420074View::OnFileNwe()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	doc->RemoveAll();
	doc->shapeNum = -1;
	Invalidate();
}

void CHW3_408420010_408420074View::OnFileOpen()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	CFileDialog Filedlgsig(TRUE, _T("DPV"), _T("MySave"), OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, _T("DPV File|*.DPV|RP Model"));
	CString filePath;
	std::ifstream filePtr;

	OnFileNwe();

	if (Filedlgsig.DoModal() != IDOK) {//FileDialog error
		MessageBox(_T("FileDialog Error!"), _T("I don't know WTF just happen"), MB_ICONSTOP);
		return;
	}
	filePath = Filedlgsig.GetPathName();
	filePtr.open(filePath, std::ios::in);//std::ios::binary |
	if (!filePtr.is_open())//open in stream error
	{
		MessageBox(_T("%s", filePath), _T("I don't know WTF just happen"), MB_ICONSTOP);
		return;
	}


	int Pnum;
	int Lnum;
	int Enum;
	int Rnum;
	int Polynum;

	filePtr.read((char*)&Pnum, sizeof(Pnum));//一段式讀取點數資料到系統
	filePtr.read((char*)&Lnum, sizeof(Lnum));//讀取線數資料到系統
	filePtr.read((char*)&Enum, sizeof(Enum));//一段式讀取點數資料到系統
	filePtr.read((char*)&Rnum, sizeof(Rnum));//一段式讀取點數資料到系統
	filePtr.read((char*)&Polynum, sizeof(Polynum));//一段式讀取點數資料到系統

	int i = 0;
	for (i = 0; i < Pnum; i++)
	{
		filePtr.read((char*)&TempPoint, sizeof(TempPoint)); //兩段式讀取資料到系統(CArray)
		doc->pArray.Add(TempPoint);
	}
	for (i = 0; i < Lnum; i++)
	{
		filePtr.read((char*)&TempLine, sizeof(TempLine)); //兩段式讀取資料到系統(CArray)
		doc->lArray.Add(TempLine);

	}
	for (i = 0; i < Enum; i++)
	{
		filePtr.read((char*)&TempEllipse, sizeof(TempEllipse)); //兩段式讀取資料到系統(CArray)
		doc->eArray.Add(TempEllipse);
	}
	for (i = 0; i < Rnum; i++)
	{
		filePtr.read((char*)&TempRect, sizeof(TempRect)); //兩段式讀取資料到系統(CArray)
		doc->rArray.Add(TempRect);
	}
	for (i = 0; i < Polynum; i++)
	{
		filePtr.read((char*)&TempPolygon, sizeof(TempPolygon)); //兩段式讀取資料到系統(CArray)
		doc->polyArray.Add(TempPolygon);
	}
	UpdateData(FALSE);
	Invalidate();

}


void CHW3_408420010_408420074View::OnFileSave()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	CFileDialog Filedlgsig(FALSE, _T("DPV"), _T("MySave"), OFN_OVERWRITEPROMPT, _T("DPV File|*.DPV|RP Model"));
	CString filePath;
	std::ofstream filePtr;
	if (Filedlgsig.DoModal() != IDOK) {//FileDialog error
		MessageBox(_T("FileDialog Error!"), _T("I don't know WTF just happen"), MB_ICONSTOP);
		return;
	}
	filePath = Filedlgsig.GetPathName();
	filePtr.open(filePath, std::ios::out);
	if (!filePtr.is_open())//open out stream error
	{
		MessageBox(_T("%s", filePath), _T("I don't know WTF just happen"), MB_ICONSTOP);
		return;
	}
	int Pnum = doc->pArray.GetSize();
	int Lnum = doc->lArray.GetSize();
	int Enum = doc->eArray.GetSize();
	int Rnum = doc->rArray.GetSize();
	int Polynum = doc->polyArray.GetSize();

	filePtr.write((char*)&Pnum, sizeof(Pnum));//寫出點數到檔案
	filePtr.write((char*)&Lnum, sizeof(Lnum));//寫出線數到檔案
	filePtr.write((char*)&Enum, sizeof(Enum));//寫出線數到檔案
	filePtr.write((char*)&Rnum, sizeof(Rnum));//寫出線數到檔案
	filePtr.write((char*)&Polynum, sizeof(Polynum));//寫出線數到檔案

	int i = 0;
	for (i = 0; i < Pnum; i++)
	{
		filePtr.write((char*)&doc->pArray[i], sizeof(doc->pArray[i]));//寫出點資料到檔案
	}
	for (i = 0; i < Lnum; i++)
	{
		filePtr.write((char*)&doc->lArray[i], sizeof(doc->lArray[i])); //寫出資料到檔案
	}
	for (i = 0; i < Enum; i++)
	{
		filePtr.write((char*)&doc->eArray[i], sizeof(doc->eArray[i])); //寫出資料到檔案
	}
	for (i = 0; i < Rnum; i++)
	{
		filePtr.write((char*)&doc->rArray[i], sizeof(doc->rArray[i])); //寫出資料到檔案
	}
	for (i = 0; i < Polynum; i++)
	{
		filePtr.write((char*)&doc->polyArray[i], sizeof(doc->polyArray[i])); //寫出資料到檔案
	}
	filePtr.close();
}


void CHW3_408420010_408420074View::OnFileSavecvs()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	CString filestring, filestring2;
	int i;

	CFileDialog Filedlgsig(FALSE, "CSV", "MyCsv", OFN_HIDEREADONLY, "CSV File | *.CSV");
	if (Filedlgsig.DoModal() != IDOK) {//FileDialog error
		MessageBox(_T("FileDialog Error!"), _T("I don't know WTF just happen"), MB_ICONSTOP);
		return;
	}

	filestring = Filedlgsig.GetPathName();
	errno_t err;
	FILE *fp;
	if ((err = fopen_s(&fp, filestring, "w")) != 0) //開啟存檔
	{
		MessageBox("File Save Error.", " Save Error", MB_ICONSTOP);
		return;
	}

	int Pnum = doc->pArray.GetSize();
	int Lnum = doc->lArray.GetSize();
	int Enum = doc->eArray.GetSize();
	int Rnum = doc->rArray.GetSize();
	int Polynum = doc->polyArray.GetSize();

	fprintf(fp, "點數,%d\n", Pnum);
	for (i = 0; i < Pnum; i++)
	{
		int CR = GetRValue(doc->pArray[i].color);
		int CB = GetBValue(doc->pArray[i].color);
		int CG = GetGValue(doc->pArray[i].color);
		fprintf(fp, "%d,%d,%d,%d,%d\n",
			doc->pArray[i].point.x, doc->pArray[i].point.y,
			CR, CG, CB);
	}

	fprintf(fp, "線數,%d\n", Lnum);
	for (i = 0; i < Lnum; i++)
	{
		int CR = GetRValue(doc->lArray[i].color);
		int CB = GetBValue(doc->lArray[i].color);
		int CG = GetGValue(doc->lArray[i].color);
		fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
			doc->lArray[i].StartPnt.x, doc->lArray[i].StartPnt.y,
			doc->lArray[i].EndPnt.x, doc->lArray[i].EndPnt.y,
			doc->lArray[i].LineWidth, doc->lArray[i].Type,
			CR, CG, CB);
	}

	fprintf(fp, "橢圓數,%d\n", Enum);
	for (i = 0; i < Enum; i++)
	{
		int CR = GetRValue(doc->eArray[i].color);
		int CG = GetGValue(doc->eArray[i].color);
		int CB = GetBValue(doc->eArray[i].color);
		int fCR = GetRValue(doc->eArray[i].fcolor);
		int fCG = GetGValue(doc->eArray[i].fcolor);
		int fCB = GetBValue(doc->eArray[i].fcolor);
		fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
			doc->eArray[i].StartPnt.x, doc->eArray[i].StartPnt.y,
			doc->eArray[i].EndPnt.x, doc->eArray[i].EndPnt.y,
			doc->eArray[i].LineWidth, doc->eArray[i].Filled,
			CR, CG, CB, fCR, fCG, fCB);
	}

	fprintf(fp, "四方形數,%d\n", Rnum);
	for (i = 0; i < Rnum; i++)
	{
		int CR = GetRValue(doc->rArray[i].color);
		int CG = GetGValue(doc->rArray[i].color);
		int CB = GetBValue(doc->rArray[i].color);
		int fCR = GetRValue(doc->rArray[i].fcolor);
		int fCG = GetGValue(doc->rArray[i].fcolor);
		int fCB = GetBValue(doc->rArray[i].fcolor);
		fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
			doc->rArray[i].StartPnt.x, doc->rArray[i].StartPnt.y,
			doc->rArray[i].EndPnt.x, doc->rArray[i].EndPnt.y,
			doc->rArray[i].LineWidth, doc->rArray[i].Filled,
			CR, CG, CB, fCR, fCG, fCB);
	}

	fprintf(fp, "多邊形數,%d\n", Polynum);
	for (i = 0; i < Polynum; i++)
	{
		int CR = GetRValue(doc->polyArray[i].color);
		int CG = GetGValue(doc->polyArray[i].color);
		int CB = GetBValue(doc->polyArray[i].color);
		int fCR = GetRValue(doc->polyArray[i].fcolor);
		int fCG = GetGValue(doc->polyArray[i].fcolor);
		int fCB = GetBValue(doc->polyArray[i].fcolor);
		fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d\n",
			doc->polyArray[i].LineWidth, doc->polyArray[i].Filled,
			CR, CG, CB, fCR, fCG, fCB);
		//output all points
		CArray<CPoint, CPoint &> &points = doc->polyArray[i].pts;
		int ptsNum = points.GetCount();
		fprintf(fp, "points,%d\n", ptsNum);
		for (int j = 0; j < ptsNum; j++) {
			fprintf(fp, "%d,%d\n",
				points[j].x, points[j].y);
		}
	}

	fclose(fp);
}


void CHW3_408420010_408420074View::OnFileOpencvs()
{
	// TODO: 在此加入您的命令處理常式程式碼
	CHW3_408420010_408420074Doc *doc = GetDocument();
	CString filestring, filestring2;

	OnFileNwe();

	CFileDialog Filedlgsig(TRUE, _T("CSV"), _T("MyCsv"), OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY, _T("CSV File|*.CSV"));
	if (Filedlgsig.DoModal() != IDOK) {//FileDialog error
		MessageBox(_T("FileDialog Error!"), _T("I don't know WTF just happen"), MB_ICONSTOP);
		return;
	}

	filestring = Filedlgsig.GetPathName();
	errno_t err;
	FILE *fp;
	if ((err = fopen_s(&fp, filestring, "r")) != 0) //開啟存檔
	{
		MessageBox("File Save Error.", " Save Error", MB_ICONSTOP);
		return;
	}

	char gettring[600] = { '\0' };
	char *ptr, *temp;
	const char* del = ",\n";
	int i = 0;
	int CR, CG, CB, fCR, fCG, fCB;

	fseek(fp, 0, SEEK_SET);
	
	fgets(gettring, 500, fp);//點數,0
	ptr = strtok_s(gettring, del, &temp);//0
	ptr = strtok_s(NULL, del, &temp);//null

	int Pnum = atoi(ptr);
	for (i = 0; i < Pnum; i++)
	{
		fgets(gettring, 500, fp);//x,y,R,G,B
		ptr = strtok_s(gettring, del, &temp);//y,R,G,B
		TempPoint.point.x = atoi(ptr);//x
		ptr = strtok_s(NULL, del, &temp);//R,G,B
		TempPoint.point.y = atoi(ptr);//y
		ptr = strtok_s(NULL, del, &temp);//G,B
		CR = atoi(ptr);//R
		ptr = strtok_s(NULL, del, &temp);//B
		CG = atoi(ptr);//G
		ptr = strtok_s(NULL, del, &temp);//null
		CB = atoi(ptr);//B
		TempPoint.color = RGB(CR, CG, CB);
		doc->pArray.Add(TempPoint);
	}

	fgets(gettring, 500, fp);//線數,4
	ptr = strtok_s(gettring, del, &temp);//4
	ptr = strtok_s(NULL, del, &temp);//null

	int Lnum = atoi(ptr);
	for (i = 0; i < Lnum; i++) {
		fgets(gettring, 500, fp);//startX,startY,endX,endY, Lwidth, type, R, G, B
		ptr = strtok_s(gettring, del, &temp);//startY, endX, endY, Lwidth, type, R, G, B
		TempLine.StartPnt.x = atoi(ptr);//startX
		ptr = strtok_s(NULL, del, &temp);//endX, endY, Lwidth, type, R, G, B
		TempLine.StartPnt.y = atoi(ptr);//startY
		ptr = strtok_s(NULL, del, &temp);//endY, Lwidth, type, R, G, B
		TempLine.EndPnt.x = atoi(ptr);//endX
		ptr = strtok_s(NULL, del, &temp);//Lwidth, type, R, G, B
		TempLine.EndPnt.y = atoi(ptr);//endY
		ptr = strtok_s(NULL, del, &temp);//type, R, G, B
		TempLine.LineWidth = atoi(ptr);//Lwidth
		ptr = strtok_s(NULL, del, &temp);//R, G, B
		TempLine.Type = atoi(ptr);//type
		ptr = strtok_s(NULL, del, &temp);//G,B
		CR = atoi(ptr);//R
		ptr = strtok_s(NULL, del, &temp);//B
		CG = atoi(ptr);//G
		ptr = strtok_s(NULL, del, &temp);//null
		CB = atoi(ptr);//B
		TempLine.color = RGB(CR, CG, CB);
		doc->lArray.Add(TempLine);
	}

	fgets(gettring, 500, fp);//橢圓數,2
	ptr = strtok_s(gettring, del, &temp);//2
	ptr = strtok_s(NULL, del, &temp);//null

	int Enum = atoi(ptr);
	for (i = 0; i < Enum; i++)
	{
		fgets(gettring, 500, fp);//startX, startY,endX,endY, Lwidth, filled, R, G, B, fR, fG,fB
		ptr = strtok_s(gettring, del, &temp);//startY,endX,endY, Lwidth, filled, R, G, B, fR, fG,fB
		TempEllipse.StartPnt.x = atoi(ptr);//startX
		ptr = strtok_s(NULL, del, &temp);//endX,endY, Lwidth, filled, R, G, B, fR, fG,fB
		TempEllipse.StartPnt.y = atoi(ptr);//startY
		ptr = strtok_s(NULL, del, &temp);//endY, Lwidth, filled, R, G, B, fR, fG,fB
		TempEllipse.EndPnt.x = atoi(ptr);//endX
		ptr = strtok_s(NULL, del, &temp);//Lwidth, filled, R, G, B, fR, fG,fB
		TempEllipse.EndPnt.y = atoi(ptr);//endY
		ptr = strtok_s(NULL, del, &temp);//filled, R, G, B, fR, fG,fB
		TempEllipse.LineWidth = atoi(ptr);//Lwidth
		ptr = strtok_s(NULL, del, &temp);//R, G, B, fR, fG,fB
		TempEllipse.Filled = atoi(ptr);//filled
		ptr = strtok_s(NULL, del, &temp);//G, B, fR, fG,fB
		CR = atoi(ptr);//R
		ptr = strtok_s(NULL, del, &temp);//B, fR, fG,fB
		CG = atoi(ptr);//G
		ptr = strtok_s(NULL, del, &temp);//fR, fG,fB
		CB = atoi(ptr);//B
		ptr = strtok_s(NULL, del, &temp);//fG,fB
		fCR = atoi(ptr);//fR
		ptr = strtok_s(NULL, del, &temp);//fB
		fCG = atoi(ptr);//fG
		ptr = strtok_s(NULL, del, &temp);//null
		fCB = atoi(ptr);//fB
		TempEllipse.color = RGB(CR, CG, CB);
		TempEllipse.fcolor = RGB(fCR, fCG, fCB);
		doc->eArray.Add(TempEllipse);
	}

	fgets(gettring, 500, fp);//四方形數,2
	ptr = strtok_s(gettring, del, &temp);//2
	ptr = strtok_s(NULL, del, &temp);//null

	int Rnum = atoi(ptr);
	for (i = 0; i < Rnum; i++)
	{
		fgets(gettring, 500, fp);//startX, startY,endX,endY, Lwidth, filled, R, G, B, fR, fG,fB
		ptr = strtok_s(gettring, del, &temp);//startY,endX,endY, Lwidth, filled, R, G, B, fR, fG,fB
		TempRect.StartPnt.x = atoi(ptr);//startX
		ptr = strtok_s(NULL, del, &temp);//endX,endY, Lwidth, filled, R, G, B, fR, fG,fB
		TempRect.StartPnt.y = atoi(ptr);//startY
		ptr = strtok_s(NULL, del, &temp);//endY, Lwidth, filled, R, G, B, fR, fG,fB
		TempRect.EndPnt.x = atoi(ptr);//endX
		ptr = strtok_s(NULL, del, &temp);//Lwidth, filled, R, G, B, fR, fG,fB
		TempRect.EndPnt.y = atoi(ptr);//endY
		ptr = strtok_s(NULL, del, &temp);//filled, R, G, B, fR, fG,fB
		TempRect.LineWidth = atoi(ptr);//Lwidth
		ptr = strtok_s(NULL, del, &temp);//R, G, B, fR, fG,fB
		TempRect.Filled = atoi(ptr);//filled
		ptr = strtok_s(NULL, del, &temp);//G, B, fR, fG,fB
		CR = atoi(ptr);//R
		ptr = strtok_s(NULL, del, &temp);//B, fR, fG,fB
		CG = atoi(ptr);//G
		ptr = strtok_s(NULL, del, &temp);//fR, fG,fB
		CB = atoi(ptr);//B
		ptr = strtok_s(NULL, del, &temp);//fG,fB
		fCR = atoi(ptr);//fR
		ptr = strtok_s(NULL, del, &temp);//fB
		fCG = atoi(ptr);//fG
		ptr = strtok_s(NULL, del, &temp);//null
		fCB = atoi(ptr);//fB
		TempRect.color = RGB(CR, CG, CB);
		TempRect.fcolor = RGB(fCR, fCG, fCB);
		doc->rArray.Add(TempRect);
	}

	CPoint tPoint;
	fgets(gettring, 500, fp);//多邊形數,2
	ptr = strtok_s(gettring, del, &temp);//2
	ptr = strtok_s(NULL, del, &temp);//null

	int Polynum = atoi(ptr);
	for (i = 0; i < Polynum; i++)
	{
		fgets(gettring, 500, fp);//Width, filled, R, G, B, fR, fG, fB
		ptr = strtok_s(gettring, del, &temp);//filled, R, G, B, fR, fG, fB
		TempPolygon.LineWidth = atoi(ptr);//Width
		ptr = strtok_s(NULL, del, &temp);//R, G, B, fR, fG, fB
		TempPolygon.Filled = atoi(ptr);//filled
		ptr = strtok_s(NULL, del, &temp);//G, B, fR, fG, fB
		CR = atoi(ptr);//R
		ptr = strtok_s(NULL, del, &temp);//B, fR, fG, fB
		CG = atoi(ptr);//G
		ptr = strtok_s(NULL, del, &temp);//fR, fG, fB
		CB = atoi(ptr);//B
		ptr = strtok_s(NULL, del, &temp);//fG, fB
		fCR = atoi(ptr);//fR
		ptr = strtok_s(NULL, del, &temp);//fB
		fCG = atoi(ptr);//fG
		ptr = strtok_s(NULL, del, &temp);//null
		fCB = atoi(ptr);//fB
		TempPolygon.color = RGB(CR, CG, CB);

		fgets(gettring, 500, fp);//points,6
		ptr = strtok_s(gettring, del, &temp);//6
		ptr = strtok_s(NULL, del, &temp);//null
		int ptsNum = atoi(ptr);//6
		for (int j = 0; j < ptsNum; j++) 
		{
			TempPolygon.pts.RemoveAll();//clear point array prevent extra points get
			fgets(gettring, 500, fp);//x, y
			ptr = strtok_s(gettring, del, &temp);//y
			tPoint.x = atoi(ptr);//x
			ptr = strtok_s(NULL, del, &temp);//null
			tPoint.y = atoi(ptr);//y
			TempPolygon.pts.Add(tPoint);
		}
	}

	UpdateData(FALSE);
	Invalidate();
}
