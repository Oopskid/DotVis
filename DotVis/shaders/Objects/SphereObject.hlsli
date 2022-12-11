#ifndef SPHEREOBJ_H
#define SPHEREOBJ_H

    //Includes
    #include "RayCommon.hlsli"

    class SphereObject : iTraceable
    {
        bool trace(inout Ray ray, inout RayHit hitResult, const RayPrinciples rules)
        {
            return true;
        }
    };

#endif