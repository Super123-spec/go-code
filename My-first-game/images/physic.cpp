#include<graphics.h>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<cmath>
//#include<vector>
//#include<EasyX.h>

#define high 800//�����ĸ߶�
#define width 1200//�����Ŀ��
#define ECOLLIDE 0.2//��ײ�ָ�ϵ��
#define EFRICTION 0.7//��Ħ������
#define G 1//�������ٶ�
#define GND 6;

IMAGE gmod;//ͼ��
IMAGE facebook;
IMAGE lenovo;
IMAGE andriod;
IMAGE zfb;
IMAGE ae;
IMAGE app;
IMAGE bluecircle;
IMAGE bluecircle2;
IMAGE laser;
IMAGE head;
IMAGE hand;
IMAGE body;
IMAGE shield;
IMAGE bullet1;
IMAGE bullet2;
IMAGE bullet3;
IMAGE bluestar;
IMAGE bluetick;
IMAGE earth;
IMAGE garbage;
IMAGE greencircle;
IMAGE greencircle2;
IMAGE greentick;
IMAGE txhy;
IMAGE warning;
IMAGE background;
IMAGE black;
MOUSEMSG m;

struct vector {
	double x;
	double y;
};

struct player {//player������ת���ص�Ӱ��
	double x, y,st;//��������,�Ƕ�
	double w, h;//�ߣ���   ����x+w y+h ����x+w y-h����x-w y+h ����x-w y-h
	double zsx, zsy,zxx,zxy,ysx,ysy,yxx,yxy;
	vector v;//xy�ٶ�
	vector a;//xy���ٶ�
	double wv,wa;//���ٶȣ��Ǽ��ٶ�
	vector f;
	double fm;//������������,����Ϊ��ʱ����ʱ����ת
	double m;//����
	double j;//ת������
};

struct npc {
	double x, y;
	double h, w;
	double vx, vy;
	double ax, ay;
	double m;
};

struct bullet {

};

struct entity {

};


struct circles {
	double x, y;
	double r;
	double vx, vy;
	double w;
	double m;
};

struct dbx {//�����   �����������ʱһ��Ҫ������˳ʱ���趨�����򽫲������ص�bug!!!
	double xg, yg,st;//��������,�Ƕ�
	int dotnum;//�ö�����м����߽ڵ�
	double xcon[20], ycon[20];//�߽ڵ��xy����(������ĵĲο�ϵ)��һ�������������20���߽ڵ�,��20���ڵ��ֵ��ģ���в������޸ģ����򽫸ı���ײ�������״
	//ע����������һ���������ĵ����Ϸ���20,70���������ڳ�ʼ��ʱ��
	double xact[20], yact[20];//�߽ڵ���ģ���е�ʵ������
	vector v;//xy�ٶ�
	vector a;//xy���ٶ�
	double wv, wa;//���ٶȣ��Ǽ��ٶ�
	vector f;//����
	double fm;//������,����Ϊ��ʱ����ʱ����ת
	double m;//����
	double i;//ת������

	double collidewv;
	vector collidev;//����������ײ�ж�����phyupd�и��µ������κ�ʱ��һ��collide��ʼ��ʱ�򣬶�Ӧ���Ȱ�����������Ϊ��
	double test;
};

struct map {

};

struct camera {
	double x, y;
};

struct ground {//������Ϊ2000
	double x[500];//һ��ground���ӵ��500���ڵ�
	double y[500];
};

struct car {
	circles backwheel;
	circles frontwheel;
	dbx carbody;
};

//player ply;
dbx ply;
dbx rec;
dbx dimian;
camera camera;
ground gnd;
vector rp;
double st = 0;



