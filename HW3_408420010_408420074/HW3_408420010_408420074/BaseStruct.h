#pragma once
#include "framework.h"

class Shape //形狀類別的基礎類別
{
public:
	CPoint StartPnt, EndPnt, Prepoint; //定義形狀的終點與起點
	BOOL Draw1;
	int LineWidth;
	int shapenum; //形狀代號
	COLORREF color;
public:
	//建構子
	Shape() {}
	//過載=運算子
	Shape & operator= (Shape & s)
	{
		StartPnt = s.StartPnt; //設定起點
		EndPnt = s.EndPnt; //設定終點
		return *this;
	}
	virtual void draw(CDC & aDC, COLORREF color, COLORREF fcolor, int width, BOOL Filled = false) = 0;
	int GetShapeNum() //取得形狀代號
	{
		return shapenum;
	}
	void SetPoint(CPoint SPnt, CPoint EPnt) //設定形狀的起點、終點
	{
		StartPnt = SPnt;
		EndPnt = EPnt;
	}
};

class MyPoint
{
public:
	CPoint point;
	COLORREF color;
	int Tpye;
	MyPoint()
	{
		color = RGB(0, 0, 255);
		point = (0, 0);
		Tpye = 0; //系統點總類 0:點 1:圓點
	}
};


class MyLine : public Shape//直線類別
{
public:
	int Type;//0:直線 1:DotLine 2:PolyLine
	MyLine()
	{
		color = RGB(255, 0, 0);
		shapenum = 1;
		StartPnt = (0, 0);
	}
	//建構子
	MyLine(CPoint StartPnt2, CPoint EndPnt2, COLORREF color2)
	{
		color = color2;
		shapenum = 2;
		StartPnt = StartPnt2;
		EndPnt = EndPnt2;
	}
	//過載= 運算子
	MyLine & operator= (MyLine & l)
	{
		StartPnt = l.StartPnt;
		color = l.color;
		LineWidth = l.LineWidth;
		EndPnt = l.EndPnt;
		shapenum = l.shapenum;
		Type = l.Type;
		return *this;
	}
	void draw(CDC &dc, COLORREF Lcolor, COLORREF fcolor, int Lwidth, BOOL Filled = false)
	{
		CPen pen(PS_SOLID, Lwidth, Lcolor);//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
		dc.MoveTo(StartPnt);//移至直線起點
		dc.LineTo(EndPnt);//移至直線終點
		dc.SelectObject(oldPen);//還原選取的畫筆物件
	}
	void draw2(CDC &dc)
	{
		CPen pen(PS_SOLID, LineWidth, color);//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
		dc.MoveTo(StartPnt);//移至直線起點
		dc.LineTo(EndPnt);//移至直線終點
		dc.SelectObject(oldPen);//還原選取的畫筆物件
	}
	void draw3(CDC &dc)
	{
		CPen pen(PS_SOLID, LineWidth, RGB(0, 0, 0));//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
		dc.MoveTo(StartPnt);//移至直線起點
		dc.LineTo(EndPnt);//移至直線終點
		dc.SelectObject(oldPen);//還原選取的畫筆物件
	}
	void drawDashDot(CDC &dc)
	{
		CPen Center_Line_Pen(PS_DASHDOT, 1, color);//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&Center_Line_Pen);//設定DC物件使用pen物件
		dc.MoveTo(StartPnt);//移至直線起點
		dc.LineTo(EndPnt);//移至直線終點
		dc.SelectObject(oldPen);//還原選取的畫筆物件
	}
};

class MyEllipse : public Shape//橢圓形類別
{
public:
	BOOL Filled;
	COLORREF fcolor;
	MyEllipse()
	{
		color = RGB(0, 255, 0);
		fcolor = RGB(0, 0, 255);
		shapenum = 2;
		StartPnt = (0, 0);
		Filled = 1;
	}
	MyEllipse(CPoint StartPnt2, CPoint
		EndPnt2, COLORREF color2)
	{
		color = color2;
		shapenum = 2;
		StartPnt = StartPnt2;
		EndPnt = EndPnt2;
	}
	//過載= 運算子
	MyEllipse & operator= (MyEllipse & l)//過載= 運算子
	{
		Filled = l.Filled;
		fcolor = l.fcolor;
		StartPnt = l.StartPnt;
		color = l.color;
		LineWidth = l.LineWidth;
		EndPnt = l.EndPnt;
		shapenum = l.shapenum;
		return *this;
	}
	void draw(CDC & dc, COLORREF color, COLORREF fcolor, int width, BOOL Filled = false)
	{
		CRect rect(StartPnt, EndPnt);//建立CRect物件
		CBrush m_newbrush;
		CPen pen(PS_SOLID, width, color);//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(RGB(0, 255, 255));
			// m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//設定DC物件不使用畫筆
		}
		dc.Ellipse(rect);//繪出矩形
		dc.SelectObject(oldPen);//還原畫筆物件
		//m_newbrush.DeleteObject();
	}
	void draw2(CDC & dc)
	{
		CRect rect(StartPnt, EndPnt);//建立CRect物件
		CBrush m_newbrush;
		CPen pen(PS_SOLID, LineWidth, color);//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(fcolor);
			//m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//設定DC物件不使用畫筆
		}
		dc.Ellipse(rect);//繪出矩形
		dc.SelectObject(oldPen);//還原畫筆物件
		//m_newbrush.DeleteObject();
	}
};
//rect
class MyRect : public Shape//橢圓形類別
{
public:
	BOOL Filled;
	COLORREF fcolor;
	MyRect()
	{
		color = RGB(0, 255, 0);
		fcolor = RGB(0, 0, 255);
		shapenum = 3;
		StartPnt = (0, 0);
		Filled = 1;
	}
	MyRect(CPoint StartPnt2, CPoint
		EndPnt2, COLORREF color2)
	{
		color = color2;
		shapenum = 2;
		StartPnt = StartPnt2;
		EndPnt = EndPnt2;
	}
	//過載= 運算子
	MyRect & operator= (MyRect & l)//過載= 運算子
	{
		Filled = l.Filled;
		fcolor = l.fcolor;
		StartPnt = l.StartPnt;
		color = l.color;
		LineWidth = l.LineWidth;
		EndPnt = l.EndPnt;
		shapenum = l.shapenum;
		return *this;
	}
	void draw(CDC & dc, COLORREF color, COLORREF fcolor, int width, BOOL Filled = false)
	{
		CRect rect(StartPnt, EndPnt);//建立CRect物件
		CBrush m_newbrush;
		CPen pen(PS_SOLID, width, color);//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(RGB(0, 255, 255));
			// m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//設定DC物件不使用畫筆
		}
		dc.Rectangle(rect);//繪出矩形
		dc.SelectObject(oldPen);//還原畫筆物件
		//m_newbrush.DeleteObject();
	}
	void draw2(CDC & dc)
	{
		CRect rect(StartPnt, EndPnt);//建立CRect物件
		CBrush m_newbrush;
		CPen pen(PS_SOLID, LineWidth, color);//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(fcolor);
			//m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//設定DC物件不使用畫筆
		}
		dc.Rectangle(rect);//繪出矩形
		dc.SelectObject(oldPen);//還原畫筆物件
		//m_newbrush.DeleteObject();
	}
};

