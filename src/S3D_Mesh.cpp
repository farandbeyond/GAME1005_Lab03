
static void S3D_LoadMeshPar(S3D_Mesh* mesh, par_shapes_mesh* par)
{
	mesh->indices.resize((size_t)par->ntriangles * 3);
	mesh->positions.resize((size_t)par->npoints);
	mesh->normals.resize((size_t)par->npoints);
	mesh->tcoords.resize((size_t)par->npoints);

	memcpy(mesh->indices.data(), par->triangles, sizeof(uint16_t) * par->ntriangles * 3);
	memcpy(mesh->positions.data(), par->points, sizeof(Vector3) * par->npoints);
	memcpy(mesh->normals.data(), par->normals, sizeof(Vector3) * par->npoints);
	memcpy(mesh->tcoords.data(), par->tcoords, sizeof(Vector2) * par->npoints);
}

void S3D_LoadMeshPlane(S3D_Mesh* mesh)
{
	par_shapes_mesh* par = par_shapes_create_plane(1, 1);
	par_shapes_translate(par, -0.5f, -0.5f, 0.0f);
	S3D_LoadMeshPar(mesh, par);
	par_shapes_free_mesh(par);
}

void S3D_LoadMeshSphere(S3D_Mesh* mesh)
{
	par_shapes_mesh* par = par_shapes_create_parametric_sphere(8, 8);
	S3D_LoadMeshPar(mesh, par);
	par_shapes_free_mesh(par);
}

void S3D_LoadMeshObj(S3D_Mesh* mesh, const char* path)
{
	fastObjMesh* obj = fast_obj_read(path);

	size_t vertex_count = (size_t)obj->index_count;
	Vector3* positions = (Vector3*)obj->positions;
	Vector3* normals = (Vector3*)obj->normals;
	Vector2* tcoords = (Vector2*)obj->texcoords;

	mesh->positions.resize(vertex_count);
	mesh->normals.resize(vertex_count);
	mesh->tcoords.resize(vertex_count);
	mesh->indices.resize(vertex_count);
	for (size_t i = 0; i < vertex_count; i++)
	{
		fastObjIndex index = obj->indices[i];
		mesh->positions[i] = positions[index.p];
		mesh->normals[i] = normals[index.n];
		mesh->tcoords[i] = tcoords[index.t];
		mesh->indices[i] = i;
	}

	fast_obj_destroy(obj);
}

void S3D_UnloadMesh(S3D_Mesh* mesh)
{
	mesh->indices.clear();
	mesh->positions.clear();
	mesh->normals.clear();
	mesh->tcoords.clear();
}
