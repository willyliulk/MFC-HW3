#pragma once
#include "framework.h"

class Shape //�Ϊ����O����¦���O
{
public:
	CPoint StartPnt, EndPnt, Prepoint; //�w�q�Ϊ������I�P�_�I
	BOOL Draw1;
	int LineWidth;
	int shapenum; //�Ϊ��N��
	COLORREF color;
public:
	//�غc�l
	Shape() {}
	//�L��=�B��l
	Shape & operator= (Shape & s)
	{
		StartPnt = s.StartPnt; //�]�w�_�I
		EndPnt = s.EndPnt; //�]�w���I
		return *this;
	}
	virtual void draw(CDC & aDC, COLORREF color, COLORREF fcolor, int width, BOOL Filled = false) = 0;
	int GetShapeNum() //���o�Ϊ��N��
	{
		return shapenum;
	}
	void SetPoint(CPoint SPnt, CPoint EPnt) //�]�w�Ϊ����_�I�B���I
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
		Tpye = 0; //�t���I�`�� 0:�I 1:���I
	}
};


class MyLine : public Shape//���u���O
{
public:
	int Type;//0:���u 1:DotLine 2:PolyLine
	MyLine()
	{
		color = RGB(255, 0, 0);
		shapenum = 1;
		StartPnt = (0, 0);
	}
	//�غc�l
	MyLine(CPoint StartPnt2, CPoint EndPnt2, COLORREF color2)
	{
		color = color2;
		shapenum = 2;
		StartPnt = StartPnt2;
		EndPnt = EndPnt2;
	}
	//�L��= �B��l
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
		CPen pen(PS_SOLID, Lwidth, Lcolor);//�إߵe������
		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
		dc.MoveTo(StartPnt);//���ܪ��u�_�I
		dc.LineTo(EndPnt);//���ܪ��u���I
		dc.SelectObject(oldPen);//�٭������e������
	}
	void draw2(CDC &dc)
	{
		CPen pen(PS_SOLID, LineWidth, color);//�إߵe������
		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
		dc.MoveTo(StartPnt);//���ܪ��u�_�I
		dc.LineTo(EndPnt);//���ܪ��u���I
		dc.SelectObject(oldPen);//�٭������e������
	}
	void draw3(CDC &dc)
	{
		CPen pen(PS_SOLID, LineWidth, RGB(0, 0, 0));//�إߵe������
		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
		dc.MoveTo(StartPnt);//���ܪ��u�_�I
		dc.LineTo(EndPnt);//���ܪ��u���I
		dc.SelectObject(oldPen);//�٭������e������
	}
	void drawDashDot(CDC &dc)
	{
		CPen Center_Line_Pen(PS_DASHDOT, 1, color);//�إߵe������
		CPen *oldPen = dc.SelectObject(&Center_Line_Pen);//�]�wDC����ϥ�pen����
		dc.MoveTo(StartPnt);//���ܪ��u�_�I
		dc.LineTo(EndPnt);//���ܪ��u���I
		dc.SelectObject(oldPen);//�٭������e������
	}
};

