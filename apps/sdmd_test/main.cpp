#include <stdio.h>
#include <ijoon/sdmd/sdmd.h>
#include <ijoon/coreutils.h>
#include <opencv/highgui.h>

int main(int argc, char *argv[])
{
    IplImage *frame, *gray=nullptr;
    CvCapture* capture = cvCaptureFromCAM(0);
    cvNamedWindow("Input",1);

    ijoon::sdmd *md = nullptr;

    int cnt=0;
    double sum=0.;
    while(capture) {
        frame = cvQueryFrame(capture);

        if(gray == nullptr) {
            gray = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U, 1);
        }

        cvCvtColor(frame, gray, CV_RGB2GRAY);

        if(md == nullptr) {
            md = new ijoon::sdmd((unsigned char *)gray->imageData, gray->imageSize);
            md->setStride(3000);
        }
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        int motionRate = md->update((unsigned char *)gray->imageData);
        std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
        std::cout << "time : " << sec.count() << " seconds, motionRate: " << motionRate  << std::endl;
        {
            sum += sec.count();
            double avg = sum/++cnt;
            printf("avg time : %lf\n", avg);
        }


        if(cvWaitKey(33) >= 27)
            break;

        if(1 < motionRate) {
            cvRectangleR(frame, cvRect(100, 100, 500, 500), CV_RGB(255, 0, 0), 10);
        }

        cvShowImage("Input", frame);

        memcpy(gray->imageData, md->getMean(), gray->imageSize);
        cvShowImage("Mean", gray);

        memcpy(gray->imageData, md->getDelta(), gray->imageSize);
        cvShowImage("Delta", gray);

        memcpy(gray->imageData, md->getVariance(), gray->imageSize);
        cvShowImage("Variance", gray);

        memcpy(gray->imageData, md->getDifference(), gray->imageSize);
        cvShowImage("Difference", gray);
    }

    cvReleaseCapture(&capture);
    cvDestroyWindow("Input");

    return 0;
}
