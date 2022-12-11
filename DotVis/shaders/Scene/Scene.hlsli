#ifndef SCENE_H
#define SCENE_H
    
    namespace Scene
    {
        typedef uint2 Tags; //Global tag with a local tag (hashed)
    
        interface iSerialized
        {
            //Loads this class directly from a buffer at an index. Must not fail. Return the size allocated
            uint Load(uint x, inout RWByteAddressBuffer buffer);
            //Inserts this class directly into a buffer at an index. Must not fail. Return the size allocated
            uint Store(uint x, inout RWByteAddressBuffer buffer);
        };

    }

#endif