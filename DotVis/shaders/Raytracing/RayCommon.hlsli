#ifndef RAYCOMMON_H
#define RAYCOMMON_H

    //Includes
    #include "../Common.hlsli"
    #include "../Scene/Scene.hlsli"
    
    //Common defines and functionality for raytracing
    namespace RayFeatures
    {
        typedef uint ChannelCons; //Complex channel conditions. b0&b1 = included channels (any), b2&b3 = required channels (all)
        static uint channelCount = 16; //Number of ray channels supported
        static uint channelMask = 0xFFFF; //Bit mask for ray channels
        
        bool isChannelConsMet(uint channels, ChannelCons conditions)
        {
            //Reduce channels to only the included
            channels &= (conditions & channelMask);
            
            //Next condition part
            conditions >>= channelCount;
        
            //Must have any of the included channels plus match all required channels
            return channels && ((channels & conditions) == conditions);
        }

    }
    
    //Ray used for raytracing algorithms
    struct Ray
    {
        //Physical properties
        float3 position;
        float3 direction; //Should be normalized
        float4 colour; //LDR during backwards, HDR on source found
    
        //Statistics
        uint bounces; //Number of ray bounces/intersections
        float distance; //Distance travelled/accumulated
    };

    struct RayHit
    {
        float4 baseColour;
        float3 position;
        float3 normal;
        float2 uv;
        uint channels;
    
        Scene::Tags tag; //ID/discriminator
        float3 velocity;
    };

    //Rules for raytracing
    struct RayPrinciples
    {
        /*Algorithm flags. 
            b0 = ignore marching, b1 = prefer tracing, 
            b2-b9 = hit mask flags. For avoiding complex computation of discarded data
            b10 = use reflections
        */
        uint strategy;
        
        float maxDistance;
        uint maxBounces;
        RayFeatures::ChannelCons inclusionRequirements; //Required channel properties for inclusion in raytracing
        RayFeatures::ChannelCons blockRequirements; //Required channel properties for opaque/query block
    };

    interface iTraceable
    {
        bool trace(inout Ray ray, inout RayHit hitResult, const RayPrinciples rules);
    };

#endif