#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <raygui.h>

#include <external/par_shapes.h>
#include <external/fast_obj.h>

#include <vector>
#include <cassert>

struct Vector2i
{
	int x;
	int y;
};

struct S3D_Rectangle
{
	Vector2i min;
	Vector2i max;
};

struct S3D_Renderer
{
	int width;
	int height;
	Image color_buffer;
	//Image depth_buffer;
};

struct S3D_Mesh
{
	std::vector<Vector3> positions;
	std::vector<Vector3> normals;
	std::vector<Vector2> tcoords;
	std::vector<uint16_t> indices;
};

struct S3D_Camera
{
	Vector3 position;
	float yaw;
	float pitch;

	CameraProjection proj;
	union
	{
		struct
		{
			double left, right, bottom, top;
		} ortho;
		struct
		{
			double fov, aspect;
		} persp;
	};
	double near, far;
};

#include "S3D_Math.cpp"
#include "S3D_Mesh.cpp"
#include "S3D_Camera.cpp"
#include "S3D_Raster.cpp"
#include "S3D_RasterLines.cpp"
#include "S3D_RasterShapes.cpp"
#include "S3D_RasterPolygons.cpp"

#include "S3D_Demos.cpp"
