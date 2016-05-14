/*

CGE. Camomile Game Engine.

Copyright (C) 2016 slughnaz
 
CGE is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

CGE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
   
You should have received a copy of the GNU General Public License
along with CGE.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Mathematical structures */

const float CGE_PI = 3.14159265f;

struct CGE_V3
{
	float x;
	float y;
	float z;
};

typedef struct CGE_V3 CGE_V3;

struct CGE_V4
{
	float x;
	float y;
	float z;
	float w;
};

typedef struct CGE_V4 CGE_V4;

struct CGE_M4
{
	float m11;
	float m12;
	float m13;
	float m14;
	float m21;
	float m22;
	float m23;
	float m24;
	float m31;
	float m32;
	float m33;
	float m34;
	float m41;
	float m42;
	float m43;
	float m44;
};

typedef struct CGE_M4 CGE_M4;


/* Renderer structures */

struct CGE_Point
{
	CGE_V3 position;
	SDL_Color color;
};

typedef struct CGE_Point CGE_Point;

struct CGE_Line
{
	CGE_Point point1;
	CGE_Point point2;
};

typedef struct CGE_Line CGE_Line;


/* Game engine structures */

struct CGE_LookAt
{
	CGE_V3 left;
	CGE_V3 up;	
	CGE_V3 forward;
};

typedef struct CGE_LookAt CGE_LookAt;

struct CGE_Viewport
{
	float x;
	float y;
	float w;
	float h;
};

typedef struct CGE_Viewport CGE_Viewport;

struct CGE_EngineStatesInputsPhysicals
{
	int CGE_KeyQuit;
	int CGE_KeyLeft;
	int CGE_KeyRight;
	int CGE_KeyUp;
	int CGE_KeyDown;
	int CGE_KeyA;
	int CGE_KeyD;
	int CGE_KeyW;
	int CGE_KeyS;
	int CGE_KeyQ;
	int CGE_KeyE;
};

typedef struct CGE_EngineStatesInputsPhysicals CGE_EngineStatesInputsPhysicals;

struct CGE_EngineStatesInputsLogicals
{
	int CGE_Quit;
	float CGE_Yaw;
	float CGE_Pitch;
	float CGE_Roll;
	float CGE_AxisX;
	float CGE_AxisY;
	float CGE_AxisZ;
	float CGE_Advance;
	float CGE_Strafe;
};

typedef struct CGE_EngineStatesInputsLogicals CGE_EngineStatesInputsLogicals;

struct CGE_EngineStatesInputs
{
	CGE_EngineStatesInputsPhysicals physicals;
	CGE_EngineStatesInputsLogicals logicals;
};

typedef struct CGE_EngineStatesInputs CGE_EngineStatesInputs;

struct CGE_EngineStatesTimers
{
	Uint32 absolute;
	Uint32 elapsed;
	int fps;
	int fpsFrames;
	int fpsTicks;
};

typedef struct CGE_EngineStatesTimers CGE_EngineStatesTimers;

enum CGE_EngineStatesStatus
{
	CGE_ENGINESTATESSTATUS_STARTED = 0,
	CGE_ENGINESTATESSTATUS_PAUSED,
	CGE_ENGINESTATESSTATUS_STOPPED
};

typedef enum CGE_EngineStatesStatus CGE_EngineStatesStatus;

struct CGE_EngineStates
{
	CGE_EngineStatesInputs inputs;
	CGE_EngineStatesTimers timers;
	CGE_EngineStatesStatus status;
};

typedef struct CGE_EngineStates CGE_EngineStates;

struct CGE_Camera
{
	CGE_V3 position;
	CGE_V3 target;
	CGE_V3 axis;
	CGE_M4 view;
	CGE_M4 projection;
};

typedef struct CGE_Camera CGE_Camera;

struct CGE_EngineDevice
{
	CGE_M4 model;
	CGE_M4 view;
	CGE_M4 projection;
	CGE_Viewport viewport;
};

typedef struct CGE_EngineDevice CGE_EngineDevice;

struct CGE_Engine
{
	SDL_Surface *screen;
	TTF_Font *font;
	CGE_EngineStates states;
	CGE_EngineDevice device;
	CGE_Camera camera;
	CGE_Point point[4];
	CGE_Line axe[3];
};

typedef struct CGE_Engine CGE_Engine;

enum CGE_EXITCODE
{
	CGE_OK = 0,
	CGE_ERR
};

typedef enum CGE_EXITCODE CGE_EXITCODE;


/* Mathematical functions definitions */

float CGE_DegToRad(float);
float CGE_V3Length(CGE_V3);
float CGE_V4Length(CGE_V4);

CGE_V3 CGE_V3New(float, float, float);
CGE_V4 CGE_V4New(float, float, float, float);

CGE_M4 CGE_M4Identity();
CGE_M4 CGE_M4Rotate(float, float, float, float);
CGE_M4 CGE_M4Scale(float, float, float);
CGE_M4 CGE_M4Translate(float, float, float);
CGE_M4 CGE_M4Transpose(CGE_M4);
CGE_M4 CGE_M4Perspective(float, float, float, float, float, float);
CGE_M4 CGE_M4Orthographic(float, float, float, float, float, float);

float CGE_V3V3Mul(CGE_V3, CGE_V3);
float CGE_V4V4Mul(CGE_V4, CGE_V4);
CGE_V3 CGE_V3V3Cross(CGE_V3, CGE_V3);
CGE_V3 CGE_V3V3Add(CGE_V3, CGE_V3);
CGE_V4 CGE_V4V4Add(CGE_V4, CGE_V4);
CGE_V3 CGE_V3V3Sub(CGE_V3, CGE_V3);
CGE_V4 CGE_V4V4Sub(CGE_V4, CGE_V4);
CGE_V3 CGE_V3ScalarMul(CGE_V3, float);
CGE_V4 CGE_V4ScalarMul(CGE_V4, float);
CGE_V4 CGE_M4V4Mul(CGE_M4, CGE_V4);
CGE_M4 CGE_M4M4Mul(CGE_M4, CGE_M4);
CGE_V3 CGE_V3Normalize(CGE_V3);
CGE_V4 CGE_V4Normalize(CGE_V4);

CGE_M4 CGE_M4Model(CGE_V3, CGE_V3);
CGE_M4 CGE_M4View(CGE_V3, CGE_V3);
CGE_LookAt CGE_LookAtCalculate(CGE_V3, CGE_V3);
CGE_Viewport CGE_ViewportNew(float, float, float, float);


/* Renderer functions definitions */

SDL_Color CGE_ColorNew(Uint8, Uint8, Uint8); 
CGE_Point CGE_PointNew(float, float, float, Uint8, Uint8, Uint8);
CGE_Line CGE_LineNew(CGE_Point, CGE_Point);
CGE_V3 CGE_V3Clip(CGE_V4);
CGE_V4 CGE_V4Clip(CGE_V4, CGE_V4);
CGE_EXITCODE CGE_LineClip(CGE_V4 *, CGE_V4 *);

