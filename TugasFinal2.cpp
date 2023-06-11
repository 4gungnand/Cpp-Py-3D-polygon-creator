#include <GL/glut.h>

// Variables for rotation and translation
float rotationAngle = 0.0f;
float rotationSpeed = 1.0f;
float translationX = 0.0f;
float translationSpeed = 0.02f;

// Function for drawing the airplane
void drawAirplane() {
    // Fuselage
    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireCube(1.0f);

    // Wings
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(2.0f, 0.1f, 0.5f);
    glutWireCube(1.0f);
    glPopMatrix();

    // Tail
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-0.75f, 0.0f, 0.0f);
    glScalef(0.5f, 0.1f, 0.2f);
    glutWireCube(1.0f);
    glPopMatrix();
}

// Function for displaying the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Translate the object
    glTranslatef(translationX, 0.0f, -5.0f);

    // Rotate the object
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    // Draw the airplane
    drawAirplane();

    glutSwapBuffers();
}

// Function for updating the scene
void update(int value) {
    // Update the rotation angle
    rotationAngle += rotationSpeed;

    // Update the translation
    translationX += translationSpeed;

    // Reverse the translation direction if reaching the edges
    if (translationX > 2.0f || translationX < -2.0f)
        translationSpeed *= -1.0f;

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
    glutCreateWindow("Airplane Animation");

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    // Set the clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 10.0);

    // Register callback functions
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    // Start the main loop
    glutMainLoop();

    return 0;
}