class MyPolygon : public Shape
{
public:
	CArray<CPoint, CPoint &> pts;
	BOOL Filled;
	COLORREF fcolor;
	//only init color fillColor and set shapenum
	MyPolygon()
	{
		color = RGB(0, 255, 0);
		fcolor = RGB(0, 0, 255);
		shapenum = 4;
		Filled = 1;
	}
	MyPolygon & operator=(MyPolygon &l)
	{
		Filled = l.Filled;
		fcolor = l.fcolor;
		color = l.color;
		pts.Copy(l.pts);
		LineWidth = l.LineWidth;
		shapenum = l.shapenum;
		return *this;
	}
	void draw(CDC & dc, COLORREF color, COLORREF fcolor, int width, BOOL Filled = false)
	{
		CBrush m_newbrush;
		CPen pen(PS_SOLID, width, color);//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(RGB(0, 255, 255));
			// m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//設定DC物件不使用畫筆
		}
		dc.Polygon(pts.GetData(), pts.GetCount());//繪出多邊形
		dc.SelectObject(oldPen);//還原畫筆物件
		//m_newbrush.DeleteObject();
	}
	void draw2(CDC & dc)
	{
		CBrush m_newbrush;
		CPen pen(PS_SOLID, LineWidth, color);//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(fcolor);
			//m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//設定DC物件不使用畫筆
		}
		dc.Polygon(pts.GetData(), pts.GetCount());//繪出多邊形
		dc.SelectObject(oldPen);//還原畫筆物件
		//m_newbrush.DeleteObject();
	}
	void drawTempFrame(CDC & dc)
	{
		CPen pen(PS_SOLID, LineWidth, color);//建立畫筆物件
		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
		dc.MoveTo(StartPnt);//移至直線起點
		dc.LineTo(EndPnt);//移至直線終點
		dc.SelectObject(oldPen);//還原選取的畫筆物件
	}
};

//class MyLine
//{
//public:
//	CPoint StartPnt, EndPnt, Prepoint;
//	COLORREF color;
//	int LineWidth;
//	int Type;
//	MyLine()
//	{
//		color = RGB(255, 0, 0);
//		StartPnt = (0, 0);
//		LineWidth = 3;
//		Type = 0;
//	}
//	void draw(CDC &dc, COLORREF Lcolor, COLORREF fcolor, int Lwidth, BOOL Filled = false)
//	{
//		CPen pen(PS_SOLID, Lwidth, Lcolor);//建立畫筆物件
//		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
//		dc.MoveTo(StartPnt);//移至直線起點
//		dc.LineTo(EndPnt);//移至直線終點
//		dc.SelectObject(oldPen);//還原選取的畫筆物件
//	}
//	void draw2(CDC &dc)
//	{
//		CPen pen(PS_SOLID, LineWidth, color);//建立畫筆物件
//		CPen *oldPen = dc.SelectObject(&pen);//設定DC物件使用pen物件
//		dc.MoveTo(StartPnt);//移至直線起點
//		dc.LineTo(EndPnt);//移至直線終點
//		dc.SelectObject(oldPen);//還原選取的畫筆物件
//	}
//	void drawDashDot(CDC &dc)
//	{
//		CPen Center_Line_Pen(PS_DASHDOT, 1, color);//建立畫筆物件
//		CPen *oldPen = dc.SelectObject(&Center_Line_Pen);//設定DC物件使用pen物件
//		dc.MoveTo(StartPnt);//移至直線起點
//		dc.LineTo(EndPnt);//移至直線終點
//		dc.SelectObject(oldPen);//還原選取的畫筆物件
//	}
//};