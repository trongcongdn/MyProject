#pragma once
#include "Vector2.h"
#include <vector>
namespace MathHelper
{
	struct Rect{
		float x, y;
		float width, height;
		Rect(const float &x = 0.0f, const float &y = 0.0f, const float &width = 0.0f, const float &height = 0.0f)
			: x(x), y(y), width(width), height(height)
		{}
	};
	struct Circle{
		vector2f c;
		float r;
		Circle(const vector2f &c = (0.0f, 0.0f), const float &r = 0.0f)
			: c(c), r(r)
		{}
		void scale(const float &s);
		void translate(const vector2f &vec);
		bool containtPoint(const vector2f &point);
		bool containtLine(const vector2f &vt1, const vector2f &vt2);
	};
	struct Triangle{
		vector2f a, b, c;
		Triangle(const vector2f &a, const vector2f &b, const vector2f &c)
			:a(a), b(b), c(c)
		{}
	};

	enum class ShapeType { kPolygon, kCircle };

	struct ShapeDef
	{
		std::vector <vector2f> Vertexs;
		ShapeType type;
		vector2f c;
		float r;
		float scaleX;
		float scaleY;
		float rotateAngle;
		float n;
		vector2f rotatePoint;
		ShapeDef(ShapeType type = ShapeType::kPolygon, const float &scaleX = 0.0f, const float &r = 0.0f, const float &scaleY = 0.0f, const float &rotateAngle = 0.0f, const float &n = 0.0f, const vector2f &rotatePoint = (0.0f, 0.0f))
			: type(type), r(r), scaleX(scaleX), scaleY(scaleY), rotateAngle(rotateAngle), n(n), rotatePoint(rotatePoint)
		{}
		void rotate(const float &angle);
		void scale(const float &scaleX, const float &scaleY);
		void translate(const vector2f &vec);
		bool containtPoint(const vector2f &point) const;
		bool containtLine(const vector2f &vt1, const vector2f &vt2) const;
		bool collisionWithShape(const ShapeDef& shapeDefOther) const;
	};
}

