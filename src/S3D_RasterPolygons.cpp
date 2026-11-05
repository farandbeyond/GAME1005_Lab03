
void S3D_DrawTriangleWireframes(S3D_Renderer* renderer, Vector3 ndc0, Vector3 ndc1, Vector3 ndc2, Color color0, Color color1 = BLANK, Color color2 = BLANK)
{
	Vector2i screen0 = S3D_NDCToScreen(renderer, ndc0);
	Vector2i screen1 = S3D_NDCToScreen(renderer, ndc1);
	Vector2i screen2 = S3D_NDCToScreen(renderer, ndc2);

	color1 = ColorIsEqual(color1, BLANK) ? color0 : color1;
	color2 = ColorIsEqual(color2, BLANK) ? color0 : color2;

	S3D_DrawLine(renderer, screen0.x, screen0.y, screen1.x, screen1.y, color0, color1);
	S3D_DrawLine(renderer, screen1.x, screen1.y, screen2.x, screen2.y, color1, color2);
	S3D_DrawLine(renderer, screen2.x, screen2.y, screen0.x, screen0.y, color2, color0);
}

void S3D_DrawMeshWireframes(S3D_Renderer* renderer, const S3D_Mesh& mesh, Matrix mvp, Color color)
{
	for (size_t i = 0; i < mesh.indices.size(); i += 3)
	{
		Vector3 p0 = MatrixPerspectiveDivide(mesh.positions[mesh.indices[i + 0]], mvp);
		Vector3 p1 = MatrixPerspectiveDivide(mesh.positions[mesh.indices[i + 1]], mvp);
		Vector3 p2 = MatrixPerspectiveDivide(mesh.positions[mesh.indices[i + 2]], mvp);
		S3D_DrawTriangleWireframes(renderer, p0, p1, p2, color);
	}
}

void S3D_DrawMeshWireframesColor(S3D_Renderer* renderer, const S3D_Mesh& mesh, Matrix mvp, const std::vector<Color>& colors)
{
	for (size_t i = 0; i < mesh.indices.size(); i += 3)
	{
		Vector3 p0 = MatrixPerspectiveDivide(mesh.positions[mesh.indices[i + 0]], mvp);
		Vector3 p1 = MatrixPerspectiveDivide(mesh.positions[mesh.indices[i + 1]], mvp);
		Vector3 p2 = MatrixPerspectiveDivide(mesh.positions[mesh.indices[i + 2]], mvp);
		Color c0 = colors[mesh.indices[i + 0]];
		Color c1 = colors[mesh.indices[i + 1]];
		Color c2 = colors[mesh.indices[i + 2]];
		S3D_DrawTriangleWireframes(renderer, p0, p1, p2, c0, c1, c2);
	}
}
