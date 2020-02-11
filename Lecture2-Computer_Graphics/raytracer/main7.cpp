#include<iostream>
#include"sphere.h"
#include"hitable_list.h"
#include"float.h"
#include "camera.h"
#include<fstream>

bool hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc=r.origin()-center;
	float a=dot(r.direction(),r.direction());
	float b=2.0*dot(oc,r.direction());
	float c=dot(oc,oc)-radius*radius;
	float discriminant =b*b -4*a*c;
	if(discriminant<0){
		return -1.0;
	}
	else
	{
		return (-b-sqrt(discriminant))/(2.0*a);
	}
}

vec3 color(const ray& r,hitable *world)
{
	hit_record rec;


	if(world->hit(r,0.0,MAXFLOAT, rec))
	{
		return 0.5*vec3(rec.normal.x()+1,rec.normal.y()+1,rec.normal.z()+1);
	}
	else
	{
		vec3 unit_direction=unit_vector(r.direction());
		float t=0.5*(unit_direction.y()+1.0);
		return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);
	}
}


int main(){
	int nx=200;
	int ny=100;
	int ns=100;
	std::ofstream fout; 
	fout.open("seventh.ppm");
	fout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
	hitable *list[2];
	list[0]=new sphere(vec3(0,0,-1),0.5);
	list[1]=new sphere(vec3(0,-100.5,-1),100);
	hitable *world=new hitable_list(list,2);
	camera cam;
	for(int j=ny-1;j>=0;j--)
	{
		for(int i=0;i<nx;i++)
		{
			vec3 col(0,0,0);
			for(int s=0;s<ns;s++)
			{
				float u=float(i+drand48())/float(nx);
				float v=float(j+ drand48())/float(ny);
				ray r=cam.get_ray(u,v);
				vec3 p=r.point_at_parameter(2.0);
				col+=color(r,world);
			}
			col/=float(ns);
			int ir=int(255.99*col[0]); 
			int ig=int(255.99*col[1]);
			int ib=int(255.99*col[2]);
			fout<<ir<<" "<<ig<<" "<<ib<<"\n";		
		}	
	}
}