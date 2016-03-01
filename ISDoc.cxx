
#include <FL/fl_ask.H>
#include "ISDoc.h"
#include "ISUI.h"
#include <cstring>
#include <iostream>
#include <cmath>
#include <queue>


using namespace std;

priority_queue <Node> q;
bool operator < (Node x,Node y){
     return x.totalCost > y.totalCost;     // 默认大根堆，这里是小根堆，注意小根堆是大于！与sort的cmp是反的，这里是满足则交换
};

// For auxiliary purpose
	//diagonal:1,3,5,7
int dir[8][2]={{1,0},{1,-1},{0,-1},{-1,-1},
				   {-1,0},{-1,1},{0,1},{1,1}};


ISDoc::ISDoc(){
	curmap=bitmap = NULL;
	imageName[0] = '\0';
	z=1.0;
	width=height=0;
	nodeMatrix=NULL;
	drawMatrix=debugMatrix=NULL;
	seed=last=NULL;
}

void ISDoc::setUI(ISUI* ui){
	myUI = ui;
}


char* ISDoc::getImageName(){
	return imageName;
}

int ISDoc::loadImage(const char* picName){
	unsigned char* data;
	int	w, h;

	if ( (data=readBMP(picName, w, h))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}
	bitmap = data;
	zw=width = w;
	zh=height = h;
	z=1.0;
	mode = WORK_MODE;
	initializeMatrix();
	refreshCurmap();
	myUI->pic->show();
	calcLinkCost();
	calcCostTree(1,1);
	if(seed!=0)delete seed;
	if(last!=0)delete last;
	seed=last=NULL;
	// int l=width*height*3;
	// curmap=new unsigned char[l];
	// for(int i=0;i<l;i++)
	// 	curmap[i]=bitmap[i];
	//curmap=bitmap;
	//myUI->mainWindow->resize(myUI->mainWindow->x(),myUI->mainWindow->y(),width,height+20);

	//myUI->pic->resizeView(width,height);

	//myUI->pic->refresh();
	return 1;

}

int ISDoc::saveImage(char* picName){
	writeBMP(picName, width, height, bitmap);
	return 1;
}

void ISDoc::zoom(char inq)
{
	if(inq=='+')
		z*=2;
	else if(inq=='-')
		z*=0.5;
	zw=z*width;
	zh=z*height;
	cout<<"bp1\n";
	refreshCurmap();
}

void ISDoc::pixelNode(){
	mode = DEBUG_MODE;
	cout << "changing mode" << endl;
	cout << "before zw=" << zw << " zh = " << zh << endl;
	debugMatrix = new Color*[3*height];
	for (int i=0;i<3*height;i++)
		debugMatrix[i] = new Color[3*width];
	// initial the 3*h * 3*w matrix(h&w in original size)
	Color Black; Black.c1 = Black.c2 = Black.c3 = 0;
	for (int i=0;i<height;i++)
		for (int j=0;j<width;j++){

			for (int l1=0;l1<=2;l1++)
				for (int l2=0;l2<=2;l2++)
					debugMatrix[i*3+l1][j*3+l2] = Black;

			debugMatrix[i*3+1][j*3+1].c1 = nodeMatrix[i][j].c1;
			debugMatrix[i*3+1][j*3+1].c2 = nodeMatrix[i][j].c2;
			debugMatrix[i*3+1][j*3+1].c3 = nodeMatrix[i][j].c3;

		}
	// z*=3.0; zw*=3.0; zh*=3.0;
	z=1; zw=width*3; zh=height*3;
	refreshCurmap();
}