CGE_EXITCODE CGE_DrawPoint(CGE_Engine *, CGE_Point);
CGE_EXITCODE CGE_DrawLine(CGE_Engine *, CGE_Line, int);
CGE_EXITCODE CGE_DrawGrid(CGE_Engine *, CGE_V3, float);
CGE_EXITCODE CGE_DrawPixel(SDL_Surface *, CGE_Viewport, CGE_V3, Uint8, Uint8, Uint8);
CGE_EXITCODE CGE_DrawTextSolid(CGE_Engine *, char *, CGE_V3, SDL_Color);
CGE_EXITCODE CGE_DrawMatrix(CGE_Engine *, CGE_M4, CGE_V3, SDL_Color);
CGE_V3 CGE_V3ViewportTransform(CGE_Viewport, CGE_V3);


/* Game engine functions definitions */

CGE_EXITCODE CGE_Init(CGE_Engine **);
CGE_EXITCODE CGE_GetInputs(CGE_Engine *);
CGE_EXITCODE CGE_MapInputsPhysicals(CGE_Engine *, SDL_Event);
CGE_EXITCODE CGE_MapInputsLogicals(CGE_Engine *);
CGE_EXITCODE CGE_GetTimers(CGE_Engine *);
CGE_EXITCODE CGE_Move(CGE_Engine *);
CGE_EXITCODE CGE_Render(CGE_Engine *);
CGE_EXITCODE CGE_DeInit(CGE_Engine *);
CGE_EXITCODE CGE_SetCamera(CGE_Engine *, CGE_V3, CGE_V3);


/* Debugger functions definitions*/

CGE_EXITCODE CGE_M4Print(CGE_M4, char *);
CGE_EXITCODE CGE_V3Print(CGE_V3, char *);
CGE_EXITCODE CGE_V4Print(CGE_V4, char *);


/* Mathematical functions implementations */

float CGE_DegToRad(float degree)
{
	return degree * CGE_PI / 180.0f;
}

