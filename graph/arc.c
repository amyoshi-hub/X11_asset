#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <unistd.h>

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
	attr.override_redirect = False;
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
	
	int range = 135;
	int direction = 1;
	while(1){
	    if(XPending(d)){
	    XNextEvent(d, &event);
	    if(event.type = Expose){
	    switch(event.type){
		case Expose:

			XDrawArc(d, w, gc, 100, 50, 100, 100,       0*64, 360*64);//arc_base
	       		       //coordinate  x,  y,  幅  高さ start_range  finish 

			XSetArcMode(d, gc, ArcPieSlice);
			//fill_anime
			XFillArc(d, w, gc, 100, 50, 100, 100,      315*range, 135*64);
			range += direction * 5;	
			if(range >= 360 || range < 0){
				direction = -direction;
			}
			usleep(1);
			XFlush(d);
	   }
			
	   }
	   }
	}
	XFreeGC(d, gc);
	XDestroyWindow(d, w);
	XCloseDisplay(d);
	XFlush(d);
	getchar();
}