void ISDoc::initializeMatrix(){

	nodeMatrix = new Node*[height];
	for (int i=0;i<height;i++)
		nodeMatrix[i] = new Node[width];

	for (int i=0;i<height;i++)
		for (int j=0;j<width;j++){
			nodeMatrix[i][j].c1=bitmap[(i*width+j)*3];
			nodeMatrix[i][j].c2=bitmap[(i*width+j)*3+1];
			nodeMatrix[i][j].c3=bitmap[(i*width+j)*3+2];
			nodeMatrix[i][j].row=i;
			nodeMatrix[i][j].col=j;
			nodeMatrix[i][j].state=INITIAL;
			nodeMatrix[i][j].preNode=NULL;
			nodeMatrix[i][j].totalCost=-1;
			nodeMatrix[i][j].drawed=false;
		}

	drawMatrix= new Color*[height];
	for (int i=0;i<height;i++)
		drawMatrix[i]=new Color[width];
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			drawMatrix[i][j].c1=nodeMatrix[i][j].c1;
			drawMatrix[i][j].c2=nodeMatrix[i][j].c2;
			drawMatrix[i][j].c3=nodeMatrix[i][j].c3;
		} 
}

void ISDoc::refreshCurmap()
{
	cout << "z = " << z << endl;
	curmap=new unsigned char[zw*zh*3];
	if (mode == WORK_MODE){
		cout << "~~~working mode = work mode" << endl;
		for(int i=0;i<zh;i++)
			for(int j=0;j<zw;j++){
				if(nodeMatrix[int(i/z)][int(j/z)].drawed==true)
				{
					curmap[(i*zw+j)*3]=255;
					curmap[(i*zw+j)*3+1]=0;
					curmap[(i*zw+j)*3+2]=0;
				}
				else{
					curmap[(i*zw+j)*3]=drawMatrix[int(i/z)][int(j/z)].c1;
					curmap[(i*zw+j)*3+1]=drawMatrix[int(i/z)][int(j/z)].c2;
					curmap[(i*zw+j)*3+2]=drawMatrix[int(i/z)][int(j/z)].c3;
				}
			}
		cout << "endl" << endl;

	}else{
		cout << "~~~working mode = debug mode" << endl;
		for(int i=0;i<zh;i++)
			for(int j=0;j<zw;j++){
				curmap[(i*zw+j)*3]=debugMatrix[int(i/z)][int(j/z)].c1;
				curmap[(i*zw+j)*3+1]=debugMatrix[int(i/z)][int(j/z)].c2;
				curmap[(i*zw+j)*3+2]=debugMatrix[int(i/z)][int(j/z)].c3;
			}
	}
	cout << (myUI == NULL) << endl;
	cout << (myUI->pic == NULL) << endl;
	myUI->pic->refresh();
}

void ISDoc::calcLinkCost(){
	// Not calcute the out round of the pixels. To be handled later.

	double maxD=0;
	for (int i=1;i<height-1;i++)
		for (int j=1;j<width-1;j++)
			for (int d=0;d<8;d++){
				double DR,DG,DB;
				if (d%2==0){ //vertical or horizontal lines
					DR= abs( (nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c1 +
							  nodeMatrix[i+dir[(d+2)%8][0]][j+dir[(d+2)%8][1]].c1)/2.0 -
							 (nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c1 +
							  nodeMatrix[i+dir[(d+6)%8][0]][j+dir[(d+6)%8][1]].c1)/2.0 ) /2.0;
					DG= abs( (nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c2 +
							  nodeMatrix[i+dir[(d+2)%8][0]][j+dir[(d+2)%8][1]].c2)/2.0 -
							 (nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c2 +
							  nodeMatrix[i+dir[(d+6)%8][0]][j+dir[(d+6)%8][1]].c2)/2.0 ) /2.0;
					DB= abs( (nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c3 +
							  nodeMatrix[i+dir[(d+2)%8][0]][j+dir[(d+2)%8][1]].c3)/2.0 -
							 (nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c3 +
							  nodeMatrix[i+dir[(d+6)%8][0]][j+dir[(d+6)%8][1]].c3)/2.0 ) /2.0;
					nodeMatrix[i][j].D[d] = sqrt((DR*DR+DG*DG+DB*DB)/3);

					maxD = max(maxD, nodeMatrix[i][j].D[d]);
				}else{ // diagonal lines
					DR= abs( nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c1 - 
						 	 nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c1)/sqrt(2);
					DG= abs( nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c2 - 
						 	 nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c2)/sqrt(2);
					DB= abs( nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c3 - 
						 	 nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c3)/sqrt(2);
					nodeMatrix[i][j].D[d] = sqrt((DR*DR+DG*DG+DB*DB)/3);

					maxD = max(maxD, nodeMatrix[i][j].D[d]);
				}
			}

	for (int i=1;i<height-1;i++)
		for (int j=1;j<width-1;j++)
			for (int d=0;d<8;d++){
				nodeMatrix[i][j].linkCost[d] = ( maxD - nodeMatrix[i][j].D[d]);
				if (d%2==0)
					nodeMatrix[i][j].linkCost[d] *= 1;
				else
					nodeMatrix[i][j].linkCost[d] *= sqrt(2);
			}
}