float CGE_V3Length(CGE_V3 v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

float CGE_V4Length(CGE_V4 v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

CGE_V3 CGE_V3New(float x, float y, float z)
{
	CGE_V3 newv;
	
	newv.x = x;
	newv.y = y;
	newv.z = z; 

	return newv;
}

CGE_V4 CGE_V4New(float x, float y, float z, float w)
{
	CGE_V4 newv;
	
	newv.x = x;
	newv.y = y;
	newv.z = z;
	newv.w = w;

	return newv;
}

CGE_M4 CGE_M4Identity()
{
	CGE_M4 newm;

	newm.m11 = 1.0f;
	newm.m12 = 0.0f;
	newm.m13 = 0.0f;
	newm.m14 = 0.0f;
	newm.m21 = 0.0f;
	newm.m22 = 1.0f;
	newm.m23 = 0.0f;
	newm.m24 = 0.0f;
	newm.m31 = 0.0f;
	newm.m32 = 0.0f;
	newm.m33 = 1.0f;
	newm.m34 = 0.0f;
	newm.m41 = 0.0f;
	newm.m42 = 0.0f;
	newm.m43 = 0.0f;
	newm.m44 = 1.0f;

	return newm;
}

CGE_M4 CGE_M4Rotate(float a, float x, float y, float z)
{
	CGE_M4 newm;
	float arad;
	float cosa;
	float sina;
	float xx;
	float xy;
	float xz;
	float yy;
	float yz;
	float zz;

	arad = CGE_DegToRad(a);
	/*printf("arad %f\n", arad);*/
	cosa = cos(arad);
	sina = sin(arad);
	/*printf("cosa %f\n", cosa);*/
	/*printf("sina %f\n", sina);*/
	xx = x * x;
	xy = x * y;
	xz = x * z;
	yy = y * y;
	yz = y * z;
	zz = z * z;

	newm.m11 = xx * (1.0f - cosa) + cosa;
	newm.m12 = xy * (1.0f - cosa) - sina * z;
	newm.m13 = xz * (1.0f - cosa) + sina * y;
	newm.m14 = 0.0f;
	newm.m21 = xy * (1.0f - cosa) + sina * z;
	newm.m22 = yy * (1.0f - cosa) + cosa;
	newm.m23 = yz * (1.0f - cosa) - sina * x;
	newm.m24 = 0.0f;
	newm.m31 = xz * (1.0f - cosa) - sina * y;
	newm.m32 = yz * (1.0f - cosa) + sina * x;
	newm.m33 = zz * (1.0f - cosa) + cosa;
	newm.m34 = 0.0f;
	newm.m41 = 0.0f;
	newm.m42 = 0.0f;
	newm.m43 = 0.0f;
	newm.m44 = 1.0f;

	return newm;
}

CGE_M4 CGE_M4Scale(float x, float y, float z)
{
	CGE_M4 newm;

	newm.m11 = x;
	newm.m12 = 0.0f;
	newm.m13 = 0.0f;
	newm.m14 = 0.0f;
	newm.m21 = 0.0f;
	newm.m22 = y;
	newm.m23 = 0.0f;
	newm.m24 = 0.0f;
	newm.m31 = 0.0f;
	newm.m32 = 0.0f;
	newm.m33 = z;
	newm.m34 = 0.0f;
	newm.m41 = 0.0f;
	newm.m42 = 0.0f;
	newm.m43 = 0.0f;
	newm.m44 = 1.0f;

	return newm;
}

CGE_M4 CGE_M4Translate(float x, float y, float z)
{
	CGE_M4 newm;

	newm.m11 = 1.0f;
	newm.m12 = 0.0f;
	newm.m13 = 0.0f;
	newm.m14 = x;
	newm.m21 = 0.0f;
	newm.m22 = 1.0f;
	newm.m23 = 0.0f;
	newm.m24 = y;
	newm.m31 = 0.0f;
	newm.m32 = 0.0f;
	newm.m33 = 1.0f;
	newm.m34 = z;
	newm.m41 = 0.0f;
	newm.m42 = 0.0f;
	newm.m43 = 0.0f;
	newm.m44 = 1.0f;

	return newm;
}

CGE_M4 CGE_M4Transpose(CGE_M4 m)
{
	CGE_M4 newm;

	newm.m11 = m.m11;
	newm.m12 = m.m21;
	newm.m13 = m.m31;
	newm.m14 = m.m41;
	newm.m21 = m.m12;
	newm.m22 = m.m22;
	newm.m23 = m.m32;
	newm.m24 = m.m42;
	newm.m31 = m.m13;
	newm.m32 = m.m23;
	newm.m33 = m.m33;
	newm.m34 = m.m43;
	newm.m41 = m.m14;
	newm.m42 = m.m24;
	newm.m43 = m.m34;
	newm.m44 = m.m44;

	return newm;  
}

CGE_M4 CGE_M4Perspective(float l, float r, float b, float t, float n, float f)
{
	CGE_M4 newm;

	newm.m11 = 2 * n / (r - l);
	newm.m12 = 0.0f;
	newm.m13 = (r + l) / (r - l);
	newm.m14 = 0.0f;
	newm.m21 = 0.0f;
	newm.m22 = 2 * n / (t - b);
	newm.m23 = (t + b) / (t - b);
	newm.m24 = 0.0f;
	newm.m31 = 0.0f;
	newm.m32 = 0.0f;
	newm.m33 = - (f + n) / (f - n);
	newm.m34 = - (2 * f * n) / (f - n);
	newm.m41 = 0.0f;
	newm.m42 = 0.0f;
	newm.m43 = -1.0f;
	newm.m44 = 0.0f;

	return newm;
}

CGE_M4 CGE_M4Orthographic(float l, float r, float b, float t, float n, float f)
{
	CGE_M4 newm;

	newm.m11 = 2 / (r - l);
	newm.m12 = 0.0f;
	newm.m13 = 0.0f;
	newm.m14 = - (r + l) / (r - l);
	newm.m21 = 0.0f;
	newm.m22 = 2 / (t - b);
	newm.m23 = 0.0f;
	newm.m24 = - (t + b) / (t - b);
	newm.m31 = 0.0f;
	newm.m32 = 0.0f;
	newm.m33 = - 2 / (f - n);
	newm.m34 = - (f + n) / (f - n);
	newm.m41 = 0.0f;
	newm.m42 = 0.0f;
	newm.m43 = 0.0f;
	newm.m44 = 1.0f;

	return newm;
}

float CGE_V3V3Mul(CGE_V3 v1, CGE_V3 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float CGE_V4V4Mul(CGE_V4 v1, CGE_V4 v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

CGE_V3 CGE_V3V3Cross(CGE_V3 v1, CGE_V3 v2)
{
	CGE_V3 newv;

	newv.x = (v1.y * v2.z) - (v1.z * v2.y);
	newv.y = (v1.z * v2.x) - (v1.x * v2.z);
	newv.z = (v1.x * v2.y) - (v1.y * v2.x);

	return newv;
}

CGE_V3 CGE_V3V3Add(CGE_V3 v1, CGE_V3 v2)
{
	CGE_V3 newv;

	newv.x = v1.x + v2.x;
	newv.y = v1.y + v2.y;
	newv.z = v1.z + v2.z;

	return newv;
}

CGE_V4 CGE_V4V4Add(CGE_V4 v1, CGE_V4 v2)
{
	CGE_V4 newv;

	newv.x = v1.x + v2.x;
	newv.y = v1.y + v2.y;
	newv.z = v1.z + v2.z;
	newv.w = v1.w + v2.w;

	return newv;
}

CGE_V3 CGE_V3V3Sub(CGE_V3 v1, CGE_V3 v2)
{
	CGE_V3 newv;

	newv.x = v1.x - v2.x;
	newv.y = v1.y - v2.y;
	newv.z = v1.z - v2.z;

	return newv;
}

CGE_V4 CGE_V4V4Sub(CGE_V4 v1, CGE_V4 v2)
{
	CGE_V4 newv;

	newv.x = v1.x - v2.x;
	newv.y = v1.y - v2.y;
	newv.z = v1.z - v2.z;
	newv.w = v1.w - v2.w;

	return newv;
}

CGE_V3 CGE_V3ScalarMul(CGE_V3 v, float s)
{
	CGE_V3 newv;

	newv.x = v.x * s;
	newv.y = v.y * s;
	newv.z = v.z * s;

	return newv;
}

CGE_V4 CGE_V4ScalarMul(CGE_V4 v, float s)
{
	CGE_V4 newv;

	newv.x = v.x * s;
	newv.y = v.y * s;
	newv.z = v.z * s;
	newv.w = v.w * s;

	return newv;
}

CGE_V4 CGE_M4V4Mul(CGE_M4 m, CGE_V4 v)
{
	CGE_V4 newv;

	newv.x = (m.m11 * v.x) + (m.m12 * v.y) + (m.m13 * v.z) + (m.m14 * v.w);
	newv.y = (m.m21 * v.x) + (m.m22 * v.y) + (m.m23 * v.z) + (m.m24 * v.w);
	newv.z = (m.m31 * v.x) + (m.m32 * v.y) + (m.m33 * v.z) + (m.m34 * v.w);
	newv.w = (m.m41 * v.x) + (m.m42 * v.y) + (m.m43 * v.z) + (m.m44 * v.w);

	return newv;
}

CGE_M4 CGE_M4M4Mul(CGE_M4 m1, CGE_M4 m2)
{
	CGE_M4 newm;

	newm.m11 = (m1.m11 * m2.m11) + (m1.m12 * m2.m21) + (m1.m13 * m2.m31) + (m1.m14 * m2.m41);
	newm.m12 = (m1.m11 * m2.m12) + (m1.m12 * m2.m22) + (m1.m13 * m2.m32) + (m1.m14 * m2.m42);
	newm.m13 = (m1.m11 * m2.m13) + (m1.m12 * m2.m23) + (m1.m13 * m2.m33) + (m1.m14 * m2.m43);
	newm.m14 = (m1.m11 * m2.m14) + (m1.m12 * m2.m24) + (m1.m13 * m2.m34) + (m1.m14 * m2.m44);
	newm.m21 = (m1.m21 * m2.m11) + (m1.m22 * m2.m21) + (m1.m23 * m2.m31) + (m1.m24 * m2.m41);
	newm.m22 = (m1.m21 * m2.m12) + (m1.m22 * m2.m22) + (m1.m23 * m2.m32) + (m1.m24 * m2.m42);
	newm.m23 = (m1.m21 * m2.m13) + (m1.m22 * m2.m23) + (m1.m23 * m2.m33) + (m1.m24 * m2.m43);
	newm.m24 = (m1.m21 * m2.m14) + (m1.m22 * m2.m24) + (m1.m23 * m2.m34) + (m1.m24 * m2.m44);
	newm.m31 = (m1.m31 * m2.m11) + (m1.m32 * m2.m21) + (m1.m33 * m2.m31) + (m1.m34 * m2.m41);
	newm.m32 = (m1.m31 * m2.m12) + (m1.m32 * m2.m22) + (m1.m33 * m2.m32) + (m1.m34 * m2.m42);
	newm.m33 = (m1.m31 * m2.m13) + (m1.m32 * m2.m23) + (m1.m33 * m2.m33) + (m1.m34 * m2.m43);
	newm.m34 = (m1.m31 * m2.m14) + (m1.m32 * m2.m24) + (m1.m33 * m2.m34) + (m1.m34 * m2.m44);
	newm.m41 = (m1.m41 * m2.m11) + (m1.m42 * m2.m21) + (m1.m43 * m2.m31) + (m1.m44 * m2.m41);
	newm.m42 = (m1.m41 * m2.m12) + (m1.m42 * m2.m22) + (m1.m43 * m2.m32) + (m1.m44 * m2.m42);
	newm.m43 = (m1.m41 * m2.m13) + (m1.m42 * m2.m23) + (m1.m43 * m2.m33) + (m1.m44 * m2.m43);
	newm.m44 = (m1.m41 * m2.m14) + (m1.m42 * m2.m24) + (m1.m43 * m2.m34) + (m1.m44 * m2.m44);

	return newm;
}

CGE_V3 CGE_V3Normalize(CGE_V3 v)
{
	float length;
	float invLength;
	
	length = CGE_V3Length(v);

	if(length != 0.0f)
	{
		invLength = 1.0f / length;	
	}
	else
	{
		invLength = 0.0f;
	}

	v.x *= invLength;
	v.y *= invLength;
	v.z *= invLength;
	
	return v;
}

CGE_V4 CGE_V4Normalize(CGE_V4 v)
{
	float length;
	float invLength;
	
	length = CGE_V4Length(v);

	if(length != 0.0f)
	{
		invLength = 1.0f / length;	
	}
	else
	{
		invLength = 0.0f;
	}

	v.x *= invLength;
	v.y *= invLength;
	v.z *= invLength;
	v.w *= invLength;
	
	return v;
}

CGE_M4 CGE_M4Model(CGE_V3 position, CGE_V3 target)
{
	CGE_M4 newm;
	CGE_LookAt lookAt;

	lookAt = CGE_LookAtCalculate(position, target);
	
	newm = CGE_M4Identity();
	newm.m11 = lookAt.left.x;
	newm.m21 = lookAt.left.y;
	newm.m31 = lookAt.left.z;
	newm.m12 = lookAt.up.x;
	newm.m22 = lookAt.up.y;
	newm.m32 = lookAt.up.z;
	newm.m13 = lookAt.forward.x;
	newm.m23 = lookAt.forward.y;
	newm.m33 = lookAt.forward.z;
	newm.m14 = position.x;
	newm.m24 = position.y;
	newm.m34 = position.z;

	return newm;
}

CGE_M4 CGE_M4View(CGE_V3 position, CGE_V3 axis)
{
	CGE_M4 newm;

	newm = CGE_M4Identity();
	/*CGE_M4Print(newm, "Identity");*/
	newm = CGE_M4M4Mul(CGE_M4Translate(-position.x, -position.y, -position.z), newm);
	/*CGE_M4Print(newm, "Translate");*/
	newm = CGE_M4M4Mul(CGE_M4Rotate(-axis.y, 0.0f, 1.0f, 0.0f), newm);
	/*CGE_M4Print(newm, "RotateY");*/
	newm = CGE_M4M4Mul(CGE_M4Rotate(-axis.x, 1.0f, 0.0f, 0.0f), newm);
	/*CGE_M4Print(newm, "RotateX");*/
 	newm = CGE_M4M4Mul(CGE_M4Rotate(-axis.z, 0.0f, 0.0f, 1.0f), newm);
	/*CGE_M4Print(newm, "RotateZ");*/

/*	
	CGE_LookAt lookAt;

	lookAt = CGE_LookAtCalculate(target, position);	

	lookAt.left = CGE_V3New(0.0f, 0.0f, 1.0f);
	lookAt.up = CGE_V3New(0.0f, 1.0f, 0.0f);
	lookAt.forward = CGE_V3New(-1.0f, 0.0f, 0.0f);
	
	newm = CGE_M4Identity();
	newm.m11 = lookAt.left.x;
	newm.m21 = lookAt.left.y;
	newm.m31 = lookAt.left.z;
	newm.m12 = lookAt.up.x;
	newm.m22 = lookAt.up.y;
	newm.m32 = lookAt.up.z;
	newm.m13 = lookAt.forward.x;
	newm.m23 = lookAt.forward.y;
	newm.m33 = lookAt.forward.z;
	newm.m14 = -position.x;
	newm.m24 = -position.y;
	newm.m34 = -position.z;
	CGE_M4Print(newm, "lookat");
*/
	return newm;

}

CGE_LookAt CGE_LookAtCalculate(CGE_V3 position, CGE_V3 target)
{
	CGE_LookAt lookAt;

	lookAt.forward = CGE_V3V3Sub(target, position);
	lookAt.forward = CGE_V3Normalize(lookAt.forward); 

	lookAt.up = CGE_V3New(0.0f, 1.0f, 0.0f);
	lookAt.left = CGE_V3V3Cross(lookAt.up, lookAt.forward);
	lookAt.left = CGE_V3Normalize(lookAt.left);

	lookAt.up = CGE_V3V3Cross(lookAt.forward, lookAt.left);
	lookAt.up = CGE_V3Normalize(lookAt.up);

	return lookAt;
}

CGE_Viewport CGE_ViewportNew(float x, float y, float w, float h)
{
	CGE_Viewport newv;

	newv.x = x;
	newv.y = y;
	newv.w = w;
	newv.h = h;

	return newv;
}


/* Renderer functions implementations */

SDL_Color CGE_ColorNew(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Color newc;

	newc.r = r;
	newc.g = g;
	newc.b = b;

	return newc;
}

CGE_Point CGE_PointNew(float x, float y, float z, Uint8 r, Uint8 g, Uint8 b)
{
	CGE_Point newp;

	newp.position = CGE_V3New(x, y, z);
	newp.color = CGE_ColorNew(r, g, b);

	return newp;
}

CGE_Line CGE_LineNew(CGE_Point point1, CGE_Point point2)
{
	CGE_Line newl;

	newl.point1 = point1;
	newl.point2 = point2;

	return newl;
}

CGE_V3 CGE_V3Clip(CGE_V4 p)
{
	CGE_V3 newp;

	newp.x = p.x / p.w;
	newp.y = p.y / p.w;
	newp.z = p.z / p.w;

	return newp;
}

CGE_V4 CGE_V4Clip(CGE_V4 p1, CGE_V4 p2)
{
	CGE_V4 abs;
	CGE_V4 newp;
	float k;
	
	newp = p1;

	abs.x = fabs(p1.x);
	abs.y = fabs(p1.y);
	abs.z = fabs(p1.z);
	abs.w = fabs(p1.w);
 
	/* To clip or not to clip */
	if(abs.x > abs.w || abs.y > abs.w || abs.z > abs.w)
	{				
		/* Get the most out of space axis for value k */
		k = abs.x;
		if (abs.y > k)
		{
			k = abs.y;
		}
		if (abs.z > k)
		{
			k = abs.z;
		}
	
		k = k - abs.w;

		newp = CGE_V4V4Sub(p2, p1);
		newp = CGE_V4Normalize(newp);
		newp = CGE_V4V4Sub(p1, CGE_V4ScalarMul(newp, k));
		
	}

	return newp;
}

CGE_EXITCODE CGE_LineClip(CGE_V4 *v1, CGE_V4 *v2)
{
	
	if(v1->w <= 0.0f)
	{
		v1->x = v2->x;
		v1->y = v2->y;
		v1->z = v2->z;
		v1->w = v2->w;
	}
	
	if(v2->w <= 0.0f)
	{
		v1->x = v2->x = 1.0f;
		v1->y = v2->y = 1.0f;
		v1->z = v2->z = 1.0f;
		v1->w = v2->w = 1.0f;
	}	

	return CGE_OK;
}

CGE_EXITCODE CGE_DrawPoint(CGE_Engine *engine, CGE_Point p)
{	
	CGE_V4 newp;
	CGE_V3 newc;
	
	newp = CGE_V4New(p.position.x, p.position.y, p.position.z, 1.0f);	
	newp = CGE_M4V4Mul(engine->device.view, newp);
	newp = CGE_M4V4Mul(engine->device.projection, newp);
	newc = CGE_V3Clip(newp);

	if(newc.x >= -1.0f && newc.x <= 1.0f && newc.y >= -1.0f && newc.y <= 1.0f && newc.z >= -1.0f && newc.z <= 1.0f)
	{
		newc = CGE_V3ViewportTransform(engine->device.viewport, newc);
		CGE_DrawPixel(engine->screen, engine->device.viewport, newc, p.color.r, p.color.g, p.color.b);
	}

	return CGE_OK;
}

CGE_EXITCODE CGE_DrawLine(CGE_Engine *engine, CGE_Line l, int debug)
{	
	CGE_V4 newp1;
	CGE_V3 newc1;
	CGE_V4 newp2;
	CGE_V3 newc2;
	CGE_V3 delta;
	char debugtext[255];

	newp1 = CGE_V4New(l.point1.position.x, l.point1.position.y, l.point1.position.z, 1.0f);
	newp2 = CGE_V4New(l.point2.position.x, l.point2.position.y, l.point2.position.z, 1.0f);

	if (debug == 1)
	{	
		CGE_DrawTextSolid(engine, "P1(x, y, z)", CGE_V3New(0.0f, 0.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp1.x);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(200.0f, 0.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp1.y);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(300.0f, 0.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp1.z);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(400.0f, 0.0f, 0.0f), CGE_ColorNew(255, 255, 255));

		CGE_DrawTextSolid(engine, "P2(x, y, z)", CGE_V3New(0.0f, 80.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp2.x);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(200.0f, 80.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp2.y);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(300.0f, 80.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp2.z);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(400.0f, 80.0f, 0.0f), CGE_ColorNew(255, 255, 255));
	}

	newp1 = CGE_M4V4Mul(engine->device.view, newp1);
	newp2 = CGE_M4V4Mul(engine->device.view, newp2);

	newp1 = CGE_M4V4Mul(engine->device.projection, newp1);
	newp2 = CGE_M4V4Mul(engine->device.projection, newp2);

	if(debug == 1)
	{
		CGE_DrawTextSolid(engine, "Clipped (x, y, z, w)", CGE_V3New(0.0f, 16.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp1.x);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(200.0f, 16.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp1.y);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(300.0f, 16.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp1.z);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(400.0f, 16.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp1.w);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(500.0f, 16.0f, 0.0f), CGE_ColorNew(255, 255, 255));

		CGE_DrawTextSolid(engine, "Clipped (x, y, z, w)", CGE_V3New(0.0f, 96.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp2.x);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(200.0f, 96.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp2.y);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(300.0f, 96.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp2.z);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(400.0f, 96.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newp2.w);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(500.0f, 96.0f, 0.0f), CGE_ColorNew(255, 255, 255));
	}

/*
	newp1 = CGE_V4Clip(newp1, newp2);
	newp2 = CGE_V4Clip(newp2, newp1);
*/

	CGE_LineClip(&newp1, &newp2);

	newc1 = CGE_V3Clip(newp1);
	newc2 = CGE_V3Clip(newp2);

	if(debug == 1)
	{
		CGE_DrawTextSolid(engine, "Normalized (x, y, z)", CGE_V3New(0.0f, 32.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc1.x);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(200.0f, 32.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc1.y);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(300.0f, 32.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc1.z);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(400.0f, 32.0f, 0.0f), CGE_ColorNew(255, 255, 255));

		CGE_DrawTextSolid(engine, "Normalized (x, y, z)", CGE_V3New(0.0f, 112.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc2.x);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(200.0f, 112.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc2.y);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(300.0f, 112.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc2.z);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(400.0f, 112.0f, 0.0f), CGE_ColorNew(255, 255, 255));
	}

	newc1 = CGE_V3ViewportTransform(engine->device.viewport, newc1);
	newc2 = CGE_V3ViewportTransform(engine->device.viewport, newc2);

	if(debug == 1)
	{
		CGE_DrawTextSolid(engine, "Viewport (x, y, z)", CGE_V3New(0.0f, 48.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc1.x);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(200.0f, 48.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc1.y);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(300.0f, 48.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc1.z);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(400.0f, 48.0f, 0.0f), CGE_ColorNew(255, 255, 255));

		CGE_DrawTextSolid(engine, "Viewport (x, y, z)", CGE_V3New(0.0f, 128.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc2.x);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(200.0f, 128.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc2.y);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(300.0f, 128.0f, 0.0f), CGE_ColorNew(255, 255, 255));
		sprintf(debugtext, "%f", newc2.z);
		CGE_DrawTextSolid(engine, debugtext, CGE_V3New(400.0f, 128.0f, 0.0f), CGE_ColorNew(255, 255, 255));
	}
		

	delta.x = newc2.x - newc1.x;
	delta.y = newc2.y - newc1.y;

	if(delta.x == 0.0f && delta.y == 0.0f)
	{
		CGE_DrawPixel(engine->screen, engine->device.viewport, newc1, l.point1.color.r, l.point1.color.g, l.point1.color.b);
		return CGE_OK;
	}

	if(fabs(delta.x) > fabs(delta.y))
	{
		float xmin;
		float xmax;
		float slope;
		float newx;

		if(newc1.x < newc2.x)
		{
			xmin = newc1.x;
			xmax = newc2.x;
		}
		else
		{
			xmin = newc2.x;
			xmax = newc1.x;
		}
	
		if(xmin < engine->device.viewport.x)
		{
			xmin = engine->device.viewport.x;
		}
		if(xmax > (engine->device.viewport.x + engine->device.viewport.w))
		{
			xmax = engine->device.viewport.x + engine->device.viewport.w;
		}
	
		slope = delta.y / delta.x;	
		for(newx = xmin; newx <= xmax; newx += 1.0f)
		{
			CGE_V3 newpoint;
			float newy;
			
			newy = newc1.y + ((newx - newc1.x) * slope);
			newpoint.x = newx;
			newpoint.y = newy;
			CGE_DrawPixel(engine->screen, engine->device.viewport, newpoint, l.point1.color.r, l.point1.color.g, l.point1.color.b);
		}		
	
	}
	else
	{
		float ymin;
		float ymax;
		float slope;
		float newy;

		if (debug == 1)
		{	
			/*CGE_DrawTextSolid(engine, "delta.x <= delta.y", CGE_V3New(600.0f, 64.0f, 0.0f), CGE_ColorNew(255, 255, 255));*/
		}

		if(newc1.y < newc2.y)
		{
			ymin = newc1.y;
			ymax = newc2.y;
		}
		else
		{
			ymin = newc2.y;
			ymax = newc1.y;
		}

		if(ymin < engine->device.viewport.y)
		{
			ymin = engine->device.viewport.y;
		}
		if(ymax > (engine->device.viewport.y + engine->device.viewport.h))
		{
			ymax = engine->device.viewport.y + engine->device.viewport.h;
		}

		slope = delta.x / delta.y;
		for(newy = ymin; newy <= ymax; newy += 1.0f)
		{
			CGE_V3 newpoint;
			float newx;

			newx = newc1.x + ((newy - newc1.y) * slope);
			newpoint.x = newx;
			newpoint.y = newy;
			CGE_DrawPixel(engine->screen, engine->device.viewport, newpoint, l.point1.color.r, l.point1.color.g, l.point1.color.b);
		}
		
	}

	return CGE_OK;
}

CGE_EXITCODE CGE_DrawGrid(CGE_Engine *engine, CGE_V3 grid, float unit)
{
	float i;
	float j;

	CGE_Line line;
	line.point1 = CGE_PointNew(-20.0f, 0.0f, 0.0f, 80, 80, 80);
	line.point2 = CGE_PointNew(20.0f, 0.0f, 0.0f, 80, 80, 80);
	CGE_DrawLine(engine, line, 1);



	
	for(i = -grid.x; i <= grid.x; i += unit)
	{
		for(j = -grid.y; j <= grid.y; j += unit)
		{
			CGE_Line line;
			line.point1 = CGE_PointNew(i, j, -grid.z, 80, 20, 0);
			line.point2 = CGE_PointNew(i, j, grid.z, 80, 20, 0);
			CGE_DrawLine(engine, line, 0);
		}  
	}
	
	
	for(i = -grid.y; i <= grid.y; i += unit)
	{
		for(j = -grid.z; j <= grid.z; j += unit)
		{
			CGE_Line line;
			line.point1 = CGE_PointNew(-grid.x, i, j, 80, 20, 0);
			line.point2 = CGE_PointNew(grid.x, i, j, 80, 20, 0);
			CGE_DrawLine(engine, line, 0);
		}  		
	}  
	
	/*
	for(i = -grid.z; i <= grid.z; i += unit)
	{
		
	}  
	*/	

	return CGE_OK;
}

CGE_EXITCODE CGE_DrawPixel(SDL_Surface *screen, CGE_Viewport viewport, CGE_V3 position, Uint8 r, Uint8 g, Uint8 b)
{
	Uint32 color;
	Uint16 *buffer;

	if(position.x < viewport.x || position.x > (viewport.x + viewport.w) 
	|| position.y < viewport.y || position.y > (viewport.y + viewport.h))
	{
		return CGE_OK;
	}

	color = SDL_MapRGB(screen->format, r, g, b);
	buffer = (Uint16 *)screen->pixels + (int)position.y * screen->pitch / 2 + (int)position.x;
	*buffer = color;

	return CGE_OK;
}

CGE_EXITCODE CGE_DrawTextSolid(CGE_Engine *engine, char *text, CGE_V3 position, SDL_Color color)
{	
	SDL_Surface * surface;
	SDL_Rect zone;


	surface = TTF_RenderText_Solid(engine->font, text, color);
	zone.x = position.x;
	zone.y = position.y;
	zone.w = 100;
	zone.h = 50;
	SDL_BlitSurface(surface, NULL, engine->screen, &zone);
	SDL_FreeSurface(surface);

	return CGE_OK;
}

CGE_EXITCODE CGE_DrawMatrix(CGE_Engine *engine, CGE_M4 matrix, CGE_V3 position, SDL_Color color)
{
	char item[255];
	const float HSPACES = 80.0f;
	const float VSPACES = 16.0f;
	
	sprintf(item, "%f", matrix.m11);
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m12);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m13);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m14);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	position.y += VSPACES;

	sprintf(item, "%f", matrix.m21);
	position.x -= HSPACES * 3.0f;
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m22);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m23);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m24);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	position.y += VSPACES;

	sprintf(item, "%f", matrix.m31);
	position.x -= HSPACES * 3.0f;
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m32);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m33);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m34);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	position.y += VSPACES;

	sprintf(item, "%f", matrix.m41);
	position.x -= HSPACES * 3.0f;
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m42);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m43);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	sprintf(item, "%f", matrix.m44);
	position.x += HSPACES;
	CGE_DrawTextSolid(engine, item, position, color);

	return CGE_OK;
}

