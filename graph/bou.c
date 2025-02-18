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
	
	XRectangle	rectangle[5];
	
	static  int data[] = {1, 2, 3, 4, 5};
		int i;
	
	d = XOpenDisplay(NULL);	//connect to display

	black =	BlackPixel(d, 0);
	white =	WhitePixel(d, 0);
	
	
	w = XCreateSimpleWindow(d, RootWindow(d, 0),   100,   100,   260,    160,     5,     black, white);
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
	    XNextEvent(d, &event);
	    switch(event.type){
		case Expose:
			XDrawRectangle(d, w, gc, 40, 40, 240, 120);
			for(i = 0; i < 5; i++){
				rectangle[i].x =  55 + i * (30 + 15);//30は幅15は間隔
				rectangle[i].y = 120 - data[i] + 40;
				rectangle[i].width  =  30;
				rectangle[i].height =  data[i];
			}
			XDrawRectangles(d, w, gc, rectangle, 5);
			XFlush(d);
	   }
			
	}
	XFreeGC(d, gc);
	XDestroyWindow(d, w);
	XCloseDisplay(d);
	XFlush(d);
	getchar();
}
