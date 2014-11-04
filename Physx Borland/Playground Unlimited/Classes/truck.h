class Vehicle {
  private:

  Textures* htex;
  int txc;
  int txw;

  public:

  double body;

  double j1,j2,j3,j4,s1,s2;

  double wheel1;
  double wheel1_a;

  double wheel2;
  double wheel2_a;

  int keys[3]; //Places for keys

  Vehicle(double x, double y, double polygon_id, Textures* texture_handle, int texture_car, int texture_wheel);
  void Destroy();
  ~Vehicle();

  //Drawing Routines
  void Draw();

  //Car functions
  void Drive(float speed);
  void Jump(float dir, float power);
  void NoCollide(Vehicle* v);

  //Texture functions
  void SetWheelTexture(int texture_id);
  void SetBodyTexture(int texture_id);

  //Data
  double getX();
  double getY();

  //Key Presses
  void SetKeys(int key_left, int key_up, int key_right);

  //Override Updating Method
  void Update();
};

Vehicle::Vehicle(double x, double y, double polygon_id, Textures* texture_handle, int texture_car, int texture_wheel) {
  //Create Texture Handle
  htex=texture_handle;

  //Texture ID's for Body and Wheels
  txc = texture_car;
  txw = texture_wheel;

  //Dynamic Body
  body = g.CreateBody(x,y,1,SHAPE_TRIMESH,polygon_id,0,0);

  //Back Wheel
  wheel1 = g.CreateBody(x-40,y+18,1,SHAPE_SPHERE,24,0,0);
  wheel1_a = g.CreateBody(x-40,y+18,1,SHAPE_SPHERE,12,0,0);

  //Front Wheel
  wheel2 = g.CreateBody(x+40,y+18,1,SHAPE_SPHERE,24,0,0);
  wheel2_a = g.CreateBody(x+40,y+18,1,SHAPE_SPHERE,12,0,0);

  //Connect Wheel Axels To Car
  j1=CreateJoint(body, wheel1_a, JOINT_SLIDER, GetBodyX(body)-40, GetBodyY(body)+29,90);
  j2=CreateJoint(body, wheel2_a, JOINT_SLIDER, GetBodyX(body)+40, GetBodyY(body)+29,90);

  //Line Size
  SetLineSize(8);

  //Limit Joints
  SetSliderLimits(j1, -5, 15);
  SetSliderLimits(j2, -5, 15);

  //Keep Wheel Axles On Car
  s1=CreateSpring(body, wheel1_a, GetBodyX(body)-40, GetBodyY(body), GetBodyX(body)-40, GetBodyY(body)+40, 100, 100, 200, 0);
  s2=CreateSpring(body, wheel2_a, GetBodyX(body)+40, GetBodyY(body), GetBodyX(body)+40, GetBodyY(body)+40, 100, 100, 200, 0);

  //Stop Wheel Axles from Colliding with Car
  SetBodyCollide(body, wheel1, false);
  SetBodyCollide(body, wheel2, false);
  SetBodyCollide(body, wheel1_a, false);
  SetBodyCollide(body, wheel2_a, false);

  //Attach Wheels to Axles & Make Wheels Like Wheels
  SetBodyMaterial(wheel1, 0.5, 2, 0);
  SetBodyMaxRotationSpeed(wheel1,450);
  SetBodyCollide(wheel1, wheel1_a, false);
  j3=CreateJoint(wheel1, wheel1_a, JOINT_HINGE, GetBodyX(wheel1), GetBodyY(wheel1),0);

  //Make Wheels Roll on the Ground
  SetBodyMaterial(wheel2, 0.5, 2, 0);
  SetBodyMaxRotationSpeed(wheel2,450);
  SetBodyCollide(wheel2, wheel2_a, false);
  j4=CreateJoint(wheel2, wheel2_a, JOINT_HINGE, GetBodyX(wheel2), GetBodyY(wheel2),0);
}

inline void Vehicle::NoCollide(Vehicle* v) {
  SetBodyCollide(body, v->body, false);
  SetBodyCollide(body, v->wheel1, false);
  SetBodyCollide(body, v->wheel2, false);
  SetBodyCollide(body, v->wheel1_a, false);
  SetBodyCollide(body, v->wheel2_a, false);

  SetBodyCollide(wheel1, v->body, false);
  SetBodyCollide(wheel1, v->wheel1, false);
  SetBodyCollide(wheel1, v->wheel2, false);
  SetBodyCollide(wheel1, v->wheel1_a, false);
  SetBodyCollide(wheel1, v->wheel2_a, false);

  SetBodyCollide(wheel2, v->body, false);
  SetBodyCollide(wheel2, v->wheel1, false);
  SetBodyCollide(wheel2, v->wheel2, false);
  SetBodyCollide(wheel2, v->wheel1_a, false);
  SetBodyCollide(wheel2, v->wheel2_a, false);

  SetBodyCollide(wheel1_a, v->body, false);
  SetBodyCollide(wheel1_a, v->wheel1, false);
  SetBodyCollide(wheel1_a, v->wheel2, false);
  SetBodyCollide(wheel1_a, v->wheel1_a, false);
  SetBodyCollide(wheel1_a, v->wheel2_a, false);

  SetBodyCollide(wheel2_a, v->body, false);
  SetBodyCollide(wheel2_a, v->wheel1, false);
  SetBodyCollide(wheel2_a, v->wheel2, false);
  SetBodyCollide(wheel2_a, v->wheel1_a, false);
  SetBodyCollide(wheel2_a, v->wheel2_a, false);
}

inline void Vehicle::Draw() {
  glEnable(GL_TEXTURE_2D);
  htex->SetTexture(txw);
  DrawBox(GetBodyX(wheel1),GetBodyY(wheel1),48,48,GetBodyRotation(wheel1));
  DrawBox(GetBodyX(wheel2),GetBodyY(wheel2),48,48,GetBodyRotation(wheel2));
  glColor3f(1.0f,1.0f,1.0f);
  htex->SetTexture(txc);
  DrawBox(GetBodyX(body),GetBodyY(body),128,64,GetBodyRotation(body));
  glDisable(GL_TEXTURE_2D);
}

Vehicle::~Vehicle() {
  Destroy();
}

void Vehicle::Destroy() {
  DestroySpring(s1);
  DestroySpring(s2);
  DestroyJoint(j1);
  DestroyJoint(j2);
  DestroyJoint(j3);
  DestroyJoint(j4);
  DestroyBody(body);
  DestroyBody(wheel1);
  DestroyBody(wheel1_a);
  DestroyBody(wheel2);
  DestroyBody(wheel2_a);
}

inline void Vehicle::Drive(float speed) {
  AddTorque(wheel1,speed,0);
  AddTorque(wheel2,speed,0);
}

inline void Vehicle::SetWheelTexture(int texture_id) {
  txw = texture_id;
}

inline void Vehicle::SetBodyTexture(int texture_id) {
  txc = texture_id;
}

inline double Vehicle::getX() {
  return(GetBodyX(body));
}

inline double Vehicle::getY() {
  return(GetBodyY(body));
}

inline void Vehicle::Jump(float dir,float power) {
  AddForce(body,-sin((pi/180)*(dir+90))*(float)power*100,-cos((pi/180)*(dir+90))*(float)power*100,0);
}

inline void Vehicle::SetKeys(int key_left, int key_up, int key_right) {
  keys[0]=key_left;
  keys[1]=key_up;
  keys[2]=key_right;
}

inline void Vehicle::Update() {
  if (GetAsyncKeyState(keys[0])) Drive(50);
  if (GetAsyncKeyState(keys[2])) Drive(-50);
}
