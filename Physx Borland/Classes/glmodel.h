class Model {
  private:

  GLuint id;

  public:

  Model() {
    id=glGenLists(1);
  }

  void StartModel() {
    glNewList(id,GL_COMPILE);
  }

  void EndModel() {
    glEndList();
  }

  void Draw() {
    glCallList(id);
  }
};