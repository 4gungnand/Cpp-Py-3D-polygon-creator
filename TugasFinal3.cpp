#include <GL/glut.h>

// Variables for animation
float translationZ = -10.0f;
float translationSpeed = 0.05f;
float splitTranslation = 0.0f;
float splitSpeed = 0.01f;
float rotationAngleTop = 0.0f;
float rotationAngleBottom = 0.0f;
float rotationSpeed = 0.2f;

// Function for drawing the octahedron
void drawOctahedron() {
    // Set color to blue
    glColor3f(0.0f, 0.0f, 1.0f);

    // Split translation offset
    float offset = splitTranslation / 2.0f;

    // Draw the wireframe octahedron
    glBegin(GL_LINES);
    // Top pyramid
    glVertex3f(0.0f, 1.0f + offset, 0.0f);
    glVertex3f(1.0f, 0.0f + offset, 0.0f);
    glVertex3f(0.0f, 1.0f + offset, 0.0f);
    glVertex3f(-1.0f, 0.0f + offset, 0.0f);
    glVertex3f(0.0f, 1.0f + offset, 0.0f);
    glVertex3f(0.0f, 0.0f + offset, 1.0f);
    glVertex3f(0.0f, 1.0f + offset, 0.0f);
    glVertex3f(0.0f, 0.0f + offset, -1.0f);
    // Bottom pyramid
    glVertex3f(0.0f, -1.0f - offset, 0.0f);
    glVertex3f(1.0f, 0.0f - offset, 0.0f);
    glVertex3f(0.0f, -1.0f - offset, 0.0f);
    glVertex3f(-1.0f, 0.0f - offset, 0.0f);
    glVertex3f(0.0f, -1.0f - offset, 0.0f);
    glVertex3f(0.0f, 0.0f - offset, 1.0f);
    glVertex3f(0.0f, -1.0f - offset, 0.0f);
    glVertex3f(0.0f, 0.0f - offset, -1.0f);
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

    // Rotate the entire object
    glRotatef(rotationAngleTop, 0.0f, 1.0f, 0.0f);

    // Draw the top pyramid
    drawOctahedron();

    // Save the current matrix
    glPushMatrix();

    // Rotate the bottom pyramid
    glRotatef(rotationAngleBottom, 0.0f, 1.0f, 0.0f);

    // Draw the bottom pyramid
    drawOctahedron();

    // Restore the matrix
    glPopMatrix();

    glutSwapBuffers();
}

// Function for updating the scene
void update(int value) {
    // Update the translation along the z-axis
    translationZ += translationSpeed;

    // Reverse the translation direction if reaching the desired position
    if (translationZ > 0.0f)
        translationSpeed *= -1.0f;

    // Update the split translation
    splitTranslation += splitSpeed;

    // Reverse the split translation direction if reaching the desired position
    if (splitTranslation > 0.5f || splitTranslation < -0.5f)
        splitSpeed *= 0.0f;

    // Update the rotation angles
    rotationAngleTop += rotationSpeed;
    rotationAngleBottom -= rotationSpeed;

    // Redisplay the scene
    glutPostRedisplay();

    // Call update function again after 16 milliseconds (60 FPS)
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Splitting Octahedron");

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}
