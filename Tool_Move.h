#pragma once

void Tool_Move::Start()
{
	isDisplaying = false;
	isMouseDown = false;
	flickerFrameCount = 20;
	flickerColor = false;
}

void Tool_Move::End()
{
	isDisplaying = false;
	isMouseDown = false;
}

void Tool_Move::Display(int window_width, int window_height)
{
	if ((!Tool_Move::isDisplaying) || isMouseDown)
	{
		glBegin(GL_QUADS);
		glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
		glVertex2f(currentCanvas.xOffset, window_height - currentCanvas.yOffset);
		glVertex2f(currentCanvas.xOffset + (currentCanvas.width * currentCanvas.zoom), window_height - currentCanvas.yOffset);
		glVertex2f(currentCanvas.xOffset + (currentCanvas.width * currentCanvas.zoom), window_height - currentCanvas.yOffset - (currentCanvas.height * currentCanvas.zoom));
		glVertex2f(currentCanvas.xOffset, window_height - currentCanvas.yOffset - (currentCanvas.height * currentCanvas.zoom));
		glEnd();
	}
	else
	{
		glBegin(GL_LINES);
		if (flickerColor)
		{
			glColor4f(0.4f, 0.4f, 1.0f, 1.0f);
		}
		else
		{
			glColor4f(1.0f, 0.4f, 0.4f, 1.0f);
		}
		glVertex2f(currentCanvas.xOffset + (startMouseX * currentCanvas.zoom), window_height - currentCanvas.yOffset - (startMouseY * currentCanvas.zoom));
		glVertex2f(currentCanvas.xOffset + (endMouseX * currentCanvas.zoom), window_height - currentCanvas.yOffset - (startMouseY * currentCanvas.zoom));
		glVertex2f(currentCanvas.xOffset + (endMouseX * currentCanvas.zoom), window_height - currentCanvas.yOffset - (startMouseY * currentCanvas.zoom));
		glVertex2f(currentCanvas.xOffset + (endMouseX * currentCanvas.zoom), window_height - currentCanvas.yOffset - (endMouseY * currentCanvas.zoom));
		glVertex2f(currentCanvas.xOffset + (endMouseX * currentCanvas.zoom), window_height - currentCanvas.yOffset - (endMouseY * currentCanvas.zoom));
		glVertex2f(currentCanvas.xOffset + (startMouseX * currentCanvas.zoom), window_height - currentCanvas.yOffset - (endMouseY * currentCanvas.zoom));
		glVertex2f(currentCanvas.xOffset + (startMouseX * currentCanvas.zoom), window_height - currentCanvas.yOffset - (endMouseY * currentCanvas.zoom));
		glVertex2f(currentCanvas.xOffset + (startMouseX * currentCanvas.zoom), window_height - currentCanvas.yOffset - (startMouseY * currentCanvas.zoom));
		glEnd();
		flickerFrameCount--;
		if (flickerFrameCount <= 0)
		{
			flickerFrameCount = 20;
			flickerColor = !flickerColor;
		}
	}
}

bool Tool_Move::Pressed(int button, int state, int x, int y)
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
			isMouseDown = false;
			endMouseX = cx;
			endMouseY = cy;
			isDisplaying = true;
			return true;
		}
	}
	return false;
}

bool Tool_Move::BlockMousePress(int button, int state, int x, int y)
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

bool Tool_Move::SpecialKey(int key, int x, int y)
{
	if (isDisplaying)
	{
		int minX = std::min(startMouseX, endMouseX);
		int maxX = std::max(startMouseX, endMouseX);
		int minY = std::min(startMouseY, endMouseY);
		int maxY = std::max(startMouseY, endMouseY);
		switch (key)
		{
		case GLUT_KEY_LEFT:
			if (minX > 0)
			{
				Colour white = {1.0f, 1.0f, 1.0f};
				for (int x = 0; x < maxX - minX; x++)
				{
					for (int y = 0; y < maxY - minY; y++)
					{
						currentCanvas.SetPixelColour(minX + x - 1, minY + y, currentCanvas.GetPixelColour(minX + x, minY + y));
						if (x == maxX - minX - 1)
						{
							currentCanvas.SetPixelColour(minX + x, minY + y, white);
						}
					}
				}
				startMouseX--;
				endMouseX--;
				return true;
			}
			break;
		case GLUT_KEY_RIGHT:
			if (maxX < currentCanvas.width)
			{
				Colour white = {1.0f, 1.0f, 1.0f};
				for (int x = maxX - minX - 1; x >= 0; x--)
				{
					for (int y = 0; y < maxY - minY; y++)
					{
						currentCanvas.SetPixelColour(minX + x + 1, minY + y, currentCanvas.GetPixelColour(minX + x, minY + y));
						if (x == 0)
						{
							currentCanvas.SetPixelColour(minX + x, minY + y, white);
						}
					}
				}
				startMouseX++;
				endMouseX++;
				return true;
			}
			break;
		case GLUT_KEY_UP:
			if (minY > 0)
			{
				Colour white = {1.0f, 1.0f, 1.0f};
				for (int x = 0; x < maxX - minX; x++)
				{
					for (int y = 0; y < maxY - minY; y++)
					{
						currentCanvas.SetPixelColour(minX + x, minY + y - 1, currentCanvas.GetPixelColour(minX + x, minY + y));
						if (y == maxY - minY - 1)
						{
							currentCanvas.SetPixelColour(minX + x, minY + y, white);
						}
					}
				}
				startMouseY--;
				endMouseY--;
				return true;
			}
			break;
		case GLUT_KEY_DOWN:
			if (maxY < currentCanvas.height)
			{
				Colour white = {1.0f, 1.0f, 1.0f};
				for (int x = 0; x < maxX - minX; x++)
				{
					for (int y = maxY - minY - 1; y >= 0; y--)
					{
						currentCanvas.SetPixelColour(minX + x, minY + y + 1, currentCanvas.GetPixelColour(minX + x, minY + y));
						if (y == 0)
						{
							currentCanvas.SetPixelColour(minX + x, minY + y, white);
						}
					}
				}
				startMouseY++;
				endMouseY++;
				return true;
			}
			break;
		}
		return true;
	}
	return false;
}
