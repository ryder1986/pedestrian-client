#ifndef YUVRENDER_H
#define YUVRENDER_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <QImage>
#include "config.h"
using namespace cv;
using namespace std;
#include <QGLWidget>
#include "common.h"
class YuvRender : public QGLWidget
{
    Q_OBJECT
public:

    explicit YuvRender(QWidget *parent = 0);
    void set_buf(char *);







    unsigned char  CONVERT_ADJUST(double tmp)
    {
        return (unsigned char)((tmp >= 0 && tmp <= 255)?tmp:(tmp < 0 ? 0 : 255));
    }
    //YUV420P to RGB24
     void   CONVERT_YUV420PtoRGB24(unsigned char* yuv_src,unsigned char* rgb_dst,int nWidth,int nHeight)
    {
        unsigned char *tmpbuf=(unsigned char *)malloc(nWidth*nHeight*3);
        unsigned char Y,U,V,R,G,B;
        unsigned char* y_planar,*u_planar,*v_planar;
        int rgb_width , u_width;
        rgb_width = nWidth * 3;
        u_width = (nWidth >> 1);
        int ypSize = nWidth * nHeight;
        int upSize = (ypSize>>2);
        int offSet = 0;

        y_planar = yuv_src;
        u_planar = yuv_src + ypSize;
        v_planar = u_planar + upSize;

        for(int i = 0; i < nHeight; i++)
        {
            for(int j = 0; j < nWidth; j ++)
            {
                // Get the Y value from the y planar
                Y = *(y_planar + nWidth * i + j);
                // Get the V value from the u planar
                offSet = (i>>1) * (u_width) + (j>>1);
                V = *(u_planar + offSet);
                // Get the U value from the v planar
                U = *(v_planar + offSet);

                // Cacular the R,G,B values
                // Method 1
                R = CONVERT_ADJUST((Y + (1.4075 * (V - 128))));
                G = CONVERT_ADJUST((Y - (0.3455 * (U - 128) - 0.7169 * (V - 128))));
                B = CONVERT_ADJUST((Y + (1.7790 * (U - 128))));
                /*
                  // The following formulas are from MicroSoft' MSDN
                  int C,D,E;
                  // Method 2
                  C = Y - 16;
                  D = U - 128;
                  E = V - 128;
                  R = CONVERT_ADJUST(( 298 * C + 409 * E + 128) >> 8);
                  G = CONVERT_ADJUST(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  B = CONVERT_ADJUST(( 298 * C + 516 * D + 128) >> 8);
                  R = ((R - 128) * .6 + 128 )>255?255:(R - 128) * .6 + 128;
                  G = ((G - 128) * .6 + 128 )>255?255:(G - 128) * .6 + 128;
                  B = ((B - 128) * .6 + 128 )>255?255:(B - 128) * .6 + 128;
                  */
                offSet = rgb_width * i + j * 3;

                rgb_dst[offSet] = B;
                rgb_dst[offSet + 1] = G;
                rgb_dst[offSet + 2] = R;
            }
        }
        free(tmpbuf);
    }

signals:

public slots:
     void set_mat(Mat f)
     {
         frame=f;
         this->update();
     }

private:
    char yuv_buf[640*480*3/2];
    char rgb_buf[640*480*3];
    int video_width;
    int video_height;
    int pressed_x,pressed_y,pressed;
    int tick;
    Mat frame;
protected:
    void  initializeGL();
    void  resizeGL(int w, int h);
    void  paintEvent(QPaintEvent *);
 };

#endif // YUVRENDER_H
