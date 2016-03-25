#include "Sprite.h"

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

Sprite::Sprite(string spriteSheetFilename)
{
	this->loadSpriteSheet(spriteSheetFilename.c_str());
	currentAnimation = 0;
	layerID = 0;
	theta = 0;
	centerX = centerY = 0;
}

// ########################################################################################################################

void Sprite::loadSpriteSheet(const char *filename)
{
	sheet.textureID = ilutGLLoadImage((char*)filename);
	sheet.width = ilGetInteger(IL_IMAGE_WIDTH);
	sheet.height = ilGetInteger(IL_IMAGE_HEIGHT);
}

// ########################################################################################################################

void Sprite::setSpriteFrameSize(int width, int height)
{
	sz.width = width;
	sz.height = height;
	sz.normalizedWidth = (float)width/(float)sheet.width;
	sz.normalizedHeight = (float)height/(float)sheet.height;
}
// ########################################################################################################################
// this draws the sprite texture at its current frame of its current animation
// it positions the sprite based on the transformation formula: v' = RotationMatrix*(v-center) + position
// where position is the bottom left corner of the sprite and v is each corner of the sprite rectangle, v' is the transformed corner
// and RotationMatrix is defined by the sprite's theta value (counter clockwise)
// ########################################################################################################################

void Sprite::draw()
{
	/* draw the sprite */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();

	/* position the sprite into the particular pixel location */
	glTranslatef(positionX,positionY,0);

	// apply the rotation around the center of the sprite
	glTranslatef(centerX,centerY,0);
	glRotatef(theta, 0,0,1);
	glTranslatef(-centerX,-centerY,0);

	/* get the texture coordinate from the sprite so we know which frame to draw */
	float u = 0; //not sure what this should be eq to????~~~~~~~~~~~~~~~
	float v = 0;

	glColor3f(1,1,1);
	/* bind the appropriate texture frame */
	glBindTexture(GL_TEXTURE_2D,sheet.textureID);
	/* draw the image as a quad the size of the first loaded image */
	glBegin(GL_QUADS);
	glTexCoord2f(u,v);
	glVertex3f(0,0,0);

	glTexCoord2f(u,v+sz.normalizedHeight);
	glVertex3f(0,sz.height,0);

	glTexCoord2f(u+sz.normalizedWidth,v+sz.normalizedHeight);
	glVertex3f(sz.width,sz.height,0);

	glTexCoord2f(u+sz.normalizedWidth,v);
	glVertex3f(sz.width,0,0);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################
