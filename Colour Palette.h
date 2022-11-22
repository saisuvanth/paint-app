#pragma once

#include "Canvas.h"

class ColourPalette
{

public:
	static const Colour colours[];

	static int selectedIndex;

	static int palette_x_pos;

	static void Display(int window_width, int window_height)
	{
		palette_x_pos = window_width - 50;
		glBegin(GL_QUADS);
		int xPos = palette_x_pos;
		int yPos = 50;
		for (int i = 0; i < 5; i++)
		{
			if (i == selectedIndex)
			{
				glColor3f(0.6f, 0.6f, 0.6f);
			}
			else
			{
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			glVertex2f(xPos, window_height - yPos);
			glVertex2f(xPos + 50, window_height - yPos);
			glVertex2f(xPos + 50, window_height - (yPos + 50));
			glVertex2f(xPos, window_height - (yPos + 50));
			glColor3f(colours[i].r, colours[i].g, colours[i].b);
			glVertex2f(xPos + 2, window_height - (yPos + 2));
			glVertex2f(xPos + 46, window_height - (yPos + 2));
			glVertex2f(xPos + 46, window_height - (yPos + 46));
			glVertex2f(xPos + 2, window_height - (yPos + 46));
			yPos += 49;
		}
		glEnd();
	}

	static bool checkInside(int x, int y, int x_pos, int y_pos, int width, int height)
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

	static bool Pressed(int button, int state, int x, int y)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_UP)
			{
				int xPos = palette_x_pos;
				int yPos = 50;
				for (int i = 0; i < 5; i++)
				{
					// Check if the mouse is inside each colour rect
					if (checkInside(x, y, xPos, yPos, 50, 50))
					{
						// select the colour
						selectedIndex = i;
						selectedColour = colours[i];
						return true;
					}
					yPos += 49;
				}
			}
		}
		return checkInside(x, y, palette_x_pos, 50, 50, 245);
	}
};