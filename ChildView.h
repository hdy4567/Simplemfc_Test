
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();


// 특성입니다.
public:
	CArray<TCHAR, TCHAR> m_str;

	BOOL m_bDrawMode;
	int m_x1, m_y1, m_x2, m_y2;
	BOOL m_bMouseIn;
	int m_xPos, m_yPos; // 도형 위치
	int m_xMax, m_yMax; // 클라이언트 영역 크기
	BOOL m_bFill; // 도형 내부 여부 

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:

	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseLeave();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);




	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