CGE_V3 CGE_V3ViewportTransform(CGE_Viewport v, CGE_V3 p)
{
	CGE_V3 newp;

	newp.x = ((p.x + 1.0f) * v.w / 2.0f) + v.x;
	newp.y = ((-p.y + 1.0f) * v.h / 2.0f) + v.y;
	newp.z = p.z;

	return newp;
}


/* Game engine functions implementations */

CGE_EXITCODE CGE_Init(CGE_Engine **engine)
{
	CGE_Engine *newengine = NULL;
	newengine = (CGE_Engine *)malloc(sizeof(CGE_Engine));
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_EnableUNICODE(1);

	TTF_Init();

	newengine->screen = SDL_SetVideoMode(800, 600, 16, SDL_HWSURFACE);
	newengine->states.status = CGE_ENGINESTATESSTATUS_STARTED;	

	newengine->font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf", 14);
	
	newengine->states.timers.absolute = SDL_GetTicks();
	newengine->states.timers.elapsed = 0;
	newengine->states.timers.fps = 0;
	newengine->states.timers.fpsFrames = 0;
	newengine->states.timers.fpsTicks = 0;

	CGE_SetCamera(newengine, CGE_V3New(0.0f, 0.0f, 100.0f), CGE_V3New(0.0f, 0.0f, 0.0f)); 
	/*newengine->camera.projection = CGE_M4Orthographic(-0.8f, 0.8f, -0.6f, 0.6f, 1.0f, 100.0f);*/
	newengine->camera.projection = CGE_M4Perspective(-0.4f, 0.4f, -0.3f, 0.3f, 1.0f, 100.0f);
	
	newengine->device.model = CGE_M4Identity();
	newengine->device.view = CGE_M4Identity();
	newengine->device.projection = CGE_M4Identity();
	newengine->device.viewport = CGE_ViewportNew(0.0f, 0.0f, 800.0f, 600.0f);

	newengine->point[0] = CGE_PointNew(0.5f, -0.5f, 0.0f, 255, 255, 255);
	newengine->point[1] = CGE_PointNew(0.5f, 0.5f, 0.0f, 255, 255, 255);
	newengine->point[2] = CGE_PointNew(-0.5f, 0.5f, 0.0f, 255, 255, 255);
	newengine->point[3] = CGE_PointNew(-0.5f, -0.5f, 0.0f, 255, 255, 255);

	newengine->axe[0] = CGE_LineNew(CGE_PointNew(0.0f, 0.0f, 0.0f, 0, 0, 255), CGE_PointNew(10.0f, 0.0f, 0.0f, 0, 0, 255)); /*x=b*/
	newengine->axe[1] = CGE_LineNew(CGE_PointNew(0.0f, 0.0f, 0.0f, 0, 255, 0), CGE_PointNew(0.0f, 10.0f, 0.0f, 0, 255, 0)); /*y=g*/
	newengine->axe[2] = CGE_LineNew(CGE_PointNew(0.0f, 0.0f, 0.0f, 255, 0, 0), CGE_PointNew(0.0f, 0.0f, 10.0f, 255, 0, 0)); /*z=r*/

	*engine = newengine;	

	return CGE_OK;
}

