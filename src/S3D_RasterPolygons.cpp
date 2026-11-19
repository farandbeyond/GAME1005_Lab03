
void S3D_DrawTriangleWireframes(S3D_Renderer* renderer, Vector3 ndc0, Vector3 ndc1, Vector3 ndc2, Color color0, Color color1 = BLANK, Color color2 = BLANK)
{
	Vector2i v0 = S3D_NDCToScreen(renderer, ndc0);
	Vector2i v1 = S3D_NDCToScreen(renderer, ndc1);
	Vector2i v2 = S3D_NDCToScreen(renderer, ndc2);

	S3D_DrawLine(renderer, v0.x, v0.y, v1.x, v1.y, color0);
	S3D_DrawLine(renderer, v1.x, v1.y, v2.x, v2.y, color0);
	S3D_DrawLine(renderer, v2.x, v2.y, v0.x, v0.y, color0);
}

void S3D_DrawMeshWireframes(S3D_Renderer* renderer, const S3D_Mesh& mesh, Matrix mvp, Color color)
{
	//ShaderToy apply matrix to vertex
	//
	//vec3 transform(mat4 m, vec3 p)
	//{
	//	return (inverse(m) * vec4(p, 1.0)).xyz;
	//}

	//render every triangle based on given indicies
	for (size_t i = 0; i < mesh.indices.size(); i += 3)
	{
		//turn indicies into vector indexes
		uint16_t index0 = mesh.indices[i + 0];
		uint16_t index1 = mesh.indices[i + 1];
		uint16_t index2 = mesh.indices[i + 2];
		
		//get the positions
		Vector3 ndc0 = mesh.positions[index0];
		Vector3 ndc1 = mesh.positions[index1];
		Vector3 ndc2 = mesh.positions[index2];

		//draw the triangle
		S3D_DrawTriangleWireframes(renderer, ndc0, ndc1, ndc2, RED);
	}
}

void S3D_DrawMeshWireframesColor(S3D_Renderer* renderer, const S3D_Mesh& mesh, Matrix mvp, const std::vector<Color>& colors)
{
	
}

void S3D_DrawMesh(S3D_Renderer* renderer, const S3D_Mesh& mesh, S3D_UniformData uniform, S3D_FragmentShader shader)
{	
	
}
