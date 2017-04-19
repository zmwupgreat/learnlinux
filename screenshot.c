#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stddef.h>
#include<linux/fb.h>
#include<sys/mman.h>
#include<sys/ioctl.h>
typedef unsigned short WORD;  
typedef unsigned int DWORD;  
typedef unsigned long LONG;  
typedef unsigned char uint8_t;
#pragma pack(push,1)
typedef struct tagBITMAPFILEHEADER  
  {  
      WORD bfType;    
      DWORD bfSize;   
      WORD bfReserved1;   
      WORD bfReserved2;  
      DWORD bfOffBits; 
  } BITMAPFILEHEADER;  
	#pragma pack(pop)
#pragma pack(push,1)				    
typedef struct tagBITMAPINFOHEADER  
  {  
	  DWORD biSize;      
	  DWORD biWidth;     
	  DWORD biHeight;     
	  WORD biPlanes;     
	  WORD biBitCount;    
	  DWORD biCompression;   
	  DWORD biSizeImage;    
	  DWORD biXPelsPerMeter;   
	  DWORD biYPelsPerMeter;   
	  DWORD biClrUsed;   
	  DWORD biClrImportant;  
  }BITMAPINFOHEADER;
#pragma pack(pop)
int main (int argc, char *argv[])
{
	char *filename;
	
	int fo;
	unsigned long screensize;
	struct fb_var_screeninfo vinfo;//可变参数描述符
	struct fb_fix_screeninfo finfo;//固定参数描述符
	
	if(argc!=2)
	{ 
		printf("please enter the .bmp filename");
		exit(1);
	}
	else 
	{
		filename=argv[1];
	}
	printf("ScreenShot! kaca\n");
	fo=open("/dev/fb0",O_RDWR);//打开framebuffer文件
	if(fo<0)
	{
	printf("Framebuffer打开失败！\n");
	exit(1);
	}
	ioctl(fo,FBIOGET_FSCREENINFO,&finfo);//读取屏幕参数
	ioctl(fo,FBIOGET_VSCREENINFO,&vinfo);
	screensize=finfo.line_length*vinfo.yres_virtual;//计算屏幕大小
	uint8_t *buf=mmap(0,screensize,PROT_READ|PROT_WRITE,MAP_SHARED,fo,0);//将framebuffer文件映射到内存区
BITMAPFILEHEADER fileheader;
BITMAPINFOHEADER infoheader;
	fileheader.bfType=0x4d42;//BM
	fileheader.bfSize=/*54+vinfo.xres_virtual*vinfo.yres_virtual*vinfo.bits_per_pixel/8;*/sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+vinfo.xres_virtual*vinfo.yres_virtual*3;//字节大小
	fileheader.bfReserved1=0;
	fileheader.bfReserved2=0;
	fileheader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
printf("%ld",sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER));

	infoheader.biSize=sizeof(BITMAPINFOHEADER);//sizeof(BITMAPINFOHEADER);
	infoheader.biWidth=vinfo.xres;
	infoheader.biHeight=vinfo.yres;
 printf("xres %d, yres %d\n,biWidth %d,biHeight %d\n",vinfo.xres, vinfo.yres,infoheader.biWidth,infoheader.biHeight);
	infoheader.biPlanes=1;
	infoheader.biBitCount=vinfo.bits_per_pixel;
	infoheader.biCompression=0;
	infoheader.biSizeImage=vinfo.xres_virtual*vinfo.yres_virtual*vinfo.bits_per_pixel/8;
	infoheader.biXPelsPerMeter=0;
	infoheader.biYPelsPerMeter=0;
	infoheader.biClrUsed=0;
	infoheader.biClrImportant=0;
   int bmpfile;
   bmpfile=open(filename,O_RDWR|O_CREAT);
	if(bmpfile<0)
	{
		printf("%s打开失败\n！",filename);
		exit(1);
	}
	write(bmpfile,&fileheader,sizeof(BITMAPFILEHEADER));
	write(bmpfile,&infoheader,sizeof(BITMAPINFOHEADER));
	 int x, y;  
	 for(y = vinfo.yres - 1; y >= 0; y--)  
{  
		for(x = 0; x < vinfo.xres; x++)  
		{ 
		int location = (x + vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y + vinfo.yoffset) * finfo.line_length;             
	    write(bmpfile, buf + location, vinfo.bits_per_pixel/8);  
		}  
}  
	    munmap(buf, screensize);  
	    close(bmpfile);  
	    close(fo);     
	    return 0;  
}
