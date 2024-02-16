#include	<windows.h>
#include	<stdio.h>

extern	HANDLE	NonOverWriteCreateFile(LPCSTR);



void	tim2_uncompress(	unsigned char *sbuf,
							unsigned char *dbuf,
							unsigned long slen,
							unsigned long dlen	)
{	unsigned long	fv,fc;
	unsigned long	sa,sl,sc;
	unsigned long	sp=0;
	unsigned long	dp=0;

printf("uncompress ...\n");
	memset(dbuf,0x00,dlen);
	for(;;){
		fv=*(sbuf+sp);
		sp++;
		for(fc=0;fc<8;fc++){
			if((fv&1)==0){			//compress
				sl=3+(0x0f&*(sbuf+sp+1));
				sa=(((*(sbuf+sp+1))<<4)&0xf00)|(*(sbuf+sp));
				sc=(dp-sa-18)&0xfffff000;
				if(sc&0x80000000)	sc=0;

				if(dp<(sc+sa+18+sl))
						memset(dbuf+dp,*(dbuf+sc+sa+18),sl);
				else	memcpy(dbuf+dp,  dbuf+sc+sa+18, sl);

				dp+=sl;	sp+=2;						}
			else{
				dbuf[dp]=sbuf[sp];
				dp++;	sp++;						}
			fv>>=1;

			if(sp>=slen)	goto	UC_END;
			if(dp>=dlen)	goto	UC_END;
		}
	}
UC_END:
printf("SRC %08X/%08X\n",sp,slen);
printf("DST %08X/%08X\n",dp,dlen);

	dlen=dp;
}