CGE_EXITCODE CGE_GetInputs(CGE_Engine *engine)
{	
	SDL_Event e;
	
	while(SDL_PollEvent(&e))
	{
		CGE_MapInputsPhysicals(engine, e);
		CGE_MapInputsLogicals(engine);
	}

	return CGE_OK;
}

CGE_EXITCODE CGE_MapInputsPhysicals(CGE_Engine *engine, SDL_Event e)
{

	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					engine->states.status = CGE_ENGINESTATESSTATUS_STOPPED;
					break;
				case SDLK_LEFT:
					engine->states.inputs.physicals.CGE_KeyLeft = 1;
					break;
				case SDLK_RIGHT:
					engine->states.inputs.physicals.CGE_KeyRight = 1;
					break;
				case SDLK_UP:
					engine->states.inputs.physicals.CGE_KeyUp = 1;
					break;
				case SDLK_DOWN:
					engine->states.inputs.physicals.CGE_KeyDown = 1;
					break;
				case SDLK_a:
					engine->states.inputs.physicals.CGE_KeyA = 1;
					break;
				case SDLK_d:
					engine->states.inputs.physicals.CGE_KeyD = 1;
					break;
				case SDLK_w:
					engine->states.inputs.physicals.CGE_KeyW = 1;
					break;
				case SDLK_s:
					engine->states.inputs.physicals.CGE_KeyS = 1;
					break;
				case SDLK_q:
					engine->states.inputs.physicals.CGE_KeyQ = 1;
					break;
				case SDLK_e:
					engine->states.inputs.physicals.CGE_KeyE = 1;
					break;
				default:
					break;
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					break;
				case SDLK_LEFT:
					engine->states.inputs.physicals.CGE_KeyLeft = 0;
					break;
				case SDLK_RIGHT:
					engine->states.inputs.physicals.CGE_KeyRight = 0;
					break;
				case SDLK_UP:
					engine->states.inputs.physicals.CGE_KeyUp = 0;
					break;
				case SDLK_DOWN:
					engine->states.inputs.physicals.CGE_KeyDown = 0;
					break;
				case SDLK_a:
					engine->states.inputs.physicals.CGE_KeyA = 0;
					break;
				case SDLK_d:
					engine->states.inputs.physicals.CGE_KeyD = 0;
					break;
				case SDLK_w:
					engine->states.inputs.physicals.CGE_KeyW = 0;
					break;
				case SDLK_s:
					engine->states.inputs.physicals.CGE_KeyS = 0;
					break;
				case SDLK_q:
					engine->states.inputs.physicals.CGE_KeyQ = 0;
					break;
				case SDLK_e:
					engine->states.inputs.physicals.CGE_KeyE = 0;
					break;
				default:
					break;
			}
			break;
		case SDL_QUIT: 
			engine->states.status = CGE_ENGINESTATESSTATUS_STOPPED;
			break;
		default:
			break;
	}

	return CGE_OK;
}

