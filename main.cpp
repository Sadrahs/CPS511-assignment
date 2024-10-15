#define GL_SILENCE_DEPRECATION  // Silence OpenGL warnings on MacOS

#ifdef __APPLE__  // MacOS specific includes
#include <glut/glut.h>
#else  // Windows/Linux
#include <windows.h>  // Only for Windows
#include <GLut/glut.h>   // GLUT library for Windows/Linux
#endif

#include <math.h>  // For math functions like sin(), cos(), etc.
#include <stdio.h>  // For printf debugging
#include <stdlib.h>  // For exit()


// Globals for transformations and camera
float cannonAngle = 0.0f;  // Spinning angle for the cannon
float rightArmAngle = 180.0f;  // Angle for right arm rotation
float leftArmAngle = 180.0f;   // Angle for left arm rotation
float rightLegAngle = 90.0f;  // Angle for right leg rotation
float leftLegAngle = 90.0f;   // Angle for left leg rotation
float cameraAngle = 0.0f;  // Angle to rotate the camera around the model

void setHelmetMaterial() {
    // Set material properties for the helmet
    GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 };  // Slightly reflective (metallic look)
    GLfloat mat_shininess[] = { 100.0 };  // High shininess for a more metallic surface
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// Function to draw the head
void drawHead() {
    // Define the clipping plane equation (clip the lower half, below Y=1.4)
    GLdouble clip_plane[] = { 0.0, 0.96, 0, -1.2 };  // Only clip a small portion
    GLdouble clip_plane1[]= {0.0, -0.96,-0.4, 1.2 };



    // 1. Draw the top metallic half-sphere (helmet)
    glPushMatrix();
    glEnable(GL_CLIP_PLANE0);  // Enable clipping plane
    glClipPlane(GL_CLIP_PLANE0, clip_plane);  // Apply the clipping plan
    GLUquadric* head = gluNewQuadric();

    glColor3f(0.5f, 0.5f, 0.5f);  // Metallic color for the helmet
    glTranslatef(0.0f, 1.35f, 0.0f);
    glScalef(0.9, 1.0, 1.06);// Lower the helmet position
    gluSphere(head, 0.3, 20, 20);  // Slightly reduce size for better fit

    glDisable(GL_CLIP_PLANE0);  // Disable clipping plane
    glPopMatrix();
    
    // the one sphere between head and helmet
    glPushMatrix();
    glEnable(GL_CLIP_PLANE0);
    glClipPlane(GL_CLIP_PLANE0, clip_plane1);
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0.0f, 1.30f, 0.0f);
    glScalef(0.9, 1.2, 1.06);
    glutSolidSphere(0.28, 20, 20);
    glDisable(GL_CLIP_PLANE0);  // Disable clipping plane
    glPopMatrix();
    
    // 2. Draw the human face (brown sphere below the helmet)

    glPushMatrix();
    glColor3f(0.6f, 0.4f, 0.3f);  // Brownish color for human skin
    glTranslatef(0.0f, 1.3f, 0.0f);  // Position lower for the human head
    glScalef(0.9f, 1.08f, 0.9f);  // Elongate the sphere to make it look like an egg shape
    glutSolidSphere(0.28, 20, 20);  // Use a sphere for the head, but scaled to an egg
    glPopMatrix();
    
    
    // 3. Draw the black visor (front face part)
    glPushMatrix();

    // Define the clipping plane to cut off part of the cylinder (adjust the parameters to slice off properly)
    GLdouble clip_plane2[] = {0.0, 0.0, 2, -0.4};  // Adjust this for better clipping of the visor
    glEnable(GL_CLIP_PLANE0);  // Enable clipping plane
    glClipPlane(GL_CLIP_PLANE0, clip_plane2);  // Apply the clipping plane

    // Draw the visor as a black cylinder
    glColor3f(0.0f, 0.0f, 0.0f);  // Black color for the visor
    glTranslatef(0.0f, 1.38f, 0.0f);  // Adjust position on the head (closer to the front)
    glRotatef(90, 1.0f, 0.0f, 0.0f);  // Align the cylinder horizontally
    GLUquadric* visor = gluNewQuadric();
    gluCylinder(visor, 0.33f, 0.33f, 0.06f, 20, 20);  // Draw the visor cylinder with appropriate dimensions

    glDisable(GL_CLIP_PLANE0);  // Disable clipping plane
    glPopMatrix();

    // 4. Draw the black neck cover (cylinder wrapping around the neck)
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);  // Black color for the neck cover
    glTranslatef(0.0f, 1.1f, 0.0f);  // Position below the human face
    glRotatef(90, 1.0f, 0.0f, 0.0f);  // Rotate to align the cylinder vertically
    GLUquadric* neckCover = gluNewQuadric();
    gluCylinder(neckCover, 0.2, 0.27, 0.2, 20, 20);  // Short cylinder for the neck
    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);
    
    // another balack neck cover
}




