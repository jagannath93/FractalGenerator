#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <string>

using namespace std;


int getInt(double _x)  //Function for converting actual co-ordinate to screen co-ordinate.
{
    if(_x > int(_x)+0.5)
     return int(_x)+1;
    else
     return int(_x);
}

void put_point(double _x, double _y, char ch, int color = WHITE) //Custom putpixel function.
{
    int x,y;    
      
      x = getInt(_x);
      y = getInt(_y);   
     
     if(ch == 't')
      putpixel(x,y,color);
     if(ch == 'T')
     {
       setfillstyle( SOLID_FILL, color);
       bar(x-3,y+3,x+3,y-3);        
     }   
}

void changetextstyle(int font, int direction, int charsize)
{
  int ErrorCode;

  graphresult();  // clear error code             
  settextstyle(font, direction, charsize);
  ErrorCode = graphresult();            // check result                 
  if( ErrorCode != grOk ){              // if error occured             
    closegraph();
    printf(" Graphics System Error: %s\n", grapherrormsg( ErrorCode ) );
    exit( 1 );}
}



int main()
{
    int n = 0;    
    double X = 0,Y = 0,r = 0; //r - fraction
    int N = 0;
    double start_X = 0, start_Y = 0, new_X = 0, new_Y = 0;
    struct viewporttype vp;   
    
    srand((unsigned)time(NULL));    
	
	while(n < 3)
	{
	 cout<<"\nSize of polygon(no of sides): "; cin>>n;    //Inputting no. of sides of polygon.
	 if(n < 3){cout<<"\nOpen polygon!! It's difficult to find pattern with this value."<<endl;}
   }
   
	double x[n];
   double y[n];
	cout<<"\nEnter each vertex (x,y) in each line: \n";    //Inputting vertice of polygon.
	for(int i=0;i<n;i++)
	{
    cin>>x[i]>>y[i];    
   }
   
   for(;;)
   {    
   cout<<"\nEnter the starting point(x,y): "; cin>>X>>Y; //Staring point input
   start_X = X; start_Y = Y;
   
   cout<<"Enter line division ratio(r):"; cin>>r;  //Division ratio input.
  
   /*if(r <= 0)
   {cout<<"\n Division ratio Generally takes '+'ve values !!"<<endl; continue;}*/
   
   cout<<"Number of points to be processed: "; cin>>N;  //No of points to be plotted.
   if(N < 100){cout<<"\nDifficult to find pattern with these values!!"<<endl; continue;}
   
   new_X = start_X; new_Y = start_Y; //This is just to mark inital point at the end of program to prevent blur due to points overlapping
   
   initwindow( 1200 , 800 , "WinBGIm" );
   
    changetextstyle( 4, HORIZ_DIR, 3 );
   settextjustify( CENTER_TEXT, TOP_TEXT );
   outtextxy( 300, 10, "Fractal Generator" );
   //setcolor( BLACK );
   
   /*getviewsettings( &vp );
   setfillstyle( SOLID_FILL, WHITE );
   bar( 0, 0, vp.right-vp.left, vp.bottom-vp.top );      // Draw background */
   
   //setfillstyle( SOLID_FILL, WHITE);
   //outtextxy( 0 ,0 , "Hello WinBGIm!" );    
	//bgiout << "Hello WinBGIm-Stream!" ;
	//outstreamxy( 0 , 15 );	
	/*
   example parabola
	for(double i = -50.0;i<50.0;i=i+0.05)
	put_point((i*i)/16,i+50,GREEN);
	*/
	for(int k=0;k<n;k++)
	{ int l = 0; 
     if(k == n-1) l = 0;
     else l = k+1;
     //cout<<"Actual_coords: "<<x[k]<<", "<<y[k]<<endl;
     setlinestyle( 1, 0, THICK_WIDTH );
     line(getInt(x[k]),getInt(y[k]),getInt(x[l]),getInt(y[l]));
    //cout<<"Line: ("<<getInt(x[k])<<","<<getInt(y[k])<<"), ("<<getInt(x[l])<<","<<getInt(y[l])<<")"<<endl; 
   }
   

   for(int j=0;j<N;j++)
   {
     if(j%100 == 0)
     Sleep(300);
     
     int random = rand()%n;
     if(random >= 0 && random < n)   //Using random no. as index to x[k], y[k].
     {
        new_X = ((1/(r+1))*(x[random]))+((r/(r+1))*(new_X));
        new_Y = ((1/(r+1))*(y[random]))+((r/(r+1))*(new_Y));
        
        put_point(new_X,new_Y,'t', WHITE);
     }
     else
     {j--; continue;}
   }
   
    put_point(start_X,start_Y,'T', RED); //Plotting the starting point.
    
    settextjustify( LEFT_TEXT, TOP_TEXT );
    changetextstyle( 4 , HORIZ_DIR, 3 );
    //outtextxy( 700, 200, "This is a Fractal: %s",str );
       
    stringstream ss;
    string s;
    char* str;
    int xloc, yloc;
    
    xloc = 650; yloc = 120;     
    
    ss.str("");
    //yloc += textheight( "H" ) + 2;
    ss <<"PARAMETERS :";
    s = ss.str();
    str = &s[0];  // Conversion of string to char*    
    outtextxy(xloc, yloc, str);
    
    changetextstyle( 3 , HORIZ_DIR, 2 );
    
    ss.str("");
    yloc += textheight( "H" ) + 30;
    ss << n << "  sided Polygon";
    s = ss.str();
    str = &s[0];  // Conversion of string to char*    
    outtextxy(xloc, yloc, str);
    
    ss.str("");
    yloc += textheight( "H" ) + 10;
    ss << "Starting point :   ( "<<start_X<<", "<<start_Y<<" )";
    s = ss.str();
    str = &s[0];  // Conversion of string to char*    
    outtextxy( xloc, yloc, str );
    
    ss.str("");
    yloc += textheight( "H" ) + 10;
    ss <<"Division ratio(r) :   "<<r;
    s = ss.str();
    str = &s[0];  // Conversion of string to char*    
    outtextxy(xloc, yloc, str);
    
    ss.str("");
    yloc += textheight( "H" ) + 10;
    ss <<"Plotted points  :   "<<N;
    s = ss.str();
    str = &s[0];  // Conversion of string to char*    
    outtextxy(xloc, yloc, str);
    
    changetextstyle( 4, HORIZ_DIR, 3 );
    
    ss.str("");
    yloc += textheight( "H" ) + 50;
    ss <<"LEGEND :";
    s = ss.str();
    str = &s[0];  // Conversion of string to char*    
    outtextxy(xloc, yloc, str);
    
    changetextstyle( 3 , HORIZ_DIR, 2 );
    
    yloc += textheight( "H" ) + 30;
    setfillstyle( SOLID_FILL, RED);
    bar(xloc, yloc, xloc+30, yloc+30);    
    ss.str("");
    xloc += 50;
    yloc +=  3;
    ss <<"     INITIAL POINT ";
    s = ss.str();
    str = &s[0];  // Conversion of string to char*    
    outtextxy(xloc, yloc, str);
    
    xloc -= 60;
    
    yloc += textheight( "H" ) + 30;
    setlinestyle( 1, 0, THICK_WIDTH );
    line(xloc, yloc, xloc+50, yloc);
    ss.str("");
    xloc += 60;
    yloc -= 10;
    ss <<"     POLYGON BOUNDARY ";
    s = ss.str();
    str = &s[0];  // Conversion of string to char*    
    outtextxy(xloc, yloc, str);
    
    xloc -= 40;
    
    yloc += textheight( "H" ) + 30;
    setfillstyle( SOLID_FILL, WHITE);
    bar(xloc, yloc, xloc+7, yloc+7);  
    ss.str("");
    xloc += 60;
    yloc -= 5;
    ss <<"  PLOTTED POINT ";
    s = ss.str();
    str = &s[0];  // Conversion of string to char*    
    outtextxy(xloc, yloc, str);
    
    xloc -= 60;
    
    settextjustify( LEFT_TEXT, BOTTOM_TEXT );
    changetextstyle( 4, HORIZ_DIR, 1 );   
    ss.str("");
    yloc += textheight( "H" ) + 180;
    ss <<"PRESS ENTER FOR NEXT INPUT...";
    s = ss.str();
    str = &s[0];  // Conversion of string to char*    
    outtextxy(xloc, yloc, str);
    
   if(getch()) //This is just a dummy variable make cleardevice() wait until user hits something.
   cleardevice(); //To clear the screen.
 }     
   
	while(!kbhit());    
	closegraph();    
	return(0);
}
/******** END OF MAIN ***************/


/* WRITTEN BY JAGANNADH */
