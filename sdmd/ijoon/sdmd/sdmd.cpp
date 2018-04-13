#include "sdmd.h"
#include <string.h>

ijoon::sdmd::sdmd(unsigned char *I, unsigned int imageSize)
 : M(nullptr), delta(nullptr), V(nullptr), D(nullptr),
    N(4), stride(1), imageSize(imageSize) {
    createMean(I);
    createDelta();
    createDifference();
    createVariance();
}

ijoon::sdmd::~sdmd() {
    deleteMean();
    deleteDelta();
    deleteVariance();
    deleteDifference();
}

inline int ijoon::sdmd::abs(int n) {
    return (n>=0) ? (n) : (-n);
}

inline int ijoon::sdmd::crop(int n) {
    return (n<0x00) ? 0x00 : (((n)>0xFF)? 0xFF : (n));
}

int ijoon::sdmd::sgn(int a) {
    if(a > 0) return 1;
    else if(a < 0) return -1;
    else return 0;
}

void ijoon::sdmd::createMean(unsigned char *I0) {
    M = new unsigned char[imageSize];
    memcpy(M, I0, imageSize);
}

void ijoon::sdmd::deleteMean() {
    if(M != nullptr) {
        delete[] M;
    }
}

void ijoon::sdmd::createDelta() {
    delta = new unsigned char[imageSize];
}

void ijoon::sdmd::deleteDelta() {
    if(delta != nullptr) {
        delete []delta;
    }
}

void ijoon::sdmd::createVariance() {
    V = new unsigned char[imageSize];
    //memcpy(V, delta0, imageSize); // 초기일때는 delta가 어차피 0임
}

void ijoon::sdmd::deleteVariance() {
    if(V != nullptr) {
        delete []V;
    }
}

void ijoon::sdmd::createDifference() {
    D = new unsigned char[imageSize];
}

void ijoon::sdmd::deleteDifference() {
    if(D != nullptr) {
        delete []D;
    }
}

int ijoon::sdmd::update(unsigned char *I) {
    int motion_pixel = 0;
    for(int x = 0 ; x < imageSize ; x+=stride) {
        const int deviation = I[x]-M[x];
        M[x] = crop(M[x] + sgn(deviation));
        delta[x] = abs((deviation));

        if(delta[x] != 0x00) {
            V[x] = crop(V[x] + sgn(N*delta[x] - V[x]));
        }

        if(delta[x] < V[x]) {
            D[x] = 0xff;
        }
        else {
            D[x] = 0x00;
            motion_pixel++;
        }
    }

    return (int)((float)motion_pixel/(imageSize/stride) * 100.f);
}

unsigned char *ijoon::sdmd::getMean() {
    return M;
}

unsigned char *ijoon::sdmd::getDelta() {
    return delta;
}

unsigned char *ijoon::sdmd::getVariance() {
    return V;
}

unsigned char *ijoon::sdmd::getDifference() {
    return D;
}
