#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <ijoon/sdmd/sdmd.h>


int main(int argc, char *argv[])
{
    const int imageSize = 1280*720;
    unsigned char *imageData = new unsigned char[imageSize];

    ijoon::sdmd *md = nullptr;

    int cnt=0;
    double sum=0.;

    md = new ijoon::sdmd(imageData, imageSize);
    md->setStride(3000);

    int loopCount = 100;
    while(loopCount--) {

        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        int motionRate = md->update(imageData);
        std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
        std::cout << "time : " << sec.count() << " seconds, motionRate: " << motionRate  << std::endl;
        {
            sum += sec.count();
            double avg = sum/++cnt;
            printf("avg time : %lf\n", avg);
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    delete []imageData;

    return 0;
}
