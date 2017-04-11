#include "MathHelper.h"
#include <algorithm>

namespace MathHelper
{
	void ShapeDef::rotate(const float &angle)
	{
		switch (type)
		{
		case ShapeType::kCircle:
			break;
		case ShapeType::kPolygon:
			this->rotateAngle = angle;
			for (unsigned int i = 0; i < Vertexs.size(); i++)
			{
				Vertexs[i].rotateA(angle, rotatePoint);
			}
			break;
		default:
			break;
		}
	}
	void ShapeDef::scale(const float &scaleX, const float &scaleY)
	{
		switch (type)
		{
		case ShapeType::kCircle:
			r *= (scaleX + scaleY)/2.0f;
			break;
		case ShapeType::kPolygon:
			this->scaleX = scaleX;
			this->scaleY = scaleY;
			for (unsigned int i = 0; i < Vertexs.size(); i++)
			{
				Vertexs[i].x *= scaleX;
				Vertexs[i].y *= scaleY;
			}
			break;
		default:
			break;
		}
	}
	void ShapeDef::translate(const vector2f &vec)
	{
		switch (type)
		{
		case ShapeType::kCircle:
			c += vec;
			break;
		case ShapeType::kPolygon:
			for (unsigned int i = 0; i < Vertexs.size(); i++)
			{
				Vertexs[i] += vec;
			}
			break;
		default:
			break;
		}
	}
	bool ShapeDef::containtPoint(const vector2f &point)  const
	{
		if (type == ShapeType::kPolygon)
		{
			int i, j, c = 0;
			int nvert = n;
			for (i = 0, j = nvert - 1; i < nvert; j = i++) {
				if (((Vertexs[i].y>point.y) != (Vertexs[j].y>point.y)) &&
					(point.x < (Vertexs[j].x - Vertexs[i].x) * (point.y - Vertexs[i].y) / (Vertexs[j].y - Vertexs[i].y) + Vertexs[i].x))
					c = !c;
			}
			return (bool)c;
		}
		else
		{
			if (c.distance_square_with(point) <= r*r)
				return true;
			return false;
		}
		
	}

	bool ShapeDef::containtLine(const vector2f &vt1, const vector2f &vt2)  const
	{
		if (type == ShapeType::kPolygon)
		{
			int i, j, c = 0;
			int nvert = n;
			for (i = 0, j = nvert - 1; i < nvert; j = i++) {
				float den = ((Vertexs[j].y - Vertexs[i].y)*(vt2.x - vt1.x) - (Vertexs[j].x - Vertexs[i].x)*(vt2.y - vt1.y));
				float num1 = ((Vertexs[j].x - Vertexs[i].x)*(vt1.y - Vertexs[i].y) - (Vertexs[j].y - Vertexs[i].y)*(vt1.x - Vertexs[i].x));
				float num2 = ((vt2.x - vt1.x)*(vt1.y - Vertexs[i].y) - (vt2.y - vt1.y)*(vt1.x - Vertexs[i].x));
				float u1 = num1 / den;
				float u2 = num2 / den;
				if (den == 0 && num1 == 0 && num2 == 0)
					return true;
				if (den == 0)
					continue;
				if (u1 < 0 || u1 > 1 || u2 < 0 || u2 > 1)
					continue;
				return true;
			}
			return false;
		}
		else
		{
			vector2f d = vt2 - vt1;
			vector2f f = vt1 - this->c;
			float a = d.dot_product_with(d);
			float b = 2 * f.dot_product_with(d);
			float c = f.dot_product_with(f) - r*r;

			float discriminant = b*b - 4 * a*c;
			if (discriminant < 0)
			{
				return false;
			}
			else
			{
				discriminant = sqrt(discriminant);
				float t1 = (-b - discriminant) / (2 * a);
				float t2 = (-b + discriminant) / (2 * a);
				if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1))
					return true;
				return false;
			}
		}
		
	}

	bool ShapeDef::collisionWithShape(const ShapeDef& ShapeDefOther)  const
	{
		if ((this->type == ShapeType::kPolygon && ShapeDefOther.type == ShapeType::kPolygon) || (this->type == ShapeType::kCircle && ShapeDefOther.type == ShapeType::kPolygon))
		{
			for (int i = 0; i < ShapeDefOther.n; i++){
				if (this->containtPoint(ShapeDefOther.Vertexs[i]))
					return true;
			}
			return false;
		}
		else if(this->type == ShapeType::kPolygon && ShapeDefOther.type == ShapeType::kCircle)
		{
			for (int i = 0; i < this->n; i++){
				if (ShapeDefOther.containtPoint(this->Vertexs[i]))
					return true;
			}
			return false;
		}
		else if (this->type == ShapeType::kCircle && ShapeDefOther.type == ShapeType::kCircle)
		{
			if (c.distance_square_with(ShapeDefOther.c) <= (r + ShapeDefOther.r)*(r + ShapeDefOther.r))
				return true;
			return false;
		}
	}

	void Circle::scale(const float &s)
	{
		r *= s;
	}
	void Circle::translate(const vector2f &vec)
	{
		c += vec;
	}
	bool Circle::containtPoint(const vector2f &point)
	{
		if (c.distance_square_with(point) <= r*r)
			return true;
		return false;
	}
	bool Circle::containtLine(const vector2f &vt1, const vector2f &vt2)
	{
		vector2f d = vt2 - vt1;
		vector2f f = vt1 - this->c;
		float a = d.dot_product_with(d);
		float b = 2 * f.dot_product_with(d);
		float c = f.dot_product_with(f) - r*r;

		float discriminant = b*b - 4 * a*c;
		if (discriminant < 0)
		{
			return false;
		}
		else
		{
			discriminant = sqrt(discriminant);
			float t1 = (-b - discriminant) / (2 * a);
			float t2 = (-b + discriminant) / (2 * a);
			if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1))
				return true;
			return false;
		}
	}
}