//BMP read write 


typedef struct BMP{ 
  
  unsigned short bType;           /* Magic number for file */
  unsigned int   bSize;           /* Size of file */
  unsigned short bReserved1;      /* Reserved */
  unsigned short bReserved2;      /* ... */
  unsigned int   bOffBits;        /* Offset to bitmap data */

  unsigned int  bISize;           /* Size of info header */
  unsigned int  bWidth;          /* Width of image */
  unsigned int   bHeight;         /* Height of image */
  unsigned short bPlanes;         /* Number of color planes */
  unsigned short bBitCount;       /* Number of bits per pixel */
  unsigned int  bCompression;    /* Type of compression to use */
  unsigned int  bSizeImage;      /* Size of image data */
  int           bXPelsPerMeter;  /* X pixels per meter */
  int      	    bYPelsPerMeter;  /* Y pixels per meter */
  unsigned int   bClrUsed;        /* Number of colors used */
  unsigned int   bClrImportant;   /* Number of important colors */
}BMP;

 
int Read_BMP_Header(char *filename,int *h,int *w,BMP *bmp) 
{

   FILE *f;
   int *p;
    printf("\nReading BMP Header ");
      f=fopen(filename,"r");
     // printf("\nReading BMP Header ");
	  fread(&bmp->bType,sizeof(unsigned short),1,f);
      p=(int *)bmp;
	  fread(p+1,sizeof(BMP)-4,1,f);
      if (bmp->bType != 19778) {
      printf("Error, not a BMP file!\n");
      return 0;
      } 
     
      *w = bmp->bWidth;
      *h = bmp->bHeight;
  return 1;
}

void Read_BMP_Data(char *filename,int *h,int *w,BMP *bmp, int **R ,int **G,int **B)
{
		
      int i,j,i1,H,W,Wp,PAD;
	  unsigned char *RGB;
      FILE *f;
	  printf("\nReading BMP Data ");
      f=fopen(filename,"r");

      fseek(f, 0, SEEK_SET);
      fseek(f, bmp->bOffBits, SEEK_SET);
      
      W = bmp->bWidth;
      
      H = bmp->bHeight;
           
      printf("\nheight = %d width= %d ",H,W);
      //printf("w and h read\n");
      
      
      PAD = (3 * W) % 4 ? 4 - (3 * W) % 4 : 0;
      Wp = 3 * W + PAD;
      RGB = (unsigned char *)malloc(Wp* H * sizeof(unsigned char));
      fread(RGB, sizeof(unsigned char), Wp * H, f);
            
		i1=0;
      for (i = 0; i < H; i++) {
	   for (j = 0; j < W; j++){
		i1=i*(Wp)+j*3;
		B[i][j]=RGB[i1];
		G[i][j]=RGB[i1+1];
		R[i][j]=RGB[i1+2];
		//printf("B --- %d \n",B[i][j]);
		}
	}
	 fclose(f);
	 printf("read_BMP_data file closed \n");
  free(RGB);
}


int write_BMP_Header(char *filename,int *h,int *w,BMP *bmp) 
{
  
   
   FILE *f;
   int *p;
      f=fopen(filename,"w");
      printf("\n Writing BMP Header ");
      fwrite(&bmp->bType,sizeof(unsigned short),1,f);
      p=(int *)bmp;
      fwrite(p+1,sizeof(BMP)-4,1,f);
      return 1;
}

void write_BMP_Data(char *filename,int *h,int *w,BMP *bmp, int **R ,int **G,int **B){
		
      int i,j,i1,H,W,Wp,PAD;
      unsigned char *RGB;
      FILE *f;
	  printf("\nWriting BMP Data\n");
      f=fopen(filename,"w");
      printf("file opened\n");
      
      fseek(f, 0, SEEK_SET);
      fseek(f, bmp->bOffBits, SEEK_SET);
      
      printf("reading W and H\n");
      W = bmp->bWidth;
      H = bmp->bHeight;
     printf("\nheight = %d width= %d ",H,W);
      PAD = (3 * W) % 4 ? 4 - (3 * W) % 4 : 0;
      Wp = 3 * W + PAD;
      RGB = (unsigned char *)malloc(Wp* H * sizeof(unsigned char));
      fread(RGB, sizeof(unsigned char), Wp * H, f);
           
      printf("preparing RGB array \n");
	   
     i1=0;
     for (i = 0; i < H; i++) {
	   for (j = 0; j < W; j++){
		i1=i*(Wp)+j*3;
		RGB[i1]=B[i][j];
		RGB[i1+1]=G[i][j];
		RGB[i1+2]=R[i][j];
		}
	}
	fwrite(RGB, sizeof(unsigned char), Wp * H, f);
	fclose(f);
  free(RGB);
}



