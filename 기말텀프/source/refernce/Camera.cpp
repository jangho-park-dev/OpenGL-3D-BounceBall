#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
	: mProjMode { ProjMode::Orthographic }
	, mPos		{ 0.0f, 100.0f, 1000.0f }
	, mLook		{ 0.0f, 0.0f, -1.0f }
	, mUp		{ 0.0f, 1.0f, 0.0f }
	, mRight	{ 1.0f, 0.0f, 0.0f }
	, mPitch	{ 0.0f }
	, mYaw		{ 0.0f }
	, mRoll		{ 0.0f }
{
}
Camera::~Camera()
{
}

void Camera::RegenerateOrthographic(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(
		  -static_cast<GLdouble>(w / 2)
		, static_cast<GLdouble>(w / 2)
		, -static_cast<GLdouble>(h / 2)
		, static_cast<GLdouble>(h / 2)
		, Frustum_zNear
		, Frustum_zFar);

	GLvector vLook{ mPos + mLook };
	gluLookAt(
		mPos.x, mPos.y, mPos.z,
		vLook.x, vLook.y, vLook.z,
		mUp.x, mUp.y, mUp.z
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::RegeneratePerspective(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(
		  Frustum_fovy
		, static_cast<GLdouble>(w) / static_cast<GLdouble>(h)
		, Frustum_zNear
		, Frustum_zFar);

	GLvector vLook{ mPos + mLook };
	gluLookAt(
		mPos.x, mPos.y, mPos.z,
		vLook.x, vLook.y, vLook.z,
		mUp.x, mUp.y, mUp.z
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::RegenerateProjection(int w, int h)
{
	switch (mProjMode) {
	case ProjMode::Orthographic:
		RegenerateOrthographic(w, h);
		break;
	case ProjMode::Perspective:
		RegeneratePerspective(w, h);
		break;
	}
}

void Camera::Rotate(GLfloat pitch, GLfloat yaw, GLfloat roll)
{
	if (mPitch + pitch < -80.0f) {
		pitch = -80.0f - mPitch;
	}
	else if (mPitch + pitch > 80.0f) {
		pitch = 80.0f - mPitch;
	}
	mPitch += pitch;
	mYaw += yaw;
	mRoll += roll;
	if (mYaw > 360.0f) mYaw -= 360.0f;
	if (mYaw < 0.0f) mYaw += 360.0f;
	auto mtx{ GLmatrix::Rotate(mLook, roll) * GLmatrix::Rotate(mUp, yaw) * GLmatrix::Rotate(mRight, mPitch) };
	mUp = GLvector{ 0.0f, 1.0f, 0.0f };
	mLook.y = 0.0f;
	mLook = normalize(mtx * normalize(mLook));
	mRight = normalize(cross(mLook, mUp));
	mUp = normalize(cross(mRight, mLook));
}

void Camera::LookAt(const GLvector & look_at)
{
	mUp = GLvector{ 0.0f, 1.0f, 0.0f };
	mLook = normalize(look_at - mPos);
	mRight = cross(mUp, mLook);
	mUp = cross(mLook, mRight);
}

void Camera::ProcKeyInput(unsigned char key, int x, int y)
{
	static constexpr GLfloat speed{ 15.0f };
	switch (key)
	{
	case 'w':
		mPos += mLook * speed;
		break;
	case 's':
		mPos += -mLook * speed;
		break;
	case 'a':
		mPos += -mRight * speed;
		break;
	case 'd':
		mPos += mRight * speed;
		break;
	case VK_SPACE:
		mPos += mUp * speed;
		break;
	case 'f':
		mPos += -mUp * speed;
		break;
	case '2':
	case '3':
	case '4':
	case 'r':
		mPitch = 0.0f;
		mYaw = 0.0f;
		mRoll = 0.0f;
		break;
	}
}
