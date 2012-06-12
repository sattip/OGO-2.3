    /*
 * Player object -- see header file for more info
 */

#if defined _WIN32
	#include <gl\freeglut.h>
#elif defined __APPLE__
	#include <GL/freeglut.h>
#else
	#include <GL/freeglut.h>
#endif

#include "player.h"

namespace Objects {

using namespace std;

//------------------------------------------------------------------------------

Player::Player(Id _id, unsigned char _team, string _name, Pd P, Qd R, BoundingBox B)
	: BoundedObject(P, R, B)
{
	id = _id;
	team = _team;
	name = _name;

	model.head = ModelObjectContainer();
	model.body = ModelObjectContainer();
	model.weapon = ModelObjectContainer();
	model.tool = ModelObjectContainer();
	model.wheel = ModelObjectContainer();
	model.head->children.insert(Assets::Model::HeadObj);
	model.body->children.insert(Assets::Model::BodyObj);
	model.weapon->children.insert(Assets::Model::GunObj);
	model.tool->children.insert(Assets::Model::WrenchObj);
	model.wheel->children.insert(Assets::Model::WheelObj);
	children.insert(model.head);
	children.insert(model.body);
	children.insert(model.weapon);
	children.insert(model.tool);
	children.insert(model.wheel);

	//set textures
	model.head->material = Assets::Model::HeadTex;
	model.body->material = Assets::Model::BodyTex[team-'a'];
	model.weapon->material = Assets::Model::GunTex;
	model.wheel->material = Assets::Model::WheelTex[team-'a'];
	model.tool->material = Assets::Model::WrenchTex;

	//set position of seperate elements
	velocity = Vd(0,0,0);
	update(R);

	translateModel();
}

//------------------------------------------------------------------------------

Player::~Player()
{
}

//------------------------------------------------------------------------------

inline void translate(ObjectHandle o, double x, double y, double z) {
	o->origin = o->origin + Vd(x,y,z);
}

void Player::translateModel() {
	translate(model.head,0,0,1.95);
	translate(model.body,0,0,0.3);
	translate(model.weapon,-0.499,-0.037,1.333);
	translate(model.tool,0.544,-0.037,1.333);
	translate(model.wheel,0,0,0.3);
}

//------------------------------------------------------------------------------

const Vd Player::maxVelocity = Vd(0,1,0);

void Player::update(const Qd &camobj) {
	//if (velocity.y < 1) velocity.y += 0.01;

	if (velocity.y != oldVelocity.y) {
		oldVelocity = velocity;

		rotation = Qd();
		double angle = velocity.y / maxVelocity.y * 0.15f * Pi;
		rotation = rotation * Rd(angle,Vd(1,0,0));
		
		model.weapon->rotation = -rotation;
		model.tool->rotation = -rotation;
	}

	model.head->rotation = camobj;
}

//------------------------------------------------------------------------------
    
void applyBillboarding(){
    float m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX , m);
        //set look and up-vector to identity vertices
    float billBoardedMatrix[16] = { 1   ,     0,     0,   m[3],
                                    m[4]   ,  m[5], m[6],   m[7],
                                       0,     0,     1,  m[11],
                                   m[12], m[13], m[14],  m[15]};
    glLoadMatrixf(billBoardedMatrix);     
}
    
    //TODO: Color for teams, for ferry maybe use projection matrix
void Player::render(){
    glDisable(GL_LIGHTING);
    MaterialHandle teamcolor = ColorMaterial(0.0, 1.0, 0.0,1.0f);
    glPushMatrix();
		glTranslated(origin.x,origin.y,origin.z+2.7);
		glRotated(90,1,0,0);//Revert custom axis
		glPushMatrix();
			applyBillboarding();
			glScalef(0.002, 0.002, 0.002);    //Scale down
			double w = glutStrokeLength(GLUT_STROKE_ROMAN, 
									   reinterpret_cast<const unsigned char *> (name.c_str()));
			glColor4d(0,1,0,1);
			//Translate to center
			glTranslated(-w/2,0,-50);
			for(int count=0; count < name.length(); count++){
				 glutStrokeCharacter(GLUT_STROKE_ROMAN, name[count]);
			}
		glPopMatrix();
		glTranslated(0,-0.3,0);//Translate down in !typical! axis world
		applyBillboarding();
		glScalef(0.002, 0.002, 0.002);
		string teamstring = "<";
		teamstring+=(char) team;
		teamstring+=">";
		w = glutStrokeLength(GLUT_STROKE_ROMAN, 
							reinterpret_cast<const unsigned char *> (teamstring.c_str()));
		glTranslated(-w/2,0,0);
		for(int count=0; count < teamstring.length(); count++){
			glutStrokeCharacter(GLUT_STROKE_ROMAN, teamstring[count]);
		}
		teamcolor->unselect();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    Object::render();
}

//------------------------------------------------------------------------------

} // namespace Objects

//------------------------------------------------------------------------------
