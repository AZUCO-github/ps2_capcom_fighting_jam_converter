///////////////////////////////////////////////////////////////////////////////
//	PS2 Capcom Fighting Jam file converter
//		061025
//			by	AZUCO
///////////////////////////////////////////////////////////////////////////////

#include	<windows.h>
#include	<stdio.h>

extern	void	decode_cfj_type01(unsigned char *,char *);
extern	void	decode_cfj_type02(unsigned char *,char *);
extern	bool	is_tim2		(unsigned char *,char *);
extern	void	decode_tim2	(unsigned char *,char *);


void	main(void)
{	char			file[_MAX_PATH];
	char			*tfpa;
	char			*tfpb;
	HANDLE			hndl;
	unsigned char	*buff=0;
	unsigned long	size;
	char			drive[MAX_PATH];
	char			dir[MAX_PATH];
	char			fname[MAX_PATH];
	char			ext[MAX_PATH];
	unsigned long	tmp;

	printf("PS2 Capcom Fighting Jam file converter\n");
	printf("\t\tProg. By AZUCO\n\n");



	strcpy(file,GetCommandLine());				//コマンドラインをコピーする

	tfpa=strrchr(file,' ');		//一番最後のスペース以降をファイル名と見なす
	tfpa++;

	tfpb=strrchr(tfpa,'"');		//ダブルクオートありの場合
	if(tfpb!=NULL)	*tfpb=0;

	tfpb=strrchr(tfpa,'>');		//リダイレクトの場合
	if(tfpb!=NULL)	*tfpb=0;



	tfpb=&file[0];
loop:
	if(*tfpa=='\\'){	*(tfpb+0)='\\';
						*(tfpb+1)='\\';
						tfpa++;
						tfpb+=2;
						goto loop;		}
	if(*tfpa>=0x20){	*tfpb=*tfpa;
						tfpa++;
						tfpb++;
						goto loop;		}
						*tfpb=0;



//strcpy(file,"E:\\TMP\\I100\\ETC\\K.NBP");

	hndl=CreateFile(file,
					GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hndl==(HANDLE)-1){
		printf("cfj <data file>\n");
		printf("\tError\tsource file not found\n");
		exit(-1);	}

	_splitpath(file,drive,dir,fname,ext);
	size=GetFileSize(hndl,NULL);
	buff=new unsigned char[size];
	ReadFile(hndl,buff,size,&tmp,NULL);
	CloseHandle(hndl);

	if(		 strcmp(_strlwr(ext),	".tm2")==0)
		decode_tim2(buff,(char *)fname);

	if(		 strcmp(_strlwr(ext),	".bin")==0){
		if(	(strcmp(_strlwr(fname),	"ingrid"	)==0)	||
			(strcmp(_strlwr(fname),	"pl00"		)==0)	||
			(strcmp(_strlwr(fname),	"pl00pack"	)==0)	||
			(strcmp(_strlwr(fname),	"pl02"		)==0)	||
			(strcmp(_strlwr(fname),	"pl02pack"	)==0)	||
			(strcmp(_strlwr(fname),	"pl03"		)==0)	||
			(strcmp(_strlwr(fname),	"pl03pack"	)==0)	||
			(strcmp(_strlwr(fname),	"pl04"		)==0)	||
			(strcmp(_strlwr(fname),	"pl04pack"	)==0)	||
			(strcmp(_strlwr(fname),	"pl07"		)==0)	||
			(strcmp(_strlwr(fname),	"pl0a"		)==0)	||
			(strcmp(_strlwr(fname),	"pl0apack"	)==0)	||
			(strcmp(_strlwr(fname),	"pl0b"		)==0)	||
			(strcmp(_strlwr(fname),	"pl0bpack"	)==0)	||
			(strcmp(_strlwr(fname),	"pl10pack"	)==0)	||
			(strcmp(_strlwr(fname),	"pl11pac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl12pac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl13pac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl14pac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl15pac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl16pac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl18pac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl19pac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl1apac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl1bpac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl1cpac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl1dpac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl1fpac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl22pac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl2cpac"	)==0)	||
			(strcmp(_strlwr(fname),	"pl2"		)==0)	||
			(strcmp(_strlwr(fname),	"pl2dpac"	)==0)	||
			(strcmp(_strlwr(fname),	"spl0"		)==0)	||
			(strcmp(_strlwr(fname),	"spl0"		)==0)	||
			(strcmp(_strlwr(fname),	"spl2"		)==0)	||
			(strcmp(_strlwr(fname),	"vpl0"		)==0)	||
			(strcmp(_strlwr(fname),	"vpl0"		)==0)	||
			(strcmp(_strlwr(fname),	"vpl0"		)==0)	||
			(strcmp(_strlwr(fname),	"vpl0"		)==0)	||
			(strcmp(_strlwr(fname),	"vpl1"		)==0)	||
			(strcmp(_strlwr(fname),	"wem0"		)==0)	||
			(strcmp(_strlwr(fname),	"wem0"		)==0)	||
			(strcmp(_strlwr(fname),	"wpl0"		)==0)	||
			(strcmp(_strlwr(fname),	"wpl0"		)==0)	||
			(strcmp(_strlwr(fname),	"zpl0"		)==0)	||
			(strcmp(_strlwr(fname),	"zpl0"		)==0)	||
			(strcmp(_strlwr(fname),	"zpl1"		)==0)		)
				decode_cfj_type01(buff,(char *)fname);

		if(	(strcmp(_strlwr(fname),	"ba01"		)==0)	||
			(strcmp(_strlwr(fname),	"co01"		)==0)	||
			(strcmp(_strlwr(fname),	"co02"		)==0)	||
			(strcmp(_strlwr(fname),	"cs00"		)==0)	||
			(strcmp(_strlwr(fname),	"cs00tex"	)==0)	||
			(strcmp(_strlwr(fname),	"cs01"		)==0)	||
			(strcmp(_strlwr(fname),	"cs02"		)==0)	||
			(strcmp(_strlwr(fname),	"cs03"		)==0)	||
			(strcmp(_strlwr(fname),	"cs04"		)==0)	||
			(strcmp(_strlwr(fname),	"cs05"		)==0)	||
			(strcmp(_strlwr(fname),	"cs06"		)==0)	||
			(strcmp(_strlwr(fname),	"cs07"		)==0)	||
			(strcmp(_strlwr(fname),	"cs08"		)==0)	||
			(strcmp(_strlwr(fname),	"cs09"		)==0)	||
			(strcmp(_strlwr(fname),	"cs10"		)==0)	||
			(strcmp(_strlwr(fname),	"ef00"		)==0)	||
			(strcmp(_strlwr(fname),	"ne01"		)==0)	||
//			(strcmp(_strlwr(fname),	"pit_face"	)==0)	||
			(strcmp(_strlwr(fname),	"rank"		)==0)	||
			(strcmp(_strlwr(fname),	"se01"		)==0)	||
//			(strcmp(_strlwr(fname),	"sel_face"	)==0)	||
			(strcmp(_strlwr(fname),	"st00tex"	)==0)	||
			(strcmp(_strlwr(fname),	"st01tex"	)==0)	||
			(strcmp(_strlwr(fname),	"st02tex"	)==0)	||
			(strcmp(_strlwr(fname),	"st03tex"	)==0)	||
			(strcmp(_strlwr(fname),	"st04tex"	)==0)	||
			(strcmp(_strlwr(fname),	"st05tex"	)==0)	||
			(strcmp(_strlwr(fname),	"st06tex"	)==0)	||
			(strcmp(_strlwr(fname),	"st07tex"	)==0)	||
			(strcmp(_strlwr(fname),	"st08tex"	)==0)	||
			(strcmp(_strlwr(fname),	"st09tex"	)==0)		)
				decode_cfj_type02(buff,(char *)fname);
	}

	if(buff!=0)	delete[]	buff;
	CloseHandle(hndl);
}
