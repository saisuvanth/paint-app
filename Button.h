#pragma once

#include <iostream>
#include "Fonts.h"
#include <vector>

class Button;

typedef void (*Callback)(Button button);

class Button
{

public:
	Button() : callback(NULL) {}
	Callback callback;

	bool display, hovering;
	int x_pos, y_pos, width, height;

	std::string text;

	bool checkInside(int x, int y)
	{
		if (x >= x_pos)
		{
			if (y >= y_pos)
			{
				if (x < x_pos + width)
				{
					if (y < y_pos + height)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool Hover(int x, int y)
	{
		hovering = checkInside(x, y);
		return hovering;
	}

	bool Pressed(int button, int state, int x, int y)
	{
		hovering = checkInside(x, y);
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_UP)
			{
				if (hovering)
				{
					if (callback)
					{
						(*callback)((Button) * this);
					}
					return true;
				}
			}
		}
		return hovering;
	}

	void Display(int window_width, int window_height)
	{
		if (display)
		{
			glBegin(GL_QUADS);
			glColor3f(0.8f, 0.8f, 0.8f);
			glVertex2f(x_pos, window_height - y_pos);
			glVertex2f(x_pos + width, window_height - y_pos);
			glVertex2f(x_pos + width, window_height - y_pos - height);
			glVertex2f(x_pos, window_height - y_pos - height);
			glEnd();

			glBegin(GL_QUADS);
			if (hovering)
			{
				glColor3f(0.6f, 0.6f, 0.6f);
			}
			else
			{
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			glVertex2f(x_pos + 2, window_height - y_pos - 2);
			glVertex2f(x_pos + width - 2, window_height - y_pos - 2);
			glVertex2f(x_pos + width - 2, window_height - y_pos - height + 2);
			glVertex2f(x_pos + 2, window_height - y_pos - height + 2);
			glEnd();

			display_text(text, x_pos + 7, window_height - y_pos - height + 10);
		}
	}

	void Show()
	{
		display = true;
	}

	void Hide()
	{
		display = false;
	}

	void HorizontallyCenter(int window_width)
	{
		x_pos = (window_width / 2) - (width / 2);
	}

	void set_values(int x, int y, int w, int h, char *t, Callback c, bool d)
	{
		display = true;
		hovering = false;
		x_pos = x;
		y_pos = y;
		width = w;
		height = h;
		text = t;
		callback = c;
		display = d;
	}

	static Button Create(int x, int y, int w, int h, char *t, Callback c, bool d)
	{
		Button *newButton = new Button;
		newButton->set_values(x, y, w, h, t, c, d);
		return *newButton;
	}
};