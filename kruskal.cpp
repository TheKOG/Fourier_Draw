#include<windows.h>
#include<bits/stdc++.h>
#define FullWidth GetSystemMetrics(SM_CXSCREEN)
#define FullHeight GetSystemMetrics(SM_CYSCREEN)
using namespace std;
const int N=1e6+28;
HBITMAP hbmp;
BITMAP bmp;
HDC hbm;
char ch[1024];
int width,height,tot;
int gx[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}},gy[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}};
struct Complex{
    double x,y;
    int id;
    Complex(double X=0,double Y=0,int ID=0){x=X,y=Y,id=ID;}
    friend bool operator == (Complex a,Complex b){
	if(abs(a.x-b.x)>1e-7)return false;
	if(abs(a.y-b.y)>1e-7)return false;
	return true;
    }
}pos[N];
double Dis(Complex a,Complex b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
struct Edge{
    Complex u,v;
    Edge(Complex x=Complex(),Complex y=Complex()){u=x,v=y;}
};
struct Triangle{
    Complex pos[3],center;
    double radius;
    Triangle(Complex a=Complex(),Complex b=Complex(),Complex c=Complex()){
	pos[0]=a,pos[1]=b,pos[2]=c;
	double A=pow(pos[0].x,2)+pow(pos[0].y,2);
	double B=pow(pos[1].x,2)+pow(pos[1].y,2);
	double C=pow(pos[2].x,2)+pow(pos[2].y,2);
	double G=(pos[2].y-pos[1].y)*pos[0].x+(pos[0].y-pos[2].y)*pos[1].x+(pos[1].y-pos[0].y)*pos[2].x;
	center.x=((B-C)*pos[0].y+(C-A)*pos[1].y+(A-B)*pos[2].y)/(2*G);
	center.y=((C-B)*pos[0].x+(A-C)*pos[1].x+(B-A)*pos[2].x)/(2*G);
	radius=sqrt(pow(pos[0].x-center.x,2)+pow(pos[0].y-center.y,2));
    };
};
struct E{
    int fm,to,nxt;double v;
    friend bool operator < (E a,E b){return a.v<b.v;}
};
struct Gra{
    int head[N],cnt;
    E l[N<<1];
    void Ins(int x,int y,double v){
	l[++cnt].to=y;
	l[cnt].fm=x;
	l[cnt].nxt=head[x];
	l[cnt].v=v;
	head[x]=cnt;
    }
    void Sort(){sort(l+1,l+cnt+1);}
}g1,g2;
vector<Triangle>temp,delaunay;
bool cmpy(Complex a,Complex b){return a.y<b.y;}
bool cmpx(Complex a,Complex b){return a.x<b.x;}
int apr[N];
void Triangulation(){
    //calc the super triangle
    double L,R,U,D;
    sort(pos+1,pos+tot+1,cmpy);
    U=pos[1].y;
    D=pos[tot].y;
    sort(pos+1,pos+tot+1,cmpx);
    L=pos[0].x;
    R=pos[tot].x;
    for(int i=1;i<=tot;i++)pos[i].id=i;
    double tWidth=(R-L)/2,tHeight=(D-U)*2;
    Complex left=Complex(L-tWidth-15,D+5);
    Complex right=Complex(R+tWidth+15,D+5);
    Complex top=Complex(L+tWidth,D-tHeight);
    Triangle mt(left,right,top);
    temp.push_back(mt);
    delaunay.push_back(mt);
    //triangulate
    for(int i=1;i<=tot;i++){
	//judge temp triangles
	vector<Edge>ebuf,res;
	for(vector<Triangle>::iterator it=temp.begin();it!=temp.end();){
	    Triangle tTr=*it;
            if(Dis(pos[i],it->center)>it->radius&&pos[i].x-it->center.x>it->radius){
                delaunay.push_back(*it);
                it=temp.erase(it);
                continue;
            }else if(Dis(pos[i],it->center)>it->radius&&pos[i].x-it->center.x<=it->radius){
                it++;
                continue;
            }else{
                ebuf.push_back(Edge(it->pos[0],it->pos[1]));
                ebuf.push_back(Edge(it->pos[1],it->pos[2]));
                ebuf.push_back(Edge(it->pos[0],it->pos[2]));
                it=temp.erase(it);
            }
	}
	//structural new temp triangles
	for(int j=0;j<ebuf.size();j++){
            if(apr[j]!=0)continue;
            for(int k=j+1;k<ebuf.size();k++){
                if((ebuf[j].u==ebuf[k].u&&ebuf[j].v==ebuf[k].v)||
                   (ebuf[j].v==ebuf[k].u&&ebuf[j].u==ebuf[k].v)){
                    apr[k]=1;
                    apr[j]=1;
                }
            }
        }
	//printf("i=%d delaunay=%d temp=%d ebuf=%d\n",i,delaunay.size(),temp.size(),ebuf.size());
        for(int j=0;j<ebuf.size();j++){
            if(apr[j]==0){
                res.push_back(ebuf[j]);
	    }
	    apr[j]=0;
        }
        for(int j=0;j<res.size();j++){
            Triangle t(res[j].u,res[j].v,pos[i]);
            temp.push_back(t);
        }
    }
    for(vector<Triangle>::iterator it=delaunay.begin();it!=delaunay.end();it++){
	Complex p1=it->pos[0],p2=it->pos[1],p3=it->pos[2];
	//printf("Connect %d to %d to %d\n",p1.id,p2.id,p3.id);
	if(p1.id==0||p2.id==0||p3.id==0)continue;
	double len=Dis(p1,p2);
	g1.Ins(p1.id,p2.id,len),g1.Ins(p2.id,p1.id,len);
	len=Dis(p2,p3);
	g1.Ins(p2.id,p3.id,len),g1.Ins(p3.id,p2.id,len);
	len=Dis(p1,p3);
	g1.Ins(p3.id,p1.id,len),g1.Ins(p1.id,p3.id,len);
    }
}
int fa[N];
int Getfa(int x){
    return x==fa[x]?x:fa[x]=Getfa(fa[x]);
}
void kruskal(){
    for(int i=1;i<=tot;i++)fa[i]=i;
    g1.Sort();
    //printf("cnt=%d\n",g1.cnt);
    for(int i=1;i<=g1.cnt;i++){
	int x=g1.l[i].fm,y=g1.l[i].to;
	double v=g1.l[i].v;
	int fx=Getfa(x),fy=Getfa(y);
	if(fx==fy)continue;
	fa[fx]=fy;
	g2.Ins(x,y,v);
	g2.Ins(y,x,v);
    }
}
int getRed(COLORREF a){
    int gb=a>>8;
    gb=gb<<8;
    return a-gb;
}
int getGreen(COLORREF a){
    int gb=a>>8,b=a>>16;
    b=b<<8;
    return gb-b;
}
int getBlue(COLORREF a){
    int b=a>>16,aph=a>>24;
    aph=aph<<8;
    return b-aph;
}
int tmp[1800][3200][3];
int Calc(int x,int y){
    int re=0;
    for(int c=0;c<3;c++){
	int Gx=0,Gy=0;
	for(int i=y-1;i<=y+1;i++){
	    for(int j=x-1;j<=x+1;j++){
		Gx+=tmp[i][j][c]*gx[i-y+1][j-x+1];
		Gy+=tmp[i][j][c]*gy[i-y+1][j-x+1];
	    }
	}
	re+=sqrt(Gx*Gx+Gy*Gy);
    }
    return re;
}
void GetColor(){
    for(int i=0;i<=height;i++){
	for(int j=0;j<=width;j++){
	    COLORREF cr=GetPixel(hbm,j,i);
	    tmp[i][j][0]=getRed(cr);
	    tmp[i][j][1]=getGreen(cr);
	    tmp[i][j][2]=getBlue(cr);
	}
    }
}
double dis[N];
void dfs(int x,int fa){
    for(int i=g2.head[x];i;i=g2.l[i].nxt){
	int y=g2.l[i].to;
	if(y==fa)continue;
	dis[y]=dis[x]+g2.l[i].v;
	dfs(y,x);
    }
}
Complex ans[N<<1];
int s,t,sum,on[N<<1];
bool check(int x,int fa){
    if(x==t)return on[x]=1;
    for(int i=g2.head[x];i;i=g2.l[i].nxt){
	int y=g2.l[i].to;
	if(y==fa)continue;
	if(check(y,x))on[x]=1;
    }
    return on[x];
}
void Out(int x,int fa){
    ans[++sum]=pos[x];
    int son=0;
    for(int i=g2.head[x];i;i=g2.l[i].nxt){
	int y=g2.l[i].to;
	if(y==fa)continue;
	if(on[y]){son=y;continue;}
	Out(y,x);
	ans[++sum]=pos[x];
    }
    if(son)Out(son,x);
}
bool choose[N<<1];
void CalcKB(Edge eg,double &k,double &b){
    Complex u=eg.u,v=eg.v;
    k=(v.y-u.y)/(v.x-u.x);
    b=u.y-u.x*k;
}
double PtoE(Complex p,Edge eg,int mode=0){
    double k,b;
    CalcKB(eg,k,b);
    Complex p1(p.x,p.x*k+b);
    Complex p2((p.y-b)/k,p.y);
    if(Dis(p1,p2)<(1e-7))return 19260817.00;
    if(mode)printf("%.2lf %.2lf %.2lf\n",Dis(p,p1),Dis(p,p2),Dis(p1,p2));
    return Dis(p,p1)*Dis(p,p2)/Dis(p1,p2);
}
void Douglas(int l,int r){
    choose[l]=choose[r]=1;
    if(l+1>r-1)return;
    int mid=0;
    double mx=-1;
    Edge eg(ans[l],ans[r]);
    for(int i=l+1;i<r;i++){
	double dist=PtoE(ans[i],eg);
	if(dist>mx||(dist==dist&&mx!=mx)||(mx==-1&&isnan(dist)))mx=dist,mid=i;
    }
    if(mx<5&&mx==mx)return;
    Douglas(l,mid);
    Douglas(mid,r);
}
int thre;
queue<Complex>res;
signed main(){
    cerr<<"Enter the path of image: ";
    scanf("%s",ch);
    cerr<<"Loading image...\n";
    hbmp=(HBITMAP)LoadImage(GetModuleHandle(0),ch,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);
    hbm=CreateCompatibleDC(GetDC(HWND_DESKTOP));
    SelectObject(hbm,hbmp);
    if(hbmp==NULL||hbm==NULL){
	cerr<<"Load failed\n";
	return 0;
    }
    GetObject(hbmp,sizeof(BITMAP),&bmp);
    width=(int)bmp.bmWidth,height=(int)bmp.bmHeight;
    cerr<<"Image's message: Width "<<width<<", Height "<<height<<".\n";
    cerr<<"Extracting the pixels' message...\n";
    GetColor();
    cerr<<"Enter the threshold value(default 200): ";
    char chh;
    scanf("%*c%c",&chh);
    if(chh=='\n'){
	thre=200;
    }else{
	for(;isdigit(chh);chh=getchar())thre=thre*10+chh-'0';
    }
    cerr<<"Extracting image outline...\n";
    int mw=FullWidth-70,mh=FullHeight-70;
    bool *apr=new bool[(mw+28)*mh];
    for(int x=2;x<width;x++){
	for(int y=2;y<height;y++){
	    int G=Calc(x,y);
	    if(G>=thre){
		int mx=max(width,height);
		if(mx<650){
		    pos[++tot]=Complex(x*650/mx,y*650/mx);
		}else if(width<mw&&height<mh)pos[++tot]=Complex(x,y);
		else{
		    double ww=1.0*mw/width,hh=1.0*mh/height;
		    int nx,ny,ptr;
		    if(ww<hh){
			nx=x*ww,ny=y*ww;
			ptr=nx*mh+ny;
			if(apr[ptr])continue;
			apr[ptr]=1;
			pos[++tot]=Complex(nx,ny);
		    }else{
			nx=x*hh,ny=y*hh;
			ptr=nx*mh+ny;
			if(apr[ptr])continue;
			apr[ptr]=1;
			pos[++tot]=Complex(nx,ny);
		    }
		}
	    }
	}
    }
    cerr<<"Found out "<<tot<<" outline points\n";
    cerr<<"Triangulating the points...\n";
    Triangulation();
    cerr<<"Calcing the minimum spanning tree\n";
    kruskal();
    cerr<<"Printing the path to buffer...\n";
    dfs(1,0);
    double mx=0;
    for(int i=1;i<=tot;i++)if(dis[i]>mx)mx=dis[i],t=i;
    mx=0,dis[t]=0;
    dfs(t,0);
    for(int i=1;i<=tot;i++)if(dis[i]>mx)mx=dis[i],s=i;
    check(s,0);
    Out(s,0);
    cerr<<"Making the path smooth...\n";
    choose[1]=choose[sum]=1;
    Douglas(1,sum);
    for(int i=1;i<=sum;i++)
	if(choose[i])
	    res.push(ans[i]);
    cerr<<"Printing the data to the file...\n";
    freopen("data.in","w",stdout);
    printf("%d\n",res.size());
    while(res.size())printf("%.0lf %.0lf\n",res.front().x,res.front().y),res.pop();
    freopen("CON","w",stdout);
    return 0;
}
