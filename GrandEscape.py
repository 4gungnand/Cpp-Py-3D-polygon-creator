from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *


def load_object(filename):
    vertices = []
    polygons = []
    with open(filename, 'r') as file:
        num_vertices, num_polygons = map(int, file.readline().split())

        for _ in range(num_vertices):
            vertex = list(map(float, file.readline().split()))
            vertices.append(vertex)

        for _ in range(num_polygons):
            polygon = list(map(int, file.readline().split()))
            polygons.append(polygon[1:])  # Ignore the first value (number of vertices)

    return vertices, polygons


def draw_object(vertices, polygons):
    glBegin(GL_TRIANGLES)
    for polygon in polygons:
        for vertex_index in polygon:
            vertex = vertices[vertex_index - 1]
            glVertex3fv(vertex)
    glEnd()


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glRotatef(1, 3, 1, 1)
    draw_object(vertices, polygons)
    glutSwapBuffers()


# Main function
if __name__ == "__main__":
    # Load vertices and polygons from a text file
    filename = "object.txt"  # Replace with your own file name
    vertices, polygons = load_object(filename)

    glutInit()
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH)
    glutInitWindowSize(800, 600)
    glutCreateWindow(b"OpenGL Object")
    glEnable(GL_DEPTH_TEST)
    glutDisplayFunc(display)
    glutIdleFunc(display)
    glMatrixMode(GL_PROJECTION)
    gluPerspective(45, 800 / 600, 0.1, 50.0)
    glMatrixMode(GL_MODELVIEW)
    gluLookAt(0, 0, -5, 0, 0, 0, 0, 1, 0)
    glutMainLoop()