CGE_EXITCODE CGE_MapInputsLogicals(CGE_Engine *engine)
{
	engine->states.inputs.logicals.CGE_Yaw = 0.0f;
	engine->states.inputs.logicals.CGE_Pitch = 0.0f;
	engine->states.inputs.logicals.CGE_Roll = 0.0f;
	engine->states.inputs.logicals.CGE_AxisX = 0.0f;
	engine->states.inputs.logicals.CGE_AxisY = 0.0f;
	engine->states.inputs.logicals.CGE_AxisZ = 0.0f;
	engine->states.inputs.logicals.CGE_Advance = 0.0f;
	engine->states.inputs.logicals.CGE_Strafe = 0.0f;
	

	if(engine->states.inputs.physicals.CGE_KeyLeft == 1)
	{
		engine->states.inputs.logicals.CGE_Strafe -= 1.0f;
	}
	if(engine->states.inputs.physicals.CGE_KeyRight == 1)
	{
		engine->states.inputs.logicals.CGE_Strafe += 1.0f;
	}
	if(engine->states.inputs.physicals.CGE_KeyUp == 1)
	{
		engine->states.inputs.logicals.CGE_Advance += 1.0f;
	}
	if(engine->states.inputs.physicals.CGE_KeyDown == 1)
	{
		engine->states.inputs.logicals.CGE_Advance -= 1.0f;
	}
	if(engine->states.inputs.physicals.CGE_KeyA == 1)
	{
		engine->states.inputs.logicals.CGE_Yaw += 1.0f;
	}
	if(engine->states.inputs.physicals.CGE_KeyD == 1)
	{
		engine->states.inputs.logicals.CGE_Yaw -= 1.0f;
	}
	if(engine->states.inputs.physicals.CGE_KeyW == 1)
	{
		engine->states.inputs.logicals.CGE_Pitch += 1.0f;
	}
	if(engine->states.inputs.physicals.CGE_KeyS == 1)
	{
		engine->states.inputs.logicals.CGE_Pitch -= 1.0f;
	}
	if(engine->states.inputs.physicals.CGE_KeyQ == 1)
	{
		engine->states.inputs.logicals.CGE_Roll += 1.0f;
	}
	if(engine->states.inputs.physicals.CGE_KeyE == 1)
	{
		engine->states.inputs.logicals.CGE_Roll -= 1.0f;
	}
	
	return CGE_OK;
}

