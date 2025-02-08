#pragma once

class AabbCollision
{
public:
    bool checkAABBCollision(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh)
    {
        return (Ax < Bx + Bw) &&
            (Ax + Aw > Bx) &&
            (Ay < By + Bh) &&
            (Ay + Ah > By);
    }
};