void drawTriangle() {
    // Start drawing triangles
   // glBegin(GL_TRIANGLES);

    // Set the color of the triangle (optional, you can remove this if you have lighting)
    //glColor3f(1.0f, 0.0f, 0.0f);  // Red color

    // Define three vertices of the triangle
    //glVertex3f(-0.5f, -0.5f, 0.0f);  // Vertex 1 (Bottom-left)
    //glVertex3f(0.5f, -0.5f, 0.0f);   // Vertex 2 (Bottom-right)
    //glVertex3f(0.0f, 0.5f, 0.0f);    // Vertex 3 (Top-center)

    // Finish drawing
    //glEnd();
}

void drawCube() {
}


void drawQuad() {

}
void setMaterialForChest() {
    // Make chest metallic with high specularity and shininess
    GLfloat mat_specular[] = { 0.9, 0.9, 0.9, 1.0 };  // Strong specular reflection
    GLfloat mat_shininess[] = { 50.0 };  // Shininess factor (higher = shinier)

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}


// Function to draw the torso

void drawTorso() {
    // Main torso (oval shape using scaled sphere)
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(-0.65f, 0.5f, 0.0f);  // Position on the left side
    glRotatef(90, 0.0f, 1.0f, 0.0f);  // Rotate to align horizontally
    glScalef(1.2, 1.3, 1.0);
    GLUquadric* chest = gluNewQuadric();
    gluCylinder(chest, 0.3, 0.3, 1.3, 20, 20);  // Left shoulder cylinder
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(-0.6, 1.0, 0.0);
    glVertex3f(-0.2, 1.0, 0.0);
    glVertex3f(-0.6, 0.9, 0.2);
    glVertex3f(-0.2, 0.9, 0.2);
    glVertex3f(-0.6, 0.85, 0.25);
    glVertex3f(-0.2, 0.85, 0.25);
    glVertex3f(-0.6, 0.82, 0.28);
    glVertex3f(0.0, 0.82, 0.28);
    glVertex3f(-0.6, 0.8, 0.30);
    glVertex3f(0.0, 0.8, 0.30);
    glVertex3f(-0.6, 0.78, 0.34);
    glVertex3f(0.0, 0.78, 0.34);
    glVertex3f(-0.6, 0.76, 0.34);
    glVertex3f(0.0, 0.76, 0.34);
    glVertex3f(-0.6, 0.74, 0.36);
    glVertex3f(0.0, 0.74, 0.36);
    glVertex3f(-0.6, 0.72, 0.38);
    glVertex3f(0.0, 0.72, 0.38);
    glVertex3f(-0.6, 0.68, 0.40);
    glVertex3f(0.0, 0.68, 0.40);
    glVertex3f(-0.6, 0.65, 0.40);
    glVertex3f(0.0, 0.65, 0.40);
    glVertex3f(-0.6, 0.61, 0.42);
    glVertex3f(0.0, 0.61, 0.42);
    glVertex3f(-0.6, 0.57, 0.42);
    glVertex3f(0.0, 0.57, 0.42);
    glVertex3f(-0.6, 0.53, 0.45);
    glVertex3f(0.0, 0.53, 0.45);
    glVertex3f(-0.6, 0.50, 0.45);
    glVertex3f(0.0, 0.50, 0.45);
    glVertex3f(-0.6, 0.47, 0.45);
    glVertex3f(0.0, 0.47, 0.45);
    glVertex3f(-0.6, 0.42, 0.40);
    glVertex3f(0.0, 0.42, 0.40);
    glVertex3f(-0.6, 0.38, 0.38);
    glVertex3f(-0.1, 0.38, 0.38);
    glVertex3f(-0.6, 0.32, 0.37);
    glVertex3f(-0.2, 0.32, 0.37);
    glVertex3f(-0.6, 0.28, 0.36);
    glVertex3f(-0.3, 0.28, 0.36);
    glVertex3f(-0.6, 0.24, 0.35);
    glVertex3f(-0.4, 0.24, 0.35);
    glVertex3f(-0.6, 0.23, 0.34);
    glVertex3f(-0.5, 0.20, 0.34);
    glVertex3f(-0.6, 0.23, 0.33);
    glVertex3f(-0.5, 0.20, 0.33);
    glVertex3f(-0.6, 0.23, 0.32);
    glVertex3f(-0.5, 0.20, 0.32);
    glVertex3f(-0.6, 0.20, 0.30);
    glVertex3f(-0.5, 0.18, 0.30);
    glVertex3f(-0.6, 0.20, 0.28);
    glVertex3f(-0.5, 0.18, 0.28);
    glVertex3f(-0.6, 0.20, 0.27);
    glVertex3f(-0.5, 0.18, 0.27);
    glVertex3f(-0.6, 0.20, 0.25);
    glVertex3f(-0.5, 0.18, 0.25);
    glVertex3f(-0.6, 0.16, 0.24);
    glVertex3f(-0.5, 0.12, 0.24);
    glVertex3f(-0.6, 0.12, 0.22);
    glVertex3f(-0.5, 0.08, 0.22);
    glVertex3f(-0.6, 0.12, 0.18);
    glVertex3f(-0.5, 0.08, 0.18);
    glVertex3f(-0.6, 0.12, 0.17);
    glVertex3f(-0.5, 0.08, 0.17);
    glVertex3f(-0.6, 0.12, 0.14);
    glVertex3f(-0.5, 0.08, 0.14);
    glVertex3f(-0.6, 0.08, 0.10);
    glVertex3f(-0.5, 0.08, 0.10);
    glVertex3f(-0.6, 0.08, 0.08);
    glVertex3f(-0.5, 0.08, 0.08);
    glVertex3f(-0.6, 0.04, 0.06);
    glVertex3f(-0.5, 0.04, 0.06);
    glVertex3f(-0.6, 0.02, 0.04);
    glVertex3f(-0.5, 0.02, 0.04);
    glVertex3f(-0.6, 0.02, 0.02);
    glVertex3f(-0.5, 0.02, 0.02);
    glVertex3f(-0.6, 0.02, 0.00);
    glVertex3f(-0.5, 0.02, 0.00);

    glVertex3f(-0.6, 0.02, -0.00);
    glVertex3f(-0.5, 0.02, -0.00);
    glVertex3f(-0.6, 0.02, -0.02);
    glVertex3f(-0.5, 0.02, -0.02);
    glVertex3f(-0.6, 0.04, -0.04);
    glVertex3f(-0.5, 0.04, -0.04);
    glVertex3f(-0.6, 0.08, -0.08);
    glVertex3f(-0.5, 0.08, -0.08);
    glVertex3f(-0.6, 0.08, -0.10);
    glVertex3f(-0.5, 0.08, -0.10);
    glVertex3f(-0.6, 0.12, -0.14);
    glVertex3f(-0.5, 0.08, -0.14);
    glVertex3f(-0.6, 0.12, -0.17);
    glVertex3f(-0.5, 0.08, -0.17);
    glVertex3f(-0.6, 0.12, -0.18);
    glVertex3f(-0.5, 0.08, -0.18);
    glVertex3f(-0.6, 0.12, -0.22);
    glVertex3f(-0.5, 0.08, -0.22);
    glVertex3f(-0.6, 0.16, -0.24);
    glVertex3f(-0.5, 0.12, -0.24);
    glVertex3f(-0.6, 0.20, -0.25);
    glVertex3f(-0.5, 0.18, -0.25);
    glVertex3f(-0.6, 0.20, -0.27);
    glVertex3f(-0.5, 0.18, -0.27);
    glVertex3f(-0.6, 0.20, -0.28);
    glVertex3f(-0.5, 0.18, -0.28);
    glVertex3f(-0.6, 0.20, -0.30);
    glVertex3f(-0.5, 0.18, -0.30);
    glVertex3f(-0.6, 0.23, -0.32);
    glVertex3f(-0.5, 0.20, -0.32);
    glVertex3f(-0.6, 0.23, -0.33);
    glVertex3f(-0.5, 0.20, -0.33);
    glVertex3f(-0.6, 0.23, -0.34);
    glVertex3f(-0.5, 0.20, -0.34);
    glVertex3f(-0.6, 0.24, -0.35);
    glVertex3f(-0.4, 0.24, -0.35);
    glVertex3f(-0.6, 0.28, -0.36);
    glVertex3f(-0.3, 0.28, -0.36);
    glVertex3f(-0.6, 0.32, -0.37);
    glVertex3f(-0.2, 0.32, -0.37);
    glVertex3f(-0.6, 0.38, -0.38);
    glVertex3f(-0.1, 0.38, -0.38);
    glVertex3f(-0.6, 0.42, -0.40);
    glVertex3f(0.0, 0.42, -0.40);
    glVertex3f(-0.6, 0.47, -0.45);
    glVertex3f(0.0, 0.47, -0.45);
    glVertex3f(-0.6, 0.50, -0.45);
    glVertex3f(0.0, 0.50, -0.45);
    glVertex3f(-0.6, 0.53, -0.45);
    glVertex3f(0.0, 0.53, -0.45);
    glVertex3f(-0.6, 0.57, -0.42);
    glVertex3f(0.0, 0.57, -0.42);
    glVertex3f(-0.6, 0.61, -0.42);
    glVertex3f(0.0, 0.61, -0.42);
    glVertex3f(-0.6, 0.65, -0.40);
    glVertex3f(0.0, 0.65, -0.40);
    glVertex3f(-0.6, 0.68, -0.40);
    glVertex3f(0.0, 0.68, -0.40);
    glVertex3f(-0.6, 0.72, -0.38);
    glVertex3f(0.0, 0.72, -0.38);
    glVertex3f(-0.6, 0.74, -0.36);
    glVertex3f(0.0, 0.74, -0.36);
    glVertex3f(-0.6, 0.76, -0.34);
    glVertex3f(0.0, 0.76, -0.34);
    glVertex3f(-0.6, 0.78, -0.34);
    glVertex3f(0.0, 0.78, -0.34);
    glVertex3f(-0.6, 0.8, -0.30);
    glVertex3f(0.0, 0.8, -0.30);
    glVertex3f(-0.6, 0.82, -0.28);
    glVertex3f(0.0, 0.82, -0.28);
    glVertex3f(-0.6, 0.85, -0.25);
    glVertex3f(-0.2, 0.85, -0.25);
    glVertex3f(-0.6, 0.9, -0.2);
    glVertex3f(-0.2, 0.9, -0.2);
    glVertex3f(-0.6, 1.0, -0.0);
    glVertex3f(-0.2, 1.0, -0.0);



    glEnd();
    
    

    glBegin(GL_TRIANGLE_STRIP);
    
    glVertex3f(0.6, 1.0, -0.0);
    glVertex3f(0.2, 1.0, -0.0);
    glVertex3f(0.6, 0.9, -0.2);
    glVertex3f(0.2, 0.9, -0.2);
    glVertex3f(0.6, 0.85, -0.25);
    glVertex3f(0.2, 0.85, -0.25);
    glVertex3f(0.6, 0.82, -0.28);
    glVertex3f(0.0, 0.82, -0.28);
    glVertex3f(0.6, 0.8, -0.30);
    glVertex3f(0.0, 0.8, -0.30);
    glVertex3f(0.6, 0.78, -0.34);
    glVertex3f(0.0, 0.78, -0.34);
    glVertex3f(0.6, 0.76, -0.34);
    glVertex3f(0.0, 0.76, -0.34);
    glVertex3f(0.6, 0.74, -0.36);
    glVertex3f(0.0, 0.74, -0.36);
    glVertex3f(0.6, 0.72, -0.38);
    glVertex3f(0.0, 0.72, -0.38);
    glVertex3f(0.6, 0.68, -0.40);
    glVertex3f(0.0, 0.68, -0.40);
    glVertex3f(0.6, 0.65, -0.40);
    glVertex3f(0.0, 0.65, -0.40);
    glVertex3f(0.6, 0.61, -0.42);
    glVertex3f(0.0, 0.61, -0.42);
    glVertex3f(0.6, 0.57, -0.42);
    glVertex3f(0.0, 0.57, -0.42);
    glVertex3f(0.6, 0.53, -0.45);
    glVertex3f(0.0, 0.53, -0.45);
    glVertex3f(0.6, 0.50, -0.45);
    glVertex3f(0.0, 0.50, -0.45);
    glVertex3f(0.6, 0.47, -0.45);
    glVertex3f(0.0, 0.47, -0.45);
    glVertex3f(0.6, 0.42, -0.40);
    glVertex3f(0.0, 0.42, -0.40);
    glVertex3f(0.6, 0.38, -0.38);
    glVertex3f(0.1, 0.38, -0.38);
    glVertex3f(0.6, 0.32, -0.37);
    glVertex3f(0.2, 0.32, -0.37);
    glVertex3f(0.6, 0.28, -0.36);
    glVertex3f(0.3, 0.28, -0.36);
    glVertex3f(0.6, 0.24, -0.35);
    glVertex3f(0.4, 0.24, -0.35);
    glVertex3f(0.6, 0.23, -0.34);
    glVertex3f(0.5, 0.20, -0.34);
    glVertex3f(0.6, 0.23, -0.33);
    glVertex3f(0.5, 0.20, -0.33);
    glVertex3f(0.6, 0.23, -0.32);
    glVertex3f(0.5, 0.20, -0.32);
    glVertex3f(0.6, 0.20, -0.30);
    glVertex3f(0.5, 0.18, -0.30);
    glVertex3f(0.6, 0.20, -0.28);
    glVertex3f(0.5, 0.18, -0.28);
    glVertex3f(0.6, 0.20, -0.27);
    glVertex3f(0.5, 0.18, -0.27);
    glVertex3f(0.6, 0.20, -0.25);
    glVertex3f(0.5, 0.18, -0.25);
    glVertex3f(0.6, 0.16, -0.24);
    glVertex3f(0.5, 0.12, -0.24);
    glVertex3f(0.6, 0.12, -0.22);
    glVertex3f(0.5, 0.08, -0.22);
    glVertex3f(0.6, 0.12, -0.18);
    glVertex3f(0.5, 0.08, -0.18);
    glVertex3f(0.6, 0.12, -0.17);
    glVertex3f(0.5, 0.08, -0.17);
    glVertex3f(0.6, 0.12, -0.14);
    glVertex3f(0.5, 0.08, -0.14);
    glVertex3f(0.6, 0.08, -0.10);
    glVertex3f(0.5, 0.08, -0.10);
    glVertex3f(0.6, 0.08, -0.08);
    glVertex3f(0.5, 0.08, -0.08);
    glVertex3f(0.6, 0.04, -0.06);
    glVertex3f(0.5, 0.04, -0.06);
    glVertex3f(0.6, 0.02, -0.04);
    glVertex3f(0.5, 0.02, -0.04);
    glVertex3f(0.6, 0.02, -0.02);
    glVertex3f(0.5, 0.02, -0.02);
    glVertex3f(0.6, 0.02, -0.00);
    glVertex3f(0.5, 0.02, -0.00);
    
    glVertex3f(0.6, 0.02, 0.00);
    glVertex3f(0.5, 0.02, 0.00);
    glVertex3f(0.6, 0.02, 0.02);
    glVertex3f(0.5, 0.02, 0.02);
    glVertex3f(0.6, 0.04, 0.04);
    glVertex3f(0.5, 0.04, 0.04);
    glVertex3f(0.6, 0.08, 0.08);
    glVertex3f(0.5, 0.08, 0.08);
    glVertex3f(0.6, 0.08, 0.10);
    glVertex3f(0.5, 0.08, 0.10);
    glVertex3f(0.6, 0.12, 0.14);
    glVertex3f(0.5, 0.08, 0.14);
    glVertex3f(0.6, 0.12, 0.17);
    glVertex3f(0.5, 0.08, 0.17);
    glVertex3f(0.6, 0.12, 0.18);
    glVertex3f(0.5, 0.08, 0.18);
    glVertex3f(0.6, 0.12, 0.22);
    glVertex3f(0.5, 0.08, 0.22);
    glVertex3f(0.6, 0.16, 0.24);
    glVertex3f(0.5, 0.12, 0.24);
    glVertex3f(0.6, 0.20, 0.25);
    glVertex3f(0.5, 0.18, 0.25);
    glVertex3f(0.6, 0.20, 0.27);
    glVertex3f(0.5, 0.18, 0.27);
    glVertex3f(0.6, 0.20, 0.28);
    glVertex3f(0.5, 0.18, 0.28);
    glVertex3f(0.6, 0.20, 0.30);
    glVertex3f(0.5, 0.18, 0.30);
    glVertex3f(0.6, 0.23, 0.32);
    glVertex3f(0.5, 0.20, 0.32);
    glVertex3f(0.6, 0.23, 0.33);
    glVertex3f(0.5, 0.20, 0.33);
    glVertex3f(0.6, 0.23, 0.34);
    glVertex3f(0.5, 0.20, 0.34);
    glVertex3f(0.6, 0.24, 0.35);
    glVertex3f(0.4, 0.24, 0.35);
    glVertex3f(0.6, 0.28, 0.36);
    glVertex3f(0.3, 0.28, 0.36);
    glVertex3f(0.6, 0.32, 0.37);
    glVertex3f(0.2, 0.32, 0.37);
    glVertex3f(0.6, 0.38, 0.38);
    glVertex3f(0.1, 0.38, 0.38);
    glVertex3f(0.6, 0.42, 0.40);
    glVertex3f(0.0, 0.42, 0.40);
    glVertex3f(0.6, 0.47, 0.45);
    glVertex3f(0.0, 0.47, 0.45);
    glVertex3f(0.6, 0.50, 0.45);
    glVertex3f(0.0, 0.50, 0.45);
    glVertex3f(0.6, 0.53, 0.45);
    glVertex3f(0.0, 0.53, 0.45);
    glVertex3f(0.6, 0.57, 0.42);
    glVertex3f(0.0, 0.57, 0.42);
    glVertex3f(0.6, 0.61, 0.42);
    glVertex3f(0.0, 0.61, 0.42);
    glVertex3f(0.6, 0.65, 0.40);
    glVertex3f(0.0, 0.65, 0.40);
    glVertex3f(0.6, 0.68, 0.40);
    glVertex3f(0.0, 0.68, 0.40);
    glVertex3f(0.6, 0.72, 0.38);
    glVertex3f(0.0, 0.72, 0.38);
    glVertex3f(0.6, 0.74, 0.36);
    glVertex3f(0.0, 0.74, 0.36);
    glVertex3f(0.6, 0.76, 0.34);
    glVertex3f(0.0, 0.76, 0.34);
    glVertex3f(0.6, 0.78, 0.34);
    glVertex3f(0.0, 0.78, 0.34);
    glVertex3f(0.6, 0.80, 0.30);
    glVertex3f(0.0, 0.80, 0.30);
    glVertex3f(0.6, 0.82, 0.28);
    glVertex3f(0.0, 0.82, 0.28);
    glVertex3f(0.6, 0.85, 0.25);
    glVertex3f(0.2, 0.85, 0.25);
    glVertex3f(0.6, 0.90, 0.20);
    glVertex3f(0.2, 0.90, 0.20);
    glVertex3f(0.6, 1.00, 0.00);
    glVertex3f(0.2, 1.00, 0.00);

    glEnd();
    glPopMatrix();
    
    //body
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.3f, 0.0f);  // Position on the left side
    glRotatef(90, 1.0f, 0.0f, 0.0f);  // Rotate to align horizontally
    glScalef(1.4, 1.3, 1.0);
    GLUquadric* body = gluNewQuadric();
    gluCylinder(body, 0.3, 0.3, 0.6, 20, 20);  // Left shoulder cylinder
    glPopMatrix();
    
    //lower body
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);
    glTranslatef(0.0f, -0.3f, 0.0f);  // Position on the left side
    glRotatef(90, 1.0f, 0.0f, 0.0f);  // Rotate to align horizontally
    glScalef(1.4, 1.1, 1.0);
    GLUquadric* lowerbody = gluNewQuadric();
    gluCylinder(lowerbody, 0.28, 0.1, 0.5, 20, 20);  // Left shoulder cylinder
    glPopMatrix();
    


}


