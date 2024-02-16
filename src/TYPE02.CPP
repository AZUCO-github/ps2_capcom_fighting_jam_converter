#include	<windows.h>
#include	<stdio.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);
extern	void	tim2_uncompress(	unsigned char *,	unsigned char *,
									unsigned long,		unsigned long);
void	decode_cfj_type02(unsigned char *,char *);



void	decode_cfj_type02(unsigned char *sbuf,char *fname)
{
	unsigned long		IMX=*(unsigned long *)(sbuf+0x00);
	unsigned long		INO;
	unsigned long		IAD;
	unsigned long		ILN;
	HANDLE				dhdl;
	char				name[MAX_PATH];
	unsigned long		tul1;

	for(INO=0;INO<IMX;INO++){
		IAD=*(unsigned long *)(sbuf+0x04+INO*0x08+0x00);
		ILN=*(unsigned long *)(sbuf+0x04+INO*0x08+0x04);

		if(	(sbuf[IAD+0]=='T')&&
			(sbuf[IAD+1]=='I')&&
			(sbuf[IAD+2]=='M')&&
			(sbuf[IAD+3]=='2')	)	sprintf(name,"%s.tm2",fname);
		else						sprintf(name,"%s_s.bin",fname);	//split

		dhdl=NonOverWriteCreateFile((LPCSTR)name);
		WriteFile(dhdl,sbuf+IAD,ILN,&tul1,NULL);
		CloseHandle(dhdl);
	}
}
