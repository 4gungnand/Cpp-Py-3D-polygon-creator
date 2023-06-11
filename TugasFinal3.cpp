#include <GL/glut.h>

// Variables for animation
float translationZ = 0.0f;
float translationSpeed = 0.05f;
float splitTranslation = 0.0f;
float splitSpeed = 0.01f;
float rotationAngleTop = 0.0f;
float rotationAngleBottom = 0.0f;
float rotationSpeed = 1.0f;

// Function for drawing the octahedron
void drawOctahedron() {
    // Set color to blue
    glColor3f(0.0f, 0.0f, 1.0f);

    // Split translation offset
    float offset = splitTranslation / 2.0f;

    // Draw the wireframe octahedron
    glBegin(GL_LINES);
    // Top pyramid
    glPushMatrix();
    glRotatef(rotationAngleTop, 0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f + offset, 0.0f);
    glVertex3f(1.0f, 0.0f + offset, 0.0f);
    glVertex3f(0.0f, 1.0f + offset, 0.0f);
    glVertex3f(-1.0f, 0.0f + offset, 0.0f);
    glVertex3f(0.0f, 1.0f + offset, 0.0f);
    glVertex3f(0.0f, 0.0f + offset, 1.0f);
    glVertex3f(0.0f, 1.0f + offset, 0.0f);
    glVertex3f(0.0f, 0.0f + offset, -1.0f);
    glPopMatrix();

    // Bottom pyramid
    glPushMatrix();
    glRotatef(rotationAngleBottom, 0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f - offset, 0.0f);
    glVertex3f(1.0f, 0.0f - offset, 0.0f);
    glVertex3f(0.0f, -1.0f - offset, 0.0f);
    glVertex3f(-1.0f, 0.0f - offset, 0.0f);
    glVertex3f(0.0f, -1.0f - offset, 0.0f);
    glVertex3f(0.0f, 0.0f - offset, 1.0f);
    glVertex3f(0.0f, -1.0f - offset, 0.0f);
    glVertex3f(0.0f, 0.0f - offset, -1.0f);
    glPopMatrix();

    // Side edges for top 
    glVertex3f(1.0f, 0.0f + offset, 0.0f);
    glVertex3f(0.0f, 0.0f + offset, 1.0f);
    glVertex3f(-1.0f, 0.0f + offset, 0.0f);
    glVertex3f(0.0f, 0.0f + offset, 1.0f);
    glVertex3f(1.0f, 0.0f + offset, 0.0f);
    glVertex3f(0.0f, 0.0f + offset, -1.0f);
    glVertex3f(-1.0f, 0.0f + offset, 0.0f);
    glVertex3f(0.0f, 0.0f + offset, -1.0f);

    // Side edges for bottom
    glVertex3f(1.0f, 0.0f - offset, 0.0f);
    glVertex3f(0.0f, 0.0f - offset, 1.0f);
    glVertex3f(-1.0f, 0.0f - offset, 0.0f);
    glVertex3f(0.0f, 0.0f - offset, 1.0f);
    glVertex3f(1.0f, 0.0f - offset, 0.0f);
    glVertex3f(0.0f, 0.0f - offset, -1.0f);
    glVertex3f(-1.0f, 0.0f - offset, 0.0f);
    glVertex3f(0.0f, 0.0f - offset, -1.0f);
    glEnd();
}

// Function for displaying the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Translate the object
    glTranslatef(0.0f, 0.0f, translationZ);

    // Draw the octahedron
    drawOctahedron();

    glutSwapBuffers();
}

// Function for updating the scene
void update(int value) {
    // Update the translation along the z-axis
    translationZ -= translationSpeed;

    // Reverse the translation direction if reaching the desired position
    if (translationZ < -10.0f)
        translationSpeed = 0.0f;

    // Update the split translation
    splitTranslation += splitSpeed;

    // Reverse the split translation direction if reaching the desired position
    if (splitTranslation > 0.5f || splitTranslation < -0.5f)
        splitSpeed = 0.0f;
    
    // Update the rotation angles
    rotationAngleTop += rotationSpeed;
    rotationAngleBottom -= rotationSpeed;

    // Redisplay the scene
    glutPostRedisplay();

    // Call update function again after 16 milliseconds (60 FPS)
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Splitting Octahedron");

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

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
