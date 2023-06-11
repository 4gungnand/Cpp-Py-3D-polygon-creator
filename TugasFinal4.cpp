#include <GL/glut.h>

// Variables for animation and lighting
float translationZ = -20.0f;
float translationSpeed = 0.005f;
float splitTranslation = 0.0f;
float splitSpeed = 0.005f;
float rotationAngleTop = 0.0f;
float rotationAngleBottom = 0.0f;
float rotationSpeed = 0.2f;

// Function for drawing the top pyramid
void drawTopPyramid()
{
    // Define the pyramid vertices
    GLfloat pyramidVertices[][3] = {
        {0.0f, 1.0f, 0.0f},
        {1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f}
    };

    // Define the pyramid face indices
    GLint pyramidFaces[][3] = {
        {0, 1, 2},
        {0, 2, 3},
        {0, 3, 4},
        {0, 4, 1},
        {1, 3, 2},
        {1, 4, 3}
    };

    // Set material properties for the pyramid
    GLfloat pyramidAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat pyramidDiffuse[] = {0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat pyramidSpecular[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat pyramidShininess = 100.0f;

    // Set the pyramid material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT, pyramidAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pyramidDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pyramidSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, pyramidShininess);

    // Draw the pyramid faces
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 6; ++i)
    {
        glNormal3fv(pyramidVertices[pyramidFaces[i][0]]);
        glVertex3fv(pyramidVertices[pyramidFaces[i][0]]);

        glNormal3fv(pyramidVertices[pyramidFaces[i][1]]);
        glVertex3fv(pyramidVertices[pyramidFaces[i][1]]);

        glNormal3fv(pyramidVertices[pyramidFaces[i][2]]);
        glVertex3fv(pyramidVertices[pyramidFaces[i][2]]);
    }
    glEnd();
}

// Function for drawing the bottom pyramid
void drawBottomPyramid()
{
    // Define the pyramid vertices
    GLfloat pyramidVertices[][3] = {
        {0.0f, -1.0f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, -1.0f}
    };

    // Define the pyramid face indices
    GLint pyramidFaces[][3] = {
        {0, 1, 2},
        {0, 2, 3},
        {0, 3, 4},
        {0, 4, 1},
        {1, 3, 2},
        {1, 4, 3}
    };

    // Set material properties for the pyramid
    GLfloat pyramidAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat pyramidDiffuse[] = {0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat pyramidSpecular[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat pyramidShininess = 100.0f;

    // Set the pyramid material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT, pyramidAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pyramidDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pyramidSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, pyramidShininess);

    // Draw the pyramid faces
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 6; ++i)
    {
        glNormal3fv(pyramidVertices[pyramidFaces[i][0]]);
        glVertex3fv(pyramidVertices[pyramidFaces[i][0]]);

        glNormal3fv(pyramidVertices[pyramidFaces[i][1]]);
        glVertex3fv(pyramidVertices[pyramidFaces[i][1]]);

        glNormal3fv(pyramidVertices[pyramidFaces[i][2]]);
        glVertex3fv(pyramidVertices[pyramidFaces[i][2]]);
    }
    glEnd();
}

// Function for displaying the scene
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the light position
    GLfloat lightPosition[] = {1.0f, 1.0f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Set the camera position
    gluLookAt(2.0, 2.0, -20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // // Draw the top pyramid
    // glPushMatrix();
    // glTranslatef(0.0f, 1.0f, 0.0f);
    // glRotatef(rotationAngleTop, 0.0f, 1.0f, 0.0f);
    // drawTopPyramid();
    // glPopMatrix();

    // Draw the bottom pyramid
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glRotatef(rotationAngleBottom, 0.0f, 1.0f, 0.0f);
    drawBottomPyramid();
    glPopMatrix();

    glutSwapBuffers();
}

// Function for updating the scene
void update(int value)
{
    // Update the translation along the z-axis
    translationZ += translationSpeed;

    // Reverse the translation direction if reaching the desired position
    if (translationZ > -10.0f || translationZ < -30.0f)
        translationSpeed *= -1.0f;

    // Update the split translation
    splitTranslation += splitSpeed;

    // Reverse the split translation direction if reaching the desired position
    if (splitTranslation > 0.5f || splitTranslation < 0.0f)
        splitSpeed *= -1.0f;

    // Update the rotation angles for the top and bottom pyramids
    rotationAngleTop += rotationSpeed;
    rotationAngleBottom -= rotationSpeed;

    // Redisplay the scene
    glutPostRedisplay();

    // Call update function again after 16 milliseconds (60 FPS)
    glutTimerFunc(16, update, 0);
}

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Splitting Octahedron");

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    // Enable lighting and set light properties
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set light properties
    GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Set the clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);

    // Register callback functions
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    // Start the main loop
    glutMainLoop();

    return 0;
}
