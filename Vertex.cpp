
#include "Vertex.h"


Vertex::Vertex(const Vec3f& pos)
{
	Pos = pos;
	Vertex::LastNormal( &Normal );
	Vertex::LastAmbient( &Ambient );
	Vertex::LastDiffuse( &Diffuse );
	Vertex::LastShiny( &Shiny );
}

Vertex::Vertex(const Vec3f& pos, const Vec3f& normal, const Vec2f& uv , const Colour& diffuse, const Colour& ambient, const Colour& specular, float shinyness)
{
	Pos = pos;
	Normal = normal;
	Vertex::LastNormal(&Normal, true);
	UV = uv;
	Colour def(-1.0f,-1.0f,-1.0f,-1.0f);
	if (diffuse == def)
	{
		Vertex::LastDiffuse(&Diffuse);
	}
	else
	{
		Diffuse = diffuse;
		Vertex::LastDiffuse(&Diffuse, true);
	}
	if (ambient == def)
	{
		Vertex::LastAmbient(&Ambient);
	}
	else
	{
		Ambient = ambient;
		Vertex::LastAmbient(&Ambient, true);
	}

	if (specular == def )
	{
		Vertex::LastSpecular(&Specular);
	}
	else
	{
		Specular = specular;
		Vertex::LastSpecular(&Specular, true);
	}
	if (shinyness == -1)
	{
		Vertex::LastShiny(&Shiny);
	}
	else
	{
		Shiny = shinyness;
		Vertex::LastShiny(&Shiny, true);
	}


}

void Vertex::LastAmbient(Colour *v, bool set)
{
	static Colour Ambient(0.1f,0.1f,0.1f);
	if (set)
	{
		Ambient = *v;
	}
	else
	{
		*v = Ambient;
	}
}

void Vertex::LastDiffuse(Colour *v, bool set)
{
	static Colour diffuse(1,1,1);
	if (set)
	{
		diffuse = *v;
	}
	else
	{
		*v = diffuse;
	}
}

void Vertex::LastNormal(Vec3f *v, bool set)
{
	static Vec3f normal(0,0,1);
	if (set)
	{
		normal = *v;
	}
	else
	{
		*v = normal;
	}
}
 
void Vertex::LastShiny(float *f, bool set)
{
	static float shiny = 100;
	if (set)
	{
		shiny = *f;
	}
	else
	{
		*f = shiny;
	}
}

void Vertex::LastSpecular(Colour* v, bool set)
{
	static Colour specular(1,1,1);
	if(set)
	{
		specular = *v;
	}
	else
	{
		*v = specular;
	}
}

