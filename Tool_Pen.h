#pragma once

bool Tool_Pen::Pressed(int button, int state, int x, int y)
{
	if (currentCanvas.checkInside(x, y))
	{
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && !isMouseDown)
		{
			isMouseDown = true;
			mouseLastX = (x - currentCanvas.xOffset) / currentCanvas.zoom;
			mouseLastY = (y - currentCanvas.yOffset) / currentCanvas.zoom;
			return true;
		}
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP) && isMouseDown)
		{
			std::cout << "end drag" << std::endl;
			isMouseDown = false;
			return true;
		}
	}
	return false;
}

bool Tool_Pen::Hover(int x, int y)
{

	if (isMouseDown)
	{
		if (currentCanvas.checkInside(x, y))
		{
			int canvasCoordX = (x - currentCanvas.xOffset) / currentCanvas.zoom;
			int canvasCoordY = (y - currentCanvas.yOffset) / currentCanvas.zoom;

			if ((canvasCoordX == mouseLastX) && (canvasCoordY == mouseLastY))
			{
				currentCanvas.SetPixelColour(canvasCoordX, canvasCoordY, selectedColour);
			}
			else
			{

				int minX = std::min(canvasCoordX, mouseLastX);
				int maxX = std::max(canvasCoordX, mouseLastX);
				int minY = std::min(canvasCoordY, mouseLastY);
				int maxY = std::max(canvasCoordY, mouseLastY);

				double length = std::sqrt(std::pow(maxX - minX, 2) + std::pow(maxY - minY, 2));
				double moveX = (canvasCoordX - mouseLastX) / length;
				double moveY = (canvasCoordY - mouseLastY) / length;

				double curX = mouseLastX;
				double curY = mouseLastY;

				while ((curX <= maxX) && (curY <= maxY) && (curX >= minX) && (curY >= minY))
				{
					currentCanvas.SetPixelColour(round(curX), round(curY), selectedColour);
					curX += moveX;
					curY += moveY;
				}
			}

			mouseLastX = canvasCoordX;
			mouseLastY = canvasCoordY;
		}
		return true;
	}
	return currentCanvas.checkInside(x, y);
}

bool Tool_Pen::BlockMousePress(int button, int state, int x, int y)
{
	if (isMouseDown)
	{
		if (currentCanvas.checkInside(x, y))
		{
			return true;
		}
	}
	isMouseDown = false;
	return false;
}