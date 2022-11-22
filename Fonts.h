#pragma once

#include <cstring>

void draw_text(const char *text)
{
	size_t len = strlen(text);
	for (size_t i = 0; i < len; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
}

void draw_text(std::string text)
{
	size_t len = text.size();
	for (size_t i = 0; i < len; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
}

void display_text(const char *text, float x, float y)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(x, y, 0.0f);
	glScalef(0.22f, 0.22f, 1.0f);
	draw_text(text);
	glPopMatrix();
}

void display_text(std::string text, float x, float y)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(x, y, 0.0f);
	glScalef(0.22f, 0.22f, 1.0f);
	draw_text(text);
	glPopMatrix();
}

void display_text_small(const char *text, float x, float y)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(x, y, 0.0f);
	glScalef(0.17f, 0.17f, 1.0f);
	draw_text(text);
	glPopMatrix();
}

float get_text_width(const char *text)
{
	size_t len = strlen(text);
	int total_width = 0;
	for (size_t i = 0; i < len; i++)
	{
		total_width += glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]);
	}
	return total_width * 0.22f;
}

float get_text_width(std::string text)
{
	size_t len = text.size();
	int total_width = 0;
	for (size_t i = 0; i < len; i++)
	{
		total_width += glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]);
	}
	return total_width * 0.22f;
}

float get_text_width_small(const char *text)
{
	size_t len = strlen(text);
	int total_width = 0;
	for (size_t i = 0; i < len; i++)
	{
		total_width += glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]);
	}
	return total_width * 0.17f;
}
