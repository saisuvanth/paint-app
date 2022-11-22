#pragma once

class Cover
{

public:
	static bool show;

	static void Display(int window_width, int window_height)
	{
		if (show)
		{
			glBegin(GL_QUADS);
			glColor4f(0.0f, 0.0f, 0.0f, 0.85f);
			glVertex2f(0, window_height);
			glVertex2f(0 + window_width, window_height);
			glVertex2f(0 + window_width, 0);
			glVertex2f(0, 0);
			glEnd();
		}
	}

	static bool Pressed(int button, int state, int x, int y)
	{
		return show;
	}

	static bool Hover(int x, int y)
	{
		return show;
	}
};