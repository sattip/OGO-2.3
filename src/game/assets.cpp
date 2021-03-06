/*
 * Assets definitions -- see header file for more info
 */

#include <string.h>

#include <string>

#include "materials.h"
#include "assets.h"
#include "loader3ds.h"

namespace Assets {

using namespace std;

//------------------------------------------------------------------------------

using namespace Materials;

MaterialHandle Grid, SelectedGrid, ErrorGrid;

MaterialHandle WorldMaterial;
MaterialHandle Star;

MaterialHandle Wall;
MaterialHandle Test;
MaterialHandle Cloud;
MaterialHandle Grass;

MaterialHandle Widget;
MaterialHandle WidgetBG;
MaterialHandle Font;
MaterialHandle CrossHair;

namespace HealthBar{
	MaterialHandle Border;
	MaterialHandle Green;
	MaterialHandle Red;
}
    
namespace Icon{ 
   
MaterialHandle Money, Health, RichMine, Mine;
MaterialHandle  Robot_normal,    Robot_red,   Robot_blue;
MaterialHandle Pickaxe_normal, Pickaxe_red, Pickaxe_blue;
MaterialHandle RichPickaxe_normal, RichPickaxe_red, RichPickaxe_blue;
MaterialHandle   Tower_normal,   Tower_red,   Tower_blue;
MaterialHandle      HQ_normal,      HQ_red,      HQ_blue;
MaterialHandle Wall;

}

//------------------------------------------------------------------------------

namespace Model {

//player objects
ObjectHandle HeadObj, BodyObj, GunObj, WrenchObj, WheelObj;
MaterialHandle HeadTex, BodyTex[2], GunTex, WrenchTex, WheelTex[2];

//structure objects
ObjectHandle TurretObj, MineObj, DrillObj, RockObj, HQBaseObj, HQSocketObj, HQCoreObj, HQCoreinvObj;
MaterialHandle TurretTex[3], MineTex[2], DrillTex[2], RockTex, RichRockTex, HQBaseTex[3], HQSocketTex, HQCoreTex[3];
MaterialHandle GhostTex, GhostErrorTex;

//other objects
ObjectHandle CoinObj;
MaterialHandle CoinTex;

}

//------------------------------------------------------------------------------

namespace Effect {

//laser
MaterialHandle Laser[2];

}

//------------------------------------------------------------------------------

void Initialize(int argc, char *argv[])
{
	string path = "./";
	for (int i = 0; i < argc - 1; ++i)
		if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "--path"))
			path = argv[++i];
	
	Grid = TwinMaterial(LineMaterial(5),
		ShadedMaterial(Cf(0.2,0.8,0.2,1), //Ambient
	                   Cf(0.2,0.8,0.2,1), //Diffuse
	                   Cf(0.2,0.8,0.2,1), //Specular
	                   Cf(0.8,1,0,1),     //Emissive
	                   100.0));           //Shininess
	
	SelectedGrid = TwinMaterial(LineMaterial(10),
		ShadedMaterial(Cf(0.01,0.31,0.58,1), //Ambient
	                   Cf(0.01,0.31,0.58,1), //Diffuse
	                   Cf(0.01,0.31,0.58,1), //Specular
	                   Cf(0.49,0.97,1,1),    //Emissive,
	                   100.0));              //Shininess

	ErrorGrid = TwinMaterial(LineMaterial(10),
		ShadedMaterial(Cf(1, 0.14, 0),
			Cf(1, 0.14, 0),
			Cf(1, 0.14, 0),
			Cf(1, 0.14, 0),
			100.0));

	{
		ShadedMaterial shade(Cf(1,0,0,1));
		shade.emissive = Cf(1,1,0.8,1);
		Test = TwinMaterial(shade, TexturedMaterial(path + "assets/textures/terrain/grass1.png"));

		ShadedMaterial greenish(Cf(1,1,0.8,1));
		Wall = TwinMaterial(greenish, TexturedMaterial(path + "assets/textures/terrain/grass1.png"));
	}
	
	Cloud = TexturedMaterial(path + "assets/textures/world/cloud.png");
	Grass = TexturedMaterial(path + "assets/textures/terrain/grass.png");

	WorldMaterial = TwinMaterial(Cloud, ShadedMaterial(Cf(0.5, 0.5, 0.5, 1.0)));
	
	{
		ShadedMaterial light(Cf(1, 1, 1, 1));
		light.emissive = Cf(1, 1, 1, 1);
		Star = light;	
	}

	Widget =  ColorMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	WidgetBG = ColorMaterial(0.184f, 0.31f, 0.31f, 0.7f);
	Font = ColorMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	CrossHair = ColorMaterial(1.0f, 1.0f, 1.0f, 1.0f);
    
    Icon::Money = TexturedMaterial(path + "assets/textures/hud/money.png");
    Icon::Health = TexturedMaterial(path+ "assets/textures/hud/health.png");
    Icon::Mine = TexturedMaterial(path + "assets/textures/hud/mine.png");
	Icon::RichMine = TexturedMaterial(path + "assets/textures/hud/richmine.png");
    Icon::Robot_red = TexturedMaterial(path + "assets/textures/hud/robot_red.png");
    Icon::Robot_blue = TexturedMaterial(path + "assets/textures/hud/robot_blue.png");
    Icon::Robot_normal = TexturedMaterial(path + "assets/textures/hud/robot_normal.png");
    Icon::Pickaxe_normal = TexturedMaterial(path + "assets/textures/hud/pickaxe_normal.png");
    Icon::Pickaxe_blue = TexturedMaterial(path + "assets/textures/hud/pickaxe_blue.png");
    Icon::Pickaxe_red = TexturedMaterial(path + "assets/textures/hud/pickaxe_red.png");
	Icon::RichPickaxe_normal = TexturedMaterial(path + "assets/textures/hud/richpickaxe_normal.png");
    Icon::RichPickaxe_blue = TexturedMaterial(path + "assets/textures/hud/richpickaxe_blue.png");
    Icon::RichPickaxe_red = TexturedMaterial(path + "assets/textures/hud/richpickaxe_red.png");
    Icon::Tower_blue = TexturedMaterial(path + "assets/textures/hud/tower_blue.png");
    Icon::Tower_normal = TexturedMaterial(path + "assets/textures/hud/tower_normal.png");
    Icon::Tower_red = TexturedMaterial(path + "assets/textures/hud/tower_red.png");
    Icon::HQ_normal = TexturedMaterial(path + "assets/textures/hud/headquarter_normal.png");
    Icon::HQ_blue = TexturedMaterial(path + "assets/textures/hud/headquarter_blue.png");
    Icon::HQ_red = TexturedMaterial(path + "assets/textures/hud/headquarter_red.png");
	Icon::Wall = ColorMaterial(1.0f, 1.0f, 1.0f, 1.0f);
    
	//Model objects
	Model::HeadObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/head.3DS");
	Model::BodyObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/body.3DS");
	Model::GunObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/gun.3DS");
	Model::WrenchObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/wrench.3DS");
	Model::WheelObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/wheel.3DS");
	
	Model::TurretObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/turret.3DS");
	Model::MineObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/mine.3DS");
	Model::DrillObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/drill.3DS");
	Model::RockObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/rock.3DS");
	Model::HQBaseObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/HQ_Base.3DS");
	Model::HQSocketObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/HQ_Socket.3DS");
	Model::HQCoreObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/HQ_Core.3DS");
	Model::HQCoreinvObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/HQ_Core_inv.3DS");

	Model::CoinObj = Loader::ModelObject(Pd(), Qd(), path + "assets/models/coin.3DS");

	//Model textures
	Model::HeadTex = TexturedMaterial(path + "assets/textures/models/headtext.png");
	Model::BodyTex[0] = TexturedMaterial(path + "assets/textures/models/robottexred.png");
	Model::BodyTex[1] = TexturedMaterial(path + "assets/textures/models/robottexblue.png");
	Model::GunTex = TexturedMaterial(path + "assets/textures/models/guntextu.png");
	Model::WrenchTex = TexturedMaterial(path + "assets/textures/models/wrenchte.png");
	Model::WheelTex[0] = TexturedMaterial(path + "assets/textures/models/wheeltexred.png");
	Model::WheelTex[1] = TexturedMaterial(path + "assets/textures/models/wheeltexblue.png");
	
	Model::TurretTex[0] = TexturedMaterial(path + "assets/textures/models/turrettered.png");
	Model::TurretTex[1] = TexturedMaterial(path + "assets/textures/models/turretteblue.png");
	Model::TurretTex[2] = TexturedMaterial(path + "assets/textures/models/turrettenormal.png");
	Model::MineTex[0] = TexturedMaterial(path + "assets/textures/models/minetextred.png");
	Model::MineTex[1] = TexturedMaterial(path + "assets/textures/models/minetextblue.png");
	Model::DrillTex[0] = TexturedMaterial(path + "assets/textures/models/drilltexred.png");
	Model::DrillTex[1] = TexturedMaterial(path + "assets/textures/models/drilltexblue.png");
	Model::RockTex = TexturedMaterial(path + "assets/textures/models/rocktext.png");
	Model::RichRockTex = TexturedMaterial(path + "assets/textures/models/rocktextrich.png");
	Model::HQBaseTex[0] = TexturedMaterial(path + "assets/textures/models/HQBasetered.png");
	Model::HQBaseTex[1] = TexturedMaterial(path + "assets/textures/models/HQBaseteblue.png");
	Model::HQBaseTex[2] = TexturedMaterial(path + "assets/textures/models/HQBasetenormal.png");
	Model::HQSocketTex = TexturedMaterial(path + "assets/textures/models/plain.png");
	Model::HQCoreTex[0] = TexturedMaterial(path + "assets/textures/models/HQCoretered.png");
	Model::HQCoreTex[1] = TexturedMaterial(path + "assets/textures/models/HQCoreteblue.png");
	Model::HQCoreTex[2] = TexturedMaterial(path + "assets/textures/models/HQCoretenormal.png");

	Model::CoinTex = TexturedMaterial(path + "assets/textures/models/coin.png");

	Model::GhostTex = ShadedMaterial(Cf(0.196, 0.803, 0.196, 0.3));
	Model::GhostErrorTex = ShadedMaterial(Cf(1.0, 0.0, 0.0, 0.3));
	
	HealthBar::Border = TwinMaterial(LineMaterial(3), ColorMaterial(0.0, 0.0, 0.0, 1.0));
	HealthBar::Green = ColorMaterial(0.0, 1.0, 0.0, 1.0);
	HealthBar::Red = ColorMaterial(1.0, 0.0, 0.0, 1.0);

	//Effect textures
	Effect::Laser[0] = TexturedMaterial(path + "assets/textures/effects/laserred.png");
	Effect::Laser[1] = TexturedMaterial(path + "assets/textures/effects/laserblue.png");
}

