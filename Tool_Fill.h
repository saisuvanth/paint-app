#pragma once

#include <vector>

struct Tuple
{
	int x;
	int y;
};

void Tool_Fill::Fill(Colour startColour, int cx, int cy)
{
	std::vector<Tuple> vec;
	std::vector<Tuple> newvec;
	Tuple startCoord = {cx, cy};
	vec.push_back(startCoord);
	while (vec.size() > 0)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			Colour colourAtPixel = currentCanvas.GetPixelColour(vec[i].x, vec[i].y);
			if ((colourAtPixel.r == startColour.r) && (colourAtPixel.g == startColour.g) && (colourAtPixel.b == startColour.b))
			{
				currentCanvas.SetPixelColour(vec[i].x, vec[i].y, selectedColour);
				if (vec[i].x < currentCanvas.width - 1)
				{
					Tuple newCoord = {vec[i].x + 1, vec[i].y};
					newvec.push_back(newCoord);
				}
				if (vec[i].x > 0)
				{
					Tuple newCoord = {vec[i].x - 1, vec[i].y};
					newvec.push_back(newCoord);
				}
				if (vec[i].y < currentCanvas.height - 1)
				{
					Tuple newCoord = {vec[i].x, vec[i].y + 1};
					newvec.push_back(newCoord);
				}
				if (vec[i].y > 0)
				{
					Tuple newCoord = {vec[i].x, vec[i].y - 1};
					newvec.push_back(newCoord);
				}
			}
		}
		vec.empty();
		vec = newvec;
		std::vector<Tuple> b;
		newvec = b;
	}
}

bool Tool_Fill::Pressed(int button, int state, int x, int y)
{
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		int canvasCoordX = (x - currentCanvas.xOffset) / currentCanvas.zoom;
		int canvasCoordY = (y - currentCanvas.yOffset) / currentCanvas.zoom;
		Colour colourWherePressed = currentCanvas.GetPixelColour(canvasCoordX, canvasCoordY);
		if ((colourWherePressed.r != selectedColour.r) || (colourWherePressed.g != selectedColour.g) || (colourWherePressed.b != selectedColour.b))
		{
			Tool_Fill::Fill(colourWherePressed, canvasCoordX, canvasCoordY);
			return true;
		}
	}
	return false;
}