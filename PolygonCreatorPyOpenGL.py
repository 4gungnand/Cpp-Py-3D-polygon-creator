'''
Buatlah program grafik utk membuat gambar objek 3D original karya saudara yg dilengkapi animasinya. Yg diupload data objek 3D, coding dan video running program nya dlm bentuk zip atau rar
'''

import pygame
from pygame.locals import *

from OpenGL.GL import *
from OpenGL.GLU import *

colors = (
    (1, 0, 0),  # Red (ABC)
    (0, 1, 0),  # Green (ACD)
    (0, 0, 1),  # Blue (ADE)
    (1, 1, 0),  # Yellow (AEB)
    (1, 0, 1),  # Magenta (BCF)
    (0, 1, 1),  # Cyan (CDF)
    (1, 1, 1),  # White (DEF)
    (0.5, 0.5, 0.5)  # Gray (EFB)
)

class Polyhedron:
    
    def __init__(self, vertices, faces):
        self.vertices = vertices
        self.faces = faces
        
    def draw(self):        
        # draw faces
        glBegin(GL_QUADS)
        for i, face in enumerate(self.faces):
            glColor3fv(colors[i])
            for vertex_index in face:
                vertex = self.vertices[vertex_index-1]
                glVertex3fv(vertex)
        glEnd()
        
    @staticmethod
    def from_text_file(filename):
        rows, cols, vertices, faces = Polyhedron.parse_text_file(filename)
        return Polyhedron(vertices, faces)

    @staticmethod
    def parse_text_file(filename):
        try:
            with open(filename, 'r') as file:
                content = file.read()
            
            lines = content.splitlines()
            rows, cols = map(int, lines[0].split())
            
            vertices = []
            for line in lines[1:rows+1]:
                vertex = list(map(float, line.split()))
                vertices.append(vertex)
            
            faces = []
            for line in lines[rows+1:]:
                # ex: 4 1 2 6 5, where the first line indicates the number of vertices in the face
                face = list(map(int, line.split()))
                face.pop(0) # remove first elemnt
                faces.append(face)
            
            return rows, cols, vertices, faces

        except IOError:
            print(f"Error: Unable to read file '{filename}'.")

    def __str__(self):
        return f"Polyhedron(\nvertices={self.vertices}, \nfaces={self.faces}), \nvertices={len(self.vertices)},\nfaces={len(self.faces)}\n)"

def draw_torus():
    poly = Polyhedron.from_text_file(filename="text.txt")
    poly.draw()
    

def main():
    global surfaces

    pygame.init()
    display = (800, 600)
    screen = pygame.display.set_mode(display, DOUBLEBUF|OPENGL)
    clock = pygame.time.Clock()

    glMatrixMode(GL_PROJECTION)
    gluPerspective(45, (display[0]/display[1]), 0.1, 50.0)

    glMatrixMode(GL_MODELVIEW)
    glTranslatef(0, 0, -5)
    
    # background image
    glClearColor(0.5, 0.5, 0.5, 0.0)

    #glLight(GL_LIGHT0, GL_POSITION,  (0, 0, 1, 0)) # directional light from the front
    glLight(GL_LIGHT0, GL_POSITION,  (5, 5, 5, 1)) # point light from the left, top, front
    glLightfv(GL_LIGHT0, GL_AMBIENT, (0, 0, 0, 1))
    glLightfv(GL_LIGHT0, GL_DIFFUSE, (1, 1, 1, 1))

    glEnable(GL_DEPTH_TEST) 

    while True:        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()      

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)

        glEnable(GL_LIGHTING)
        glEnable(GL_LIGHT0)
        glEnable(GL_COLOR_MATERIAL)
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE )

        glRotatef(1, 3, 1, 1)
        draw_torus()

        glDisable(GL_LIGHT0)
        glDisable(GL_LIGHTING)
        glDisable(GL_COLOR_MATERIAL)

        pygame.display.flip()
        clock.tick(60)

main()