CGE_EXITCODE CGE_GetTimers(CGE_Engine *engine)
{
	Uint32 absolute = SDL_GetTicks();
	engine->states.timers.elapsed = absolute - engine->states.timers.absolute;
	engine->states.timers.absolute = absolute;

	engine->states.timers.fpsFrames++;
	engine->states.timers.fpsTicks += engine->states.timers.elapsed;
	if(engine->states.timers.fpsTicks > 1000)
	{
		/*printf("fps: %d/sec\n", engine->states.timers.fpsFrames);*/
		engine->states.timers.fps = engine->states.timers.fpsFrames;
		engine->states.timers.fpsFrames = 0;
		engine->states.timers.fpsTicks = 0;
	}

	return CGE_OK;
}

CGE_EXITCODE CGE_Move(CGE_Engine *engine)
{	
	float t;
	CGE_V4 forward;
	CGE_V4 left;
	CGE_V4 velocity;
	CGE_M4 rotate;

	t = (float)engine->states.timers.elapsed;
		
	engine->camera.axis.x += engine->states.inputs.logicals.CGE_Pitch * 0.05f * t;
	engine->camera.axis.y += engine->states.inputs.logicals.CGE_Yaw * 0.05f * t;
	engine->camera.axis.z += engine->states.inputs.logicals.CGE_Roll * 0.05f *t;

	if(engine->camera.axis.x > 40.0f)
	{
		engine->camera.axis.x = 40.0f;
	}
	if(engine->camera.axis.x < -40.0f)
	{
		engine->camera.axis.x = -40.0f;
	}
	if(engine->camera.axis.y > 180.0f)
	{
		engine->camera.axis.y = -180.0f;
	}
	if(engine->camera.axis.y < -180.0f)
	{
		engine->camera.axis.y = 180.0f;
	}
	if(engine->camera.axis.z > 10.0f)
	{
		engine->camera.axis.z = 10.0f;
	}
	if(engine->camera.axis.z < -10.0f)
	{
		engine->camera.axis.z = -10.0f;
	}

	rotate = CGE_M4Rotate(engine->camera.axis.y, 0.0f, 1.0f, 0.0f);
	forward = CGE_V4New(0.0f, 0.0f, -1.0f, 0.0f);
	left = CGE_V4New(1.0f, 0.0f, 0.0f, 0.0f);
	forward = CGE_M4V4Mul(rotate, forward);
	left = CGE_M4V4Mul(rotate, left);
	forward = CGE_V4ScalarMul(forward, engine->states.inputs.logicals.CGE_Advance);
	left = CGE_V4ScalarMul(left, engine->states.inputs.logicals.CGE_Strafe);
	velocity = CGE_V4V4Add(forward, left);
	velocity = CGE_V4Normalize(velocity);
	
	engine->camera.position.x += velocity.x * 0.05f * t;
	engine->camera.position.y += velocity.y * 0.05f * t;
	engine->camera.position.z += velocity.z * 0.05f * t;
		
	engine->camera.view = CGE_M4View(engine->camera.position, engine->camera.axis);
			
	/*	
	engine->camera.position.x += engine->states.inputs.logicals.CGE_AxisX * 0.05f * t;
	engine->camera.position.y += engine->states.inputs.logicals.CGE_AxisY * 0.05f * t;
	engine->camera.position.z += engine->states.inputs.logicals.CGE_AxisZ * 0.05f * t;
	*/
	/*CGE_SetCamera(engine, engine->camera.position, engine->camera.target);*/

	return CGE_OK;
}


