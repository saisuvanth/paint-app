#pragma once

#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>

class Canvas
{

public:
	int width, height;
	int xOffset, yOffset;
	std::string saveFilePath;
	Colour **pixels;
	float zoom;

	std::string fileName;

	void set_values(int w, int h, int xo, int yo)
	{
		fileName = "";
		width = w;
		height = h;
		xOffset = xo;
		yOffset = yo;
		zoom = 3.0f;
		struct Colour white = {1.0f, 1.0f, 1.0f};
		pixels = new Colour *[w];
		for (int x = 0; x < w; ++x)
		{
			pixels[x] = new Colour[h * 5];
			for (int y = 0; y < h; y++)
			{
				pixels[x][y] = white;
			}
		}
	}

	Colour GetPixelColour(int x, int y)
	{
		return pixels[x][y];
	}

	void SetPixelColour(int x, int y, float r, float g, float b)
	{
		struct Colour newColor = {r, g, b};
		pixels[x][y] = newColor;
	}

	void SetPixelColour(int x, int y, Colour c)
	{
		pixels[x][y] = c;
	}

	std::string to_string(float value)
	{
		std::ostringstream os;
		os << value;
		return os.str();
	}

	std::string to_string(int value)
	{
		std::ostringstream os;
		os << value;
		return os.str();
	}

	std::string Serialize()
	{
		std::string output = to_string(width) + "\n" + to_string(height);
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				output += "\n" + to_string(pixels[x][y].r);
				output += "\n" + to_string(pixels[x][y].g);
				output += "\n" + to_string(pixels[x][y].b);
			}
		}
		return output;
	}

	static Canvas Deserialize(std::string data)
	{
		std::string curLine = "";
		int width = -1;
		int height = -1;
		int i = 0;
		while ((width == -1) || (height == -1))
		{
			char c = data[i];
			if (c == '\n')
			{
				if (width == -1)
				{
					width = std::atoi(curLine.c_str());
					curLine = "";
					i++;
					continue;
				}
				if (height == -1)
				{
					height = std::atoi(curLine.c_str());
					curLine = "";
					i++;
					break;
				}
			}
			else
			{
				curLine += c;
			}
			i++;
			if (i > 10000)
			{
				Canvas *newCanvas = new Canvas;
				newCanvas->set_values(500, 500, 100, 100);
				return *newCanvas;
			}
		}

		Canvas *canvasRef = new Canvas;
		canvasRef->set_values(width, height, 100, 100);
		Canvas canvas = *canvasRef;

		curLine = "";
		int pixelNum = 0;
		int coloursDoneInPixel = 0;
		float r;
		float g;
		float b;
		for (int j = i; j < data.size(); j++)
		{
			char c = data[j];
			if (c == '\n')
			{
				if (coloursDoneInPixel == 0)
				{
					r = std::atof(curLine.c_str());
					coloursDoneInPixel++;
				}
				else
				{
					if (coloursDoneInPixel == 1)
					{
						g = std::atof(curLine.c_str());
						coloursDoneInPixel++;
					}
					else
					{
						b = std::atof(curLine.c_str());
						int xIndex = std::floor((double)pixelNum / (double)height);
						int yIndex = pixelNum % height;
						canvas.SetPixelColour(xIndex, yIndex, r, g, b);
						coloursDoneInPixel = 0;
						pixelNum++;
					}
				}
				curLine = "";
			}
			else
			{
				curLine += c;
			}
		}
		return canvas;
	}

	void Draw(int window_width, int window_height)
	{
		glBegin(GL_QUADS);
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				// for each pixel draw a quad - size of quad is equal to the zoom
				glColor3f(pixels[x][y].r, pixels[x][y].g, pixels[x][y].b);
				glVertex2f((x * zoom) + xOffset, window_height - ((y * zoom) + yOffset));
				glVertex2f(((x + 1) * zoom) + xOffset, window_height - ((y * zoom) + yOffset));
				glVertex2f(((x + 1) * zoom) + xOffset, window_height - (((y + 1) * zoom) + yOffset));
				glVertex2f((x * zoom) + xOffset, window_height - (((y + 1) * zoom) + yOffset));
			}
		}
		glEnd();
	}

	bool checkInside(int x, int y)
	{
		if (x >= xOffset)
		{
			if (y >= yOffset)
			{
				if (x < xOffset + (width * zoom))
				{
					if (y < yOffset + (height * zoom))
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	int round(float num)
	{
		return std::ceil(num - 0.5);
	}
};

Canvas NewCanvas(int w, int h, int xOffset, int yOffset)
{
	Canvas *newCanvas = new Canvas;
	newCanvas->set_values(w, h, xOffset, yOffset);
	return *newCanvas;
}

static Canvas currentCanvas;
