
// HW3_408420010_408420074Doc.h: CHW3_408420010_408420074Doc 類別的介面
//


#pragma once
#include "BaseStruct.h"

class CHW3_408420010_408420074Doc : public CDocument
{
protected: // 僅從序列化建立
	CHW3_408420010_408420074Doc() noexcept;
	DECLARE_DYNCREATE(CHW3_408420010_408420074Doc)

// 屬性
public:
	CArray <MyPoint, MyPoint &> pArray;
	CArray <MyLine, MyLine &> lArray;
	CArray <MyEllipse, MyEllipse &> eArray;
	CArray <MyRect, MyRect &> rArray;
	CArray <MyPolygon, MyPolygon &> polyArray;
	int shapeNum;
	COLORREF Obj_Color;
	COLORREF Obj_fColor;
	COLORREF Obj_BgColor;
	int P_Type;
	int L_Type;
	bool onPolygon = false;
	void RemoveAll() 
	{
		pArray.RemoveAll();
		lArray.RemoveAll();
		eArray.RemoveAll();
		rArray.RemoveAll();
		polyArray.RemoveAll();
	}

// 作業
public:

// 覆寫
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 程式碼實作
public:
	virtual ~CHW3_408420010_408420074Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 產生的訊息對應函式
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 為搜尋處理常式設定搜尋內容的 Helper 函式
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
