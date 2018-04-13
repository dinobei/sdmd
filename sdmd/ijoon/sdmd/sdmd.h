#pragma once

namespace ijoon {
    class sdmd {
    public:
        sdmd(unsigned char *I, unsigned int imageSize);
        ~sdmd();

    public:
        void setN(int n) {N = n;}; // The range value N is small (between 1 and 4), and usually a power of 2 is chosen for optimzation
        void setStride(int s) {stride = s;} // density adjust
        int update(unsigned char *I);

        // for visualization
        unsigned char *getMean();
        unsigned char *getDelta();
        unsigned char *getVariance();
        unsigned char *getDifference();

    private:
        inline int abs(int n);
        inline int crop(int n);
        int sgn(int a);
        void createMean(unsigned char *I0);
        void deleteMean();
        void updateMean(unsigned char *I, unsigned char *M);

        void createDelta();
        void deleteDelta();
        void updateDelta(unsigned char *delta, unsigned char *I, unsigned char *M);

        void createVariance();
        void deleteVariance();
        void updateVariance(unsigned char *V, unsigned char *delta);

        void createDifference();
        void deleteDifference();
        int updateDifference();

    private: // inner variable
        unsigned char *M; // Background
        unsigned char *delta;
        unsigned char *V; // Variance
        unsigned char *D; // Detection

    private: // param
        int N;
        int stride;
        const unsigned int imageSize;
    };
}
