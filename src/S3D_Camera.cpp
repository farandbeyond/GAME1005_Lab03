
inline Matrix S3D_CameraRotationMatrix(S3D_Camera camera)
{
	Matrix rotation = QuaternionToMatrix(QuaternionFromEuler(camera.pitch * DEG2RAD, camera.yaw * DEG2RAD, 0.0f));
	return rotation;
}

inline Matrix S3D_CameraViewMatrix(S3D_Camera camera)
{
	Matrix mat_cam = S3D_CameraRotationMatrix(camera) * MatrixTranslate(camera.position.x, camera.position.y, camera.position.z);
	Matrix mat_view = MatrixInvert(mat_cam);
	return mat_view;
}

inline Matrix S3D_CameraProjMatrix(S3D_Camera camera)
{
	Matrix mat_proj = MatrixIdentity();
	switch (camera.proj)
	{
	case CAMERA_ORTHOGRAPHIC:
		mat_proj = MatrixOrtho(camera.ortho.left, camera.ortho.right, camera.ortho.bottom, camera.ortho.top, camera.near, camera.far);
		break;

	case CAMERA_PERSPECTIVE:
		mat_proj = MatrixPerspective(camera.persp.fov * DEG2RAD, camera.persp.aspect, camera.near, camera.far);
		break;
	}
	return mat_proj;
}

void S3D_CameraLookAt(S3D_Camera* camera, Vector3 eye, Vector3 target, Vector3 up)
{
	Matrix mat_camera = MatrixInvert(MatrixLookAt(eye, target, up));
	Vector3 degrees = QuaternionToEuler(QuaternionFromMatrix(mat_camera)) * RAD2DEG;
	camera->pitch = degrees.x;
	camera->yaw = degrees.y;
	camera->position = { mat_camera.m12, mat_camera.m13, mat_camera.m14 };
}

void S3D_CameraPerspective(S3D_Camera* camera, double fov_degrees, double aspect, double near, double far)
{
	camera->near = near;
	camera->far = far;
	camera->persp.fov = fov_degrees;
	camera->persp.aspect = aspect;
}

void S3D_CameraOrtho(S3D_Camera* camera, double left, double right, double bottom, double top, double near, double far)
{
	camera->near = near;
	camera->far = far;
	camera->ortho.left = left;
	camera->ortho.right = right;
	camera->ortho.bottom = bottom;
	camera->ortho.top = top;
}

void S3D_CameraUpdate(S3D_Camera* camera, float speed_linear, float speed_angular)
{
	static bool camera_enabled_prev = false;
	static bool camera_enabled_curr = true;

	Vector2 mouse_delta = GetMouseDelta();
	camera_enabled_curr = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
	if (camera_enabled_curr != camera_enabled_prev)
	{
		mouse_delta = Vector2Zeros;
		if (camera_enabled_curr)
			DisableCursor();
		else
			EnableCursor();
	}
	camera_enabled_prev = camera_enabled_curr;

	if (camera_enabled_curr)
	{
		float dt = GetFrameTime();
		camera->yaw += mouse_delta.x * speed_angular * dt;
		camera->pitch += mouse_delta.y * speed_angular * dt;
		
		Matrix rotation = S3D_CameraRotationMatrix(*camera);
		Vector3 local_x = { rotation.m0, rotation.m1, rotation.m2 };
		Vector3 local_y = { rotation.m4, rotation.m5, rotation.m6 };
		Vector3 local_z = { rotation.m8, rotation.m9, rotation.m10 };

		if (IsKeyDown(KEY_W)) camera->position -= local_z * speed_linear * dt;
		if (IsKeyDown(KEY_S)) camera->position += local_z * speed_linear * dt;
		if (IsKeyDown(KEY_A)) camera->position -= local_x * speed_linear * dt;
		if (IsKeyDown(KEY_D)) camera->position += local_x * speed_linear * dt;
		if (IsKeyDown(KEY_LEFT_SHIFT)) camera->position -= local_y * speed_linear * dt;
		if (IsKeyDown(KEY_SPACE)) camera->position += local_y * speed_linear * dt;
	}
}
