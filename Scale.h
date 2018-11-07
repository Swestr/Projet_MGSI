class Scale : public Vent
{
  public:
    float u, v, w;
    Vent *f;
    Scale(float u1,float v1,float w1, Vent *a){
      f = a;
      u = u1;
      v = v1;
      w = w1;
    }
    bool dedans(float x, float y, float z){
      return f->dedans(x/u, y/v, z/w);
    }
};
