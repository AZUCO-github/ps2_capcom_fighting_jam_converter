#include	<windows.h>
#include	<stdio.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
void	decode_cfj_type01(unsigned char *,char *);



void	decode_cfj_type01(unsigned char *sbuf,char *fname)
{
	unsigned long		slen=*(unsigned long *)(sbuf+0x00);
	unsigned long		pchp=*(unsigned long *)(sbuf+0x10);
	unsigned long		ptmp=*(unsigned long *)(sbuf+0x14);
	unsigned long		cchp=(slen-pchp)/0x70;
	if(cchp>0x100)	cchp=0x100;

	unsigned long		xbmp=16;
	unsigned long		ybmp=cchp*8;
	char				nbmp[MAX_PATH];
	unsigned char *		bbmp;
	HANDLE				hbmp;
	BITMAPFILEHEADER	bf;
	BITMAPINFOHEADER	bi;

	unsigned long		tul1;

	unsigned long		cntx,cnty,cntz,cntc;
	unsigned long		pt01,pt02,pt03;


	bbmp=new unsigned char[ybmp*xbmp*4];	//x y c

	sprintf(nbmp,"%s.bmp",fname);
	hbmp=NonOverWriteCreateFile((LPCSTR)nbmp);

	*((char *)&bf.bfType+0)='B';
	*((char *)&bf.bfType+1)='M';
	bf.bfSize=			sizeof(BITMAPFILEHEADER)+
						sizeof(BITMAPINFOHEADER)+
						ybmp*xbmp*4;				//image
	bf.bfOffBits=		sizeof(BITMAPFILEHEADER)+
						sizeof(BITMAPINFOHEADER);

	bi.biSize=			sizeof(BITMAPINFOHEADER);
	bi.biWidth=			xbmp;
	bi.biHeight=		ybmp;
	bi.biPlanes=		1;
	bi.biBitCount=		32;
	bi.biCompression=	0;
	bi.biSizeImage=		0;
	bi.biXPelsPerMeter=	0;
	bi.biYPelsPerMeter=	0;
	bi.biClrUsed=		0;
	bi.biClrImportant=	0;

	WriteFile(hbmp,&bf,sizeof(BITMAPFILEHEADER),&tul1,NULL);
	WriteFile(hbmp,&bi,sizeof(BITMAPINFOHEADER),&tul1,NULL);

		pt03=0;
	for(cntc=0;cntc<cchp;cntc++){
		pt01=pchp+cntc*0x70;	//16c palette
		pt02=pt01+0x30;			//chip data

		for(cntz=0;cntz<0x40;cntz++){
			bbmp[pt03+0+0]=sbuf[pt01+cntz+(0+(sbuf[pt02]>>4  )*3)];
			bbmp[pt03+0+1]=sbuf[pt01+cntz+(1+(sbuf[pt02]>>4  )*3)];
			bbmp[pt03+0+2]=sbuf[pt01+cntz+(2+(sbuf[pt02]>>4  )*3)];
			bbmp[pt03+0+3]=0;
			bbmp[pt03+4+0]=sbuf[pt01+cntz+(0+(sbuf[pt02]&0x0f)*3)];
			bbmp[pt03+4+1]=sbuf[pt01+cntz+(1+(sbuf[pt02]&0x0f)*3)];
			bbmp[pt03+4+2]=sbuf[pt01+cntz+(2+(sbuf[pt02]&0x0f)*3)];
			bbmp[pt03+4+3]=0;

			pt03+=8;											}
	}

	WriteFile(hbmp,bbmp,xbmp*ybmp*4,&tul1,NULL);
	CloseHandle(hbmp);
	delete[]	bbmp;
}
