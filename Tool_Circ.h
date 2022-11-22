#pragma once

bool Tool_Circ::Pressed(int button, int state, int x, int y)
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
				float radH = (maxX - minX) / 2;
				float radV = (maxY - minY) / 2;
				float centX = (maxX + minX) / 2;
				float centY = (maxY + minY) / 2;
				for (int px = 0; px <= maxX - minX; px++)
				{
					for (int py = 0; py <= maxY - minY; py++)
					{
						if ((std::pow(((px + minX) - centX) / radH, 2) + std::pow(((py + minY) - centY) / radV, 2)) < 1)
						{
							currentCanvas.SetPixelColour(minX + px, minY + py, selectedColour);
						}
					}
				}
			}
			isMouseDown = false;
			return true;
		}
	}
	return false;
}

bool Tool_Circ::BlockMousePress(int button, int state, int x, int y)
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