// Function to draw an arm
void drawArm(float angle) {
}

// Function to draw a leg
void drawLeg(float angle) {
    
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);  // Gray color for the leg
    glTranslatef(-0.2f, -0.3f, 0.0f);  // Translate to position below torso
    glRotatef(angle, 1.0f, 0.0f, 0.0f);  // Rotate the leg for movement
    glScalef(1.0f, 1.0f, 1.0f);  // Elongate cylinder for the thigh
    GLUquadric* thigh = gluNewQuadric();
    gluCylinder(thigh, 0.18, 0.18, 1.5, 20, 20);  // Draw thigh cylinder
    
    glPopMatrix();
    


}


// Function to draw the cannon (gun)
void drawCannon() {

}

// Display callback to draw the 3D bot
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set up camera and view
    glLoadIdentity();
    gluLookAt(5 * cos(cameraAngle * M_PI / 180.0), 2.0, 5 * sin(cameraAngle * M_PI / 180.0),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);  // Camera view

    // Draw body parts
    drawTorso();   // Draw the new torso with details
    drawHead();    // Head with visor
    drawArm(rightArmAngle);
    drawTriangle();  // Call our custom function to draw the triangle
    drawQuad();
    drawCube();

    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);  // Mirror for left arm
    drawArm(leftArmAngle);
    glPopMatrix();
    drawLeg(rightLegAngle);
    glPushMatrix();
    glScalef(-1.0f, 1.0f, 1.0f);  // Mirror for left leg
    drawLeg(leftLegAngle);
    glPopMatrix();

    glutSwapBuffers();  // Double buffer swap
}



