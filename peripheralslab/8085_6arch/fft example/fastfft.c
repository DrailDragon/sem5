
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/********************************************
** This program determines the Fast Four-  **
** ier Transform (FFT) of a supplied image.**
** The program does this by calling the    **
** routines referenced in the fft.h file.  **
**                                         **
** Author:    Daryle Niedermayer           **
**            184-3-54440                  **
** Date:      Oct 5, 1999                  **
**                                         **
** Credits:   Derived from the template    **
**            supplied by Xue Dong Yang    **
**            Oct 2, 1999                  ****                                         **
** To see the FFT run though its procedure **
** define _DEBUG_                          **
********************************************/
#undef _DEBUG_

/********************************************
** h and w must be defined for the   **
** correct image size.                     **
********************************************/
#define ROWS 256		 
#define COLS 256

/********************************************
** This same procedure can be used to gen  **
** erate either the FFT or DFT algorithms. **
** Define either _FFT_OPT_ or _DFT_OPT_    **
** here.                                   **
** _FFT_OPT_ is the default.               **
********************************************/
#define _FFT_OPT_

#ifdef _DFT_OPT_
#undef _FFT_OPT_
#else
#define _FFT_OPT_
#undef _DFT_OPT_
#endif

/********************************************
** Other files and definitions to include  **
********************************************/
#include "img.h"		/* Assume it is at the current directory */
#include "fft.h"		/* Fast Fourier Transform routines       */
#include "bmp.h"

unsigned char in_buf[ROWS][COLS];	/* Buffer for the input image */
unsigned char out_buf[ROWS][COLS];	/* Buffer for the output Fourier
					   spectrum image */