//------------------------------------------------------------------------------

void Terminate()
{
	Grid.clear();
	SelectedGrid.clear();
	Test.clear();
	Cloud.clear();
	Grass.clear();

	WorldMaterial.clear();

	Widget.clear();
	Font.clear();
	CrossHair.clear();
	
	Icon::Money.clear();
    Icon::Health.clear();
	Icon::Mine.clear();
    Icon::Robot_red.clear();
    Icon::Robot_blue.clear();
    Icon::Robot_normal.clear();
    Icon::Pickaxe_normal.clear();
    Icon::Pickaxe_blue.clear();
    Icon::Pickaxe_red.clear();
    Icon::Tower_normal.clear();
    Icon::Tower_red.clear();
    Icon::HQ_normal.clear();
    Icon::HQ_blue.clear();
    Icon::HQ_red.clear();
	Icon::RichMine.clear();
	Icon::Wall.clear();

	//Model objects
	Model::HeadObj.clear();
	Model::BodyObj.clear();
	Model::GunObj.clear();
	Model::WrenchObj.clear();
	Model::WheelObj.clear();
	
	Model::TurretObj.clear();
	Model::MineObj.clear();
	Model::DrillObj.clear();
	Model::RockObj.clear();
	Model::HQBaseObj.clear();
	Model::HQSocketObj.clear();
	Model::HQCoreObj.clear();
	Model::HQCoreinvObj.clear();

	Model::CoinObj.clear();

	//Model textures
	Model::HeadTex.clear();
	Model::BodyTex[0].clear();
	Model::BodyTex[1].clear();
	Model::GunTex.clear();
	Model::WrenchTex.clear();
	Model::WheelTex[0].clear();
	Model::WheelTex[1].clear();
	
	Model::TurretTex[0].clear();
	Model::TurretTex[1].clear();
	Model::TurretTex[2].clear();
	Model::MineTex[0].clear();
	Model::MineTex[1].clear();
	Model::DrillTex[0].clear();
	Model::DrillTex[1].clear();
	Model::RockTex.clear();
	Model::RichRockTex.clear();
	Model::HQBaseTex[0].clear();
	Model::HQBaseTex[1].clear();
	Model::HQBaseTex[2].clear();
	Model::HQSocketTex.clear();
	Model::HQCoreTex[0].clear();
	Model::HQCoreTex[1].clear();
	Model::HQCoreTex[2].clear();

	Model::CoinTex.clear();
	
	Model::GhostTex.clear();
	Model::GhostErrorTex.clear();

	//Effect textures
	Effect::Laser[0].clear();
	Effect::Laser[1].clear();
}

//------------------------------------------------------------------------------

} // namespace Assets

//------------------------------------------------------------------------------
