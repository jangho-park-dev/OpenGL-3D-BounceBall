#include "stdafx.h"
#include "ProjectLibrary.h"

namespace TestNameSpace
{


	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
	{
		FILE *fp;
		GLubyte *bits;

		int bitsize;
		int infosize;
		BITMAPFILEHEADER header;
		if (fopen_s(&fp, filename, "rb") != NULL)
		{   // 비트맵 파일을 바이너리 모드로 연다. (return_value == NULL) 일 경우 파일열기 성공.
			return NULL;
		}

		if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)   // 비트맵의 헤더 정보를 읽는다.
		{
			fclose(fp);
			return NULL;
		}

		if (header.bfType != 'MB')      // 만일 비트맵이 아니라면 실행을 중지한다.
		{
			fclose(fp);
			return NULL;
		}

		infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);      // BITMAPINFO의 위치를 계산한다.

		if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
		{
			fclose(fp);
			return NULL;
		}

		if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)      // BITMAPINFO를 읽는다.
		{
			free(*info);
			fclose(fp);
			return NULL;
		}

		if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)      // 비트맵 이미지의 크기를 계산한다.
		{
			bitsize = ((*info)->bmiHeader.biWidth *
				(*info)->bmiHeader.biBitCount + 7) / 8 *
				abs((*info)->bmiHeader.biHeight);
		}

		if ((bits = (unsigned char*)malloc(bitsize)) == NULL)      // 비트맵 데이터를 읽고 파일을 닫는다.
		{
			free(*info);
			fclose(fp);
			return NULL;
		}

		if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize)
		{
			free(*info);
			free(bits);
			fclose(fp);
			return NULL;
		}

		fclose(fp);
		return bits;
	}































	void SpringLine::AddPoints(GLVector3 point)
	{




	}


	void SpringLine::Initialize(double size, int cycle, bool colorRandomOption, bool rainbowColorOption)
	{

		this->vector3List.RemoveAll();
		this->rendering = false;



		this->size = size;
		this->cycle = cycle;


		this->colorRandomOption = colorRandomOption;
		this->rainbowColorOption = rainbowColorOption;


		for (int j = 0; j < this->cycle; ++j)
		{
			this->vector3List.Add(GLVector3((-180) + (j * 1.6 * this->size), 1 * this->size, 0 * this->size));
		}


	}

	void SpringLine::ObjectiveRendering()
	{
		if (!rendering)
		{
			return;
		}


		this->ApplyMatrix();


		static int temp = 0;
		static int nextSpringStack = 0;
		static int start = 0;
		static int end = 0;
		static double moveX = 0;

		static int a = 0;

		if (temp >= 360)
		{
			temp = 0;
			nextSpringStack++;
		}








		glBegin(GL_LINE_STRIP);

		for (int j = 0 + nextSpringStack; j < this->cycle + nextSpringStack; ++j)
		{
			if (j != nextSpringStack)
			{
				start = 0;

			}
			else
			{
				start = temp;

			}
			if (j != this->cycle + nextSpringStack - 1)
			{
				end = 360;

			}
			else
			{
				end = temp;

			}


			for (int i = 0 + start; i < end; ++i)
			{
				if (this->colorRandomOption)
				{
					glColor3d(this->color3D.x, this->color3D.y, this->color3D.z);


				}
				else if (this->rainbowColorOption)
				{
					glColor3d(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);


				}
				else
				{
					glColor3d(1, 0, 0);


				}

				if (i < 180)
				{
					glVertex3d((-180) + (j * 1.6 * this->size) + 1 * this->size * cos((i* PI6) / 180.0) + moveX, 0 + 1 * this->size + 1 * this->size * sin((i* PI6) / 180.0), 0 * this->size);
				}
				else if (i < 360)
				{

					glVertex3d((-180) + (1 * this->size * 0.8) + (j * 1.6 * this->size) + 1 * this->size * 1.8 * cos((i * PI6) / 180.0) + moveX, 0 + 1 * this->size + 1 * this->size * 1.8 *  sin((i* PI6) / 180.0), 0 * this->size);

				}


			}



		}
		glEnd();

		if (animationFlag)
		{
			temp++;
			moveX -= (1.6 * this->size) / (360);
		}






		this->masterMatrixs->glLoadMasterMatrix();


	}


	//class Polygon0

	void Polygon0::DrawTextureSphere(float r, int n, GLuint texture)
	{


		ApplyMatrix();
		glEnable(GL_LIGHTING);
		glDisable(GL_LIGHTING);





		glColor4f(1.f, 1.f, 1.f, 1.0f);





		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);



		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		glBindTexture(GL_TEXTURE_2D, texture);


		glutSolidSphere(r, 30.0, 30.0);





		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);


		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);



		this->masterMatrixs->glLoadMasterMatrix();


	}
	void Polygon0::DrawStar(float size)
	{

		ApplyMatrix();

		if (!this->objectActivate)
			return;

		glDisable(GL_LIGHTING);





		this->Scale(size, size, size);
		this->SetFreeRotateXAxis(GLVector3(0, 0, 0), GLVector3(1, 0, 0));
		this->SetFreeRotateYAxis(GLVector3(0, 0, 0), GLVector3(0, 1, 0));


		ApplyMatrix();
		this->freeXAxisRotateDegree = 0;
		this->freeYAxisRotateDegree = 0 + addRotation;
		glColor4f(this->color4D.x, this->color4D.y, this->color4D.z, this->color4D.w);
		glutSolidTetrahedron();
		glColor4f(0, 0, 0, 1);
		glutWireTetrahedron();
		this->masterMatrixs->glLoadMasterMatrix();



		ApplyMatrix();
		this->freeXAxisRotateDegree = 180;
		this->freeYAxisRotateDegree = 0 - addRotation;
		glColor4f(this->color4D.x, this->color4D.y, this->color4D.z, this->color4D.w);
		glutSolidTetrahedron();
		glColor4f(0, 0, 0, 1);
		glutWireTetrahedron();
		this->masterMatrixs->glLoadMasterMatrix();




		ApplyMatrix();
		this->freeXAxisRotateDegree = 0;
		this->freeYAxisRotateDegree = 180 + addRotation;
		glColor4f(this->color4D.x, this->color4D.y, this->color4D.z, this->color4D.w);
		glutSolidTetrahedron();
		glColor4f(0, 0, 0, 1);
		glutWireTetrahedron();
		this->masterMatrixs->glLoadMasterMatrix();

		ApplyMatrix();
		this->freeXAxisRotateDegree = 180;
		this->freeYAxisRotateDegree = 180 - addRotation;
		glColor4f(this->color4D.x, this->color4D.y, this->color4D.z, this->color4D.w);
		glutSolidTetrahedron();
		glColor4f(0, 0, 0, 1);
		glutWireTetrahedron();
		this->masterMatrixs->glLoadMasterMatrix();



		addRotation = (addRotation + 1) % 360;


		glColor3f(0.0, 0.0, 0.0);




		// Place base of cube on marker surface.
		//glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.


		glEnable(GL_LIGHTING);





		this->masterMatrixs->glLoadMasterMatrix();

	}


	void Polygon0::DrawTextureCube2(float size, GLuint texture, GLuint textureFloor)
	{
		ApplyMatrix();
		long f, i;
		//glDisable(GL_LIGHTING);


		static GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 }; //Black Color
		static GLfloat qaBlue[] = { 1.0, 1.0, 0.3, 1.0 }; //Green Color
		static GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 }; //White Color
		static GLfloat qaRed[] = { 1.0, 0.0, 0.0, 1.0 }; //White Color
		static GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 }; //Green Color
		static GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
		static GLfloat qaBlue2[] = { 0.0, 0.0,1.0f, 1.0 }; //Green Color









		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const GLfloat cube_vertex_colors[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
		};
		GLint cube_num_faces = 6;
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 }, //밑면
		{ 4, 5, 6, 7 }
		};



		if (size <= 0)
		{

			size = 2.0;
		}

		glColor4f(1.f, 1.f, 1.f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glBegin(GL_QUADS);





		for (f = 0; f < cube_num_faces; f++)
		{


			if (f == 4)
			{
				glEnd();
				glBindTexture(GL_TEXTURE_2D, textureFloor);
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glBegin(GL_QUADS);
			}
			else if (f == 5)
			{

				glEnd();
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glBegin(GL_QUADS);


			}

			for (i = 0; i < 4; i++)
			{
				this->SetNormal(
					GLVector3(cube_vertices[cube_faces[f][2]][0] * size - cube_vertices[cube_faces[f][1]][0] * size, cube_vertices[cube_faces[f][2]][1] * size - cube_vertices[cube_faces[f][1]][1] * size, cube_vertices[cube_faces[f][2]][2] * size - cube_vertices[cube_faces[f][1]][2] * size),
					GLVector3(cube_vertices[cube_faces[f][0]][0] * size - cube_vertices[cube_faces[f][1]][0] * size, cube_vertices[cube_faces[f][0]][1] * size - cube_vertices[cube_faces[f][1]][1] * size, cube_vertices[cube_faces[f][0]][2] * size - cube_vertices[cube_faces[f][1]][2] * size)

				);

				//glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
				if (i == 0)
					glTexCoord2f(1, 1);
				else if (i == 1)
					glTexCoord2f(1, 0);
				else if (i == 2)
					glTexCoord2f(0, 0);
				else if (i == 3)
					glTexCoord2f(0, 1);
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
			}


		}
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		for (f = 0; f < cube_num_faces; f++)
		{
			glBegin(GL_LINE_LOOP);
			for (i = 0; i < 4; i++)
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
			glEnd();
		}


		// Place base of cube on marker surface.
		//glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.

		glEnable(GL_DEPTH_TEST);

		this->masterMatrixs->glLoadMasterMatrix();
	}









	void Polygon0::DrawTextureCube(float size, GLuint textrue)
	{
		ApplyMatrix();
		long f, i;
		//glDisable(GL_LIGHTING);

		static GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 }; //Black Color
		static GLfloat qaBlue[] = { 1.0, 1.0, 0.3, 1.0 }; //Green Color
		static GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 }; //White Color
		static GLfloat qaRed[] = { 1.0, 0.0, 0.0, 1.0 }; //White Color
		static GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 }; //Green Color
		static GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
		static GLfloat qaBlue2[] = { 0.0, 0.0,1.0f, 1.0 }; //Green Color









		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const GLfloat cube_vertex_colors[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
		};
		GLint cube_num_faces = 6;
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};



		if (size <= 0)
		{

			size = 2.0;
		}



		glColor4f(1.f, 1.f, 1.f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, textrue);
		glBegin(GL_QUADS);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		for (f = 0; f < cube_num_faces; f++)
			for (i = 0; i < 4; i++)
			{
				this->SetNormal(
					GLVector3(cube_vertices[cube_faces[f][2]][0] * size - cube_vertices[cube_faces[f][1]][0] * size, cube_vertices[cube_faces[f][2]][1] * size - cube_vertices[cube_faces[f][1]][1] * size, cube_vertices[cube_faces[f][2]][2] * size - cube_vertices[cube_faces[f][1]][2] * size),
					GLVector3(cube_vertices[cube_faces[f][0]][0] * size - cube_vertices[cube_faces[f][1]][0] * size, cube_vertices[cube_faces[f][0]][1] * size - cube_vertices[cube_faces[f][1]][1] * size, cube_vertices[cube_faces[f][0]][2] * size - cube_vertices[cube_faces[f][1]][2] * size)

				);

				//glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
				if (i == 0)
					glTexCoord2f(1, 1);
				else if (i == 1)
					glTexCoord2f(1, 0);
				else if (i == 2)
					glTexCoord2f(0, 0);
				else if (i == 3)
					glTexCoord2f(0, 1);
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
			}
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		for (f = 0; f < cube_num_faces; f++)
		{
			glBegin(GL_LINE_LOOP);
			for (i = 0; i < 4; i++)
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
			glEnd();
		}


		// Place base of cube on marker surface.
		//glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.

		glEnable(GL_DEPTH_TEST);


		this->masterMatrixs->glLoadMasterMatrix();
	}


	void Polygon0::DrawSphere2(float size, bool colorRandomOption, bool rainbowColorOption, bool wireOption)
	{
		ApplyMatrix();
		static GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 }; //Black Color
		static GLfloat qaBlue[] = { 0.0, 1.0, 1.0, 1.0 }; //Green Color
		static GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 }; //White Color
		static GLfloat qaRed[] = { 1.0, 0.0, 0.0, 1.0 }; //White Color
		static GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 }; //Green Color
		static GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
		static GLfloat qaBlue2[] = { 0.0, 0.0,1.0f, 1.0 }; //Green Color
		glEnable(GL_LIGHTING);

		//glEnable(GL_COLOR_MATERIAL); 
		//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaBlue2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaBlue);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60);


		if (colorRandomOption)
		{
			glColor3d(0.02, 0.3, 1.0);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaBlue2);

		}
		else if (rainbowColorOption)
		{
			glColor3d(rand() % 10 / 10, rand() % 10 / 10, rand() % 10 / 10);


		}
		else
		{
			glColor3d(1, 0, 0);


		}

		if (wireOption == false)
		{

			glColor4f(0.02, 0.3, 1.0, 1.0);
			glutSolidSphere(size, 120, 120);
		}
		else
		{
			glutWireSphere(size, 60, 60);
		}


		glDisable(GL_COLOR_MATERIAL);

		this->masterMatrixs->glLoadMasterMatrix();



	}


	void Polygon0::SetBasicParameter(float size, bool colorRandomOption, bool rainbowColorOption)
	{

		this->size = size;
		this->colorRandomOption = colorRandomOption;
		this->rainbowColorOption = rainbowColorOption;

	}

	int Polygon0::NumberOfPoint()
	{
		return this->vector3List.Length();


	}

	void DrawingLine::ObjectiveRendering()
	{

		this->ApplyMatrix();
		if (this->rendering)
		{


			if (this->vector3List.Length() < 2)
			{
				this->rendering = false;
				return;
			}



			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < this->vector3List.Length(); ++i)
			{
				glVertex3d(this->vector3List.GetDataOfIndex(i).x, this->vector3List.GetDataOfIndex(i).y, this->vector3List.GetDataOfIndex(i).z);

			}
			glEnd();



		}
		this->masterMatrixs->glLoadMasterMatrix();

	}

	void Polygon0::DrawBoard(float size, bool colorRandomOption, bool rainbowColorOption)
	{


		ApplyMatrix();
		glDisable(GL_LIGHTING); // Just use colours.

		long f, i;
		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 0.1, 1.0 },
		{ -1.0, 0.1, 1.0 },
		{ -1.0, 0.1, -1.0 },
		{ 1.0, 0.1, -1.0 },

		{ 1.0, 0, 1.0 },
		{ -1.0, 0, 1.0 },
		{ -1.0, 0, -1.0 },
		{ 1.0, 0, -1.0 },


		};
		const GLfloat cube_vertex_colors[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
		};
		GLint cube_num_faces = 6;
		const short cube_faces[6][4] =
		{
		{ 0, 1, 2, 3 },
		{ 4, 5, 1, 0 },
		{ 4, 5, 6, 7 },
		{ 3, 2, 6, 7 },
		{ 0, 4, 7, 3 },
		{ 1, 2, 6, 5 }
		};

		if (size <= 0)
		{

			size = 2.0;
		}
		this->masterMatrixs->glLoadMasterMatrix();
		glTranslated(this->currentTranslateMatrix[12], this->currentTranslateMatrix[13], this->currentTranslateMatrix[14]);
		glRotated(this->currentXRotateMatrix[0], this->currentXRotateMatrix[1], this->currentXRotateMatrix[2], this->currentXRotateMatrix[3]);
		glRotated(this->currentYRotateMatrix[0], this->currentYRotateMatrix[1], this->currentYRotateMatrix[2], this->currentYRotateMatrix[3]);
		glRotated(this->currentZRotateMatrix[0], this->currentZRotateMatrix[1], this->currentZRotateMatrix[2], this->currentZRotateMatrix[3]);
		glScaled(this->currentScaleMatrix[0], this->currentScaleMatrix[1], this->currentScaleMatrix[2]);


		if (colorRandomOption)
		{
			glBegin(GL_QUADS);
			for (f = 0; f < cube_num_faces; f++)
				for (i = 0; i < 4; i++)
				{
					glColor3f(this->color3D.x, this->color3D.y, this->color3D.z);
					glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
				}
			glEnd();

		}

		else if (rainbowColorOption)
		{
			glBegin(GL_QUADS);
			for (f = 0; f < cube_num_faces; f++)
				for (i = 0; i < 4; i++)
				{
					glColor3f(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);
					glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
				}
			glEnd();

		}

		else
		{
			glBegin(GL_QUADS);
			for (f = 0; f < cube_num_faces; f++)
				for (i = 0; i < 4; i++)
				{
					glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
					glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
				}
			glEnd();
		}
		glColor3f(0.0, 0.0, 0.0);
		for (f = 0; f < cube_num_faces; f++)
		{
			glBegin(GL_LINE_LOOP);
			for (i = 0; i < 4; i++)
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
			glEnd();
		}



		// Place base of cube on marker surface.
		//glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.

		glEnable(GL_LIGHTING);
		this->masterMatrixs->glLoadMasterMatrix();


	}

	void Polygon0::DrawWireRectangle(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();



		const GLfloat rectangleVertices[4][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		};

		this->size = size;


		glColor4d(0, 1.0, 0.5, this->alpha);

		glBegin(GL_LINE);

		for (int i = 0; i < 4; ++i)
		{
			glVertex2d(rectangleVertices[i][0] * size, rectangleVertices[i][1] * size);
		}


		glEnd();




		this->masterMatrixs->glLoadMasterMatrix();
	}

	void Polygon0::DrawBoard(InitializeData initializeData)
	{

	}


	void Polygon0::Confirm()
	{

		this->rendering = true;
	}
	void Polygon0::Disable()
	{
		this->rendering = false;
	}

	void Polygon0::Initialize()
	{
		this->vector3List.RemoveAll();
		this->rendering = false;
	}
	void Polygon0::Undo()
	{

		this->vector3List.Remove();

	}

	void DrawingLine::AddPoints(GLVector3 point)
	{
		if (this->vector3List.Length() >= lineLimit)
		{


			return;

		}



		vector3List.Add(point);



	}

	//class MasterMatrix


	void MasterMatrix::OrthoOrPerspective()
	{
		this->orthoOrPerspective = !this->orthoOrPerspective;
		printf("asd%d\n", this->orthoOrPerspective);
		this->created = false;

		this->perspective = orthoOrPerspective;
		this->ortho = !orthoOrPerspective;




	}

	void MasterMatrix::PrintMatrix44(GLdouble* pMatrix)
	{
		printf("\n\n");
		for (int i = 0; i < 16; ++i)
		{
			if (i % 4 == 0)
			{
				printf("\n\n");

			}

			printf("%f  ", pMatrix[i]);

		}

	}

	GLdouble* MasterMatrix::MuliplyMatrix44(GLdouble* pMatrix1, GLdouble* pMatrix2)
	{

		GLdouble temp = 0;
		static GLdouble result[16];


		for (int j = 0; j < 4; ++j)
		{


			for (int k = 0; k < 4; ++k)
			{

				for (int l = 0; l < 4; ++l)
				{
					temp += pMatrix1[4 * j + (l)] * pMatrix2[4 * l + (k)];

				}


				result[j * 4 + (k)] = temp;

				temp = 0;

			}




		}

		return result;



	}
	void MasterMatrix::InitializeOrthoData()
	{
		this->orthoData.screenLTX = -400;
		this->orthoData.screenLTY = 400;

		this->orthoData.screenRBX = 400;
		this->orthoData.screenRBY = -400;

		this->orthoData.zNear = 400;
		this->orthoData.zFar = -400;

		this->orthoData.width = 800;
		this->orthoData.height = 800;

		this->orthoData.zSize = 800;


	}
	void MasterMatrix::InitializeCamera()
	{

		this->thisCamera.eyeX = 0;
		this->thisCamera.eyeY = 0;
		this->thisCamera.eyeZ = 300;
		this->thisCamera.centerX = 0;
		this->thisCamera.centerY = 0;
		this->thisCamera.centerZ = 0;
		this->thisCamera.upX = 0;
		this->thisCamera.upY = 1;
		this->thisCamera.upZ = 0;
		this->thisCamera.aspect = 1;
		this->thisCamera.fovy = 60.0;
		this->thisCamera.zNear = 1.0;
		this->thisCamera.zFar = 15000.0 + this->thisCamera.eyeZ;
	}

	void MasterMatrix::PerspectiveSetting()
	{

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(this->thisCamera.fovy, this->thisCamera.aspect, this->thisCamera.zNear, this->thisCamera.zFar + this->thisCamera.eyeZ);
		glTranslatef(0.0, -20.0, -30);
		this->created = true;

		glMatrixMode(GL_MODELVIEW);

	}

	void MasterMatrix::OrthoSetting()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(this->orthoData.screenLTX, this->orthoData.screenRBX, this->orthoData.screenRBY, this->orthoData.screenLTY, this->orthoData.zNear, this->orthoData.zFar);
		glTranslatef(0.0, 0.0, 10.f);
		this->created = true;

		glMatrixMode(GL_MODELVIEW);
	}

	void MasterMatrix::InitializeCamera(Camera camera)
	{
		this->thisCamera = camera;

	}

	void MasterMatrix::InitializeOrthoData(OrthoData orthoData)
	{
		this->orthoData = orthoData;

	}



	MasterMatrix::MasterMatrix(bool projection)
	{
		for (int i = 0; i < 16; ++i)
		{

			this->currentTranslateMatrix[i] = this->identityMatrix[i];


		}

		a = rand() % 120;
		printf("%d 프로젝션 %d\n", a, projection);


		this->InitializeCamera();
		this->InitializeOrthoData();

		if (projection == true)
		{
			this->perspective = true;
			this->ortho = false;
		}
		else if (projection == false)
		{
			this->perspective = false;
			this->ortho = true;
		}

	}



	MasterMatrix::MasterMatrix()
	{

		for (int i = 0; i < 16; ++i)
		{

			this->currentTranslateMatrix[i] = this->identityMatrix[i];

		}

		a = rand() % 120;
		printf("%d?\n", a);


		this->InitializeCamera();
		this->InitializeOrthoData();
		this->perspective = true;

	}


	MasterMatrix::MasterMatrix(OrthoData orthoData)
	{
		for (int i = 0; i < 16; ++i)
		{

			this->currentTranslateMatrix[i] = this->identityMatrix[i];

		}

		this->InitializeCamera();
		this->InitializeOrthoData(orthoData);


		this->ortho = true;

	}

	MasterMatrix::MasterMatrix(Camera camera)
	{
		for (int i = 0; i < 16; ++i)
		{

			this->currentTranslateMatrix[i] = this->identityMatrix[i];

		}

		this->InitializeCamera(camera);
		this->InitializeOrthoData();


		this->perspective = true;

	}

	MasterMatrix::MasterMatrix(Camera camera, OrthoData orthoData)
	{
		for (int i = 0; i < 16; ++i)
		{

			this->currentTranslateMatrix[i] = this->identityMatrix[i];

		}

		this->InitializeCamera(camera);
		this->InitializeOrthoData(orthoData);

		this->perspective = true;


	}



	void MasterMatrix::glSetMasterMatrix(GLdouble* translateMatrix, GLdouble* rotateMatrix, GLdouble* scaleMatrix)
	{



		for (int i = 0; i < 16; ++i)
		{
			this->currentTranslateMatrix[i] = translateMatrix[i];

		}

		for (int i = 0; i < 4; ++i)
		{
			this->currentXRotateMatrix[i] = rotateMatrix[i];
		}
		for (int i = 0; i < 4; ++i)
		{
			this->currentYRotateMatrix[i] = rotateMatrix[i + 4];
		}
		for (int i = 0; i < 4; ++i)
		{
			this->currentZRotateMatrix[i] = rotateMatrix[i + 8];
		}

		for (int i = 0; i < 3; ++i)
		{
			this->currentScaleMatrix[i] = scaleMatrix[i];
		}

		this->glLoadMasterMatrix();

	}
	void MasterMatrix::glMultMasterMatrix(GLdouble* pMatrix)
	{
		//행렬곱

	}


	void MasterMatrix::glLoadMasterMatrix()
	{
		//printf("일반 + %d\n", this->a);


		if (!this->created)
		{
			printf("\n%d적팀 정글은 탑에 사는데..\n", this->perspective);

			if (this->perspective)
			{
				this->PerspectiveSetting();
				printf("원근투영");

			}

			else if (this->ortho)
			{
				this->OrthoSetting();
				printf("직교투영");
			}

			created = true;

		}

		glLoadIdentity();
		glPushMatrix();
		glPopMatrix();





		//printf("%faa\n", this->currentYRotateMatrix[0]);
		//printf("%f %f %f %f\n", this->currentXRotateMatrix[0], this->currentXRotateMatrix[1], this->currentXRotateMatrix[2], this->currentXRotateMatrix[3]);
		glLoadMatrixd(this->currentTranslateMatrix);


		glRotated(this->currentXRotateMatrix[0], this->currentXRotateMatrix[1], this->currentXRotateMatrix[2], this->currentXRotateMatrix[3]);
		glRotated(this->currentYRotateMatrix[0], this->currentYRotateMatrix[1], this->currentYRotateMatrix[2], this->currentYRotateMatrix[3]);
		glRotated(this->currentZRotateMatrix[0], this->currentZRotateMatrix[1], this->currentZRotateMatrix[2], this->currentZRotateMatrix[3]);
		glScaled(this->currentScaleMatrix[0], this->currentScaleMatrix[1], this->currentScaleMatrix[2]);



		gluLookAt
		(
			this->thisCamera.eyeX, this->thisCamera.eyeY, this->thisCamera.eyeZ,
			this->thisCamera.centerX, this->thisCamera.centerY, this->thisCamera.centerZ,
			this->thisCamera.upX, this->thisCamera.upY, this->thisCamera.upZ
		);

		glPushMatrix();
		glPopMatrix();





	}


	void TwinCube::DrawTwinCube(MasterMatrix* masterMatrixs, float size, GLdouble space, bool horVerFlag, GLdouble* pMatrix)
	{

		//horizontal
		if (horVerFlag)
		{

			masterMatrixs->glLoadMasterMatrix();



			glTranslated(pMatrix[12], pMatrix[13], pMatrix[14]);
			glTranslated(space / 2.0, 0, 0);
			DrawCube(masterMatrixs, size);

			glTranslated(pMatrix[12], pMatrix[13], pMatrix[14]);
			glTranslated(-space / 2.0, 0, 0);
			DrawCube(masterMatrixs, size);

		}
		//Vertical
		else if (!horVerFlag)
		{

			masterMatrixs->glLoadMasterMatrix();



			glTranslated(pMatrix[12], pMatrix[13], pMatrix[14]);
			glTranslated(0, space / 2.0, 0);
			DrawCube(masterMatrixs, size);

			glTranslated(pMatrix[12], pMatrix[13], pMatrix[14]);
			glTranslated(0, -space / 2.0, 0);
			DrawCube(masterMatrixs, size);

		}







	}


	//GLAnimator member






	/*
	void Polygon0::DrawSpring(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();


		glBegin(GL_LINES);

		for (int i = 0; i < 540; ++i)
		{
			if (colorRandomOption)
			{
				glColor3d(this->color3D.x, this->color3D.y, this->color3D.z);


			}
			else if (rainbowColorOption)
			{
				glColor3d(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);


			}
			else
			{
				glColor3d(1, 0, 0);


			}

			if (i < 180) {
				glVertex3d((-180) + 1 * size * cos((i* PI6) / 180.0), 0 + 1 * size + 1 * size * sin((i* PI6) / 180.0), 0 * size);
			}
			else if (i < 360)
			{

				glVertex3d((-180) + (1 * size) + 1 * size * 2 * cos((i * PI6) / 180.0), 0 + 1 * size + 1 * size * 2 * sin((i* PI6) / 180.0), 0 * size);

			}
			else if (i < 540)
			{
				glVertex3d((-180) + (2 * size) + 1 * size * cos((i* PI6) / 180.0), 0 + 1 * size + 1 * size * sin((i* PI6) / 180.0), 0 * size);


			}

		}
		glEnd();




		this->masterMatrixs->glLoadMasterMatrix();
	}
	*/
	//method base:
	//ApplyMatrix();

	//Drawing..

	//this->masterMatrixs->glLoadMasterMatrix();

	void Polygon0::ObjectiveRendering()
	{

	}
	void Polygon0::AddPoints(GLVector3 point)
	{

	}

	void Polygon0::DrawLine(float size, bool colorRandomOption, bool rainbowColorOption)
	{

		ApplyMatrix();

		static const GLVector3 start = GLVector3(this->Position().x, this->Position().y, this->Position().z);
		static const GLVector3 next = GLVector3(this->Position().x + 1, this->Position().y + 1, this->Position().z + 1);
		if (colorRandomOption)
		{
			glColor3d(this->color3D.x, this->color3D.y, this->color3D.z);


		}
		else if (rainbowColorOption)
		{
			glColor3d(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);


		}
		else
		{
			glColor3d(1, 0, 0);


		}

		glBegin(GL_LINE_STRIP);

		glVertex3d(start.x * size, start.y* size, start.z* size);
		glVertex3d(next.x* size, next.y* size, next.z* size);



		glEnd();



		this->masterMatrixs->glLoadMasterMatrix();
	}

	void Polygon0::DrawZigzag(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();

		static const int cycle = 4;
		static const double compression = 0.5;


		if (colorRandomOption)
		{
			glColor3d(this->color3D.x, this->color3D.y, this->color3D.z);


		}
		else if (rainbowColorOption)
		{
			glColor3d(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);


		}
		else
		{
			glColor3d(1, 0, 0);


		}


		glBegin(GL_LINE_STRIP);



		for (int i = 0; i < cycle; ++i)
		{
			glVertex3d(size * 3 * i * compression, 0, 0);
			glVertex3d(size  * (3 * i + 1) * compression, 3 * size, 0);
			glVertex3d(size  * (3 * i + 2) * compression, -3 * size, 0);
			glVertex3d(size  * (3 * i + 3) * compression, 0, 0);
		}


		glEnd();





		this->masterMatrixs->glLoadMasterMatrix();
	}


	void Polygon0::DrawCircle(float radius, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();





		if (colorRandomOption)
		{
			glColor3d(this->color3D.x, this->color3D.y, this->color3D.z);


		}
		else if (rainbowColorOption)
		{
			glColor3d(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);


		}
		else
		{
			glColor3d(1, 0, 0);


		}
		glBegin(GL_LINE_STRIP);

		for (int i = 0; i <= 360; ++i)
		{

			glVertex3d(0 + radius * sin((i * PI6) / 180.0), 0 + radius * cos((i * PI6) / 180.0), 0);



		}

		glEnd();


		this->masterMatrixs->glLoadMasterMatrix();
	}
	void Polygon0::DrawXYZLine(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();
		glDisable(GL_LIGHTING);

		glColor3d(1, 0, 0);
		glBegin(GL_LINE_STRIP);

		glVertex3d(-1 * size, 0, 0);

		glVertex3d(1 * size, 0, 0);


		glEnd();
		glColor3d(0, 1, 0);
		glBegin(GL_LINE_STRIP);


		glVertex3d(0, 1 * size, 0);

		glVertex3d(0, -1 * size, 0);

		glEnd();


		glColor3d(0, 0, 1);
		glBegin(GL_LINE_STRIP);


		glVertex3d(0, 0, -1 * size);

		glVertex3d(0, 0, 1 * size);

		glEnd();

		glEnable(GL_LIGHTING);

		this->masterMatrixs->glLoadMasterMatrix();



	}
	void Polygon0::DrawXYLine(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();


		glColor3d(1, 0, 0);
		glBegin(GL_LINE_STRIP);

		glVertex3d(-1 * size, 0, 0);

		glVertex3d(1 * size, 0, 0);


		glEnd();
		glColor3d(0, 1, 0);
		glBegin(GL_LINE_STRIP);


		glVertex3d(0, 1 * size, 0);

		glVertex3d(0, -1 * size, 0);

		glEnd();


		this->masterMatrixs->glLoadMasterMatrix();


	}

	void Polygon0::DrawRibbon(float size, bool colorRandomOption, bool rainbowColorOption, bool animationFlag)
	{

		ApplyMatrix();

		GLVector3 vertices[5]
		{
			GLVector3(-1 * size,1 * size,0 * size),
			GLVector3(-1 * size,-1 * size,0 * size),
			GLVector3(0 * size,0 * size,0 * size),
			GLVector3(1 * size,1 * size,0 * size),
			GLVector3(1 * size,-1 * size,0 * size)

		};


		static bool plus = true;
		static int stack = 0;
		static const int stackLimit = 120;

		static const double slope = 0.3;

		static const double incrementModulus = 0.03;



		if (colorRandomOption)
		{
			glColor3d(this->color3D.x, this->color3D.y, this->color3D.z);


		}
		else if (rainbowColorOption)
		{
			glColor3d(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);


		}
		else
		{
			glColor3d(1, 0, 0);


		}


		glBegin(GL_POLYGON);
		glVertex3d(vertices[0].x - stack * size * incrementModulus, vertices[0].y + stack * size * incrementModulus * slope, vertices[0].z);
		glVertex3d(vertices[1].x - stack * size * incrementModulus, vertices[1].y - stack * size * slope * incrementModulus, vertices[1].z);
		glVertex3d(vertices[2].x, vertices[2].y, vertices[2].z);

		glEnd();


		glBegin(GL_POLYGON);
		glVertex3d(vertices[3].x + stack * size * incrementModulus, vertices[3].y + stack * size * slope * incrementModulus, vertices[3].z);
		glVertex3d(vertices[4].x + stack * size * incrementModulus, vertices[4].y - stack * size * slope * incrementModulus, vertices[4].z);
		glVertex3d(vertices[2].x, vertices[2].y, vertices[2].z);

		glEnd();


		if (animationFlag)
		{

			if (plus)
			{

				stack++;

			}
			else
			{
				stack--;

			}

			if (stack > stackLimit && plus)
			{
				plus = false;

				stack = stackLimit - 1;


			}
			else if (stack < 0 && !plus)
			{

				plus = true;

				stack = 1;

			}
		}


		this->masterMatrixs->glLoadMasterMatrix();

	}

	void Polygon0::DrawRectEscalator(float size, bool colorRandomOption, bool rainbowColorOption, bool animationFlag)
	{


		ApplyMatrix();


		struct RectStruct
		{

			bool activate;
			GLVector3 vertex[2];



		};

		static RectStruct rectStruct[5];

		static bool firstGenerated = true;


		if (firstGenerated)
		{
			rectStruct[0].activate = false;





			rectStruct[1].vertex[0] = GLVector3(-3.5* size, 1 * size, 0 * size);
			rectStruct[1].vertex[1] = GLVector3(-2.5* size, 0 * size, 0 * size);
			rectStruct[1].activate = true;





			rectStruct[2].vertex[0] = GLVector3(-1.5* size, 1 * size, 0 * size);
			rectStruct[2].vertex[1] = GLVector3(-0.5* size, 0 * size, 0 * size);
			rectStruct[2].activate = true;





			rectStruct[3].vertex[0] = GLVector3(0.5* size, 1 * size, 0 * size);
			rectStruct[3].vertex[1] = GLVector3(1.5* size, 0 * size, 0 * size);
			rectStruct[3].activate = true;





			rectStruct[4].vertex[0] = GLVector3(2.5* size, 1 * size, 0 * size);
			rectStruct[4].vertex[1] = GLVector3(3.5* size, 0 * size, 0 * size);
			rectStruct[4].activate = true;


			firstGenerated = false;
		}



		static double xMove = 1;
		static double rightLimit = 0;
		static double left = 0;
		static bool flag = false;



		rightLimit = 3.5 * size;


		if (colorRandomOption)
		{
			glColor3d(this->color3D.x, this->color3D.y, this->color3D.z);


		}
		else if (rainbowColorOption)
		{
			glColor3d(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);


		}
		else
		{
			glColor3d(1, 0, 0);


		}

		for (int i = 0; i < 5; ++i)
		{

			if (rectStruct[i].activate)
			{



				if (rightLimit <= rectStruct[4].vertex[1].x)
				{

					if (flag == false)
					{
						flag = true;

					}
					rectStruct[4].vertex[1].x = rightLimit;

					if (rectStruct[0].activate == false)
					{
						rectStruct[0].vertex[0] = GLVector3(-4.5* size, 1 * size, 0 * size);
						rectStruct[0].vertex[1] = GLVector3(-4.5* size, 0 * size, 0 * size);
						rectStruct[0].activate = true;

					}


					rectStruct[0].vertex[0].x = -4.5* size;
				}

				if (flag && rectStruct[4].vertex[0].x >= rightLimit)
				{
					flag = false;

					for (int j = 0; j < 4; ++j)
					{
						rectStruct[4 - j] = rectStruct[4 - j - 1];



					}
					rectStruct[0].activate = false;

				}


				if (animationFlag)
				{
					rectStruct[i].vertex[0].x += xMove;
					rectStruct[i].vertex[1].x += xMove;
				}
				glRectd(rectStruct[i].vertex[0].x, rectStruct[i].vertex[0].y, rectStruct[i].vertex[1].x, rectStruct[i].vertex[1].y);




			}


		}




		this->masterMatrixs->glLoadMasterMatrix();
	}




	//추후에 오버플로우 방지하도록 구현
	void Polygon0::DrawSineGraph(float size, bool colorRandomOption, bool rainbowColorOption, bool animationFlag)
	{
		ApplyMatrix();
		static int cycle = 6;

		static int temp = 0;

		static double xMove = 0;








		glBegin(GL_LINE_STRIP);
		for (int i = 0 + temp / 2; i <= 360 + temp / 2; ++i)
		{
			if (colorRandomOption)
			{
				glColor3d(this->color3D.x, this->color3D.y, this->color3D.z);


			}
			else if (rainbowColorOption)
			{
				glColor3d(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);


			}
			else
			{
				glColor3d(1, 0, 0);


			}

			glVertex3d((-180) + i + xMove, size * sin(10 * ((i * PI6) / 180.0)), 0);



		}
		glEnd();

		if (animationFlag)
		{
			xMove -= 0.5;
			temp++;
		}




		this->masterMatrixs->glLoadMasterMatrix();
	}


	void Polygon0::DrawRectangle(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();

		const GLfloat rectangleVertices[4][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		};

		this->size = size;


		glColor4d(0, 1.0, 0.5, this->alpha);

		glBegin(GL_QUADS);

		for (int i = 0; i < 4; ++i)
		{
			glVertex2d(rectangleVertices[i][0] * size, rectangleVertices[i][1] * size);
		}


		glEnd();



		this->masterMatrixs->glLoadMasterMatrix();

	}

	//나중에 오버플로우 방지 코드 만들어라
	void Polygon0::DrawSpring(float size, bool colorRandomOption, bool rainbowColorOption, bool animationFlag)
	{
		ApplyMatrix();
		static int temp = 0;
		static int nextSpringStack = 0;
		static int start = 0;
		static int end = 0;
		const static int springNum = 6;
		static double moveX = 0;

		static int a = 0;

		if (temp >= 360)
		{
			temp = 0;
			nextSpringStack++;
		}








		glBegin(GL_LINE_STRIP);

		for (int j = 0 + nextSpringStack; j < springNum + nextSpringStack; ++j)
		{
			if (j != nextSpringStack)
			{
				start = 0;

			}
			else
			{
				start = temp;

			}
			if (j != springNum + nextSpringStack - 1)
			{
				end = 360;

			}
			else
			{
				end = temp;

			}


			for (int i = 0 + start; i < end; ++i)
			{
				if (colorRandomOption)
				{
					glColor3d(this->color3D.x, this->color3D.y, this->color3D.z);


				}
				else if (rainbowColorOption)
				{
					glColor3d(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);


				}
				else
				{
					glColor3d(1, 0, 0);


				}

				if (i < 180)
				{
					glVertex3d((-180) + (j * 1.6 * size) + 1 * size * cos((i* PI6) / 180.0) + moveX, 0 + 1 * size + 1 * size * sin((i* PI6) / 180.0), 0 * size);
				}
				else if (i < 360)
				{

					glVertex3d((-180) + (1 * size * 0.8) + (j * 1.6 * size) + 1 * size * 1.8 * cos((i * PI6) / 180.0) + moveX, 0 + 1 * size + 1 * size * 1.8 *  sin((i* PI6) / 180.0), 0 * size);

				}


			}



		}
		glEnd();

		if (animationFlag)
		{
			temp++;
			moveX -= (1.6 * size) / (360);
		}



		this->masterMatrixs->glLoadMasterMatrix();
	}

	//2D
	void Polygon0::DrawTriangle(float size, bool colorRandomOption, bool rainbowColorOption)
	{


		ApplyMatrix();

		if (this->objectActivate == false)
		{
			return;
		}

		const GLfloat triangleVertices[3][3] =
		{
		{ 1.0, 0.0, 0.0 },  //1
		{ -1.0, 0.0, 0.0 }, //2
		{ 0.0, 1.0, 0.0 },	//3


		};
		const GLfloat triangleVerticesColors[3][3] =
		{
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },

		};
		GLint triangleFaces = 1;
		//GLint rectangleFaces = 3;


		const short triangleFacesColors[1][3] =
		{


		{ 1, 2, 0 },



		};

		this->size = size;



		for (int i = 0; i < triangleFaces; ++i)
		{
			glEnable(GL_BLEND);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_LINE_LOOP);
			for (int j = 0; j < 3; ++j)
			{
				glColor4f(triangleVerticesColors[triangleFacesColors[i][j]][0], triangleVerticesColors[triangleFacesColors[i][j]][1], triangleVerticesColors[triangleFacesColors[i][j]][2], this->alpha);
				glVertex3f(triangleVertices[triangleFacesColors[i][j]][0] * size, triangleVertices[triangleFacesColors[i][j]][1] * size, triangleVertices[triangleFacesColors[i][j]][2] * size * 0.1);
			}

			glEnd();

			glEnable(GL_BLEND);

		}







		glDisable(GL_LIGHTING);






		this->masterMatrixs->glLoadMasterMatrix();



	}



	void Polygon0::DrawWireTriangle(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();


		const GLfloat triangleVertices[6][3] =
		{
		{ 1.0, 0.0, 0.0 },  //1
		{ -1.0, 0.0, 0.0 }, //2
		{ 0.0, 1.0, 0.0 },	//3
		{ 1.0, 0.0, 1.0 },  //4
		{ -1.0, 0.0, 1.0 }, //5
		{ 0.0, 1.0, 1.0 },  //6

		};
		const GLfloat triangleVerticesColors[6][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0 },

		};
		GLint triangleFaces = 2;
		GLint rectangleFaces = 3;


		const short triangleFacesColors[2][3] =
		{


		{ 1, 2, 0 },
		{ 3, 5, 4 }



		};
		const short rectangleFacesColor[6][3]
		{
		{ 1, 5, 2 },
		{ 1, 4, 5 },

		{ 0, 2, 5 },
		{ 0, 5, 3 },

		{ 0, 3, 4 },
		{ 0, 4, 1 },
		};



		for (int i = 0; i < triangleFaces; ++i)
		{


			glBegin(GL_LINE_LOOP);
			for (int j = 0; j < 3; ++j)
			{
				glColor3f(triangleVerticesColors[triangleFacesColors[i][j]][0], triangleVerticesColors[triangleFacesColors[i][j]][1], triangleVerticesColors[triangleFacesColors[i][j]][2]);
				glVertex3f(triangleVertices[triangleFacesColors[i][j]][0] * size, triangleVertices[triangleFacesColors[i][j]][1] * size, triangleVertices[triangleFacesColors[i][j]][2] * size * 0.1);
			}
			glEnd();



		}



		for (int i = 0; i < rectangleFaces * 2; ++i)
		{




			glBegin(GL_LINE_LOOP);
			for (int j = 0; j < 3; ++j)
			{
				glColor3f(triangleVerticesColors[rectangleFacesColor[i][j]][0], triangleVerticesColors[rectangleFacesColor[i][j]][1], triangleVerticesColors[rectangleFacesColor[i][j]][2]);
				glVertex3f(triangleVertices[rectangleFacesColor[i][j]][0] * size, triangleVertices[rectangleFacesColor[i][j]][1] * size, triangleVertices[rectangleFacesColor[i][j]][2] * size * 0.1);
			}

			glEnd();


		}




		glDisable(GL_LIGHTING);

		this->masterMatrixs->glLoadMasterMatrix();
	}


	void Polygon0::DrawSphere(float size, bool colorRandomOption, bool rainbowColorOption, bool wireOption)
	{

		ApplyMatrix();

		static GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 }; //Black Color
		static GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 }; //Green Color
		static GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 }; //White Color
		static GLfloat qaRed[] = { 1.0, 0.0, 0.0, 1.0 }; //White Color

		static GLfloat qaAmbientLight[] = { 0.1, 0.1, 0.1, 1.0 };
		static GLfloat qaDiffuseLight[] = { 1, 1, 1, 1.0 };
		static GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
		static GLfloat emitLight[] = { 0.9, 0.9, 0.9, 0.01 };
		static GLfloat Noemit[] = { 0.0, 0.0, 0.0, 1.0 };
		// Light source position
		static GLfloat qaLightPosition[] = { 0, 0, 0, 1 };

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		// Set lighting intensity and color
		glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);



		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaGreen);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.2);

		if (colorRandomOption)
		{
			glColor3d(this->color3D.x, this->color3D.y, this->color3D.z);


		}
		else if (rainbowColorOption)
		{
			glColor3d(rand() % 10 / 10, rand() % 10 / 10, rand() % 10 / 10);


		}
		else
		{
			glColor3d(1, 0, 0);


		}

		if (wireOption == false)
		{
			glutSolidSphere(size, 25, 25);
		}
		else
		{
			glutWireSphere(size, 25, 25);
		}

		glPopMatrix();
		glPushMatrix();






		glTranslatef(5.0, 200.0, -350.0);

		// Set the light position
		glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLight);   // Make sphere glow (emissive) 
		glutSolidSphere(size / 6, 25, 25);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);



		this->masterMatrixs->glLoadMasterMatrix();

		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}


	void Polygon0::DrawSphere(float size, bool colorRandomOption, bool rainbowColorOption)
	{

		ApplyMatrix();

		static GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 }; //Black Color
		static GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 }; //Green Color
		static GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 }; //White Color
		static GLfloat qaRed[] = { 1.0, 0.0, 0.0, 1.0 }; //White Color

		static GLfloat qaAmbientLight[] = { 0.1, 0.1, 0.1, 1.0 };
		static GLfloat qaDiffuseLight[] = { 1, 1, 1, 1.0 };
		static GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
		static GLfloat emitLight[] = { 0.9, 0.9, 0.9, 0.01 };
		static GLfloat Noemit[] = { 0.0, 0.0, 0.0, 1.0 };
		// Light source position
		static GLfloat qaLightPosition[] = { 0, 0, 0, 1 };

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		// Set lighting intensity and color
		glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);



		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaGreen);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.2);

		if (colorRandomOption)
		{
			glColor3d(this->color3D.x, this->color3D.y, this->color3D.z);


		}
		else if (rainbowColorOption)
		{
			glColor3d(rand() % 10 / 10, rand() % 10 / 10, rand() % 10 / 10);


		}
		else
		{
			glColor3d(1, 0, 0);


		}


		glutSolidSphere(size, 25, 25);


		glPopMatrix();
		glPushMatrix();






		glTranslatef(5.0, 200.0, -350.0);

		// Set the light position
		glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLight);   // Make sphere glow (emissive) 
		glutSolidSphere(size / 6, 25, 25);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);



		this->masterMatrixs->glLoadMasterMatrix();

		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}

	void Polygon0::DrawWireTorus(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();
		if (colorRandomOption)
		{

			glColor3f(this->color3D.x, this->color3D.y, this->color3D.z);
		}
		else if (rainbowColorOption)
		{
			glColor3f(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);
		}
		else
		{
			glColor3f(0, 0, 1);
		}
		glutWireTorus(size - 10, size, 25, 25);
		this->masterMatrixs->glLoadMasterMatrix();
	}
	void Polygon0::DrawWireCone(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();
		if (colorRandomOption)
		{

			glColor3f(this->color3D.x, this->color3D.y, this->color3D.z);
		}
		else if (rainbowColorOption)
		{
			glColor3f(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);
		}
		else
		{
			glColor3f(0, 0, 1);
		}
		glutWireCone(size, size * 2, 25, 25);
		this->masterMatrixs->glLoadMasterMatrix();
	}
	void Polygon0::Create3DObject(int num, float size, bool colorRandomOption, bool rainbowColorOption)
	{


		switch (num)
		{
		case 1:
			DrawCube(size, colorRandomOption, rainbowColorOption);
			break;
		case 2:
			DrawWireCube(size, colorRandomOption, rainbowColorOption);
			break;
		case 3:
			DrawWireSphere(size, colorRandomOption, rainbowColorOption);
			break;
		case 4:
			DrawSphere(size, colorRandomOption, rainbowColorOption);
			break;
		case 5:
			DrawWireCone(size, colorRandomOption, rainbowColorOption);

			break;
		case 6:
			DrawWireTorus(size, colorRandomOption, rainbowColorOption);

			break;
		case 7:
			DrawWireTorus(size, true, true);
			DrawWireSphere(size, true, true);
			DrawWireSphere(size - 20, true, true);

			break;
		case 8:
			DrawWireTriangle(size, colorRandomOption, rainbowColorOption);


			break;
		case 9:
			DrawWireCube(size, false, true);
			DrawWireSphere(size, false, true);
			DrawWireSphere(size - 20, colorRandomOption, false);

			break;
		case 10:
			DrawCube(size, false, false);
			DrawWireSphere(size, false, true);
			DrawWireSphere(size - 20, colorRandomOption, false);

			break;
		}


	}

	void Polygon0::ApplyMatrix()
	{
		static GLdouble temp = 5.0;

		this->masterMatrixs->glLoadMasterMatrix();

		glTranslated(this->currentTranslateMatrix[12], this->currentTranslateMatrix[13], this->currentTranslateMatrix[14]);



		//짐벌락 해결
		if (this->rotationAccumulate)
		{

			glMultMatrixd(this->rotationMatrix);

			glPushMatrix();
			glLoadIdentity();


			if (this->xyzDegree[0] != 0)
			{

				glRotated(this->xyzDegree[0], 1, 0, 0);

			}
			if (this->xyzDegree[1] != 0)
			{
				glRotated(this->xyzDegree[1], 0, 1, 0);
			}

			if (this->xyzDegree[2] != 0)
			{
				glRotated(this->xyzDegree[2], 0, 0, 1);
			}






			xyzDegree[0] = 0;
			xyzDegree[1] = 0;
			xyzDegree[2] = 0;



			glMultMatrixd(this->rotationMatrix);
			glGetDoublev(GL_MODELVIEW_MATRIX, this->rotationMatrix);

			glPopMatrix();

		}





		//x Axis

		glTranslated(this->freeXAxisPoints[0].x, this->freeXAxisPoints[0].y, this->freeXAxisPoints[0].z);


		glRotated(this->freeXAxisRotateDegree,
			this->freeXAxisPoints[1].x - this->freeXAxisPoints[0].x,
			this->freeXAxisPoints[1].y - this->freeXAxisPoints[0].y,
			this->freeXAxisPoints[1].z - this->freeXAxisPoints[0].z);


		glTranslated(-this->freeXAxisPoints[0].x, -this->freeXAxisPoints[0].y, -this->freeXAxisPoints[0].z);


		//y Axis

		glTranslated(this->freeYAxisPoints[0].x, this->freeYAxisPoints[0].y, this->freeYAxisPoints[0].z);


		glRotated(this->freeYAxisRotateDegree,
			this->freeYAxisPoints[1].x - this->freeYAxisPoints[0].x,
			this->freeYAxisPoints[1].y - this->freeYAxisPoints[0].y,
			this->freeYAxisPoints[1].z - this->freeYAxisPoints[0].z);



		glTranslated(-this->freeYAxisPoints[0].x, -this->freeYAxisPoints[0].y, -this->freeYAxisPoints[0].z);


		//z Axis




		glTranslated(this->freeZAxisPoints[0].x, this->freeZAxisPoints[0].y, this->freeZAxisPoints[0].z);

		glRotated(freeZAxisRotateDegree,
			this->freeZAxisPoints[1].x - this->freeZAxisPoints[0].x,
			this->freeZAxisPoints[1].y - this->freeZAxisPoints[0].y,
			this->freeZAxisPoints[1].z - this->freeZAxisPoints[0].z);


		glTranslated(-this->freeZAxisPoints[0].x, -this->freeZAxisPoints[0].y, -this->freeZAxisPoints[0].z);












		//짐벌락 미해결

		glRotated(this->currentXRotateMatrix[0], this->currentXRotateMatrix[1], this->currentXRotateMatrix[2], this->currentXRotateMatrix[3]);
		glRotated(this->currentYRotateMatrix[0], this->currentYRotateMatrix[1], this->currentYRotateMatrix[2], this->currentYRotateMatrix[3]);
		glRotated(this->currentZRotateMatrix[0], this->currentZRotateMatrix[1], this->currentZRotateMatrix[2], this->currentZRotateMatrix[3]);







		//glTranslated(this->currentTranslateMatrix[12], this->currentTranslateMatrix[13], this->currentTranslateMatrix[14]);


		glScaled(this->currentScaleMatrix[0], this->currentScaleMatrix[1], this->currentScaleMatrix[2]);

	}


	void Polygon0::DrawHexahedron(float size, bool colorRandomOption, bool rainbowColorOption, bool wireOption)
	{
		ApplyMatrix();



		long f, i;
		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ -1.0, 1.0, -1.0 },
		{ 1.0, 1.0, -1.0 },

		{ 1.0, 0, 1.0 },
		{ -1.0, 0, 1.0 },
		{ -1.0, 0, -1.0 },
		{ 1.0, 0, -1.0 },


		};
		const GLfloat cube_vertex_colors[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
		};
		GLint cube_num_faces = 6;
		const short cube_faces[6][4] =
		{
		{ 0, 1, 2, 3 },
		{ 4, 5, 1, 0 },
		{ 4, 5, 6, 7 },
		{ 3, 2, 6, 7 },
		{ 0, 4, 7, 3 },
		{ 1, 2, 6, 5 }
		};

		if (size <= 0)
		{

			size = 2.0;
		}


		if (!wireOption)
		{
			if (colorRandomOption)
			{
				glBegin(GL_QUADS);
				for (f = 0; f < cube_num_faces; f++)
					for (i = 0; i < 4; i++)
					{
						glColor3f(this->color3D.x, this->color3D.y, this->color3D.z);
						glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
					}
				glEnd();

			}

			else if (rainbowColorOption)
			{
				glBegin(GL_QUADS);
				for (f = 0; f < cube_num_faces; f++)
					for (i = 0; i < 4; i++)
					{
						glColor3f(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);
						glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
					}
				glEnd();

			}

			else
			{
				glBegin(GL_QUADS);
				for (f = 0; f < cube_num_faces; f++)
					for (i = 0; i < 4; i++)
					{
						glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
						glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
					}
				glEnd();
			}
		}



		glColor3f(1.0, 0.5, 0.3);
		for (f = 0; f < cube_num_faces; f++)
		{
			glBegin(GL_LINE_LOOP);
			for (i = 0; i < 4; i++)
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
			glEnd();
		}



		// Place base of cube on marker surface.
		//glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
		glDisable(GL_LIGHTING); // Just use colours.



		this->masterMatrixs->glLoadMasterMatrix();

	}
	void Polygon0::DrawHexahedron(InitializeData initializeData)
	{
		ApplyMatrix();





		this->masterMatrixs->glLoadMasterMatrix();
	}


	void Polygon0::DrawTeapot(float size, bool colorRandomOption, bool rainbowColorOption, bool wireOption)
	{
		ApplyMatrix();

		ColorSetting(colorRandomOption, rainbowColorOption);

		if (wireOption)
		{
			glutWireTeapot(size);

		}
		else
		{
			glutSolidTeapot(size);
			glutWireTeapot(size);

		}


		this->masterMatrixs->glLoadMasterMatrix();

	}
	void Polygon0::DrawTeapot(InitializeData initializeData)
	{
		ApplyMatrix();





		this->masterMatrixs->glLoadMasterMatrix();
	}



	void Polygon0::DrawCone(float size, bool colorRandomOption, bool rainbowColorOption, bool wireOption)
	{
		ApplyMatrix();







		glRotated(-90, 1, 0, 0);

		if (wireOption)
		{
			glColor3d(0, 1, 1);

			glutWireCone(size, size, 25, 25);

		}
		else
		{
			ColorSetting(colorRandomOption, rainbowColorOption);
			glutSolidCone(size, size, 25, 25);


		}


		this->masterMatrixs->glLoadMasterMatrix();
	}
	void Polygon0::DrawCone(InitializeData initializeData)
	{
		ApplyMatrix();





		this->masterMatrixs->glLoadMasterMatrix();
	}

	void Polygon0::ColorSetting(bool colorRandomOption, bool rainbowColorOption)
	{
		if (colorRandomOption)
		{

			glColor3f(this->color3D.x, this->color3D.y, this->color3D.z);
		}
		else if (rainbowColorOption)
		{
			glColor3f(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);
		}
		else
		{
			glColor3f(0, 0, 1);
		}

	}

	void Polygon0::DrawWireSphere(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();

		if (colorRandomOption)
		{

			glColor3f(this->color3D.x, this->color3D.y, this->color3D.z);
		}
		else if (rainbowColorOption)
		{
			glColor3f(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);
		}
		else
		{
			glColor3f(0, 0, 1);
		}


		glutWireSphere(size, 25, 25);

		this->masterMatrixs->glLoadMasterMatrix();

	}
	void Polygon0::DrawWireCube(float size, bool colorRandomOption, bool rainbowColorOption)
	{

		long f, i;
		const GLfloat cube_vertices[8][3] =
		{
			{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const GLfloat cube_vertex_colors[8][3] =
		{
			{ 1.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
		};
		GLint cube_num_faces = 6;
		// index list
		const short cube_faces[6][4] =
		{
			{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};

		if (size <= 0)
		{

			size = 2.0;
		}
		this->masterMatrixs->glLoadMasterMatrix();
		glTranslated(this->currentTranslateMatrix[12], this->currentTranslateMatrix[13], this->currentTranslateMatrix[14]);
		glRotated(this->currentXRotateMatrix[0], this->currentXRotateMatrix[1], this->currentXRotateMatrix[2], this->currentXRotateMatrix[3]);
		glRotated(this->currentYRotateMatrix[0], this->currentYRotateMatrix[1], this->currentYRotateMatrix[2], this->currentYRotateMatrix[3]);
		glRotated(this->currentZRotateMatrix[0], this->currentZRotateMatrix[1], this->currentZRotateMatrix[2], this->currentZRotateMatrix[3]);
		glScaled(this->currentScaleMatrix[0], this->currentScaleMatrix[1], this->currentScaleMatrix[2]);




		/*
		glBegin(GL_QUADS);
		for (f = 0; f < cube_num_faces; f++)
			for (i = 0; i < 4; i++) {
				glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
			}
		glEnd();
		*/
		if (colorRandomOption)
		{

			glColor3f(this->color3D.x, this->color3D.y, this->color3D.z);
		}
		else if (rainbowColorOption)
		{
			glColor3f(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);
		}
		else
		{
			glColor3f(1, 1, 0);
		}

		for (f = 0; f < cube_num_faces; f++)
		{
			glBegin(GL_LINE_LOOP);
			for (i = 0; i < 4; i++)
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
			glEnd();
		}



		// Place base of cube on marker surface.
		//glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
		glDisable(GL_LIGHTING); // Just use colours.


		this->masterMatrixs->glLoadMasterMatrix();

	}

	void Polygon0::DrawCube(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();
		long f, i;
		glDisable(GL_LIGHTING);

		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const GLfloat cube_vertex_colors[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
		};
		GLint cube_num_faces = 6;
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};



		if (size <= 0)
		{

			size = 2.0;
		}

		if (colorRandomOption)
		{
			glBegin(GL_QUADS);
			for (f = 0; f < cube_num_faces; f++)
				for (i = 0; i < 4; i++)
				{
					glColor3f(this->color3D.x, this->color3D.y, this->color3D.z);
					glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
				}
			glEnd();

		}

		else if (rainbowColorOption)
		{
			glBegin(GL_QUADS);
			for (f = 0; f < cube_num_faces; f++)
				for (i = 0; i < 4; i++)
				{
					glColor3f(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);
					glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
				}
			glEnd();

		}

		else
		{
			glBegin(GL_QUADS);
			for (f = 0; f < cube_num_faces; f++)
				for (i = 0; i < 4; i++)
				{
					glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
					glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
				}
			glEnd();
		}
		glColor3f(0.0, 0.0, 0.0);
		for (f = 0; f < cube_num_faces; f++)
		{
			glBegin(GL_LINE_LOOP);
			for (i = 0; i < 4; i++)
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * size, cube_vertices[cube_faces[f][i]][1] * size, cube_vertices[cube_faces[f][i]][2] * size);
			glEnd();
		}



		// Place base of cube on marker surface.
		//glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.


		glEnable(GL_LIGHTING);

		this->masterMatrixs->glLoadMasterMatrix();


	}

	void Polygon0::DrawCube(MasterMatrix* masterMatrixs, float fSize, int* list, GLdouble* pMatrix)
	{
		// Colour cube data.

		//float fSize = 50.0f; //이 수치를 조정하면 큐브 사이즈를 바꿀 수 있다.
		long f, i;
		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const GLfloat cube_vertex_colors[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
		};
		GLint cube_num_faces = 6;
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};

		if (fSize <= 0)
		{

			fSize = 2.0;
		}



		if (!*list)
		{
			*list = glGenLists(1);
			glNewList(*list, GL_COMPILE);
			glBegin(GL_QUADS);
			for (f = 0; f < cube_num_faces; f++)
				for (i = 0; i < 4; i++)
				{
					glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
					glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
				}
			glEnd();
			glColor3f(0.0, 0.0, 0.0);
			for (f = 0; f < cube_num_faces; f++)
			{
				glBegin(GL_LINE_LOOP);
				for (i = 0; i < 4; i++)
					glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
				glEnd();
			}
			glEndList();
		}


		// Place base of cube on marker surface.
		//glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
		glDisable(GL_LIGHTING); // Just use colours.
		glCallList(*list); // Draw the cube.

		masterMatrixs->glLoadMasterMatrix();

		//스택행렬도 단위행렬로 해준다.
		glPushMatrix();// Save world coordinate system.
		glPopMatrix(); // Restore world coordinate system.


	}



	void Polygon0::DrawCube(MasterMatrix* masterMatrixs, float fSize)
	{
		// Colour cube data.
		static GLuint polyList = 0;
		//float fSize = 50.0f; //이 수치를 조정하면 큐브 사이즈를 바꿀 수 있다.
		long f, i;
		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const GLfloat cube_vertex_colors[8][3] =
		{
			{ 1.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 1.0, 1.0 },
		{ 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
		};
		GLint cube_num_faces = 6;
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};

		if (fSize <= 0)
		{

			fSize = 2.0;
		}



		if (!polyList)
		{
			polyList = glGenLists(1);
			glNewList(polyList, GL_COMPILE);
			glBegin(GL_QUADS);
			for (f = 0; f < cube_num_faces; f++)
				for (i = 0; i < 4; i++)
				{
					glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
					glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
				}
			glEnd();
			glColor3f(0.0, 0.0, 0.0);
			for (f = 0; f < cube_num_faces; f++)
			{
				glBegin(GL_LINE_LOOP);
				for (i = 0; i < 4; i++)
					glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
				glEnd();
			}
			glEndList();
		}

		//glLoadMatrixf(*cube_vertices);
		//glutWireCube(50);

		//glPushMatrix(); 

									 //glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
		glDisable(GL_LIGHTING); // Just use colours.
		glCallList(polyList); // Draw the cube.

		masterMatrixs->glLoadMasterMatrix();

	}



	void RectangularClock::DrawBlock(MasterMatrix* masterMatrixs, int n, GLdouble size, GLdouble* pMatrix)
	{

		masterMatrixs->glLoadMasterMatrix();

		if (n == 1)
		{

			//1
			glColor4d(this->color4D[0], this->color4D[1], this->color4D[2], this->color4D[3]);
			glTranslated(pMatrix[12], pMatrix[13], pMatrix[14]);
			glScaled(4.0, 1.0, 1.0);
			glTranslated(0, size*5.33, 0);
			glutSolidCube(size);
			if (this->wireOption)
			{
				glColor3d(0, 0, 0);
				glutWireCube(size);
			}

			masterMatrixs->glLoadMasterMatrix();
			glPushMatrix();
			glPopMatrix();

		}
		else if (n == 2)
		{

			//2
			glColor4d(this->color4D[0], this->color4D[1], this->color4D[2], this->color4D[3]);
			glTranslated(pMatrix[12], pMatrix[13], pMatrix[14]);
			glScaled(1.0, 4.0, 1.0);
			glTranslated((size * 2 + size / 2), size * 0.66, 0);
			glutSolidCube(size);
			if (this->wireOption)
			{
				glColor3d(0, 0, 0);
				glutWireCube(size);
			}
			masterMatrixs->glLoadMasterMatrix();
			glPushMatrix();
			glPopMatrix();
		}

		else if (n == 3)
		{

			//3
			glColor4d(this->color4D[0], this->color4D[1], this->color4D[2], this->color4D[3]);
			glTranslated(pMatrix[12], pMatrix[13], pMatrix[14]);
			glScaled(1.0, 4.0, 1.0);
			glTranslated((size * 2 + size / 2), -size * 0.66, 0);
			glutSolidCube(size);
			if (this->wireOption)
			{
				glColor3d(0, 0, 0);
				glutWireCube(size);
			}
			masterMatrixs->glLoadMasterMatrix();
			glPushMatrix();
			glPopMatrix();
		}

		else if (n == 4)
		{

			//4
			glColor4d(this->color4D[0], this->color4D[1], this->color4D[2], this->color4D[3]);
			glTranslated(pMatrix[12], pMatrix[13], pMatrix[14]);
			glScaled(4.0, 1.0, 1.0);
			glTranslated(0, -size * 5.33, 0);
			glutSolidCube(size);
			if (this->wireOption)
			{
				glColor3d(0, 0, 0);
				glutWireCube(size);
			}
			masterMatrixs->glLoadMasterMatrix();
			glPushMatrix();
			glPopMatrix();
		}

		else if (n == 5)
		{

			//5
			glColor4d(this->color4D[0], this->color4D[1], this->color4D[2], this->color4D[3]);
			glTranslated(pMatrix[12], pMatrix[13], pMatrix[14]);
			glScaled(1.0, 4.0, 1.0);
			glTranslated(-(size * 2 + size / 2), -size * 0.66, 0);
			glutSolidCube(size);
			if (this->wireOption)
			{
				glColor3d(0, 0, 0);
				glutWireCube(size);
			}
			masterMatrixs->glLoadMasterMatrix();
			glPushMatrix();
			glPopMatrix();
		}
		else if (n == 6)
		{

			//6
			glColor4d(this->color4D[0], this->color4D[1], this->color4D[2], this->color4D[3]);
			glTranslated(pMatrix[12], pMatrix[13], pMatrix[14]);
			glScaled(1.0, 4.0, 1.0);
			glTranslated(-(size * 2 + size / 2), size * 0.66, 0);
			glutSolidCube(size);
			if (this->wireOption)
			{
				glColor3d(0, 0, 0);
				glutWireCube(size);
			}
			masterMatrixs->glLoadMasterMatrix();
			glPushMatrix();
			glPopMatrix();

		}
		else if (n == 7)
		{

			//7
			glColor4d(this->color4D[0], this->color4D[1], this->color4D[2], this->color4D[3]);
			glTranslated(pMatrix[12], pMatrix[13], pMatrix[14]);
			glScaled(4.0, 1.0, 1.0);
			glTranslated(0, 0, 0);
			glutSolidCube(size);
			if (this->wireOption)
			{
				glColor3d(0, 0, 0);
				glutWireCube(size);
			}
			masterMatrixs->glLoadMasterMatrix();
			glPushMatrix();
			glPopMatrix();
		}

	}
	/*
	void RectangularClock::RectangularClockNum(int n, GLdouble size)
	{

		if (size < 0) {
			size = 1.0;
		}
		if (n == 8) {
			glLoadIdentity();
			glPushMatrix();
			glPopMatrix();

			glScaled(1.0, 4.0, 1.0);
			glTranslated(-(size * 2 + size / 2), size * 0.66, 0);
			glutSolidCube(size);
			glLoadIdentity();
			glPushMatrix();
			glPopMatrix();


			glScaled(4.0, 1.0, 1.0);
			glTranslated(0, 0, 0);
			glutSolidCube(size);
			glLoadIdentity();
			glPushMatrix();
			glPopMatrix();


			glScaled(1.0, 4.0, 1.0);
			glTranslated(-(size * 2 + size / 2), -size * 0.66, 0);
			glutSolidCube(size);
			glLoadIdentity();
			glPushMatrix();
			glPopMatrix();


			glScaled(1.0, 4.0, 1.0);
			glTranslated((size * 2 + size / 2), -size * 0.66, 0);
			glutSolidCube(size);
			glLoadIdentity();
			glPushMatrix();
			glPopMatrix();


			glScaled(1.0, 4.0, 1.0);
			glTranslated((size * 2 + size / 2), size * 0.66, 0);
			glutSolidCube(size);
			glLoadIdentity();
			glPushMatrix();
			glPopMatrix();


			glScaled(4.0, 1.0, 1.0);
			glTranslated(0, size*5.33, 0);
			glutSolidCube(size);
			glLoadIdentity();
			glPushMatrix();
			glPopMatrix();

			glScaled(4.0, 1.0, 1.0);
			glTranslated(0, -size * 5.33, 0);
			glutSolidCube(size);
			glLoadIdentity();
			glPushMatrix();
			glPopMatrix();
		}

	}
	*/
	void RectangularClock::RectangularClockNum(MasterMatrix* masterMatrixs, int n, GLdouble size, GLdouble* pMatrix, bool wireOption, GLdouble* color4D)
	{

		/*
			 -    1
			| |  6,2
			 _    7
			| |  5,3
			 _    4

		*/
		glDisable(GL_LIGHTING);
		this->wireOption = wireOption;
		this->color4D = color4D;

		if (size < 0)
		{
			size = 1.0;
		}

		if (n == 0)
		{

			for (int i = 0; i < 6; ++i)
			{
				DrawBlock(masterMatrixs, i + 1, size, pMatrix);
			}

		}

		else if (n == 1)
		{

			DrawBlock(masterMatrixs, 2, size, pMatrix);
			DrawBlock(masterMatrixs, 3, size, pMatrix);
		}

		else if (n == 2)
		{

			DrawBlock(masterMatrixs, 1, size, pMatrix);
			DrawBlock(masterMatrixs, 2, size, pMatrix);
			DrawBlock(masterMatrixs, 4, size, pMatrix);
			DrawBlock(masterMatrixs, 5, size, pMatrix);
			DrawBlock(masterMatrixs, 7, size, pMatrix);

		}

		else if (n == 3)
		{


			DrawBlock(masterMatrixs, 1, size, pMatrix);
			DrawBlock(masterMatrixs, 2, size, pMatrix);
			DrawBlock(masterMatrixs, 3, size, pMatrix);
			DrawBlock(masterMatrixs, 4, size, pMatrix);
			DrawBlock(masterMatrixs, 7, size, pMatrix);

		}
		else if (n == 4)
		{

			DrawBlock(masterMatrixs, 2, size, pMatrix);
			DrawBlock(masterMatrixs, 3, size, pMatrix);
			DrawBlock(masterMatrixs, 6, size, pMatrix);
			DrawBlock(masterMatrixs, 7, size, pMatrix);
		}
		else if (n == 5)
		{
			DrawBlock(masterMatrixs, 1, size, pMatrix);
			DrawBlock(masterMatrixs, 3, size, pMatrix);
			DrawBlock(masterMatrixs, 4, size, pMatrix);
			DrawBlock(masterMatrixs, 6, size, pMatrix);
			DrawBlock(masterMatrixs, 7, size, pMatrix);

		}
		else if (n == 6)
		{
			DrawBlock(masterMatrixs, 1, size, pMatrix);
			DrawBlock(masterMatrixs, 3, size, pMatrix);
			DrawBlock(masterMatrixs, 4, size, pMatrix);
			DrawBlock(masterMatrixs, 5, size, pMatrix);
			DrawBlock(masterMatrixs, 6, size, pMatrix);
			DrawBlock(masterMatrixs, 7, size, pMatrix);
		}

		else if (n == 7)
		{


			DrawBlock(masterMatrixs, 1, size, pMatrix);
			DrawBlock(masterMatrixs, 2, size, pMatrix);
			DrawBlock(masterMatrixs, 3, size, pMatrix);
			DrawBlock(masterMatrixs, 6, size, pMatrix);
		}

		else if (n == 8)
		{


			for (int i = 0; i < 7; ++i)
			{

				DrawBlock(masterMatrixs, i + 1, size, pMatrix);
			}

		}

		else if (n == 9)
		{

			DrawBlock(masterMatrixs, 1, size, pMatrix);
			DrawBlock(masterMatrixs, 2, size, pMatrix);
			DrawBlock(masterMatrixs, 3, size, pMatrix);
			DrawBlock(masterMatrixs, 4, size, pMatrix);
			DrawBlock(masterMatrixs, 6, size, pMatrix);
			DrawBlock(masterMatrixs, 7, size, pMatrix);
		}


		glEnable(GL_LIGHTING);
	}





	//DraggingLine : Polygon0 Def

	void DraggingLine::SetPosition(GLVector3 startPoint, GLVector3 endPoint)
	{



		this->startPoint = startPoint;
		this->endPoint = endPoint;



	}

	void DraggingLine::SetPosition(GLVector3 endPoint)
	{




		this->endPoint = endPoint;



	}

	void DraggingLine::Enable()
	{

		this->onMyMouse = true;
	}

	void DraggingLine::Disable()
	{

		this->onMyMouse = false;



	}

	void DraggingLine::DrawDraggingLine(bool colorRandomOption, bool rainbowColorOption)
	{


		ApplyMatrix();

		if (this->onMyMouse)
		{


			glColor3d(1.0, 0.2, 0.2);


			glBegin(GL_LINES);


			glVertex3d(this->startPoint.x, this->startPoint.y, this->Position().z);
			glVertex3d(this->endPoint.x, this->endPoint.y, this->Position().z);




			glEnd();
		}

		this->masterMatrixs->glLoadMasterMatrix();

	}

	void GLAnimator::ScalingAnimation(Polygon0* objectPointer)
	{
		static bool first = false;



	}
	void GLAnimator::AlphaBlendingAnimation(Polygon0* objectPointer)
	{

		if (!this->temp1)
		{
			return;
		}

		static bool first = false;
		static AnimatorParameter* asdd = new AnimatorParameter;



		if (!first)
		{

			asdd->keyFrame = 30;
			asdd->loop = false;
			asdd->animationKind = AlphaBlending;
			asdd->animationActivate = true;
			asdd->currentFrame = 0;

			this->asd->push_back(*asdd);
			first = true;

			//asd->begin();



		}


		if (asdd->animationActivate)
		{


			objectPointer->alpha -= 1.0 / asdd->keyFrame;

			asdd->currentFrame += 1;
			if (asdd->currentFrame >= asdd->keyFrame)
			{

				first = false;
				asdd->animationActivate = false;
				this->temp1 = false;
			}


		}








	}


	void Greed::FillTriangle()
	{

		if (this->greedData.pointer < 48)
		{

			this->greedData.greed[this->greedData.pointer++] = true;
		}

	}


	void Greed::DrawGreed()
	{
		ApplyMatrix();



		for (int i = 0; i < this->greedData.height / this->greedData.size; ++i)
		{
			for (int j = 0; j < this->greedData.width / this->greedData.size; ++j)
			{

				glColor4d(1, 0, 0, 1);
				glBegin(GL_LINE_LOOP);

				glVertex2d(j * this->greedData.size, i * this->greedData.size);
				glVertex2d((j + 1) * this->greedData.size, i * this->greedData.size);
				glVertex2d((j + 1) * this->greedData.size, (i + 1) * this->greedData.size);
				glVertex2d(j * this->greedData.size, (i + 1) * this->greedData.size);

				glEnd();
				//짝
				if (this->greedData.greed[2 * (j + (i * (this->greedData.width / this->greedData.size)))])
				{



					glBegin(GL_TRIANGLES);
					glColor4d((rand() % ((rand() % 11) + 1)) / 10.0, (rand() % ((rand() % 11) + 1)) / 10.0, (rand() % ((rand() % 11) + 1)) / 10.0, this->alpha);
					glVertex3d(j * this->greedData.size, i * this->greedData.size, 0);
					glColor4d((rand() % 11) / 10.0, (rand() % 11) / 10.0, (rand() % 11) / 10.0, this->alpha);
					glVertex3d((j + 1) * this->greedData.size, i * this->greedData.size, 0);
					glColor4d((rand() % ((rand() % 11) + 1)) / 10.0, (rand() % ((rand() % 11) + 1)) / 10.0, (rand() % ((rand() % 11) + 1)) / 10.0, this->alpha);
					glVertex3d(j * this->greedData.size, (i + 1) * this->greedData.size, 0);
					glEnd();
				}
				if (this->greedData.greed[2 * (j + (i * (this->greedData.width / this->greedData.size))) + 1])
				{

					glBegin(GL_TRIANGLES);
					glColor4d((rand() % 11) / 10.0, (rand() % 11) / 10.0, (rand() % 11) / 10.0, this->alpha);
					glVertex3d((j + 1) * this->greedData.size, i * this->greedData.size, 0);
					glColor4d((rand() % 11) / 10.0, (rand() % 11) / 10.0, (rand() % 11) / 10.0, this->alpha);
					glVertex3d((j + 1) * this->greedData.size, (i + 1) * this->greedData.size, 0);
					glColor4d((rand() % 11) / 10.0, (rand() % 11) / 10.0, (rand() % 11) / 10.0, this->alpha);
					glVertex3d(j * this->greedData.size, (i + 1) * this->greedData.size, 0);
					glEnd();


				}







			}

		}






		this->masterMatrixs->glLoadMasterMatrix();

	}

	//class RunningMachine
	void RunningMachine::DrawRunningMachine(float size, bool colorRandomOption, bool rainbowColorOption)
	{

		ApplyMatrix();

		static int width = 10;
		static int rotation = 0;
		static double temp[3]{ 0 , 0 , 0 };

		for (int i = 0; i < 3; ++i)
		{
			temp[i] = currentTranslateMatrix[12 + i];
		}


		glPushMatrix();
		glColor4d(0, 1.0, 0, this->alpha);
		glScaled(4, 0.5, 1);
		glRotated(rotation--, 0, 0, 1);
		rotation = rotation % 360;
		for (int i = 0; i < width; ++i)
		{
			glutWireTorus(1 * size, 2.5 * size, 25, 25);
			glTranslated(0, 0, 1 * size);

		}
		glPopMatrix();

		glPushMatrix();
		//size * (width + 2)

		this->Translate(0, -2 * size, size * (width / 2 - 1));


		this->currentScaleMatrix[0] = 2.8;
		this->currentScaleMatrix[1] = 5;
		this->currentScaleMatrix[2] = 1.5;


		this->DrawBoard(size * (width / 2), false, false);


		this->Translate(0, 2 * size, -size * (width / 2 - 1));

		this->ClearCurrentScale();




		this->currentScaleMatrix[1] = 8;
		this->Translate(-380, 0, -50);


		this->DrawHexahedron(size, false, false, false);



		this->ClearCurrentScale();
		this->Translate(380, 0, 50);




		this->currentScaleMatrix[1] = 8;
		this->Translate(-380, 0, 290);


		this->DrawHexahedron(size, false, false, false);



		this->ClearCurrentScale();
		this->Translate(380, 0, -290);


		this->currentScaleMatrix[0] = 0.2;

		this->Translate(-350, 200, 100);
		this->DrawBoard(300, false, false);

		this->Translate(350, -200, -100);

		this->ClearCurrentScale();






		this->masterMatrixs->glLoadMasterMatrix();
	}


	void RunningMachine::Generate()
	{


	}







	//class RunningPeople
	void RunningPeople::DrawingRunningPeople(float size, bool colorRandomOption, bool rainbowColorOption)
	{

		ApplyMatrix();
		static int keyFrame = 20;
		static int currentFrame = 0;
		static int degree = 0;
		static int dir = 5;



		this->Scale(0.5, 3, 1);
		this->Translate(0, 100, 0);
		this->DrawHexahedron(size, false, false, false);

		this->Translate(0, -100, 0);
		this->ClearCurrentScale();



		this->SetFreeRotateZAxis(GLVector3(0, size * 2, 0), GLVector3(0, size * 2, 1));
		this->FreeAxisRotate2(0, 0, degree);
		degree += dir;
		if (degree > 80 || degree < -80)
		{
			dir *= -1;
		}

		this->Scale(0.5, 2, 0.5);
		this->Translate(0, 0, 50);
		this->DrawHexahedron(size, false, false, false);
		this->freeZAxisRotateDegree = 0;


		this->FreeAxisRotate2(0, 0, -degree);
		this->Translate(0, 0, -100);
		this->DrawHexahedron(size, false, false, false);



		this->freeZAxisRotateDegree = 0;




		this->Translate(0, 0, 50);
		this->ClearCurrentScale();



		this->masterMatrixs->glLoadMasterMatrix();
	}



	//class ChulbongPeople
	void ChulbongPeople::DrawingChulbongPeople(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();
		static int degree = 0;
		static int dir = 5;


		this->Translate(0, size * 10, 0);



		//철봉
		this->Scale(0.5, 0.5, 4);
		this->DrawCube(size, colorRandomOption, rainbowColorOption);
		this->ClearCurrentScale();



		this->Scale(0.5, 10, 0.5);
		this->Translate(0, -size * 9.5, -size * 4);
		this->DrawCube(size, colorRandomOption, rainbowColorOption);
		this->Translate(0, size * 9.5, size * 4);
		this->ClearCurrentScale();


		this->Scale(0.5, 10, 0.5);
		this->Translate(0, -size * 9.5, size * 4);
		this->DrawCube(size, colorRandomOption, rainbowColorOption);
		this->Translate(0, size * 9.5, -size * 4);
		this->ClearCurrentScale();


		this->SetFreeRotateZAxis(GLVector3(0, size * 2.5, 0), GLVector3(0, size * 2.5, 1));
		this->FreeAxisRotate2(0, 0, degree);
		degree += dir;
		degree = degree % 360;

		//두팔
		this->Scale(0.5, 3, 0.5);
		this->Translate(0, -size * 2.5, -size * 2);
		this->DrawCube(size, false, false);
		this->Translate(0, 0, size * 4);
		this->DrawCube(size, false, false);
		this->Translate(0, size * 2.5, -size * 2);
		this->ClearCurrentScale();



		//대가리
		this->Translate(0, -size * 3, 0);
		this->DrawWireSphere(size, false, false);
		this->Translate(0, size * 3, 0);



		this->SetFreeRotateZAxis(GLVector3(0, size * 7, 0), GLVector3(0, size * 7, 1));



		//몸뚱이
		this->Scale(0.5, 3, 2);
		this->Translate(0, -size * 7, 0);
		this->DrawCube(size, false, false);
		this->Translate(0, size * 7, 0);
		this->ClearCurrentScale();


		this->freeZAxisRotateDegree = 0;






		this->Translate(0, -size * 10, 0);

		this->masterMatrixs->glLoadMasterMatrix();



	}




	//class BenchPressPeople
	void BenchPressPeople::DrawingBenchPressPeople(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();


		static int degree = 0;
		static int degree2 = 0;
		static int dir = -1;
		static int dir2 = 1;

		//직육면체는 총 13개 필요
		//거치대 3개
		//벤치봉 1개
		//벤치봉에 끼울 토러스 4개
		//사람 9개(팔4 다리4 몸1)
		//대가리 구체 1개



		//거치대(등받이)
		this->Scale(2.5, 1, 5);
		this->DrawCube(size, false, false);
		this->ClearCurrentScale();
		//거치대(기둥1,2)
		this->Scale(0.5, 3, 0.5);
		this->Translate(-2.5*size, 2 * size, -3 * size);
		this->DrawCube(size, false, false);
		this->Translate(5 * size, 0, 0);
		this->DrawCube(size, false, false);
		this->Translate(-2.5 * size, -2 * size, 3 * size);
		this->ClearCurrentScale();

		//벤치봉

		this->Translate(0, degree2 - size * 2.8, 0);

		this->Scale(6, 0.5, 0.5);
		this->Translate(0, 6 * size, 0);
		this->DrawCube(size, false, false);
		this->ClearCurrentScale();
		this->Translate(0, -6 * size, 0);

		//토러스4개
		this->Rotate2(90, 0, 1, 0, 1);
		this->Translate(-size * 4, size * 6, 0);
		this->DrawWireTorus(size, false, false);

		this->Scale(1, 0.7, 1);
		this->Translate(-size * 1.5, 0, 0);
		this->DrawWireTorus(size, false, false);
		this->ClearCurrentScale();


		this->Translate(size * 9.5, 0, 0);
		this->DrawWireTorus(size, false, false);


		this->Scale(1, 0.7, 1);
		this->Translate(size * 1.5, 0, 0);
		this->DrawWireTorus(size, false, false);
		this->ClearCurrentScale();


		this->Rotate2(-90, 0, 1, 0, 1);
		this->ClearCurrentScale();
		this->Translate(-size * 5.5, -size * 6, 0);


		this->Translate(0, -degree2 + size * 2.8, 0);


		//사람몸
		this->Scale(1, 0.5, 2.5);
		this->Translate(0, 1.5*size, 0.5*size);
		this->DrawCube(size, false, false);
		this->Translate(0, -1.5*size, -0.5*size);
		this->ClearCurrentScale();





		//사람다리
		this->Scale(0.25, 0.5, 2);
		this->Translate(-size, 1.5*size, size * 5);
		this->DrawCube(size, false, false);

		this->Translate(2 * size, 0, 0);
		this->DrawCube(size, false, false);

		this->ClearCurrentScale();
		this->Translate(-size, -1.5*size, -size * 5);




		//사람팔(어깨)
		this->SetFreeRotateZAxis(GLVector3(size, 0, 0), GLVector3(size, 0, 1));
		this->FreeAxisRotate2(0, 0, degree);
		degree += dir;
		degree = degree % 360;

		if (degree >= 0 || degree <= -90)
		{
			dir *= -1;
		}


		this->Scale(1, 0.25, 0.5);
		this->Translate(-2.3*size, 1.5*size, 0);
		this->DrawCube(size, false, false);

		this->freeZAxisRotateDegree = 0;


		this->SetFreeRotateZAxis(GLVector3(-size, 0, 0), GLVector3(-size, 0, 1));
		this->FreeAxisRotate2(0, 0, degree2);
		degree2 += dir2;
		degree2 = degree2 % 360;

		if (degree2 <= 0 || degree2 >= 90)
		{
			dir2 *= -1;
		}

		this->Translate(4.6 * size, 0, 0);
		this->DrawCube(size, false, false);

		this->freeZAxisRotateDegree = 0;


		this->ClearCurrentScale();
		this->Translate(-2.3*size, -1.5*size, 0);






		//사람팔(팔목)




		this->Scale(0.25, 1, 0.5);



		this->SetFreeRotateZAxis(GLVector3(0, size, 0), GLVector3(0, size, 1));
		this->FreeAxisRotate2(0, 0, -degree * 0.9 - 90 * 0.9);

		this->Translate(-1.3*size, 1.5 * size, 0);
		this->Translate(0, -(1 * size * degree) / 30, 0);


		this->DrawCube(size, false, false);
		this->freeZAxisRotateDegree = 0;
		this->Translate(0, (1 * size * degree) / 30, 0);



		this->SetFreeRotateZAxis(GLVector3(0, size, 0), GLVector3(0, size, 1));
		this->FreeAxisRotate2(0, 0, -degree2 * 0.9 + 90 * 0.9);



		this->Translate(2.6 * size, 0, 0);
		this->Translate(0, (1 * size * degree2) / 30, 0);
		this->DrawCube(size, false, false);
		this->freeZAxisRotateDegree = 0;
		this->Translate(0, -(1 * size * degree2) / 30, 0);

		this->ClearCurrentScale();
		this->Translate(-1.3*size, -1.5 * size, 0);





		this->masterMatrixs->glLoadMasterMatrix();
	}





	//class GymTree
	void GymTree::DrawingGymTree(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();

		static int keyFrame = 3600;
		static int currentFrame = 0;


		static double scaling = 0;
		static double increase = 0.01 / (keyFrame / 120);

		this->size = size;

		if (currentFrame < keyFrame / 2)
		{
			increase = abs(increase);
		}
		else if (currentFrame < keyFrame)
		{


			increase = -abs(increase);

		}
		else
		{
			currentFrame = 0;
			scaling = 0;
		}

		this->Scale(1 + scaling, 1 + scaling, 1 + scaling);
		currentFrame++;
		scaling += increase;

		this->Translate(0, size * 6, 0);
		this->DrawWireSphere(size * 2, false, true);
		this->Translate(0, -size * 6, 0);
		this->ClearCurrentScale();

		this->Scale(1, 4, 1);
		this->DrawHexahedron(size, false, false, false);
		this->ClearCurrentScale();



		this->masterMatrixs->glLoadMasterMatrix();
	}


	//class Star
	void Star::DrawingStar(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();


		glColor4d(this->color4D.x, this->color4D.y, this->color4D.z, this->color4D.w);
		glBegin(GL_TRIANGLES);

		/*
		glVertex3d(0, 5, 0);
		glVertex3d(-4.75, 1.54, 0);
		glVertex3d(-2.93, -4.04, 0);
		glVertex3d(2.93, -4.04, 0);
		glVertex3d(4.75, 1.54, 0);
		*/
		/*
		this->Scale(10, 10, 10);
		glVertex3d(0, 5, 0);
		glVertex3d(-2.93, -4.04, 0);
		glVertex3d(4.75, 1.54, 0);
		glVertex3d(-4.75, 1.54, 0);
		glVertex3d(2.93, -4.04, 0);
		*/
		glVertex3d(0, 5 * size, 0);
		glVertex3d(-4.33 * size, -2.5 * size, 0);
		glVertex3d(4.315 * size, -1.47 * size, 0);

		glEnd();



		glTranslated(0, 1 * size, 0);

		glBegin(GL_TRIANGLES);
		glVertex3d(0, -5 * size, 0);
		glVertex3d(4.33 * size, 2.5 * size, 0);
		glVertex3d(-4.315 * size, 1.47 * size, 0);


		glEnd();



		this->masterMatrixs->glLoadMasterMatrix();
	}

	//class Plane

	void Plane::Set(bool axisRotation)
	{

	}
	void Plane::DrawingPlane(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();


		this->SetFreeRotateYAxis(GLVector3(0, size, 0), GLVector3(0, size + 1, 0));
		this->FreeAxisRotate2(0, 1, 0);

		//몸체

		this->Scale(1, 0.5, 3);
		this->DrawCube(size, colorRandomOption, rainbowColorOption);
		this->ClearCurrentScale();


		//날개(왼쪽)
		this->Translate(-2.5 * size, 0, 0);
		this->Scale(2.5, 0.25, 0.5);
		this->DrawCube(size, false, false);


		this->Translate(2.5 * size, 0, 0);
		this->ClearCurrentScale();

		//날개(오른쪽)
		this->Translate(2.5 * size, 0, 0);
		this->Scale(2.5, 0.25, 0.5);
		this->DrawCube(size, false, false);


		this->Translate(-2.5 * size, 0, 0);
		this->ClearCurrentScale();


		//프로펠러
		this->Translate(0, 0, -3 * size);
		this->Rotate2(270, 1, 0, 0, 0);
		this->DrawCone(size, false, false, false);
		this->Rotate2(-270, 1, 0, 0, 0);

		this->Rotate2(90, 0, 1, 0, 1);

		this->Scale(2, 0.25, 0.25);
		this->DrawCube(size, false, false);


		this->ClearCurrentScale();
		this->Rotate2(-90, 0, 1, 0, 1);

		this->Translate(0, 0, 3 * size);


		this->masterMatrixs->glLoadMasterMatrix();
	}

	//class MyAnimatorParameter
	void MyAnimatorParameter::InitializeAnimatorParameter(int keyFrame, int currentFrame, bool animationActivate, bool loop)
	{
		this->animatorParameter.animationActivate = animationActivate;
		this->animatorParameter.currentFrame = currentFrame;
		this->animatorParameter.keyFrame = keyFrame;
		this->animatorParameter.loop = loop;

	}



	//class OpenCube
	void OpenCube::OpenFront()
	{

		if (this->test[0])
		{


			for (int i = 0; i < 6; ++i)
			{
				faceFluid[i] = false;
			}

			faceFluid[0] = true;




			//this->myAnimatorParameter.animatorParameter.
			if (this->myAnimatorParameter[0].animatorParameter.animationActivate)
			{
				//3,2,1,0

				//각속도 90도
				printf("ㅋ");


				//hint:
				//this->cube_vertices_fluid[0][0] = -1 + 2 * cos(PI/1.5);
				//this->cube_vertices_fluid[0][2] = 1 + 2 * sin(PI / 1.5);
				//this->cube_vertices_fluid[1][0] = -1 + 2 * cos(PI / 1.5);
				//this->cube_vertices_fluid[1][2] = 1 + 2 * sin(PI / 1.5);


				this->cube_vertices_fluid[0][0] = -1 + 2 * cos((PI / 180) * this->myAnimatorParameter[0].animatorParameter.currentFrame);
				this->cube_vertices_fluid[0][2] = 1 + 2 * sin((PI / 180) *  this->myAnimatorParameter[0].animatorParameter.currentFrame);
				this->cube_vertices_fluid[1][0] = -1 + 2 * cos((PI / 180) *  this->myAnimatorParameter[0].animatorParameter.currentFrame);
				this->cube_vertices_fluid[1][2] = 1 + 2 * sin((PI / 180) *  this->myAnimatorParameter[0].animatorParameter.currentFrame);


				this->myAnimatorParameter[0].animatorParameter.currentFrame += 1;
				if (this->myAnimatorParameter[0].animatorParameter.currentFrame >= this->myAnimatorParameter[0].animatorParameter.keyFrame)
				{
					this->myAnimatorParameter[0].animatorParameter.animationActivate = false;

					this->test[0] = false;

					this->myAnimatorParameter[1].animatorParameter.animationActivate = true;
					this->test[2] = true;
				}

				//printf("%d\n", this->myAnimatorParameter.animatorParameter.currentFrame);
			}



		}
	}




	void OpenCube::CloseFront()
	{

		if (this->test[1])
		{
			for (int i = 0; i < 6; ++i)
			{
				faceFluid[i] = false;
			}

			faceFluid[0] = true;


			//this->myAnimatorParameter.animatorParameter.
			if (this->myAnimatorParameter[0].animatorParameter.animationActivate)
			{
				//3,2,1,0

				//각속도 90도
				printf("ㅋ");


				//hint:
				//this->cube_vertices_fluid[0][0] = -1 + 2 * cos(PI/1.5);
				//this->cube_vertices_fluid[0][2] = 1 + 2 * sin(PI / 1.5);
				//this->cube_vertices_fluid[1][0] = -1 + 2 * cos(PI / 1.5);
				//this->cube_vertices_fluid[1][2] = 1 + 2 * sin(PI / 1.5);




				this->cube_vertices_fluid[0][0] = -1 + 2 * cos((PI / 180) * this->myAnimatorParameter[0].animatorParameter.currentFrame);
				this->cube_vertices_fluid[0][2] = 1 + 2 * sin((PI / 180) *  this->myAnimatorParameter[0].animatorParameter.currentFrame);
				this->cube_vertices_fluid[1][0] = -1 + 2 * cos((PI / 180) *  this->myAnimatorParameter[0].animatorParameter.currentFrame);
				this->cube_vertices_fluid[1][2] = 1 + 2 * sin((PI / 180) *  this->myAnimatorParameter[0].animatorParameter.currentFrame);




				this->myAnimatorParameter[0].animatorParameter.currentFrame -= 1;
				if (this->myAnimatorParameter[0].animatorParameter.currentFrame < 0)
				{
					this->myAnimatorParameter[0].animatorParameter.animationActivate = false;

					this->test[1] = false;

				}



				//printf("%d\n", this->myAnimatorParameter.animatorParameter.currentFrame);





			}



		}

	}




	void OpenCube::RollFront()
	{
		if (this->test[2])
		{


			//this->myAnimatorParameter.animatorParameter.
			if (this->myAnimatorParameter[1].animatorParameter.animationActivate)
			{



				this->myAnimatorParameter[1].animatorParameter.currentFrame += 1;
				if (this->myAnimatorParameter[1].animatorParameter.currentFrame >= this->myAnimatorParameter[1].animatorParameter.keyFrame)
				{
					this->myAnimatorParameter[1].animatorParameter.animationActivate = false;
					this->test[2] = false;

				}

				//printf("%d\n", this->myAnimatorParameter.animatorParameter.currentFrame);
			}



		}

	}
	void OpenCube::RollBackFront()
	{
		if (this->test[3])
		{


			//this->myAnimatorParameter.animatorParameter.
			if (this->myAnimatorParameter[1].animatorParameter.animationActivate)
			{



				this->myAnimatorParameter[1].animatorParameter.currentFrame -= 1;
				if (this->myAnimatorParameter[1].animatorParameter.currentFrame < 0)
				{
					this->myAnimatorParameter[1].animatorParameter.animationActivate = false;
					this->test[3] = false;

					this->test[1] = true;
					this->myAnimatorParameter[0].animatorParameter.animationActivate = true;


				}

				//printf("%d\n", this->myAnimatorParameter.animatorParameter.currentFrame);
			}



		}

	}



	void OpenCube::OpenTop()
	{
		if (this->test[4])
		{
			for (int i = 0; i < 6; ++i)
			{
				faceFluid[i] = false;
			}

			faceFluid[3] = true;

			//this->myAnimatorParameter.animatorParameter.
			if (this->myAnimatorParameter[2].animatorParameter.animationActivate)
			{
				//3,2,1,0

				//각속도 90도
				printf("ㅋ");


				//hint:
				//this->cube_vertices_fluid[0][0] = -1 + 2 * cos(PI/1.5);
				//this->cube_vertices_fluid[0][2] = 1 + 2 * sin(PI / 1.5);
				//this->cube_vertices_fluid[1][0] = -1 + 2 * cos(PI / 1.5);
				//this->cube_vertices_fluid[1][2] = 1 + 2 * sin(PI / 1.5);


				this->cube_vertices_fluid[0][0] = -1 + 2 * cos((PI / 180) * this->myAnimatorParameter[2].animatorParameter.currentFrame);
				this->cube_vertices_fluid[0][1] = 1 + 2 * sin((PI / 180) *  this->myAnimatorParameter[2].animatorParameter.currentFrame);
				this->cube_vertices_fluid[4][0] = -1 + 2 * cos((PI / 180) *  this->myAnimatorParameter[2].animatorParameter.currentFrame);
				this->cube_vertices_fluid[4][1] = 1 + 2 * sin((PI / 180) *  this->myAnimatorParameter[2].animatorParameter.currentFrame);


				this->myAnimatorParameter[2].animatorParameter.currentFrame += 1;
				if (this->myAnimatorParameter[2].animatorParameter.currentFrame >= this->myAnimatorParameter[2].animatorParameter.keyFrame)
				{
					this->myAnimatorParameter[2].animatorParameter.animationActivate = false;

					this->test[4] = false;

					this->myAnimatorParameter[3].animatorParameter.animationActivate = true;
					this->test[5] = true;
				}

				//printf("%d\n", this->myAnimatorParameter.animatorParameter.currentFrame);
			}



		}

	}
	void OpenCube::CloseTop()
	{
		if (this->test[5])
		{
			for (int i = 0; i < 6; ++i)
			{
				faceFluid[i] = false;
			}

			faceFluid[3] = true;

			//this->myAnimatorParameter.animatorParameter.
			if (this->myAnimatorParameter[2].animatorParameter.animationActivate)
			{
				//3,2,1,0

				//각속도 90도
				printf("ㅋ");


				//hint:
				//this->cube_vertices_fluid[0][0] = -1 + 2 * cos(PI/1.5);
				//this->cube_vertices_fluid[0][2] = 1 + 2 * sin(PI / 1.5);
				//this->cube_vertices_fluid[1][0] = -1 + 2 * cos(PI / 1.5);
				//this->cube_vertices_fluid[1][2] = 1 + 2 * sin(PI / 1.5);


				this->cube_vertices_fluid[0][0] = -1 + 2 * cos((PI / 180) * this->myAnimatorParameter[2].animatorParameter.currentFrame);
				this->cube_vertices_fluid[0][1] = 1 + 2 * sin((PI / 180) *  this->myAnimatorParameter[2].animatorParameter.currentFrame);
				this->cube_vertices_fluid[4][0] = -1 + 2 * cos((PI / 180) *  this->myAnimatorParameter[2].animatorParameter.currentFrame);
				this->cube_vertices_fluid[4][1] = 1 + 2 * sin((PI / 180) *  this->myAnimatorParameter[2].animatorParameter.currentFrame);


				this->myAnimatorParameter[2].animatorParameter.currentFrame -= 1;
				if (this->myAnimatorParameter[2].animatorParameter.currentFrame < 0)
				{
					this->myAnimatorParameter[2].animatorParameter.animationActivate = false;

					this->test[5] = false;


				}

				//printf("%d\n", this->myAnimatorParameter.animatorParameter.currentFrame);
			}



		}

	}

	void OpenCube::SpringRise()
	{


	}

	void OpenCube::SpringContract()
	{


	}


	void OpenCube::DrawingOpenCube(float size, bool colorRandomOption, bool rainbowColorOption)
	{
		ApplyMatrix();

		this->OpenFront();

		this->RollFront();

		this->CloseFront();

		this->RollBackFront();



		this->OpenTop();



		this->CloseTop();




		this->size = size;


		static int keyFrame = 150;

		static int currentFrame = 0;

		static int speed = 3;








		if (size <= 0)
		{

			size = 2.0;
		}

		if (colorRandomOption)
		{

			glBegin(GL_QUADS);
			for (int f = 0; f < cube_num_faces; f++)
				if (this->faceFluid[f] == false)
				{
					for (int i = 0; i < 4; i++)
					{
						glColor3f(this->color3D.x, this->color3D.y, this->color3D.z);
						glVertex3f(cube_vertices[cube_faces[f][i]][0] * this->size, cube_vertices[cube_faces[f][i]][1] * this->size, cube_vertices[cube_faces[f][i]][2] * this->size);

					}
				}

				else
					for (int i = 0; i < 4; i++)
					{
						glColor3f(this->color3D.x, this->color3D.y, this->color3D.z);
						glVertex3f(cube_vertices_fluid[cube_faces[f][i]][0] * this->size, cube_vertices_fluid[cube_faces[f][i]][1] * this->size, cube_vertices_fluid[cube_faces[f][i]][2] * this->size);

					}

			glEnd();

		}

		else if (rainbowColorOption)
		{
			glBegin(GL_QUADS);
			for (int f = 0; f < cube_num_faces; f++)
				if (this->faceFluid[f] == false)
				{
					for (int i = 0; i < 4; i++)
					{
						glColor3f(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);
						glVertex3f(cube_vertices[cube_faces[f][i]][0] * this->size, cube_vertices[cube_faces[f][i]][1] * this->size, cube_vertices[cube_faces[f][i]][2] * this->size);
					}
				}
				else
				{
					for (int i = 0; i < 4; i++)
					{
						glColor3f(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);
						glVertex3f(cube_vertices_fluid[cube_faces[f][i]][0] * this->size, cube_vertices_fluid[cube_faces[f][i]][1] * this->size, cube_vertices_fluid[cube_faces[f][i]][2] * this->size);
					}

				}


			glEnd();

		}

		else
		{
			glBegin(GL_QUADS);
			for (int f = 0; f < cube_num_faces; f++)
				if (this->faceFluid[f] == false)
				{
					for (int i = 0; i < 4; i++)
					{
						glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
						glVertex3f(cube_vertices[cube_faces[f][i]][0] * this->size, cube_vertices[cube_faces[f][i]][1] * this->size, cube_vertices[cube_faces[f][i]][2] * this->size);
					}
				}

				else
					for (int i = 0; i < 4; i++)
					{
						glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
						glVertex3f(cube_vertices_fluid[cube_faces[f][i]][0] * this->size, cube_vertices_fluid[cube_faces[f][i]][1] * this->size, cube_vertices_fluid[cube_faces[f][i]][2] * this->size);
					}


			glEnd();
		}
		glColor3f(0.0, 0.0, 0.0);
		for (int f = 0; f < cube_num_faces; f++)
		{
			glBegin(GL_LINE_LOOP);
			for (int i = 0; i < 4; i++)
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * this->size, cube_vertices[cube_faces[f][i]][1] * this->size, cube_vertices[cube_faces[f][i]][2] * this->size);
			glEnd();
		}



		// Place base of cube on marker surface.
		//glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
		glDisable(GL_LIGHTING); // Just use colours.



		static int tempd = 0;



		//glEnable(GL_CULL_FACE);






		this->Translate(0, 0, speed * this->myAnimatorParameter[1].animatorParameter.currentFrame);
		this->Rotate2(speed * this->myAnimatorParameter[1].animatorParameter.currentFrame, 1, 0, 0, 0);


		this->DrawWireSphere(0.9 * size, false, false);



		this->Translate(0, 0, -speed * this->myAnimatorParameter[1].animatorParameter.currentFrame);
		this->Rotate2(-speed * this->myAnimatorParameter[1].animatorParameter.currentFrame, 1, 0, 0, 0);





		this->Translate(0, 0, speed * this->myAnimatorParameter[3].animatorParameter.currentFrame);
		this->Rotate2(speed * this->myAnimatorParameter[3].animatorParameter.currentFrame, 1, 0, 0, 0);



		this->DrawWireSphere(0.8 * size, false, true);


		this->Translate(0, 0, -speed * this->myAnimatorParameter[3].animatorParameter.currentFrame);
		this->Rotate2(-speed * this->myAnimatorParameter[3].animatorParameter.currentFrame, 1, 0, 0, 0);



		this->masterMatrixs->glLoadMasterMatrix();

	}



	//class Bezier
	void Bezier::DrawCurveLine()
	{
		ApplyMatrix();



		// 컨트롤 포인트 설정
		static GLfloat ctrlpoints[4][3] = {
			{ -40.0 * this->size, -40.0 * this->size, 0.0 },{ -20.0 * this->size, 40.0 * this->size, 0.0 },{ 20.0 * this->size, 20.0 * this->size, 0.0 } ,{ 40.0 * this->size, 0.0, 0.0 } };
		// 곡선 제어점 설정: 매개변수 u의 최소값은 0, 최대값은 1,
		// 제어점간의 데이터 개수는 3, 제어점은 4개를 사용
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
		glEnable(GL_MAP1_VERTEX_3);
		// 제어점 사이의 곡선위의 점들을 계산한다. 제어점 사이를 10개로 나누어 그 점들을 연결한다.  곡선위의 점 계산
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= 10; i++)
			glEvalCoord1f((GLfloat)i / 10.0);
		glEnd();
		glDisable(GL_MAP1_VERTEX_3);
		// 제어점에 점을 그린다.
		glPointSize(5.0);
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POINTS);
		for (int i = 0; i < 4; i++)
			glVertex3fv(&ctrlpoints[i][0]);
		glEnd();



		this->masterMatrixs->glLoadMasterMatrix();

	}




	//class BounceBall
	void BounceBall::Draw()
	{
		ApplyMatrix();


		if (this->bounceBallProperty.doYouWantDrawBoundingBox)
		{
			this->DrawBoundingBox();
		}


		//this->DrawSphere

		this->DrawSphere2(this->initializeData.size, this->initializeData.randomColorOption, this->initializeData.rainbowColorOption, false);








		this->masterMatrixs->glLoadMasterMatrix();



	}
	void BounceBall::AllProcess()
	{
		this->HandleEvent();

		this->Update();

		this->Draw();


	}

	void BounceBall::StateEnter()
	{
		if (this->bounceBallProperty.state == Idle)
		{

			printf("Idle 진입\n");

		}

		else if (this->bounceBallProperty.state == JumpUp)
		{
			this->bounceBallProperty.velocity.y = this->bounceBallProperty.jumpPower.y;

			if (this->soundFileName != "")
			{

				PlaySoundA(this->soundFileName, NULL, SND_ASYNC | SND_NOSTOP);
			}
		}
		else if (this->bounceBallProperty.state == SuperJumpup)
		{
			this->bounceBallProperty.velocity.y = this->bounceBallProperty.superJumpPower.y;

			if (this->soundFileName != "")
			{

				PlaySoundA(this->soundFileName, NULL, SND_ASYNC | SND_NOSTOP);
			}
		}
	}

	void BounceBall::HandleEvent()
	{

		if (this->stateStack.size() > 0)
		{
			this->bounceBallProperty.state = (BounceBall::SimpleState)this->stateStack.back();
			this->StateEnter();
			this->stateStack.pop_back();

		}


	}

	void BounceBall::Update()
	{


		if (this->bounceBallProperty.state == Idle)
		{



		}

		else if (this->bounceBallProperty.state == JumpUp)
		{

			this->Translate(this->bounceBallProperty.velocity);

			this->bounceBallProperty.velocity.y -= 0.9;

			if (this->bounceBallProperty.landingActivate)
			{
				if (this->Position().y <= this->bounceBallProperty.landingYPosition)
				{

					this->stateStack.push_back(JumpUp);
				}
			}

			if (bounceBallProperty.velocity.x != 0 || bounceBallProperty.velocity.y != 0 || bounceBallProperty.velocity.z != 0)
			{
				this->direction = this->masterMatrixs->Normalize(this->bounceBallProperty.velocity);
			}
		}
		else if (this->bounceBallProperty.state == SuperJumpup)
		{

			this->Translate(this->bounceBallProperty.velocity);

			this->bounceBallProperty.velocity.y -= 0.9;

			if (this->bounceBallProperty.landingActivate)
			{
				if (this->Position().y <= this->bounceBallProperty.landingYPosition)
				{

					this->stateStack.push_back(JumpUp);
				}
			}

			if (bounceBallProperty.velocity.x != 0 || bounceBallProperty.velocity.y != 0 || bounceBallProperty.velocity.z != 0)
			{
				this->direction = this->masterMatrixs->Normalize(this->bounceBallProperty.velocity);
			}

		}



	}

	void BounceBall::GetBoundingBoxVertices()
	{


		this->boundingBoxRange[0] = GLVector3(this->Position().x - this->initializeData.size, this->Position().y - this->initializeData.size, this->Position().z - this->initializeData.size);
		this->boundingBoxRange[1] = GLVector3(this->Position().x + this->initializeData.size, this->Position().y + this->initializeData.size, this->Position().z + this->initializeData.size);

	}

	void BounceBall::DrawBoundingBox()
	{
		ApplyMatrix();


		this->DrawWireCube(this->initializeData.size, false, false);


		this->masterMatrixs->glLoadMasterMatrix();
	}

	bool BounceBall::CollisionCheck()
	{
		return false;

	}


	void BounceBall::InitializeBall(float size, bool doYouWantDrawBoundingBox, bool landingActivate, GLVector3 velocity, GLVector3 jumpPower, int state)
	{
		this->initializeData.size = size;

		this->bounceBallProperty.landingActivate = landingActivate;
		this->bounceBallProperty.doYouWantDrawBoundingBox = doYouWantDrawBoundingBox;
		this->bounceBallProperty.jumpPower = jumpPower;
		this->bounceBallProperty.velocity = velocity;
		this->stateStack.push_back(state);
		this->bounceBallProperty.originalJumpPower = jumpPower;
		this->bounceBallProperty.superJumpPower = GLVector3(0, jumpPower.y * 1.5, 0);
	}




	//class LightSource
	void LightSource::DrawLightSource()
	{
		if (!this->objectActivate)
		{
			return;
		}

		ApplyMatrix();
		this->InitLighting();
		//this->DrawCube(50, false, false);
		this->qaLightPosition[0] = this->Position().x;
		this->qaLightPosition[1] = this->Position().y;
		this->qaLightPosition[2] = this->Position().z;
		if (this->wantToUseSpotLight)
		{


			glLightfv(GL_LIGHT0 + (this->lightSourceNum % 8), GL_POSITION, qaSpotLightPosition);

		}
		else
		{


			glLightfv(GL_LIGHT0 + (this->lightSourceNum % 8), GL_POSITION, qaLightPosition);

		}
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLight);   // Make sphere glow (emissive) 
		glutSolidSphere(5 * size, 25, 25);

		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);



		this->masterMatrixs->glLoadMasterMatrix();
	}

	void LightSource::InitLighting()
	{
		// Enable lighting
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0 + (this->lightSourceNum % 8));


		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, qaAmbientLight);
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0);


		this->qaLightPosition[0] = this->Position().x;
		this->qaLightPosition[1] = this->Position().y;
		this->qaLightPosition[2] = this->Position().z;



		if (this->wantToUseSpotLight)
		{
			glLightfv(GL_LIGHT0 + (this->lightSourceNum % 8), GL_AMBIENT, qaAmbientLight);
			glLightfv(GL_LIGHT0 + (this->lightSourceNum % 8), GL_DIFFUSE, qaDiffuseLight);
			glLightfv(GL_LIGHT0 + (this->lightSourceNum % 8), GL_SPECULAR, qaSpecularLight);


			glLightfv(GL_LIGHT0 + (this->lightSourceNum % 8), GL_POSITION, qaSpotLightPosition);
			glLightfv(GL_LIGHT0 + (this->lightSourceNum % 8), GL_SPOT_DIRECTION, qaSpotLightDirection);
			glLightf(GL_LIGHT0 + (this->lightSourceNum % 8), GL_SPOT_CUTOFF, spotLightDegree);
			glLightf(GL_LIGHT0 + (this->lightSourceNum % 8), GL_SPOT_EXPONENT, spotLightExponent);

		}

		else if (!this->wantToUseSpotLight)
		{

			// Set lighting intensity and color
			glLightfv(GL_LIGHT0 + (this->lightSourceNum % 8), GL_AMBIENT, qaAmbientLight);
			glLightfv(GL_LIGHT0 + (this->lightSourceNum % 8), GL_DIFFUSE, qaDiffuseLight);
			glLightfv(GL_LIGHT0 + (this->lightSourceNum % 8), GL_SPECULAR, qaSpecularLight);
			glLightfv(GL_LIGHT0 + (this->lightSourceNum % 8), GL_POSITION, qaLightPosition);

		}


		//glDisable(GL_LIGHTING);
		//glDisable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
	}

	void LightSource::Off()
	{
		glDisable(GL_LIGHT0 + (this->lightSourceNum % 8));
	}
	void LightSource::On()
	{

		glEnable(GL_LIGHT0 + (this->lightSourceNum % 8));
	}
	void LightSource::OnOff()
	{
		this->onOff = !this->onOff;
		this->objectActivate = onOff;

		if (this->onOff)
		{
			glEnable(GL_LIGHT0 + (this->lightSourceNum % 8));

		}
		else
		{
			glDisable(GL_LIGHT0 + (this->lightSourceNum % 8));
		}

	}





	//class Cylinder
	void Cylinder::DrawCylinder()
	{
		if (!this->objectActivate)
		{
			return;
		}

		ApplyMatrix();

		glRotated(90, 1, 0, 0);
		glutSolidCylinder(this->radius, this->height, 25, 25);
		if (this->wireOption)
		{
			glDisable(GL_LIGHTING);
			glColor3d(0, 1.0, 0.1);
			glutWireCylinder(this->radius, this->height, 25, 25);
			glEnable(GL_LIGHTING);
		}


		this->masterMatrixs->glLoadMasterMatrix();
	}

	void Cylinder::DrawCylinder(double radius, double height, bool wireOption)
	{
		if (!this->objectActivate)
		{
			return;
		}

		ApplyMatrix();



		this->SetParameter(radius, height, wireOption);

		glRotated(90, 1, 0, 0);
		glutSolidCylinder(this->radius, this->height, 25, 25);
		if (this->wireOption)
		{
			glDisable(GL_LIGHTING);
			glColor3d(0, 1.0, 0.1);
			glutWireCylinder(this->radius, this->height, 25, 25);
			glEnable(GL_LIGHTING);
		}


		this->masterMatrixs->glLoadMasterMatrix();
	}
	void Cylinder::SetParameter(double radius, double height, bool wireOption)
	{
		this->radius = radius;
		this->height = height;
		this->wireOption = wireOption;


	}




	//class Pyramid

	void Pyramid::DrawPyramid()
	{
		ApplyMatrix();

		static double pyramidVertices[5][3] =
		{
			//bottom
			{1,0,-1},
			{-1,0,-1},
			{-1,0,1},
			{1,0,1},
			//top
			{ 0,1,0 }

		};

		static int sideFaceIndexList[4][3] =
		{

			{ 4,2,3 },
			{ 4,3,0 },
			{ 4,0,1 },
			{ 4,1,2 },


		};



		glBegin(GL_QUADS);

		for (int i = 0; i < 4; ++i)
		{

			glVertex3d(pyramidVertices[i][0] * this->width, pyramidVertices[i][1] * this->width, pyramidVertices[i][2] * this->width);



		}



		glEnd();
		for (int i = 0; i < 4; ++i)
		{
			glBegin(GL_TRIANGLE_STRIP);
			for (int j = 0; j < 3; ++j)
			{
				if (j == 0)
				{


					glVertex3d(pyramidVertices[sideFaceIndexList[i][j]][0] * this->width, pyramidVertices[sideFaceIndexList[i][j]][1] * this->height, pyramidVertices[sideFaceIndexList[i][j]][2] * this->width);
				}

				else
				{

					glVertex3d(pyramidVertices[sideFaceIndexList[i][j]][0] * this->width, pyramidVertices[sideFaceIndexList[i][j]][1] * this->width, pyramidVertices[sideFaceIndexList[i][j]][2] * this->width);

				}
			}
			glEnd();

		}
		//노멀 설정



		this->masterMatrixs->glLoadMasterMatrix();
	}
	void Pyramid::DrawPyramid(double width, double height, bool wireOption)
	{
		ApplyMatrix();

		this->SetParameter(width, height, wireOption);

		static double pyramidVertices[5][3] =
		{
			//bottom
			{ 1,0,-1 },
		{ -1,0,-1 },
		{ -1,0,1 },
		{ 1,0,1 },
		//top
		{ 0,1,0 }

		};

		static int sideFaceIndexList[4][3] =
		{

			{ 4,2,3 },
		{ 4,3,0 },
		{ 4,0,1 },
		{ 4,1,2 },


		};



		glBegin(GL_QUADS);

		for (int i = 0; i < 4; ++i)
		{

			glVertex3d(pyramidVertices[i][0] * this->width, pyramidVertices[i][1] * this->width, pyramidVertices[i][2] * this->width);



		}



		glEnd();



		for (int i = 0; i < 4; ++i)
		{
			glBegin(GL_TRIANGLE_STRIP);
			this->SetNormal(
				GLVector3(pyramidVertices[sideFaceIndexList[i][0]][0] * this->width, pyramidVertices[sideFaceIndexList[i][0]][1] * this->height, pyramidVertices[sideFaceIndexList[i][0]][2] * this->width),
				GLVector3(pyramidVertices[sideFaceIndexList[i][1]][0] * this->width, pyramidVertices[sideFaceIndexList[i][1]][1] * this->height, pyramidVertices[sideFaceIndexList[i][1]][2] * this->width)

			);

			for (int j = 0; j < 3; ++j)
			{
				if (j == 0)
				{


					glVertex3d(pyramidVertices[sideFaceIndexList[i][j]][0] * this->width, pyramidVertices[sideFaceIndexList[i][j]][1] * this->height, pyramidVertices[sideFaceIndexList[i][j]][2] * this->width);
				}

				else
				{

					glVertex3d(pyramidVertices[sideFaceIndexList[i][j]][0] * this->width, pyramidVertices[sideFaceIndexList[i][j]][1] * this->width, pyramidVertices[sideFaceIndexList[i][j]][2] * this->width);

				}
			}
			glEnd();

		}



		//노멀 설정


		this->masterMatrixs->glLoadMasterMatrix();
	}
	void Pyramid::SetParameter(double width, double height, bool wireOption)
	{
		this->width = width;
		this->height = height;
		this->wireOption = wireOption;




	}

	//class RollerCoasterTrain

	void RollerCoasterTrain::DrawTrain(float size, bool random, bool rainbow)
	{
		ApplyMatrix();

		this->size = size;





		this->Scale(1, 1, 3);
		this->SetFreeRotateXAxis(GLVector3(0, 0, 0), GLVector3(1, 0, 0));
		this->SetFreeRotateYAxis(GLVector3(0, 0, 0), GLVector3(0, 1, 0));
		this->DrawHexahedron(this->size, random, rainbow, false);

		this->Scale(1, 3, 1);
		this->Translate(0, this->size, 1.5*this->size);
		this->SetFreeRotateXAxis(GLVector3(0, -this->size, -1.5*this->size), GLVector3(+1, -this->size, -1.5*this->size));
		this->SetFreeRotateYAxis(GLVector3(0, -this->size, -1.5*this->size), GLVector3(0, -this->size + 2, -1.5*this->size));
		this->DrawCube(this->size / 2, false, true);
		this->Translate(0, -this->size, -1.5*this->size);


		this->Scale(1, 1, 1);
		this->SetFreeRotateXAxis(GLVector3(0, 0, 0), GLVector3(1, 0, 0));
		this->SetFreeRotateYAxis(GLVector3(0, 0, 0), GLVector3(0, 1, 0));
		this->DrawSphere2(this->size, false, false, false);

		this->Translate(0, 0, -1.5 * this->size);
		this->SetFreeRotateXAxis(GLVector3(0, 0, 1.5 * this->size), GLVector3(1, 0, 1.5 * this->size));
		this->SetFreeRotateYAxis(GLVector3(0, 0, 1.5 * this->size), GLVector3(0, 1, 1.5 * this->size));
		this->DrawSphere2(this->size, false, false, false);
		this->Translate(0, 0, 1.5 * this->size);


		this->Translate(0, 0, 1.5 * this->size);
		this->SetFreeRotateXAxis(GLVector3(0, 0, -1.5 * this->size), GLVector3(1, 0, -1.5 * this->size));
		this->SetFreeRotateYAxis(GLVector3(0, 0, -1.5 * this->size), GLVector3(0, 1, -1.5 * this->size));
		this->DrawSphere2(this->size, false, false, false);
		this->Translate(0, 0, -1.5 * this->size);


		this->masterMatrixs->glLoadMasterMatrix();
	}







	//class RollerCoasterRail
	void RollerCoasterRail::DrawSpline()
	{
		ApplyMatrix();

		static double cubeSize = 10.0;
		static int loop = 10;



		glDisable(GL_LIGHTING);





		if (this->cardinalControlPoints.size() >= 1)
		{


			for (int i = 0; i < this->cardinalControlPoints.size(); ++i)
			{







				this->Translate(this->cardinalControlPoints[i]);
				this->DrawCube(5, false, false);

				this->Translate(-this->cardinalControlPoints[i].x, -this->cardinalControlPoints[i].y, -this->cardinalControlPoints[i].z);






			}


			for (int j = 0; j < this->cardinalControlPoints.size() - 1; ++j)
			{
				if (this->cardinalControlMiddlePoints.size() < this->cardinalControlPoints.size() - 1)
				{
					this->cardinalControlMiddlePoints.push_back(GLVector3(0, 0, 0));
				}


				if (j != 0 && j + 2 < this->cardinalControlPoints.size())
				{

					this->cardinalControlMiddlePoints[j] = GLVector3(

						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)0.5).x,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)0.5).y,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)0.5).z

					);

					glColor3d(1, 0.5, 0.2);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 100; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 100.0).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 100.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 100.0).z
						);

					}


					glEnd();


					glColor3d(0.5, 0.5, 1.0);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 10; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 10.0).x - 10,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 10.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 10.0).z
						);

					}


					glEnd();



					for (int k = 0; k < loop; ++k)
					{


						this->Translate(this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)k / (double)loop));
						this->DrawBoard(cubeSize, false, false);



						this->Translate
						(
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)k / (double)loop).x,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)k / (double)loop).y,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)k / (double)loop).z
						);



					}




					//printf("1번\n");
				}

				else if (j + 2 < this->cardinalControlPoints.size())
				{


					this->cardinalControlMiddlePoints[j] = GLVector3(

						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)0.5).x,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)0.5).y,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)0.5).z

					);



					glColor3d(1, 0.5, 0.2);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 100; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 100.0).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 100.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 100.0).z
						);
					}

					glEnd();

					//printf("2번 %d\n",j);


					glColor3d(0.5, 0.5, 1.0);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 10; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 10.0).x - 10,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 10.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / 10.0).z
						);
					}

					glEnd();



					for (int k = 0; k < loop; ++k)
					{


						this->Translate(this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)k / (double)loop));
						this->DrawBoard(cubeSize, false, false);



						this->Translate
						(
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)k / (double)loop).x,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)k / (double)loop).y,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)k / (double)loop).z
						);



					}

				}
				else
				{

					this->cardinalControlMiddlePoints[j] = GLVector3(

						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)0.5).x,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)0.5).y,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)0.5).z

					);





					glColor3d(1, 0.5, 0.2);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 100; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / 100.0).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / 100.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / 100.0).z
						);
					}

					glEnd();



					glColor3d(0.5, 0.5, 1.0);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 10; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / 10.0).x - 10,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / 10.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / 10.0).z
						);
					}

					glEnd();




					for (int k = 0; k < loop; ++k)
					{


						this->Translate(this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)k / (double)loop));
						this->DrawBoard(cubeSize, false, false);



						this->Translate
						(
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)k / (double)loop).x,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)k / (double)loop).y,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)k / (double)loop).z
						);



					}

					//printf("3번 %d\n",j);
				}



				if (3 == this->cardinalControlPoints.size())
				{
					this->cardinalControlMiddlePoints[j] = GLVector3(

						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)0.5).x,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)0.5).y,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)0.5).z

					);


					glColor3d(1, 0.5, 0.2);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 100; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / 100.0).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / 100.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / 100.0).z
						);
					}

					glEnd();



					glColor3d(0, 0.5, 1.0);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 10; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / 10.0).x - 10,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / 10.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / 10.0).z
						);
					}

					glEnd();



					for (int k = 0; k < loop; ++k)
					{


						this->Translate(this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)k / (double)loop));
						this->DrawBoard(cubeSize, false, false);



						this->Translate
						(
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)k / (double)loop).x,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)k / (double)loop).y,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)k / (double)loop).z
						);



					}


				}
				else if (this->cardinalControlPoints.size() >= 4)
				{


					this->cardinalControlMiddlePoints[j] = GLVector3(

						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)0.5).x,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)0.5).y,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)0.5).z

					);


					glColor3d(1, 0.5, 0.2);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 100; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / 100.0).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / 100.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / 100.0).z
						);
					}

					glEnd();



					glColor3d(0.1, 0.5, 1.0);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 10; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / 10.0).x - 10,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / 10.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / 10.0).z
						);
					}

					glEnd();



					for (int k = 0; k < loop; ++k)
					{


						this->Translate(this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)k / (double)loop));
						this->DrawBoard(cubeSize, false, false);



						this->Translate
						(
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)k / (double)loop).x,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)k / (double)loop).y,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)k / (double)loop).z
						);

					}

				}

				else
				{


					this->cardinalControlMiddlePoints[j] = GLVector3(

						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)0.5).x,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)0.5).y,
						this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)0.5).z

					);



					glColor3d(1, 0.5, 0.2);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 100; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)100.0).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)100.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)100.0).z);
					}

					glEnd();



					glColor3d(0.1, 0.5, 1.0);
					glBegin(GL_LINE_STRIP);

					for (int i = 0; i < 10; ++i)
					{
						glVertex3d(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)10.0).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)10.0).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)10.0).z);
					}

					glEnd();



					for (int k = 0; k < loop; ++k)
					{


						this->Translate(this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)k / (double)loop));
						this->DrawBoard(cubeSize, false, false);



						this->Translate
						(
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)k / (double)loop).x,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)k / (double)loop).y,
							-this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)k / (double)loop).z
						);

					}

				}




			}




		}





		glEnable(GL_LIGHTING);





		this->masterMatrixs->glLoadMasterMatrix();
	}


	void RollerCoasterRail::MoveObjectOnRail()
	{
		ApplyMatrix();


		if (this->thisObject == nullptr)
		{
			return;
		}


		static double cubeSize = 10.0;
		static int loop = 10;

		static int saveJ = 0;
		static int saveI = 0;
		static int savek = 0;
		static double* scalarTriple;

		static int temp = 100;

		glDisable(GL_LIGHTING);

		//짐벌락 말고 자유축 회전으로.

		if (this->cardinalControlPoints.size() < 2)
		{
			saveI = 0;
			saveJ = 0;
			savek = 0;
			return;
		}

		if (this->cardinalControlPoints.size() >= 1)
		{



			for (int j = saveJ; j < this->cardinalControlPoints.size() - 1; ++j)
			{

				if ((int)this->cardinalControlPoints[j].y < (int)this->cardinalControlPoints[j + 1].y)
				{
					temp = 160;
				}
				else if ((int)this->cardinalControlPoints[j].y > (int)this->cardinalControlPoints[j + 1].y)
				{
					temp = 60;
				}
				else
				{
					temp = 100;
				}


				if (j != 0 && j + 2 < this->cardinalControlPoints.size())
				{




					for (int i = saveI; i < temp; ++i)
					{

						this->thisObject->freeAxisRotate = true;
						scalarTriple = this->masterMatrixs->ScalarTriple(

							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z),
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z),
							this->thisObject->standardDirection);
						this->thisObject->FreeXAxisRotate(scalarTriple[1]);
						this->thisObject->FreeYAxisRotate(scalarTriple[0]);

						this->thisObject->direction = GLVector3(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z);




						this->thisObject->SetPosition(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z);


						saveI = i + 1;

						return;
					}








					//printf("1번\n");
				}

				else if (j + 2 < this->cardinalControlPoints.size())
				{






					for (int i = saveI; i < temp; ++i)
					{



						this->thisObject->freeAxisRotate = true;
						scalarTriple = this->masterMatrixs->ScalarTriple(
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z),
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z),

							this->thisObject->standardDirection);
						this->thisObject->FreeXAxisRotate(scalarTriple[1]);
						this->thisObject->FreeYAxisRotate(scalarTriple[0]);


						this->thisObject->direction = GLVector3(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z);



						this->thisObject->SetPosition(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z);

						saveI = i + 1;


						return;


					}

					//printf("2번 %d\n",j);







				}
				else
				{




					for (int i = saveI; i < temp; ++i)
					{


						this->thisObject->freeAxisRotate = true;
						scalarTriple = this->masterMatrixs->ScalarTriple(

							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).z),
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).z),

							this->thisObject->standardDirection);
						this->thisObject->FreeXAxisRotate(scalarTriple[1]);
						this->thisObject->FreeYAxisRotate(scalarTriple[0]);


						this->thisObject->direction = GLVector3(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).z);



						this->thisObject->SetPosition(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).z);


						saveI = i + 1;

						return;
					}

					//printf("2번 %d\n",j);









					//printf("3번 %d\n",j);
				}

				if (j == this->cardinalControlPoints.size() - 2)
				{
					if (3 == this->cardinalControlPoints.size())
					{








						for (int i = savek; i < temp; ++i)
						{


							this->thisObject->freeAxisRotate = true;
							scalarTriple = this->masterMatrixs->ScalarTriple(

								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).z),
								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).z),

								this->thisObject->standardDirection);
							this->thisObject->FreeXAxisRotate(scalarTriple[1]);
							this->thisObject->FreeYAxisRotate(scalarTriple[0]);




							this->thisObject->direction = GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).z);





							this->thisObject->SetPosition(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).z
							);



							savek = i + 1;

							return;

						}







					}
					else if (this->cardinalControlPoints.size() >= 4)
					{





						for (int i = savek; i < temp; ++i)
						{


							this->thisObject->freeAxisRotate = true;
							scalarTriple = this->masterMatrixs->ScalarTriple(

								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).z),
								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).z),


								this->thisObject->standardDirection);
							this->thisObject->FreeXAxisRotate(scalarTriple[1]);
							this->thisObject->FreeYAxisRotate(scalarTriple[0]);


							this->thisObject->direction = GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).z);


							this->thisObject->SetPosition(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).z
							);



							savek = i + 1;

							return;

						}








					}

					else
					{

						for (int i = savek; i < temp; ++i)
						{



							this->thisObject->freeAxisRotate = true;
							scalarTriple = this->masterMatrixs->ScalarTriple(

								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).z),
								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).z),

								this->thisObject->standardDirection);
							this->thisObject->FreeXAxisRotate(scalarTriple[1]);
							this->thisObject->FreeYAxisRotate(scalarTriple[0]);


							this->thisObject->direction = GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).z);



							this->thisObject->SetPosition(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).z
							);



							savek = i + 1;

							return;

						}






					}


				}
				saveJ = j + 1;
				saveI = 0;
				savek = 0;
				return;

			}

			saveJ = 0;


		}








		glEnable(GL_LIGHTING);



		this->masterMatrixs->glLoadMasterMatrix();
	}




	void RollerCoasterRail::MoveObjectOnRail2()
	{
		ApplyMatrix();


		if (this->thisObject2 == nullptr)
		{
			return;
		}


		static double cubeSize = 10.0;
		static int loop = 10;

		static int saveJ = 0;
		static int saveI = 0;
		static int savek = 0;
		static double* scalarTriple;

		static int temp = 100;

		glDisable(GL_LIGHTING);

		//짐벌락 말고 자유축 회전으로.

		if (this->cardinalControlPoints.size() < 2)
		{
			saveI = 0;
			saveJ = 0;
			savek = 0;
			return;
		}

		if (this->cardinalControlPoints.size() >= 1)
		{



			for (int j = saveJ; j < this->cardinalControlPoints.size() - 1; ++j)
			{

				if ((int)this->cardinalControlPoints[j].y < (int)this->cardinalControlPoints[j + 1].y)
				{
					temp = 160;
				}
				else if ((int)this->cardinalControlPoints[j].y > (int)this->cardinalControlPoints[j + 1].y)
				{
					temp = 60;
				}
				else
				{
					temp = 100;
				}


				if (j != 0 && j + 2 < this->cardinalControlPoints.size())
				{




					for (int i = saveI; i < temp; ++i)
					{

						this->thisObject2->freeAxisRotate = true;
						scalarTriple = this->masterMatrixs->ScalarTriple(

							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z),
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z),
							this->thisObject2->standardDirection);
						this->thisObject2->FreeXAxisRotate(scalarTriple[1]);
						this->thisObject2->FreeYAxisRotate(scalarTriple[0]);

						this->thisObject2->direction = GLVector3(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z);




						this->thisObject2->SetPosition(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z);


						saveI = i + 1;

						return;
					}








					//printf("1번\n");
				}

				else if (j + 2 < this->cardinalControlPoints.size())
				{






					for (int i = saveI; i < temp; ++i)
					{



						this->thisObject2->freeAxisRotate = true;
						scalarTriple = this->masterMatrixs->ScalarTriple(
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z),
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z),

							this->thisObject2->standardDirection);
						this->thisObject2->FreeXAxisRotate(scalarTriple[1]);
						this->thisObject2->FreeYAxisRotate(scalarTriple[0]);


						this->thisObject2->direction = GLVector3(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z);



						this->thisObject2->SetPosition(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z);

						saveI = i + 1;


						return;


					}

					//printf("2번 %d\n",j);







				}
				else
				{




					for (int i = saveI; i < temp; ++i)
					{


						this->thisObject2->freeAxisRotate = true;
						scalarTriple = this->masterMatrixs->ScalarTriple(

							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).z),
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).z),

							this->thisObject2->standardDirection);
						this->thisObject2->FreeXAxisRotate(scalarTriple[1]);
						this->thisObject2->FreeYAxisRotate(scalarTriple[0]);


						this->thisObject2->direction = GLVector3(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).z);



						this->thisObject2->SetPosition(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).z);


						saveI = i + 1;

						return;
					}

					//printf("2번 %d\n",j);









					//printf("3번 %d\n",j);
				}

				if (j == this->cardinalControlPoints.size() - 2)
				{
					if (3 == this->cardinalControlPoints.size())
					{








						for (int i = savek; i < temp; ++i)
						{


							this->thisObject2->freeAxisRotate = true;
							scalarTriple = this->masterMatrixs->ScalarTriple(

								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).z),
								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).z),

								this->thisObject2->standardDirection);
							this->thisObject2->FreeXAxisRotate(scalarTriple[1]);
							this->thisObject2->FreeYAxisRotate(scalarTriple[0]);




							this->thisObject2->direction = GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).z);





							this->thisObject2->SetPosition(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).z
							);



							savek = i + 1;

							return;

						}







					}
					else if (this->cardinalControlPoints.size() >= 4)
					{





						for (int i = savek; i < temp; ++i)
						{


							this->thisObject2->freeAxisRotate = true;
							scalarTriple = this->masterMatrixs->ScalarTriple(

								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).z),
								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).z),


								this->thisObject2->standardDirection);
							this->thisObject2->FreeXAxisRotate(scalarTriple[1]);
							this->thisObject2->FreeYAxisRotate(scalarTriple[0]);


							this->thisObject2->direction = GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).z);


							this->thisObject2->SetPosition(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).z
							);



							savek = i + 1;

							return;

						}








					}

					else
					{

						for (int i = savek; i < temp; ++i)
						{



							this->thisObject2->freeAxisRotate = true;
							scalarTriple = this->masterMatrixs->ScalarTriple(

								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).z),
								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).z),

								this->thisObject2->standardDirection);
							this->thisObject2->FreeXAxisRotate(scalarTriple[1]);
							this->thisObject2->FreeYAxisRotate(scalarTriple[0]);


							this->thisObject2->direction = GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).z);



							this->thisObject2->SetPosition(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).z
							);



							savek = i + 1;

							return;

						}






					}


				}
				saveJ = j + 1;
				saveI = 0;
				savek = 0;
				return;

			}

			saveJ = 0;


		}








		glEnable(GL_LIGHTING);



		this->masterMatrixs->glLoadMasterMatrix();
	}



	void RollerCoasterRail::MoveObjectOnRail3()
	{
		ApplyMatrix();


		if (this->thisObject3 == nullptr)
		{
			return;
		}


		static double cubeSize = 10.0;
		static int loop = 10;

		static int saveJ = 0;
		static int saveI = 0;
		static int savek = 0;
		static double* scalarTriple;

		static int temp = 100;

		glDisable(GL_LIGHTING);

		//짐벌락 말고 자유축 회전으로.

		if (this->cardinalControlPoints.size() < 2)
		{
			saveI = 0;
			saveJ = 0;
			savek = 0;
			return;
		}

		if (this->cardinalControlPoints.size() >= 1)
		{



			for (int j = saveJ; j < this->cardinalControlPoints.size() - 1; ++j)
			{

				if ((int)this->cardinalControlPoints[j].y < (int)this->cardinalControlPoints[j + 1].y)
				{
					temp = 160;
				}
				else if ((int)this->cardinalControlPoints[j].y > (int)this->cardinalControlPoints[j + 1].y)
				{
					temp = 60;
				}
				else
				{
					temp = 100;
				}



				if (j != 0 && j + 2 < this->cardinalControlPoints.size())
				{




					for (int i = saveI; i < temp; ++i)
					{

						this->thisObject3->freeAxisRotate = true;
						scalarTriple = this->masterMatrixs->ScalarTriple(

							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z),
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z),
							this->thisObject3->standardDirection);
						this->thisObject3->FreeXAxisRotate(scalarTriple[1]);
						this->thisObject3->FreeYAxisRotate(scalarTriple[0]);

						this->thisObject3->direction = GLVector3(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z);




						this->thisObject3->SetPosition(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j - 1], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z);


						saveI = i + 1;

						return;
					}








					//printf("1번\n");
				}

				else if (j + 2 < this->cardinalControlPoints.size())
				{






					for (int i = saveI; i < temp; ++i)
					{



						this->thisObject3->freeAxisRotate = true;
						scalarTriple = this->masterMatrixs->ScalarTriple(
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z),
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z),

							this->thisObject3->standardDirection);
						this->thisObject3->FreeXAxisRotate(scalarTriple[1]);
						this->thisObject3->FreeYAxisRotate(scalarTriple[0]);


						this->thisObject3->direction = GLVector3(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)(i + 1) / temp).z);



						this->thisObject3->SetPosition(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 2], (double)i / temp).z);

						saveI = i + 1;


						return;


					}

					//printf("2번 %d\n",j);







				}
				else
				{




					for (int i = saveI; i < temp; ++i)
					{


						this->thisObject3->freeAxisRotate = true;
						scalarTriple = this->masterMatrixs->ScalarTriple(

							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).z),
							GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).z),

							this->thisObject3->standardDirection);
						this->thisObject3->FreeXAxisRotate(scalarTriple[1]);
						this->thisObject3->FreeYAxisRotate(scalarTriple[0]);


						this->thisObject3->direction = GLVector3(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)(i + 1) / temp).z);



						this->thisObject3->SetPosition(
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).x,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).y,
							this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[j], this->cardinalControlPoints[j], this->cardinalControlPoints[j + 1], this->cardinalControlPoints[j + 1], (double)i / temp).z);


						saveI = i + 1;

						return;
					}

					//printf("2번 %d\n",j);









					//printf("3번 %d\n",j);
				}

				if (j == this->cardinalControlPoints.size() - 2)
				{
					if (3 == this->cardinalControlPoints.size())
					{








						for (int i = savek; i < temp; ++i)
						{


							this->thisObject3->freeAxisRotate = true;
							scalarTriple = this->masterMatrixs->ScalarTriple(

								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).z),
								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).z),

								this->thisObject3->standardDirection);
							this->thisObject3->FreeXAxisRotate(scalarTriple[1]);
							this->thisObject3->FreeYAxisRotate(scalarTriple[0]);




							this->thisObject3->direction = GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)(i + 1) / temp).z);





							this->thisObject3->SetPosition(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[0], this->cardinalControlPoints[0], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], (double)i / temp).z
							);



							savek = i + 1;

							return;

						}







					}
					else if (this->cardinalControlPoints.size() >= 4)
					{





						for (int i = savek; i < temp; ++i)
						{


							this->thisObject3->freeAxisRotate = true;
							scalarTriple = this->masterMatrixs->ScalarTriple(

								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).z),
								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).z),


								this->thisObject3->standardDirection);
							this->thisObject3->FreeXAxisRotate(scalarTriple[1]);
							this->thisObject3->FreeYAxisRotate(scalarTriple[0]);


							this->thisObject3->direction = GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)(i + 1) / temp).z);


							this->thisObject3->SetPosition(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[this->cardinalControlPoints.size() - 2], this->cardinalControlPoints[this->cardinalControlPoints.size() - 1], this->cardinalControlPoints[0], this->cardinalControlPoints[1], (double)i / temp).z
							);



							savek = i + 1;

							return;

						}








					}

					else
					{

						for (int i = savek; i < temp; ++i)
						{



							this->thisObject3->freeAxisRotate = true;
							scalarTriple = this->masterMatrixs->ScalarTriple(

								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).z),
								GLVector3(
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).x,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).y,
									this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).z),

								this->thisObject3->standardDirection);
							this->thisObject3->FreeXAxisRotate(scalarTriple[1]);
							this->thisObject3->FreeYAxisRotate(scalarTriple[0]);


							this->thisObject3->direction = GLVector3(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)(i + 1) / (double)temp).z);



							this->thisObject3->SetPosition(
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).x,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).y,
								this->masterMatrixs->CalcCadinalSpline(this->cardinalControlPoints[1], this->cardinalControlPoints[1], this->cardinalControlPoints[0], this->cardinalControlPoints[0], (double)i / (double)temp).z
							);



							savek = i + 1;

							return;

						}






					}


				}
				saveJ = j + 1;
				saveI = 0;
				savek = 0;
				return;

			}

			saveJ = 0;


		}








		glEnable(GL_LIGHTING);



		this->masterMatrixs->glLoadMasterMatrix();
	}








	//class JangAeMul


	void JangAeMul::DrawJangAeMul(float size, bool random, bool rainbow)
	{
		ApplyMatrix();

		this->size = size;

		this->DrawCube(size, random, rainbow);



		this->masterMatrixs->glLoadMasterMatrix();
	}






	//class PicnicRobot



	void PicnicRobot::Draw()
	{
		ApplyMatrix();


		if (this->picnicRobotProperty.doYouWantDrawBoundingBox)
		{
			this->DrawBoundingBox();
		}
		this->SetFreeRotateZAxis(GLVector3(0, size * 2, 0), GLVector3(0, size * 2, 1));




		static int keyFrame = 20;
		static int currentFrame = 0;
		static int degree = 0;
		static int dir = 5;



		this->Scale(0.5, 3, 1.5);
		this->Translate(0, this->size * 2, 0);

		this->SetFreeRotateYAxis(GLVector3(0, -this->size * 2, 0), GLVector3(0, -this->size * 2 + 1, 0));


		this->DrawHexahedron(size, false, false, false);

		this->Translate(0, -this->size * 2, 0);
		this->ClearCurrentScale();




		this->FreeAxisRotate2(0, 0, degree);

		if (this->picnicRobotProperty.state == PicnicRobot::SimpleState::Walking)
		{
			degree += dir;
		}

		else if (this->picnicRobotProperty.state == PicnicRobot::SimpleState::Idle)
		{

			degree = 0;
		}

		if (degree > 80 || degree < -80)
		{
			dir *= -1;
		}





		this->Scale(0.5, 2, 0.5);
		this->Translate(0, 0, this->size);

		this->SetFreeRotateYAxis(GLVector3(0, 0, -this->size), GLVector3(0, 1, -this->size));
		//this->FreeAxisRotate2(0, 1, 0);


		this->DrawHexahedron(size, false, false, false);
		this->freeZAxisRotateDegree = 0;









		this->FreeAxisRotate2(0, 0, -degree);
		this->Translate(0, 0, -this->size * 2);

		this->SetFreeRotateYAxis(GLVector3(0, 0, 1 * this->size), GLVector3(0, 1, 1 * this->size));
		//this->FreeAxisRotate2(0, 1, 0);

		this->DrawHexahedron(size, false, false, false);
		this->freeZAxisRotateDegree = 0;




		this->Translate(0, 0, this->size);
		this->ClearCurrentScale();







		this->masterMatrixs->glLoadMasterMatrix();



	}


	void PicnicRobot::AllProcess()
	{
		this->HandleEvent();

		this->Update();

		this->Draw();


	}

	void PicnicRobot::StateEnter()
	{
		if (this->picnicRobotProperty.state == PicnicRobot::SimpleState::Idle)
		{
			this->picnicRobotProperty.velocity = GLVector3(0, 0, 0);


		}

		else if (this->picnicRobotProperty.state == PicnicRobot::SimpleState::Walking)
		{
			if (this->picnicRobotProperty.robotDirection == PicnicRobot::Direction::Down)
			{

				this->picnicRobotProperty.velocity = GLVector3(0, 0, 3.5);
				this->FreeYAxisRotate(90);
				this->direction = GLVector3(0, 0, 1);
				if (this->equipment != nullptr)
				{

					this->equipment->Rotate(90 + 180, 0, 1, 0, 1);

				}
			}

			else if (this->picnicRobotProperty.robotDirection == PicnicRobot::Direction::Up)
			{

				this->picnicRobotProperty.velocity = GLVector3(0, 0, -3.5);
				this->FreeYAxisRotate(270);
				this->direction = GLVector3(0, 0, -1);

				if (this->equipment != nullptr)
				{

					this->equipment->Rotate(270 + 180, 0, 1, 0, 1);

				}


			}
			else if (this->picnicRobotProperty.robotDirection == PicnicRobot::Direction::Left)
			{

				this->picnicRobotProperty.velocity = GLVector3(-3.5, 0, 0);
				this->FreeYAxisRotate(0);
				this->direction = GLVector3(-1, 0, 0);

				if (this->equipment != nullptr)
				{

					this->equipment->Rotate(180, 0, 1, 0, 1);

				}

			}

			else if (this->picnicRobotProperty.robotDirection == PicnicRobot::Direction::Right)
			{
				this->picnicRobotProperty.velocity = GLVector3(3.5, 0, 0);
				this->FreeYAxisRotate(180);

				this->direction = GLVector3(1, 0, 0);



				if (this->equipment != nullptr)
				{

					this->equipment->Rotate(180 + 180, 0, 1, 0, 1);

				}


			}

		}

	}

	void PicnicRobot::Fire()
	{

		for (int i = 0; i < this->bulletObjectList.size(); ++i)
		{
			if (!this->bulletObjectList[i].objectActivate)
			{

				this->bulletObjectList.erase(this->bulletObjectList.begin() + i);
			}

		}




		//if(this)
		this->bulletObjectList.push_back(BulletObject(this->masterMatrixs));
		this->bulletObjectList.back().SetPosition(this->Position().x, this->Position().y + this->size * 2, this->Position().z);

		if (rand() % 2 == 0)
		{
			this->bulletObjectList.back().laserOption = true;
		}



		if (this->picnicRobotProperty.velocity.x != 0 &&
			this->picnicRobotProperty.velocity.y != 0 &&
			this->picnicRobotProperty.velocity.z != 0)
		{
			this->bulletObjectList.back().velocity = this->picnicRobotProperty.velocity;
		}
		else
		{
			if (this->picnicRobotProperty.robotDirection == PicnicRobot::Direction::Down)
			{

				this->bulletObjectList.back().velocity = GLVector3(0, 0, 7);
				this->bulletObjectList.back().FreeYAxisRotate(90);

			}

			else if (this->picnicRobotProperty.robotDirection == PicnicRobot::Direction::Up)
			{

				this->bulletObjectList.back().velocity = GLVector3(0, 0, -7);
				this->bulletObjectList.back().FreeYAxisRotate(270);
			}
			else if (this->picnicRobotProperty.robotDirection == PicnicRobot::Direction::Left)
			{

				this->bulletObjectList.back().velocity = GLVector3(-7, 0, 0);
				this->bulletObjectList.back().FreeYAxisRotate(0);
			}

			else if (this->picnicRobotProperty.robotDirection == PicnicRobot::Direction::Right)
			{
				this->bulletObjectList.back().velocity = GLVector3(7, 0, 0);
				this->bulletObjectList.back().FreeYAxisRotate(180);


			}
		}
		this->bulletObjectList.back().boundingBoxSize = 20;
		this->bulletObjectList.back().size = 20;



	}

	void PicnicRobot::HandleEvent()
	{

		if (this->stateStack.size() > 0)
		{
			this->picnicRobotProperty.state = (PicnicRobot::SimpleState)this->stateStack.back();
			this->StateEnter();
			this->stateStack.pop_back();

		}


	}

	void PicnicRobot::Update()
	{



		if (this->picnicRobotProperty.option == PicnicRobot::Option::Manual)
		{

			if (this->picnicRobotProperty.state == PicnicRobot::SimpleState::Idle)
			{



			}

			else if (this->picnicRobotProperty.state == PicnicRobot::SimpleState::Walking)
			{

				this->Translate(this->picnicRobotProperty.velocity);

			}

			for (int i = 0; i < this->bulletObjectList.size(); ++i)
			{
				this->bulletObjectList[i].AllProcess();

			}

			if (this->equipment != nullptr)
			{

				this->equipment->SetPosition(this->Position());

			}


		}


		else if (this->picnicRobotProperty.option == PicnicRobot::Option::Auto)
		{

			if (this->picnicRobotProperty.state == PicnicRobot::SimpleState::Idle)
			{
				this->stateStack.push_back(PicnicRobot::SimpleState::Walking);
				this->picnicRobotProperty.robotDirection = (PicnicRobot::Direction)(rand() % 4);


			}

			else if (this->picnicRobotProperty.state == PicnicRobot::SimpleState::Walking)
			{
				if (this->timer > 220)
				{
					this->stateStack.push_back(PicnicRobot::SimpleState::Walking);
					this->picnicRobotProperty.robotDirection = (PicnicRobot::Direction)(rand() % 4);
					this->timer = 0;
				}
				this->Translate(this->picnicRobotProperty.velocity);
				this->timer++;

			}

			for (int i = 0; i < this->bulletObjectList.size(); ++i)
			{
				this->bulletObjectList[i].AllProcess();

			}


			if (this->equipment != nullptr)
			{

				this->equipment->SetPosition(this->Position());

			}


		}

		else if (this->picnicRobotProperty.option == PicnicRobot::Option::Couple)
		{
			if (this->couple == nullptr)

			{

				this->picnicRobotProperty.option = PicnicRobot::Option::Auto;
			}



			if (this->picnicRobotProperty.state == PicnicRobot::SimpleState::Idle)
			{
				this->stateStack.push_back(PicnicRobot::SimpleState::Walking);
				this->picnicRobotProperty.robotDirection = couple->picnicRobotProperty.robotDirection;


			}

			else if (this->picnicRobotProperty.state == PicnicRobot::SimpleState::Walking)
			{

				this->stateStack.push_back(PicnicRobot::SimpleState::Walking);
				this->picnicRobotProperty.robotDirection = couple->picnicRobotProperty.robotDirection;

				this->Translate(this->picnicRobotProperty.velocity);

			}

			for (int i = 0; i < this->bulletObjectList.size(); ++i)
			{
				this->bulletObjectList[i].AllProcess();

			}


			if (this->equipment != nullptr)
			{

				this->equipment->SetPosition(this->Position());

			}

			printf("커플모드\n");
		}

	}

	void PicnicRobot::GetBoundingBoxVertices()
	{


	}

	void PicnicRobot::DrawBoundingBox()
	{
		ApplyMatrix();




		this->masterMatrixs->glLoadMasterMatrix();
	}





	//class BulletObject
	void BulletObject::Draw()
	{
		ApplyMatrix();





		this->SetFreeRotateYAxis(GLVector3(0, 0, 0), GLVector3(0, 1, 0));


		if (this->laserOption)
		{

			this->Scale(5, 1, 1);
			this->DrawSphere2(this->size * 2, false, true, false);
		}

		else
		{
			this->DrawSphere2(this->size, false, false, false);

		}

		this->Translate(this->size * 1.5, 0, 0);


		this->SetFreeRotateYAxis(GLVector3(-this->size * 1.5, 0, 0), GLVector3(-this->size * 1.5, 1, 0));
		this->DrawSphere2(this->size, false, false, false);

		this->Translate(this->size * -1.5, 0, 0);





		this->masterMatrixs->glLoadMasterMatrix();

	}

	void BulletObject::Update()
	{



		this->Translate(this->velocity);

		this->checkLifeSpan++;



		if (this->checkLifeSpan > lifeSpan)
		{

			this->objectActivate = false;
		}

	}

	void BulletObject::AllProcess()
	{
		if (this->objectActivate == false)
		{
			return;
		}
		this->Update();




		this->Draw();

	}





	//class WeatherObject


	void WeatherObject::Draw()
	{
		ApplyMatrix();

		glEnable(GL_LIGHTING);
		//glDisable(GL_LIGHTING);
		for (int i = -this->height; i < this->height; ++i)
		{

			for (int j = -this->width; j < this->width; ++j)
			{


				//glColor3f(rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0);
				glColor3f(
					this->tiles[i + this->height][j + this->width].tileColor.x + this->tiles[i + this->height][j + this->width].stack * 0.2,
					this->tiles[i + this->height][j + this->width].tileColor.y + this->tiles[i + this->height][j + this->width].stack * 0.2,
					this->tiles[i + this->height][j + this->width].tileColor.z + this->tiles[i + this->height][j + this->width].stack * 0.2);


				glBegin(GL_QUADS);




				glVertex3d(this->size*(j + 1), 0, -this->size*(i + 1));
				glVertex3d(this->size*(j), 0, -this->size*(i + 1));
				glVertex3d(this->size*(j), 0, -this->size*(i));
				glVertex3d(this->size*(j + 1), 0, -this->size*(i));



				glEnd();


			}

		}

		//glEnable(GL_LIGHTING);

		this->masterMatrixs->glLoadMasterMatrix();
	}
	void WeatherObject::AddSnow(int n)
	{
		this->snowStartYPosition = this->Position().y + this->yStartPositionModulus * this->size;
		this->snowEndYPosition = this->Position().y + this->yEndPositionModulus * this->size;

		for (int i = 0; i < n; ++i)
		{
			this->snowRainList.push_back(Polygon0(this->masterMatrixs));
			this->snowRainList.back().j = (rand() % this->width * 2) - this->width;
			this->snowRainList.back().i = (rand() % this->height * 2) - this->height;



			this->snowRainList.back().SetPosition(this->snowRainList.back().j * this->size, this->snowStartYPosition, this->snowRainList.back().i * this->size * -1);
			this->snowRainList.back().velocity = GLVector3(0, -1 * (rand() % 4) / 4.0 - 1, 0);
			this->snowRainList.back().size = this->size / 2;

		}
	}

	void WeatherObject::StateEnter()
	{

		if (this->currentState == WeatherObject::SimpleState::Snow)
		{



			this->Clear();
			this->AddSnow(30);

		}

		else if (this->currentState == WeatherObject::SimpleState::Rain)
		{

			this->Clear();
			this->AddSnow(30);

		}

		else if (this->currentState == WeatherObject::SimpleState::Normal)
		{

			this->Clear();


		}

	}

	void WeatherObject::AllProcess()
	{
		if (!this->objectActivate)
			return;

		this->HandleEvent();
		this->Update();
		this->Draw();
	}

	void WeatherObject::Update()
	{

		if (this->currentState == WeatherObject::SimpleState::Rain)
		{


			for (int i = 0; i < this->snowRainList.size(); ++i)
			{

				this->snowRainList[i].Scale(1, 2, 1);
				this->snowRainList[i].Translate(this->snowRainList[i].velocity);
				this->snowRainList[i].color3D = GLVector3(0.2, 0.2, 0.2);
				this->snowRainList[i].DrawSphere2(this->snowRainList[i].size, true, false, false);


				if (this->snowRainList[i].Position().y < this->snowEndYPosition)
				{

					this->tiles[this->snowRainList[i].i + this->height][this->snowRainList[i].j + this->width].stack += 1;

					this->snowRainList[i].objectActivate = false;

					this->snowRainList.erase(this->snowRainList.begin() + i);

					this->AddSnow(1);
				}

			}
		}
		else if (this->currentState == WeatherObject::SimpleState::Snow)
		{


			for (int i = 0; i < this->snowRainList.size(); ++i)
			{
				this->snowRainList[i].Scale(1, 1, 1);
				this->snowRainList[i].Translate(this->snowRainList[i].velocity);
				this->snowRainList[i].DrawSphere2(this->snowRainList[i].size, false, false, false);


				if (this->snowRainList[i].Position().y < this->snowEndYPosition)
				{

					this->tiles[this->snowRainList[i].i + this->height][this->snowRainList[i].j + this->width].stack += 1;

					this->snowRainList[i].objectActivate = false;

					this->snowRainList.erase(this->snowRainList.begin() + i);

					this->AddSnow(1);
				}

			}
		}


	}

	void WeatherObject::HandleEvent()
	{

		if (this->stateStack.size() > 0)
		{
			this->currentState = (WeatherObject::SimpleState)this->stateStack.back();
			this->StateEnter();
			this->stateStack.pop_back();

		}


	}

	void WeatherObject::Clear()
	{

		for (int i = -this->height; i < this->height; ++i)
		{

			for (int j = -this->width; j < this->width; ++j)
			{

				this->tiles[i + this->height][j + this->width].stack = 0;
			}


		}
		for (int i = 0; i < this->snowRainList.size(); ++i)
		{
			this->snowRainList[i].objectActivate = false;
		}
		this->snowRainList.clear();

	}


	//class SimpleWireSphereParticle

	void SimpleWireSphereParticle::DrawSimpleWireSphereParticle()
	{
		if (!this->objectActivate)
		{
			return;
		}


		if ((int)this->size == 1)
		{

			this->size = 30.0f;

		}

		ApplyMatrix();







		this->Scale(1 + 0.03 * this->currentFrame, 1 + 0.03 * this->currentFrame, 1 + 0.03 * this->currentFrame);


		this->DrawWireSphere(this->size, false, false);

		this->currentFrame++;


		if (this->currentFrame > this->keyFrame)
		{
			this->objectActivate = false;
		}




		this->masterMatrixs->glLoadMasterMatrix();
	}
	void SimpleWireSphereParticle::Clear()
	{

		this->currentFrame = 0;
		this->objectActivate = true;

	}




	//class BezierCape

	void BezierCape::DrawBezierCape()
	{
		ApplyMatrix();


		static double temp = 0.1;

		static int keyFrame = 80;
		static int keyFrame2 = 0;
		static int currentFrame = 0;
		static int currentFrame2 = 0;

		static bool asd = false;

		currentFrame++;



		this->Scale(10, 10, 3);


		// 3차원 상의 제어점 설정 
		static GLfloat ctrlpoints[3][3][3] = {
			{{-8.0, 4, 4.0},{-6.0, 8, 4.0},{0.0, 4.0, 4.0}},
		{{-8.0, 4.0, 0.0}, {-6.0, 8.0, 0.0}, {0.0, 4.0, 0.0}},
		{{-8.0, 4.0, -4.0}, {-6.0, 8.0, -4.0}, {0.0, 4.0, -4.0}} };


		static GLfloat ctrlpoints2[3][3][3] = {
		{{4.0, 0, 4.0},{6.0, 4, 4.0},{12.0, 0.0, 4.0}},
		{{4.0, 0.0, 0.0}, {6.0, 4.0, 0.0}, {12.0, 0.0, 0.0}},
		{{4.0, 0.0, -4.0}, {6.0, 4.0, -4.0}, {12.0, 0.0, -4.0}} };

		glColor3f(0.0, 1.0, 0.2);

		// 곡면 제어점 설정 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);
		// 그리드를 이용한 곡면 드로잉 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
		// 선을 이용하여 그리드 연결 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glPointSize(2.0);







		if (!asd)
		{


			if (currentFrame < keyFrame / 2)
			{
				ctrlpoints[0][currentFrame2][1] += temp;
				ctrlpoints[1][currentFrame2][1] += temp;
				ctrlpoints[2][currentFrame2][1] += temp;


			}
			else if (currentFrame < keyFrame)
			{
				ctrlpoints[0][currentFrame2][1] -= temp;
				ctrlpoints[1][currentFrame2][1] -= temp;
				ctrlpoints[2][currentFrame2][1] -= temp;

			}
		}




		if (currentFrame >= keyFrame)
		{
			currentFrame = -1;
			currentFrame2 += 1;
		}

		if (currentFrame2 >= keyFrame2)
		{
			currentFrame2 = 0;

		}


		this->masterMatrixs->glLoadMasterMatrix();

	}

	void BezierCape::DrawBezierCape(float size)
	{
		ApplyMatrix();



		this->masterMatrixs->glLoadMasterMatrix();
	}




	//class Tunnel
	void Tunnel::DrawTunnel(float size, float height)
	{
		ApplyMatrix();



		this->size = size;
		this->Translate(-this->size * 3, 0, 0);

		this->SetFreeRotateYAxis(GLVector3(this->size * 3, 0, 0), GLVector3(this->size * 3, 1, 0));
		this->DrawCube(this->size, false, false);


		for (int i = 0; i < height; ++i)
		{
			this->Translate(0, this->size, 0);

			this->SetFreeRotateYAxis(GLVector3(this->size * 3, -this->size * (i + 1), 0), GLVector3(this->size * 3, -this->size * (i + 1) + 1, 0));
			this->DrawCube(this->size, false, false);
		}

		for (int i = 0; i < 6; ++i)
		{

			this->Translate(this->size, 0, 0);


			this->SetFreeRotateYAxis(GLVector3(this->size * 3 + (i + 1) * -this->size, -this->size * (height), 0), GLVector3(this->size * 3 + (i + 1) * -this->size, -this->size * (height)+1, 0));

			this->DrawCube(this->size, false, false);
		}

		for (int i = 0; i < height; ++i)
		{
			this->Translate(0, -this->size, 0);

			this->SetFreeRotateYAxis(GLVector3(this->size * 3 + 6 * -this->size, -this->size * (height), 0), GLVector3(this->size * 3 + 6 * -this->size, -this->size * (height)+1, 0));

			this->DrawCube(this->size, false, false);
		}


		this->Translate(-this->size * 3, 0, 0);




		this->masterMatrixs->glLoadMasterMatrix();
	}


	//class PhotonBomb
	void PhotonBomb::ThrowPhotonBomb(float impactPointY)
	{



		if (!this->objectActivate)
		{
			if (curFrame < keyFrame)
			{
				this->Scale(1 + 0.01 * curFrame, 1 + 0.01 * curFrame, 1 + 0.01 * curFrame);
				this->DrawSphere2(100, true, false, false);
				this->DrawSphere2(90, false, false, true);
				this->DrawSphere2(110, true, false, true);
				this->DrawCube(60, false, false);
				curFrame++;
			}

			return;
		}
		ApplyMatrix();



		this->Translate(0, vel, 0);
		this->DrawSphere2(100, false, false, false);

		vel += acc;

		if (this->Position().y < impactPointY)
			this->objectActivate = false;




		this->masterMatrixs->glLoadMasterMatrix();
	}

	//class TitleScreen

	void TitleScreen::DrawStarCursor(float size, GLuint texture)
	{
		ApplyMatrix();
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, this->alpha);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		for (i = 0; i < 4; i++)
		{
			//glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
			if (i == 3)
				glTexCoord2f(1, 1);
			else if (i == 2)
				glTexCoord2f(1, 0);
			else if (i == 1)
				glTexCoord2f(0, 0);
			else if (i == 0)
				glTexCoord2f(0, 1);
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		}
		glEnd();

		glColor3f(0.0, 0.0, 0.0);

		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 4; i++)
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		glEnd();

		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		this->masterMatrixs->glLoadMasterMatrix();
	}




	void TitleScreen::DrawQuitButton(float size, GLuint texture)
	{
		ApplyMatrix();
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, this->alpha);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		for (i = 0; i < 4; i++)
		{
			//glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
			if (i == 3)
				glTexCoord2f(1, 1);
			else if (i == 2)
				glTexCoord2f(1, 0);
			else if (i == 1)
				glTexCoord2f(0, 0);
			else if (i == 0)
				glTexCoord2f(0, 1);
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		}
		glEnd();

		glColor3f(0.0, 0.0, 0.0);

		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 4; i++)
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		glEnd();

		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		this->masterMatrixs->glLoadMasterMatrix();
	}

	void TitleScreen::DrawPlayButton(float size, GLuint texture)
	{
		ApplyMatrix();
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, this->alpha);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		for (i = 0; i < 4; i++)
		{
			//glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
			if (i == 3)
				glTexCoord2f(1, 1);
			else if (i == 2)
				glTexCoord2f(1, 0);
			else if (i == 1)
				glTexCoord2f(0, 0);
			else if (i == 0)
				glTexCoord2f(0, 1);
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		}
		glEnd();

		glColor3f(0.0, 0.0, 0.0);

		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 4; i++)
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		glEnd();

		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		this->masterMatrixs->glLoadMasterMatrix();
	}


	void TitleScreen::DrawTitleScreen(float size, GLuint texture)
	{
		ApplyMatrix();
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, this->alpha);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		for (i = 0; i < 4; i++)
		{
			//glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
			if (i == 3)
				glTexCoord2f(1, 1);
			else if (i == 2)
				glTexCoord2f(1, 0);
			else if (i == 1)
				glTexCoord2f(0, 0);
			else if (i == 0)
				glTexCoord2f(0, 1);
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		}
		glEnd();

		glColor3f(0.0, 0.0, 0.0);

		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 4; i++)
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		glEnd();

		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		this->masterMatrixs->glLoadMasterMatrix();
	}


	//class LogoScreen
	void LogoScreen::DrawLogoScreen(float size, GLuint texture)
	{
		ApplyMatrix();
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, this->alpha);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		for (i = 0; i < 4; i++)
		{
			//glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
			if (i == 3)
				glTexCoord2f(1, 1);
			else if (i == 2)
				glTexCoord2f(1, 0);
			else if (i == 1)
				glTexCoord2f(0, 0);
			else if (i == 0)
				glTexCoord2f(0, 1);
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		}
		glEnd();

		glColor3f(0.0, 0.0, 0.0);

		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 4; i++)
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		glEnd();

		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		this->masterMatrixs->glLoadMasterMatrix();
	}




	//class ScoreUI
	void ScoreUI::DrawScoreUI(float size, GLuint texture)
	{
		ApplyMatrix();
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		const GLfloat cube_vertices[8][3] =
		{
		{ 1.0, 1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ -1.0, -1.0, 1.0 },
		{ -1.0, 1.0, 1.0 },
		{ 1.0, 1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ -1.0, -1.0, -1.0 },
		{ -1.0, 1.0, -1.0 }
		};
		const short cube_faces[6][4] =
		{
		{ 3, 2, 1, 0 },
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 3, 0, 4, 7 },
		{ 1, 2, 6, 5 },
		{ 4, 5, 6, 7 }
		};
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, this->alpha);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		for (i = 0; i < 4; i++)
		{
			//glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
			if (i == 3)
				glTexCoord2f(1, 1);
			else if (i == 2)
				glTexCoord2f(1, 0);
			else if (i == 1)
				glTexCoord2f(0, 0);
			else if (i == 0)
				glTexCoord2f(0, 1);
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		}
		glEnd();

		glColor3f(0.0, 0.0, 0.0);

		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 4; i++)
			glVertex3f(cube_vertices[cube_faces[0][i]][0] * size, cube_vertices[cube_faces[0][i]][1] * size, 0);
		glEnd();



		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		this->masterMatrixs->glLoadMasterMatrix();



	}

}