int main()
{
	
  
  int h,w;
  BMP b;
  int **R,**G,**B;
  BMP *bmp=&b;
  int temp;

  int  i, j;                     /* i and j are loop counters */
  				/* n is the log(N) of the sample size.*/
  
  
  float max, scale_factor;			/* used for scaling the images brightness.          */
  COMPLEX *ft;					/* pointer to the array containing the results of the ft.*/
   
  COMPLEX F_buffer[ROWS];            		/* Buffer of complex numbers */
  									/* to hand off to FT function*/
  int half_width, half_height;
  unsigned char swap_buf[ROWS][COLS]; 					/* Shifted image for output  */

 //     printf("in main \n");
 
//	printf("before read_header h = %d \n",h);
//	printf("before read_header w = %d \n",w);
  
 
  
  Read_BMP_Header("square32.bmp",&h,&w,bmp);

	printf(" H =%d W =%d",h,w);
	R = (int **)malloc(h*sizeof(int));
	G = (int **)malloc(h*sizeof(int));
	B = (int **)malloc(h*sizeof(int));
	for(i=0;i<h;i++){
		R[i]=(int *)malloc(w*sizeof(int));
 		G[i]=(int *)malloc(w*sizeof(int));
		B[i]=(int *)malloc(w*sizeof(int));
		}

   Read_BMP_Data("square32.bmp",&h,&w,bmp,R,G,B);

	printf("converting RGB to grayscale \n");
	
  //RGB -> Grayscale 
	for(i=0;i<h;i++){
	 for(j=0;j<w;j++){
		 	temp=(int) 0.3*R[i][j]+0.1*B[i][j]+0.6*G[i][j];
			R[i][j]=temp;
			G[i][j]=temp;
			B[i][j]=temp;
			in_buf[i][j]=temp;
			//printf("%d %d value of temp---%d\n",i,j,temp);
 			 }
			}
	printf("RGB to gray done, converting real to complex array \n");
		
    /*Convert the real image into complex image first.*/
  for (i=0; i<h; i++)
    for (j=0; j<w; j++) {
      F[i][j].r = (float)in_buf[i][j];  /*The real part = input image */
      F[i][j].i = 0.0;			/* The imaginery part = 0 */
      
      //printf("%d --- %d \n",F[i][j].r,F[i][j].i);
    }
  


  
  /* ========================= PASS 1 ==============================
	Applying the 1D FFT function to each columun of the input
	image, and save the intermediate results into a temparory
	array F1.
     =============================================================== */

  printf("entering pass1 \n");
	  
  for (j=0; j<w; j++) {

    /* Copy a column from array F into the temporary vector TF*/
	for (i=0; i<h; i++) {
	   F_buffer[i].r = F[i][j].r;
	   //printf("\nF_buffer for FFT i/p---%d = %d",i,F_buffer[i].r);
	   F_buffer[i].i = F[i][j].r;
   	   //printf("\nF_buffer for FFT i/p---%d = %d",i,F_buffer[i].i);
    }

	
    /* Call the corresponding function to compute the Fourier transform 
	   depending on whether the _DFT_OPT_ or _FFT_OPT_ flag is set   */
#ifdef _DFT_OPT_
	ft = DFT(F_buffer,h);
#else
	ft = FFT(F_buffer,h);
#endif

    /* Copy the returned result into a temporary array F1 */
	for (i=0; i<h; i++) {
       F1[i][j].r = ft[i].r;
	   F1[i][j].i = ft[i].i;
	}
  }

  /* ========================= PASS 2 ==============================
	Applying the 1D FFT function to each row of the intermediate
	results, and save the result back into array F.
     =============================================================== */

printf("entering pass 2 \n");
  
  for (i=0; i<h; i++) {
    /* Copy a row from array F1 into the temporary vector TF*/

	for (j=0; j<w; j++) {
	   F_buffer[j].r = F1[i][j].r;
	   F_buffer[j].i = F1[i][j].r;
    }

    /* Call the corresponding function to compute the Fourier transform 
	   depending on whether the _DFT_OPT_ or _FFT_OPT_ flag is set   */
#ifdef _DFT_OPT_
	ft = DFT(F_buffer,h);
#else
	ft = FFT(F_buffer,h);
#endif

    /* Copy the returned result back into array F */
	for (j=0; j<w; j++) {
       F[i][j].r = ft[j].r;
	   F[i][j].i = ft[j].i;
	}
  }

  /* Compute the Fourier spectrum |F(u,v)| and save it into the
     output image buffer out_buf.
     Note that proper scaling for the values is needed in order
     to obtain a reasonably bright image.*/
 
  max = 0;
  for (i=0; i<h; i++) {
    for (j=0; j<w; j++) {
      if (complex_mag(F[i][j]) > max) max = complex_mag(F[i][j]);
    }
  }

#ifdef _DEBUG_
  printf ("The min and maximum values are: %f and %f \n",min,max);
#endif

  scale_factor = 255/(log(1 + max));
  for (i=0; i < h; i++) {
    for (j=0; j < w; j++) {
      out_buf[i][j] = (unsigned char) scale_factor*(log(1 + complex_mag(F[i][j])));
    }
  }

  /* Swap sectors of the image to reposition the image to the center of the
     screen.
  */

  half_height = (int)h/2;
  half_width  = (int)w/2;

  for (i=0; i<half_height; i++) {
    for (j=0; j<half_width; j++) {
	  swap_buf[half_height+i][half_width+j] = out_buf[i][j];
	  swap_buf[i][j]             = out_buf[(half_height-1)-i][(half_height-1)-j];
	  swap_buf[i][j+half_width]  = out_buf[(half_height-1)-i][j];
	  swap_buf[half_height+i][j] = out_buf[i][(half_width-1)-j];
    }
  }

  printf("preparing final array \n");
  
  	for(i=0;i<h;i++){
	 for(j=0;j<w;j++){
			R[i][j]=swap_buf[i][j];
			G[i][j]=swap_buf[i][j];
			B[i][j]=swap_buf[i][j];
			 }
			}

  
  write_BMP_Header("fftsq32.bmp",&h,&w,bmp);
  write_BMP_Data("fftsq32.bmp",&h,&w,bmp,R,G,B);
  printf(" successfully completed\n");
  return 0;
  
}



