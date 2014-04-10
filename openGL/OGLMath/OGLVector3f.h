#pragma once

class OGLVector3f
{
	public:
		float x;
		float y;
		float z;

		OGLVector3f		(void);
		OGLVector3f		(const OGLVector3f &);
		OGLVector3f		(float, float, float);

		OGLVector3f		operator+	(OGLVector3f &);
		OGLVector3f		operator-	(OGLVector3f &);
		OGLVector3f		operator=	(OGLVector3f &);

		OGLVector3f		operator*	(float);
		OGLVector3f		operator/	(float);

		float			length		(void);
		float			dot			(OGLVector3f &);

		OGLVector3f		cross		(OGLVector3f &);
		OGLVector3f		normalize	(void);
		OGLVector3f		negative	(void);

};