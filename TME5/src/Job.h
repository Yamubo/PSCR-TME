#pragma once

namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};

// Job concret : exemple

/**
class SleepJob : public Job {
	int calcul (int v) {
		std::cout << "Computing for arg =" << v << std::endl;
		// traiter un gros calcul
		this_thread::sleep_for(1s);
		int ret = v % 255;
		std::cout << "Obtained for arg =" << arg <<  " result " << ret << std::endl;
		return ret;
	}
	int arg;
	int * ret;
public :
	SleepJob(int arg, int * ret) : arg(arg), ret(ret) {}
	void run () {
		* ret = calcul(arg);
	}
	~SleepJob(){}
};
**/



//Job draw ////// à changer de place : mettre dans le main
class DrawJob : public Job {

	//pool submit (new drawjob(x , y , pixel, scene))
	int * x ; 
	int * y ; 
	Color * pixels ; 
	Scene * scene ;
	svector<Vec3D> * lights ;
	const Scene::screen_t & screen ;

public :
	DrawJob( int * x , int * y , Color * pixel , Scene * scene , svector<Vec3D> light , const Scene::screen_t & screen  ): x(x) , y(y) , pixels(pixel) , scene(scene) , lights(light) ,screen(screen) {} 
	void run() {
			// le point de l'ecran par lequel passe ce rayon
			auto & screenPoint = screen[y][x];
			// le rayon a inspecter
			Rayon ray(scene.getCameraPos(), screenPoint);
			
			int targetSphere = findClosestInter(scene, ray);

			if (targetSphere == -1) {
				// keep background color
				return;
			} else {
				const Sphere & obj = *(scene.begin() + targetSphere);
				// pixel prend la couleur de l'objet
				Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
				// le point de l'image (pixel) dont on vient de calculer la couleur
				Color & pixel = pixels[y*scene.getHeight() + x];
				// mettre a jour la couleur du pixel dans l'image finale.
				pixel = finalcolor;
			}
	}
	~DrawJob(){}
};

}
