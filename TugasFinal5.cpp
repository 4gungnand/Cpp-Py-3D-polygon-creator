#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <vector>

// Define a struct to represent a vertex
struct Vertex
{
    float x, y, z;
};

// Define a struct to represent a polygon
struct Polygon
{
    std::vector<int> vertices;
};

// Define vectors to store vertices and polygons
std::vector<Vertex> vertices;
std::vector<Polygon> polygons;

// Function for reading the object data from a text file
bool readObjectData(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to open file: " << filename << std::endl;
        return false;
    }

    int numVertices, numPolygons;
    file >> numVertices >> numPolygons;

    // Read the vertices
    vertices.resize(numVertices);
    for (int i = 0; i < numVertices; ++i)
    {
        file >> vertices[i].x >> vertices[i].y >> vertices[i].z;
    }

    // Read the polygons
    polygons.resize(numPolygons);
    for (int i = 0; i < numPolygons; ++i)
    {
        int numVertices;
        file >> numVertices;
        polygons[i].vertices.resize(numVertices);
        for (int j = 0; j < numVertices; ++j)
        {
            file >> polygons[i].vertices[j];
        }
    }

    file.close();
    return true;
}

// Function for rendering the object
void renderObject()
{
    // Disable lighting for flat colors
    glDisable(GL_LIGHTING);

    for (int i = 0; i < polygons.size(); ++i)
    {
        const Polygon &polygon = polygons[i];

        // Assign a color for each polygon
        if (i % 2 == 0)
        {
            // Blue-ish color for even-indexed polygons
            glColor3f(0.0f, 0.0f, 1.0f);
        }
        else
        {
            // Cyan-ish color for odd-indexed polygons
            glColor3f(0.0f, 1.0f, 1.0f);
        }

        glBegin(GL_POLYGON);
        for (int vertexIndex : polygon.vertices)
        {
            const Vertex &vertex = vertices[vertexIndex - 1];
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
        glEnd();
    }

    // Re-enable lighting for other objects in the scene if needed
    glEnable(GL_LIGHTING);
}

// Variables for animation
float rotationAngle = 0.0f;
float rotationSpeed = 1.0f; // Adjust this value to change the rotation speed
// Scaling factor for the cube
float scaleFactor = 0.5f; // Adjust this value to change the size of the cube
float translateZ = 0.0f;
float translationSpeed = 0.05f;

// Function for displaying the scene
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Translate and rotate the object
    glTranslatef(0.0f, 0.0f, translateZ);
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.5f);

    // Apply scale factor
    glScalef(scaleFactor, scaleFactor, scaleFactor);

    // Render the object
    renderObject();

    glutSwapBuffers();
}

// Function for updating the scene
void update(int value)
{
    // Update the rotation angle
    rotationAngle += rotationSpeed;
    
    // Redisplay the scene
    glutPostRedisplay();

    // Call update function again after a certain interval
    glutTimerFunc(16, update, 0);
}

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Render Objek Sederhana");

    // Load the object data from a file
    if (!readObjectData("object.txt"))
    {
        return 1;
    }

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);

    // Enable depth testing and smooth shading
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    // Enable lighting and set up a light source
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPosition[] = {10.0, 10.0, 10.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Set the polygon rasterization mode to fill
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Register display callback function
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    // Start the main loop
    glutMainLoop();

    return 0;
}
