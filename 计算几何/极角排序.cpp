//极角排序
struct Point
{
	__int128 x,y;
	int Q;
	Point(__int128 x=0,__int128 y=0):x(x),y(y)
	{
		if(x>0&&y>=0)	Q=1;
		else if(x<=0&&y>0)	Q=2;
		else if(x<0&&y<=0)	Q=3;
		else if(x>=0&&y<0)	Q=4;	
	}
	Point operator - (const Point &b) const {return Point(x-b.x,y-b.y); }
	bool operator < (const Point &b) const
	{
		if(Q==b.Q)	return x*b.y-b.x*y>0;
		return Q<b.Q;
	}
};