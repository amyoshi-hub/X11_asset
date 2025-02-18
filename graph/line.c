#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>

void main(){
	Display *d;	//window struct
	Window	w;	//window id
	GC	gc;	//graphic
	Font f;
	Pixmap	p;
	XEvent	event;	//x_event struct
	XSetWindowAttributes	attr;
	unsigned long	white, black;

	static XPoint s_data[] = {30,160, 100,70, 130,110, 200,50, 300,20};
	static XPoint d_data[] = {30,150, 100,60, 130,180, 200,70, 300,20};
	
	d = XOpenDisplay(NULL);	//connect to display

	black =	BlackPixel(d, 0);
	white =	WhitePixel(d, 0);
	
	
	w = XCreateSimpleWindow(d, RootWindow(d, 0),   100,   100,    260,     160,     1,     black, white);
			      //create window      , put_x, put_y, width, height, frame, black, window_white,

	XSelectInput(d, w, ExposureMask);//expose event
	attr.override_redirect = True;
	XChangeWindowAttributes(d, w, CWOverrideRedirect, &attr);
	
	XMapWindow(d, w);//to be able to see
	
	p = XCreatePixmap(d, w, 260, 160, DefaultDepth(d, 0));//wに対してのサイズ深さはサーバー依存
	//graphic
	gc = XCreateGC(d, p, 0, 0);//graphic typeこの場合はグラフィックコンテキストはpixmapに対して
	
	//pixmap inital
	XSetForeground(d, gc, white);
	XFillRectangle(d, p, gc, 0, 0, 260, 160);

	//font set
	f = XLoadFont(d, "fixed");
	XSetFont(d, gc, f);
	
	XSetForeground(d, gc, black);
	while(1){
	    XNextEvent(d, &event);
	    switch(event.type){
		case Expose:
			//gruph_x_y
			XSetLineAttributes(d, gc, 1, LineSolid, CapButt, JoinMiter);//幅1, 実線, 端の形状
			XDrawLine(d, p, gc, 30, 160, 300, 160);//x軸
			XDrawLine(d, p, gc, 30, 160,  30,  20);//y軸
			//line1
			XSetLineAttributes(d, gc, 2, LineSolid, CapRound, JoinRound);//幅2, 実線, 端の形状
			XDrawLines(d, p, gc, s_data, 5, CoordModeOrigin);//原点からの絶対座標で線を描画  5:点の数
			//line2
			XSetLineAttributes(d, gc, 2, LineOnOffDash, CapRound, JoinMiter);//幅2, 点線, 端の形状
			XDrawLines(d, p, gc, d_data, 5, CoordModeOrigin);//d_data表示 5:点の数

			XCopyArea(d, p, w, gc, 0, 0, 260, 160, 0, 0);
	   }
	}
	XFlush(d);
	getchar();
}
