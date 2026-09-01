
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Simplemfc2_mouse.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_xPos = m_yPos = 60; // 임의 값으로 초기화
	m_bFill = FALSE; // 도형 내부를 채우지 않음
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_MOUSELEAVE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SIZE()
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}
//
//void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
//{

//}


void Draw() {

	//dc.SelectStockObject(LTGRAY_BRUSH);
	//dc.Ellipse(10, 10, 400, 100);
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	// 화면 출력용 폰트를 선택한다.
	CFont font;
	font.CreatePointFont(150, _T("궁서"));
	dc.SelectObject(&font);

	// 현재까지 입력된 글자들을 화면에 출력한다.
	CRect rect;
	GetClientRect(&rect);
	dc.DrawText(m_str.GetData(), m_str.GetSize(), &rect, DT_LEFT);


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{

	// 마우스 캡처를 시작한다(MFC 함수 사용).
	SetCapture();
	// 그리기 모드를 시작한다.
	m_bDrawMode = TRUE;


	//void2 {
	//CClientDC dc(this);
	//dc.SelectStockObject(NULL_BRUSH);
	//// 최종적인 타원을 그린다.
	//dc.SetROP2(R2_COPYPEN);
	//m_x2 = point.x;
	//m_y2 = point.y;
	//dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
	//// 그리기 모드를 끝낸다.
	//m_bDrawMode = FALSE;


	//// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//m_bDrawMode = TRUE;
	//// 좌표를 저장한다.
	//m_x1 = m_x2 = point.x;
	//m_y1 = m_y2 = point.y;
	//}

	//void 1{
	//CClientDC dc(this);
	//dc.SetMapMode(MM_LOMETRIC); // 매핑 모드를 변경한다.
	//CPoint pt = point; // point 객체를 복사한다.
	//dc.DPtoLP(&pt); // 장치 좌표를 논리 좌표로 변환한다.
	//dc.Rectangle(pt.x - 100, pt.y + 100, pt.x + 100, pt.y - 100);
	//}


	CWnd::OnLButtonDown(nFlags, point);

}


void movedraw() { 
	//if (m_bDrawMode) {
	//	CClientDC dc(this);
	//	dc.SelectStockObject(NULL_BRUSH);
	//	// 이전에 그린 타원을 지운다.
	//	dc.SetROP2(R2_NOT);
	//	dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
	//	CWnd::OnMouseMove(nFlags, point);

	//	// 새로운 타원을 그린다.
	//	dc.SetROP2(R2_NOT);
	//	m_x2 = point.x;
	//	m_y2 = point.y;
	//	dc.Ellipse(m_x1, m_y1, m_x2, m_y2);
	}


void OnMouseMove_test() {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		// 그리기 모드이면 타원을 지우고 그리기를 반복한다.
	//if (m_bMouseIn == FALSE) {

	//	TRACKMOUSEEVENT tme;
	//	tme.cbSize = sizeof(tme);
	//	tme.dwFlags = TME_LEAVE;
	//	tme.hwndTrack = this->m_hWnd;
	//	tme.dwHoverTime = HOVER_DEFAULT;
	//	::TrackMouseEvent(&tme);

	//	// 메인 윈도우 크기를 300*150으로 변경한다.
	//	CWnd* pMainWnd = AfxGetMainWnd();
	//	CRect rect;
	//	pMainWnd->GetWindowRect(&rect);
	//	rect.right = rect.left + 300;
	//	rect.bottom = rect.top + 150;
	//	pMainWnd->MoveWindow(&rect);

	//	// 마우스 커서가 클라이언트 영역에 있음을 기억해둔다.
	//	m_bMouseIn = TRUE;
}





void CChildView::OnMouseMove(UINT nFlags, CPoint point)
	{
	if (m_bMouseIn == FALSE) {
		// 마우스 커서 추적을 요청한다.
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = this->m_hWnd;
		tme.dwHoverTime = HOVER_DEFAULT;
		::TrackMouseEvent(&tme);

		// 메인 윈도우 크기를 300*150으로 변경한다.
		CWnd* pMainWnd = AfxGetMainWnd();
		CRect rect;
		pMainWnd->GetWindowRect(&rect);
		rect.right = rect.left + 300;
		rect.bottom = rect.top + 200;
		pMainWnd->MoveWindow(&rect);

		// 마우스 커서가 클라이언트 영역에 있음을 기억해둔다.
		m_bMouseIn = TRUE;

	}
}


/// <summary> :: 범위지정 연산자  </summary>


void OnSetCursor_CursorChange1() {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
// 클라이언트 영역이면 커서를 변경한다.
//if (nHitTest == HTCLIENT) {
//	CPoint point;
//	::GetCursorPos(&point); // 커서 위치(스크린 좌표)를 얻는다.
//	ScreenToClient(&point); // 스크린 좌표를 클라이언트 좌표로 변환한다.
//	CRgn rgn;
//	rgn.CreateEllipticRgn(10, 10, 400, 100); // 타원형 리전을 생성한다.
//	if (rgn.PtInRegion(point)) // 커서가 리전 안쪽에 있는지 확인한다.
//		// 사용자 정의 커서로 변경한다.
//		::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
//	else
//		// 표준 커서 중 하나로 변경한다.
//		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
//	return TRUE;
}

void OnSetCursor_CursorChange2() {
}




BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
		return CWnd::OnSetCursor(pWnd, nHitTest, message);
}
/// <summary> 커서 추척 후, 커서가 영역 들어오면 커지기 </summary>
void CChildView::OnMouseLeave()
{

	// 마우스 커서가 클라이언트 영역 밖에 있음을 기억해둔다.
	m_bMouseIn = FALSE;

	// 메인 윈도우 크기를 200*200으로 변경한다.
	CWnd* pMainWnd = AfxGetMainWnd();
	CRect rect;
	pMainWnd->GetWindowRect(&rect);
	rect.right = rect.left + 200;
	rect.bottom = rect.top + 200;
	pMainWnd->MoveWindow(&rect);


	//// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//m_bMouseIn = FALSE;

	//// 메인 윈도우 크기를 200*100으로 변경한다.
	//CWnd* pMainWnd = AfxGetMainWnd();
	//CRect rect;
	//pMainWnd->GetWindowRect(&rect);
	//rect.right = rect.left + 200;
	//rect.bottom = rect.top + 100;
	//pMainWnd->MoveWindow(&rect);


	
	CWnd::OnMouseLeave();
}


/// <summary> 깜빡이는 직사각형 상자, 캐럿만들기 </summary>
void OnSetFocus_CreatCarrot() {
	//CreateSolidCaret(20, 20);
	//SetCaretPos(CPoint(50, 50));
	//ShowCaret();
	//::SetCaretBlinkTime(30);
	//CWnd::OnSetFocus(pOldWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CChildView::OnSetFocus(CWnd* pOldWnd)
{

}

void CChildView::OnKillFocus(CWnd* pNewWnd)
{
	HideCaret();
	::DestroyCaret();
	CWnd::OnKillFocus(pNewWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	m_xMax = cx;
	m_yMax = cy;
	//CWnd::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		// [Backspace] 키 입력 시 맨 마지막 글자를 삭제한다.
	if (nChar == _T('\b')) {
		if (m_str.GetSize() > 0)
			m_str.RemoveAt(m_str.GetSize() - 1);
	}
	// 그 밖의 경우에는 동적 배열에 글자를 추가한다.
	else {
		m_str.Add(nChar);
	}

	// 화면을 갱신한다.
	Invalidate();

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}
