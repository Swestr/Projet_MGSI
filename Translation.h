class Translation : public Vent
{
  public:
    float u, v, w;
    Vent *f;
    Translation(float x, float y, float z, Vent *fig)
    {
      u = x;
      v = y;
      w = z;
      f = fig;
    }
    bool dedans(float x, float y, float z)
    {
      return f->dedans(x - u, y - v, z - w);
    }
};
