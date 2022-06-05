#pragma once

#ifndef RAYCOMMON_H
#define RAYCOMMON_H

    //Includes
    #include "Common.hlsli"
    
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
            return channels && (channels & conditions == conditions);
        }

    }
    
    //Ray used for raytracing algorithms
    struct Ray
    {
        //Physical properties
        float3 position;
        float3 direction; //Should be normalized
        
        //Statistics
        uint bounces = 0; //Number of ray bounces/intersections
        float distance = 0; //Distance travelled/accumulated
    };

    //Rules for raytracing
    struct RayPrinciples
    {
        
        
        RayFeatures::ChannelCons inclusionRequirements; //Required channel properties for inclusion in raytracing
        RayFeatures::ChannelCons blockRequirements; //Required channel properties for opaque/query block
    }; 

#endif