void ISDoc::initStates(){
	for (int i=0;i<height;i++)
		for (int j=0;j<width;j++){
			nodeMatrix[i][j].totalCost = -1;
			nodeMatrix[i][j].preNode = NULL;
			nodeMatrix[i][j].state = INITIAL;
		}
}

void ISDoc::calcCostTree(int row,int col){
	for (int i=1;i<height;i++)
		for (int j=1;j<width;j++)
			if (nodeMatrix[i][j].drawed)
				cout << "("<<i<<","<<j<<")  ";


	if(seed!=NULL)
		delete seed;
	seed=new Point;
	seed->row=row;
	seed->col=col;
	Node x;
	int di,dj;
	initStates();
	cout << "seed: "<<row << " " << col << endl;
	q.push(nodeMatrix[row][col]);
	nodeMatrix[row][col].state = ACTIVE; nodeMatrix[row][col].totalCost = 0;
	while (!q.empty()){
		x=q.top(); q.pop();
		nodeMatrix[x.row][x.col].state = EXPANDED;
		for (int d=0;d<8;d++){
			di = x.row + dir[d][0]; dj = x.col + dir[d][1];
			if (di<=0 || dj<=0 || di>=height-1 || dj>=width-1) continue;
			if (nodeMatrix[di][dj].state ==EXPANDED) continue;
			if (nodeMatrix[di][dj].drawed ==true) continue;
			if (nodeMatrix[di][dj].state == INITIAL){
				nodeMatrix[di][dj].state = ACTIVE;
				nodeMatrix[di][dj].preNode = &nodeMatrix[x.row][x.col];
				nodeMatrix[di][dj].totalCost = x.totalCost + x.linkCost[d];
				q.push(nodeMatrix[di][dj]);
			}else{
				if (nodeMatrix[di][dj].totalCost > x.totalCost + x.linkCost[d]){
					nodeMatrix[di][dj].totalCost = x.totalCost + x.linkCost[d];
					nodeMatrix[di][dj].preNode = &nodeMatrix[x.row][x.col];
				}
			}
		}
	}
	// cout << "c1" << endl;
	// for (int i=height-2;i>0;i--,cout<<endl)
	// 	for (int j=1;j<width-1;j++)
	// 		cout<<(int)nodeMatrix[i][j].c1/32<<' ';

	// for (int i=height-2;i>0;i--,cout<<endl)
	// 	for (int j=1;j<width-1;j++)
	// 		cout<<(int)nodeMatrix[i][j].linkCost[1]/2 <<' ';
	// cout<<"\n\n\n\n";
	// for (int i=height-2;i>0;i--,cout<<endl)	
	// 	for (int j=1;j<width-1;j++)
	// 		cout<<(int)nodeMatrix[i][j].totalCost/350<<' ';
}

void ISDoc::drawContour(int row,int col)
{
	cout << "drawContour" << endl;
	if(last!=NULL)
	{
		cout << "last != NULL" << endl;
		Node* p=&nodeMatrix[last->row][last->col];
		while( p->row!=seed->row || p->col!=seed->col )
		{
			p->drawed=false;
			p=p->preNode;
		}
		last=NULL;///////
	}
	if(nodeMatrix[row][col].drawed==false)
	{
		cout << "node.drawed = false" << endl;
		last=new Point;
		last->row=row;
		last->col=col;
		Node *p=&nodeMatrix[last->row][last->col];
		while( p->row!=seed->row || p->col!=seed->col )
		{
			cout << p->row << " " << p->col << "draw" << endl;
			p->drawed=true;
			p=p->preNode;
		}
	}
	refreshCurmap();
}