class MyEllipse : public Shape//�������O
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
	//�L��= �B��l
	MyEllipse & operator= (MyEllipse & l)//�L��= �B��l
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
		CRect rect(StartPnt, EndPnt);//�إ�CRect����
		CBrush m_newbrush;
		CPen pen(PS_SOLID, width, color);//�إߵe������
		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(RGB(0, 255, 255));
			// m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//�]�wDC���󤣨ϥεe��
		}
		dc.Ellipse(rect);//ø�X�x��
		dc.SelectObject(oldPen);//�٭�e������
		//m_newbrush.DeleteObject();
	}
	void draw2(CDC & dc)
	{
		CRect rect(StartPnt, EndPnt);//�إ�CRect����
		CBrush m_newbrush;
		CPen pen(PS_SOLID, LineWidth, color);//�إߵe������
		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(fcolor);
			//m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//�]�wDC���󤣨ϥεe��
		}
		dc.Ellipse(rect);//ø�X�x��
		dc.SelectObject(oldPen);//�٭�e������
		//m_newbrush.DeleteObject();
	}
};
//rect
class MyRect : public Shape//�������O
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
	//�L��= �B��l
	MyRect & operator= (MyRect & l)//�L��= �B��l
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
		CRect rect(StartPnt, EndPnt);//�إ�CRect����
		CBrush m_newbrush;
		CPen pen(PS_SOLID, width, color);//�إߵe������
		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(RGB(0, 255, 255));
			// m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//�]�wDC���󤣨ϥεe��
		}
		dc.Rectangle(rect);//ø�X�x��
		dc.SelectObject(oldPen);//�٭�e������
		//m_newbrush.DeleteObject();
	}
	void draw2(CDC & dc)
	{
		CRect rect(StartPnt, EndPnt);//�إ�CRect����
		CBrush m_newbrush;
		CPen pen(PS_SOLID, LineWidth, color);//�إߵe������
		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(fcolor);
			//m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//�]�wDC���󤣨ϥεe��
		}
		dc.Rectangle(rect);//ø�X�x��
		dc.SelectObject(oldPen);//�٭�e������
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
		CPen pen(PS_SOLID, width, color);//�إߵe������
		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(RGB(0, 255, 255));
			// m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//�]�wDC���󤣨ϥεe��
		}
		dc.Polygon(pts.GetData(), pts.GetCount());//ø�X�h���
		dc.SelectObject(oldPen);//�٭�e������
		//m_newbrush.DeleteObject();
	}
	void draw2(CDC & dc)
	{
		CBrush m_newbrush;
		CPen pen(PS_SOLID, LineWidth, color);//�إߵe������
		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
		if (Filled)
		{
			m_newbrush.CreateSolidBrush(fcolor);
			//m_newbrush.CreateHatchBrush(HS_FDIAGONAL,RGB(0,55,55));
			dc.SelectObject(&m_newbrush);
		}
		else
		{
			dc.SelectStockObject(NULL_BRUSH);//�]�wDC���󤣨ϥεe��
		}
		dc.Polygon(pts.GetData(), pts.GetCount());//ø�X�h���
		dc.SelectObject(oldPen);//�٭�e������
		//m_newbrush.DeleteObject();
	}
	void drawTempFrame(CDC & dc)
	{
		CPen pen(PS_SOLID, LineWidth, color);//�إߵe������
		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
		dc.MoveTo(StartPnt);//���ܪ��u�_�I
		dc.LineTo(EndPnt);//���ܪ��u���I
		dc.SelectObject(oldPen);//�٭������e������
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
//		CPen pen(PS_SOLID, Lwidth, Lcolor);//�إߵe������
//		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
//		dc.MoveTo(StartPnt);//���ܪ��u�_�I
//		dc.LineTo(EndPnt);//���ܪ��u���I
//		dc.SelectObject(oldPen);//�٭������e������
//	}
//	void draw2(CDC &dc)
//	{
//		CPen pen(PS_SOLID, LineWidth, color);//�إߵe������
//		CPen *oldPen = dc.SelectObject(&pen);//�]�wDC����ϥ�pen����
//		dc.MoveTo(StartPnt);//���ܪ��u�_�I
//		dc.LineTo(EndPnt);//���ܪ��u���I
//		dc.SelectObject(oldPen);//�٭������e������
//	}
//	void drawDashDot(CDC &dc)
//	{
//		CPen Center_Line_Pen(PS_DASHDOT, 1, color);//�إߵe������
//		CPen *oldPen = dc.SelectObject(&Center_Line_Pen);//�]�wDC����ϥ�pen����
//		dc.MoveTo(StartPnt);//���ܪ��u�_�I
//		dc.LineTo(EndPnt);//���ܪ��u���I
//		dc.SelectObject(oldPen);//�٭������e������
//	}
//};