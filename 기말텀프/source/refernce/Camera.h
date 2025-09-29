#pragma once

constexpr GLdouble Frustum_fovy		{ 60.0 };
constexpr GLdouble Frustum_zNear	{ 1.0 };
constexpr GLdouble Frustum_zFar		{ 10000.0 };

class Camera
{
public:
	enum class ProjMode : unsigned char { Orthographic, Perspective };

public:
	Camera();
	~Camera();

	void RegenerateOrthographic(int w, int h);
	void RegeneratePerspective(int w, int h);
	void RegenerateProjection(int w, int h);

	void Rotate(GLfloat pitch, GLfloat yaw, GLfloat roll);

	void LookAt(const GLvector& look_at);

	void ProcKeyInput(unsigned char key, int x, int y);

	void SetProjMode(const ProjMode& mode) { mProjMode = mode; }
	void SetPos(const GLvector& pos) { mPos = pos; }

	const ProjMode& GetProjMode()	const	{ return mProjMode; }
	const GLvector& GetPos()		const	{ return mPos; }
	const GLvector& GetLook()		const	{ return mLook; }
	const GLvector& GetUp()			const	{ return mUp; }
	const GLvector& GetRight()		const	{ return mRight; }

private:
	ProjMode					mProjMode;

	GLvector					mPos;
	GLvector					mLook;
	GLvector					mUp;
	GLvector					mRight;

	GLfloat						mPitch;
	GLfloat						mYaw;
	GLfloat						mRoll;
};