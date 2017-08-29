#ifndef CAMERA_H
#define CAMERA_H
/*
    well,there are two policies,one is emit buffer when VideoSrc avilable, one is timer emit fetching from VideoSrc per xx msecond.

*/
#include <QTimer>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <QImage>
#include "client.h"
#include "config.h"
#include "yuvrender.h"
using namespace cv;
using namespace std;
class VideoHandler:public QObject{
    Q_OBJECT
public:

    IplImage * frame_ori;
    VideoHandler()
    {

    }
    ~VideoHandler()
    {

    }
    void work(char * url)
    {
        int min_win_width = 64;	// 48, 64, 96, 128, 160, 192, 224
        int max_win_width = 256;

        CascadeClassifier cascade;
        vector<Rect> objs;
        //string cascade_name = "../Hog_Adaboost_Pedestrian_Detect\\hogcascade_pedestrians.xml";
        string cascade_name = "/root/hogcascade_pedestrians.xml";

        if (!cascade.load(cascade_name))
        {
            cout << "can't load cascade!" << endl;
            //return -1;
        }
#if 1

        // while (1)
        {
            //   frame_ori = cvQueryFrame(p_cap);
            //   frame.create(frame_ori->height,frame_ori->width,CV_8U);
            //   memcpy(frame.data,frame_ori->imageData,frame_ori->imageSize);
            Mat frame(frame_ori);
         //   imshow("result", frame);
         //   emit(pic_ok(frame));
            //   imshow("fdsf",frame);


            //  cout << "opened " << endl;
            //*p_cap >> frame;

            //        while(1)
            //            ;
            if (!frame.empty())
            {
                frame_num++;
                if (frame_num % 100 == 0)
                {
                    cout << "Processed " << frame_num << " frames!" << endl;
                }

                //   if (frame_num % 3 == 0)
                if (1)
                {
                    //resize(frame,frame,Size(frame.cols / 2, frame.rows / 2),CV_INTER_LINEAR);
                    //resize(frame,frame,Size(704, 576),CV_INTER_LINEAR);
                    cvtColor(frame, gray_frame, CV_BGR2GRAY);
                    //  gray_frame=frame;
                    //Rect rect;
                    //rect.x = 275;
                    //rect.y = 325;
                    //rect.width = 600;
                    //rect.height = 215;

                    //Mat detect_area = gray_frame(rect);
                    //cascade.detectMultiScale(detect_area,objs,1.1,3);
                    cascade.detectMultiScale(gray_frame, objs, 1.1, 3);


                    vector<Rect>::iterator it = objs.begin();
                    while (it != objs.end() && objs.size() != 0)
                    {
                        pedestrian_num++;
                        pedestrians = frame(*it);

                        Rect rct = *it;
                        if (rct.width >= min_win_width && rct.width < max_win_width)
                        {
                            //   sprintf(file_name, "%d.jpg", pedestrian_num);
                            //  imwrite(file_name, pedestrians);

                            //rct.x += rect.x;
                            //rct.y += rect.y;

                      //    rectangle(frame, rct, Scalar(0, 255, 0), 2);
                        }

                        it++;
                    }

                    //rectangle(frame,rect,Scalar(0,255,0),2);
                    // imshow("result", frame);

                     //   QImage  img = QImage((const uchar*)(frame.data),frame.cols,frame.rows,frame.cols*frame.channels(),QImage::Format_Indexed8);
                    //outputVideo << frame;
                    //   waitKey(1);
                    objs.clear();
                }

            }
            else
            {

                cout << "frame err" << endl;
                //break;
            }
        }
#endif
    }

signals:
    void pic_ok(Mat);
private:
    Mat gray_frame;
    Mat pedestrians;
    int pedestrian_num = 0;
    int frame_num = 0;

};
class VideoSrc: public QObject{
    Q_OBJECT
public:

    VideoSrc()
    {
        //     p_cap= cvCreateFileCapture("rtsp://192.168.1.81:554");  //读取视频
        p_cap= cvCreateFileCapture("/root/repo-github/pedestrian/test.mp4");  //读取视频
    }
    VideoSrc(QString path)
    {
        //     p_cap= cvCreateFileCapture("rtsp://192.168.1.81:554");  //读取视频

        strcpy(url,path.toStdString().data());
        p_cap= cvCreateFileCapture(url);  //读取视频

        //    prt(info,"get %s",url.toStdString().data());
    }
    ~VideoSrc()
    {
        delete p_cap;
    }
    void output_video(VideoHandler &handler)
    {
        //handler.frame_ori= cvQueryFrame(p_cap);
         handler.frame_ori= cvQueryFrame(p_cap);
            int err=0;
         if(handler.frame_ori==NULL){
             prt(info,"get video source fail, source url:%s",url);
            err=1;
             std::this_thread::sleep_for(chrono::milliseconds(100));
         }else{
             //    prt(info,"get video source url:%s",url);
         }
      //  Mat frm=Mat( handler.frame_ori).clone();
         Mat frm;
         frm.resize(0);

         if(!err)
             frm=Mat( handler.frame_ori);

        emit(frame_update(frm));
    }
    VideoHandler &operator>>(VideoHandler &handler)
    {

        int err=0;
        handler.frame_ori= cvQueryFrame(p_cap);
        if(handler.frame_ori==NULL){
            prt(info,"get video source fail, source url:%s",url);
            err=1;
            std::this_thread::sleep_for(chrono::milliseconds(1000));
        }else{
            //    prt(info,"get video source url:%s",url);
        }
         if(!err)
             std::this_thread::sleep_for(chrono::milliseconds(1000));
//            handler.work(url);

        return handler;
    }
signals:
    void frame_update(Mat frame);
private:
    CvCapture *p_cap;
     char url[PATH_LEN];

};


