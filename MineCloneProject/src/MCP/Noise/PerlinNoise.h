#pragma once

namespace MC
{
    class PerlinNoise
    {
    public:
        PerlinNoise();
        ~PerlinNoise();

        double Gen(double x, double y, double z);

    private:
        double fade(double t);
        double grad(int hash, double x, double y, double z);
        int inc(int num);
        
    private:
        //Random numbers 0-256
        int* randomNumbers;
        int repeat;
    };

    
}
