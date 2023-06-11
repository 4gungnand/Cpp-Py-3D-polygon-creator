#include <GL/glut.h>

// Variables for rotation
float rotationAngle = 0.0f;
float rotationSpeed = 1.0f;

// Function for drawing the object
void drawObject() {
    // Set color to green
    glColor3f(0.0f, 1.0f, 0.0f);

    // Draw a cube
    glutWireCube(1.0f);
}

// Function for displaying the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Translate the object away from the camera
    glTranslatef(0.0f, 0.0f, -2.0f);

    // Rotate the object
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    // Draw the object
    drawObject();

    glutSwapBuffers();
}

// Function for updating the scene
void update(int value) {
    // Update the rotation angle
    rotationAngle += rotationSpeed;

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
    glutCreateWindow("OpenGL Animation");

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