CGE_EXITCODE CGE_Render(CGE_Engine *engine)
{	
	char fps[255];

	if(SDL_MUSTLOCK(engine->screen))
	{
		if(SDL_LockSurface(engine->screen) < 0)
		{
			return CGE_ERR;
		}
	}

	SDL_FillRect(engine->screen, NULL, 0);

		
	engine->device.view = engine->camera.view;
	engine->device.projection = engine->camera.projection;

	
	CGE_DrawGrid(engine, CGE_V3New(50.0f, 50.0f, 50.0f), 20.0f);

	CGE_DrawLine(engine, engine->axe[0], 0);
	CGE_DrawLine(engine, engine->axe[1], 0);
	CGE_DrawLine(engine, engine->axe[2], 0);

	CGE_DrawLine(engine, CGE_LineNew(engine->point[0], engine->point[1]), 0);
	CGE_DrawLine(engine, CGE_LineNew(engine->point[1], engine->point[2]), 0);
	CGE_DrawLine(engine, CGE_LineNew(engine->point[2], engine->point[0]), 0);
	CGE_DrawLine(engine, CGE_LineNew(engine->point[2], engine->point[3]), 0);
	CGE_DrawLine(engine, CGE_LineNew(engine->point[3], engine->point[0]), 0);
/*
	CGE_DrawPoint(engine, engine->point[0]);
	CGE_DrawPoint(engine, engine->point[1]);
	CGE_DrawPoint(engine, engine->point[2]);
	CGE_DrawPoint(engine, engine->point[3]);
*/


	sprintf(fps, "FPS : %i", engine->states.timers.fps);
	CGE_DrawTextSolid(engine, fps, CGE_V3New(0.0f, 580.0f, 0.0f), CGE_ColorNew(255.0f, 255.0f, 255.0f));

/*	
	CGE_DrawMatrix(engine, engine->device.view, CGE_V3New(0.0f, 332.0f, 0.0f), CGE_ColorNew(255.0f, 255.0f, 255.0f));
	CGE_DrawMatrix(engine, engine->device.projection, CGE_V3New(0.0f, 112.0f, 0.0f), CGE_ColorNew(255.0f, 255.0f, 255.0f));
*/
/*
	CGE_DrawTextSolid(engine, "Mala", CGE_V3New(0.0f, 14.0f, 0.0f), CGE_ColorNew(255.0f, 255.0f, 155.0f));
	CGE_DrawTextSolid(engine, "Osaur", CGE_V3New(0.0f, 28.0f, 0.0f), CGE_ColorNew(155.0f, 255.0f, 255.0f));
	CGE_DrawTextSolid(engine, "Trrrain", CGE_V3New(0.0f, 42.0f, 0.0f), CGE_ColorNew(255.0f, 155.0f, 255.0f));
*/
	/*CGE_M4Print(engine->device.view, "view");*/
	/*CGE_M4Print(engine->device.projection, "projection");*/


	if(SDL_MUSTLOCK(engine->screen))
	{
		SDL_UnlockSurface(engine->screen);
	}

	SDL_UpdateRect(engine->screen, 0, 0, 800, 600);

	return CGE_OK;
}

CGE_EXITCODE CGE_DeInit(CGE_Engine *engine)
{
	free(engine);
	SDL_Quit();
		
	return CGE_OK;
}

CGE_EXITCODE CGE_SetCamera(CGE_Engine *engine, CGE_V3 position, CGE_V3 target)
{	
	engine->camera.position = position;
	engine->camera.target = target;	
	engine->camera.view = CGE_M4View(position, target);

	return CGE_OK;
}


/* Entry point */

int main(int argc, char *agrv[])
{
	CGE_Engine *engine = NULL;
	
	CGE_Init(&engine);	

	while(engine->states.status == CGE_ENGINESTATESSTATUS_STARTED)
	{
		CGE_GetInputs(engine);
		CGE_GetTimers(engine);
		CGE_Move(engine);
		CGE_Render(engine);
		SDL_Delay(1);
		/*engine->states.status = CGE_ENGINESTATESSTATUS_STOPPED;*/
	}

	CGE_DeInit(engine);

	return 0;
}


/* Debugger functions implementations */

CGE_EXITCODE CGE_M4Print(CGE_M4 m, char *label)
{
	printf("\nmatrix %s\n", label);
	printf("m11 : %f\t", m.m11);
	printf("m12 : %f\t", m.m12);
	printf("m13 : %f\t", m.m13);
	printf("m14 : %f\n", m.m14);
	printf("m21 : %f\t", m.m21);
	printf("m22 : %f\t", m.m22);
	printf("m23 : %f\t", m.m23);
	printf("m24 : %f\n", m.m24);
	printf("m31 : %f\t", m.m31);
	printf("m32 : %f\t", m.m32);
	printf("m33 : %f\t", m.m33);
	printf("m34 : %f\n", m.m34);
	printf("m41 : %f\t", m.m41);
	printf("m42 : %f\t", m.m42);
	printf("m43 : %f\t", m.m43);
	printf("m44 : %f\n", m.m44);
	printf("\n");

	return CGE_OK;
}

CGE_EXITCODE CGE_V3Print(CGE_V3 v, char *label)
{
	printf("\npoint %s\n", label);
	printf("x : %f\t", v.x);
	printf("y : %f\t", v.y);
	printf("z : %f\n", v.z);
	printf("\n");	
	
	return CGE_OK;
}

CGE_EXITCODE CGE_V4Print(CGE_V4 v, char *label)
{
	printf("\npoint %s\n", label);
	printf("x : %f\t", v.x);
	printf("y : %f\t", v.y);
	printf("z : %f\t", v.z);
	printf("w : %f\n", v.w);
	printf("\n");	
	
	return CGE_OK;
}


