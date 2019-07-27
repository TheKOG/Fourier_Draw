#include"O4.h"
#include<windows.h>
#include<bits/stdc++.h>
#define FullWidth GetSystemMetrics(SM_CXSCREEN)
#define FullHeight GetSystemMetrics(SM_CYSCREEN)
using namespace std;
const int Height=650;
const int Width=650;
const int N=1e6+28;
namespace FFT{
    const double pi=acos(-1);
    struct Complex{
	double x,y;
	Complex(double a=0,double b=0){x=a,y=b;};
    };
    Complex operator + (Complex a,Complex b){return Complex(a.x+b.x,a.y+b.y);}
    Complex operator - (Complex a,Complex b){return Complex(a.x-b.x,a.y-b.y);}
    Complex operator * (Complex a,Complex b){return Complex(a.x*b.x-a.y*b.y,a.y*b.x+a.x*b.y);}
    Complex operator * (Complex a,double b){return Complex(a.x*b,a.y*b);}
    Complex operator * (double a,Complex b){return Complex(b.x*a,b.y*a);}
    int rota[N];
    int pre(int n){
	int cnt=1;
	int high=0;
	while(cnt<n)cnt<<=1,high++;
	for(int i=0;i<cnt;i++)
	    rota[i]=(rota[i>>1]>>1)|((i&1)<<(high-1));
	return cnt;
    }
    int lim;
    void fft(int n,Complex *buf,int fft){
	lim=pre(n);
	for(int i=0;i<lim;i++)if(i<rota[i])swap(buf[i],buf[rota[i]]);
	for(int len=2;len<=lim;len<<=1){
	    Complex wn=Complex(cos(fft*2*pi/len),sin(fft*2*pi/len));
	    for(int s=0;s<lim;s+=len){
		Complex w=Complex(1,0);
		for(int k=s;k<s+len/2;k++,w=w*wn){
		    Complex x,y;
		    x=buf[k],y=w*buf[k+len/2];
		    buf[k]=x+y;
		    buf[k+len/2]=x-y;
		}
	    }
	}
    }
    void CalcPos(double n,Complex *buf,Complex *pos){
	for(int k=0;k<lim;k++){
	    pos[k]=buf[k]*Complex(cos(2*pi*k*n/lim),sin(2*pi*k*n/lim));
	    pos[k].x/=lim,pos[k].y/=lim;
	}
    }
    double Length(Complex X){
	return sqrt(X.x*X.x+X.y*X.y);
    }
}
using namespace FFT;
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void Paint(HWND hwnd);
void Init(HWND hwnd);
void Copy(char *buf);
int tot,getStart,Stop;
double step;
Complex pos[N],point[N];
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;
    memset(&wc,0,sizeof(wc));
    wc.cbSize		 = sizeof(WNDCLASSEX);
    wc.lpfnWndProc	 = WndProc;
    wc.hInstance	 = hInstance;
    wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = "WindowClass";
    wc.hIcon=(HICON)LoadImage(GetModuleHandle(0),"lll.ico",IMAGE_ICON,128,128,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
    wc.hIconSm=(HICON)LoadImage(GetModuleHandle(0),"lll.ico",IMAGE_ICON,128,128,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
    if(!RegisterClassEx(&wc)) {MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);return 0;}
    hwnd=CreateWindowEx(
			WS_EX_CLIENTEDGE,
			"WindowClass","Fourier Draw",
			WS_VISIBLE|WS_OVERLAPPEDWINDOW,
			(FullWidth-Width-20)/2,(FullHeight-Height-40)/2,
			Width+21,Height+45,
			NULL,
			NULL,
			hInstance,
			NULL
			);
    if(hwnd==NULL){MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);return 0;}
    Init(hwnd);
    double start=clock();
    int wait=0;
    while(msg.message!=WM_QUIT){
	if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
	    TranslateMessage(&msg);
	    DispatchMessage(&msg);
	}else{
	    if(clock()>=start+0.1*CLOCKS_PER_SEC)start+=0.1*CLOCKS_PER_SEC;
	    else continue;
	    if(getStart&&Stop==0){
		if(step>1.0*tot-(1e-7))step=0;
		Paint(hwnd);
		step+=1;
	    }else{
		Paint(hwnd);
	    }
	}
    }
    return msg.wParam;
}
HDC WinMap,dWinMap;
HBITMAP dbm;
HBRUSH black,red,green,blue,white,grey,dark,Indirect;
HPEN Black,White,Green,Red,Blue,Grey;
void Init(HWND hwnd){
    srand(time(0));
    SetWindowLong(hwnd,GWL_STYLE,GetWindowLong(hwnd,GWL_STYLE)&(~WS_MAXIMIZEBOX&~WS_THICKFRAME));
    black=CreateSolidBrush(RGB(0,0,0));
    grey=CreateSolidBrush(RGB(100,100,100));
    red=CreateSolidBrush(RGB(255,0,0));
    green=CreateSolidBrush(RGB(0,255,0));
    blue=CreateSolidBrush(RGB(0,0,255));
    white=CreateSolidBrush(RGB(255,255,255));
    Black=CreatePen(PS_SOLID,0,RGB(0,0,0));
    Grey=CreatePen(PS_SOLID,0,RGB(100,100,100));
    White=CreatePen(PS_SOLID,0,RGB(255,255,255));
    Green=CreatePen(PS_SOLID,2,RGB(0,255,0));
    Red=CreatePen(PS_SOLID,0,RGB(255,0,0));
    Blue=CreatePen(PS_SOLID,0,RGB(0,0,255));
    LOGBRUSH logbr;
    memset(&logbr,0,sizeof(LOGBRUSH));   
    logbr.lbColor=RGB(255,255,255);
    logbr.lbStyle=BS_NULL;
    Indirect=CreateBrushIndirect(&logbr);
    WinMap=GetDC(hwnd);
    dWinMap=CreateCompatibleDC(WinMap);
    dbm=CreateCompatibleBitmap(WinMap,Width,Height);
    SelectObject(dWinMap,dbm);
    SetBkMode(dWinMap,TRANSPARENT);
    freopen("data.in","r",stdin);
    int tmp;
    if(scanf("%d",&tmp)!=EOF){
	tot=tmp;
	for(int i=0;i<tot;i++)
	    if(scanf("%lf%lf",&point[i].x,&point[i].y)==EOF)break;
    }
    freopen("CON","r",stdin);
}
char s[256];
int cnt,Show,Hide;
Complex draw[N],vec[N];
void Paint(HWND hwnd){
    SelectObject(dWinMap,white);
    SelectObject(dWinMap,White);
    Rectangle(dWinMap,0,0,Width,Height);
    SelectObject(dWinMap,black);
    SelectObject(dWinMap,Black);
    if(getStart==0||Show){
	for(int i=0;i<tot;i++)
	    Rectangle(dWinMap,(int)point[i].x-2,(int)point[i].y-2,(int)point[i].x+2,(int)point[i].y+2);
    }
    if(getStart){
	SelectObject(dWinMap,Indirect);
	if(step<1e-7)cnt=0;
	CalcPos(step,pos,vec);
	draw[++cnt]=Complex(0,0);
	MoveToEx(dWinMap,0,0,NULL);
	for(int i=0;i<lim;i++){
	    int len=(int)Length(vec[i]);
	    SelectObject(dWinMap,Red);
	    if(!Hide)Ellipse(dWinMap,(int)draw[cnt].x-len,(int)draw[cnt].y-len,(int)draw[cnt].x+len,(int)draw[cnt].y+len);
	    draw[cnt]=draw[cnt]+vec[i];
	    SelectObject(dWinMap,Blue);
	    if(!Hide)LineTo(dWinMap,(int)draw[cnt].x,(int)draw[cnt].y);
	}
	SelectObject(dWinMap,Green);
	MoveToEx(dWinMap,(int)draw[1].x,(int)draw[1].y,NULL);
	for(int i=2;i<=cnt;i++)
	    LineTo(dWinMap,(int)draw[i].x,(int)draw[i].y);
    }
    BitBlt(WinMap,0,0,Width,Height,dWinMap,0,0,SRCCOPY);
}
void Copy(char *buf){
    int len=strlen(buf)+1;
    if(OpenClipboard(NULL)){
	HGLOBAL hmem=GlobalAlloc(GHND,len);
	char *pmem=(char*)GlobalLock(hmem);
	EmptyClipboard();
	memcpy(pmem,buf,len);
	SetClipboardData(CF_TEXT,hmem);
	CloseClipboard();
	GlobalFree(hmem);
    }
}
LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam){
    switch(Message){
    case WM_DESTROY:{PostQuitMessage(0);break;}
    case WM_LBUTTONDOWN:{
	double x=(double)LOWORD(lParam),y=(double)HIWORD(lParam);
	point[tot++]=Complex(x,y);
	point[tot]=Complex(0,0);
	break;
    }
    case WM_KEYDOWN:{
	switch(wParam){
	case VK_ESCAPE:{
	    getStart=tot=0;
	    memset(point,0,sizeof(point));
	    break;
	}
	case 'Z':{
	    if(tot)tot--;
	    break;
	}
	case 'X':{
	    if(point[tot].x>1e-7)tot++;
	    break;
	}
	case VK_F5:{
	    if(getStart==0){
		getStart=1;
		Stop=0,step=0,cnt=0;
		int lim=pre(tot);
		memcpy(pos,point,lim*sizeof(Complex));
		fft(tot,pos,-1);
	    }else{
		getStart=0;
	    }
	    break;
	}
	case VK_SPACE:{
	    Stop=1-Stop;
	    break;
	}
	case VK_F1:{
	    Show=1-Show;
	    break;
	}
	case VK_F2:{
	    Hide=1-Hide;
	    break;
	}
	}
	break;
    }
    default:return DefWindowProc(hwnd,Message,wParam,lParam);
    }
    return 0;
}
/*

*/