class Camera : public QObject
{
    Q_OBJECT
public:
      YuvRender render;
    explicit Camera(camera_data_t dat,QObject *parent=0) : data(dat),QObject(parent)
    {
        tick=0;
        p_video_src=new VideoSrc(data.ip);
        timer=new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(work()));
        timer->start(100);
        connect(p_video_src,SIGNAL(frame_update(Mat)),&render,SLOT(render_set_mat(Mat)));
    }
    ~Camera(){
        delete timer;
        delete p_video_src;
    }
    void restart(camera_data_t dat)
    {
        data=dat;
    }


signals:

public slots:
    void work()
    {
        p_video_src->output_video(video_handler);
       // *p_video_src>>video_handler;

        //        p_src->set(handler);
        //    handler.work();
      //  tick++;
        // char tmp[100];
        //       QString tmp(p_video_src->get_url());
        //        if(tick==20){
        //        //   strcpy(tmp,p_video_src->url);
        //            prt(info,"restart cam %s, per 20 frame",tmp.toStdString().data());
        //            delete p_video_src;
        //            p_video_src=new VideoSrc(tmp);
        //            tick=0;
        //        }
    }
private:


    camera_data_t data;
    QTimer *timer;
    VideoSrc*p_video_src;
    VideoHandler video_handler;
    int tick;
};


//class Camera : public QObject
//{
//    Q_OBJECT
//public:
//    VideoHandler handler;
//    VideoSrc *p_src;
//    YuvRender render;
//    int tick;
//    explicit Camera(camera_data_t dat,QObject *parent=0) : data(dat),QObject(parent)
//    {
//        tick=0;
//        p_src=new VideoSrc();
//        timer=new QTimer();
//        connect(timer,SIGNAL(timeout()),this,SLOT(work()));
//        timer->start(10);
//        connect(p_src,SIGNAL(frame_update(Mat)),&render,SLOT(set_mat(Mat)));
//    }
//    ~Camera(){
//        delete timer;
//    }

//signals:

//public slots:
//    void work()
//    {
//        tick++;
//        //    prt(info,"working");
//        p_src->set(handler);
//        if(tick==200){
//            tick=0;
//            delete p_src;
//            p_src=new VideoSrc();
//             connect(p_src,SIGNAL(frame_update(Mat)),&render,SLOT(set_mat(Mat)));
//        }
//    //    handler.work();
//    }

//private:
//    camera_data_t data;
//    QTimer *timer;


//};

#include"camera.h"
#include <QGridLayout>
class CameraManager:public QObject{
    Q_OBJECT
public:
    Config *cfg;
    CameraManager(){
       cfg=new Config("/root/repo-github/pedestrian-client/config.json");
      //   cfg=new Config();

//        for(int i=0;i<cfg.data.camera_amount;i++){
//            Camera *c=new Camera(cfg.data.camera[i]);
//            //   Camera c(cfg.data.camera[i]);
//            cams.append(c);
//        }
    }
    ~CameraManager(){
//        for(int i=0;i<cfg.data.camera_amount;i++){


//            delete cams[i];
//        }
    }
    void save_config(QByteArray rst){
        cfg->set_ba(rst);

        cfg->save();
    }
    QByteArray get_config()
    {
        return cfg->get_ba();
    }

    void add_camera(QString ip)
    {
        //         Camera *c=new Camera(cfg.data.camera[i]);

        camera_data_t ca;
        ca.ip=ip;
        ca.port=554;
        cfg->data.camera.append(ca);
        cfg->data.camera_amount++;
        Camera *c=new Camera(cfg->data.camera[cfg->data.camera_amount-1]);
        cams.append(c);
        cfg->save();
       //  if(i==0)
     //    connect(c->p_src,SIGNAL(frame_update(Mat)),&c->render,SLOT(set_mat(Mat)));
     //   if(i==0)
    //    layout->addWidget(&c->render,1,cams.length()-1);
    }
    void del_camera(int index)
    {
        int num=cams.size();
        Camera *c=cams[index-1];
        delete c;
        cams.removeAt(index-1);
        cfg->data.camera.removeAt(index-1);
        cfg->data.camera_amount--;
        cfg->save();
    }
    void change_camera()
    {

    }
    void reconfig_camera(QGridLayout *layout)
    {
        foreach (Camera *c, cams) {
            delete c;
        }
        int num;
        cams.clear();
        for(int i=0;i<cfg->data.camera_amount;i++){
             Camera *c=new Camera(cfg->data.camera[i]);
             cams.append(c);
            //  if(i==0)
          //    connect(c->p_src,SIGNAL(frame_update(Mat)),&c->render,SLOT(set_mat(Mat)));
          //   if(i==0)
             layout->addWidget(&c->render,i,i);
        }
        num=cams.size();
    }
    void config_camera(QGridLayout *layout)
    {

        int num;
        for(int i=0;i<cfg->data.camera_amount;i++){
             Camera *c=new Camera(cfg->data.camera[i]);
             cams.append(c);
            //  if(i==0)
          //    connect(c->p_src,SIGNAL(frame_update(Mat)),&c->render,SLOT(set_mat(Mat)));
          //   if(i==0)
             layout->addWidget(&c->render,i,i);
        }
        num=cams.size();
    }
    QList <Camera *> cams;
private:


  //  Client *client;
};


#endif // CAMERA_H
