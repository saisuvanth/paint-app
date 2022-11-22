#pragma once

bool Tool_Rect::Pressed(int button, int state, int x, int y)
{
	if (currentCanvas.checkInside(x, y))
	{
		int cx = (x - currentCanvas.xOffset) / currentCanvas.zoom;
		int cy = (y - currentCanvas.yOffset) / currentCanvas.zoom;
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && !isMouseDown)
		{
			isMouseDown = true;
			startMouseX = cx;
			startMouseY = cy;
			return true;
		}
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP) && isMouseDown)
		{
			if ((startMouseX == cx) && (startMouseY == cy))
			{
				currentCanvas.SetPixelColour(cx, cy, selectedColour);
			}
			else
			{
				int minX = std::min(cx, startMouseX);
				int maxX = std::max(cx, startMouseX);
				int minY = std::min(cy, startMouseY);
				int maxY = std::max(cy, startMouseY);
				for (int px = 0; px <= maxX - minX; px++)
				{
					for (int py = 0; py <= maxY - minY; py++)
					{
						currentCanvas.SetPixelColour(minX + px, minY + py, selectedColour);
					}
				}
			}
			isMouseDown = false;
			return true;
		}
	}
	return false;
}

bool Tool_Rect::BlockMousePress(int button, int state, int x, int y)
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