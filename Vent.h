class Vent
{
public:
  virtual bool dedans(float x, float y, float z) = 0;

  void dessineVoxel()
  {
    int n = 50;
      for (size_t i = 0; i < n; i++)
      {
        for (size_t j = 0; j < n; j++)
        {
          for(size_t k = 0; k< n ; k++)
          {
          float fi = (float)i / (float)n;
          float fj = (float)j / (float)n;
          float fk = (float)k / (float)n;
          if (dedans(fi, fj, fk))
          { glPushMatrix();
            glColor3f(1, 1, 1);
            glTranslatef(fi, fj, fk);
            glutSolidCube(0.1);
            glPopMatrix();
          }
        }
      }
    }

  }
};
