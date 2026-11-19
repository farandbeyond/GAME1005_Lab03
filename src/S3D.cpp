#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <raygui.h>

#include <external/par_shapes.h>
#include <external/fast_obj.h>

#include <array>
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
	Image depth_buffer;
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

struct S3D_UniformData
{
	Matrix world;
	Matrix normal;
	Matrix mvp;

	Image image;
};

struct S3D_Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 tcoord;

	Vector3 ndc;
	Vector2i screen;
};

struct S3D_Fragment
{
	Vector3 p;  // Position (world)        
	Vector3 n;  // Normal   (world)
	Vector2 t;  // Tcoord   (local)
	Vector3 bc; // Barycentric
	float depth;
};

using S3D_FragmentShader = Vector3(*)(S3D_Fragment fragment, const S3D_UniformData& uniform);

#include "S3D_Math.cpp"
#include "S3D_Mesh.cpp"
#include "S3D_Camera.cpp"
#include "S3D_Raster.cpp"
#include "S3D_RasterLines.cpp"
#include "S3D_RasterShapes.cpp"
#include "S3D_RasterPolygons.cpp"

#include "S3D_Demos.cpp"