// Timer function to animate the spinning cannon
void updateCannon(int value) {
    cannonAngle += 1.0f;
    if (cannonAngle > 360.0f) cannonAngle -= 360.0f;
    glutPostRedisplay();
    glutTimerFunc(16, updateCannon, 0);  // Re-register timer
}

// Keyboard callback to control bot's joints and animation
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':  // Rotate right arm
            rightArmAngle += 5.0f;
            if (rightArmAngle > 360.0f) rightArmAngle -= 360.0f;
            break;
        case 'A':  // Rotate left arm
            leftArmAngle += 5.0f;
            if (leftArmAngle > 360.0f) leftArmAngle -= 360.0f;
            break;
        case 'd':  // Rotate right leg
            rightLegAngle += 5.0f;
            if (rightLegAngle > 360.0f) rightLegAngle -= 360.0f;
            break;
        case 'D':  // Rotate left leg
            leftLegAngle += 5.0f;
            if (leftLegAngle > 360.0f) leftLegAngle -= 360.0f;
            break;
        case 27:  // ESC key to quit
            exit(0);
            break;
    }
    glutPostRedisplay();  // Redraw with updated angles
}

// Special keyboard callback to rotate the camera with arrow keys
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            cameraAngle -= 5.0f;  // Rotate camera left
            break;
        case GLUT_KEY_RIGHT:
            cameraAngle += 5.0f;  // Rotate camera right
            break;
    }
    glutPostRedisplay();  // Redraw with updated camera position
}
void initLighting() {
    // Enable lighting and set up light properties
    glEnable(GL_LIGHTING);  // Enable lighting globally
    glEnable(GL_LIGHT0);    // Enable light 0 (main light source)
    
    // Set light 0's position and color properties
    GLfloat lightPos[] = { 2.0f, 2.0f, 2.0f, 1.0f };  // Position of the light (x, y, z, w)
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };  // Diffuse color (white light)
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // Ambient color (general lighting)
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Specular color for highlights
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Optional: Add a second light source (light 1) for better lighting
    glEnable(GL_LIGHT1);  // Enable another light
    GLfloat lightPos1[] = { -2.0f, 2.0f, -2.0f, 1.0f };  // Position for the second light
    GLfloat lightDiffuse1[] = { 0.7f, 0.7f, 0.7f, 1.0f };  // Slightly dimmer diffuse light
    GLfloat lightAmbient1[] = { 0.1f, 0.1f, 0.1f, 1.0f };  // Lower ambient light
    GLfloat lightSpecular1[] = { 0.9f, 0.9f, 0.9f, 1.0f };  // Specular highlight

    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);

    // Enable materials to reflect the lighting
    glEnable(GL_COLOR_MATERIAL);  // Enable material reflection of lighting
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  // Apply material settings to front of objects
}




// Initialize the OpenGL environment
void init() {
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glShadeModel(GL_SMOOTH);  // Enable smooth shading
    

    // Lighting setup
    initLighting();
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    
    
    // Set up projection and camera
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 150.0);  // Perspective projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(180.0 ,90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0, 90.0);  // Camera setup
    
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Enable depth buffer
    glutInitWindowSize(600, 600);
    glutCreateWindow("Robocop Bot");

    init();  // Call initialization function

    glutDisplayFunc(display);  // Register display callback
    glutKeyboardFunc(keyboard);  // Register keyboard callback
    glutSpecialFunc(specialKeys);  // Register special keys for camera
    glutTimerFunc(16, updateCannon, 0);  // Start animation loop

    glutMainLoop();  // Enter GLUT main loop
    return 0;
}
