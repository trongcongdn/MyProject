#pragma once
#include <Vector2.h>

#define kcA 0x41
#define kcD 0x44
#define kcF 0x46
#define kcG 0x47
#define kcS 0x53
#define kcW 0x57

struct MouseInput
{
	vector2f pos;
	bool isPress;
	bool isPressing;
	bool isMoving;
	bool isRlease;
	MouseInput(vector2f pos = (0.0f, 0.0f), bool isPress = false, bool isPressing = false, bool isRlease = false, bool isMoving = false)
		:pos(pos),
		isPress(isPress),
		isPressing(isPressing),
		isMoving(isMoving),
		isRlease(isRlease)
	{}
	void resetInput(){
		isPress = false;
		isMoving = false;
		isRlease = false;
	}
};

struct KeyInput
{
	bool a_is_press;
	bool s_is_press;
	bool w_is_press;
	bool d_is_press;
	bool f_is_press;
	bool g_is_press;
	bool f_is_release;
	bool g_is_release;

	KeyInput()
		:a_is_press(false),
		s_is_press(false),
		w_is_press(false),
		d_is_press(false),
		f_is_press(false),
		g_is_press(false),
		f_is_release(false),
		g_is_release(false)
	{}
};
