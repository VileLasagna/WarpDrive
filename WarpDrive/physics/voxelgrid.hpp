#ifndef WD_VOXEL_GRID_HPP_DEFINED
#define WD_VOXEL_GRID_HPP_DEFINED

#include "WarpDrive/basemaths/vec3.hpp"
#include "WarpDrive/physics/collisionsystem.hpp"

class VoxelGrid: public CollisionSystem
{

public:

    VoxelGrid();
    VoxelGrid(float Cellsize, int WorldSize);

};

#endif //WD_VOXEL_GRID_HPP_DEFINED
