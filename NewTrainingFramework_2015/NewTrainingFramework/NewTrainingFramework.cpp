// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tchar.h>
#include <cstdio>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"



float angle = 0;
float step = 0.1;
float totalTime = 0;

GLuint vboId;
Shaders myShaders;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	//triangle data (heap)
	Vertex verticesData[3];

	verticesData[0].pos.x =  0.0f;  verticesData[0].pos.y =  0.5f;  verticesData[0].pos.z =  0.0f;
	verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z =  0.0f;
	verticesData[2].pos.x =  0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;

	verticesData[0].color.x = 1.0f;  verticesData[0].color.y = 0.0f;  verticesData[0].color.z = 0.0f;
	verticesData[1].color.x = 0.0f;  verticesData[1].color.y = 1.0f;  verticesData[1].color.z = 0.0f;
	verticesData[2].color.x = 0.0f;  verticesData[2].color.y = 0.0f;  verticesData[2].color.z = 1.0f;

	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	
	
	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (myShaders.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.colorAttribute);
		glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)));
	}

	Matrix modelMatrix;
	Matrix MVP;
	modelMatrix.SetRotationZ(angle);
	
	MVP = modelMatrix* camera.viewMatrix * camera.perspectiveMatrix;

	if (myShaders.matrixUniform != -1)
	{
		glUniformMatrix4fv(myShaders.matrixUniform, 1, GL_FALSE, (float*)(&modelMatrix.m[0][0]));
	}

	if (myShaders.mvpUniform != -1) {
		glUniformMatrix4fv(myShaders.mvpUniform, 1, GL_FALSE, (float*)&MVP.m[0][0]);
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );

}

void Update ( ESContext *esContext, float deltaTime )
{
	
	totalTime += deltaTime;
	if (totalTime > Globals::frameTime) {
		camera.deltaTime = Globals::frameTime;
		totalTime -= Globals::frameTime;
		//angle += step;
		//if (angle > 2 * PI)
			//angle = angle - 2 * PI;
	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
    //if (bIsPressed)
		switch (key){
		case 'w': case 'W':
			camera.moveOz(-1);
			break;
		case 's': case 'S':
			camera.moveOz(1);
			break;
		case 'a': case 'A':
			camera.moveOx(1);
			break;
		case 'd': case 'D':
			camera.moveOx(-1);
			break;
		case 'q': case 'Q':
			camera.moveOy(1);
			break;
		case 'e': case 'E':
			camera.moveOy(-1);
			break;

		case VK_UP:
			camera.rotateOx(1);
			break;
		case VK_DOWN:
			camera.rotateOx(-1);
			break;
		case VK_LEFT:
			camera.rotateOy(-1);
			break;
		case VK_RIGHT:
			camera.rotateOy(1);
			break;
		case 'o': case 'O':
			camera.rotateOz(-1);
			break;
		case 'p': case 'P':
			camera.rotateOz(1);
			break;
		}
		
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();

	
	return 0;
}