//�ж������߶��Ƿ��ཻ�ĺ���
int cross(double Ax1, double Ay1, double Ax2, double Ay2, double Bx1, double By1, double Bx2, double By2)
{
	if (
		(max(Ax1, Ax2) >= min(Bx1, Bx2) && min(Ax1, Ax2) <= max(Bx1, Bx2)) &&  //�ж�x��ͶӰ
		(max(Ay1, Ay2) >= min(By1, By2) && min(Ay1, Ay2) <= max(By1, By2))    //�ж�y��ͶӰ
		)
	{
		if (
			((Bx1 - Ax1) * (Ay2 - Ay1) - (By1 - Ay1) * (Ax2 - Ax1)) *          //�ж�B�Ƿ���A
			((Bx2 - Ax1) * (Ay2 - Ay1) - (By2 - Ay1) * (Ax2 - Ax1)) <= 0 &&
			((Ax1 - Bx1) * (By2 - By1) - (Ay1 - By1) * (Bx2 - Bx1)) *          //�ж�A�Ƿ���B
			((Ax2 - Bx1) * (By2 - By1) - (Ay2 - By1) * (Bx2 - Bx1)) <= 0
			)
		{
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}


//�������й���������ĺ���.......
vector setvector(double a, double b) {
	vector pl;
	pl.x = a;
	pl.y = b;
	return pl;
}

vector fillvector(double x1,double y1,double x2, double y2) {//������1ָ��2������
	vector pl;
	pl.x = x2-x1;
	pl.y = y2-y1;
	return pl;
}

vector muti(vector a, double r) {//��������
	vector pl;
	pl.x = a.x * r;
	pl.y = a.y * r;
	return pl;
}

vector plus(vector a, vector b) {//���������
	vector pl;
	pl.x = a.x + b.x;
	pl.y = a.y + b.y;
	return pl;
}

vector normalize(vector a) {//��һ��������λ��
	vector pl;
	pl.x = a.x / sqrt(a.x * a.x + a.y * a.y);
	pl.y = a.y / sqrt(a.x * a.x + a.y * a.y);
	return pl;
}

double dmuti(vector a,vector b) {//���������
	return a.x * b.x + a.y * b.y;
}

double cmuti(vector a, vector b) {//������a���b,����z�����������Է���double
	return a.y * b.x - a.x * b.y;
}

vector vertical(vector a) {//����a��ֱ�ĵ�λ����������Ϊa��ʱ����ת90��
	vector pl;
	pl.x = a.y;
	pl.y = -1 * a.x;
	pl = normalize(pl);
	return pl;
}
//�������й���������ĺ���.......

//�������йص�����µĺ���.......
ground groundinit(ground gnd) {
	int i;
	for (i = 0;i <= 499;i++) {
		gnd.x[i] = gnd.x[i] + i*GND;
		gnd.y[i] = 800;
	}
	return gnd;
}
ground groundupdate(ground gnd,dbx ply) {
	int i,random;
	while (gnd.x[250] <= ply.xg) {
		for (i = 0;i <= 498;i++) {
			gnd.x[i] = gnd.x[i] + GND;
			gnd.y[i] = gnd.y[i + 1];
		}
		gnd.x[499] = gnd.x[499] + GND;
		gnd.y[499] = gnd.y[499] - rand() %5;
	}
	
	return gnd;
}



void drawdbx(dbx a) {
	int i;
	for (i = 0;i <= a.dotnum - 2;i++) {
		line(a.xact[i] - camera.x, a.yact[i] - camera.y, a.xact[i + 1] - camera.x, a.yact[i + 1] - camera.y);
	}
	line(a.xact[a.dotnum - 1] - camera.x, a.yact[a.dotnum - 1] - camera.y, a.xact[0] - camera.x, a.yact[0] - camera.y);
}



void drawcircles(circles a) {
	circle(a.x, a.y, a.r);
	
}

void drawground(ground gnd){
	int i;
	for (i = 0;i <= 498;i++) {
		line(gnd.x[i] - camera.x, gnd.y[i] - camera.y, gnd.x[i + 1] - camera.x, gnd.y[i + 1] - camera.y);
	}
}

void show() {
	putimage(0,0, 1250, 850, &black, 0, 0);
	putimage(-camera.x, -camera.y, 4000, 1600, &background, 0, 0);
	//bar(ply.x-50 - camera.x, ply.y-50 - camera.y, ply.x - camera.x + 50, ply.y - camera.y + 50);
	loadimage(&gmod, _T("./images/gmod.jpg"), 50, 50, true);
	//rotateimage(&gmod, &gmod,-ply.st,true);
	
	//putimage(ply.xg - 25 - camera.x, ply.yg - 25 - camera.y, 50, 50, &gmod, 0, 0);
	
	circle(-camera.x, -camera.y,3);
	
	drawdbx(ply);
	drawdbx(rec);
	drawdbx(dimian);
	drawground(gnd);
	//line(ply.x - ply.w - camera.x, ply.y + ply.h - camera.y, ply.x - ply.w - camera.x, ply.y - ply.h - camera.y);
	//line(ply.x - ply.w - camera.x, ply.y + ply.h - camera.y, ply.x - ply.w - camera.x, ply.y - ply.h - camera.y);
	//line(ply.x - ply.w - camera.x, ply.y + ply.h - camera.y, ply.x - ply.w - camera.x, ply.y - ply.h - camera.y);
	TCHAR p[20];
	_stprintf_s(p, _T("%f"),ply.xg);
	outtextxy(10,30, p);
	_stprintf_s(p, _T("%f"),ply.yg);
	outtextxy(10, 50, p);
	_stprintf_s(p, _T("%f"),rp.x);
	outtextxy(10, 70, p);
	_stprintf_s(p, _T("%f"), rp.y);
	outtextxy(10, 90, p);
	_stprintf_s(p, _T("%f"), ply.wv);
	outtextxy(10, 130, p);
	_stprintf_s(p, _T("%f"), ply.collidewv);
	outtextxy(10, 150, p);

	FlushBatchDraw();
	Sleep(1);
}

void load() {
	loadimage(&background, _T("./images/background.jpg"), 4000, 1600, true);
	loadimage(&black, _T("./images/black.jpg"), 1250, 850, true);
	loadimage(&facebook, _T("./images/facebook.jpg"), 50, 50, true);
	loadimage(&gmod, _T("./images/gmod.jpg"), 50, 50, true);
	loadimage(&gmod, _T("./images/gmod.jpg"), 50, 50, true);
}

void startup() {
	gnd = groundinit(gnd);
	//�����ã���rec����ε���״��ʼ��
	rec.xg = 500;
	rec.yg = 100;
	rec.dotnum = 4;
	rec.xcon[0] = -40;
	rec.ycon[0] = -20;
	rec.xcon[1] = 40;
	rec.ycon[1] = -20;
	rec.xcon[2] = 40;
	rec.ycon[2] = 20;
	rec.xcon[3] = -40;
	rec.ycon[3] = 20;
	rec.m = 100;
	rec.i = 8000 * rec.m / 3;
	rec.test = 0;

	dimian.xg = 1000;
	dimian.yg = 800;
	dimian.dotnum = 4;
	dimian.xcon[0] = -100;
	dimian.ycon[0] = -200;
	dimian.xcon[1] = 100;
	dimian.ycon[1] = -200;
	dimian.xcon[2] = 100;
	dimian.ycon[2] = 200;
	dimian.xcon[3] = -100;
	dimian.ycon[3] = 200;
	dimian.m = 400;
	dimian.i = dimian.m * 50000 / 3;

	ply.xcon[0] = -25;
	ply.ycon[0] = -25;
	ply.xcon[1] = 25;
	ply.ycon[1] = -25;
	ply.xcon[2] = 25;
	ply.ycon[2] = 25;
	ply.xcon[3] = -25;
	ply.ycon[3] = 25;
	ply.dotnum = 4;
	ply.m = 100;
	ply.i = ply.m * 1250 / 3;
	initgraph(width, high);
	setfillcolor(YELLOW);
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 3);
	setcolor(YELLOW);
	load();
	BeginBatchDraw();
}

void startmenu() {

}

void pausemenu() {

}

void rotate(double x1, double y1, double x2, double y2, double st) {//1��2��ת����
	
	x1 = (x1 - x2) * cos(-st) - (y1 - y2) * sin(-st) + x2;
	
	y1 = (x1 - x2) * sin(-st) + (y1 - y2) * cos(-st) + y2;
}



player drotate(player ply) {//1��2��ת����
	ply.zsx = (-ply.w) * cos(-ply.st) - (-ply.h) * sin(-ply.st) + ply.x;
	ply.zsy = (-ply.w) * sin(-ply.st) + (-ply.h) * cos(-ply.st) + ply.y;
	ply.zxx = (-ply.w) * cos(-ply.st) - (+ply.h) * sin(-ply.st) + ply.x;
	ply.zxy = (-ply.w) * sin(-ply.st) + (+ply.h) * cos(-ply.st) + ply.y;
	ply.ysx = (ply.w) * cos(-ply.st) - (-ply.h) * sin(-ply.st) + ply.x;
	ply.ysy = (ply.w) * sin(-ply.st) + (-ply.h) * cos(-ply.st) + ply.y;
	ply.yxx = (ply.w) * cos(-ply.st) - (+ply.h) * sin(-ply.st) + ply.x;
	ply.yxy = (ply.w) * sin(-ply.st) + (+ply.h) * cos(-ply.st) + ply.y;
	return ply;
}

dbx dbxrotate(dbx ply) {//���������������ϵ�����������뵱ǰ�Ƕȣ�������߽ڵ��ʵ������
	int i;
	for (i = 0;i <= ply.dotnum - 1;i++) {
		ply.xact[i] = (ply.xcon[i]) * cos(-ply.st) - (ply.ycon[i]) * sin(-ply.st)+ ply.xg;
		ply.yact[i] = (ply.xcon[i]) * sin(-ply.st) + (ply.ycon[i]) * cos(-ply.st)+ ply.yg;
	}
	return ply;
}

void camerachange(double x,double y) {//�����׼�ĸ�������������Ƕ�������-600-400����show��ͼ�����У��������궼Ҫ��ȥ
	camera.x = x-600;
	camera.y = y-400;
}

void smocamerachange(double x,double y) {//�����׼�ĸ�������������Ƕ�������-600-400����show��ͼ�����У��������궼Ҫ��ȥ
	camera.x = camera.x+0.2*(x-600-camera.x);
	camera.y = camera.y + 0.2 * (y - 400 - camera.y);
}

void force() {

}


//��ײ�ж��븳ֵ����  collide and anticollide
dbx anticollide(dbx a, dbx b) {//anti�ı�b��collide����������a��,���ಿ��ֱ���հ�collide�����ж���

	vector ra;//a�����ĵ�a�ĵ�ǰ�о��߽ڵ������
	ra = setvector(0, 0);
	vector rafa;//ra�ķ�����
	vector rb;//b�����ĵ�a�ĵ�ǰ�о��߽ڵ������
	vector rbfa;//rb�ķ�����
	vector lineb;//b�ĵ�ǰ�о�������
	vector n;//b�ĵ�ǰ�о��������ĵ�λ������
	vector r;//b�ĵ�ǰ�о��������ĵ�λ��������
	vector s;//��b���о�����ʼ��ָ��a�ĵ�ǰ�о��߽ڵ������
	vector dotspeeda;//a�ĵ�ǰ�о��߽ڵ����a���ĵ��ٶ�����
	vector dotspeedb;//a�ĵ�ǰ�о��߽ڵ��ͶӰ����b���ĵ��ٶ�����
	vector temp1;
	vector temp2;
	vector temp3;

	double vr;//a�ĵ�ǰ�о��߽ڵ���b�ĵ�ǰ�о���������ķ�������ٶ�
	double J;//����ó����յķ������

	int i, j;//i��a�߽ڵ����������j��b��������������
	for (i = 0;i <= a.dotnum - 1;i++) {
		for (j = 0;j <= b.dotnum - 1;j++) {
			//�趨Ҫ�о���b������
			if (j == b.dotnum - 1) {
				lineb = fillvector(b.xact[j], b.yact[j], b.xact[0], b.yact[0]);
			}
			else {
				lineb = fillvector(b.xact[j], b.yact[j], b.xact[j + 1], b.yact[j + 1]);
			}
			//�����b�������ĵ�λ���������͵�λ������
			r = normalize(lineb);
			n = vertical(lineb);
			s = fillvector(b.xact[j], b.yact[j], a.xact[i], a.yact[i]);



			if (dmuti(s, n) <= 0 and dmuti(s, n) >= -15) {

				if (dmuti(s, r) >= 0 and dmuti(s, r) <= sqrt(lineb.x * lineb.x + lineb.y * lineb.y)) {
					ra = fillvector(a.xg, a.yg, a.xact[i], a.yact[i]);
					rafa = vertical(ra);
					dotspeeda = plus(a.v, muti(rafa, a.wv * sqrt(ra.x * ra.x + ra.y * ra.y)));
					rb = fillvector(b.xg, b.yg, a.xact[i], a.yact[i]);
					rbfa = vertical(rb);
					dotspeedb = plus(b.v, muti(rbfa, b.wv * sqrt(rb.x * rb.x + rb.y * rb.y)));
					vr = dmuti(n, plus(dotspeeda, muti(dotspeedb, -1)));
					if (vr < 0 and dmuti(ra, n) <= 0) {//��������ٶ��ж�
						temp1 = setvector(-ra.y * (ra.x * n.y - ra.y * n.x), ra.x * (ra.x * n.y - n.x * ra.y));
						temp1 = muti(temp1, 1 / a.i);
						temp2 = setvector(-rb.y * (rb.x * n.y - rb.y * n.x), rb.x * (rb.x * n.y - n.x * rb.y));
						temp2 = muti(temp2, 1 / b.i);
						J = (-vr * (1 + ECOLLIDE)) / ((1 / a.m) + (1 / b.m) + dmuti(n, temp1) + dmuti(n, temp2));
						b.collidev = plus(b.collidev, muti(n, -J / b.m));
						b.collidewv = b.collidewv + (cmuti(rb, muti(n, -J)) / b.i);
						temp3 = muti(n, dmuti(s, n));
						temp3 = muti(temp3, a.m / ((a.m + b.m)*4));
						b.xg = b.xg + temp3.x;
						b.yg = b.yg + temp3.y;
					}
				}
			}



		}
	}

	return b;
}









dbx collide(dbx a,dbx b) {//�ж�a��b�Ƿ�����ײ������ֻ����a��collide����
	vector ra;//a�����ĵ�a�ĵ�ǰ�о��߽ڵ������
	ra = setvector(0, 0);
	vector rafa;//ra�ķ�����
	vector rb;//b�����ĵ�a�ĵ�ǰ�о��߽ڵ������
	vector rbfa;//rb�ķ�����
	vector lineb;//b�ĵ�ǰ�о�������
	vector n;//b�ĵ�ǰ�о��������ĵ�λ������
	vector r;//b�ĵ�ǰ�о��������ĵ�λ��������
	vector s;//��b���о�����ʼ��ָ��a�ĵ�ǰ�о��߽ڵ������
	vector dotspeeda;//a�ĵ�ǰ�о��߽ڵ����a���ĵ��ٶ�����
	vector dotspeedb;//a�ĵ�ǰ�о��߽ڵ��ͶӰ����b���ĵ��ٶ�����
	vector temp1;
	vector temp2;
	vector temp3;
	
	double vr;//a�ĵ�ǰ�о��߽ڵ���b�ĵ�ǰ�о���������ķ�������ٶ�
	double J;//����ó����յķ������

	int i, j,k;//i��a�߽ڵ����������jk��b��������������,havedone�����ж��Ƿ�ִ��anticollide��havedone=1ʱ��ִ��
	int havedone = 0;

	for (i = 0;i <= a.dotnum - 1;i++) {
		for (j = 0;j <= b.dotnum - 1;j++) {
			//�趨Ҫ�о���b������
			if (j == b.dotnum - 1) {
				lineb = fillvector(b.xact[j], b.yact[j], b.xact[0], b.yact[0]);
			}
			else {
				lineb = fillvector(b.xact[j], b.yact[j], b.xact[j + 1], b.yact[j + 1]);
			}
			//�����b�������ĵ�λ���������͵�λ������
			r = normalize(lineb);
			n = vertical(lineb);
			s = fillvector(b.xact[j], b.yact[j], a.xact[i], a.yact[i]);
			
			

			if (dmuti(s, n) <= 0 and dmuti(s, n)>=-15) {
				
				if (dmuti(s, r) >= 0 and dmuti(s, r) <= sqrt(lineb.x * lineb.x + lineb.y * lineb.y)) {
					ra = fillvector(a.xg, a.yg, a.xact[i], a.yact[i]);
					rafa = vertical(ra);
					dotspeeda = plus(a.v,muti(rafa, a.wv * sqrt(ra.x * ra.x + ra.y * ra.y)));
					rb = fillvector(b.xg, b.yg, a.xact[i], a.yact[i]);
					rbfa = vertical(rb);
					dotspeedb = plus(b.v,muti(rbfa, b.wv * sqrt(rb.x * rb.x + rb.y * rb.y)));
					vr = dmuti(n, plus(dotspeeda, muti(dotspeedb, -1)));
					if (vr < 0 and dmuti(ra, n) <= 0) {//��������ٶ��ж�
						temp1 = setvector(-ra.y * (ra.x * n.y - ra.y * n.x), ra.x * (ra.x * n.y - n.x * ra.y));
						temp1 = muti(temp1, 1 / a.i);
						temp2 = setvector(-rb.y * (rb.x * n.y - rb.y * n.x), rb.x * (rb.x * n.y - n.x * rb.y));
						temp2 = muti(temp2, 1 / b.i);
						J = (-vr * (1+ECOLLIDE)) / ((1 / a.m) + (1 / b.m) + dmuti(n, temp1) + dmuti(n, temp2));//���Jʵ������������С
						a.collidev = plus(a.collidev, muti(n, J / a.m));
						a.collidewv = a.collidewv + (cmuti(ra, muti(n, J)) / a.i);
						temp3 = muti(n, dmuti(s, n));
						temp3 = muti(temp3, b.m / (a.m + b.m)/4);
						a.xg = a.xg - temp3.x;
						a.yg = a.yg - temp3.y;
						havedone = 1;

						//�ǵ����������xy�����������������������⽫ӭ�ж���!!!!!!!!!!!
					}
				}
			}

			
			
		}
	}

	if (havedone == 0) {
		a=anticollide(b, a);
	}

	return a;
}

dbx sepaxis(dbx a, dbx b) {//WOW WOW WOW һ���ǳ��ɹ�����ײ��������ʹ˵�������������
	vector ra;//a�����ĵ�a�ĵ�ǰ�о��߽ڵ������
	ra = setvector(0, 0);
	vector rafa;//ra�ķ�����
	vector rb;//b�����ĵ�a�ĵ�ǰ�о��߽ڵ������
	vector rbfa;//rb�ķ�����
	vector line;//��ǰ�о�������
	vector n;//b�ĵ�ǰ�о��������ĵ�λ������
	vector r;//b�ĵ�ǰ�о��������ĵ�λ��������
	vector s;//��b���о�����ʼ��ָ��a�ĵ�ǰ�о��߽ڵ������
	vector dotspeeda;//a�ĵ�ǰ�о��߽ڵ����a���ĵ��ٶ�����
	vector dotspeedb;//a�ĵ�ǰ�о��߽ڵ��ͶӰ����b���ĵ��ٶ�����
	vector temp1;
	vector temp2;
	vector temp3;
	vector templine;vector templiner;vector tempn;double tex=0;double tey=0; double distance = 10000;int type=0;//type=0��a��1��b
	double maxa=-10000, mina=10000, maxb=-10000, minb=10000;
	vector temp4;
	vector gline;//������������
	dbx* td;

	temp3 = setvector(0, 0);
	tempn = setvector(0, 0);
	templiner = setvector(0, 0);
	templine = setvector(0, 0);
	
	double vr;//a�ĵ�ǰ�о��߽ڵ���b�ĵ�ǰ�о���������ķ�������ٶ�
	double J;//����ó����յķ������

	int i, j, k,l;//i��a�߽ڵ����������jk��b��������������,havedone�����ж��Ƿ�ִ��anticollide��havedone=1ʱ��ִ��
	int havedone = 0;

	for (i = 0;i <= a.dotnum - 1;i++) {//a(i)
		maxa = -10000, mina = 10000, maxb = -10000, minb = 10000;
		if (i == a.dotnum - 1) {
			line = fillvector(a.xact[i], a.yact[i], a.xact[0], a.yact[0]);
		}
		else {
			line = fillvector(a.xact[i], a.yact[i], a.xact[i + 1], a.yact[i + 1]);
		}

		//�����a�������ĵ�λ���������͵�λ������
		r = normalize(line);
		n = vertical(line);
		
		for (j = 0;j <= a.dotnum - 1;j++) {//��a�����е�ͶӰ���÷�����,�����������Сֵ
			temp4 = fillvector(a.xact[i], a.yact[i], a.xact[j], a.yact[j]);
			if (dmuti(temp4, n) >= maxa) {
				maxa = dmuti(temp4, n);
			}
			if (dmuti(temp4, n) <= mina) {
				mina = dmuti(temp4, n);
			}
		}

		for (j = 0;j <= b.dotnum - 1;j++) {//��b�����е�ͶӰ��a������,�����������Сֵ
			temp4 = fillvector(a.xact[i], a.yact[i], b.xact[j], b.yact[j]);
			if (dmuti(temp4, n) >= maxb) {
				maxb = dmuti(temp4, n);
			}
			if (dmuti(temp4, n) <= minb) {
				minb = dmuti(temp4, n);
			}
		}

		//�������ж�ab��ֵ�Ƿ��ཻ�������������ֹ����
		if (maxa <= minb or maxb <= mina) {
			return a;
		}
		//�����ص�����,��ǵ�ǰ��
		gline = fillvector(a.xg, a.yg, b.xg, b.yg);
		if (min(abs(maxb - mina), abs(maxa - minb)) <= distance and dmuti(gline,n)>=0) {
			distance = min(abs(maxb - mina), abs(maxa - minb));
			templine = line;
			templiner = r;
			tempn = n;
			tex = a.xact[i];
			tey = a.yact[i];
			type = 0;
		}
	}

	
	//������������ת��b�߶�a�ж�
	for (i = 0;i <= b.dotnum - 1;i++) {//b(i)
		maxa = -10000, mina = 10000, maxb = -10000, minb = 10000;
		if (i == b.dotnum - 1) {
			line = fillvector(b.xact[i], b.yact[i], b.xact[0], b.yact[0]);
		}
		else {
			line = fillvector(b.xact[i], b.yact[i], b.xact[i + 1], b.yact[i + 1]);
		}

		//�����b�������ĵ�λ���������͵�λ������
		r = normalize(line);
		n = vertical(line);

		for (j = 0;j <= b.dotnum - 1;j++) {//��b�����е�ͶӰ���÷�����,�����������Сֵ
			temp4 = fillvector(b.xact[i], b.yact[i], b.xact[j], b.yact[j]);
			if (dmuti(temp4, n) >= maxb) {
				maxb = dmuti(temp4, n);
			}
			if (dmuti(temp4, n) <= minb) {
				minb = dmuti(temp4, n);
			}
		}

		for (j = 0;j <= a.dotnum - 1;j++) {//��a�����е�ͶӰ��b������,�����������Сֵ
			temp4 = fillvector(b.xact[i], b.yact[i], a.xact[j], a.yact[j]);
			if (dmuti(temp4, n) >= maxa) {
				maxa = dmuti(temp4, n);
			}
			if (dmuti(temp4, n) <= mina) {
				mina = dmuti(temp4, n);
			}
		}

		//�������ж�ab��ֵ�Ƿ��ཻ�������������ֹ����
		if (maxa <= minb or maxb <= mina) {
			return a;
		}
		//�����ص�����,��ǵ�ǰ��
		gline = fillvector(b.xg, b.yg, a.xg, a.yg);
		if (min(abs(maxb - mina), abs(maxa - minb)) <= distance and dmuti(gline, n) >= 0) {
			//�洢������Ҫ����Ϣ
			distance = min(abs(maxb - mina), abs(maxa - minb));
			templine = line;
			templiner = r;
			tempn = n;
			tex = b.xact[i];
			tey = b.yact[i];
			type = 1;
		}
	}

	//���ˣ�����ȷ������ײ�߼��䷨�������Լ����Ÿ÷������Ŀ�Խ���룬֮�����a��b�Ĳ������¼���

	
	if (type == 0) {//˵����a�ıߣ���ʱ����һ��b�ı߽ڵ㣬a������������
		for (i = 0;i <= b.dotnum - 1;i++) {
			s = fillvector(tex, tey, b.xact[i], b.yact[i]);
			if (dmuti(s, tempn) <= 0) {
				if (dmuti(s, templiner) >= 0 and dmuti(s, templiner) <= sqrt(templine.x * templine.x + templine.y * templine.y)) {
					//�˴���ʼͬʱ����a��b�Ĳ�������
					ra = fillvector(a.xg, a.yg, b.xact[i], b.yact[i]);
					rafa = vertical(ra);
					dotspeeda = plus(a.v, muti(rafa, a.wv * sqrt(ra.x * ra.x + ra.y * ra.y)));
					rb = fillvector(b.xg, b.yg, b.xact[i], b.yact[i]);
					rbfa = vertical(rb);
					dotspeedb = plus(b.v, muti(rbfa, b.wv * sqrt(rb.x * rb.x + rb.y * rb.y)));
					vr = dmuti(tempn, plus(dotspeeda, muti(dotspeedb, -1)));
					if (vr > 0) {//��������ٶ��ж�
						temp1 = setvector(-ra.y * (ra.x * tempn.y - ra.y * tempn.x), ra.x * (ra.x * tempn.y - tempn.x * ra.y));
						temp1 = muti(temp1, 1 / a.i);
						temp2 = setvector(-rb.y * (rb.x * tempn.y - rb.y * tempn.x), rb.x * (rb.x * tempn.y - tempn.x * rb.y));
						temp2 = muti(temp2, 1 / b.i);
						J = (-vr * (1 + ECOLLIDE)) / ((1 / a.m) + (1 / b.m) + dmuti(tempn, temp1) + dmuti(tempn, temp2));//���Jʵ������������С
						
						a.collidev = plus(a.collidev, muti(tempn, J / a.m));
						a.collidewv = a.collidewv + (cmuti(ra, muti(tempn, J)) / a.i);

					}
				}
			}
		}
	}

	if (type == 1) {//˵����b�ıߣ���ʱ����һ��a�ı߽ڵ㣬a������������
		for (i = 0;i <= a.dotnum - 1;i++) {
			s = fillvector(tex, tey, a.xact[i], a.yact[i]);
			if (dmuti(s, tempn) <= 0) {
				if (dmuti(s, templiner) >= 0 and dmuti(s, templiner) <= sqrt(templine.x * templine.x + templine.y * templine.y)) {
					//�˴���ʼͬʱ����a��b�Ĳ�������
					rb = fillvector(b.xg, b.yg, a.xact[i], a.yact[i]);
					rbfa = vertical(rb);
					dotspeedb = plus(b.v, muti(rbfa, b.wv * sqrt(rb.x * rb.x + rb.y * rb.y)));
					ra = fillvector(a.xg, a.yg, a.xact[i], a.yact[i]);
					rafa = vertical(ra);
					dotspeeda = plus(a.v, muti(rafa, a.wv * sqrt(ra.x * ra.x + ra.y * ra.y)));
					vr = dmuti(tempn, plus(dotspeedb, muti(dotspeeda, -1)));
					if (vr > 0) {//��������ٶ��ж�
						temp1 = setvector(-rb.y * (rb.x * tempn.y - rb.y * tempn.x), rb.x * (rb.x * tempn.y - tempn.x * rb.y));
						temp1 = muti(temp1, 1 / b.i);
						temp2 = setvector(-ra.y * (ra.x * tempn.y - ra.y * tempn.x), ra.x * (ra.x * tempn.y - tempn.x * ra.y));
						temp2 = muti(temp2, 1 / a.i);
						J = (-vr * (1 + ECOLLIDE)) / ((1 / a.m) + (1 / b.m) + dmuti(tempn, temp1) + dmuti(tempn, temp2));//���Jʵ������������С
						a.collidev = plus(a.collidev, muti(tempn, -J / a.m));
						a.collidewv = a.collidewv - (cmuti(ra, muti(tempn, J)) / a.i);
						

					}
				}
			}
		}
	}

	//������ٶȸ�����Ϻ����ŷ�������������״
	if (type == 0) {
		temp3 = muti(tempn, distance);
		temp3 = muti(temp3, b.m / (a.m + b.m));
		a.xg = a.xg - temp3.x;
		a.yg = a.yg - temp3.y;
		
	}
	if (type == 1) {
		temp3 = muti(tempn, distance);
		temp3 = muti(temp3, b.m / (a.m + b.m));
		a.xg = a.xg + temp3.x;
		a.yg = a.yg + temp3.y;
	}
	return a;
}



dbx groundanticollide(ground a, dbx b) {//anti�ı�b��collide����������a��,���ಿ��ֱ���հ�collide�����ж���

	vector ra;//a�����ĵ�a�ĵ�ǰ�о��߽ڵ������
	ra = setvector(0, 0);
	vector rafa;//ra�ķ�����
	vector rb;//b�����ĵ�a�ĵ�ǰ�о��߽ڵ������
	vector rbfa;//rb�ķ�����
	vector lineb;//b�ĵ�ǰ�о�������
	vector n;//b�ĵ�ǰ�о��������ĵ�λ������
	vector r;//b�ĵ�ǰ�о��������ĵ�λ��������
	vector s;//��b���о�����ʼ��ָ��a�ĵ�ǰ�о��߽ڵ������
	vector dotspeeda;//a�ĵ�ǰ�о��߽ڵ����a���ĵ��ٶ�����
	vector dotspeedb;//a�ĵ�ǰ�о��߽ڵ��ͶӰ����b���ĵ��ٶ�����
	vector temp1;
	vector temp2;
	vector temp3;

	double vr;//a�ĵ�ǰ�о��߽ڵ���b�ĵ�ǰ�о���������ķ�������ٶ�
	double J;//����ó����յķ������

	int i, j;//i��a�߽ڵ����������j��b��������������
	for (i = 100;i <= 399;i++) {
		for (j = 0;j <= b.dotnum - 1;j++) {
			//�趨Ҫ�о���b������
			if (j == b.dotnum - 1) {
				lineb = fillvector(b.xact[j], b.yact[j], b.xact[0], b.yact[0]);
			}
			else {
				lineb = fillvector(b.xact[j], b.yact[j], b.xact[j + 1], b.yact[j + 1]);
			}
			//�����b�������ĵ�λ���������͵�λ������
			r = normalize(lineb);
			n = vertical(lineb);
			s = fillvector(b.xact[j], b.yact[j], a.x[i], a.y[i]);



			if (dmuti(s, n) <= 0 and dmuti(s, n) >= -15) {

				if (dmuti(s, r) >= 0 and dmuti(s, r) <= sqrt(lineb.x * lineb.x + lineb.y * lineb.y)) {
					ra = fillvector(0, 2000, a.x[i], a.y[i]);
					rafa = vertical(ra);
					
					rb = fillvector(b.xg, b.yg, a.x[i], a.y[i]);
					rbfa = vertical(rb);
					dotspeedb = plus(b.v, muti(rbfa, b.wv * sqrt(rb.x * rb.x + rb.y * rb.y)));
					vr = dmuti(n, muti(dotspeedb, -1));
					if (vr < 0 and dmuti(ra, n) <= 0) {//��������ٶ��ж�
						
						temp2 = setvector(-rb.y * (rb.x * n.y - rb.y * n.x), rb.x * (rb.x * n.y - n.x * rb.y));
						temp2 = muti(temp2, 1 / b.i);
						J = (-vr * (1 + ECOLLIDE)) / ((1 / b.m) + dmuti(n, temp2));
						b.collidev = plus(b.collidev, muti(n, -J / b.m));
						b.collidewv = b.collidewv + (cmuti(rb, muti(n, -J)) / b.i);
						temp3 = muti(n, dmuti(s, n));
						temp3 = muti(temp3, 1/4);
						b.xg = b.xg + temp3.x;
						b.yg = b.yg + temp3.y;
					}
				}
			}



		}
	}

	return b;
}

dbx groundcollide(dbx a, ground gnd) {
	vector ra;//a�����ĵ�a�ĵ�ǰ�о��߽ڵ������
	ra = setvector(0, 0);
	vector rafa;//ra�ķ�����
	vector rb;//b�����ĵ�a�ĵ�ǰ�о��߽ڵ������
	vector rbfa;//rb�ķ�����
	vector lineb;//b�ĵ�ǰ�о�������
	vector n;//b�ĵ�ǰ�о��������ĵ�λ������
	vector r;//b�ĵ�ǰ�о��������ĵ�λ��������
	vector s;//��b���о�����ʼ��ָ��a�ĵ�ǰ�о��߽ڵ������
	vector dotspeeda;//a�ĵ�ǰ�о��߽ڵ����a���ĵ��ٶ�����
	vector dotspeedb;//a�ĵ�ǰ�о��߽ڵ��ͶӰ����b���ĵ��ٶ�����
	vector temp1;
	vector temp2;
	vector temp3;

	double vr;//a�ĵ�ǰ�о��߽ڵ���b�ĵ�ǰ�о���������ķ�������ٶ�
	double J;//����ó����յķ������

	int i, j, k;//i��a�߽ڵ����������jk��b��������������,havedone�����ж��Ƿ�ִ��anticollide��havedone=1ʱ��ִ��
	int havedone = 0;

	for (i = 0;i <= a.dotnum - 1;i++) {
		for (j = 100;j <= 399;j++) {
			//�趨Ҫ�о���gnd������
			
			lineb = fillvector(gnd.x[j], gnd.y[j], gnd.x[j + 1], gnd.y[j + 1]);
			
			//�����gnd�������ĵ�λ���������͵�λ������
			r = normalize(lineb);
			n = vertical(lineb);
			s = fillvector(gnd.x[j], gnd.y[j], a.xact[i], a.yact[i]);



			if (dmuti(s, n) <= 0 and dmuti(s, n) >= -15) {

				if (dmuti(s, r) >= 0 and dmuti(s, r) <= sqrt(lineb.x * lineb.x + lineb.y * lineb.y)) {
					ra = fillvector(a.xg, a.yg, a.xact[i], a.yact[i]);
					rafa = vertical(ra);
					dotspeeda = plus(a.v, muti(rafa, a.wv * sqrt(ra.x * ra.x + ra.y * ra.y)));
					rb = fillvector(0, 2000, a.xact[i], a.yact[i]);
					rbfa = vertical(rb);
					//dotspeedb = plus(b.v, muti(rbfa, b.wv * sqrt(rb.x * rb.x + rb.y * rb.y)));
					vr = dmuti(n,dotspeeda);
					if (vr < 0 and dmuti(ra, n) <= 0) {//��������ٶ��ж�
						temp1 = setvector(-ra.y * (ra.x * n.y - ra.y * n.x), ra.x * (ra.x * n.y - n.x * ra.y));
						temp1 = muti(temp1, 1 / a.i);
						
						J = (-vr * (1 + ECOLLIDE)) / ((1 / a.m) + dmuti(n, temp1));//���Jʵ������������С
						a.collidev = plus(a.collidev, muti(n, J / a.m));
						a.collidewv = a.collidewv + (cmuti(ra, muti(n, J)) / a.i);
						temp3 = muti(n, dmuti(s, n));
						temp3 = muti(temp3, 1 / 4);
						a.xg = a.xg - temp3.x;
						a.yg = a.yg - temp3.y;
						havedone = 1;

						//�ǵ����������xy�����������������������⽫ӭ�ж���!!!!!!!!!!!
					}
				}
			}



		}
	}

	if (havedone == 0) {
		a = groundanticollide(gnd, a);
	}

	return a;
	
}

dbx dbxphyupd(dbx ply) {
	ply.fm = 0;
	ply.f = setvector(0, G*ply.m);
	ply.a = muti(ply.f, 1 / ply.m);
	ply.wa = ply.fm / ply.i;
	ply.v = plus(ply.v, ply.a);
	ply.v = plus(ply.v, ply.collidev);
	ply.wv = ply.wv + ply.wa;
	ply.wv = ply.wv + ply.collidewv;
	ply.xg = ply.xg + ply.v.x;
	ply.yg = ply.yg + ply.v.y;
	ply.st = ply.st + ply.wv;//�Ƕȸ���

	ply = dbxrotate(ply);


	ply.v.x = ply.v.x - 0.06 * ply.v.x;//������ԣ�������ģ�����ƺ�Ӧ��ɾ������
	ply.v.y = ply.v.y - 0.03 * ply.v.y;//������ԣ�������ģ�����ƺ�Ӧ��ɾ������


	if (ply.v.x <= 0.0001 and ply.v.x > 0) {
		ply.v.x = 0;
	}
	if (ply.v.y <= 0.0001 and ply.v.y > 0) {
		ply.v.y = 0;
	}


	
	//��ÿ��������µ������Ҫ��collide�������ã����ܽ�����һ��dt������
	ply.collidev = setvector(0, 0);
	ply.collidewv = 0;

	if (ply.yg > 1570) {
		ply.yg = 1570;
		ply.v.y = 0;
	}
	return ply;
}


player playerphyupd(player ply) {
	force();
	ply.fm = 10;
	ply.f = setvector(0, 1 * ply.m);
	ply.a = muti(ply.f, 1 / ply.m);
	ply.wa = ply.fm / ply.j;
	ply.v = plus(ply.v, ply.a);
	ply.wv = ply.wv + ply.wa;
	ply.x = ply.x + ply.v.x;
	ply.y = ply.y + ply.v.y;
	ply.st = ply.st + ply.wv;//�Ƕȸ���

	ply=drotate(ply);


	ply.v.x = ply.v.x - 0.06 * ply.v.x;//������ԣ�������ģ�����ƺ�Ӧ��ɾ������
	ply.v.y = ply.v.y - 0.03 * ply.v.y;//������ԣ�������ģ�����ƺ�Ӧ��ɾ������
	

	if (ply.v.x <= 0.0001 and ply.v.x > 0) {
		ply.v.x = 0;
	}
	if (ply.v.y <= 0.0001 and ply.v.y > 0) {
		ply.v.y = 0;
	}
	

	if (ply.y > 1570) {
		ply.y = 1570;
		ply.v.y = 0;
	}

	/*if (cross(0, 100, 1000, 500, ply.x + 25, ply.y + 25, ply.x - 25, ply.y - 25) == 1) {
		ply.vy = 0;
	}*/
	return ply;
}

void npcphyupd() {

}

void entityphyupd() {

}

void bulletphyupd() {

}


void updwithinput() {

	


	if (GetAsyncKeyState(VK_LEFT)){
		
		ply.v.x=ply.v.x-1;
	}

	if (GetAsyncKeyState(VK_RIGHT)){
		ply.v.x = ply.v.x + 1;
		
	}

	
	if (GetAsyncKeyState(VK_UP)){
		ply.v.y=ply.v.y-1;
		
	}
	
	if (GetAsyncKeyState(VK_DOWN)){
		ply.v.y = ply.v.y + 1;
		
	}
	if (GetAsyncKeyState(VK_SPACE)) {
		ply.v.y = -16;

	}
	if (GetAsyncKeyState('W')) {
		rotate(ply.xg,ply.yg,0,0,1);
		//drotate(st);
		st = st + 0.1;
		
	}
}

void updwithoutinput() {//withoutΪ����Լ��ģ��,��һ��dt����¼�
	rec=sepaxis(rec, dimian);
	dimian=sepaxis(dimian,rec);
	ply = sepaxis(ply, rec);
	rec = sepaxis(rec, ply);
	ply = sepaxis(ply, dimian);
	dimian = sepaxis(dimian, ply);
	//dimian = collide(dimian, ply);
	//ply = groundcollide(ply, gnd);


	ply=dbxphyupd(ply);
	rec = dbxphyupd(rec);
	dimian= dbxphyupd(dimian);

	gnd = groundupdate(gnd,ply);
	npcphyupd();
	entityphyupd();
	bulletphyupd();
	Sleep(1);
}


int main() {
	double x=200, y=100;
	ply.xg = 50;ply.yg = 50;
	printf("666");
	startup();

	
	//putimage(500,100,100,100,&gmod,20,20, NOTSRCERASE);
	//putimage(2, 2, 100, 100, &gmod, 50, 50, SRCINVERT);
	//putimage(0, 0, 4000, 1600, &background, 0, 0);//���£�����
	//bar(200, 100, 300, 300);
	

	while (1) {
		show();
		updwithinput();
		updwithoutinput();
		//camerachange(ply.x-ply.vx,ply.y-ply.vy);
		smocamerachange(ply.xg, ply.yg);
	}

	FlushBatchDraw();

	getchar();
	closegraph();
	return 0;
}